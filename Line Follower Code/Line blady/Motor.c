/*
 * Motor.c
 *
 * Created: 4/19/2016 12:34:33 PM
 *  Author: Mohamed
 */ 

#define F_CPU 16000000
#include <util/delay.h>
#include <avr/io.h>
#include "Inc.h"

void pwm_init()
{
	
	TCCR0|= (1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<CS02);    //Mode = Fast PWM & PWM Output  = Non Inverted  & Fc = 16M/64 = 250k
	TCCR2|= (1<<WGM20)|(1<<WGM21)|(1<<COM21)|(1<<CS22)|(1<<CS21);    //Mode = Fast PWM & PWM Output  = Non Inverted & Fc = 16M/64 = 250k
	DDRC = 0xff;
	DDRD |= (1<<PD7);	 // OCR2 output
	DDRB |= (1<<PB3);    // OCR0 output
}

/******************************************************************************
void Motor (unsigned char dir1, unsigned char duty1, unsigned char duty2)
{
	
	
	if(dir1 == 'F')
	{
		PORTC = 0b00010001;
	}
	else if(dir1=='L')
	{
		PORTC = 0b00000001;
	}
	else if(dir1 == 'R')
	{
		PORTC = 0b00010000;
	}
	
	//OCR0= duty1;
	//OCR2= duty2;
	
}
*********************************************************************************/
/*void Motor2 (unsigned char dir2, unsigned char duty2)
{
	OCR2= duty2;
	
	if(dir2 == 'f')
	{
		PORTC|=(1<<PC4);  //Forward
		PORTC&=(~(1<<PC5));
	}
	else if (dir2 == 'b')
	{
		PORTC|=(1<<PC5);
		PORTC&=(~(1<<PC4)); // back
	}
	else if (dir2 == 's')
	{
		PORTC&=(~(1<<PC5));
		PORTC&=(~(1<<PC4));
	}
}*/