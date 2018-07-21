/*
 * cmd.h
 *
 * Created: 10-12-2017 10:01:16
 *  Author: Andreas
 */ 


#ifndef CMD_H_
#define CMD_H_

#include "asf.h"
#include "audia6.h"
#include "mcp23017.h"


uint8_t read_data[2][8];
uint8_t data_LED[2][8];

bool port_update_ongoing;

void data_handler(char buffer[]);
void update_all_ports(void);
void set_blinker(bool state, bool left, bool right);
void party_lights(uint16_t party_vals[]);
void flashy_flash1(void);
void flashy_flash2(void);
void flashy_fades(void);
void reset_all_lights(void);
bool a_okay(void);
void configure_pin(uint8_t port, uint8_t addr, uint8_t pin, bool value);
void mcp23017_reset_error_codes(void);
void party_lights_2(uint16_t party_vals[],uint8_t band);
void flashy_flash3(void);


#define FLASH_ALL_ON "FHA1"
#define FLASH_ALL_OFF "FHA0"

#define BLINK_ALL_ON "BKA 1"
#define BLINK_ALL_OFF "BKA 0"

#define BLINK_LEFT_ON "BKL 1"
#define BLINK_LEFT_OFF "BKL 0"

#define BLINK_RIGHT_ON "BKR 1"
#define BLINK_RIGHT_OFF "BKR 0"

#define HORN_0_ON "HRN1 1"
#define HORN_0_OFF "HRN1 0"
#define HORN_1_ON "HRN2 1"
#define HORN_1_OFF "HRN2 0"
#define HORN_2_ON "HRN3 1"
#define HORN_2_OFF "HRN3 0"
#define HORN_3_ON "HRN4 1"
#define HORN_3_OFF "HRN4 0"

#define SOUND_0_ON "SB00 1"
#define SOUND_0_OFF "SB00 0"
#define SOUND_1_ON "SB01 1"
#define SOUND_1_OFF "SB01 0"
#define SOUND_2_ON "SB02 1"
#define SOUND_2_OFF "SB02 0"
#define SOUND_3_ON "SB03 1"
#define SOUND_3_OFF "SB03 0"
#define SOUND_4_ON "SB04 1"
#define SOUND_4_OFF "SB04 0"
#define SOUND_5_ON "SB05 1"
#define SOUND_5_OFF "SB05 0"
#define SOUND_6_ON "SB06 1"
#define SOUND_6_OFF "SB06 0"
#define SOUND_7_ON "SB07 1"
#define SOUND_7_OFF "SB07 0"
#define SOUND_8_ON "SB08 1"
#define SOUND_8_OFF "SB08 0"
#define SOUND_9_ON "SB09 1"
#define SOUND_9_OFF "SB09 0"
#define SOUND_10_ON "SB10 1"
#define SOUND_10_OFF "SB10 0"
#define SOUND_RESET "SBRST 42"

#define PARTY_ON "PRT 1"
#define PARTY_OFF "PRT 0"
#define WATER_ON "WTR 1"
#define WATER_OFF "WTR 0"
#define START_ON "STA 1"
#define START_OFF "STA 0"

#define LED_BAR_ON "LED 1"
#define LED_BAR_OFF "LED 0"

#define HDL_ON "HDL 1"
#define HDL_OFF "HDL 0"

#define MASTER_RESET "MSTRRST 42"
#define MINOR_RESET "MNRRST 42"

#define MASTER_TEST "MSTRTST 42"

#define BRIAN_ON "BRIAN 1"
#define BRIAN_OFF "BRIAN 0"

#define FLASHY1_ON "FLSH1 1"
#define FLASHY1_OFF "FLSH1 0"

#define FLASHY2_ON "FLSH2 1"
#define FLASHY2_OFF "FLSH2 0"

#define FLASHY3_ON "FLSH3 1"
#define FLASHY3_OFF "FLSH3 0"

#define FLASHYFADE_ON "FLSHFD 1"
#define FLASHYFADE_OFF "FLSHFD 0"

#define PARTY_TRESH_0 "PRTTRSH0"
#define PARTY_TRESH_1 "PRTTRSH1"
#define PARTY_TRESH_2 "PRTTRSH2"
#define PARTY_TRESH_3 "PRTTRSH3"
#define PARTY_TRESH_4 "PRTTRSH4"
#define PARTY_TRESH_5 "PRTTRSH5"
#define PARTY_TRESH_6 "PRTTRSH6"
#define PARTY_TRESH_7 "PRTTRSH7"

#define CUT_OUT_VALVE_ON "COV 1"
#define CUT_OUT_VALVE_OFF "COV 0"

#define PARTY_REV2_ON "PRTRV21"
#define PARTY_REV2_OFF "PRTRV20"

//ADDR 001
#define POSITION_FRONT_LEFT_PIN 0
#define POSITION_FRONT_LEFT_ADR 1
#define POSITION_FRONT_LEFT_PORT 0

#define LOW_BEAM_LEFT_PIN 1
#define LOW_BEAM_LEFT_ADR 1
#define LOW_BEAM_LEFT_PORT 0

#define HIGH_BEAM_LEFT_PIN 2
#define HIGH_BEAM_LEFT_ADR 1
#define HIGH_BEAM_LEFT_PORT 0

#define FOG_FRONT_LEFT_PIN 3
#define FOG_FRONT_LEFT_ADR 1
#define FOG_FRONT_LEFT_PORT 0

#define LEDBAR_PIN 4
#define LEDBAR_ADR 1
#define LEDBAR_PORT 0

/*
#define BLINK_FRONT_LEFT_PIN 2
#define BLINK_FRONT_LEFT_ADR 2
#define BLINK_FRONT_LEFT_PORT 0
*/

//ADDR 010
#define POSITION_FRONT_RIGHT_PIN 0
#define POSITION_FRONT_RIGHT_ADR 2
#define POSITION_FRONT_RIGHT_PORT 0

#define LOW_BEAM_RIGHT_PIN 1
#define LOW_BEAM_RIGHT_ADR 2
#define LOW_BEAM_RIGHT_PORT 0

#define HIGH_BEAM_RIGHT_PIN 2
#define HIGH_BEAM_RIGHT_ADR 2
#define HIGH_BEAM_RIGHT_PORT 0

#define FOG_FRONT_RIGHT_PIN 3
#define FOG_FRONT_RIGHT_ADR 2
#define FOG_FRONT_RIGHT_PORT 0




/*
#define BLINK_FRONT_RIGHT_PIN 2
#define BLINK_FRONT_RIGHT_ADR 1
#define BLINK_FRONT_RIGHT_PORT 0
*/


//ADDR 011
#define POSITION_REAR_LEFT_PIN 0
#define POSITION_REAR_LEFT_ADR 3
#define POSITION_REAR_LEFT_PORT 0

#define REVERSE_LEFT_PIN 1
#define REVERSE_LEFT_ADR 3
#define REVERSE_LEFT_PORT 0

#define BLINK_LEFT_PIN 2
#define BLINK_LEFT_ADR 3
#define BLINK_LEFT_PORT 0

#define SUB_LEFT_PIN 3
#define SUB_LEFT_ADR 3
#define SUB_LEFT_PORT 0

#define SUB_RIGHT_PIN 4
#define SUB_RIGHT_ADR 3
#define SUB_RIGHT_PORT 0

//ADDR 100
#define POSITION_REAR_RIGHT_PIN 0
#define POSITION_REAR_RIGHT_ADR 4
#define POSITION_REAR_RIGHT_PORT 0

#define REVERSE_RIGHT_PIN 1
#define REVERSE_RIGHT_ADR 4
#define REVERSE_RIGHT_PORT 0

#define BLINK_RIGHT_PIN 2
#define BLINK_RIGHT_ADR 4
#define BLINK_RIGHT_PORT 0

//ADDR 101
/*#define LED_BAR_PIN 0
#define LED_BAR_ADR 5
#define LED_BAR_PORT 0	//B*/

#define VALVE_OPEN_PIN 0
#define VALVE_OPEN_ADR 5
#define VALVE_OPEN_PORT 0

#define VALVE_CLOSE_PIN 1
#define VALVE_CLOSE_ADR 5
#define VALVE_CLOSE_PORT 0

#define CABIN_FRONT_PIN 2
#define CABIN_FRONT_ADR 5
#define CABIN_FRONT_PORT 0

#define CABIN_MIDDLE_PIN 3
#define CABIN_MIDDLE_ADR 5
#define CABIN_MIDDLE_PORT 0

#define CABIN_BACK_PIN 4
#define CABIN_BACK_ADR 5
#define CABIN_BACK_PORT 0

#define party_treshold 2500

uint16_t party_thresholds[7];

#endif /* CMD_H_ */