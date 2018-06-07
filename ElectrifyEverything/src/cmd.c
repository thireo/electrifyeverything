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
	uint8_t porta;
	uint8_t portb;
}mcp23017_ports_object;


struct mcp23017_devices
{
	bool should_be_enabled;
	bool is_enabled;
	uint8_t i2c_addr;
	mcp23017_ports_object ports;
};

struct mcp23017_object
{
	struct mcp23017_devices devices[8];
};

struct mcp23017_object mcp23017_data={				\
	.devices[0].should_be_enabled = false,			\
	.devices[0].is_enabled = false,					\
	.devices[0].i2c_addr = MCP23017_I2C_ADDR_000,	\
	.devices[0].ports.porta = 0x00,					\
	.devices[0].ports.portb = 0x00,					\
	.devices[1].should_be_enabled = true,			\
	.devices[1].is_enabled = false,					\
	.devices[1].i2c_addr = MCP23017_I2C_ADDR_001,	\
	.devices[1].ports.porta = 0x00,					\
	.devices[1].ports.portb = 0x00,					\
	.devices[2].should_be_enabled = true,			\
	.devices[2].is_enabled = false,					\
	.devices[2].i2c_addr = MCP23017_I2C_ADDR_010,	\
	.devices[2].ports.porta = 0x00,					\
	.devices[2].ports.portb = 0x00,					\
	.devices[3].should_be_enabled = true,			\
	.devices[3].is_enabled = false,					\
	.devices[3].i2c_addr = MCP23017_I2C_ADDR_011,	\
	.devices[3].ports.porta = 0x00,					\
	.devices[3].ports.portb = 0x00,					\
	.devices[4].should_be_enabled = true,			\
	.devices[4].is_enabled = false,					\
	.devices[4].i2c_addr = MCP23017_I2C_ADDR_100,	\
	.devices[4].ports.porta = 0x00,					\
	.devices[4].ports.portb = 0x00,					\
	.devices[5].should_be_enabled = false,			\
	.devices[5].is_enabled = false,					\
	.devices[5].i2c_addr = MCP23017_I2C_ADDR_101,	\
	.devices[5].ports.porta = 0x00,					\
	.devices[5].ports.portb = 0x00,					\
	.devices[6].should_be_enabled = false,			\
	.devices[6].is_enabled = false,					\
	.devices[6].i2c_addr = MCP23017_I2C_ADDR_110,	\
	.devices[6].ports.porta = 0x00,					\
	.devices[6].ports.portb = 0x00,					\
	.devices[7].should_be_enabled = false,			\
	.devices[7].is_enabled = false,					\
	.devices[7].i2c_addr = MCP23017_I2C_ADDR_111,	\
	.devices[7].ports.porta = 0x00,					\
	.devices[7].ports.portb = 0x00};



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
		data_LED[POSITION_FRONT_LEFT_PORT][POSITION_FRONT_LEFT_ADR] |= (1 << POSITION_FRONT_LEFT_PIN);
		data_LED[POSITION_FRONT_RIGHT_PORT][POSITION_FRONT_RIGHT_ADR] |= (1 << POSITION_FRONT_RIGHT_PIN);
		data_LED[POSITION_REAR_LEFT_PORT][POSITION_REAR_LEFT_ADR] |= (1 << POSITION_REAR_LEFT_PIN);
		data_LED[POSITION_REAR_RIGHT_PORT][POSITION_REAR_RIGHT_ADR] |= (1 << POSITION_REAR_RIGHT_PIN);
		
		data_LED[LOW_BEAM_RIGHT_PORT][LOW_BEAM_RIGHT_ADR] |= (1 << LOW_BEAM_RIGHT_PIN);
		data_LED[LOW_BEAM_LEFT_PORT][LOW_BEAM_LEFT_ADR] |= (1 << LOW_BEAM_LEFT_PIN);
		
		data_LED[HIGH_BEAM_RIGHT_PORT][HIGH_BEAM_RIGHT_ADR] |= (1 << HIGH_BEAM_RIGHT_PIN);
		data_LED[HIGH_BEAM_LEFT_PORT][HIGH_BEAM_LEFT_ADR] |= (1 << HIGH_BEAM_LEFT_PIN);
		
		data_LED[BLINK_RIGHT_PORT][BLINK_RIGHT_ADR] |= (1 << BLINK_RIGHT_PIN);
		data_LED[BLINK_LEFT_PORT][BLINK_LEFT_ADR] |= (1 << BLINK_LEFT_PIN);
		
		data_LED[REVERSE_LEFT_PORT][REVERSE_LEFT_ADR] |= (1 << REVERSE_LEFT_PIN);
		data_LED[REVERSE_RIGHT_PORT][REVERSE_RIGHT_ADR] |= (1 << REVERSE_RIGHT_PIN);
		
		data_LED[FOG_FRONT_RIGHT_PORT][FOG_FRONT_RIGHT_ADR] |= (1 << FOG_FRONT_RIGHT_PIN);
		data_LED[FOG_FRONT_LEFT_PORT][FOG_FRONT_LEFT_ADR] |= (1 << FOG_FRONT_LEFT_PIN);
		
		data_LED[SUB_LEFT_PORT][SUB_LEFT_ADR] |= (1 << SUB_LEFT_PIN);
		data_LED[SUB_RIGHT_PORT][SUB_RIGHT_ADR] |= (1 << SUB_RIGHT_PIN);
		
		data_LED[LEDBAR_PORT][LEDBAR_ADR] |= (1 << LEDBAR_PIN);
		
		flash_all = true;
	}
	else if(strncmp(buffer,FLASH_ALL_OFF,4) == 0)
	{
		data_LED[POSITION_FRONT_LEFT_PORT][POSITION_FRONT_LEFT_ADR] &= ~(1 << POSITION_FRONT_LEFT_PIN);
		data_LED[POSITION_FRONT_RIGHT_PORT][POSITION_FRONT_RIGHT_ADR] &= ~(1 << POSITION_FRONT_RIGHT_PIN);
		data_LED[POSITION_REAR_LEFT_PORT][POSITION_REAR_LEFT_ADR] &= ~(1 << POSITION_REAR_LEFT_PIN);
		data_LED[POSITION_REAR_RIGHT_PORT][POSITION_REAR_RIGHT_ADR] &= ~(1 << POSITION_REAR_RIGHT_PIN);
		
		data_LED[LOW_BEAM_RIGHT_PORT][LOW_BEAM_RIGHT_ADR] &= ~(1 << LOW_BEAM_RIGHT_PIN);
		data_LED[LOW_BEAM_LEFT_PORT][LOW_BEAM_LEFT_ADR] &= ~(1 << LOW_BEAM_LEFT_PIN);
		
		data_LED[HIGH_BEAM_RIGHT_PORT][HIGH_BEAM_RIGHT_ADR] &= ~(1 << HIGH_BEAM_RIGHT_PIN);
		data_LED[HIGH_BEAM_LEFT_PORT][HIGH_BEAM_LEFT_ADR] &= ~(1 << HIGH_BEAM_LEFT_PIN);
		
		data_LED[BLINK_RIGHT_PORT][BLINK_RIGHT_ADR] &= ~(1 << BLINK_RIGHT_PIN);
		data_LED[BLINK_LEFT_PORT][BLINK_LEFT_ADR] &= ~(1 << BLINK_LEFT_PIN);
		
		data_LED[REVERSE_LEFT_PORT][REVERSE_LEFT_ADR] &= ~(1 << REVERSE_LEFT_PIN);
		data_LED[REVERSE_RIGHT_PORT][REVERSE_RIGHT_ADR] &= ~(1 << REVERSE_RIGHT_PIN);
		
		data_LED[FOG_FRONT_RIGHT_PORT][FOG_FRONT_RIGHT_ADR] &= ~(1 << FOG_FRONT_RIGHT_PIN);
		data_LED[FOG_FRONT_LEFT_PORT][FOG_FRONT_LEFT_ADR] &= ~(1 << FOG_FRONT_LEFT_PIN);
		
		data_LED[SUB_LEFT_PORT][SUB_LEFT_ADR] &= ~(1 << SUB_LEFT_PIN);
		data_LED[SUB_RIGHT_PORT][SUB_RIGHT_ADR] &= ~(1 << SUB_RIGHT_PIN);
		
		data_LED[LEDBAR_PORT][LEDBAR_ADR] &= ~(1 << LEDBAR_PIN);
		
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
		press_sb_btn(SB_PIN_BTN00);
	}
	else if(strncmp(buffer,SOUND_0_OFF,6) == 0)
	{
		release_sb_btn(SB_PIN_BTN00);
	}
	else if(strncmp(buffer,SOUND_1_ON,6) == 0)
	{
		press_sb_btn(SB_PIN_BTN01);
	}
	else if(strncmp(buffer,SOUND_1_OFF,6) == 0)
	{
		release_sb_btn(SB_PIN_BTN01);
	}
	else if(strncmp(buffer,SOUND_2_ON,6) == 0)
	{
		press_sb_btn(SB_PIN_BTN02);
	}
	else if(strncmp(buffer,SOUND_2_OFF,6) == 0)
	{
		release_sb_btn(SB_PIN_BTN02);
	}
	else if(strncmp(buffer,SOUND_3_ON,6) == 0)
	{
		press_sb_btn(SB_PIN_BTN03);
	}
	else if(strncmp(buffer,SOUND_3_OFF,6) == 0)
	{
		release_sb_btn(SB_PIN_BTN03);
	}
	else if(strncmp(buffer,SOUND_4_ON,6) == 0)
	{
		press_sb_btn(SB_PIN_BTN04);
	}
	else if(strncmp(buffer,SOUND_4_OFF,6) == 0)
	{
		release_sb_btn(SB_PIN_BTN04);
	}
	else if(strncmp(buffer,SOUND_5_ON,6) == 0)
	{
		press_sb_btn(SB_PIN_BTN05);
	}
	else if(strncmp(buffer,SOUND_5_OFF,6) == 0)
	{
		release_sb_btn(SB_PIN_BTN05);
	}
	else if(strncmp(buffer,SOUND_6_ON,6) == 0)
	{
		press_sb_btn(SB_PIN_BTN06);
	}
	else if(strncmp(buffer,SOUND_6_OFF,6) == 0)
	{
		release_sb_btn(SB_PIN_BTN06);
	}
	else if(strncmp(buffer,SOUND_7_ON,6) == 0)
	{
		press_sb_btn(SB_PIN_BTN07);
	}
	else if(strncmp(buffer,SOUND_7_OFF,6) == 0)
	{
		release_sb_btn(SB_PIN_BTN07);
	}
	else if(strncmp(buffer,SOUND_8_ON,6) == 0)
	{
		press_sb_btn(SB_PIN_BTN08);
	}
	else if(strncmp(buffer,SOUND_8_OFF,6) == 0)
	{
		release_sb_btn(SB_PIN_BTN08);
	}
	else if(strncmp(buffer,SOUND_9_ON,6) == 0)
	{
		press_sb_btn(SB_PIN_BTN09);
	}
	else if(strncmp(buffer,SOUND_9_OFF,6) == 0)
	{
		release_sb_btn(SB_PIN_BTN09);
	}
	else if(strncmp(buffer,SOUND_10_ON,6) == 0)
	{
		press_sb_btn(SB_PIN_BTN10);
	}
	else if(strncmp(buffer,SOUND_10_OFF,6) == 0)
	{
		release_sb_btn(SB_PIN_BTN10);
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
		data_LED[HIGH_BEAM_LEFT_PORT][HIGH_BEAM_LEFT_ADR] |= (1 << HIGH_BEAM_LEFT_PIN);
		data_LED[HIGH_BEAM_RIGHT_PORT][HIGH_BEAM_RIGHT_ADR] |= (1 << HIGH_BEAM_RIGHT_PIN);
		data_LED[LEDBAR_PORT][LEDBAR_ADR] |= (1 << LEDBAR_PIN);
		led_bar = true;
	}
	else if(strncmp(buffer,LED_BAR_OFF,5) == 0)
	{
		data_LED[HIGH_BEAM_LEFT_PORT][HIGH_BEAM_LEFT_ADR] &= ~(1 << HIGH_BEAM_LEFT_PIN);
		data_LED[HIGH_BEAM_RIGHT_PORT][HIGH_BEAM_RIGHT_ADR] &= ~(1 << HIGH_BEAM_RIGHT_PIN);
		data_LED[LEDBAR_PORT][LEDBAR_ADR] &= ~(1 << LEDBAR_PIN);
		led_bar = false;
	}
	else if(strncmp(buffer,HDL_ON,5) == 0)
	{
		data_LED[LOW_BEAM_RIGHT_PORT][LOW_BEAM_RIGHT_ADR] |= (1 << LOW_BEAM_RIGHT_PIN);
		data_LED[LOW_BEAM_LEFT_PORT][LOW_BEAM_LEFT_ADR] |= (1 << LOW_BEAM_LEFT_PIN);
		data_LED[POSITION_FRONT_LEFT_PORT][POSITION_FRONT_LEFT_ADR] |= (1 << POSITION_FRONT_LEFT_PIN);
		data_LED[POSITION_FRONT_RIGHT_PORT][POSITION_FRONT_RIGHT_ADR] |= (1 << POSITION_FRONT_RIGHT_PIN);
		data_LED[POSITION_REAR_LEFT_PORT][POSITION_REAR_LEFT_ADR] |= (1 << POSITION_REAR_LEFT_PIN);
		data_LED[POSITION_REAR_RIGHT_PORT][POSITION_REAR_RIGHT_ADR] |= (1 << POSITION_REAR_RIGHT_PIN);
	}
	else if(strncmp(buffer,HDL_OFF,5) == 0)
	{
		data_LED[LOW_BEAM_RIGHT_PORT][LOW_BEAM_RIGHT_ADR] &= ~(1 << LOW_BEAM_RIGHT_PIN);
		data_LED[LOW_BEAM_LEFT_PORT][LOW_BEAM_LEFT_ADR] &= ~(1 << LOW_BEAM_LEFT_PIN);
		data_LED[POSITION_FRONT_LEFT_PORT][POSITION_FRONT_LEFT_ADR] &= ~(1 << POSITION_FRONT_LEFT_PIN);
		data_LED[POSITION_FRONT_RIGHT_PORT][POSITION_FRONT_RIGHT_ADR] &= ~(1 << POSITION_FRONT_RIGHT_PIN);
		data_LED[POSITION_REAR_LEFT_PORT][POSITION_REAR_LEFT_ADR] &= ~(1 << POSITION_REAR_LEFT_PIN);
		data_LED[POSITION_REAR_RIGHT_PORT][POSITION_REAR_RIGHT_ADR] &= ~(1 << POSITION_REAR_RIGHT_PIN);
	}
	else if(strncmp(buffer,BRIAN_ON,7) == 0)
	{
		data_LED[FOG_FRONT_RIGHT_PORT][FOG_FRONT_RIGHT_ADR] |= (1 << FOG_FRONT_RIGHT_PIN);
		data_LED[FOG_FRONT_LEFT_PORT][FOG_FRONT_LEFT_ADR] |= (1 << FOG_FRONT_LEFT_PIN);
		data_LED[POSITION_FRONT_LEFT_PORT][POSITION_FRONT_LEFT_ADR] |= (1 << POSITION_FRONT_LEFT_PIN);
		data_LED[POSITION_FRONT_RIGHT_PORT][POSITION_FRONT_RIGHT_ADR] |= (1 << POSITION_FRONT_RIGHT_PIN);
		data_LED[POSITION_REAR_LEFT_PORT][POSITION_REAR_LEFT_ADR] |= (1 << POSITION_REAR_LEFT_PIN);
		data_LED[POSITION_REAR_RIGHT_PORT][POSITION_REAR_RIGHT_ADR] |= (1 << POSITION_REAR_RIGHT_PIN);
	}
	else if(strncmp(buffer,BRIAN_OFF,7) == 0)
	{
		data_LED[FOG_FRONT_RIGHT_PORT][FOG_FRONT_RIGHT_ADR] &= ~(1 << FOG_FRONT_RIGHT_PIN);
		data_LED[FOG_FRONT_LEFT_PORT][FOG_FRONT_LEFT_ADR] &= ~(1 << FOG_FRONT_LEFT_PIN);
		data_LED[POSITION_FRONT_LEFT_PORT][POSITION_FRONT_LEFT_ADR] &= ~(1 << POSITION_FRONT_LEFT_PIN);
		data_LED[POSITION_FRONT_RIGHT_PORT][POSITION_FRONT_RIGHT_ADR] &= ~(1 << POSITION_FRONT_RIGHT_PIN);
		data_LED[POSITION_REAR_LEFT_PORT][POSITION_REAR_LEFT_ADR] &= ~(1 << POSITION_REAR_LEFT_PIN);
		data_LED[POSITION_REAR_RIGHT_PORT][POSITION_REAR_RIGHT_ADR] &= ~(1 << POSITION_REAR_RIGHT_PIN);
	}
	else if(strncmp(buffer,FLASHY1_ON,7) == 0)
	{
		flashy1 = true;
	}
	else if(strncmp(buffer,FLASHY1_OFF,7) == 0)
	{
		flashy1 = false;
	}
	else if(strncmp(buffer,FLASHY2_ON,7) == 0)
	{
		flashy2 = true;
	}
	else if(strncmp(buffer,FLASHY2_OFF,7) == 0)
	{
		flashy2 = false;
	}
	else if(strncmp(buffer,FLASHYFADE_ON,8) == 0)
	{
		flashyfade = true;
	}
	else if(strncmp(buffer,FLASHYFADE_OFF,8) == 0)
	{
		flashyfade = false;
	}
	else if (strncmp(buffer,MASTER_RESET,10) == 0)
	{
		//wdt_init();
		while (1)
		{
			//
		}
	}
	else if (strncmp(buffer,MASTER_TEST,10) == 0)
	{
		master_test = true;
	}
}

void update_all_ports()
{

	/*if (flash_all)
	{
		data[1] = 0xFF;
	}
	else
	{
		data[1] = 0x00;
	}*/


	for (int i=0;i<8;i++)
	{
		data_LED[0][i] |= 0x80;
		data_LED[1][i] |= 0x80;
	}

	
	
	mcp23017_set_pins(MCP23017_I2C_ADDR_000,data_LED[0][0],data_LED[1][0]);
	mcp23017_set_pins(MCP23017_I2C_ADDR_001,data_LED[0][1],data_LED[1][1]);
	mcp23017_set_pins(MCP23017_I2C_ADDR_010,data_LED[0][2],data_LED[1][2]);
	mcp23017_set_pins(MCP23017_I2C_ADDR_011,data_LED[0][3],data_LED[1][3]);
	mcp23017_set_pins(MCP23017_I2C_ADDR_100,data_LED[0][4],data_LED[1][4]);
	mcp23017_set_pins(MCP23017_I2C_ADDR_101,data_LED[0][5],data_LED[1][5]);
	mcp23017_set_pins(MCP23017_I2C_ADDR_110,data_LED[0][6],data_LED[1][6]);
	mcp23017_set_pins(MCP23017_I2C_ADDR_111,data_LED[0][7],data_LED[1][7]);
	
	
	/*
	mcp23017_set_pins(MCP23017_I2C_ADDR_000,(uint8_t)data[1],(uint8_t)data[1]);
	mcp23017_set_pins(MCP23017_I2C_ADDR_001,(uint8_t)data[1],(uint8_t)data[1]);
	mcp23017_set_pins(MCP23017_I2C_ADDR_010,(uint8_t)data[1],(uint8_t)data[1]);
	mcp23017_set_pins(MCP23017_I2C_ADDR_011,(uint8_t)data[1],(uint8_t)data[1]);
	mcp23017_set_pins(MCP23017_I2C_ADDR_100,(uint8_t)data[1],(uint8_t)data[1]);
	mcp23017_set_pins(MCP23017_I2C_ADDR_101,(uint8_t)data[1],(uint8_t)data[1]);
	mcp23017_set_pins(MCP23017_I2C_ADDR_110,(uint8_t)data[1],(uint8_t)data[1]);
	mcp23017_set_pins(MCP23017_I2C_ADDR_111,(uint8_t)data[1],(uint8_t)data[1]);*/
	
	/*
	for(int i=0;i<8;i++)
	{
		mcp23017_set_pins(MCP23017_I2C_ADDR_000+i,(uint8_t)data[1],(uint8_t)data[1]);
	}*/
}

void set_blinker(bool state, bool left, bool right)
{
	if (state)
	{
		if (left)
		{
			data_LED[BLINK_LEFT_PORT][BLINK_LEFT_ADR] |= (1 << BLINK_LEFT_PIN);
		}
		if (right)
		{
			data_LED[BLINK_RIGHT_PORT][BLINK_RIGHT_ADR] |= (1 << BLINK_RIGHT_PIN);
		}
	}
	else
	{
		data_LED[BLINK_RIGHT_PORT][BLINK_RIGHT_ADR] &= ~(1 << BLINK_RIGHT_PIN);
		data_LED[BLINK_LEFT_PORT][BLINK_LEFT_ADR] &= ~(1 << BLINK_LEFT_PIN);
	}
}


void party_lights(uint16_t party_vals[])
{
	if (party_vals[0] > party_treshold)
	{
		data_LED[SUB_LEFT_PORT][SUB_LEFT_ADR] |= (1 << SUB_LEFT_PIN);
		data_LED[SUB_RIGHT_PORT][SUB_RIGHT_ADR] |= (1 << SUB_RIGHT_PIN);
		data_LED[REVERSE_RIGHT_PORT][REVERSE_RIGHT_ADR] |= (1 << REVERSE_RIGHT_PIN);
		data_LED[REVERSE_LEFT_PORT][REVERSE_LEFT_ADR] |= (1 << REVERSE_LEFT_PIN);
		data_LED[HIGH_BEAM_LEFT_PORT][HIGH_BEAM_RIGHT_ADR] |= (1 << HIGH_BEAM_RIGHT_PIN);
		data_LED[HIGH_BEAM_LEFT_PORT][HIGH_BEAM_LEFT_ADR] |= (1 << HIGH_BEAM_LEFT_PIN);
	}
	else
	{
		data_LED[SUB_LEFT_PORT][SUB_LEFT_ADR] &= ~(1 << SUB_LEFT_PIN);
		data_LED[SUB_RIGHT_PORT][SUB_RIGHT_ADR] &= ~(1 << SUB_RIGHT_PIN);
		data_LED[REVERSE_RIGHT_PORT][REVERSE_RIGHT_ADR] &= ~(1 << REVERSE_RIGHT_PIN);
		data_LED[REVERSE_LEFT_PORT][REVERSE_LEFT_ADR] &= ~(1 << REVERSE_LEFT_PIN);
		data_LED[HIGH_BEAM_LEFT_PORT][HIGH_BEAM_RIGHT_ADR] &= ~(1 << HIGH_BEAM_RIGHT_PIN);
		data_LED[HIGH_BEAM_LEFT_PORT][HIGH_BEAM_LEFT_ADR] &= ~(1 << HIGH_BEAM_LEFT_PIN);
	}
	if (party_vals[1] > party_treshold)
	{
		data_LED[POSITION_FRONT_RIGHT_PORT][POSITION_FRONT_RIGHT_ADR] |= (1 << POSITION_FRONT_RIGHT_PIN);
		data_LED[POSITION_FRONT_LEFT_PORT][POSITION_FRONT_LEFT_ADR] |= (1 << POSITION_FRONT_LEFT_PIN);
		data_LED[POSITION_REAR_RIGHT_PORT][POSITION_REAR_RIGHT_ADR] |= (1 << POSITION_REAR_RIGHT_PIN);
		data_LED[POSITION_REAR_LEFT_PORT][POSITION_REAR_LEFT_ADR] |= (1 << POSITION_REAR_LEFT_PIN);
	}
	else
	{
		data_LED[POSITION_FRONT_RIGHT_PORT][POSITION_FRONT_RIGHT_ADR] &= ~(1 << POSITION_FRONT_RIGHT_PIN);
		data_LED[POSITION_FRONT_LEFT_PORT][POSITION_FRONT_LEFT_ADR] &= ~(1 << POSITION_FRONT_LEFT_PIN);
		data_LED[POSITION_REAR_RIGHT_PORT][POSITION_REAR_RIGHT_ADR] &= ~(1 << POSITION_REAR_RIGHT_PIN);
		data_LED[POSITION_REAR_LEFT_PORT][POSITION_REAR_LEFT_ADR] &= ~(1 << POSITION_REAR_LEFT_PIN);
	}
	if (party_vals[2] > party_treshold)
	{
		data_LED[LOW_BEAM_LEFT_PORT][LOW_BEAM_RIGHT_ADR] |= (1 << LOW_BEAM_RIGHT_PIN);
		data_LED[LOW_BEAM_LEFT_PORT][LOW_BEAM_LEFT_ADR] |= (1 << LOW_BEAM_LEFT_PIN);
	}
	else
	{
		data_LED[LOW_BEAM_LEFT_PORT][LOW_BEAM_RIGHT_ADR] &= ~(1 << LOW_BEAM_RIGHT_PIN);
		data_LED[LOW_BEAM_LEFT_PORT][LOW_BEAM_LEFT_ADR] &= ~(1 << LOW_BEAM_LEFT_PIN);
	}
	/*if (party_vals[3] > party_treshold)
	{
		data_LED[HIGH_BEAM_LEFT_PORT][HIGH_BEAM_RIGHT_ADR] |= (1 << HIGH_BEAM_RIGHT_PIN);
		data_LED[HIGH_BEAM_LEFT_PORT][HIGH_BEAM_LEFT_ADR] |= (1 << HIGH_BEAM_LEFT_PIN);
	}
	else
	{
		data_LED[HIGH_BEAM_LEFT_PORT][HIGH_BEAM_RIGHT_ADR] &= ~(1 << HIGH_BEAM_RIGHT_PIN);
		data_LED[HIGH_BEAM_LEFT_PORT][HIGH_BEAM_LEFT_ADR] &= ~(1 << HIGH_BEAM_LEFT_PIN);
	}*/
	if (party_vals[4] > party_treshold)
	{
		data_LED[BLINK_RIGHT_PORT][BLINK_RIGHT_ADR] |= (1 << BLINK_RIGHT_PIN);
		data_LED[BLINK_LEFT_PORT][BLINK_LEFT_ADR] |= (1 << BLINK_LEFT_PIN);
	}
	else
	{
		data_LED[BLINK_RIGHT_PORT][BLINK_RIGHT_ADR] &= ~(1 << BLINK_RIGHT_PIN);
		data_LED[BLINK_LEFT_PORT][BLINK_LEFT_ADR] &= ~(1 << BLINK_LEFT_PIN);
	}
	if (party_vals[5] > party_treshold)
	{
		data_LED[FOG_FRONT_LEFT_PORT][FOG_FRONT_LEFT_ADR] |= (1 << FOG_FRONT_LEFT_PIN);
		data_LED[FOG_FRONT_RIGHT_PORT][FOG_FRONT_RIGHT_ADR] |= (1 << FOG_FRONT_RIGHT_PIN);
	}
	else
	{
		data_LED[FOG_FRONT_LEFT_PORT][FOG_FRONT_LEFT_ADR] &= ~(1 << FOG_FRONT_LEFT_PIN);
		data_LED[FOG_FRONT_RIGHT_PORT][FOG_FRONT_RIGHT_ADR] &= ~(1 << FOG_FRONT_RIGHT_PIN);
	}
	/*if (party_vals[6] > party_treshold)
	{
		data_LED[LEDBAR_PORT][LEDBAR_ADR] |= (1 << LEDBAR_PIN);
	}
	else
	{
		data_LED[LEDBAR_PORT][LEDBAR_ADR] &= ~(1 << LEDBAR_PIN);
	}*/
}

void flashy_flash1()
{
	static uint8_t state = 0;
	switch(state)
	{
		case 0:
			reset_all_lights();
			data_LED[HIGH_BEAM_RIGHT_PORT][HIGH_BEAM_RIGHT_ADR] |= (1 << HIGH_BEAM_RIGHT_PIN);
			state++;
			break;
		case 1:
			data_LED[HIGH_BEAM_RIGHT_PORT][HIGH_BEAM_RIGHT_ADR] &= ~(1 << HIGH_BEAM_RIGHT_PIN);
			data_LED[LOW_BEAM_RIGHT_PORT][LOW_BEAM_RIGHT_ADR] |= (1 << LOW_BEAM_RIGHT_PIN);
			state++;
			break;
		case 2:
			data_LED[LOW_BEAM_RIGHT_PORT][LOW_BEAM_RIGHT_ADR] &= ~(1 << LOW_BEAM_RIGHT_PIN);
			data_LED[POSITION_FRONT_RIGHT_PORT][POSITION_FRONT_RIGHT_ADR] |= (1 << POSITION_FRONT_RIGHT_PIN);
			state++;
			break;
		case 3:
			data_LED[POSITION_FRONT_RIGHT_PORT][POSITION_FRONT_RIGHT_ADR] &= ~(1 << POSITION_FRONT_RIGHT_PIN);
			data_LED[POSITION_FRONT_LEFT_PORT][POSITION_FRONT_LEFT_ADR] |= (1 << POSITION_FRONT_LEFT_PIN);
			state++;
			break;
		case 4:
			data_LED[POSITION_FRONT_LEFT_PORT][POSITION_FRONT_LEFT_ADR] &= ~(1 << POSITION_FRONT_LEFT_PIN);
			data_LED[LOW_BEAM_LEFT_PORT][LOW_BEAM_LEFT_ADR] |= (1 << LOW_BEAM_LEFT_PIN);
			state++;
			break;
		case 5:
			data_LED[LOW_BEAM_LEFT_PORT][LOW_BEAM_LEFT_ADR] &= ~(1 << LOW_BEAM_LEFT_PIN);
			data_LED[HIGH_BEAM_LEFT_PORT][HIGH_BEAM_LEFT_ADR] |= (1 << HIGH_BEAM_LEFT_PIN);
			state++;
			break;
		case 6:
			data_LED[HIGH_BEAM_LEFT_PORT][HIGH_BEAM_LEFT_ADR] &= ~(1 << HIGH_BEAM_LEFT_PIN);
			data_LED[BLINK_LEFT_PORT][BLINK_LEFT_ADR] |= (1 << BLINK_LEFT_PIN);
			state++;
			break;
		case 7:
			data_LED[BLINK_LEFT_PORT][BLINK_LEFT_ADR] &= ~(1 << BLINK_LEFT_PIN);
			data_LED[REVERSE_LEFT_PORT][REVERSE_LEFT_ADR] |= (1 << REVERSE_LEFT_PIN);
			state++;
			break;
		case 8:
			data_LED[REVERSE_LEFT_PORT][REVERSE_LEFT_ADR] &= ~(1 << REVERSE_LEFT_PIN);
			data_LED[POSITION_REAR_LEFT_PORT][POSITION_REAR_LEFT_ADR] |= (1 << POSITION_REAR_LEFT_PIN);
			state++;
			break;
		case 9:
			data_LED[POSITION_REAR_LEFT_PORT][POSITION_REAR_LEFT_ADR] &= ~(1 << POSITION_REAR_LEFT_PIN);
			data_LED[REVERSE_RIGHT_PORT][REVERSE_RIGHT_ADR] |= (1 << REVERSE_RIGHT_PIN);
			state++;
			break;
		case 10:
			data_LED[REVERSE_RIGHT_PORT][REVERSE_RIGHT_ADR] &= ~(1 << REVERSE_RIGHT_PIN);
			data_LED[POSITION_REAR_RIGHT_PORT][POSITION_REAR_RIGHT_ADR] |= (1 << POSITION_REAR_RIGHT_PIN);
			state++;
			break;
		case 11:
			data_LED[POSITION_REAR_RIGHT_PORT][POSITION_REAR_RIGHT_ADR] &= ~(1 << POSITION_REAR_RIGHT_PIN);
			data_LED[BLINK_RIGHT_PORT][BLINK_RIGHT_ADR] |= (1 << BLINK_RIGHT_PIN);
			state++;
			break;
		/*case 12:
			data_LED[BLINK_RIGHT_PORT][BLINK_RIGHT_ADR] &= ~(1 << BLINK_RIGHT_PIN);
			data_LED[LEDBAR_PORT][LEDBAR_ADR] |= (1 << LEDBAR_PIN);
			state++;
			break;
		case 13:
			data_LED[LEDBAR_PORT][LEDBAR_ADR] &= ~(1 << LEDBAR_PIN);
			state++;
			break;
		case 14:
			data_LED[LEDBAR_PORT][LEDBAR_ADR] |= (1 << LEDBAR_PIN);
			state++;
			break;
		case 15:
			data_LED[LEDBAR_PORT][LEDBAR_ADR] &= ~(1 << LEDBAR_PIN);
			state++;
			break;
		case 16:
			data_LED[LEDBAR_PORT][LEDBAR_ADR] |= (1 << LEDBAR_PIN);
			state++;
			break;
		case 17:
			data_LED[LEDBAR_PORT][LEDBAR_ADR] &= ~(1 << LEDBAR_PIN);
			state++;
			break;
		case 18:
			data_LED[LEDBAR_PORT][LEDBAR_ADR] |= (1 << LEDBAR_PIN);
			state++;
			break;*/
		case 19:
			reset_all_lights();
			state = 0;
			break;
			
		default:
			reset_all_lights();
			state = 0;
			break;
	}
}

void flashy_flash2()
{
	static uint8_t state = 0;
	switch(state)
	{
		case 0:
			reset_all_lights();
			data_LED[LEDBAR_PORT][LEDBAR_ADR] |= (1 << LEDBAR_PIN);
			state++;
			break;
		case 1:
			data_LED[LEDBAR_PORT][LEDBAR_ADR] &= ~(1 << LEDBAR_PIN);
			state++;
			break;
		case 2:
			data_LED[LEDBAR_PORT][LEDBAR_ADR] |= (1 << LEDBAR_PIN);
			state++;
			break;
		case 3:
			data_LED[LEDBAR_PORT][LEDBAR_ADR] &= ~(1 << LEDBAR_PIN);
			state++;
			break;
		case 4:
			data_LED[LEDBAR_PORT][LEDBAR_ADR] |= (1 << LEDBAR_PIN);
			state++;
			break;
		case 5:
			data_LED[LEDBAR_PORT][LEDBAR_ADR] &= ~(1 << LEDBAR_PIN);
			state++;
			break;
		case 6:
			data_LED[HIGH_BEAM_LEFT_PORT][HIGH_BEAM_LEFT_ADR] |= (1 << HIGH_BEAM_LEFT_PIN);
			data_LED[HIGH_BEAM_RIGHT_PORT][HIGH_BEAM_RIGHT_ADR] |= (1 << HIGH_BEAM_RIGHT_PIN);
			data_LED[REVERSE_LEFT_PORT][REVERSE_LEFT_ADR] |= (1 << REVERSE_LEFT_PIN);
			data_LED[REVERSE_RIGHT_PORT][REVERSE_RIGHT_ADR] |= (1 << REVERSE_RIGHT_PIN);
			state++;
			break;
		case 7:
			data_LED[HIGH_BEAM_LEFT_PORT][HIGH_BEAM_LEFT_ADR] &= ~(1 << HIGH_BEAM_LEFT_PIN);
			data_LED[HIGH_BEAM_RIGHT_PORT][HIGH_BEAM_RIGHT_ADR] &= ~(1 << HIGH_BEAM_RIGHT_PIN);
			data_LED[LOW_BEAM_LEFT_PORT][LOW_BEAM_LEFT_ADR] |= (1 << LOW_BEAM_LEFT_PIN);
			data_LED[LOW_BEAM_RIGHT_PORT][LOW_BEAM_RIGHT_ADR] |= (1 << LOW_BEAM_RIGHT_PIN);
			data_LED[REVERSE_LEFT_PORT][REVERSE_LEFT_ADR] &= ~(1 << REVERSE_LEFT_PIN);
			data_LED[REVERSE_RIGHT_PORT][REVERSE_RIGHT_ADR] &= ~(1 << REVERSE_RIGHT_PIN);
			state++;
			break;
		case 8:
			data_LED[LOW_BEAM_LEFT_PORT][LOW_BEAM_LEFT_ADR] &= ~(1 << LOW_BEAM_LEFT_PIN);
			data_LED[LOW_BEAM_RIGHT_PORT][LOW_BEAM_RIGHT_ADR] &= ~(1 << LOW_BEAM_RIGHT_PIN);
			data_LED[FOG_FRONT_LEFT_PORT][FOG_FRONT_LEFT_ADR] |= (1 << FOG_FRONT_LEFT_PIN);
			data_LED[FOG_FRONT_RIGHT_PORT][FOG_FRONT_RIGHT_ADR] |= (1 << FOG_FRONT_RIGHT_PIN);
			data_LED[POSITION_REAR_LEFT_PORT][POSITION_REAR_LEFT_ADR] |= (1 << POSITION_REAR_LEFT_PIN);
			data_LED[POSITION_REAR_RIGHT_PORT][POSITION_REAR_RIGHT_ADR] |= (1 << POSITION_REAR_RIGHT_PIN);
			state++;
			break;
		case 9:
			data_LED[FOG_FRONT_LEFT_PORT][FOG_FRONT_LEFT_ADR] &= ~(1 << FOG_FRONT_LEFT_PIN);
			data_LED[FOG_FRONT_RIGHT_PORT][FOG_FRONT_RIGHT_ADR] &= ~(1 << FOG_FRONT_RIGHT_PIN);
			data_LED[LOW_BEAM_LEFT_PORT][LOW_BEAM_LEFT_ADR] |= (1 << LOW_BEAM_LEFT_PIN);
			data_LED[LOW_BEAM_RIGHT_PORT][LOW_BEAM_RIGHT_ADR] |= (1 << LOW_BEAM_RIGHT_PIN);
			data_LED[POSITION_REAR_LEFT_PORT][POSITION_REAR_LEFT_ADR] &= ~(1 << POSITION_REAR_LEFT_PIN);
			data_LED[POSITION_REAR_RIGHT_PORT][POSITION_REAR_RIGHT_ADR] &= ~(1 << POSITION_REAR_RIGHT_PIN);
			state++;
			break;
		case 10:
			data_LED[LOW_BEAM_LEFT_PORT][LOW_BEAM_LEFT_ADR] &= ~(1 << LOW_BEAM_LEFT_PIN);
			data_LED[LOW_BEAM_RIGHT_PORT][LOW_BEAM_RIGHT_ADR] &= ~(1 << LOW_BEAM_RIGHT_PIN);
			data_LED[HIGH_BEAM_LEFT_PORT][HIGH_BEAM_LEFT_ADR] |= (1 << HIGH_BEAM_LEFT_PIN);
			data_LED[HIGH_BEAM_RIGHT_PORT][HIGH_BEAM_RIGHT_ADR] |= (1 << HIGH_BEAM_RIGHT_PIN);
			state = 0;
			break;
		default:
			reset_all_lights();
			state = 0;
	}
}

void flashy_fades()
{
	static uint8_t pwm_val = 0;
	static uint8_t duty_cycle = 10;
	
	if (pwm_val > duty_cycle)
	{
		data_LED[POSITION_FRONT_LEFT_PORT][POSITION_FRONT_LEFT_ADR] |= (1 << POSITION_FRONT_LEFT_PIN);
		data_LED[POSITION_FRONT_RIGHT_PORT][POSITION_FRONT_RIGHT_ADR] |= (1 << POSITION_FRONT_RIGHT_PIN);
		data_LED[POSITION_REAR_LEFT_PORT][POSITION_REAR_LEFT_ADR] |= (1 << POSITION_REAR_LEFT_PIN);
		data_LED[POSITION_REAR_RIGHT_PORT][POSITION_REAR_RIGHT_ADR] |= (1 << POSITION_REAR_RIGHT_PIN);
		
		data_LED[LOW_BEAM_RIGHT_PORT][LOW_BEAM_RIGHT_ADR] |= (1 << LOW_BEAM_RIGHT_PIN);
		data_LED[LOW_BEAM_LEFT_PORT][LOW_BEAM_LEFT_ADR] |= (1 << LOW_BEAM_LEFT_PIN);
		
		data_LED[HIGH_BEAM_RIGHT_PORT][HIGH_BEAM_RIGHT_ADR] |= (1 << HIGH_BEAM_RIGHT_PIN);
		data_LED[HIGH_BEAM_LEFT_PORT][HIGH_BEAM_LEFT_ADR] |= (1 << HIGH_BEAM_LEFT_PIN);
		
		data_LED[BLINK_RIGHT_PORT][BLINK_RIGHT_ADR] |= (1 << BLINK_RIGHT_PIN);
		data_LED[BLINK_LEFT_PORT][BLINK_LEFT_ADR] |= (1 << BLINK_LEFT_PIN);
		
		data_LED[REVERSE_LEFT_PORT][REVERSE_LEFT_ADR] |= (1 << REVERSE_LEFT_PIN);
		data_LED[REVERSE_RIGHT_PORT][REVERSE_RIGHT_ADR] |= (1 << REVERSE_RIGHT_PIN);
		
		data_LED[FOG_FRONT_RIGHT_PORT][FOG_FRONT_RIGHT_ADR] |= (1 << FOG_FRONT_RIGHT_PIN);
		data_LED[FOG_FRONT_LEFT_PORT][FOG_FRONT_LEFT_ADR] |= (1 << FOG_FRONT_LEFT_PIN);
	}
	else
	{
		data_LED[POSITION_FRONT_LEFT_PORT][POSITION_FRONT_LEFT_ADR] &= ~(1 << POSITION_FRONT_LEFT_PIN);
		data_LED[POSITION_FRONT_RIGHT_PORT][POSITION_FRONT_RIGHT_ADR] &= ~(1 << POSITION_FRONT_RIGHT_PIN);
		data_LED[POSITION_REAR_LEFT_PORT][POSITION_REAR_LEFT_ADR] &= ~(1 << POSITION_REAR_LEFT_PIN);
		data_LED[POSITION_REAR_RIGHT_PORT][POSITION_REAR_RIGHT_ADR] &= ~(1 << POSITION_REAR_RIGHT_PIN);
		
		data_LED[LOW_BEAM_RIGHT_PORT][LOW_BEAM_RIGHT_ADR] &= ~(1 << LOW_BEAM_RIGHT_PIN);
		data_LED[LOW_BEAM_LEFT_PORT][LOW_BEAM_LEFT_ADR] &= ~(1 << LOW_BEAM_LEFT_PIN);
		
		data_LED[HIGH_BEAM_RIGHT_PORT][HIGH_BEAM_RIGHT_ADR] &= ~(1 << HIGH_BEAM_RIGHT_PIN);
		data_LED[HIGH_BEAM_LEFT_PORT][HIGH_BEAM_LEFT_ADR] &= ~(1 << HIGH_BEAM_LEFT_PIN);
		
		data_LED[BLINK_RIGHT_PORT][BLINK_RIGHT_ADR] &= ~(1 << BLINK_RIGHT_PIN);
		data_LED[BLINK_LEFT_PORT][BLINK_LEFT_ADR] &= ~(1 << BLINK_LEFT_PIN);
		
		data_LED[REVERSE_LEFT_PORT][REVERSE_LEFT_ADR] &= ~(1 << REVERSE_LEFT_PIN);
		data_LED[REVERSE_RIGHT_PORT][REVERSE_RIGHT_ADR] &= ~(1 << REVERSE_RIGHT_PIN);
		
		data_LED[FOG_FRONT_RIGHT_PORT][FOG_FRONT_RIGHT_ADR] &= ~(1 << FOG_FRONT_RIGHT_PIN);
		data_LED[FOG_FRONT_LEFT_PORT][FOG_FRONT_LEFT_ADR] &= ~(1 << FOG_FRONT_LEFT_PIN);
	}
	
	pwm_val++;
	if (pwm_val >= PWM_FREQ)
	{
		pwm_val = 0;
		duty_cycle += 10;
		if (duty_cycle >= PWM_FREQ)
		{
			duty_cycle = 10;
		}
	}
	
}

void reset_all_lights()
{
	for (int i=0;i<8;i++)
	{
		data_LED[0][i] = 0x80;
		data_LED[1][i] = 0x80;
	}
}

bool a_okay()
{
	mcp23017_read_all_ports(read_data);
	
	bool return_val = true;
	for (int i=0;i<8;i++)
	{
		if (mcp23017_data.devices[i].should_be_enabled)
		{
			if ((read_data[0][i] & ~0x80) != (data_LED[0][i] & ~0x80))
			{
				return_val = false;
			}
			if ((read_data[1][i] & ~0x80) != (data_LED[1][i] & ~0x80))
			{
				return_val = false;
			}
		}
	}
	return return_val;
}