/*
 * obd.c
 *
 * Created: 09-09-2018 20:21:18
 *  Author: Andreas
 */ 
#include "asf.h"
#include "obd.h"
#include "uart.h"
#include "string.h"


void obd_uart_write(char buffer[])
{
	sb_uart_write(buffer);
}


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
	dataMode = 1;

	sb_uart_write("ATZ\r");
	delay_ms(10);
	sb_uart_write("ATE0\r");
	delay_ms(10);
	sb_uart_write("ATH0\r");
	//delay_ms(10);
	//sb_uart_write("ATSP%u\r");
	delay_ms(10);
	sb_uart_write("010D\r");
	
	sb_uart_write("ATRV\r");


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
		obd_send_query(pid);
	}
}

void obd_send_query(uint8_t pid)
{
	char cmd[8];
	sprintf(cmd,"%02X%02X\r",dataMode,pid);
	obd_uart_write(cmd);
}

bool obd_send_c