/*
* mcp23017.h
*
* Created: 21-12-2017 18:22:05
*  Author: Andreas
*/


#ifndef ADS1115_H_
#define ADS1115_H_

#include "asf.h"


#define MCP23017_I2C_ADDR_000 0x20//0b0010000
#define MCP23017_I2C_ADDR_001 0x21//0b0010001
#define MCP23017_I2C_ADDR_010 0x22//0b0010010
#define MCP23017_I2C_ADDR_011 0x23//0b0010011
#define MCP23017_I2C_ADDR_100 0x24//0b0010100
#define MCP23017_I2C_ADDR_101 0x25//0b0010101
#define MCP23017_I2C_ADDR_110 0x26//0b0010110
#define MCP23017_I2C_ADDR_111 0x27//0b0010111




//Registers
#define MCP23017_IODIRA 0x00
#define MCP23017_IPOLA 0x02
#define MCP23017_GPINTENA 0x04
#define MCP23017_DEFVALA 0x06
#define MCP23017_INTCONA 0x08
#define MCP23017_IOCONA 0x0A
#define MCP23017_GPPUA 0x0C
#define MCP23017_INTFA 0x0E
#define MCP23017_INTCAPA 0x10
#define MCP23017_GPIOA 0x12
#define MCP23017_OLATA 0x14


#define MCP23017_IODIRB 0x01
#define MCP23017_IPOLB 0x03
#define MCP23017_GPINTENB 0x05
#define MCP23017_DEFVALB 0x07
#define MCP23017_INTCONB 0x09
#define MCP23017_IOCONB 0x0B
#define MCP23017_GPPUB 0x0D
#define MCP23017_INTFB 0x0F
#define MCP23017_INTCAPB 0x11
#define MCP23017_GPIOB 0x13
#define MCP23017_OLATB 0x15

#define MCP23017_INT_ERR 255

#define MCP23017_PWR_PIN PIN_PA07

void test_addr(void);
void set_to_output(void);
uint8_t init_all_ports(void);
void toggle_all_pins(void);
void set_all_pins_to(bool val);

uint8_t mcp23017_set_pins(uint8_t addr, uint8_t porta, uint8_t portb);
void mcp23017_read_all_ports(uint8_t read_data_ptr[2][8], uint8_t states[8]);
void mcp23017_reset(void);

void mcp23017_pin_init(void);

void mcp23017_bus_reset();

#endif /* MCP23017_H_ */