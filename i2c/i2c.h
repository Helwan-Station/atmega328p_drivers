/*
 * i2c.h
 *
 * Author: fathy, Asmaa
 */ 
#ifndef _i2c_h_ 
#define _i2c_h_
#define F_CPU 8000000ul
#define sclvalu 400000ul
#define BITRATE(TWSR)	((F_CPU/sclvalu)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1)))))		//--- Bitrate formula
#include <avr/delay.h>
#include <avr/io.h>
void i2cstart();
void i2cint();
void I2CWRITE(unsigned char data);
unsigned char i2cread(unsigned char islast);
void i2cstop();
void i2clisten();
unsigned char I2CRECEIVE(unsigned char iamlast);
void i2csend(unsigned char date);
void i2cintslave(unsigned char slaveaddr);
#endif
