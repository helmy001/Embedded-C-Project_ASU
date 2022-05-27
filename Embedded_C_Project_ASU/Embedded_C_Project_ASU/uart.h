/****************************************************
 *  Module : Uart
 *
 *  File Name :Uart.h
 *
 *  Author: Helmy
 ****************************************************/ 


#ifndef UART_H_
#define UART_H_

#include "Common_Macros.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU/(BAUDRATE * 8UL)))-1)

/************************************************************************/
/*                         Functions Prototypes                         */
/************************************************************************/
void Uart_SendByte(const unsigned char data);
unsigned char Uart_ReceiveByte();
void Uart_SendString(const unsigned char * str);
void UART_ReceiveString(unsigned char *Str);
void Uart_init();

#endif /* UART_H_ */