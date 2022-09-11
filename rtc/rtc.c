/*
 * rtc.c
 *
 * Author: fathy
 */ 
#include "i2c_driver.h"
#include "oled_driver.h"
#include "rtc.h"


	
	void rtc_setdatetime(fat_c *rtc){
		i2c_start();
		i2cWRITE(WRITEMODE);
		i2cWRITE(secondregadd);
		i2cWRITE(rtc->sec);
		i2cWRITE(rtc->min);
		i2cWRITE(rtc->hour);
i2cWRITE(rtc->weekday);
i2cWRITE(rtc->month);
i2cWRITE(rtc->year);
i2c_stop();
	};
	

	fat_c* rtc_getdatetime(fat_c *rtc){
		i2c_start();
		i2cWRITE(WRITEMODE);

		i2cWRITE(secondregadd);
		
		i2c_start();
		i2cWRITE(READMODE);
		rtc->sec=i2c_readack();
		rtc->min=i2c_readack();
		rtc->hour=i2c_readack();
		rtc->weekday=i2c_readack();
		rtc->data=i2c_readack();
		rtc->month=i2c_readack();
		rtc->year=i2c_readack();
		i2c_stop();
		
		
			return rtc;
	}
	

	
	
