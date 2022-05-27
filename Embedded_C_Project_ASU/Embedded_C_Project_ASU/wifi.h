/****************************************************
 *  Module : Wifi
 *
 *  File Name :wifi.h
 *
 *  Author: Helmy
 ****************************************************/ 


#ifndef WIFI_H_
#define WIFI_H_

#include <stdio.h>
#include "Common_Macros.h"
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"




void Wifi_Init(const unsigned char *ssid,const unsigned char* password);
void Get_Ip();
unsigned char Get_Request_Details();
void Website();
unsigned short GetLength(unsigned char* str);



#endif /* WIFI_H_ */