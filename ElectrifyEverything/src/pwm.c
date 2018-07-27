
/*
 * pwm.c
 *
 * Created: 14-01-2018 13:48:23
 *  Author: Andreas Thirsbro
 */ 
#include "pwm.h"
#include "mcp23017.h"
#include "cmd.h"
#include "msgeq7.h"
#include "ble_uart.h"
#include "i2c.h"
#include "uart.h"

void pwm_port(void)
{
	pwm_count = 0;
	struct port_config config_port_pin;
	port_get_config_defaults(&config_port_pin);
	config_port_pin.input_pull = PORT_PIN_PULL_NONE;
	config_port_pin.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(PIN_PA02,&config_port_pin);
}

void init_TC3(void)
{	
	PM->APBCMASK.reg |= PM_APBCMASK_TC3;

	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN(0) | GCLK_CLKCTRL_ID_TCC2_TC3;
	
	TC3->COUNT16.CTRLA.reg = TC_CTRLA_MODE_COUNT16 | TC_CTRLA_WAVEGEN_MFRQ |
	TC_CTRLA_PRESCALER_DIV1 | TC_CTRLA_PRESCSYNC_RESYNC;

	TC3->COUNT16.COUNT.reg = 0;
	TC3->COUNT16.CC[0].reg = COMPARE_MATCH;
	
	
	TC3->COUNT16.CTRLA.reg |= TC_CTRLA_ENABLE;
	TC3->COUNT16.DBGCTRL.reg = TC_DBGCTRL_DBGRUN;
	TC3->COUNT16.INTENSET.reg = TC_INTENSET_MC0;
	NVIC_EnableIRQ(TC3_IRQn);
	NVIC_SetPriority(TC3_IRQn,2);
	/*PORT->Group[0].DIRSET.reg=18;
	PORT->Group[0].PINCFG[18].bit.PMUXEN=1;
	PORT->Group[0].PMUX[9].bit.PMUXE = 4;*/
}
int count = 0;

bool pin_state = false;
uint16_t values_bands[6];

bool a_okayish = true;
char buffer[64];
void TC3_Handler()
{
	static bool blink_state = false;
	// Overflow interrupt triggered
	if ( TC3->COUNT16.INTFLAG.bit.OVF == 1 )
	{
		if ((pwm_count % 5) == 0)
		{
			should_update = true;
			should_updates++;
		}
		
		pwm_count++;

		if (pwm_count > PWM_FREQ)
		{
			should_updates = 0;
			/*if ((seconds % 300) == 0)
			{
				execute_order_66 = true;
			}*/
			seconds++;
			if ((seconds % 5) == 0)
			{
				should_check = true;
			}
			//uint8_t *ptr = &read_data[0][0];
			//a_okayish = a_okay(read_data);
			/*set_blinker(blink_state, blink_left,blink_right);
			blink_state = !blink_state;*/
			/*char buffer[64];
			if (party)
			{
				sprintf(buffer,"%d %d %d %d %d %d",values_bands[0],values_bands[1],values_bands[2],values_bands[3],values_bands[4],values_bands[5]);
				ble_uart_write(buffer);
			}*/
			pwm_count = 0;
		}
		TC3->COUNT16.INTFLAG.reg = TC_INTFLAG_MC0;
	}
}

void things_to_do(void)
{
	if (party)
	{
		msgeq7_all_bands(values_bands);
		party_lights(values_bands);
		sprintf(buffer,"%04d %04d %04d %04d %04d %04d\r\n",values_bands[0],values_bands[1],values_bands[2],values_bands[3],values_bands[4],values_bands[5]);
		uart_write(&buffer);
	}
	if ((should_updates % 25) == 0)
	{
		if (flashy1)
		{
			flashy_flash1();
		}
		else if (flashy2)
		{
			flashy_flash2();
		}
		else if (flashy3)
		{
			flashy_flash3();
		}
	}
	if (flashyfade)
	{
		flashy_fades();
	}

	
	/*if (party)
	{
		sprintf(buffer,"%d %d %d %d %d %d\r\n",values_bands[0],values_bands[1],values_bands[2],values_bands[3],values_bands[4],values_bands[5]);
		ble_uart_write(buffer);
	}*/
}
