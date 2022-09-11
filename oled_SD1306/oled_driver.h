/*
 * oled_driver.h
 *
 * Author: salma
 */ 


#ifndef OLED_DRIVER_H_
#define OLED_DRIVER_H_
#include "i2c_driver.h"



#define SSD1306_DEFAULT_ADDRESS 0x78 //don't change default address unless you see datasheet (default address for 128 x 64 oled SSD1306)
#define SSD1306_SETCONTRAST 0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON 0xA5
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_DISPLAYON 0xAF
#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS 0xDA
#define SSD1306_SETVCOMDETECT 0xDB
#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 0xD9
#define SSD1306_SETMULTIPLEX 0xA8
#define SSD1306_SETLOWCOLUMN 0x00
#define SSD1306_SETHIGHCOLUMN 0x10
#define SSD1306_SETSTARTLINE 0x40
#define SSD1306_MEMORYMODE 0x20
#define SSD1306_COLUMNADDR 0x21
#define SSD1306_PAGEADDR   0x22
#define SSD1306_COMSCANINC 0xC0
#define SSD1306_COMSCANDEC 0xC8
#define SSD1306_SEGREMAP 0xA0
#define SSD1306_CHARGEPUMP 0x8D
#define SSD1306_SWITCHCAPVCC 0x2
#define SSD1306_NOP 0xE3

#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64
#define SSD1306_BUFFERSIZE (SSD1306_WIDTH*SSD1306_HEIGHT)/8


#define WRITE 1
#define READ 0

void sendCommand(int command);
void invert(int inverted);
void SSD1306_intialize();
void sendFramebuffer(char *buffer);
void drawRectangle(char* buffer, int x1, int y1, int x2, int y2);
void drawVLine(char* buffer, int x, int y, int length);
void drawHLine(char* buffer, int x, int y, int length) ;
void drawPixel(char* buffer, int pos_x, int pos_y) ;

void clear(char* buffer);

void writeLetter(char* buffer, char letter[8][8], int begin_x, int begin_y, int size, int bold); //letter A-Z, a-z, 0-9, !, #, $, %, &, ?
void numberToChar(char* buffer , uint8_t number, int x, int y); //0 -> 99 //ToDo fix
void digitToChar(char* buffer , uint8_t number, int x, int y); //numbers from zero to


#endif /* OLED_DRIVER_H_ */

