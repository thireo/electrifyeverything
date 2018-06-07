/*
 * uart.c
 *
 * Created: 05-12-2017 21:02:10
 *  Author: Andreas
 */ 

#include "asf.h"
#include "uart.h"
#include "string.h"

struct usart_module ble_uart_module;
/**
 *  Configure console.
 */
/*

volatile uint8_t rx_buffer[MAX_RX_BUFFER_LENGTH];

void ble_uart_init(void)
{		
 	struct usart_config usart_conf;

	usart_get_config_defaults(&usart_conf);
	usart_conf.mux_setting = CONF_STDIO_MUX_SETTING;
	usart_conf.pinmux_pad0 = CONF_STDIO_PINMUX_PAD0;
	usart_conf.pinmux_pad1 = CONF_STDIO_PINMUX_PAD1;
	usart_conf.pinmux_pad2 = CONF_STDIO_PINMUX_PAD2;
	usart_conf.pinmux_pad3 = CONF_STDIO_PINMUX_PAD3;
	usart_conf.baudrate    = CONF_STDIO_BAUDRATE;
	usart_conf.generator_source = GCLK_GENERATOR_1;
	usart_conf.stopbits = USART_STOPBITS_1;
	
	//stdio_serial_init(&ble_uart_module, CONF_STDIO_USART_MODULE, &usart_conf);
	while (usart_init(&ble_uart_module,CONF_STDIO_USART_MODULE, &usart_conf) != STATUS_OK) {
		
    }
	usart_enable(&ble_uart_module);
}


void ble_uart_cb_init(void)
{
	usart_register_callback(&ble_uart_module,ble_uart_tx_cb,USART_CALLBACK_BUFFER_TRANSMITTED);
	usart_register_callback(&ble_uart_module,ble_uart_rx_cb,USART_CALLBACK_BUFFER_RECEIVED);
	
	usart_enable_callback(&ble_uart_module,USART_CALLBACK_BUFFER_TRANSMITTED);
	usart_enable_callback(&ble_uart_module,USART_CALLBACK_BUFFER_RECEIVED);
	
	
	/*uint8_t string[] = "ABCDE";
    usart_write_buffer_job(&ble_uart_module, string, sizeof(string));*/
//}
/*
void ble_uart_tx_cb(struct usart_module *const usart_module)
{
	//asf
}

void ble_uart_rx_cb(struct usart_module *const usart_module)
{
	usart_write_buffer_job(&ble_uart_module,(uint8_t *)rx_buffer,MAX_RX_BUFFER_LENGTH);
	//delay_ms(250);
	//printf("rx\n");
	//printf("WOW: %s",rx_buffer);
}

void ble_uart_read(void)
{
	usart_read_buffer_job(&ble_uart_module,(uint8_t *)rx_buffer, MAX_RX_BUFFER_LENGTH);
}

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

