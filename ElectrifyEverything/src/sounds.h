/*
 * sounds.h
 *
 * Created: 22-04-2018 20:24:14
 *  Author: Andreas
 */ 


#ifndef SOUNDS_H_
#define SOUNDS_H_
#include "mcp23017.h"

#define SOUNDS_PIN_SS PIN_PA05 //Low is Sample, high is Speak
#define SOUNDS_PIN_SPDT_SEL1 PIN_PA06	//Low is SB_out, high is MTH_out
#define SOUNDS_PIN_SPDT_SEL2 PIN_PA07	//Low is SPDT_out1, high is Speak.

#define SB_PIN_BTN00 PIN_PA11
#define SB_PIN_BTN01 PIN_PA12
#define SB_PIN_BTN02 PIN_PA13
#define SB_PIN_BTN03 PIN_PA14
#define SB_PIN_BTN04 PIN_PA15
#define SB_PIN_BTN05 PIN_PA16
#define SB_PIN_BTN06 PIN_PA17
#define SB_PIN_BTN07 PIN_PA18
#define SB_PIN_BTN08 PIN_PA19
#define SB_PIN_BTN09 PIN_PA20
#define SB_PIN_BTN10 PIN_PA21

#define MTH_ADDR MCP23017_I2C_ADDR_000
#define MTH_BTN1 0
#define MTH_BTN2 1
#define MTH_BTN3 2
#define MTH_BTN4 3
#define MTH_BTN5 4
#define MTH_BTN6 5
#define MTH_BTN7 6
#define MTH_EN 7



void sounds_init_pins(void);

void select_audio_out(void);
void select_sample(void);

void select_mth(void);
void select_soundboard(void);
void select_audio_in(void);

void press_sb_btn(uint8_t btn);
void release_sb_btn(uint8_t btn);

void press_mth_btn(uint8_t btn);
void release_mth_btn(uint8_t btn);






#endif /* SOUNDS_H_ */