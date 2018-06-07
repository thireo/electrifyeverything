/*
 * wdt.h
 *
 * Created: 19-05-2018 23:10:05
 *  Author: Andreas
 */ 


#ifndef WDT_H_
#define WDT_H_

#include "asf.h"

void wdt_init();
void wdt_init_cb();
void wdt_early_cb();



#endif /* WDT_H_ */