/*
 * uart.c
 *
 * Created: 8/23/2022 8:38:18 PM
 *  Author: mohamed gamal
 */ 
#include "uart.h"
#include <avr/io.h>
#include <avr/delay.h>
#define F_CPU 8000000ul
#define BAUD 9600
#define BAU (F_CPU)/(BAUD*16UL)-1

void uartint(){
	DDRB=0XFF;
	UBRR0H = (BAU>>8);
	UBRR0L= BAU;
	
	UCSR0B|=(1<<TXEN0)|(1<<RXEN0);
	UCSR0C|=(1<<UCSZ00)|(1<<UCSZ01);
	
};
void send(char a){
	while(!(UCSR0A &(1<<UDRE0)));
	UDR0=a;
};
void recive(){
	while(!(UCSR0A &(1<<RXC0)));
	PORTB=UDR0;
};