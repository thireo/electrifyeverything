/*
 * audia6.h
 *
 * Created: 06-02-2018 18:50
 *  Author: Andreas
 */ 

#ifndef AUDIA6_H_
#define AUDIA6_H_

volatile bool flash_all;
volatile bool blink_all;
volatile bool blink_left;
volatile bool blink_right;

volatile bool led_bar;

volatile bool horn0;
volatile bool horn1;
volatile bool horn2;
volatile bool horn3;

volatile bool sound0;
volatile bool sound1;
volatile bool sound2;
volatile bool sound3;
volatile bool sound4;
volatile bool sound5;
volatile bool sound6;
volatile bool sound7;
volatile bool sound8;
volatile bool sound9;

volatile bool party;
volatile bool water;
volatile bool start;

volatile bool master_test;

volatile bool flashy1;
volatile bool flashy2;
volatile bool flashy3;
volatile bool flashyfade;

volatile bool partyrev2;
volatile uint8_t party_band_chosen;

volatile bool valve_open;
volatile bool valve_close;

#endif /* AUDIA6_H_ */