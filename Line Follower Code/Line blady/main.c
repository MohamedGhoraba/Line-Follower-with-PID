/*
 * Line blady.c
 *
 * Created: 4/19/2016 12:32:33 PM
 * Author : Mohamed
 */ 
#define  F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include "Inc.h"

float pGain = 212.8902;
float iGain = 630.8826;
float dGain = 17.9598;
int32_t eInteg = 0;
int32_t eprev = 0;
int  delay = 10;
float control;
float s;

float Readsensors()
{
	float avgsensor = 0.0;
	uint8_t sensor1,sensor2,sensor3;
	
	if (PINA == 0b00000110)
	{
		sensor1 = 1;
	}
	else
	{
		sensor1 = 0;
	}
	
	if (PINA == 0b00000101)
	{
		sensor2 = 1;
	}
	else
	{
		sensor2 = 0;
	}
	
	if (PINA == 0b00000011)
	{
		sensor3 = 1;
	}
	else
	{
		sensor3 = 0;
	}

	if (sensor1 == 0 && sensor2 == 0 && sensor3 == 0)
	{
		return 0xFF;
	}
	
	avgsensor = (float) sensor1*1 + sensor2*2 + sensor3*3;
	avgsensor = (float) avgsensor / (sensor1 + sensor2 + sensor3);
	
	return avgsensor;
}

float PID(float cur_value , float req_value)
{
	float pid,error;
	
	error = cur_value - req_value;
	eInteg += error;
	eprev = error;
	pid = (pGain * error) + (iGain * eInteg) + (dGain * (error - eprev));
	
	
	return pid;
}

void DelayMs(uint8_t ms)
{
	uint8_t i;
	for (i=0;i<ms;i++)
	{
		_delay_ms(1);
	}
}

int main(void)
{
	pwm_init();
	DDRA = 0xf8;
	float sprev=0;
	
	while (1) 
    {		
			s = Readsensors();
			
			if (s == 0xFF)
			{
				s = sprev;
			}
			
			control = PID(s , 2.0);
			
			if (control > 200)
			{
				control = 200;
			}
			
			if (control < -200)
			{
				control = -200;
			}
			
			if (control > 0.0)
			{
				if (control > 100)
				{
					PORTC = 0b00100001;
					OCR2 = control - 100;
					OCR0 = 100;
				}
				else
				{
					PORTC = 0b00010001;
					OCR2 = 100 - control;
					OCR0 = 100;
				}
			}
			
			if (control <= 0.0)
			{
				if (control < -100)
				{
					PORTC = 0b00010010;
					OCR0 = -(control + 100);
					OCR2 = 100;
				}
				else
				{
					PORTC = 0b00010001;
					OCR0 = 100 + control;
					OCR2 = 100;
				}
				
			}
			
			DelayMs(delay);
			sprev = s;
		
		/////////////////////////////////////////////////////////
	  /*  if (PINA == 0b00000101)			// forward
		{ 
			PORTC = 0b00010001;
			OCR0 = 80;
			OCR2 = 80;
		}
		else if (PINA == 0b00000011 || PINA == 0b00000001 )	// right
		{
			PORTC = 0b00000001;
			OCR0 = 100;
			
		}
		else if (PINA == 0b00000110 || PINA == 0b00000100)	// left
		{
			PORTC = 0b00010000;
			OCR2 = 100;
			
		}*/
	  ////////////////////////////////////////////////////////////
	  
	}
}

