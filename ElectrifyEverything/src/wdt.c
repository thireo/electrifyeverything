/*
 * wdt.c
 *
 * Created: 19-05-2018 23:09:49
 *  Author: Andreas
 */ 
#include "wdt.h"

void wdt_init()
{
	struct wdt_conf config_wdt;
	wdt_get_config_defaults(&config_wdt);
	
	config_wdt.always_on = false;
	config_wdt.timeout_period = WDT_PERIOD_4096CLK;
	config_wdt.early_warning_period = WDT_PERIOD_2048CLK;
	
	wdt_set_config(&config_wdt);
	//wdt_init_cb();
}

void wdt_init_cb()
{
	wdt_register_callback(wdt_early_cb,WDT_CALLBACK_EARLY_WARNING);
	wdt_enable_callback(WDT_CALLBACK_EARLY_WARNING);
}

void wdt_early_cb()
{
	//Luke, Bob's your uncle!
}