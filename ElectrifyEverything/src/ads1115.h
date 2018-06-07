/*
* ads1115.h
*
* Created: 12-12-2017 12:00:05
*  Author: Andreas
*/


#ifndef ADS1115_H_
#define ADS1115_H_

#include "asf.h"

#include "algo.h"




volatile int16_t adc_channels[8];


#define READY_PIN			PIN_PA17A_EIC_EXTINT1
#define READY_PINMUX		PINMUX_PA17A_EIC_EXTINT1
#define READY_EXTINT_LINE	1//PIN_PA17A_EIC_EXTINT_NUM



typedef union{
	struct{
		unsigned int OS :			1;
		unsigned int MUX :			3;
		unsigned int PGA :			3;
		unsigned int MODE :			1;
		unsigned int DR :			3;
		unsigned int COMP_MODE :	1;
		unsigned int COMP_POL :		1;
		unsigned int COMP_LAT :		1;
		unsigned int COMP_QUE :		2;
	};
	uint8_t bytes[2];
} config_data_bytes;

void configure_i2c_master(void);
void ADS1115_set_config(config_data_bytes config);
int16_t ADS1115_get_conv_result(void);
void ADS1115_enable_ready_pin(void);

void ADS1115_configure_extint_channel(void);
void ADS1115_configure_extint_callbacks(void);
void ADS1115_ready_callback(void);

int16_t ADS1115_get_config(void);
int16_t ADS1115_get_high_threshold(void);

#define TIMEOUT 1

#define ADS1115_CHOSEN_ADDR ADS1115_ADDR_1

#define ADS1115_ADDR_0		0b1001000 //ADDR -> GND
#define ADS1115_ADDR_1		0b1001001 //ADDR -> VDD
#define ADS1115_ADDR_2		0b1001010 //ADDR -> SDA
#define ADS1115_ADDR_3		0b1001011 //ADDR -> SCL
#define ADS1115_READ_BiT	0b11111111
#define ADS1115_WRITE_BiT	0b11111110

#define ADS1115_APR_CONV	0b00000000	//Conversion register
#define ADS1115_APR_CONF	0b00000001	//Config register
#define ADS1115_APR_LO_TH	0b00000010	//Low threshold register
#define ADS1115_APR_HI_TH	0b00000011	//High threshold register



#define ADS1115_SS_START	0b1
											//AIN_P		AIN_N
#define ADS1115_MUX_AIN0_AIN1		0b000	//AIN0		AIN1
#define ADS1115_MUX_AIN0_AIN3		0b001	//AIN0		AIN3
#define ADS1115_MUX_AIN1_AIN3		0b010	//AIN1		AIN3
#define ADS1115_MUX_AIN2_AIN3		0b011	//AIN2		AIN3
#define ADS1115_MUX_AIN0_GND		0b100	//AIN0		GND
#define ADS1115_MUX_AIN1_GND		0b101	//AIN1		GND
#define ADS1115_MUX_AIN2_GND		0b110	//AIN2		GND
#define ADS1115_MUX_AIN3_GND		0b111	//AIN3		GND


										//Full Scale Range
#define ADS1115_PGA_6_144_V		0b000	//+-6.144V
#define ADS1115_PGA_4_096_V		0b001	//+-4.096V
#define ADS1115_PGA_2_048_V		0b010	//+-2.048V
#define ADS1115_PGA_1_024_V		0b011	//+-1.024V
#define ADS1115_PGA_0_512_V		0b100	//+-0.512V
#define ADS1115_PGA_0_256_V		0b101	//+-0.256V
//#define ADS1115_PGA_0_256_V		0b110	//+-0.256V
//#define ADS1115_PGA_0_256_V		0b111	//+-0.256V

#define ADS1115_MODE_C		0b0		//Continuous Conversion Mode
#define ADS1115_MODE_SS		0b1		//Single Shot Mode (or Power-Down state)


//Data Rate (Samples per Second)
#define ADS1115_DR_8_SPS		0b000
#define ADS1115_DR_16_SPS		0b001
#define ADS1115_DR_32_SPS		0b010
#define ADS1115_DR_64_SPS		0b011
#define ADS1115_DR_128_SPS		0b100
#define ADS1115_DR_250_SPS		0b101
#define ADS1115_DR_475_SPS		0b110
#define ADS1115_DR_860_SPS		0b111

#define ADS1115_COMP_MODE_TRADITIONAL	0b0	//Traditional comparator (default)
#define ADS1115_COMP_MODE_WIN	0b1	//Window comparator

#define ADS1115_COMP_POL_LOW	0b0	//Active low (default)
#define ADS1115_COMP_POL_HIGH	0b1	//Active high

#define ADS1115_COMP_LAT_DEF	0b0	//Non-latching comparator (default)
#define ADS1115_COMP_LAT_LATCH	0b1	//Latching comparator

#define ADS1115_COMP_QUE_ASSERT_AFTER_1		0b00	//Assert after one conversion
#define ADS1115_COMP_QUE_ASSERT_AFTER_2		0b01	//Assert after two conversions
#define ADS1115_COMP_QUE_ASSERT_AFTER_4		0b10	//Assert after four conversions
#define ADS1115_COMP_QUE_DISABLE			0b11	//Disable comparator and set ALERT_RDY pin to high-impedance (default)

#endif /* ADS1115_H_ */