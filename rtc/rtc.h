/*
 * rtc.h
 *
 * Created: 9/4/2022 2:31:50 PM
 *  Author: mohamed gamal
 */
#ifndef RTC_H_
#define RTC_H_
#define F_CPU 8000000ul
#include <avr/delay.h>
#include <avr/io.h>

typedef struct{
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t weekday;
	uint8_t data;
	uint8_t month;
	uint8_t year;
}fat_c;


#define READMODE 0xd1
#define WRITEMODE 0xd0
#define secondregadd 0x00
#define dataregadd 0x04
#include <string.h>
#include <stdio.h>
#include "i2c_driver.h"
#include "oled_driver.h"
void rtc_setdatetime(fat_c *rtc);
fat_c* rtc_getdatetime(fat_c *rtc);


#endif
