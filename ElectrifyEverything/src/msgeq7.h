/*
 * msgeq7.h
 *
 * Created: 22-04-2018 20:16:42
 *  Author: Andreas
 */ 


#ifndef MSGEQ7_H_
#define MSGEQ7_H_

#include "asf.h"

#define MSGEQ7_PIN_STROBE PIN_PA24
#define MSGEQ7_PIN_RESET PIN_PA25
#define MSGEQ7_PIN_DC_OUT PIN_PB08

//TODO write ADC code
void msgeq7_adc_init(void);
void msgeq7_port_init(void);
void msgeq7_init(void);
uint16_t single_conversion(void);
void msgeq7_all_bands(uint16_t bands[]);

#endif /* MSGEQ7_H_ */