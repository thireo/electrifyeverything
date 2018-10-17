/*
 * obd_uart.h
 *
 * Created: 14-10-2018 14:47:18
 *  Author: Andreas
 */ 

#ifndef OBD_UART_H_
#define OBD_UART_H_

#include "main.h"
#include "asf.h"
#include "status_codes.h"

#define OBD_BAUDRATE 115200


#define OBD_UART_MODULE  SERCOM1
#define OBD_MUX_SETTING   USART_RX_0_TX_2_XCK_3
#define OBD_PINMUX_PAD0   PINMUX_PB02D_SERCOM5_PAD0//PINMUX_PB08D_SERCOM4_PAD0
#define OBD_PINMUX_PAD1   PINMUX_UNUSED//PINMUX_PB03D_SERCOM5_PAD1//PINMUX_PB09D_SERCOM4_PAD1
#define OBD_PINMUX_PAD2   PINMUX_PA20C_SERCOM5_PAD2
#define OBD_PINMUX_PAD3   PINMUX_UNUSED
#define OBD_BAUDRATE      9600//115200

#define OBD_MAX_RX_BUFFER_LENGTH   5

#define OBD_UART_TIMEOUT 0xFFFF

#define PORTGROUP_A		0
#define PORTGROUP_B		1

#define OBD_RX_PIN	16  // PA08 - RX
#define OBD_TX_PIN	18 // PA10 - TX


volatile char obd_rx_buffer_array[1024];
volatile static int obd_buff_count;
volatile int line_count;



void obd_uart_clk_init(void);
void obd_uart_pin_init(void);
void obd_uart_init(void);

enum status_code obd_uart_write(uint8_t *data);
enum status_code obd_uart_read(uint8_t *read_data, uint8_t data_length);


#endif /* OBD_UART_H_ */