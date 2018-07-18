/*
 * sounds.c
 *
 * Created: 22-04-2018 20:24:22
 *  Author: Andreas
 */ 
#include "sounds.h"

void sounds_init_pins(void)
{
	struct port_config config_port_pin;
	port_get_config_defaults(&config_port_pin);
	config_port_pin.input_pull = PORT_PIN_PULL_UP;
	config_port_pin.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(SOUNDS_PIN_SS,&config_port_pin);
	//port_pin_set_config(SOUNDS_PIN_SPDT_SEL1,&config_port_pin);
	//port_pin_set_config(SOUNDS_PIN_SPDT_SEL2,&config_port_pin);
	
	port_pin_set_config(SB_PIN_RESET,&config_port_pin);
	port_pin_set_output_level(SB_PIN_RESET,true);
	
	
	
	
	port_pin_set_config(SB_PIN_BTN00,&config_port_pin);
	port_pin_set_output_level(SB_PIN_BTN00,true);
	
	port_pin_set_config(SB_PIN_BTN01,&config_port_pin);
	port_pin_set_output_level(SB_PIN_BTN01,true);
	
	port_pin_set_config(SB_PIN_BTN02,&config_port_pin);
	port_pin_set_output_level(SB_PIN_BTN02,true);
	
	port_pin_set_config(SB_PIN_BTN03,&config_port_pin);
	port_pin_set_output_level(SB_PIN_BTN03,true);
	
	port_pin_set_config(SB_PIN_BTN04,&config_port_pin);
	port_pin_set_output_level(SB_PIN_BTN04,true);
	
	port_pin_set_config(SB_PIN_BTN05,&config_port_pin);
	port_pin_set_output_level(SB_PIN_BTN05,true);
	
	port_pin_set_config(SB_PIN_BTN06,&config_port_pin);
	port_pin_set_output_level(SB_PIN_BTN06,true);
	
	port_pin_set_config(SB_PIN_BTN07,&config_port_pin);
	port_pin_set_output_level(SB_PIN_BTN07,true);
	
	port_pin_set_config(SB_PIN_BTN08,&config_port_pin);
	port_pin_set_output_level(SB_PIN_BTN08,true);
	
	port_pin_set_config(SB_PIN_BTN09,&config_port_pin);
	port_pin_set_output_level(SB_PIN_BTN09,true);
	
	port_pin_set_config(SB_PIN_BTN10,&config_port_pin);
	port_pin_set_output_level(SB_PIN_BTN10,true);
	
	config_port_pin.direction = PORT_PIN_PULL_UP;
	port_pin_set_config(SB_PIN_UG,&config_port_pin);
	port_pin_set_output_level(SB_PIN_UG,true);
}



/*
void select_audio_out(void)
{
	port_pin_set_output_level(SOUNDS_PIN_SS,true);
	port_pin_set_output_level(SOUNDS_PIN_SPDT_SEL2,true);
}
void select_sample(void)
{
	port_pin_set_output_level(SOUNDS_PIN_SS,false);
}

void select_mth(void)
{
	port_pin_set_output_level(SOUNDS_PIN_SPDT_SEL1,true);
	port_pin_set_output_level(SOUNDS_PIN_SPDT_SEL2,false);
}

void select_soundboard(void)
{
	port_pin_set_output_level(SOUNDS_PIN_SPDT_SEL1,false);
	port_pin_set_output_level(SOUNDS_PIN_SPDT_SEL2,false);
}*/

void press_sb_btn_once(uint8_t btn)
{
	//sounds_reset();
	/*for (int i=0;i<11;i++)
	{
		if (i+11 == btn)
		{*/
			port_pin_set_output_level(btn,false);
		/*}
		else
		{
			port_pin_set_output_level(i+11,true);
		}
	}*/
	delay_ms(150);
	port_pin_set_output_level(btn,true);
}

void press_sb_btn(uint8_t btn)
{
	port_pin_set_output_level(btn,false);
}

void release_sb_btn(uint8_t btn)
{
	port_pin_set_output_level(btn,true);
}

void press_mth_btn(uint8_t btn)
{
	uint8_t porta = (uint8_t) (1<<btn);
	porta |= 1 << MTH_EN;
	mcp23017_set_pins(MTH_ADDR,porta,0x00);
}

void release_mth_btn(uint8_t btn)
{
	mcp23017_set_pins(MTH_ADDR,0x00,0x00);
}

void sounds_reset(void)
{
	port_pin_set_output_level(SB_PIN_RESET,false);
	delay_ms(50);
	port_pin_set_output_level(SB_PIN_RESET,true);
	release_sb_btn(SB_PIN_BTN00);
	release_sb_btn(SB_PIN_BTN01);
	release_sb_btn(SB_PIN_BTN02);
	release_sb_btn(SB_PIN_BTN03);
	release_sb_btn(SB_PIN_BTN04);
	release_sb_btn(SB_PIN_BTN05);
	release_sb_btn(SB_PIN_BTN06);
	release_sb_btn(SB_PIN_BTN07);
	release_sb_btn(SB_PIN_BTN08);
	release_sb_btn(SB_PIN_BTN09);
	release_sb_btn(SB_PIN_BTN10);
	delay_ms(150);

}