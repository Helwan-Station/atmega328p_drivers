/*
 * twi_lcd.h
 *
 * Created: 9/2/2022 9:49:07 PM
 *  Author: eng5s
 */ 


#ifndef TWI_LCD_H_
#define TWI_LCD_H_



void PCF8574_write(unsigned char x);
void twi_lcd_4bit_send(unsigned char x);
void twi_lcd_cmd(unsigned char x);
void twi_lcd_dwr(unsigned char x);
void twi_lcd_msg(char *c);
void twi_lcd_clear();
void twi_lcd_init();


#endif /* TWI_LCD_H_ */