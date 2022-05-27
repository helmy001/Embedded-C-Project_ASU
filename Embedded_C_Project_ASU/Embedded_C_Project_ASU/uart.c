/****************************************************
 *  Module :Uart
 *
 *  File Name :Uart.c
 *
 *  Author: Helmy
 ****************************************************/ 


#include "uart.h"


void Uart_init()
{
	//Asynchronous USART , No Parity , one stop bit, 8 bit data mode
	UCSR0C=(1<<UCSZ01)|(1<<UCSZ00);
	UCSR0B=(1<<TXEN0)|(1<<RXEN0);
	
	//Enabling Double Speed Operation this bit will reduce the divisor of the baud rate divider from 16 to 8
	UCSR0A=(1<<U2X0);
	
     
	UBRR0L=BAUD_PRESCALE;
	UBRR0H=BAUD_PRESCALE>>8;
	
}

void Uart_SendByte(const unsigned char data)
{
	while(BIT_IS_CLEAR(UCSR0A,UDRE0));
	UDR0=data;
}

unsigned char Uart_ReceiveByte(void){
	while(BIT_IS_CLEAR(UCSR0A,RXC0));
	return UDR0;
}

void Uart_SendString(const unsigned char * str){
	for(unsigned short i=0;str[i]!='\0';i++)
	{
		Uart_SendByte(str[i]);
	}
}

void UART_ReceiveString(unsigned char *Str)
{
	unsigned char i = 0;
	Str[i] = Uart_ReceiveByte();
	while(Str[i] != '\0')
	{
		i++;
		Str[i] = Uart_ReceiveByte();
	}
	Str[i] = '\0';
}


