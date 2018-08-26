/*
 * uart.h
 *
 * Created: 05-12-2017 21:02:28
 *  Author: Andreas
 */ 


#ifndef UART_H_
#define UART_H_

#define BAUDRATE 115200
#define SYSTEM_CLK 8000000

#define CONF_STDIO_USART_MODULE  SERCOM1
#define CONF_STDIO_MUX_SETTING   USART_RX_0_TX_2_XCK_3
#define CONF_STDIO_PINMUX_PAD0   PINMUX_PB02D_SERCOM5_PAD0//PINMUX_PB08D_SERCOM4_PAD0
#define CONF_STDIO_PINMUX_PAD1   PINMUX_UNUSED//PINMUX_PB03D_SERCOM5_PAD1//PINMUX_PB09D_SERCOM4_PAD1
#define CONF_STDIO_PINMUX_PAD2   PINMUX_PA20C_SERCOM5_PAD2
#define CONF_STDIO_PINMUX_PAD3   PINMUX_UNUSED
#define CONF_STDIO_BAUDRATE      115200

#define MAX_RX_BUFFER_LENGTH   5

#define PORTGROUP_A		0
#define PORTGROUP_B		1

#define RX_PIN	16  // PA08 - RX
#define TX_PIN	18 // PA10 - TX


volatile char sb_rx_buffer_array[1024];
volatile static int sb_buff_count;

void uart_init(void);
void uart_cb_init(void);
void uart_rx_cb(struct usart_module *const ble_uart_module);
void uart_tx_cb(struct usart_module *const ble_uart_module);
void uart_read(void);


void sb_uart_write(char buffer[]);
void sb_uart_clk_init(void);
void sb_uart_pin_init(void);
void sb_uart_init(void);
void sb_reset_buffers(void);

/*
void strcmp(void);
void Put_Uart(char buffer[]);*/

void test_send(void);

#endif /* UART_H_ */