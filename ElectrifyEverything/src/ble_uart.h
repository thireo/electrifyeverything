/*
 * ble_uart.h
 *
 * Created: 09-12-2017 08:43:23
 *  Author: Andreas
 */ 


#ifndef BLE_UART_H_
#define BLE_UART_H_

#include "asf.h"
#include "main.h"

#define BLE_UART_BAUDRATE	9600
#define BLE_UART_RX_PIN		8  // PA08 - RX
#define BLE_UART_TX_PIN		10 // PA10 - TX
#define BLE_UART_SERCOM		SERCOM2



volatile char rx_buffer_array[1024];
volatile static int buff_count;
void reset_buffers(void);


void ble_uart_clk_init(void);
void ble_uart_pin_init(void);
void ble_uart_init(void);
void ble_uart_write(uint8_t *data);

#endif /* BLE_UART_H_ */