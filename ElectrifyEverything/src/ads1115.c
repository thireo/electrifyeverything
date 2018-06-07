/*
 * ads1115.c
 *
 * Created: 12-12-2017 12:00:21
 *  Author: Andreas
 */ 
#include "ads1115.h"

static uint8_t current_channel;
/*
void configure_i2c_master(void)
{
	struct i2c_master_config config_i2c_master;
	i2c_master_get_config_defaults(&config_i2c_master);
	config_i2c_master.buffer_timeout = 10000;
	config_i2c_master.baud_rate = I2C_MASTER_BAUD_RATE_100KHZ;
	i2c_master_init(&i2c_master_instance, SERCOM5, &config_i2c_master);
	i2c_master_enable(&i2c_master_instance);
}*/
/*
void ADS1115_set_config(config_data_bytes config)
{
	current_channel = config.MUX;
	
	uint8_t write_buffer[3];
	write_buffer[0] = ADS1115_APR_CONF;
	write_buffer[1] = config.bytes[0];
	write_buffer[2] = config.bytes[1];
		
	struct i2c_master_packet packet = {
		.address     = ADS1115_CHOSEN_ADDR,
		.data_length = 3,
		.data        = &write_buffer,
		.ten_bit_address = false,
		.high_speed      = false,
		.hs_master_code  = 0x0,
	};
	uint16_t timeout = 0;

	i2c_master_write_packet_wait(&i2c_master_instance,&packet);

	while (i2c_master_write_packet_wait(&i2c_master_instance,&packet) != STATUS_OK)
	{
		if (timeout++ == TIMEOUT) {
			break;
		}
	}
}



int16_t ADS1115_get_conv_result(void)
{
	uint8_t buf = ADS1115_APR_CONV;
	struct i2c_master_packet write_packet = {
		.address     = ADS1115_CHOSEN_ADDR,
		.data_length = 1,
		.data        = &buf,
		.ten_bit_address = false,
		.high_speed      = false,
		.hs_master_code  = 0x0,
	};
	
	uint16_t timeout = 0;
	while (i2c_master_write_packet_wait(&i2c_master_instance,&write_packet) != STATUS_OK)
	{
		if (timeout++ == TIMEOUT) {
			break;
		}
	}
	
	//delay_ms(10);
	
	timeout = 0;
	uint8_t read_buffer[2];
	read_buffer[0] = 0;
	read_buffer[1] = 0;
	
	struct i2c_master_packet read_packet = {
		.address     = ADS1115_CHOSEN_ADDR,
		.data_length = 2,
		.data        = read_buffer,
		.ten_bit_address = false,
		.high_speed      = false,
		.hs_master_code  = 0x0,
	};
	
	while (i2c_master_read_packet_wait(&i2c_master_instance,&read_packet) != STATUS_OK)
	{
		if (timeout++ == TIMEOUT) {
			break;
		}
	}
	//i2c_master_write_byte(&i2c_master_instance,reg);
	//i2c_master_read_byte(&i2c_master_instance,&return_byte);
	//return_byte = packet.data;
	
	int16_t temp = 0;
	temp = read_buffer[0] | read_buffer[1]<<8;
	return temp;
}

void ADS1115_enable_ready_pin(void)
{
	uint8_t write_buffer[3];
	write_buffer[0] = ADS1115_APR_HI_TH;
	write_buffer[1] = 0x80;
	write_buffer[2] = 0x00;
	
	
	struct i2c_master_packet packet = {
		.address     = ADS1115_CHOSEN_ADDR,
		.data_length = 3,
		.data        = write_buffer,
		.ten_bit_address = false,
		.high_speed      = false,
		.hs_master_code  = 0x0,
	};
	uint16_t timeout = 0;

	while (i2c_master_write_packet_wait(&i2c_master_instance,&packet) != STATUS_OK)
	{
		if (timeout++ == TIMEOUT) {
			break;
		}
	}
	
	
	write_buffer[0] = ADS1115_APR_LO_TH;
	write_buffer[1] = 0x00;
	write_buffer[2] = 0x00;
	
	struct i2c_master_packet packet1 = {
		.address     = ADS1115_CHOSEN_ADDR,
		.data_length = 3,
		.data        = write_buffer,
		.ten_bit_address = false,
		.high_speed      = false,
		.hs_master_code  = 0x0,
	};
	
	timeout = 0;

	while (i2c_master_write_packet_wait(&i2c_master_instance,&packet1) != STATUS_OK)
	{
		if (timeout++ == TIMEOUT) {
			break;
		}
	}
	timeout = 0;
}


void ADS1115_configure_extint_channel(void)
{
	struct extint_chan_conf config_extint_chan;
	extint_chan_get_config_defaults(&config_extint_chan);
	config_extint_chan.gpio_pin           = READY_PIN;
	config_extint_chan.gpio_pin_mux       = READY_PINMUX;
	config_extint_chan.gpio_pin_pull      = EXTINT_PULL_UP;
	config_extint_chan.detection_criteria = EXTINT_DETECT_FALLING;
	extint_chan_set_config(READY_EXTINT_LINE, &config_extint_chan);
}

void ADS1115_configure_extint_callbacks(void)
{
	extint_register_callback(ADS1115_ready_callback,READY_EXTINT_LINE,EXTINT_CALLBACK_TYPE_DETECT);
	extint_chan_enable_callback(READY_EXTINT_LINE,EXTINT_CALLBACK_TYPE_DETECT);
}

volatile static bool clear_to_proceed = false;

void ADS1115_ready_callback(void)
{
	uint16_t result = ADS1115_get_conv_result();
	adc_channels[current_channel] = (int16_t)(result*0.1875);
	clear_to_proceed = true;
	//update_adc_val(current_channel,result);
}



int16_t ADS1115_get_high_threshold(void)
{
	struct i2c_master_packet write_packet = {
		.address     = ADS1115_CHOSEN_ADDR+ADS1115_WRITE_BiT,
		.data_length = 1,
		.data        = ADS1115_APR_HI_TH,
		.ten_bit_address = false,
		.high_speed      = false,
		.hs_master_code  = 0x0,
	};
	
	uint16_t timeout = 0;
	while (i2c_master_write_packet_wait(&i2c_master_instance,&write_packet) != STATUS_OK)
	{
		if (timeout++ == TIMEOUT) {
			break;
		}
	}
	
	timeout = 0;
	uint8_t read_buffer[2];
	
	struct i2c_master_packet read_packet = {
		.address     = ADS1115_CHOSEN_ADDR+ADS1115_READ_BiT,
		.data_length = 2,
		.data        = read_buffer,
		.ten_bit_address = false,
		.high_speed      = false,
		.hs_master_code  = 0x0,
	};
	
	while (i2c_master_read_packet_wait(&i2c_master_instance,&read_packet) != STATUS_OK)
	{
		if (timeout++ == TIMEOUT) {
			break;
		}
	}
	//i2c_master_write_byte(&i2c_master_instance,reg);
	//i2c_master_read_byte(&i2c_master_instance,&return_byte);
	//return_byte = packet.data;
	
	int16_t temp = 0;
	temp = read_buffer[0]<<8 || read_buffer[1];
	
	return temp;
}

int16_t ADS1115_get_config(void)
{
	static uint8_t write_buffer = ADS1115_APR_CONF;
	struct i2c_master_packet write_packet = {
		.address     = ADS1115_CHOSEN_ADDR,
		.data_length = 1,
		.data        = &write_buffer,
		.ten_bit_address = false,
		.high_speed      = false,
		.hs_master_code  = 0x0,
	};
	
	
	
	uint16_t timeout = 0;
	while (i2c_master_write_packet_wait(&i2c_master_instance,&write_packet) != STATUS_OK)
	{
		if (timeout++ == TIMEOUT) {
			break;
		}
	}
	
	timeout = 0;
	static uint8_t read_buffer[2];
	
	struct i2c_master_packet read_packet = {
		.address     = ADS1115_CHOSEN_ADDR,
		.data_length = 2,
		.data        = read_buffer,
		.ten_bit_address = false,
		.high_speed      = false,
		.hs_master_code  = 0x0,
	};
	
	while (i2c_master_read_packet_wait(&i2c_master_instance,&read_packet) != STATUS_OK)
	{
		if (timeout++ == TIMEOUT) {
			break;
		}
	}
	//i2c_master_write_byte(&i2c_master_instance,reg);
	//i2c_master_read_byte(&i2c_master_instance,&return_byte);
	//return_byte = packet.data;
	
	int16_t temp = 0;
	temp = read_buffer[0]<<8 || read_buffer[1];
	
	return temp;
}
*/