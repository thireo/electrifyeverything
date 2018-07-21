/*
 * cmd.c
 *
 * Created: 10-12-2017 10:01:08
 *  Author: Andreas
 */ 
#include "cmd.h"
#include "string.h"
#include "ble_uart.h"
#include "pwm.h"
#include "audia6.h"
#include "mcp23017.h"
char test_bob[] = "PWM";
#include "sounds.h"
#include "uart.h"

bool bool_map_1[26][8] = {
	{false,false,false,false,false,false,false,false},
	{false,true,false,false,false,false,false,false},
	{false,false,true,false,false,false,false,false},
	{false,false,false,true,false,false,false,false},
	{false,false,false,false,true,false,false,false},
	{false,false,false,false,false,true,false,false},
	{false,false,false,false,false,false,true,false},
	{false,false,false,false,false,false,false,true},
	{false,false,false,false,false,false,true,false},
	{false,false,false,false,false,true,false,false},
	{false,false,false,false,true,false,false,false},
	{false,false,false,true,false,false,false,false},
	{false,false,true,false,false,false,false,false},
	{false,true,false,false,false,false,false,false},
	{true,false,false,false,false,false,false,false},
	{false,false,false,true,true,false,false,false},
	{false,false,true,false,false,true,false,false},
	{false,true,false,false,false,false,true,false},
	{true,false,false,false,false,false,false,true},
	{false,true,false,false,false,false,true,false},
	{false,false,true,false,false,true,false,false},
	{false,false,false,true,true,false,false,false},
	{false,false,false,false,false,false,false,false},
	{false,false,false,true,true,false,false,false},
	{false,false,false,false,false,false,false,false},
	{true,true,true,true,true,true,true,true}
};


typedef union
{
	struct{
		unsigned int pa0	:	1;
		unsigned int pa1	:	1;
		unsigned int pa2	:	1;
		unsigned int pa3	:	1;
		unsigned int pa4	:	1;
		unsigned int pa5	:	1;
		unsigned int pa6	:	1;
		unsigned int pa7	:	1;
		unsigned int pb0	:	1;
		unsigned int pb1	:	1;
		unsigned int pb2	:	1;
		unsigned int pb3	:	1;
		unsigned int pb4	:	1;
		unsigned int pb5	:	1;
		unsigned int pb6	:	1;
		unsigned int pb7	:	1;
	};
	uint8_t ports[2];
}mcp23017_ports_object;


struct mcp23017_devices
{
	bool should_be_enabled;
	bool is_enabled;
	bool error_detected;
	enum status_code status;
	uint8_t i2c_addr;
	mcp23017_ports_object outputs;
	mcp23017_ports_object output_errors;
};

struct mcp23017_object
{
	struct mcp23017_devices devices[8];
};

struct mcp23017_object mcp23017_data={				\
	.devices[0].should_be_enabled = false,			\
	.devices[0].is_enabled = false,					\
	.devices[0].error_detected = false,				\
	.devices[0].i2c_addr = MCP23017_I2C_ADDR_000,	\
	.devices[0].outputs.ports[0] = 0x00,			\
	.devices[0].outputs.ports[1] = 0x00,			\
	.devices[0].output_errors.ports[0] = 0x00,		\
	.devices[0].output_errors.ports[1] = 0x00,		\
	.devices[0].status = STATUS_OK,					\
	.devices[1].should_be_enabled = true,			\
	.devices[1].is_enabled = false,					\
	.devices[1].error_detected = false,				\
	.devices[1].i2c_addr = MCP23017_I2C_ADDR_001,	\
	.devices[1].outputs.ports[0] = 0x00,			\
	.devices[1].outputs.ports[1] = 0x00,			\
	.devices[1].output_errors.ports[0] = 0x00,		\
	.devices[1].output_errors.ports[1] = 0x00,		\
	.devices[1].status = STATUS_OK,					\
	.devices[2].should_be_enabled = true,			\
	.devices[2].is_enabled = false,					\
	.devices[2].error_detected = false,				\
	.devices[2].i2c_addr = MCP23017_I2C_ADDR_010,	\
	.devices[2].outputs.ports[0] = 0x00,			\
	.devices[2].outputs.ports[1] = 0x00,			\
	.devices[2].output_errors.ports[0] = 0x00,		\
	.devices[2].output_errors.ports[1] = 0x00,		\
	.devices[2].status = STATUS_OK,					\
	.devices[3].should_be_enabled = true,			\
	.devices[3].is_enabled = false,					\
	.devices[3].error_detected = false,				\
	.devices[3].i2c_addr = MCP23017_I2C_ADDR_011,	\
	.devices[3].outputs.ports[0] = 0x00,			\
	.devices[3].outputs.ports[1] = 0x00,			\
	.devices[3].output_errors.ports[0] = 0x00,		\
	.devices[3].output_errors.ports[1] = 0x00,		\
	.devices[3].status = STATUS_OK,					\
	.devices[4].should_be_enabled = true,			\
	.devices[4].is_enabled = false,					\
	.devices[4].error_detected = false,				\
	.devices[4].i2c_addr = MCP23017_I2C_ADDR_100,	\
	.devices[4].outputs.ports[0] = 0x00,			\
	.devices[4].outputs.ports[1] = 0x00,			\
	.devices[4].output_errors.ports[0] = 0x00,		\
	.devices[4].output_errors.ports[1] = 0x00,		\
	.devices[4].status = STATUS_OK,					\
	.devices[5].should_be_enabled = true,			\
	.devices[5].is_enabled = false,					\
	.devices[5].error_detected = false,				\
	.devices[5].i2c_addr = MCP23017_I2C_ADDR_101,	\
	.devices[5].outputs.ports[0] = 0x00,			\
	.devices[5].outputs.ports[1] = 0x00,			\
	.devices[5].output_errors.ports[0] = 0x00,		\
	.devices[5].output_errors.ports[1] = 0x00,		\
	.devices[5].status = STATUS_OK,					\
	.devices[6].should_be_enabled = false,			\
	.devices[6].is_enabled = false,					\
	.devices[6].error_detected = false,				\
	.devices[6].i2c_addr = MCP23017_I2C_ADDR_110,	\
	.devices[6].outputs.ports[0] = 0x00,			\
	.devices[6].outputs.ports[1] = 0x00,			\
	.devices[6].output_errors.ports[0] = 0x00,		\
	.devices[6].output_errors.ports[1] = 0x00,		\
	.devices[6].status = STATUS_OK,					\
	.devices[7].should_be_enabled = false,			\
	.devices[7].is_enabled = false,					\
	.devices[7].error_detected = false,				\
	.devices[7].i2c_addr = MCP23017_I2C_ADDR_111,	\
	.devices[7].outputs.ports[0] = 0x00,			\
	.devices[7].outputs.ports[1] = 0x00,			\
	.devices[7].output_errors.ports[0] = 0x00,		\
	.devices[7].output_errors.ports[1] = 0x00,		\
	.devices[7].status = STATUS_OK};





void data_handler(char buffer[])
{
	int buf_s = strlen(buffer);
	if (strncmp(buffer,test_bob,3) == 0)
	{
		ble_uart_write("bob was found");
		
		if (strlen(buffer) > strlen(test_bob))
		{
			int arg1;
			sscanf(buffer,"PWM %d",&arg1);
			//arg1 = buffer[4]-'0';
			if (arg1 < 1)
			{
				arg1 = 1;
			}
			pwm_bob = arg1;
			char string_buffer[32];
			sprintf(string_buffer,": %d",arg1);
			ble_uart_write(string_buffer);
		}
	}


	if(strncmp(buffer,FLASH_ALL_ON,4) == 0)
	{
		configure_pin(POSITION_FRONT_LEFT_PORT,POSITION_FRONT_LEFT_ADR, POSITION_FRONT_LEFT_PIN,true);
		configure_pin(POSITION_FRONT_RIGHT_PORT,POSITION_FRONT_RIGHT_ADR, POSITION_FRONT_RIGHT_PIN,true);
		configure_pin(POSITION_REAR_LEFT_PORT,POSITION_REAR_LEFT_ADR, POSITION_REAR_LEFT_PIN,true);
		configure_pin(POSITION_REAR_RIGHT_PORT,POSITION_REAR_RIGHT_ADR, POSITION_REAR_RIGHT_PIN,true);
		
		configure_pin(LOW_BEAM_RIGHT_PORT,LOW_BEAM_RIGHT_ADR, LOW_BEAM_RIGHT_PIN,true);
		configure_pin(LOW_BEAM_LEFT_PORT,LOW_BEAM_LEFT_ADR, LOW_BEAM_LEFT_PIN,true);
		
		configure_pin(HIGH_BEAM_RIGHT_PORT,HIGH_BEAM_RIGHT_ADR, HIGH_BEAM_RIGHT_PIN,true);
		configure_pin(HIGH_BEAM_LEFT_PORT,HIGH_BEAM_LEFT_ADR, HIGH_BEAM_LEFT_PIN,true);
		
		configure_pin(BLINK_RIGHT_PORT,BLINK_RIGHT_ADR, BLINK_RIGHT_PIN,true);
		configure_pin(BLINK_LEFT_PORT,BLINK_LEFT_ADR, BLINK_LEFT_PIN,true);
		
		configure_pin(REVERSE_LEFT_PORT,REVERSE_LEFT_ADR, REVERSE_LEFT_PIN,true);
		configure_pin(REVERSE_RIGHT_PORT,REVERSE_RIGHT_ADR, REVERSE_RIGHT_PIN,true);
		
		configure_pin(FOG_FRONT_RIGHT_PORT,FOG_FRONT_RIGHT_ADR, FOG_FRONT_RIGHT_PIN,true);
		configure_pin(FOG_FRONT_LEFT_PORT,FOG_FRONT_LEFT_ADR, FOG_FRONT_LEFT_PIN,true);
		
		configure_pin(SUB_LEFT_PORT,SUB_LEFT_ADR, SUB_LEFT_PIN,true);
		configure_pin(SUB_RIGHT_PORT,SUB_RIGHT_ADR, SUB_RIGHT_PIN,true);
		
		configure_pin(LEDBAR_PORT,LEDBAR_ADR, LEDBAR_PIN,true);
		
		configure_pin(CABIN_MIDDLE_PORT,CABIN_MIDDLE_ADR,CABIN_MIDDLE_PIN,true);
		configure_pin(CABIN_FRONT_PORT,CABIN_FRONT_ADR,CABIN_FRONT_PIN,true);
		configure_pin(CABIN_BACK_PORT,CABIN_BACK_ADR,CABIN_BACK_PIN,true);
		
		flash_all = true;
	}
	else if(strncmp(buffer,FLASH_ALL_OFF,4) == 0)
	{
		configure_pin(POSITION_FRONT_LEFT_PORT,POSITION_FRONT_LEFT_ADR,POSITION_FRONT_LEFT_PIN,false);
		configure_pin(POSITION_FRONT_RIGHT_PORT,POSITION_FRONT_RIGHT_ADR,POSITION_FRONT_RIGHT_PIN,false);
		configure_pin(POSITION_REAR_LEFT_PORT,POSITION_REAR_LEFT_ADR,POSITION_REAR_LEFT_PIN,false);
		configure_pin(POSITION_REAR_RIGHT_PORT,POSITION_REAR_RIGHT_ADR,POSITION_REAR_RIGHT_PIN,false);
		
		configure_pin(LOW_BEAM_RIGHT_PORT,LOW_BEAM_RIGHT_ADR,LOW_BEAM_RIGHT_PIN,false);
		configure_pin(LOW_BEAM_LEFT_PORT,LOW_BEAM_LEFT_ADR,LOW_BEAM_LEFT_PIN,false);
		
		configure_pin(HIGH_BEAM_RIGHT_PORT,HIGH_BEAM_RIGHT_ADR,HIGH_BEAM_RIGHT_PIN,false);
		configure_pin(HIGH_BEAM_LEFT_PORT,HIGH_BEAM_LEFT_ADR,HIGH_BEAM_LEFT_PIN,false);
		
		configure_pin(BLINK_RIGHT_PORT,BLINK_RIGHT_ADR,BLINK_RIGHT_PIN,false);
		configure_pin(BLINK_LEFT_PORT,BLINK_LEFT_ADR,BLINK_LEFT_PIN,false);
		
		configure_pin(REVERSE_LEFT_PORT,REVERSE_LEFT_ADR,REVERSE_LEFT_PIN,false);
		configure_pin(REVERSE_RIGHT_PORT,REVERSE_RIGHT_ADR,REVERSE_RIGHT_PIN,false);
		
		configure_pin(FOG_FRONT_RIGHT_PORT,FOG_FRONT_RIGHT_ADR,FOG_FRONT_RIGHT_PIN,false);
		configure_pin(FOG_FRONT_LEFT_PORT,FOG_FRONT_LEFT_ADR,FOG_FRONT_LEFT_PIN,false);
		
		configure_pin(SUB_LEFT_PORT,SUB_LEFT_ADR,SUB_LEFT_PIN,false);
		configure_pin(SUB_RIGHT_PORT,SUB_RIGHT_ADR,SUB_RIGHT_PIN,false);
		
		configure_pin(LEDBAR_PORT,LEDBAR_ADR,LEDBAR_PIN,false);
		
		configure_pin(CABIN_MIDDLE_PORT,CABIN_MIDDLE_ADR,CABIN_MIDDLE_PIN,false);
		configure_pin(CABIN_FRONT_PORT,CABIN_FRONT_ADR,CABIN_FRONT_PIN,false);
		configure_pin(CABIN_BACK_PORT,CABIN_BACK_ADR,CABIN_BACK_PIN,false);
		
		flash_all = false;
	}
	else if(strncmp(buffer,BLINK_ALL_ON,5) == 0)
	{
		blink_left = true;
		blink_right = true;
		blink_all = true;
	}
	else if(strncmp(buffer,BLINK_ALL_OFF,5) == 0)
	{
		blink_left = false;
		blink_right = false;
		blink_all = false;
	}
	else if(strncmp(buffer,BLINK_LEFT_ON,5) == 0)
	{
		blink_left = true;
	}
	else if(strncmp(buffer,BLINK_LEFT_OFF,5) == 0)
	{
		blink_left = false;
	}
	else if(strncmp(buffer,BLINK_RIGHT_ON,5) == 0)
	{
		blink_right = true;
	}
	else if(strncmp(buffer,BLINK_RIGHT_OFF,5) == 0)
	{
		blink_right = false;
	}
	else if(strncmp(buffer,HORN_0_ON,6) == 0)
	{
		horn0 = true;
	}
	else if(strncmp(buffer,HORN_0_OFF,6) == 0)
	{
		horn0 = false;
	}
	else if(strncmp(buffer,HORN_1_ON,6) == 0)
	{
		horn1 = true;
	}
	else if(strncmp(buffer,HORN_1_OFF,6) == 0)
	{
		horn1 = false;
	}
	else if(strncmp(buffer,HORN_2_ON,6) == 0)
	{
		horn2 = true;
	}
	else if(strncmp(buffer,HORN_2_OFF,6) == 0)
	{
		horn2 = false;
	}
	else if(strncmp(buffer,HORN_3_ON,6) == 0)
	{
		horn3 = true;
	}
	else if(strncmp(buffer,HORN_3_OFF,6) == 0)
	{
		horn3 = false;
	}
	else if(strncmp(buffer,SOUND_0_ON,6) == 0)
	{
		press_sb_btn_once(SB_PIN_BTN00);
	}
	else if(strncmp(buffer,SOUND_0_OFF,6) == 0)
	{
		release_sb_btn(SB_PIN_BTN00);
	}
	else if(strncmp(buffer,SOUND_1_ON,6) == 0)
	{
		press_sb_btn_once(SB_PIN_BTN01);
	}
	else if(strncmp(buffer,SOUND_1_OFF,6) == 0)
	{
		release_sb_btn(SB_PIN_BTN01);
	}
	else if(strncmp(buffer,SOUND_2_ON,6) == 0)
	{
		press_sb_btn_once(SB_PIN_BTN02);
	}
	else if(strncmp(buffer,SOUND_2_OFF,6) == 0)
	{
		release_sb_btn(SB_PIN_BTN02);
	}
	else if(strncmp(buffer,SOUND_3_ON,6) == 0)
	{
		press_sb_btn_once(SB_PIN_BTN03);
	}
	else if(strncmp(buffer,SOUND_3_OFF,6) == 0)
	{
		release_sb_btn(SB_PIN_BTN03);
	}
	else if(strncmp(buffer,SOUND_4_ON,6) == 0)
	{
		press_sb_btn_once(SB_PIN_BTN04);
	}
	else if(strncmp(buffer,SOUND_4_OFF,6) == 0)
	{
		release_sb_btn(SB_PIN_BTN04);
	}
	else if(strncmp(buffer,SOUND_5_ON,6) == 0)
	{
		press_sb_btn_once(SB_PIN_BTN05);
	}
	else if(strncmp(buffer,SOUND_5_OFF,6) == 0)
	{
		release_sb_btn(SB_PIN_BTN05);
	}
	else if(strncmp(buffer,SOUND_6_ON,6) == 0)
	{
		press_sb_btn_once(SB_PIN_BTN06);
	}
	else if(strncmp(buffer,SOUND_6_OFF,6) == 0)
	{
		release_sb_btn(SB_PIN_BTN06);
	}
	else if(strncmp(buffer,SOUND_7_ON,6) == 0)
	{
		press_sb_btn_once(SB_PIN_BTN07);
	}
	else if(strncmp(buffer,SOUND_7_OFF,6) == 0)
	{
		release_sb_btn(SB_PIN_BTN07);
	}
	else if(strncmp(buffer,SOUND_8_ON,6) == 0)
	{
		press_sb_btn_once(SB_PIN_BTN08);
	}
	else if(strncmp(buffer,SOUND_8_OFF,6) == 0)
	{
		release_sb_btn(SB_PIN_BTN08);
	}
	else if(strncmp(buffer,SOUND_9_ON,6) == 0)
	{
		press_sb_btn_once(SB_PIN_BTN09);
	}
	else if(strncmp(buffer,SOUND_9_OFF,6) == 0)
	{
		release_sb_btn(SB_PIN_BTN09);
	}
	else if(strncmp(buffer,SOUND_10_ON,6) == 0)
	{
		press_sb_btn_once(SB_PIN_BTN10);
	}
	else if(strncmp(buffer,SOUND_10_OFF,6) == 0)
	{
		release_sb_btn(SB_PIN_BTN10);
	}
	else if (strncmp(buffer,SOUND_RESET,sizeof(SOUND_RESET)-1) == 0)
	{
		ble_uart_write("SB: RESETTING");
		sounds_reset();
	}
	else if(strncmp(buffer,PARTY_ON,5) == 0)
	{
		party = true;
	}
	else if(strncmp(buffer,PARTY_OFF,5) == 0)
	{
		party = false;
		reset_all_lights();
	}
	else if(strncmp(buffer,WATER_ON,5) == 0)
	{
		water = true;
	}
	else if(strncmp(buffer,WATER_ON,5) == 0)
	{
		water = false;
	}
	else if(strncmp(buffer,START_ON,5) == 0)
	{
		start = true;
	}
	else if(strncmp(buffer,START_OFF,5) == 0)
	{
		start = false;
	}
	else if(strncmp(buffer,LED_BAR_ON,5) == 0)
	{
		configure_pin(HIGH_BEAM_LEFT_PORT,HIGH_BEAM_LEFT_ADR, HIGH_BEAM_LEFT_PIN,true);
		configure_pin(HIGH_BEAM_RIGHT_PORT,HIGH_BEAM_RIGHT_ADR, HIGH_BEAM_RIGHT_PIN,true);
		configure_pin(LEDBAR_PORT,LEDBAR_ADR, LEDBAR_PIN,true);
		led_bar = true;
	}
	else if(strncmp(buffer,LED_BAR_OFF,5) == 0)
	{
		configure_pin(HIGH_BEAM_LEFT_PORT,HIGH_BEAM_LEFT_ADR,HIGH_BEAM_LEFT_PIN,false);
		configure_pin(HIGH_BEAM_RIGHT_PORT,HIGH_BEAM_RIGHT_ADR,HIGH_BEAM_RIGHT_PIN,false);
		configure_pin(LEDBAR_PORT,LEDBAR_ADR,LEDBAR_PIN,false);
		led_bar = false;
	}
	else if(strncmp(buffer,HDL_ON,5) == 0)
	{
		configure_pin(LOW_BEAM_RIGHT_PORT,LOW_BEAM_RIGHT_ADR, LOW_BEAM_RIGHT_PIN,true);
		configure_pin(LOW_BEAM_LEFT_PORT,LOW_BEAM_LEFT_ADR, LOW_BEAM_LEFT_PIN,true);
		configure_pin(POSITION_FRONT_LEFT_PORT,POSITION_FRONT_LEFT_ADR, POSITION_FRONT_LEFT_PIN,true);
		configure_pin(POSITION_FRONT_RIGHT_PORT,POSITION_FRONT_RIGHT_ADR, POSITION_FRONT_RIGHT_PIN,true);
		configure_pin(POSITION_REAR_LEFT_PORT,POSITION_REAR_LEFT_ADR, POSITION_REAR_LEFT_PIN,true);
		configure_pin(POSITION_REAR_RIGHT_PORT,POSITION_REAR_RIGHT_ADR, POSITION_REAR_RIGHT_PIN,true);
	}
	else if(strncmp(buffer,HDL_OFF,5) == 0)
	{
		configure_pin(LOW_BEAM_RIGHT_PORT,LOW_BEAM_RIGHT_ADR,LOW_BEAM_RIGHT_PIN,false);
		configure_pin(LOW_BEAM_LEFT_PORT,LOW_BEAM_LEFT_ADR,LOW_BEAM_LEFT_PIN,false);
		configure_pin(POSITION_FRONT_LEFT_PORT,POSITION_FRONT_LEFT_ADR,POSITION_FRONT_LEFT_PIN,false);
		configure_pin(POSITION_FRONT_RIGHT_PORT,POSITION_FRONT_RIGHT_ADR,POSITION_FRONT_RIGHT_PIN,false);
		configure_pin(POSITION_REAR_LEFT_PORT,POSITION_REAR_LEFT_ADR,POSITION_REAR_LEFT_PIN,false);
		configure_pin(POSITION_REAR_RIGHT_PORT,POSITION_REAR_RIGHT_ADR,POSITION_REAR_RIGHT_PIN,false);
	}
	else if(strncmp(buffer,BRIAN_ON,7) == 0)
	{
		configure_pin(FOG_FRONT_RIGHT_PORT,FOG_FRONT_RIGHT_ADR, FOG_FRONT_RIGHT_PIN,true);
		configure_pin(FOG_FRONT_LEFT_PORT,FOG_FRONT_LEFT_ADR, FOG_FRONT_LEFT_PIN,true);
		configure_pin(POSITION_FRONT_LEFT_PORT,POSITION_FRONT_LEFT_ADR, POSITION_FRONT_LEFT_PIN,true);
		configure_pin(POSITION_FRONT_RIGHT_PORT,POSITION_FRONT_RIGHT_ADR, POSITION_FRONT_RIGHT_PIN,true);
		configure_pin(POSITION_REAR_LEFT_PORT,POSITION_REAR_LEFT_ADR, POSITION_REAR_LEFT_PIN,true);
		configure_pin(POSITION_REAR_RIGHT_PORT,POSITION_REAR_RIGHT_ADR, POSITION_REAR_RIGHT_PIN,true);
	}
	else if(strncmp(buffer,BRIAN_OFF,7) == 0)
	{
		configure_pin(FOG_FRONT_RIGHT_PORT,FOG_FRONT_RIGHT_ADR,FOG_FRONT_RIGHT_PIN,false);
		configure_pin(FOG_FRONT_LEFT_PORT,FOG_FRONT_LEFT_ADR,FOG_FRONT_LEFT_PIN,false);
		configure_pin(POSITION_FRONT_LEFT_PORT,POSITION_FRONT_LEFT_ADR,POSITION_FRONT_LEFT_PIN,false);
		configure_pin(POSITION_FRONT_RIGHT_PORT,POSITION_FRONT_RIGHT_ADR,POSITION_FRONT_RIGHT_PIN,false);
		configure_pin(POSITION_REAR_LEFT_PORT,POSITION_REAR_LEFT_ADR,POSITION_REAR_LEFT_PIN,false);
		configure_pin(POSITION_REAR_RIGHT_PORT,POSITION_REAR_RIGHT_ADR,POSITION_REAR_RIGHT_PIN,false);
	}
	else if(strncmp(buffer,FLASHY1_ON,7) == 0)
	{
		flashy1 = true;
	}
	else if(strncmp(buffer,FLASHY1_OFF,7) == 0)
	{
		flashy1 = false;
		reset_all_lights();
	}
	else if(strncmp(buffer,FLASHY2_ON,7) == 0)
	{
		flashy2 = true;
	}
	else if(strncmp(buffer,FLASHY2_OFF,7) == 0)
	{
		reset_all_lights();
		flashy2 = false;
	}
	else if(strncmp(buffer,FLASHY3_ON,7) == 0)
	{
		flashy3 = true;
	}
	else if(strncmp(buffer,FLASHY3_OFF,7) == 0)
	{
		reset_all_lights();
		flashy3 = false;
	}
	else if(strncmp(buffer,FLASHYFADE_ON,8) == 0)
	{
		flashyfade = true;
	}
	else if(strncmp(buffer,FLASHYFADE_OFF,8) == 0)
	{
		reset_all_lights();
		flashyfade = false;
	}
	else if (strncmp(buffer,MASTER_RESET,10) == 0)
	{
		ble_uart_write("RESET ACK\n");
		delay_ms(250);
		wdt_init();
		while (1)
		{
			//
		}
	}
	else if (strncmp(buffer,MINOR_RESET,sizeof(MINOR_RESET)-1) == 0)
	{
		ble_uart_write("MINOR RESET ACK\n");
		delay_ms(250);
		sounds_reset();
		init_all_ports();
		party = false;
		ble_uart_write("MINOR RESET DONE\n");
	}
	else if (strncmp(buffer,PARTY_TRESH_0,sizeof(PARTY_TRESH_0)-1)  == 0)
	{
		int temp = sizeof(PARTY_TRESH_0);//party_treshold;
		sscanf(buffer,"PRTTRSH0 %d",&temp);
		party_thresholds[0] = (uint16_t)temp;
	}
	else if (strncmp(buffer,PARTY_TRESH_1,sizeof(PARTY_TRESH_1)-1) == 0)
	{
		int temp = party_treshold;
		sscanf(buffer,"PRTTRSH1 %d",&temp);
		party_thresholds[1] = (uint16_t)temp;
	}
	else if (strncmp(buffer,PARTY_TRESH_2,sizeof(PARTY_TRESH_2)-1) == 0)
	{
		int temp = party_treshold;
		sscanf(buffer,"PRTTRSH2 %d",&temp);
		party_thresholds[2] = (uint16_t)temp;
	}
	else if (strncmp(buffer,PARTY_TRESH_3,sizeof(PARTY_TRESH_3)-1) == 0)
	{
		int temp = party_treshold;
		sscanf(buffer,"PRTTRSH3 %d",&temp);
		party_thresholds[3] = (uint16_t)temp;
	}
	else if (strncmp(buffer,PARTY_TRESH_4,sizeof(PARTY_TRESH_4)-1) == 0)
	{
		int temp = party_treshold;
		sscanf(buffer,"PRTTRSH4 %d",&temp);
		party_thresholds[4] = (uint16_t)temp;
	}
	else if (strncmp(buffer,PARTY_TRESH_5,sizeof(PARTY_TRESH_5)-1) == 0)
	{
		int temp = party_treshold;
		sscanf(buffer,"PRTTRSH5 %d",&temp);
		party_thresholds[5] = (uint16_t)temp;
	}
	else if (strncmp(buffer,PARTY_TRESH_6,sizeof(PARTY_TRESH_6)-1) == 0)
	{
		int temp = party_treshold;
		sscanf(buffer,"PRTTRSH6 %d",&temp);
		party_thresholds[6] = (uint16_t)temp;
	}
	else if (strncmp(buffer,PARTY_TRESH_7,sizeof(PARTY_TRESH_7)-1) == 0)
	{
		int temp = party_treshold;
		sscanf(buffer,"PRTTRSH7 %d",&temp);
		party_thresholds[7] = (uint16_t)temp;
	}
	else if (strncmp(buffer,CUT_OUT_VALVE_ON,sizeof(CUT_OUT_VALVE_ON)-1) == 0)
	{
		valve_open = true;
		valve_close = false;
	}
	else if (strncmp(buffer,CUT_OUT_VALVE_OFF,sizeof(CUT_OUT_VALVE_OFF)-1) == 0)
	{
		valve_open = false;
		valve_close = true;
	}
	else if(strncmp(buffer,PARTY_REV2_ON,sizeof(PARTY_REV2_ON)-1) == 0)
	{
		uint8_t temp;
		sscanf(buffer,"PRTRV21 %d",&temp);
		party_band_chosen = temp;
		partyrev2 = true;
	}
	else if(strncmp(buffer,PARTY_REV2_OFF,sizeof(PARTY_REV2_OFF)-1) == 0)
	{
		partyrev2 = false;
	}
	ble_uart_write("ACK");
}

void update_all_ports()
{
	if (!port_update_ongoing)
	{
		port_update_ongoing = true;
		for (int i=0;i<8;i++)
		{
			mcp23017_data.devices[i].outputs.pa7 = 1;
			mcp23017_data.devices[i].outputs.pb7 = 1;
			mcp23017_data.devices[i].status = mcp23017_set_pins(MCP23017_I2C_ADDR_000+i,mcp23017_data.devices[i].outputs.ports[0],mcp23017_data.devices[i].outputs.ports[1]);
		}
		port_update_ongoing = false;
	}
}

void set_blinker(bool state, bool left, bool right)
{
	if (state)
	{
		if (left)
		{
			configure_pin(BLINK_LEFT_PORT,BLINK_LEFT_ADR,BLINK_LEFT_PIN,state);
		}
		if (right)
		{
			configure_pin(BLINK_RIGHT_PORT,BLINK_RIGHT_ADR,BLINK_RIGHT_PIN,state);
		}
	}
	else
	{
		configure_pin(BLINK_RIGHT_PORT,BLINK_RIGHT_ADR, BLINK_RIGHT_PIN,state);
		configure_pin(BLINK_LEFT_PORT,BLINK_LEFT_ADR, BLINK_LEFT_PIN,state);
	}
}


void party_lights(uint16_t party_vals[])
{
	if (party_vals[0] > party_thresholds[0])
	{
		configure_pin(SUB_LEFT_PORT,SUB_LEFT_ADR,SUB_LEFT_PIN,true);
		configure_pin(SUB_RIGHT_PORT,SUB_RIGHT_ADR,SUB_RIGHT_PIN,true);
		configure_pin(REVERSE_RIGHT_PORT,REVERSE_RIGHT_ADR,REVERSE_RIGHT_PIN,true);
		configure_pin(REVERSE_LEFT_PORT,REVERSE_LEFT_ADR,REVERSE_LEFT_PIN,true);
		configure_pin(CABIN_BACK_PORT,CABIN_BACK_ADR,CABIN_BACK_PIN,true);
	}
	else
	{
		configure_pin(SUB_LEFT_PORT,SUB_LEFT_ADR, SUB_LEFT_PIN,false);
		configure_pin(SUB_RIGHT_PORT,SUB_RIGHT_ADR, SUB_RIGHT_PIN,false);
		configure_pin(REVERSE_RIGHT_PORT,REVERSE_RIGHT_ADR, REVERSE_RIGHT_PIN,false);
		configure_pin(REVERSE_LEFT_PORT,REVERSE_LEFT_ADR, REVERSE_LEFT_PIN,false);
		configure_pin(CABIN_BACK_PORT,CABIN_BACK_ADR,CABIN_BACK_PIN,false);
	}
	if (party_vals[1] > party_thresholds[1])
	{
		configure_pin(POSITION_FRONT_RIGHT_PORT,POSITION_FRONT_RIGHT_ADR,POSITION_FRONT_RIGHT_PIN,true);
		configure_pin(POSITION_FRONT_LEFT_PORT,POSITION_FRONT_LEFT_ADR,POSITION_FRONT_LEFT_PIN,true);
		configure_pin(POSITION_REAR_RIGHT_PORT,POSITION_REAR_RIGHT_ADR,POSITION_REAR_RIGHT_PIN,true);
		configure_pin(POSITION_REAR_LEFT_PORT,POSITION_REAR_LEFT_ADR,POSITION_REAR_LEFT_PIN,true);
	}
	else
	{
		configure_pin(POSITION_FRONT_RIGHT_PORT,POSITION_FRONT_RIGHT_ADR, POSITION_FRONT_RIGHT_PIN,false);
		configure_pin(POSITION_FRONT_LEFT_PORT,POSITION_FRONT_LEFT_ADR, POSITION_FRONT_LEFT_PIN,false);
		configure_pin(POSITION_REAR_RIGHT_PORT,POSITION_REAR_RIGHT_ADR, POSITION_REAR_RIGHT_PIN,false);
		configure_pin(POSITION_REAR_LEFT_PORT,POSITION_REAR_LEFT_ADR, POSITION_REAR_LEFT_PIN,false);
	}
	if (party_vals[2] > party_thresholds[2])
	{
		configure_pin(LOW_BEAM_LEFT_PORT,LOW_BEAM_RIGHT_ADR,LOW_BEAM_RIGHT_PIN,true);
		configure_pin(LOW_BEAM_LEFT_PORT,LOW_BEAM_LEFT_ADR,LOW_BEAM_LEFT_PIN,true);
	}
	else
	{
		configure_pin(LOW_BEAM_LEFT_PORT,LOW_BEAM_RIGHT_ADR, LOW_BEAM_RIGHT_PIN,false);
		configure_pin(LOW_BEAM_LEFT_PORT,LOW_BEAM_LEFT_ADR, LOW_BEAM_LEFT_PIN,false);
	}
	if (party_vals[3] > party_thresholds[3])
	{
		configure_pin(HIGH_BEAM_LEFT_PORT,HIGH_BEAM_RIGHT_ADR,HIGH_BEAM_RIGHT_PIN,true);
		configure_pin(HIGH_BEAM_LEFT_PORT,HIGH_BEAM_LEFT_ADR,HIGH_BEAM_LEFT_PIN,true);
		configure_pin(CABIN_MIDDLE_PORT,CABIN_MIDDLE_ADR,CABIN_MIDDLE_PIN,true);
	}
	else
	{
		configure_pin(HIGH_BEAM_LEFT_PORT,HIGH_BEAM_RIGHT_ADR, HIGH_BEAM_RIGHT_PIN,false);
		configure_pin(HIGH_BEAM_LEFT_PORT,HIGH_BEAM_LEFT_ADR, HIGH_BEAM_LEFT_PIN,false);
		configure_pin(CABIN_MIDDLE_PORT,CABIN_MIDDLE_ADR,CABIN_MIDDLE_PIN,false);

	}
	if (party_vals[4] > party_thresholds[4])
	{
		configure_pin(BLINK_RIGHT_PORT,BLINK_RIGHT_ADR,BLINK_RIGHT_PIN,true);
		configure_pin(BLINK_LEFT_PORT,BLINK_LEFT_ADR,BLINK_LEFT_PIN,true);
		configure_pin(CABIN_FRONT_PORT,CABIN_FRONT_ADR,CABIN_FRONT_PIN,true);
	}
	else
	{
		configure_pin(BLINK_RIGHT_PORT,BLINK_RIGHT_ADR, BLINK_RIGHT_PIN,false);
		configure_pin(BLINK_LEFT_PORT,BLINK_LEFT_ADR, BLINK_LEFT_PIN,false);
		configure_pin(CABIN_FRONT_PORT,CABIN_FRONT_ADR,CABIN_FRONT_PIN,false);
	}
	if (party_vals[5] > party_thresholds[5])
	{
		configure_pin(FOG_FRONT_LEFT_PORT,FOG_FRONT_LEFT_ADR,FOG_FRONT_LEFT_PIN,true);
		configure_pin(FOG_FRONT_RIGHT_PORT,FOG_FRONT_RIGHT_ADR,FOG_FRONT_RIGHT_PIN,true);
	}
	else
	{
		configure_pin(FOG_FRONT_LEFT_PORT,FOG_FRONT_LEFT_ADR, FOG_FRONT_LEFT_PIN,false);
		configure_pin(FOG_FRONT_RIGHT_PORT,FOG_FRONT_RIGHT_ADR, FOG_FRONT_RIGHT_PIN,false);
	}
	if (party_vals[6] > party_thresholds[6])
	{
		configure_pin(LEDBAR_PORT,LEDBAR_ADR,LEDBAR_PIN,true);
	}
	else
	{
		configure_pin(LEDBAR_PORT,LEDBAR_ADR, LEDBAR_PIN,false);
	}
}

void party_lights_2(uint16_t party_vals[],uint8_t band)
{
	reset_all_lights();
	configure_pin(LOW_BEAM_LEFT_PORT,LOW_BEAM_LEFT_ADR,LOW_BEAM_LEFT_PIN,party_vals[band]>party_thresholds[band]);
	configure_pin(LOW_BEAM_RIGHT_PORT,LOW_BEAM_RIGHT_ADR,LOW_BEAM_RIGHT_PIN,party_vals[band]>party_thresholds[band]);

	configure_pin(HIGH_BEAM_LEFT_PORT,HIGH_BEAM_LEFT_ADR,HIGH_BEAM_LEFT_PIN,party_vals[band]>party_thresholds[band]+100);
	configure_pin(HIGH_BEAM_RIGHT_PORT,HIGH_BEAM_RIGHT_ADR,HIGH_BEAM_RIGHT_PIN,party_vals[band]>party_thresholds[band]+100);
	configure_pin(POSITION_REAR_LEFT_PORT,POSITION_REAR_LEFT_ADR,POSITION_REAR_LEFT_PIN,party_vals[band]>party_thresholds[band]+100);
	configure_pin(POSITION_REAR_RIGHT_PORT,POSITION_REAR_RIGHT_ADR,POSITION_REAR_RIGHT_PIN,party_vals[band]>party_thresholds[band]+100);

	configure_pin(POSITION_FRONT_RIGHT_PORT,POSITION_FRONT_RIGHT_ADR,POSITION_FRONT_RIGHT_PIN,party_vals[band]>party_thresholds[band]+200);
	configure_pin(POSITION_FRONT_LEFT_PORT,POSITION_FRONT_LEFT_ADR,POSITION_FRONT_LEFT_PIN,party_vals[band]>party_thresholds[band]+200);
	configure_pin(REVERSE_LEFT_PORT,REVERSE_LEFT_ADR,REVERSE_LEFT_PIN,party_vals[band]>party_thresholds[band]+200);
	configure_pin(REVERSE_RIGHT_PORT,REVERSE_RIGHT_ADR,REVERSE_RIGHT_PIN,party_vals[band]>party_thresholds[band]+200);

	configure_pin(BLINK_LEFT_PORT,BLINK_LEFT_ADR,BLINK_LEFT_PIN,party_vals[band]>party_thresholds[band]+300);
	configure_pin(BLINK_RIGHT_PORT,BLINK_RIGHT_ADR,BLINK_RIGHT_PIN,party_vals[band]>party_thresholds[band]+300);
}

void flashy_flash1()
{
	static uint8_t state = 0;
	switch(state)
	{
		case 0:
			reset_all_lights();
			configure_pin(LOW_BEAM_RIGHT_PORT,LOW_BEAM_RIGHT_ADR,LOW_BEAM_RIGHT_PIN,true);
			break;
		case 1:
			reset_all_lights();
			configure_pin(HIGH_BEAM_RIGHT_PORT,HIGH_BEAM_RIGHT_ADR,HIGH_BEAM_RIGHT_PIN,true);
			break;
		case 2:
			reset_all_lights();
			configure_pin(POSITION_FRONT_RIGHT_PORT,POSITION_FRONT_RIGHT_ADR,POSITION_FRONT_RIGHT_PIN,true);
			break;
		case 3:
			reset_all_lights();
			configure_pin(POSITION_FRONT_LEFT_PORT,POSITION_FRONT_LEFT_ADR,POSITION_FRONT_LEFT_PIN,true);
			state++;
			break;
		case 4:
			reset_all_lights();
			configure_pin(HIGH_BEAM_LEFT_PORT,LOW_BEAM_LEFT_ADR,LOW_BEAM_LEFT_PIN,true);
			break;
		case 5:
			reset_all_lights();
			configure_pin(LOW_BEAM_LEFT_PORT,HIGH_BEAM_LEFT_ADR,HIGH_BEAM_LEFT_PIN,true);
			break;
		case 6:
			reset_all_lights();
			configure_pin(BLINK_LEFT_PORT,BLINK_LEFT_ADR,BLINK_LEFT_PIN,true);
			break;
		case 7:
			reset_all_lights();
			configure_pin(REVERSE_LEFT_PORT,REVERSE_LEFT_ADR,REVERSE_LEFT_PIN,true);
			break;
		case 8:
			reset_all_lights();
			configure_pin(POSITION_REAR_LEFT_PORT,POSITION_REAR_LEFT_ADR,POSITION_REAR_LEFT_PIN,true);
			break;
		case 9:
			reset_all_lights();
			configure_pin(POSITION_REAR_RIGHT_PORT,POSITION_REAR_RIGHT_ADR,POSITION_REAR_RIGHT_PIN,true);
			break;
		case 10:
			reset_all_lights();
			configure_pin(REVERSE_RIGHT_PORT,REVERSE_RIGHT_ADR,REVERSE_RIGHT_PIN,true);
			break;
		case 11:
			reset_all_lights();
			configure_pin(BLINK_RIGHT_PORT,BLINK_RIGHT_ADR,BLINK_RIGHT_PIN,true);
			break;
		case 12:
			reset_all_lights();
			state = 0;
			break;
		default:
			reset_all_lights();
			state = 0;
			break;
	}
	state++;
}

void flashy_flash2()
{
	static uint8_t state = 0;
	switch(state)
	{
		case 0:
			reset_all_lights();
			configure_pin(LEDBAR_PORT,LEDBAR_ADR,LEDBAR_PIN,true);
			state++;
			break;
		case 1:
			configure_pin(LEDBAR_PORT,LEDBAR_ADR, LEDBAR_PIN,false);
			state++;
			break;
		case 2:
			configure_pin(LEDBAR_PORT,LEDBAR_ADR,LEDBAR_PIN,true);
			state++;
			break;
		case 3:
			configure_pin(LEDBAR_PORT,LEDBAR_ADR, LEDBAR_PIN,false);
			state++;
			break;
		case 4:
			configure_pin(LEDBAR_PORT,LEDBAR_ADR,LEDBAR_PIN,true);
			state++;
			break;
		case 5:
			configure_pin(LEDBAR_PORT,LEDBAR_ADR, LEDBAR_PIN,false);
			state++;
			break;
		case 6:
			configure_pin(HIGH_BEAM_LEFT_PORT,HIGH_BEAM_LEFT_ADR,HIGH_BEAM_LEFT_PIN,true);
			configure_pin(HIGH_BEAM_RIGHT_PORT,HIGH_BEAM_RIGHT_ADR,HIGH_BEAM_RIGHT_PIN,true);
			configure_pin(REVERSE_LEFT_PORT,REVERSE_LEFT_ADR,REVERSE_LEFT_PIN,true);
			configure_pin(REVERSE_RIGHT_PORT,REVERSE_RIGHT_ADR,REVERSE_RIGHT_PIN,true);
			state++;
			break;
		case 7:
			configure_pin(HIGH_BEAM_LEFT_PORT,HIGH_BEAM_LEFT_ADR, HIGH_BEAM_LEFT_PIN,false);
			configure_pin(HIGH_BEAM_RIGHT_PORT,HIGH_BEAM_RIGHT_ADR, HIGH_BEAM_RIGHT_PIN,false);
			configure_pin(LOW_BEAM_LEFT_PORT,LOW_BEAM_LEFT_ADR,LOW_BEAM_LEFT_PIN,true);
			configure_pin(LOW_BEAM_RIGHT_PORT,LOW_BEAM_RIGHT_ADR,LOW_BEAM_RIGHT_PIN,true);
			configure_pin(REVERSE_LEFT_PORT,REVERSE_LEFT_ADR, REVERSE_LEFT_PIN,false);
			configure_pin(REVERSE_RIGHT_PORT,REVERSE_RIGHT_ADR, REVERSE_RIGHT_PIN,false);
			state++;
			break;
		case 8:
			configure_pin(LOW_BEAM_LEFT_PORT,LOW_BEAM_LEFT_ADR, LOW_BEAM_LEFT_PIN,false);
			configure_pin(LOW_BEAM_RIGHT_PORT,LOW_BEAM_RIGHT_ADR, LOW_BEAM_RIGHT_PIN,false);
			configure_pin(FOG_FRONT_LEFT_PORT,FOG_FRONT_LEFT_ADR,FOG_FRONT_LEFT_PIN,true);
			configure_pin(FOG_FRONT_RIGHT_PORT,FOG_FRONT_RIGHT_ADR,FOG_FRONT_RIGHT_PIN,true);
			configure_pin(POSITION_REAR_LEFT_PORT,POSITION_REAR_LEFT_ADR,POSITION_REAR_LEFT_PIN,true);
			configure_pin(POSITION_REAR_RIGHT_PORT,POSITION_REAR_RIGHT_ADR,POSITION_REAR_RIGHT_PIN,true);
			state++;
			break;
		case 9:
			configure_pin(FOG_FRONT_LEFT_PORT,FOG_FRONT_LEFT_ADR, FOG_FRONT_LEFT_PIN,false);
			configure_pin(FOG_FRONT_RIGHT_PORT,FOG_FRONT_RIGHT_ADR, FOG_FRONT_RIGHT_PIN,false);
			configure_pin(LOW_BEAM_LEFT_PORT,LOW_BEAM_LEFT_ADR,LOW_BEAM_LEFT_PIN,true);
			configure_pin(LOW_BEAM_RIGHT_PORT,LOW_BEAM_RIGHT_ADR,LOW_BEAM_RIGHT_PIN,true);
			configure_pin(POSITION_REAR_LEFT_PORT,POSITION_REAR_LEFT_ADR, POSITION_REAR_LEFT_PIN,false);
			configure_pin(POSITION_REAR_RIGHT_PORT,POSITION_REAR_RIGHT_ADR, POSITION_REAR_RIGHT_PIN,false);
			state++;
			break;
		case 10:
			configure_pin(LOW_BEAM_LEFT_PORT,LOW_BEAM_LEFT_ADR, LOW_BEAM_LEFT_PIN,false);
			configure_pin(LOW_BEAM_RIGHT_PORT,LOW_BEAM_RIGHT_ADR, LOW_BEAM_RIGHT_PIN,false);
			configure_pin(HIGH_BEAM_LEFT_PORT,HIGH_BEAM_LEFT_ADR,HIGH_BEAM_LEFT_PIN,true);
			configure_pin(HIGH_BEAM_RIGHT_PORT,HIGH_BEAM_RIGHT_ADR,HIGH_BEAM_RIGHT_PIN,true);
			state = 0;
			break;
		default:
			reset_all_lights();
			state = 0;
	}
}

void flashy_fades()
{
	//static uint8_t pwm_val = 0;
	static uint8_t duty_cycle = PWM_FREQ/4;
	
	if (pwm_count > duty_cycle)
	{
		configure_pin(POSITION_FRONT_LEFT_PORT,POSITION_FRONT_LEFT_ADR,POSITION_FRONT_LEFT_PIN,true);
		configure_pin(POSITION_FRONT_RIGHT_PORT,POSITION_FRONT_RIGHT_ADR,POSITION_FRONT_RIGHT_PIN,true);
		configure_pin(POSITION_REAR_LEFT_PORT,POSITION_REAR_LEFT_ADR,POSITION_REAR_LEFT_PIN,true);
		configure_pin(POSITION_REAR_RIGHT_PORT,POSITION_REAR_RIGHT_ADR,POSITION_REAR_RIGHT_PIN,true);
		
		configure_pin(LOW_BEAM_RIGHT_PORT,LOW_BEAM_RIGHT_ADR,LOW_BEAM_RIGHT_PIN,true);
		configure_pin(LOW_BEAM_LEFT_PORT,LOW_BEAM_LEFT_ADR,LOW_BEAM_LEFT_PIN,true);
		
		configure_pin(HIGH_BEAM_RIGHT_PORT,HIGH_BEAM_RIGHT_ADR,HIGH_BEAM_RIGHT_PIN,true);
		configure_pin(HIGH_BEAM_LEFT_PORT,HIGH_BEAM_LEFT_ADR,HIGH_BEAM_LEFT_PIN,true);
		
		configure_pin(BLINK_RIGHT_PORT,BLINK_RIGHT_ADR,BLINK_RIGHT_PIN,true);
		configure_pin(BLINK_LEFT_PORT,BLINK_LEFT_ADR,BLINK_LEFT_PIN,true);
		
		configure_pin(REVERSE_LEFT_PORT,REVERSE_LEFT_ADR,REVERSE_LEFT_PIN,true);
		configure_pin(REVERSE_RIGHT_PORT,REVERSE_RIGHT_ADR,REVERSE_RIGHT_PIN,true);
		
		configure_pin(FOG_FRONT_RIGHT_PORT,FOG_FRONT_RIGHT_ADR,FOG_FRONT_RIGHT_PIN,true);
		configure_pin(FOG_FRONT_LEFT_PORT,FOG_FRONT_LEFT_ADR,FOG_FRONT_LEFT_PIN,true);
	}
	else
	{
		configure_pin(POSITION_FRONT_LEFT_PORT,POSITION_FRONT_LEFT_ADR, POSITION_FRONT_LEFT_PIN,false);
		configure_pin(POSITION_FRONT_RIGHT_PORT,POSITION_FRONT_RIGHT_ADR, POSITION_FRONT_RIGHT_PIN,false);
		configure_pin(POSITION_REAR_LEFT_PORT,POSITION_REAR_LEFT_ADR, POSITION_REAR_LEFT_PIN,false);
		configure_pin(POSITION_REAR_RIGHT_PORT,POSITION_REAR_RIGHT_ADR, POSITION_REAR_RIGHT_PIN,false);
		
		configure_pin(LOW_BEAM_RIGHT_PORT,LOW_BEAM_RIGHT_ADR, LOW_BEAM_RIGHT_PIN,false);
		configure_pin(LOW_BEAM_LEFT_PORT,LOW_BEAM_LEFT_ADR, LOW_BEAM_LEFT_PIN,false);
		
		configure_pin(HIGH_BEAM_RIGHT_PORT,HIGH_BEAM_RIGHT_ADR, HIGH_BEAM_RIGHT_PIN,false);
		configure_pin(HIGH_BEAM_LEFT_PORT,HIGH_BEAM_LEFT_ADR, HIGH_BEAM_LEFT_PIN,false);
		
		configure_pin(BLINK_RIGHT_PORT,BLINK_RIGHT_ADR, BLINK_RIGHT_PIN,false);
		configure_pin(BLINK_LEFT_PORT,BLINK_LEFT_ADR, BLINK_LEFT_PIN,false);
		
		configure_pin(REVERSE_LEFT_PORT,REVERSE_LEFT_ADR, REVERSE_LEFT_PIN,false);
		configure_pin(REVERSE_RIGHT_PORT,REVERSE_RIGHT_ADR, REVERSE_RIGHT_PIN,false);
		
		configure_pin(FOG_FRONT_RIGHT_PORT,FOG_FRONT_RIGHT_ADR, FOG_FRONT_RIGHT_PIN,false);
		configure_pin(FOG_FRONT_LEFT_PORT,FOG_FRONT_LEFT_ADR, FOG_FRONT_LEFT_PIN,false);
	}
	
	//pwm_val++;
	if (pwm_count >= PWM_FREQ)
	{
		//pwm_val = 0;
		duty_cycle += PWM_FREQ/10;
		if (duty_cycle >= PWM_FREQ)
		{
			duty_cycle = PWM_FREQ/4;
		}
	}
}

void flashy_flash3(void)
{
	static uint8_t count = 0;
	
	reset_all_lights();

	configure_pin(BLINK_LEFT_PORT,BLINK_LEFT_ADR,BLINK_LEFT_PIN,bool_map_1[count][0]);
	configure_pin(LOW_BEAM_LEFT_PORT,LOW_BEAM_LEFT_ADR,LOW_BEAM_LEFT_PIN,bool_map_1[count][1]);
	configure_pin(HIGH_BEAM_LEFT_PORT,HIGH_BEAM_LEFT_ADR,HIGH_BEAM_LEFT_PIN,bool_map_1[count][2]);
	configure_pin(POSITION_FRONT_LEFT_PORT,POSITION_FRONT_LEFT_ADR,POSITION_FRONT_LEFT_PIN,bool_map_1[count][3]);
	configure_pin(POSITION_FRONT_RIGHT_PORT,POSITION_FRONT_RIGHT_ADR,POSITION_FRONT_RIGHT_PIN,bool_map_1[count][4]);
	configure_pin(HIGH_BEAM_RIGHT_PORT,HIGH_BEAM_RIGHT_ADR,HIGH_BEAM_RIGHT_PIN,bool_map_1[count][5]);
	configure_pin(LOW_BEAM_RIGHT_PORT,LOW_BEAM_RIGHT_ADR,LOW_BEAM_RIGHT_PIN,bool_map_1[count][6]);
	configure_pin(BLINK_RIGHT_PORT,BLINK_RIGHT_ADR,BLINK_RIGHT_PIN,bool_map_1[count][7]);
	count++;
	if(count > 25)
	{
		count = 0;
	}
}

void reset_all_lights()
{
	for (int i=0;i<8;i++)
	{
		mcp23017_data.devices[i].outputs.ports[0] = 0x80;
		mcp23017_data.devices[i].outputs.ports[1] = 0x80;
	}
}

bool a_okay()
{
	char buffer[32];
	uint8_t states[8];
	mcp23017_read_all_ports(read_data,states);
	
	bool return_val = true;
	for (int i=0;i<8;i++)
	{
		if (mcp23017_data.devices[i].should_be_enabled)
		{
			mcp23017_data.devices[i].output_errors.ports[0] = mcp23017_data.devices[i].outputs.ports[0] - read_data[0][i];
			mcp23017_data.devices[i].output_errors.ports[1] = mcp23017_data.devices[i].outputs.ports[1] - read_data[1][i];
			
			if ((mcp23017_data.devices[i].output_errors.ports[0] + mcp23017_data.devices[i].output_errors.ports[1]) > 0)
			{
				mcp23017_data.devices[i].error_detected = true;
			}
			
			if ((read_data[0][i] & ~0x80) != (mcp23017_data.devices[i].outputs.ports[0] & ~0x80))
			{
				return_val = false;
			}
			if ((read_data[1][i] & ~0x80) != (mcp23017_data.devices[i].outputs.ports[1] & ~0x80))
			{
				return_val = false;
			}
		}
		mcp23017_data.devices[i].status = states[i];
		sprintf(buffer,"ADDR: %d -> %d\n",i,mcp23017_data.devices[i].status);
		ble_uart_write(buffer);
		uart_write(buffer);
	}
	sprintf(buffer,"ERR: %d%d%d%d%d%d%d%d\r\n",mcp23017_data.devices[7].error_detected,mcp23017_data.devices[6].error_detected,mcp23017_data.devices[5].error_detected,mcp23017_data.devices[4].error_detected,mcp23017_data.devices[3].error_detected,mcp23017_data.devices[2].error_detected,mcp23017_data.devices[1].error_detected,mcp23017_data.devices[0].error_detected);
	ble_uart_write(buffer);
	uart_write(buffer);
	
	return return_val;
}

void configure_pin(uint8_t port, uint8_t addr, uint8_t pin, bool value)
{
	if(value)
	{
		mcp23017_data.devices[addr].outputs.ports[port] |= (1 << pin);
	}
	else
	{
		mcp23017_data.devices[addr].outputs.ports[port] &= ~(1 << pin);
	}
}

void mcp23017_reset_error_codes()
{
	for (int i=0;i<8;i++)
	{
		mcp23017_data.devices[i].output_errors.ports[0] = 0;
		mcp23017_data.devices[i].output_errors.ports[1] = 0;
		mcp23017_data.devices[i].error_detected = false;
		mcp23017_data.devices[i].status = STATUS_OK;
	}
}