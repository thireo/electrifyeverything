/*
 * DS18B20.c
 *
 * Created: 26-12-2017 21:36:10
 *  Author: Andreas Thirsbro
 */ 
#include "ds18b20.h"
/*
void ds18b20_port_init()
{
	struct port_config config_port_pin;
	port_get_config_defaults(&config_port_pin);
	config_port_pin.input_pull = PORT_PIN_PULL_NONE;
	config_port_pin.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(DS18B20_PIN_1,&config_port_pin);
}

void ds18b20_port_output()
{
	struct port_config config_port_pin;
	port_get_config_defaults(&config_port_pin);
	config_port_pin.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(DS18B20_PIN_1,&config_port_pin);
}

void ds18b20_port_input()
{
	struct port_config config_port_pin;
	port_get_config_defaults(&config_port_pin);
	config_port_pin.direction = PORT_PIN_DIR_INPUT;
	port_pin_set_config(DS18B20_PIN_1,&config_port_pin);
}

uint8_t ds18b20_read_bit(void)
{
	system_interrupt_disable_global();
	ds18b20_port_output();
	port_pin_set_output_level(DS18B20_PIN_1,false);
	delay_us(3);
	ds18b20_port_input();
	uint8_t read_bit = port_pin_get_input_level(DS18B20_PIN_1);
	system_interrupt_enable_global();
	delay_us(53);
	return read_bit;
}

uint8_t ds18b20_reset(void)
{
	uint8_t read_bit;
	uint8_t retries = 125;
	system_interrupt_disable_global();
	ds18b20_port_input();
	system_interrupt_enable_global();
	// wait until the wire is high... just in case
	do {
		if (--retries == 0) return 0;
		delay_us(2);
	} while ( !port_pin_get_input_level(DS18B20_PIN_1));

	system_interrupt_disable_global();
	ds18b20_port_output();
	port_pin_set_output_level(DS18B20_PIN_1,false);
	system_interrupt_enable_global();
	delay_us(480);
	system_interrupt_disable_global();
	ds18b20_port_input();	// allow it to float
	//delay_us(70);
	delay_us(200);
	bool read_bool = !port_pin_get_input_level(DS18B20_PIN_1);
	system_interrupt_enable_global();
	delay_us(410);
	return read_bit;
}*/