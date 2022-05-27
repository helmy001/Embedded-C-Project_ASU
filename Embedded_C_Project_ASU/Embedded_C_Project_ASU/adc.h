/****************************************************
 *  Module :ADC
 *
 *  File Name :adc.h
 *
 *  Author: Helmy
 ****************************************************/ 


#ifndef ADC_H_

#define ADC_H_

#define F_CPU 16000000UL

#include "Common_Macros.h"
#include <avr/io.h>
#include <avr/interrupt.h>


/************************************************************************/
/*                         Functions Prototypes                         */
/************************************************************************/
void Adc_init(void);
unsigned short Adc_readChannel(unsigned char pin_num);



#endif /* ADC_H_ */