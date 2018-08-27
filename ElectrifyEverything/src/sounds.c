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
	char *filetype;
	int filesize;
};

struct adafruit_soundboards
{
	bool started;
	bool is_playing;
	int number_of_tracks;
	int partition_size; //in 512 byte chunks.
	int currently_playing;
	struct soundboard_tracks tracks[19];
};

struct adafruit_soundboards soundboard_instance ={		\
	.started = false,									\
	.is_playing = false,								\
	.tracks[0].filename = "UNDEFINED FILE",				\
	.tracks[0].filetype = "N/A",						\
	.tracks[0].is_playing = false,						\
	.tracks[0].track_number = 0,						\
	.tracks[0].filesize = 0,							\
	.tracks[1].filename = "UNDEFINED FILE",				\
	.tracks[1].filetype = "N/A",						\
	.tracks[1].is_playing = false,						\
	.tracks[1].track_number = 1,						\
	.tracks[1].filesize = 0,							\
	.tracks[2].filename = "UNDEFINED FILE",				\
	.tracks[2].filetype = "N/A",						\
	.tracks[2].is_playing = false,						\
	.tracks[2].track_number = 2,						\
	.tracks[2].filesize = 0,							\
	.tracks[3].filename = "UNDEFINED FILE",				\
	.tracks[3].filetype = "N/A",						\
	.tracks[3].is_playing = false,						\
	.tracks[3].track_number = 3,						\
	.tracks[3].filesize = 0,							\
	.tracks[4].filename = "UNDEFINED FILE",				\
	.tracks[4].filetype = "N/A",						\
	.tracks[4].is_playing = false,						\
	.tracks[4].track_number = 4,						\
	.tracks[4].filesize = 0,							\
	.tracks[5].filename = "UNDEFINED FILE",				\
	.tracks[5].filetype = "N/A",						\
	.tracks[5].is_playing = false,						\
	.tracks[5].track_number = 5,						\
	.tracks[5].filesize = 0,							\
	.tracks[6].filename = "UNDEFINED FILE",				\
	.tracks[6].filetype = "N/A",						\
	.tracks[6].is_playing = false,						\
	.tracks[6].track_number = 6,						\
	.tracks[6].filesize = 0,							\
	.tracks[7].filename = "UNDEFINED FILE",				\
	.tracks[7].filetype = "N/A",						\
	.tracks[7].is_playing = false,						\
	.tracks[7].track_number = 7,						\
	.tracks[7].filesize = 0,							\
	.tracks[8].filename = "UNDEFINED FILE",				\
	.tracks[8].filetype = "N/A",						\
	.tracks[8].is_playing = false,						\
	.tracks[8].track_number = 8,						\
	.tracks[8].filesize = 0,							\
	.tracks[9].filename = "UNDEFINED FILE",				\
	.tracks[9].filetype = "N/A",						\
	.tracks[9].is_playing = false,						\
	.tracks[9].track_number = 9,						\
	.tracks[9].filesize = 0,							\
	.tracks[10].filename = "UNDEFINED FILE",			\
	.tracks[10].filetype = "N/A",						\
	.tracks[10].is_playing = false,						\
	.tracks[10].track_number = 10,						\
	.tracks[10].filesize = 0,							\
	.tracks[11].filename = "UNDEFINED FILE",			\
	.tracks[11].filetype = "N/A",						\
	.tracks[11].is_playing = false,						\
	.tracks[11].track_number = 11,						\
	.tracks[11].filesize = 0,							\
	.tracks[12].filename = "UNDEFINED FILE",			\
	.tracks[12].filetype = "N/A",						\
	.tracks[12].is_playing = false,						\
	.tracks[12].track_number = 12,						\
	.tracks[12].filesize = 0,							\
	.tracks[13].filename = "UNDEFINED FILE",			\
	.tracks[13].filetype = "N/A",						\
	.tracks[13].is_playing = false,						\
	.tracks[13].track_number = 13,						\
	.tracks[13].filesize = 0,							\
	.tracks[14].filename = "UNDEFINED FILE",			\
	.tracks[14].filetype = "N/A",						\
	.tracks[14].is_playing = false,						\
	.tracks[14].track_number = 14,						\
	.tracks[14].filesize = 0,							\
	.tracks[15].filename = "UNDEFINED FILE",			\
	.tracks[15].filetype = "N/A",						\
	.tracks[15].is_playing = false,						\
	.tracks[15].track_number = 15,						\
	.tracks[15].filesize = 0,							\
	.tracks[16].filename = "UNDEFINED FILE",			\
	.tracks[16].filetype = "N/A",						\
	.tracks[16].is_playing = false,						\
	.tracks[16].track_number = 16,						\
	.tracks[16].filesize = 0,							\
	.tracks[17].filename = "UNDEFINED FILE",			\
	.tracks[17].filetype = "N/A",						\
	.tracks[17].is_playing = false,						\
	.tracks[17].track_number = 17,						\
	.tracks[17].filesize = 0,							\
	.tracks[18].filename = "UNDEFINED FILE",			\
	.tracks[18].filetype = "N/A",						\
	.tracks[18].is_playing = false,						\
	.tracks[18].track_number = 18,						\
	.tracks[18].filesize = 0,							\
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
	//delay_ms(1000);
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
	//delay_ms(150);

}
int temp_track = 0;
char * stringy_pointy;
void sb_event_handler(char buffer[])
{
	if (strstr(buffer,"Adafruit FX Sound Board") != NULL && line_count > 3)
	{
		line_count = 0;
		int files = 0;
		char * string_pointer = strstr(buffer,"Files ");
		sscanf(string_pointer,"Files %d\r\n",&files);
		soundboard_instance.number_of_tracks = files;
		
		string_pointer = strstr(buffer,"FAT ");
		if (string_pointer != NULL)
		{
			int size;
			sscanf(string_pointer,"FAT %x\r\n",&size);
			soundboard_instance.partition_size = size;
		}
		
		sb_reset_buffers();
		delay_ms(500);
		sb_uart_write("L\n");
		//Adafruit Soundboard started.
	}
	if (strstr(buffer,"NoFile") != NULL)
	{
		line_count = 0;
		//The file wasn't found.
	}
	if (strstr(buffer,"done") != NULL)
	{
		line_count = 0;
		soundboard_instance.is_playing = false;
		soundboard_instance.tracks[soundboard_instance.currently_playing].is_playing = false;
		sb_reset_buffers();
	}
	if(strstr(buffer,"play") != NULL && (strstr(buffer,"WAV") != NULL || strstr(buffer,"OGG") != NULL))
	{
		line_count = 0;
		int track;
		int no;
		char filetype[3];
		char filename[8];
		sscanf(buffer,"\r\n\rplay\t%d\tT%d     %3[^\n]",&track,&no,filetype);
		sscanf(buffer,"\r\n\rplay\t%d\t%s     %3[^\n]",&track,filename,filetype);
		soundboard_instance.is_playing = true;
		soundboard_instance.tracks[no].is_playing = true;
		soundboard_instance.currently_playing = no;
		sb_reset_buffers();
	}
	if(strstr(buffer,"play") == NULL && (strstr(buffer,"WAV") != NULL || strstr(buffer,"OGG") != NULL) && (strstr(buffer,"\t\r\n") != NULL))
	{
		if (line_count==soundboard_instance.number_of_tracks+2 && line_count > 0 && soundboard_instance.number_of_tracks > 0)
		{
			line_count = 0;
			char *pointy;
			char tempName[9];
			char tempType[4];
			int tempSize;
			for (int k=0;k<soundboard_instance.number_of_tracks;k++)
			{
				
				pointy = strstr(buffer,"\n");
				pointy += k*25;
				if (pointy != NULL)
				{
					sscanf(pointy,"%8s%3s%d\t",tempName,tempType,&tempSize);
					soundboard_instance.tracks[k].filetype = malloc(4);
					strcpy(soundboard_instance.tracks[k].filetype,tempType);
					soundboard_instance.tracks[k].filename = malloc(9);
					strcpy(soundboard_instance.tracks[k].filename,tempName);
					soundboard_instance.tracks[k].filesize = tempSize;
				}
			}
			soundboard_instance.started = true;
			sb_reset_buffers();
		}
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


	
