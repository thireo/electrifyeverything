/*
 * uart.c
 *
 * Created: 05-12-2017 21:02:10
 *  Author: Andreas
 */ 

#include "asf.h"
#include "uart.h"
#include "string.h"

struct usart_module uart_instance;
/**
 *  Configure console.
 */


volatile uint8_t uart_rx_buffer[MAX_RX_BUFFER_LENGTH];

void uart_init(void)
{		
 	struct usart_config usart_conf;

	usart_get_config_defaults(&usart_conf);
	usart_conf.mux_setting = CONF_STDIO_MUX_SETTING;
	usart_conf.pinmux_pad0 = CONF_STDIO_PINMUX_PAD0;
	usart_conf.pinmux_pad1 = CONF_STDIO_PINMUX_PAD1;
	usart_conf.pinmux_pad2 = CONF_STDIO_PINMUX_PAD2;
	usart_conf.pinmux_pad3 = CONF_STDIO_PINMUX_PAD3;
	//usart_conf.baudrate    = CONF_STDIO_BAUDRATE;
	usart_conf.generator_source = GCLK_GENERATOR_3;
	//usart_conf.stopbits = USART_STOPBITS_1;
	
		// Start the Software Reset and wait for it to finish
	CONF_STDIO_USART_MODULE->USART.CTRLA.bit.SWRST = 1 ;
	while ( CONF_STDIO_USART_MODULE->USART.CTRLA.bit.SWRST || CONF_STDIO_USART_MODULE->USART.SYNCBUSY.bit.SWRST );
	
	// Turn on peripheral clock for SERCOM being used
	PM->APBCMASK.reg |= PM_APBCMASK_SERCOM5;

	//Setting clock
	GCLK->CLKCTRL.reg =
	GCLK_CLKCTRL_ID( (0x19U) )	|	// connected  SERCOMx to
	GCLK_CLKCTRL_GEN_GCLK3		|	// generic Clock Generator 0
	GCLK_CLKCTRL_CLKEN;			// and enable it

	while ( GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY ); // Wait for synchronization
	
	
	PORT->Group[1].DIRCLR.reg = PORT_PB03;	// RX as input
	
	PORT->Group[1].DIRSET.reg = PORT_PB02;	// TX as output
	PORT->Group[1].OUTSET.reg = PORT_PB02;	// TX idle state is high

	// set port multiplexer for peripheral TX
	// =======================================
	uint32_t temp = (PORT->Group[1].PMUX[2>>1].reg) & PORT_PMUX_PMUXO( 3 );
	PORT->Group[1].PMUX[2>>1].reg = temp | PORT_PMUX_PMUXE( 3 );
	
	PORT->Group[1].PINCFG[2].reg = PORT_PINCFG_PMUXEN ; // Enable port mux
	temp = (PORT->Group[1].PMUX[3>>1].reg) & PORT_PMUX_PMUXO( 3 );
	PORT->Group[1].PMUX[3>>1].reg = temp | PORT_PMUX_PMUXE( 3 );
	PORT->Group[1].PINCFG[3].reg = PORT_PINCFG_PMUXEN | PORT_PINCFG_INEN; // Enable port mux
	
		
	CONF_STDIO_USART_MODULE->USART.CTRLA.reg =
	SERCOM_USART_CTRLA_DORD						|	// LSB_FIRST
	SERCOM_USART_CTRLA_TXPO(0)		|	// TX on Pad2
	SERCOM_USART_CTRLA_RXPO(1)	|	// RX on Pad0
	SERCOM_USART_CTRLA_SAMPR(0)	|	// 16 times oversampling
	SERCOM_USART_CTRLA_RUNSTDBY					|	// Run in standby mode
	SERCOM_USART_CTRLA_MODE_USART_INT_CLK;			// Use internal clock
	
	
	// Asynchronous arithmetic mode
	// 65535 * ( 1 - sampleRateValue * baudrate / SystemCoreClock);
	// 65535 - 65535 * (sampleRateValue * baudrate / SystemCoreClock));
	CONF_STDIO_USART_MODULE->USART.BAUD.reg = 65535.0f * ( 1.0f - (16.0 * (float)(BAUDRATE)) / (float)(SYSTEM_CLK));
	//BLE_UART_SERCOM->USART.BAUD.bit.BAUD = 9600;
	
	CONF_STDIO_USART_MODULE->USART.CTRLB.reg =
	SERCOM_USART_CTRLB_CHSIZE(0)	|	// 8 bit character size
	SERCOM_USART_CTRLB_TXEN			|	// Enable Transmit
	SERCOM_USART_CTRLB_RXEN;			// Enable Receive

	// Get Synced
	while (CONF_STDIO_USART_MODULE->USART.SYNCBUSY.bit.CTRLB);

	//Set the Interrupt to use
	//CONF_STDIO_USART_MODULE->USART.INTENSET.reg = SERCOM_USART_INTENSET_RXC;	// Interrupt on received complete
	
	/*// Enable interrupts
	NVIC_EnableIRQ(SERCOM2_IRQn);
	NVIC_SetPriority(SERCOM2_IRQn,1);*/
	
	// enable the peripheral block
	CONF_STDIO_USART_MODULE->USART.CTRLA.bit.ENABLE = 0x1u;
	
	// Wait for sercom to enable
	while(CONF_STDIO_USART_MODULE->USART.SYNCBUSY.bit.ENABLE);
	
}


void uart_cb_init(void)
{
	usart_register_callback(&uart_instance,uart_tx_cb,USART_CALLBACK_BUFFER_TRANSMITTED);
	usart_register_callback(&uart_instance,uart_rx_cb,USART_CALLBACK_BUFFER_RECEIVED);
	
	usart_enable_callback(&uart_instance,USART_CALLBACK_BUFFER_TRANSMITTED);
	usart_enable_callback(&uart_instance,USART_CALLBACK_BUFFER_RECEIVED);
}
	
	
	/*uint8_t string[] = "ABCDE";
    usart_write_buffer_job(&ble_uart_module, string, sizeof(string));*/
//}

void uart_tx_cb(struct usart_module *const usart_module)
{
	//asf
}

void uart_rx_cb(struct usart_module *const usart_module)
{
	usart_write_buffer_job(&uart_instance,(uint8_t *)uart_rx_buffer,MAX_RX_BUFFER_LENGTH);
	//delay_ms(250);
	//printf("rx\n");
	//printf("WOW: %s",rx_buffer);
}

void uart_read(void)
{
	usart_read_buffer_job(&uart_instance,(uint8_t *)uart_rx_buffer, MAX_RX_BUFFER_LENGTH);
}

void uart_write(uint8_t* data)
{
	uint32_t i = 0;
	while(data[i] != '\0')
	{
		if(CONF_STDIO_USART_MODULE->USART.INTFLAG.bit.DRE == 1)
		{
			CONF_STDIO_USART_MODULE->USART.DATA.reg = (uint16_t)data[i++];
		}
	}
}


/*
char test[] = "bob";
volatile uint8_t buffer[];
void ble_strcmp(void)
{
	static int i = 0;
	if (rx_buffer[0] == 0)
	{
		buffer[i] = 0;
		i = 0;
	}
	else
	{
		buffer[i++] = rx_buffer;
		//printf("%d",i);
	}
	
	
	//printf("STRING: %s\n",strcat(buffer,rx_buffer));
	if (strncmp(buffer,test,sizeof(test)) == 0)
	{
		//printf("ACK %d\n",sizeof(rx_buffer));
		Put_Uart("test");
	}
}

void Put_Uart(char buffer[])
{
	uint32_t i = 0;
	while(buffer[i] != '\0')
	{
		if(SERCOM4->USART.INTFLAG.bit.DRE == 1)
		{
			SERCOM4->USART.DATA.reg = buffer[i++];
		}
	}	
}

void test_send(void)
{
	uint8_t string[] = "Hello Kitty\r\n";
	usart_write_buffer_wait(&ble_uart_module,string,sizeof(string));
}
*/

//
///*Assigning pin to the alternate peripheral function*/
//static inline void pin_set_peripheral_function(uint32_t pinmux)
//{
	//uint8_t port = (uint8_t)((pinmux >> 16)/32);
	//PORT->Group[port].PINCFG[((pinmux >> 16) - (port*32))].bit.PMUXEN = 1;
	//PORT->Group[port].PMUX[((pinmux >> 16) - (port*32))/2].reg &= ~(0xF << (4 * ((pinmux >>
	//16) & 0x01u)));
	//PORT->Group[port].PMUX[((pinmux >> 16) - (port*32))/2].reg |= (uint8_t)((pinmux &
	//0x0000FFFF) << (4 * ((pinmux >> 16) & 0x01u)));
//}

