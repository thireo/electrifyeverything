/*
 * sounds.c
 *
 * Created: 22-04-2018 20:24:22
 *  Author: Andreas
 */ 
#include "sounds.h"
#include "uart.h"
#include "string.h"

struct soundboard_tracks
{
	bool is_playing;
	int track_number;
	char *filename;
	char filetype[3];
};

struct adafruit_soundboards
{
	bool started;
	bool is_playing;
	struct soundboard_tracks tracks[11];
};

struct adafruit_soundboards soundboard_instance ={		\
	.started = false,									\
	.is_playing = false,								\
	.tracks[0].filename = "",							\
	.tracks[0].filetype = "   ",						\
	.tracks[0].is_playing = false,						\
	.tracks[0].track_number = 0,						\
	.tracks[1].filename = "",							\
	.tracks[1].filetype = "   ",						\
	.tracks[1].is_playing = false,						\
	.tracks[1].track_number = 1,						\
	.tracks[2].filename = "",							\
	.tracks[2].filetype = "   ",						\
	.tracks[2].is_playing = false,						\
	.tracks[2].track_number = 2,						\
	.tracks[3].filename = "",							\
	.tracks[3].filetype = "   ",						\
	.tracks[3].is_playing = false,						\
	.tracks[3].track_number = 3,						\
	.tracks[4].filename = "",							\
	.tracks[4].filetype = "   ",						\
	.tracks[4].is_playing = false,						\
	.tracks[4].track_number = 4,						\
	.tracks[5].filename = "",							\
	.tracks[5].filetype = "   ",						\
	.tracks[5].is_playing = false,						\
	.tracks[5].track_number = 5,						\
	.tracks[6].filename = "",							\
	.tracks[6].filetype = "   ",						\
	.tracks[6].is_playing = false,						\
	.tracks[6].track_number = 6,						\
	.tracks[0].filename = "",							\
	.tracks[7].filetype = "   ",						\
	.tracks[7].is_playing = false,						\
	.tracks[7].track_number = 7,						\
	.tracks[8].filename = "",							\
	.tracks[8].filetype = "   ",						\
	.tracks[8].is_playing = false,						\
	.tracks[8].track_number = 8,						\
	.tracks[9].filename = "",							\
	.tracks[9].filetype = "   ",						\
	.tracks[9].is_playing = false,						\
	.tracks[9].track_number = 9,						\
	.tracks[10].filename = "",							\
	.tracks[10].filetype = "   ",						\
	.tracks[10].is_playing = false,						\
	.tracks[10].track_number = 10,						\
};

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
	
	
	
	
	/*port_pin_set_config(SB_PIN_BTN00,&config_port_pin);
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
	port_pin_set_output_level(SB_PIN_BTN10,true);*/
	
	config_port_pin.direction = PORT_PIN_PULL_DOWN;
	port_pin_set_config(SB_PIN_UG,&config_port_pin);
	port_pin_set_output_level(SB_PIN_UG,false);
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
	delay_ms(1000);
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

void sb_event_handler(char buffer[])
{
	if (strstr(buffer,"Adafruit FX Sound Board") != NULL)
	{
		sb_reset_buffers();
		sb_uart_write("#03\n");
		//Adafruit Soundboard started.
	}
	if (strstr(buffer,"NoFile") != NULL)
	{
		//The file wasn't found.
	}
	if (strstr(buffer,"done") != NULL)
	{
		//Finished playing track
	}
	if (strstr(buffer,"play") != NULL)
	{
		// strstr(sb_rx_buffer_array,"play") <- returns pointer to..
		//Started playing track
	}
	if (strstr(buffer,"WAV") != NULL || strstr(buffer,"OGG") != NULL)
	{
		int track;
		int no;
		char filename[3];
		sscanf(buffer,"\r\n\rplay\t%d\tT%d     %[^\n]",&track,&no,filename);
		soundboard_instance.tracks[no].is_playing = true;
		//soundboard_instance.tracks[no].filetype = filename;
	}
	
}

void sb_play_track_by_number(int number)
{
	char buffer[8];
	sprintf(buffer,"#%d\n",number);
	sb_uart_write(buffer);
}

void sb_quit(void)
{
	sb_uart_write("q\n");
}


	
