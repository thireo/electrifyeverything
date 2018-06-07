/*
 * msgeq7.c
 *
 * Created: 22-04-2018 20:16:27
 *  Author: Andreas
 */ 
#include "msgeq7.h"

struct adc_module adc_instance;

void msgeq7_init()
{
	msgeq7_port_init();
	msgeq7_adc_init();
}

void msgeq7_port_init()
{
	struct port_config config_port_pin;
	port_get_config_defaults(&config_port_pin);
	config_port_pin.input_pull = PORT_PIN_PULL_DOWN;
	config_port_pin.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(MSGEQ7_PIN_RESET,&config_port_pin);
	port_pin_set_output_level(MSGEQ7_PIN_RESET,false);
	config_port_pin.input_pull = PORT_PIN_PULL_UP;
	port_pin_set_config(MSGEQ7_PIN_STROBE,&config_port_pin);
	port_pin_set_output_level(MSGEQ7_PIN_STROBE,true);
}

void msgeq7_adc_init()
{
	struct adc_config config_adc;
	adc_get_config_defaults(&config_adc);
	
	config_adc.gain_factor = ADC_GAIN_FACTOR_1X;
	config_adc.positive_input = ADC_POSITIVE_INPUT_PIN2; //PIN_PB08
	config_adc.differential_mode = false;
	config_adc.negative_input = ADC_NEGATIVE_INPUT_GND;
	
	adc_init(&adc_instance, ADC, &config_adc);
	adc_enable(&adc_instance);
}


uint16_t single_conversion()
{
	adc_start_conversion(&adc_instance);
	uint16_t result;

	do {
		/* Wait for conversion to be done and read out result */
	} while (adc_read(&adc_instance, &result) == STATUS_BUSY);
	return result;
}

void msgeq7_all_bands(uint16_t bands[])
{
	port_pin_set_output_level(MSGEQ7_PIN_RESET,true);
	delay_us(1);
	port_pin_set_output_level(MSGEQ7_PIN_RESET,false);
	delay_us(75);
	
	for (int i=0;i<7;i++)
	{
		port_pin_set_output_level(MSGEQ7_PIN_STROBE,false);
		delay_us(40);
		bands[i] = single_conversion();
		port_pin_set_output_level(MSGEQ7_PIN_STROBE,true);
		delay_us(40);
	}
}