/*
 * esp8266_c.c
 *
 * Author: salma
 */ 

#include "esp8266_c.h"
#include "uart.h"

void intialize_esp8266()
{
	
	//intialize UART
	uartint();

	
}

void esp8266_putch(unsigned char bt)
{
	
	//send one char using UART
	send(bt);
}

unsigned char esp8266_getch()
{
	
	//get on char from UART
	recive();
	
}


void esp8266_send_string(char* st_pt)
{
	
	while(*st_pt) //if there is a char
		esp8266_putch(*st_pt++);
		
}

int esp8266_isStarted(void)
{
	
	esp8266_print("AT\r\n");
	return (esp8266_waitResponse() == ESP8266_OK);
	
}

int esp8266_restart(void)
{
	esp8266_print("AT+RST\r\n");
	if(esp8266_waitResponse() != ESP8266_OK)
	{
		
		return 0;
	}
	return (esp8266_waitResponse() == ESP8266_READY);
	
}

void eps8266_echoCMDS(int echo)
{
	
	esp8266_print("ATE");
	if(echo)
	{
		
		esp8266_putch('1');
	}
	else
	{
		
		esp8266_putch('0');
	}
	esp8266_print("\r\n");
	esp8266_print("OK");
}



void esp8266_mode(unsigned char mode)
{
	
	esp8266_print("AT+CWMODE=");
	esp8266_putch(mode + '0');
	esp8266_print("\r\n");
	esp8266_waitResponse();
}


unsigned char esp8266_connect(unsigned char* ssid, unsigned char* pass)
{
	
	esp8266_print("AT+CWJAP=\"");
	esp8266_print(ssid);
	esp8266_print("\", \"");
	esp8266_print(pass);
	esp8266_print("\"\r\n");
	return esp8266_waitResponse();
}

void esp8266_disconnect(void)
{
	
	esp8266_print("AT+CWQAP\r\n");
	esp8266_waitFor("OK");
}

void esp8266_ip(unsigned char* store_in)
{
	
	esp8266_print("AT+CIFSR\r\n");
	unsigned char received;
	
	do{
		received = esp8266_getch();
	}
	while(received <'0' || received > '9');
	
	for(unsigned char i = 0; i < 4; i++)
	{
		
		store_in[i] = 0;
		do 
		{
			store_in[i] = 10*store_in[i] + received - '0';
			received = esp8266_getch();
		} while (received >= '0' && received <= '9');
		received = esp8266_getch();
	}
	
	esp8266_waitFor("OK");
}

int esp8266_start(unsigned char protocol, char* ip, unsigned char port)
{
	
	esp8266_print("AT+CIPSTART=\"");
	if(protocol == ESP8266_TCP)
	{
		
		esp8266_print("TCP");
		
	}
	else
	{
		esp8266_print("UDP");
	}
	esp8266_print("\", \"");
	esp8266_print(ip);
	esp8266_print("\",");
	unsigned char port_str[5] = "\0\0\0\0";
	sprintf(port_str, "%u", port);
	esp8266_print(port_str);
	esp8266_print("\r\n");
	if(esp8266_waitResponse() != ESP8266_OK)
	{
		
		return 0;
	}
	
	if(esp8266_waitResponse() != ESP8266_LINKED)
	{
		return 0;
	}
	
	return 1;
}

int esp8266_send(unsigned char* data)
{
	
	unsigned char length_str[6]  ="\0\0\0\0\0";
	sprintf(length_str, "%u", strlen(data));
	esp8266_print("AT+CIPSEND=");
	esp8266_print(length_str);
	esp8266_print("\r\n");
	while(esp8266_getch() != '>');
	esp8266_print(data);
	
	if(esp8266_waitResponse() == ESP8266_OK)
	{
		
		return 1;
	}
	
	return 0;
}

void esp8266_recieve(unsigned char* store_in, int max_length, int discard_headers)
{
	
	esp8266_waitFor("+IPD");
	int length = 0;
	unsigned char received = esp8266_getch();
	
	do 
	{
		length = length * 10 + received - '0';
		received = esp8266_getch();
	} while (received >= '0' && received <= '9');
	
	if(discard_headers)
	{
		
		length -= esp8266_waitFor("\r\n\r\n");
	}
	
	if(length < max_length)
	{
		
		max_length = length;
	}
	
	int i;
	
	for(i =0 ; i < max_length; i++)
	{
		
		store_in[i] = esp8266_getch();
	}
	
	store_in[i] = 0;
	for(; i < length; i++)
	{
		esp8266_getch();
	}
	
	esp8266_waitFor("OK");
	
}

void esp8266_print(unsigned const char *ptr)
{
	while(*ptr != 0)
	{
		esp8266_putch(*ptr++);
	}
}


inline int esp8266_waitFor(unsigned char* string)
{
	unsigned char so_far = 0;
	unsigned char received;
	int counter = 0;
	
	do 
	{
		received = esp8266_getch();
		counter++;
		if(received == string[so_far])
			{so_far++;}
		else
		{
			so_far = 0;
		}
		
	} while (string[so_far] != 0);
	
	return counter;
}

inline unsigned char esp8266_waitResponse(void) {
	unsigned char so_far[6] = {0,0,0,0,0,0};
	unsigned const char lengths[6] = {2,5,4,9,6,6};
	unsigned const char* strings[6] = {"OK", "ready", "FAIL", "no change", "Linked", "Unlink"};
	unsigned const char responses[6] = {ESP8266_OK, ESP8266_READY, ESP8266_FAIL, ESP8266_NOCHANGE, ESP8266_LINKED, ESP8266_UNLINK};
	unsigned char received;
	unsigned char response;
	int continue_loop = 1;
	while (continue_loop) {
		received = esp8266_getch();
		for (unsigned char i = 0; i < 6; i++) {
			if (strings[i][so_far[i]] == received) {
				so_far[i]++;
				if (so_far[i] == lengths[i]) {
					response = responses[i];
					continue_loop = 0;
				}
				} else {
				so_far[i] = 0;
			}
		}
	}
	return response;
}

unsigned char esp8266_config_softAP(unsigned char* softssid, unsigned char* softpass)
{
	esp8266_print("AT+CWSAP=\"");
	esp8266_print(softssid);
	esp8266_print("\", \"");
	esp8266_print(softpass);
	esp8266_print("\", 5, 3\r\n");
	return esp8266_waitResponse();
}
