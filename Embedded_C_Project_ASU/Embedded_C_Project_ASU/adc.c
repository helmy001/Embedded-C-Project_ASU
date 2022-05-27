/****************************************************
 *  Module :ADC
 *
 *  File Name :adc.c
 *
 *  Author: Khaled
 ****************************************************/ 


#include "adc.h"



/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void Adc_init(void)
{
	ADMUX=0;
	ADCSRA|=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}


unsigned short Adc_readChannel(unsigned char Analog_Pin_Number)
{
	ADMUX=(ADMUX&0xE0)|(Analog_Pin_Number&0x07);
	SIT_BIT(ADCSRA,ADSC);	    	//start conversion
	while(BIT_IS_CLEAR(ADCSRA,ADIF));
	SIT_BIT(ADCSRA,ADIF);		   //clear ADIF flag by writing a logical one to it 
	
	return ADC;
	
}


