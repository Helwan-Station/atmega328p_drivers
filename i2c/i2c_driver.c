
 
/*

		Author: Asmaa, fathy
*/

#include "i2c_driver.h"

void i2c_init()
{
	TWSR=0x00;
	TWBR = BITRATE(TWSR = 0x00);
	TWCR=0X04;				
}

/* Function to Send Start Condition */

void i2c_start()
{
		TWCR|=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
		while (!(TWCR&(1<<TWINT)));

}

/* Function to Send Slave Address for Write operation */

void i2cWRITE(unsigned char data)
{
	TWDR=data;								//--- SLA Address and write instruction
	TWCR=(1<<TWINT)|(1<<TWEN);					//--- Clear TWI interrupt flag,Enable TWI
	while (!(TWCR & (1<<TWINT)));				//--- Wait till complete TWDR int transmitted to Slave

}

/* Function to Send Data to Slave Device  */


/* Function to Send Stop Condition */

void i2c_stop()
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);		//--- Stop Condition as per Datasheet
}


char i2c_readack()
{
	
	TWCR=(1<<TWINT)|(1<<TWEN) | (1 << TWEA);				
	while (!(TWCR & (1<<TWINT)));				
	
	
	return TWDR;
}
