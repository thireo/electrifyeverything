/*
 * uart.h
 *
 * Created: 05-12-2017 21:02:28
 *  Author: Andreas
 */ 


#ifndef SB_UART_H_
#define SB_UART_H_

#include "main.h"

#define SB_UART_MODULE		SERCOM1
#define SB_UART_BAUDRATE	9600
#define SB_UART_RX_PIN		16  // PA08 - RX
#define SB_UART_TX_PIN		18 // PA10 - TX

#define MAX_RX_BUFFER_LENGTH   5

volatile char sb_rx_buffer_array[1024];
volatile static int sb_buff_count;
volatile int line_count;

void sb_uart_write(uint8_t *data);
void sb_uart_clk_init(void);
void sb_uart_pin_init(void);
void sb_uart_init(void);
void sb_reset_buffers(void);

#endif /* SB_UART_H_ */