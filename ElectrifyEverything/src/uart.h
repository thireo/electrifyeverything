/*
 * uart.h
 *
 * Created: 05-12-2017 21:02:28
 *  Author: Andreas
 */ 


#ifndef UART_H_
#define UART_H_


#define CONF_STDIO_USART_MODULE  SERCOM4
#define CONF_STDIO_MUX_SETTING   USART_RX_1_TX_0_XCK_1
#define CONF_STDIO_PINMUX_PAD2   PINMUX_UNUSED
#define CONF_STDIO_PINMUX_PAD3   PINMUX_UNUSED
#define CONF_STDIO_PINMUX_PAD0   PINMUX_PB08D_SERCOM4_PAD0
#define CONF_STDIO_PINMUX_PAD1   PINMUX_PB09D_SERCOM4_PAD1
#define CONF_STDIO_BAUDRATE      9600

#define MAX_RX_BUFFER_LENGTH   5


void ble_uart_init(void);
void ble_uart_cb_init(void);
void ble_uart_rx_cb(struct usart_module *const ble_uart_module);
void ble_uart_tx_cb(struct usart_module *const ble_uart_module);
void ble_uart_read(void);
void ble_strcmp(void);
void Put_Uart(char buffer[]);

void test_send(void);

#endif /* UART_H_ */