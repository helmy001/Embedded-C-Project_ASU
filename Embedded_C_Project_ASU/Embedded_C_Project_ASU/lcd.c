/****************************************************
 *  Module :LCD
 *
 *  File Name :lcd.c
 *
 *  Author: Helmy
 ****************************************************/ 


#include "lcd.h"



/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void LCD_init(void)
{
	LCD_CTRL_PORT_DIR|=(1<<RS)|(1<<EN);       //configure control pins as output
	LCD_DATA_PORT_DIR=0xf0;							 //configure data Port as output
	LCD_sendcommand(FOUR_BITS_DATA_MODE);
	LCD_sendcommand(TWO_LINE_LCD_FOUR_BIT_MODE);		
	LCD_sendcommand(CURSOR_OFF);
	LCD_sendcommand(CLEAR_COMMAND);
	
}


void LCD_sendcommand(unsigned char command)
{
	CLEAR_BIT(LCD_CTRL_PORT,RS);
	_delay_ms(1);
	SIT_BIT(LCD_CTRL_PORT,EN);
	_delay_ms(1);
	
	#ifdef Upper_Four_bit_mode
		LCD_DATA_PORT=(command&0xF0)|(LCD_DATA_PORT&0x0F);
		_delay_ms(1);
		CLEAR_BIT(LCD_CTRL_PORT,EN);
		_delay_ms(1);
		SIT_BIT(LCD_CTRL_PORT,EN);
		_delay_ms(1);
		LCD_DATA_PORT=((command&0x0F)<<4)|(LCD_DATA_PORT&0x0F);
	#endif
	
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT,EN);
	_delay_ms(1);
	
	
}


void LCD_displayCharacter(unsigned char data)
{
		SIT_BIT(LCD_CTRL_PORT,RS);
		_delay_ms(1);
		SIT_BIT(LCD_CTRL_PORT,EN);
		_delay_ms(1);
		
		#ifdef Upper_Four_bit_mode
		LCD_DATA_PORT=(data&0xF0)|(LCD_DATA_PORT&0x0F);
		_delay_ms(1);
		CLEAR_BIT(LCD_CTRL_PORT,EN);
		_delay_ms(1);
		SIT_BIT(LCD_CTRL_PORT,EN);
		_delay_ms(1);
		LCD_DATA_PORT=((data&0x0F)<<4)|(LCD_DATA_PORT&0x0F);
		#endif
		
		_delay_ms(1);
		CLEAR_BIT(LCD_CTRL_PORT,EN);
		_delay_ms(1);
}

void LCD_DisplayString(char *str)
{
		
	for(unsigned short i=0;str[i]!='\0';i++)
		LCD_displayCharacter(str[i]);		
			
}

void LCD_clearScreen()
{
	LCD_sendcommand(CLEAR_COMMAND);
}


void LCD_goToRowColumn(unsigned char row,unsigned char col)
{
	unsigned char Address;
	
	/* first of all calculate the required address */
	switch(row)
	{
		case 0:
				Address=col;
				break;
		case 1:
				Address=col+0x40;
				break;

	}					
	/* to write to a specific address in the LCD 
	 * we need to apply the corresponding command 0b10000000+Address */
	LCD_sendcommand(Address | SET_CURSOR_LOCATION); 
}
