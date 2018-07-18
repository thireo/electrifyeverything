/*
 * DS18B20.h
 *
 * Created: 26-12-2017 21:36:33
 *  Author: Andreas Thirsbro
 */ 


#ifndef DS18B20_H_
#define DS18B20_H_
#include "asf.h"

#define DS18B20_PIN_1 PIN_PA21


#define DS18B20_START_CONV			0x44
#define DS18B20_READ_SCRATCH_PADD	0xBE
#define DS18B20_WRITE_SCRATCH_PAD	0x4E
#define DS18B20_COPY_SCRATCH_PAD	0x48
#define DS18B20_RECALL_EEPROM		0xB8
#define DS18B20_READ_PSU			0xB4


/*void ds18b20_port_init();
void ds18b20_port_output();
void ds18b20_port_input();
uint8_t ds18b20_read_bit(void);
uint8_t ds18b20_reset(void);
*/

#endif /* DS18B20_H_ */