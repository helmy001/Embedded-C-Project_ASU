/****************************************************
 *  Module :LCD
 *
 *  File Name :lcd.h
 *
 *  Author: Helmy
 ****************************************************/ 



#ifndef LCD_H_

#define LCD_H_


#include "Common_Macros.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


/************************************************************************/
/*                        PreProcessor Defines                          */
/************************************************************************/

#define Upper_Four_bit_mode

#define LCD_CTRL_PORT PORTB
#define LCD_CTRL_PORT_DIR DDRB

#define LCD_DATA_PORT PORTD
#define LCD_DATA_PORT_DIR DDRD

#define RS 0
#define EN 1
//#define RW 1

/* LCD Commands */

#define CLEAR_COMMAND 0x01
#define FOUR_BITS_DATA_MODE 0x02
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define TWO_LINE_LCD_FOUR_BIT_MODE 0x40
#define CURSOR_FIRST_LINE 0x80
#define SET_CURSOR_LOCATION 0x80
#define CURSOR_SECOND_LINE 0xC0
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E


/************************************************************************/
/*                         Functions Prototypes                         */
/************************************************************************/

void LCD_init(void);
void LCD_sendcommand(unsigned char command);
void LCD_displayCharacter(unsigned char data);
void LCD_DisplayString(char *str);
void LCD_clearScreen();
void LCD_goToRowColumn(unsigned char row,unsigned char col);


#endif /* LCD_H_ */