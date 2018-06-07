/*
 * ads1115.c
 *
 * Created: 12-12-2017 12:00:21
 *  Author: Andreas
 */ 
#include "mcp23017.h"
#include "i2c.h"

static uint8_t current_channel;


void test_addr(void)
{
	i2c_write(MCP23017_I2C_ADDR_000,0,0);
}

void set_to_output(void)
{
	uint8_t data[2];
	data[0] = MCP23017_IODIRA;
	data[1] = 0x00;
	uint8_t state = i2c_write(MCP23017_I2C_ADDR_000,(uint8_t *)data,2);
	
	data[0] = MCP23017_GPIOA;
	data[1] = 0xFF;
	state = i2c_write(MCP23017_I2C_ADDR_000,(uint8_t *)data,2);
}

uint8_t init_all_ports(void)
{
	uint8_t states = 0;
	uint8_t data[2];
	data[1] = 0x00;
	
	for (int i=0;i<8;i++)
	{
		data[0] = MCP23017_IODIRA;
		uint8_t state = i2c_write(MCP23017_I2C_ADDR_000+i,(uint8_t *)data,2);
		if (state == STATUS_OK)
		{
			data[0] = MCP23017_IODIRB;
			state = i2c_write(MCP23017_I2C_ADDR_000+i,(uint8_t *)data,2);
			if (state == STATUS_OK)
			{
				states |= (1 << i);
			}
		}
	}
	
	data[1] = 0x80;
	data[0] = MCP23017_GPIOA;
	uint8_t state = i2c_write(MCP23017_I2C_ADDR_001,(uint8_t *)data,2);
	data[0] = MCP23017_GPIOB;
	state = i2c_write(MCP23017_I2C_ADDR_001,(uint8_t *)data,2);
	
	return states;
}

static bool port_state = false;
void toggle_all_pins(void)
{
	uint8_t data[2];
	data[0] = MCP23017_GPIOA;
	if (port_state)
	{
		data[1] = 0x00;
		port_state = !port_state;
	}
	else
	{
		data[1] = 0xFF;
		port_state = !port_state;
	}
	uint8_t state = i2c_write(MCP23017_I2C_ADDR_001,(uint8_t *)data,2);	
	data[0] = MCP23017_GPIOB;
	state = i2c_write(MCP23017_I2C_ADDR_001,(uint8_t *)data,2);	
}

void set_all_pins_to(bool val)
{
	uint8_t data[2];
	data[0] = MCP23017_GPIOA;
	if (!val)
	{
		data[1] = 0x00;
	}
	else
	{
		data[1] = 0xFF;
	}
	uint8_t state = i2c_write(MCP23017_I2C_ADDR_000,(uint8_t *)data,2);	
	data[0] = MCP23017_GPIOB;
	state = i2c_write(MCP23017_I2C_ADDR_000,(uint8_t *)data,2);	
}

void mcp23017_set_pins(uint8_t addr, uint8_t porta, uint8_t portb)
{
	uint8_t data[2];
	data[0] = MCP23017_GPIOA;
	data[1] = porta;
	i2c_write(addr,(uint8_t *)data,2);
	data[0] = MCP23017_GPIOB;
	data[1] = portb;
	i2c_write(addr,(uint8_t *)data,2);
}

uint8_t data_being_read[8][2];

void mcp23017_read_all_ports(uint8_t read_data_ptr[2][8])
{
	
	//uint8_t data = 0x00;
	for (uint8_t i=0;i<8;i++)
	{
		//data = 0x00;
		//data_being_read[i][0] = 0;
		//read_data_ptr[i][0] = 0;
		i2c_read(MCP23017_I2C_ADDR_000+i,MCP23017_GPIOA, 1,(uint8_t *)&read_data_ptr[0][i]);
		//read_data[i][0] = data;
		//data_being_read[i][0] = data;
		//read_data_ptr[i][1] = 0;
		i2c_read(MCP23017_I2C_ADDR_000+i,MCP23017_GPIOB, 1,(uint8_t *)&read_data_ptr[1][i]);
		//data_being_read[i][1] = data;
		//read_data[i][1] = data;
	}
	//read_data = data_being_read;
}