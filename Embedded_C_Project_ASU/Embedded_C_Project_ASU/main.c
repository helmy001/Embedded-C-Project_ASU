/****************************************************
 * Embedded_C_Project_ASU.c
 *
 *  File Name :main.c
 *
 *  Author: Helmy
 ****************************************************/
 
#include <avr/interrupt.h>
#include "wifi.h"
#include "lcd.h"
#include "adc.h"
#include "uart.h"


#define Motion_sensor 2
unsigned char IP[16];
unsigned char flag=0;

ISR(TIMER1_COMPA_vect)
{
	Display_Temp();
	
	Display_smoke();
}

ISR(INT0_vect)
{
    Display_Motion();	
}

void Display_Temp()
{
	LCD_clearScreen();
	LCD_goToRowColumn(0,0);
	LCD_DisplayString("Temp:");
	char buff[16];
	itoa(Adc_readChannel(0),buff,10);             /* 10 for decimal */
	LCD_goToRowColumn(0,5);
	LCD_DisplayString(buff);
}


void Display_Motion()
{
	LCD_goToRowColumn(1,0);
	LCD_DisplayString("Motion Detected");
}

void Display_smoke()
{
	LCD_goToRowColumn(0,9);
	char buff[16];
	itoa(Adc_readChannel(1),buff,10);
	LCD_DisplayString(buff);
}

void Timer1_Init()
{
	
	TCNT1=0;									// Set Timer 1 initial value to 0
	TCCR1B=(1<<CS12)|(1<<CS10)|(1<<WGM12);		// Prescaler  Clk/1024
	TIMSK1|=(1<<OCIE1A);						//enable interrupt
	OCR1A=0xFFFF;								//Init the compare register with the number of counts you need , freq_atmega328p= 16mhz .
	
}

void INT0_Init(void)
{
	DDRD&=~(1<<2);					//Motion sensor Pin as Input
	EIMSK|= (1<<INT0);				// Enable external interrupt pin INT0
	EICRA|=(1<<ISC00)|(1<<ISC01);		//with rising edge
}




int main(void)
{
				
	CLEAR_BIT(DDRD,0);				//Rx pin as InPut 
	LCD_init();
	LCD_clearScreen();
	Adc_init();
	Uart_init();
	Wifi_Init("SSID","Password");			//send your WIFI SSID and your Password for esp to Connect 
	Get_Ip(IP);
	Timer1_Init();			//every 3 seconds display temp on lcd timer interrupt
	INT0_Init();			//external interrupt
	sei();					//enable Global Interrupt
    while (1) 
    {
		 
	  Website();
		
	}
    
}

