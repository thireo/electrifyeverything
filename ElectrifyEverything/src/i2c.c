/*
 * i2c.c
 *
 * Created: 22-12-2017 17:52:49
 *  Author: Andreas
 */ 

#include "i2c.h"

void configure_i2c_master(void)
{
	/* Initialize config structure and software module. */
	struct i2c_master_config config_i2c_master;
	i2c_master_get_config_defaults(&config_i2c_master);
	/* Change buffer timeout to something longer. */
	config_i2c_master.buffer_timeout = 10000;
	config_i2c_master.baud_rate = I2C_MASTER_BAUD_RATE_100KHZ;
	/* Initialize and enable device with config. */
	i2c_master_init(&i2c_master_instance, SERCOM5, &config_i2c_master);
	i2c_master_enable(&i2c_master_instance);
}

uint8_t i2c_write(uint8_t address,uint8_t* data, uint8_t data_size)
{
	struct i2c_master_packet packet = {
		.address     = address,
		.data_length = data_size,
		.data        = data,
		.ten_bit_address = false,
		.high_speed      = false,
		.hs_master_code  = 0x0,
	};
	uint16_t timeout = 0;

	return i2c_master_write_packet_wait(&i2c_master_instance,&packet);

	/*while (i2c_master_write_packet_wait(&i2c_master_instance,&packet) != STATUS_OK)
	{
		if (timeout++ == I2C_TIMEOUT) {
			break;
		}
	}*/
}

int * i2c_addr_scan(void)
{
	uint8_t found_counter = 0;
	for (uint8_t i=0;i<128;i++)
	{
		if (i2c_write(i,0,0) == STATUS_OK)
		{
			found_counter++;
		}
	}
	static uint8_t found_array[255];//[found_counter+1];
	found_array[0] = found_counter;
	found_counter=1;
	for (uint8_t i=0;i<128;i++)
	{
		if (i2c_write(i,0,0) == STATUS_OK)
		{
			found_array[found_counter] = i;
			found_counter++;
		}
	}	
	return found_array;
}

void i2c_read(uint8_t addr,uint8_t reg, uint8_t data_length,uint8_t* data_ptr)
{
	//uint8_t read_datab[data_length];
	uint8_t state = 0;
	//uint8_t address = (addr << 1) + 1;
	
	uint8_t data[2];
	data[0] = reg;
	data[1] = 0xFF;
	
	struct i2c_master_packet packet = {
		.address     = addr | (1 << 8),
		.data_length = data_length,
		.data        = data,
		.ten_bit_address = false,
		.high_speed      = false,
		.hs_master_code  = 0x0,
	};
	uint16_t timeout = 0;

	while (i2c_master_write_packet_wait(&i2c_master_instance,&packet) != STATUS_OK)
	{
		if (timeout++ == I2C_TIMEOUT) {
			return;
			break;
		}
	}
	
	struct i2c_master_packet read_packet = {
		.address     = addr,// | (1 << 8),
		.data_length = data_length,
		.data        = data_ptr,
		.ten_bit_address = false,
		.high_speed      = false,
		.hs_master_code  = 0x0,
	};
	state = i2c_master_read_packet_wait(&i2c_master_instance,&read_packet);
	//return read_data;
}

/* INSERT IN MAIN TO RECEIVE ARRAY OF ATTACHED I2C DEVICES
	uint8_t *array;
	array = i2c_addr_scan();
	uint8_t array_size = *array;
	uint8_t returned_array[array_size];
	for (uint8_t i=1;i<array_size+1;i++)
	{
		returned_array[i-1] =(uint8_t) *(array+i);
	}

*/