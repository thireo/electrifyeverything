/*
 * uart.c
 *
 * Created: 05-12-2017 21:02:10
 *  Author: Andreas
 */ 

#include "asf.h"
#include "uart.h"
#include "string.h"

/**
 *  Configure console.
 */


void sb_uart_clk_init(void)
{
	// Start the Software Reset and wait for it to finish
	CONF_STDIO_USART_MODULE->USART.CTRLA.bit.SWRST = 1 ;
	while ( CONF_STDIO_USART_MODULE->USART.CTRLA.bit.SWRST || CONF_STDIO_USART_MODULE->USART.SYNCBUSY.bit.SWRST );
	
	// Turn on peripheral clock for SERCOM being used
	PM->APBCMASK.reg |= PM_APBCMASK_SERCOM1;

	//Setting clock
	GCLK->CLKCTRL.reg =
	GCLK_CLKCTRL_ID( 0x15U )	|	// connected  SERCOMx to
	GCLK_CLKCTRL_GEN_GCLK0		|	// generic Clock Generator 3
	GCLK_CLKCTRL_CLKEN;			// and enable it

	while ( GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY ); // Wait for synchronization
}

void sb_uart_pin_init(void)
{
	PORT->Group[PORTGROUP_A].DIRCLR.reg = PORT_PA16;	// RX as input
	
	PORT->Group[PORTGROUP_A].DIRSET.reg = PORT_PA18;	// TX as output
	PORT->Group[PORTGROUP_A].OUTSET.reg = PORT_PA18;	// TX idle state is high

	// set port multiplexer for peripheral TX
	// =======================================
	uint32_t temp = (PORT->Group[PORTGROUP_A].PMUX[TX_PIN>>1].reg) & PORT_PMUX_PMUXO( PORT_PMUX_PMUXO_C_Val );
	PORT->Group[PORTGROUP_A].PMUX[TX_PIN>>1].reg = temp | PORT_PMUX_PMUXE( PORT_PMUX_PMUXE_C_Val );
	
	PORT->Group[PORTGROUP_A].PINCFG[TX_PIN].reg = PORT_PINCFG_PMUXEN ; // Enable port mux
	temp = (PORT->Group[PORTGROUP_A].PMUX[RX_PIN>>1].reg) & PORT_PMUX_PMUXO( PORT_PMUX_PMUXO_C_Val );
	PORT->Group[PORTGROUP_A].PMUX[RX_PIN>>1].reg = temp | PORT_PMUX_PMUXE( PORT_PMUX_PMUXE_C_Val );
	PORT->Group[PORTGROUP_A].PINCFG[RX_PIN].reg = PORT_PINCFG_PMUXEN | PORT_PINCFG_INEN; // Enable port mux
}

void sb_uart_init(void)
{
	sb_uart_clk_init();
	sb_uart_pin_init();
	
	sb_buff_count = 0;
	
	CONF_STDIO_USART_MODULE->USART.CTRLA.reg =
	SERCOM_USART_CTRLA_DORD						|	// LSB_FIRST
	SERCOM_USART_CTRLA_TXPO(0)					|	// TX on Pad2
	SERCOM_USART_CTRLA_RXPO(2)					|	// RX on Pad0
	SERCOM_USART_CTRLA_SAMPR(0)					|	// 16 times oversampling
	SERCOM_USART_CTRLA_RUNSTDBY					|	// Run in standby mode
	SERCOM_USART_CTRLA_MODE_USART_INT_CLK;			// Use internal clock
	
	
	// Asynchronous arithmetic mode
	// 65535 * ( 1 - sampleRateValue * baudrate / SystemCoreClock);
	// 65535 - 65535 * (sampleRateValue * baudrate / SystemCoreClock));
	CONF_STDIO_USART_MODULE->USART.BAUD.reg = 65535.0f * ( 1.0f - (16.0 * (float)(9600)) / (float)(SYSTEM_CLK));
	//BLE_UART_SERCOM->USART.BAUD.bit.BAUD = 9600;
	
	CONF_STDIO_USART_MODULE->USART.CTRLB.reg =
	SERCOM_USART_CTRLB_CHSIZE(0)	|	// 8 bit character size
	SERCOM_USART_CTRLB_TXEN			|	// Enable Transmit
	SERCOM_USART_CTRLB_RXEN;			// Enable Receive

	// Get Synced
	while (CONF_STDIO_USART_MODULE->USART.SYNCBUSY.bit.CTRLB);

	//Set the Interrupt to use
	CONF_STDIO_USART_MODULE->USART.INTENSET.reg = SERCOM_USART_INTENSET_RXC;	// Interrupt on received complete
	
	// Enable interrupts
	NVIC_EnableIRQ(SERCOM1_IRQn);
	NVIC_SetPriority(SERCOM1_IRQn,1);
	
	// enable the peripheral block
	CONF_STDIO_USART_MODULE->USART.CTRLA.bit.ENABLE = 0x1u;
	
	// Wait for sercom to enable
	while(CONF_STDIO_USART_MODULE->USART.SYNCBUSY.bit.ENABLE);
}


void SERCOM1_Handler()
{
	if (CONF_STDIO_USART_MODULE->USART.INTFLAG.bit.RXC)
	{
		char temp = (uint8_t) CONF_STDIO_USART_MODULE->USART.DATA.reg;
		if (temp != '\0')
		{
			// Got a character
			if (sb_buff_count > sizeof(sb_rx_buffer_array)-1)
			{
				sb_buff_count = 0;
				sb_rx_buffer_array[sb_buff_count] = (uint8_t) CONF_STDIO_USART_MODULE->USART.DATA.reg;
			}
			else
			{
				sb_rx_buffer_array[sb_buff_count++] = (uint8_t)CONF_STDIO_USART_MODULE->USART.DATA.reg;
			}
		}

	}
}

void sb_uart_write(char buffer[])
{
	uint32_t i = 0;
	while(buffer[i] != '\0')
	{
		if(CONF_STDIO_USART_MODULE->USART.INTFLAG.bit.DRE == 1)
		{
			CONF_STDIO_USART_MODULE->USART.DATA.reg = (uint16_t)buffer[i++];
		}
	}
}

void sb_reset_buffers(void)
{
	for (uint32_t k=0;k<sizeof(sb_rx_buffer_array);k++)
	{
		sb_rx_buffer_array[k] = 0;
	}
	sb_buff_count = 0;
}






