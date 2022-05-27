/*****************************************************
 *  Module : Common_Macros
 *
 *  File Name: Common_Macros.h
 * 
 *  Author: Helmy
 ****************************************************/ 


#ifndef COMMON_MACROS_H_

#define COMMON_MACROS_H_

	#define F_CPU 16000000UL
	
	#define SIT_BIT(REG,BIT)  (REG|=(1<<BIT))

	#define CLEAR_BIT(REG,BIT)  (REG&=(~(1<<BIT)))

	#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))		

	#define BIT_IS_SET(REG,BIT) (REG&(1<<BIT))		  //return true if bit is set

	#define BIT_IS_CLEAR(REG,BIT) (!(REG&(1<<BIT)))  //return true if bit is clear




#endif /* COMMON_MACROS_H_ */