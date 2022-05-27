
#include "sensors.h"


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
	if(BIT_IS_SET(PIND,2))
	{
		LCD_goToRowColumn(1,0);
		LCD_DisplayString("Motion Detected");
	}
}

void Display_smoke()
{
	LCD_goToRowColumn(0,9);
	char buff[16];
	itoa(Adc_readChannel(1),buff,10);
	LCD_DisplayString(buff);
}
