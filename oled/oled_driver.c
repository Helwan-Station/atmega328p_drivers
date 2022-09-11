/*
 * oled_driver.c
 *
 * Created: 9/3/2022 1:40:37 AM
 *  Author: eng5s
 */ 

#include "oled_driver.h"

void SSD1306_intialize() {
	i2c_init();

	// Turn display off
	sendCommand(SSD1306_DISPLAYOFF);

	sendCommand(SSD1306_SETDISPLAYCLOCKDIV);
	sendCommand(0x80);

	sendCommand(SSD1306_SETMULTIPLEX);
	sendCommand(0x3F);
	
	sendCommand(SSD1306_SETDISPLAYOFFSET);
	sendCommand(0x00);
	
	sendCommand(SSD1306_SETSTARTLINE | 0x00);
	
	// We use internal charge pump
	sendCommand(SSD1306_CHARGEPUMP);
	sendCommand(0x14);
	
	// Horizontal memory mode
	sendCommand(SSD1306_MEMORYMODE);
	sendCommand(0x00);
	
	sendCommand(SSD1306_SEGREMAP | 0x1);

	sendCommand(SSD1306_COMSCANDEC);

	sendCommand(SSD1306_SETCOMPINS);
	sendCommand(0x12);

	// Max contrast
	sendCommand(SSD1306_SETCONTRAST);
	sendCommand(0xCF);

	sendCommand(SSD1306_SETPRECHARGE);
	sendCommand(0xF1);

	sendCommand(SSD1306_SETVCOMDETECT);
	sendCommand(0x40);

	sendCommand(SSD1306_DISPLAYALLON_RESUME);

	// Non-inverted display
	sendCommand(SSD1306_NORMALDISPLAY);

	// Turn display back on
	sendCommand(SSD1306_DISPLAYON);
}


void sendCommand(int command) {
	i2c_start();
	i2cWRITE(SSD1306_DEFAULT_ADDRESS);
	i2cWRITE(0x00);
	i2cWRITE(command);
	i2c_stop();
}



void invert(int inverted) {
	if (inverted) {
		sendCommand(SSD1306_INVERTDISPLAY);
		} else {
		sendCommand(SSD1306_NORMALDISPLAY);
	}
}



void sendFramebuffer(char *buffer) {
	sendCommand(SSD1306_COLUMNADDR);
	sendCommand(0x00);
	sendCommand(0x7F);

	sendCommand(SSD1306_PAGEADDR);
	sendCommand(0x00);
	sendCommand(0x07);

	// We have to send the buffer as 16 bytes packets
	// Our buffer is 1024 bytes long, 1024/16 = 64
	// We have to send 64 packets
	for (int packet = 0; packet < 64; packet++) {
		i2c_start();
		i2cWRITE(SSD1306_DEFAULT_ADDRESS);
		i2cWRITE(0x40);
		for (int packet_byte = 0; packet_byte < 16; ++packet_byte) {
			i2cWRITE(buffer[packet*16+packet_byte]);
		}
		i2c_stop();
	}
	
}



void drawPixel(char* buffer, int pos_x, int pos_y) {
	if (pos_x >= SSD1306_WIDTH || pos_y >= SSD1306_HEIGHT) {
		return;
	}

	buffer[pos_x+(pos_y/8)*SSD1306_WIDTH] |= (1 << (pos_y&7));
}

void drawVLine(char* buffer, int x, int y, int length) {
	for (int i = 0; i < length; ++i) {
		drawPixel(buffer, x, i+y);
	}
}

void drawHLine(char* buffer, int x, int y, int length) {
	for (int i = 0; i < length; ++i) {
		drawPixel(buffer, i+x,y);
	}
}

void drawRectangle(char* buffer, int x1, int y1, int x2, int y2) {
	int length = x2 - x1 + 1;
	int height = y2 - y1;

	drawHLine(buffer, x1,y1,length);
	drawHLine(buffer, x1,y2,length);
	drawVLine(buffer, x1,y1,height);
	drawVLine(buffer, x2,y1,height);
}

void clear(char* buffer) {
	for (int buffer_location = 0; buffer_location < SSD1306_BUFFERSIZE; buffer_location++) {
		buffer[buffer_location] = 0x00;
	}
}

//begin_x, begin_y -> coordindates of first pixel at top left
//size -> 0 (default) or choose sizes from 8 -> 32
//size -> bold (0 "false", 1 "true")  , by adding extra black pixels

void writeLetter(char* buffer, char letter[8][8], int begin_x, int begin_y, int size, int bold) //letter A-Z, a-z, 0-9, !, #, $, %, &, ? 
{
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
			if(letter[i][j] == 1)
				
					drawPixel(buffer, begin_x + j, begin_y+i);

	}
	
}

