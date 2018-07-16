/*
 * i2c.h
 *
 * Created: 22-12-2017 17:53:01
 *  Author: Andreas
 */ 


#ifndef I2C_H_
#define I2C_H_

#include "asf.h"

#define I2C_TIMEOUT 10

struct i2c_master_module i2c_master_instance;


void configure_i2c_master(void);

uint8_t i2c_write(uint8_t address,uint8_t* data, uint8_t data_size);
int * i2c_addr_scan(void);
uint8_t i2c_read(uint8_t addr,uint8_t reg, uint8_t data_length,uint8_t* data_ptr);

#endif /* I2C_H_ */