/*
 * main.h
 *
 * Created: 19-12-2017 17:46:26
 *  Author: Andreas
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define SYSTEM_CLK 8000000


// defines for SAMD21
#define PORTGROUP_A		0
#define PORTGROUP_B		1

#define GPIO_SERCOM_ALT_D 3 //peripheral function D - SERCOM-ALT

#define GCM_SERCOM0_CORE          (0x14U)
#define GCM_SERCOM1_CORE          (0x15U)
#define GCM_SERCOM2_CORE          (0x16U)
#define GCM_SERCOM3_CORE          (0x17U)
#define GCM_SERCOM4_CORE          (0x18U)
#define GCM_SERCOM5_CORE          (0x19U)

#define SAMPLE_RATE_x16 0


#define SOFTWARE_VERSION 42


#endif /* MAIN_H_ */