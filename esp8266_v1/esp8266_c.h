/*
 * esp8266_c.h
 *
 * Created: 9/4/2022 2:50:15 PM
 *  Author: eng5s
 */ 


#ifndef ESP8266_C_H_
#define ESP8266_C_H_

#define ESP8266_STATION 0x01
#define ESP8266_SOFTAP 0x02

#define ESP8266_TCP 1
#define ESP8266_UDP 0

#define ESP8266_OK 1
#define ESP8266_READY 2
#define ESP8266_FAIL 3
#define ESP8266_NOCHANGE 4
#define ESP8266_LINKED 5
#define ESP8266_UNLINK 6

void intialize_esp8266(void);

//input from user -> output to ESP8266
void esp8266_putch(unsigned char);
unsigned char esp8266_getch(void);

void esp8266_send_string(char* st_pt);

//function prototypes
int esp8266_isStarted(void);  //check if module is started (AT)
int esp8266_restart(void);    //restart module (AT+RST)
void eps8266_echoCMDS(int);  //enable/disable command mode (ATE)


//wifi mode (station / softAP / station+softAP) (AT+CWMODE)
void esp8266_mode(unsigned char);

//connect to AP (AT+CWJAP)
unsigned char esp8266_connect(unsigned char*, unsigned char*);

//disconnect from AP (AT+CWQAP)
void esp8266_disconnect(void);

//local IP (AT+CIFSR)
void esp8266_ip(unsigned char*);

//create connection (AT+CIPSTART)
int esp8266_start(unsigned char protocol, char* ip, unsigned char port);

//send data (AT+CIPSEND)
int esp8266_send(unsigned char*);

//recieve data (+IPD)
void esp8266_recieve(unsigned char*, int , int);

//functions for internal use only
//print a string to the output
void esp8266_print(unsigned const char*);

//wait for a certain string on the input
inline int esp8266_waitFor(unsigned char*);

//wait for any response on the input
inline unsigned char esp8266_waitResponse(void);

unsigned char esp8266_config_softAP(unsigned char* softssid, unsigned char* softpass);

#endif /* ESP8266_C_H_ */