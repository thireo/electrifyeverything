/*
 * pwm.h
 *
 * Created: 14-01-2018 13:48:41
 *  Author: Andreas Thirsbro
 */ 


#ifndef PWM_H_
#define PWM_H_

#include "asf.h"
#define GCLK_FREQ 8000000
#define PWM_FREQ 100
#define COMPARE_MATCH (GCLK_FREQ/PWM_FREQ) 

int pwm_count;


struct tc_module tc_instance;
void init_TC3();
void TC3_Handler();
void pwm_port();

volatile int pwm_bob;




#endif /* PWM_H_ */