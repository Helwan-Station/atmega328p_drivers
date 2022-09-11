/*
 * uart.h
 *
 * Created: 8/23/2022 8:37:54 PM
 *  Author: mohamed gamal
 */ 
#ifndef _uart_h_
#define _uart_h_
#include <avr/io.h>
#include <avr/delay.h>
#define F_CPU 8000000ul
#define BAUD 9600
#define BAU (F_CPU)/(BAUD*16UL)-1
void uartint();
void send(char a);
void recive();
#endif
