/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to system_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include "main.h"
//#include "uart.h"
#include "ble_uart.h"
//#include "ads1115.h"
#include "mcp23017.h"
#include "i2c.h"
#include "cmd.h"
#include "pwm.h"
#include "sounds.h"
#include "msgeq7.h"

//#include "ds18b20.h"

//extern uint8_t rx_buffer[MAX_RX_BUFFER_LENGTH];



char buffer[32];



int main (void)
{
	
	system_init();
	delay_init();
	ble_uart_init();
	configure_i2c_master();
	
	uint8_t states = init_all_ports();
	sprintf(buffer,"I2C: %d%d%d%d%d%d%d%d",(states >> 7)&0x01,(states >> 6)&0x01,(states >> 5)&0x01,(states >> 4)&0x01,(states >> 3)&0x01,(states >> 2)&0x01,(states >> 1)&0x01,(states >> 0)&0x01);
	
	ble_uart_write(buffer);
	
	sounds_init_pins();
	
	pwm_port();
	init_TC3();
	
	//select_audio_out();
	
	msgeq7_init();
	select_sample();
	
	
	
	/*select_mth();
	press_mth_btn(MTH_EN);
	press_mth_btn(MTH_BTN2);
	release_mth_btn(MTH_BTN2);
	select_soundboard();*/

	/*press_sb_btn(SB_PIN_BTN01);
	release_sb_btn(SB_PIN_BTN01);*/
	
	//ble_uart_cb_init();
	
	/*
	ds18b20_port_init();
	delay_ms(100);
	port_pin_set_output_level(DS18B20_PIN_1,false);
	delay_us(250);
	port_pin_set_output_level(DS18B20_PIN_1,true);
	delay_us(500);
	port_pin_set_output_level(DS18B20_PIN_1,true);
	delay_us(150);
	port_pin_set_output_level(DS18B20_PIN_1,false);	
	
	uint8_t read_bit = ds18b20_reset();
	read_bit = ds18b20_reset();*/
	
	
	
	
	//system_interrupt_enable_global();
	
	
	/*
	ADS1115_configure_extint_channel();
	ADS1115_configure_extint_callbacks();
	delay_ms(1000);
		
	system_interrupt_enable_global();
	config_data_bytes config;
	config.OS = ADS1115_SS_START;
	config.MUX = ADS1115_MUX_AIN0_GND;
	config.PGA = ADS1115_PGA_6_144_V;
	config.MODE = ADS1115_MODE_SS;
	config.DR = ADS1115_DR_250_SPS;
	config.COMP_MODE = ADS1115_COMP_MODE_TRADITIONAL;
	config.COMP_POL = ADS1115_COMP_POL_LOW;
	config.COMP_LAT = ADS1115_COMP_LAT_DEF;
	config.COMP_QUE = ADS1115_COMP_QUE_DISABLE;
	ADS1115_set_config(config);
	ADS1115_enable_ready_pin();*/
	

	//flashyfade = true;

	
	while (1)
	{
		for (int i=0;i<sizeof(rx_buffer_array);i++)
		{
			if (rx_buffer_array[i] == '\n')
			{
				data_handler(rx_buffer_array);
				reset_buffers();
			}
			else if (rx_buffer_array[i] == 0)
			{
				break;
			}
		}
		

		
		/*if (rx_buffer_array[0] != 0)
		{
			
			reset_buffers();
		}*/
		
		

// 		config.MUX = ADS1115_MUX_AIN0_GND;
// 		ADS1115_set_config(config);
		
		//delay_ms(1000);
		//toggle_all_pins();
		
		/*delay_ms(10);
		config.MUX = ADS1115_MUX_AIN1_GND;
		ADS1115_set_config(config);
		delay_ms(10);
		config.MUX = ADS1115_MUX_AIN2_GND;
		ADS1115_set_config(config);
		
		config.MUX = ADS1115_MUX_AIN3_GND;
		ADS1115_set_config(config);*/
		
		//delay_ms(1);
		/*set_all_pins_to(true);		
		delay_ms(10);
		set_all_pins_to(false);		
		delay_ms(500);*/
		//delay_ms(500);
		//ble_uart_write("bob");
		//Uart_write('h');
		//printf("billybob\n");
		
		//ble_strcmp();
		//ble_uart_read();
		
		
		

	}

	/* Insert application code here, after the board has been initialized. */
}
/*
void get_next_channel(void)
{
	if (clear_to_proceed)
	{
		current_channel++;
		if (current_channel > ADS1115_MUX_AIN3_GND)
		{
			current_channel = ADS1115_MUX_AIN0_GND;
		}
		config.MUX = current_channel;
	}
}*/