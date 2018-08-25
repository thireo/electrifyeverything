/*
 * ble_uart.h
 *
 * Created: 09-12-2017 08:43:23
 *  Author: Andreas
 */ 


#ifndef BLE_UART_H_
#define BLE_UART_H_

#include "asf.h"


#define PORTGROUP_A		0
#define PORTGROUP_B		1

#define BAUDRATE 9600
#define SYSTEM_CLK 8000000


#define RX_PIN	8  // PA08 - RX
#define TX_PIN	10 // PA10 - TX


#define GPIO_SERCOM_ALT_D 3 //peripheral function D - SERCOM-ALT

#define BLE_UART_SERCOM SERCOM2

// defines for SAMD21
#define GCM_SERCOM0_CORE          (0x14U)
#define GCM_SERCOM1_CORE          (0x15U)
#define GCM_SERCOM2_CORE          (0x16U)
#define GCM_SERCOM3_CORE          (0x17U)
#define GCM_SERCOM4_CORE          (0x18U)
#define GCM_SERCOM5_CORE          (0x19U)



#define SAMPLE_RATE_x16 0


volatile char rx_buffer_array[1024];
volatile static int buff_count;
void reset_buffers(void);


void ble_uart_clk_init(void);
void ble_uart_pin_init(void);
void ble_uart_init(void);
void ble_uart_write(char buffer[]);
void Uart_write(const uint16_t data);

#endif /* BLE_UART_H_ */