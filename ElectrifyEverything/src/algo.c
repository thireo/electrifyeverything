/*
 * algo.c
 *
 * Created: 19-12-2017 18:11:14
 *  Author: Andreas
 */ 
#include "algo.h"

static int16_t adc_channels[8];

void update_adc_val(uint8_t channel, int16_t value)
{
	adc_channels[channel] = (int16_t)(value*0.1875);
}