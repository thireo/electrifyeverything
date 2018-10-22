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
#include "uart.h"
#include "ble_uart.h"
//#include "ads1115.h"
#include "mcp23017.h"
#include "i2c.h"
#include "cmd.h"
#include "pwm.h"
#include "sounds.h"
#include "msgeq7.h"
#include "uart.h"
#include "string.h"
#include "obd.h"


//#include "ds18b20.h"

//extern uint8_t rx_buffer[MAX_RX_BUFFER_LENGTH];



char buffer[32];



int main (void)
{
	
	system_init();
	delay_init();
	ble_uart_init();
	//uart_init();
	//sb_reset_buffers();
	
	
	
	//sounds_init_pins();
	//sb_uart_init();
	delay_ms(1500);
	//sounds_reset();

	obd_init();
	
	init_TC3();
	
	//sb_play_track_by_number(0);
	
	
	//sprintf(buffer,"#02\n");
	//uart_write(buffer);
	
	/*
	sprintf(buffer,"\n<-------------------->\n");
	ble_uart_write(buffer);
	uart_write(buffer);
	delay_ms(2000);
	sprintf(buffer,"Master Board Started\n");
	ble_uart_write(buffer);
	uart_write(buffer);
	sprintf(buffer,"SOFTWARE_VERSION: %d\r\n", SOFTWARE_VERSION);
	ble_uart_write(buffer);
	uart_write(buffer);
	sprintf(buffer,"<-------------------->\n\n");
	ble_uart_write(buffer);
	uart_write(buffer);
	mcp23017_pin_init();
	
	configure_i2c_master();
	
	uint8_t states = init_all_ports();
	//sprintf(buffer,"I2C: %d%d%d%d%d%d%d%d",(states >> 7)&0x01,(states >> 6)&0x01,(states >> 5)&0x01,(states >> 4)&0x01,(states >> 3)&0x01,(states >> 2)&0x01,(states >> 1)&0x01,(states >> 0)&0x01);
	
	//ble_uart_write(buffer);
	

	
	sounds_init_pins();
	
	//sounds_reset();
	
	pwm_port();
	init_TC3();
	
	msgeq7_init();
	//select_sample();
	
	//party = true;
	
	party_thresholds[0] = 1500;//1375;
	party_thresholds[1] = 1550;
	party_thresholds[2] = 1400;
	party_thresholds[3] = 2500;
	party_thresholds[4] = 3000;
	party_thresholds[5] = 2000;
	party_thresholds[6] = 2375;
	 
	*/
	
	//int sound_no = 0;
	
	while (1)
	{
		
		if (obd_should_update)
		{
			char buffer[32];
			sprintf(buffer,"Battery: %dV\r\n",(int)get_battery_voltage());
			ble_uart_write(buffer);
			sprintf(buffer,"RPM: %d\r\n",get_engine_rpm());
			ble_uart_write(buffer);
			obd_should_update = false;
		}
		
		if (is_started())
		{
			/*sb_play_track_by_number(3);
			delay_ms(1000);
			sb_play_track_by_number(4);*/
		}
		
		
		for (uint32_t i=0;i<sizeof(rx_buffer_array)-1;i++)
		{
			if (rx_buffer_array[i] == '\n' & rx_buffer_array[i+1] == 0)//'\n')
			{
				data_handler(rx_buffer_array);
				reset_buffers();
			}
			else if (rx_buffer_array[i] == 0)
			{
				break;
			}
		}
		
		sb_event_handler(sb_rx_buffer_array);
		/*if (strstr(sb_rx_buffer_array,"done") != NULL)
		//if (strncmp(sb_rx_buffer_array,"\r\n\rAdafruit",7) == 0)
		{
			if (sound_no > 10)
			{
				sound_no = 0;
			}
			sb_reset_buffers();
			sb_play_track_by_number(sound_no++);
			if (sound_no == 3)
			{
				delay_ms(250);
				sb_play_track_by_number(2);
			}
			//sb_uart_write(buffer);
		}*/
		if (should_update)
		{
			should_update = false;
			things_to_do();
			update_all_ports();
		}
		if (execute_order_66)
		{
			system_interrupt_disable_global();
			ble_uart_write("EXEC ORDER 66\n");
			execute_order_66 = false;
			//init_all_ports();
			mcp23017_reset();
			a_okay();
			system_interrupt_enable_global();
		}
		
		if (valve_open)
		{
			system_interrupt_disable_global();
			valve_open = false;
			configure_pin(VALVE_OPEN_PORT,VALVE_OPEN_ADR,VALVE_OPEN_PIN,true);
			configure_pin(VALVE_CLOSE_PORT,VALVE_CLOSE_ADR,VALVE_CLOSE_PIN,false);
			update_all_ports();
			delay_ms(300);
			configure_pin(VALVE_OPEN_PORT,VALVE_OPEN_ADR,VALVE_OPEN_PIN,false);
			update_all_ports();
			delay_ms(4000);
			configure_pin(VALVE_OPEN_PORT,VALVE_OPEN_ADR,VALVE_OPEN_PIN,true);
			update_all_ports();
			delay_ms(300);
			configure_pin(VALVE_OPEN_PORT,VALVE_OPEN_ADR,VALVE_OPEN_PIN,false);
			update_all_ports();
			system_interrupt_enable_global();
		}
		if (valve_close)
		{
			system_interrupt_disable_global();
			valve_close = false;
			configure_pin(VALVE_OPEN_PORT,VALVE_OPEN_ADR,VALVE_OPEN_PIN,false);
			configure_pin(VALVE_CLOSE_PORT,VALVE_CLOSE_ADR,VALVE_CLOSE_PIN,true);
			update_all_ports();
			delay_ms(300);
			configure_pin(VALVE_CLOSE_PORT,VALVE_CLOSE_ADR,VALVE_CLOSE_PIN,false);
			update_all_ports();
			delay_ms(4000);
			configure_pin(VALVE_CLOSE_PORT,VALVE_CLOSE_ADR,VALVE_CLOSE_PIN,true);
			update_all_ports();
			delay_ms(300);
			configure_pin(VALVE_CLOSE_PORT,VALVE_CLOSE_ADR,VALVE_CLOSE_PIN,false);
			update_all_ports();
			system_interrupt_enable_global();
		}
		
		if (should_check)
		{
			should_check = false;
			mcp23017_check_all();
		}
	}
}
