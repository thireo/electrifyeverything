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
#define PWM_FREQ 250
#define COMPARE_MATCH (GCLK_FREQ/PWM_FREQ) 

#if ((COMPARE_MATCH > 65535))
#error "TOO LARGE COMPARE_MATCH VALUE. TRY INCREASING PWM_FREQ"
#endif

int pwm_count;
int seconds;
bool should_update;
bool execute_order_66;
bool should_check;
bool obd_should_update;
int should_updates;

struct tc_module tc_instance;
void init_TC3(void);
void TC3_Handler(void);
void pwm_port(void);
void things_to_do(void);

volatile int pwm_bob;




#endif /* PWM_H_ */