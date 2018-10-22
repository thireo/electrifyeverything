/*
 * ble_uart.c
 *
 * Created: 09-12-2017 08:43:11
 *  Author: Andreas
 */ 

#include "ble_uart.h"
#include "cmd.h"

typedef enum
{
	UART_TX_PAD_0 = 0x0ul,	// Only for UART
	UART_TX_PAD_2 = 0x1ul,  // Only for UART
	UART_TX_RTS_CTS_PAD_0_2_3 = 0x2ul,  // Only for UART with TX on PAD0, RTS on PAD2 and CTS on PAD3
} SercomUartTXPad;

typedef enum
{
	SERCOM_RX_PAD_0 = 0,
	SERCOM_RX_PAD_1,
	SERCOM_RX_PAD_2,
	SERCOM_RX_PAD_3
} SercomRXPad;


void ble_uart_clk_init(void)
{
	// Start the Software Reset and wait for it to finish
	BLE_UART_SERCOM->USART.CTRLA.bit.SWRST = 1 ;
	while ( BLE_UART_SERCOM->USART.CTRLA.bit.SWRST || BLE_UART_SERCOM->USART.SYNCBUSY.bit.SWRST );
	
	// Turn on peripheral clock for SERCOM being used
	PM->APBCMASK.reg |= PM_APBCMASK_SERCOM2;

	//Setting clock
	GCLK->CLKCTRL.reg =
	GCLK_CLKCTRL_ID( GCM_SERCOM2_CORE )	|	// connected  SERCOMx to
	GCLK_CLKCTRL_GEN_GCLK0		|	// generic Clock Generator 0
	GCLK_CLKCTRL_CLKEN;			// and enable it

	while ( GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY ); // Wait for synchronization
}

void ble_uart_pin_init(void)
{
	PORT->Group[PORTGROUP_A].DIRCLR.reg = PORT_PA08;	// RX as input
	
	PORT->Group[PORTGROUP_A].DIRSET.reg = PORT_PA10;	// TX as output
	PORT->Group[PORTGROUP_A].OUTSET.reg = PORT_PA10;	// TX idle state is high

	// set port multiplexer for peripheral TX
	// =======================================
	uint32_t temp = (PORT->Group[PORTGROUP_A].PMUX[BLE_UART_TX_PIN>>1].reg) & PORT_PMUX_PMUXO( GPIO_SERCOM_ALT_D );
	PORT->Group[PORTGROUP_A].PMUX[BLE_UART_TX_PIN>>1].reg = temp | PORT_PMUX_PMUXE( GPIO_SERCOM_ALT_D );
	
	PORT->Group[PORTGROUP_A].PINCFG[BLE_UART_TX_PIN].reg = PORT_PINCFG_PMUXEN ; // Enable port mux
	temp = (PORT->Group[PORTGROUP_A].PMUX[BLE_UART_RX_PIN>>1].reg) & PORT_PMUX_PMUXO( GPIO_SERCOM_ALT_D );
	PORT->Group[PORTGROUP_A].PMUX[BLE_UART_RX_PIN>>1].reg = temp | PORT_PMUX_PMUXE( GPIO_SERCOM_ALT_D );
	PORT->Group[PORTGROUP_A].PINCFG[BLE_UART_RX_PIN].reg = PORT_PINCFG_PMUXEN | PORT_PINCFG_INEN; // Enable port mux
}

void ble_uart_init(void)
{	
	ble_uart_clk_init();
	ble_uart_pin_init();
	
	
	
	BLE_UART_SERCOM->USART.CTRLA.reg =
	SERCOM_USART_CTRLA_DORD						|	// LSB_FIRST
	SERCOM_USART_CTRLA_TXPO(UART_TX_PAD_2)		|	// TX on Pad2
	SERCOM_USART_CTRLA_RXPO(SERCOM_RX_PAD_0)	|	// RX on Pad0
	SERCOM_USART_CTRLA_SAMPR(SAMPLE_RATE_x16)	|	// 16 times oversampling
	SERCOM_USART_CTRLA_RUNSTDBY					|	// Run in standby mode
	SERCOM_USART_CTRLA_MODE_USART_INT_CLK;			// Use internal clock
	
	
	// Asynchronous arithmetic mode
	// 65535 * ( 1 - sampleRateValue * baudrate / SystemCoreClock);
	// 65535 - 65535 * (sampleRateValue * baudrate / SystemCoreClock));
	BLE_UART_SERCOM->USART.BAUD.reg = 65535.0f * ( 1.0f - (16.0 * (float)(BLE_UART_BAUDRATE)) / (float)(SYSTEM_CLK));
	//BLE_UART_SERCOM->USART.BAUD.bit.BAUD = 9600;
	
	BLE_UART_SERCOM->USART.CTRLB.reg =
	SERCOM_USART_CTRLB_CHSIZE(0)	|	// 8 bit character size
	SERCOM_USART_CTRLB_TXEN			|	// Enable Transmit
	SERCOM_USART_CTRLB_RXEN;			// Enable Receive

	// Get Synced
	while (BLE_UART_SERCOM->USART.SYNCBUSY.bit.CTRLB);

	//Set the Interrupt to use
	BLE_UART_SERCOM->USART.INTENSET.reg = SERCOM_USART_INTENSET_RXC;	// Interrupt on received complete
	
	// Enable interrupts
	NVIC_EnableIRQ(SERCOM2_IRQn);
	NVIC_SetPriority(SERCOM2_IRQn,1);
	
	// enable the peripheral block
	BLE_UART_SERCOM->USART.CTRLA.bit.ENABLE = 0x1u;
	
	// Wait for sercom to enable
	while(BLE_UART_SERCOM->USART.SYNCBUSY.bit.ENABLE);
	
	reset_buffers();
}

void ble_uart_write(uint8_t *data)
{
	system_interrupt_disable_global();
	uint32_t i = 0;
	while(data[i] != '\0')
	{
		if(BLE_UART_SERCOM->USART.INTFLAG.bit.DRE == 1)
		{
			BLE_UART_SERCOM->USART.DATA.reg = (uint16_t)data[i++];
		}
	}
	system_interrupt_enable_global();
}

void SERCOM2_Handler()
{
	if (BLE_UART_SERCOM->USART.INTFLAG.bit.RXC)
	{
		//while (BLE_UART_SERCOM->USART.INTFLAG.bit.DRE != 0 )
		//{
			// Got a character
			if (buff_count > sizeof(rx_buffer_array)-1)
			{
				buff_count = 0;
				rx_buffer_array[buff_count] = (uint8_t) BLE_UART_SERCOM->USART.DATA.reg;
			}
			else
			{
				rx_buffer_array[buff_count++] = (uint8_t)BLE_UART_SERCOM->USART.DATA.reg;
			}
		//}

	}
}

void reset_buffers()
{
	for (uint32_t k=0;k<sizeof(rx_buffer_array);k++)
	{
		rx_buffer_array[k] = 0;
	}
	buff_count = 0;
}

/*void SERCOM2_Handler()
{
	static int i = 0;
	if (BLE_UART_SERCOM->USART.INTFLAG.bit.RXC)
	{
		// Got a character
		uint8_t rxData = (uint8_t) (0x00FF & BLE_UART_SERCOM->USART.DATA.reg);
		if (rxData != 10) //ikke linje skift
		{
			rx_buffer_array[i++] = (char)rxData;
		}
		else
		{
			//ble_uart_write(rx_buffer_array);
			data_handler(rx_buffer_array);
			i = 0;
			
			for (int k=0;k<sizeof(rx_buffer_array);k++)
			{
				rx_buffer_array[k] = 0;
			}
		}
		return;
	}
}*/