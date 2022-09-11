
/*
		
		Autho: Asmaa, fathy
	
*/


#ifndef I2C_DRIVER_H_					/* Define library H file if not defined */
#define I2C_DRIVER_H_
#include <util/delay.h>							//--- Delay Lib file
#include <util/twi.h>
#define SCL_CLK 400000L							//--- SCL for TWI
#define BITRATE(TWSR)	((F_CPU/SCL_CLK)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1)))))		//--- Bitrate formula

void i2c_init();
void i2cWRITE(unsigned char data);
void i2c_stop();
void i2c_start();

char i2c_readack();






#endif											/* I2C_MASTER_H_FILE_H_ */
