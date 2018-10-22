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

#define OBD_UART_MODULE		SERCOM0
#define OBD_UART_BAUDRATE	9600//115200
#define OBD_UART_RX_PIN		5  // PA08 - RX
#define OBD_UART_TX_PIN		4 // PA10 - TX
#define OBD_UART_TIMEOUT	0xFFFF

#define OBD_MAX_RX_BUFFER_LENGTH   5

void obd_uart_clk_init(void);
void obd_uart_pin_init(void);
void obd_uart_init(void);
enum status_code obd_uart_write(uint8_t *data);
enum status_code obd_uart_read(uint8_t *read_data, uint8_t data_length);


#endif /* OBD_UART_H_ */