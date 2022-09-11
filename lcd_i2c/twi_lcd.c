
#include <avr/io.h>
#define F_CPU	8000000UL
#include <util/delay.h>
#include "i2c.h"



#define PCF8574	0x20							//--- Slave Address is 7-Bit and Last Bit is either read or write
#define	WRITE			0
#define READ			1

unsigned char lcd = 0x00;						//--- Declaring a variable as lcd for data operation

/* Function to Write data in PCF8574 */

void PCF8574_write(unsigned char x)
{
	i2c_start();							//--- Start Condition
	i2cWRITE((PCF8574 << 1)| WRITE);	//--- SLA+W is Send 0x40
	i2cWRITE(x);						//--- Data to Slave Device
	i2c_stop();								//--- Stop Condition
}

/* Function to Write 4-bit data to LCD */

void twi_lcd_4bit_send(unsigned char x)
{
	unsigned char temp = 0x00;					//--- temp variable for data operation
	
	lcd &= 0x0F;								//--- Masking last four bit to prevent the RS, RW, EN, Backlight
	temp = (x & 0xF0);							//--- Masking higher 4-Bit of Data and send it LCD
	lcd |= temp;								//--- 4-Bit Data and LCD control Pin
	lcd |= (0x04);								//--- Latching Data to LCD EN = 1
	PCF8574_write(lcd);							//--- Send Data From PCF8574 to LCD PORT
	_delay_us(1);								//--- 1us Delay
	lcd &= ~(0x04);								//--- Latching Complete
	PCF8574_write(lcd);							//--- Send Data From PCF8574 to LCD PORT
	_delay_us(5);								//--- 5us Delay to Complete Latching
	
	
	temp = ((x & 0x0F)<<4);						//--- Masking Lower 4-Bit of Data and send it LCD
	lcd &= 0x0F;								//--- Masking last four bit to prevent the RS, RW, EN, Backlight
	lcd |= temp;								//--- 4-Bit Data and LCD control Pin
	lcd |= (0x04);								//--- Latching Data to LCD EN = 1
	PCF8574_write(lcd);							//--- Send Data From PCF8574 to LCD PORT
	_delay_us(1);								//--- 1us Delay
	lcd &= ~(0x04);								//--- Latching Complete
	PCF8574_write(lcd);							//--- Send Data From PCF8574 to LCD PORT
	_delay_us(5);								//--- 5us Delay to Complete Latching
	
}

/* Function to Write to LCD Command Register */

void twi_lcd_cmd(unsigned char x)
{
	lcd = 0x08;									//--- Enable Backlight Pin
	lcd &= ~(0x01);								//--- Select Command Register By RS = 0
	PCF8574_write(lcd);							//--- Send Data From PCF8574 to LCD PORT
	twi_lcd_4bit_send(x);						//--- Function to Write 4-bit data to LCD
	
}

/* Function to Write to LCD Command Register */

void twi_lcd_dwr(unsigned char x)
{
	lcd |= 0x09;								//--- Enable Backlight Pin & Select Data Register By RS = 1
	PCF8574_write(lcd);							//--- Send Data From PCF8574 to LCD PORT
	twi_lcd_4bit_send(x);						//--- Function to Write 4-bit data to LCD
}

/* Function to Send String of Data */

void twi_lcd_msg(char *c)
{
	while (*c != '\0')							//--- Check Pointer for Null
	twi_lcd_dwr(*c++);							//--- Send the String of Data
}

/* Function to Execute Clear LCD Command */

void twi_lcd_clear()
{
	twi_lcd_cmd(0x01);
}

/* Function to Initialize LCD in 4-Bit Mode, Cursor Setting and Row Selection */

void twi_lcd_init()
{
	lcd = 0x04;						//--- EN = 1 for 25us initialize Sequence
	PCF8574_write(lcd);
	_delay_us(25);
	
	twi_lcd_cmd(0x03);				//--- Initialize Sequence
	twi_lcd_cmd(0x03);				//--- Initialize Sequence
	twi_lcd_cmd(0x03);				//--- Initialize Sequence
	twi_lcd_cmd(0x02);				//--- Return to Home
	twi_lcd_cmd(0x28);				//--- 4-Bit Mode 2 - Row Select
	twi_lcd_cmd(0x0F);				//--- Cursor on, Blinking on
	twi_lcd_cmd(0x01);				//--- Clear LCD
	twi_lcd_cmd(0x06);				//--- Auto increment Cursor
	twi_lcd_cmd(0x80);				//--- Row 1 Column 1 Address

}