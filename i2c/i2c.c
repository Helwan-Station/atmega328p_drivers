/*
 * i2c.c
 *
 * Created: 9/1/2022 3:45:32 PM
 *  Author: DELL
 */
#include "i2c.h"

void i2cint(void){
	TWSR=0x00;
	TWBR=BITRATE(TWSR = 0x00);
	TWCR=0X04;
}

void i2cstart(void){
	TWCR|=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!(TWCR&(1<<TWINT)));
}

void I2CWRITE(unsigned char data){
	TWDR=data;
	TWCR=(1<TWINT) | (1<<TWEN);
	while((TWCR & (1<<TWINT))==0);
	
}
unsigned char i2cread(unsigned char islast){
	if (islast==0)
	{
		TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	}
	else{
		TWCR=(1<<TWINT)|(1<<TWEN);
		while((TWCR&(1<<TWINT))==0);
		return TWDR;
	}
}
void i2cstop(){
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}
void i2cintslave(unsigned char slaveaddr){
	TWCR=0x04;
	TWAR=BITRATE(TWSR = 0x00);
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);
}
void i2csend(unsigned char date){
	TWDR=date;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while((TWCR&(1<<TWINT)==0));
}
unsigned char I2CRECEIVE(unsigned char iamlast){
	if (iamlast==0)
	{
		TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	}
	else{
		TWCR=(1<<TWCR)|(1<<TWEN);
	}
	while((TWCR&(1<<TWINT)==0));
	return(TWDR);
	};
	
void i2clisten(){
	while((TWCR&(1<<TWINT)==0));}
	