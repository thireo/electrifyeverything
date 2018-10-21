/*
 * obd.c
 *
 * Created: 09-09-2018 20:21:18
 *  Author: Andreas
 */ 
#include "asf.h"
#include "obd.h"
#include "obd_uart.h"
#include "string.h"





uint16_t hex2uint16(const char *p)
{
	char c = *p;
	uint16_t i = 0;
	for (char n = 0; c && n < 4; c = *(++p)) {
		if (c >= 'A' && c <= 'F') {
			c -= 7;
			} else if (c>='a' && c<='f') {
			c -= 39;
			} else if (c == ' ') {
			continue;
			} else if (c < '0' || c > '9') {
			break;
		}
		i = (i << 4) | (c & 0xF);
		n++;
	}
	return i;
}

uint8_t hex2uint8(const char *p)
{
	uint8_t c1 = *p;
	uint8_t c2 = *(p + 1);
	if (c1 >= 'A' && c1 <= 'F')
	c1 -= 7;
	else if (c1 >='a' && c1 <= 'f')
	c1 -= 39;
	else if (c1 < '0' || c1 > '9')
	return 0;

	if (c2 >= 'A' && c2 <= 'F')
	c2 -= 7;
	else if (c2 >= 'a' && c2 <= 'f')
	c2 -= 39;
	else if (c2 < '0' || c2 > '9')
	return 0;

	return c1 << 4 | (c2 & 0xf);
}


void obd_init(void)
{
	
	obd_uart_init();
	//dataMode = 1;

	/*obd_uart_write("ATZ\r");
	delay_ms(10);
	obd_uart_write("ATE0\r");
	delay_ms(10);
	obd_uart_write("ATH0\r");
	//delay_ms(10);
	//sb_uart_write("ATSP%u\r");
	delay_ms(10);
	obd_uart_write("010D\r");
	
	obd_uart_write("ATRV\r");*/


	obd_uart_write(INIT_CMD1);	//RESET
	obd_uart_write(INIT_CMD2);	//ECHO OFF
	obd_uart_write(INIT_CMD3);	//HEADERS OFF
	
	delay_ms(10);
	obd_uart_write("010D\r");
	
	
	//obd_uart_write("ATSP %u\r")
	
	memset(pidmap,0,sizeof(pidmap));
	
	for (uint8_t i = 0;i < 4; i++)
	{
		uint8_t pid = i * 0x20;
		obd_send_query_pid(0x01,pid,4,pidmap[i]);
	}
}

enum status_code obd_send_query_pid(uint8_t service, uint8_t pid, uint8_t data_length, uint8_t *read_read)
{
	enum status_code temp = STATUS_OK;
	char cmd[8];
	sprintf(cmd,"%02X%02X\r",service,pid);
	temp = obd_uart_write(cmd);
	temp = obd_uart_read(read_read,data_length);
	return temp;
}

enum status_code obd_send_query_string(uint8_t *string, uint8_t data_length, uint8_t *read_read)
{
	enum status_code temp = STATUS_OK;
	temp = obd_uart_write(string);
	temp = obd_uart_read(read_read,data_length);
	return temp;
}


//ENGINE LOAD [0 - 100] %
uint8_t get_engine_load(void)
{
	uint8_t A;
	obd_send_query_pid(0x01,PID_ENGINE_LOAD,1,&A);
	return (uint8_t) (100/255)*A;
}

//ENGINE COOLANT TEMPERATURE [-40 - 215] Celsius 
int get_coolant_temp(void)
{
	int A;
	obd_send_query_pid(0x01,PID_COOLANT_TEMP,1,&A);
	return (int) A-40;
}

//INTAKE MANIFOLD ABS PRESSURE [0 255] kPa
uint8_t get_intake_manifold_pressure(void)
{
	uint8_t A;
	obd_send_query_pid(0x01,PID_INTAKE_MAP,1,&A);
	return (uint8_t) A;
}

//INTAKE AIR TEMPERATURE [-40 215] Celsius
int get_intake_air_temp(void)
{
	uint8_t A;
	obd_send_query_pid(0x01,PID_INTAKE_MAP,1,&A);
	return (int) A-40;
}

//ENGINE RPM [0 16,383.75] rpm
uint16_t get_engine_rpm(void)
{
	uint8_t data[2];
	obd_send_query_pid(0x01,PID_RPM,2,data);
	return (uint16_t) (256*data[0]+data[1])/4;
}

//VEHICLE SPEED [0 255] km/h
uint8_t get_vehicle_speed(void)
{
	uint8_t A;
	obd_send_query_pid(0x01,PID_SPEED,1,&A);
	return A;
}

//Returns number of DTCs
uint8_t get_monitor_status(void)
{
	uint8_t data[4];
	obd_send_query_pid(0x01,PID_MONITOR_STATUS,4,data);
	return (uint8_t) (data[0] & 0x7F);
}

float get_battery_voltage(void)
{
	uint8_t data[6];
	obd_send_query_string("ATRV",6,data);
	float f = 0.0;
	sscanf(data,"%f",&f);
	return f;
}