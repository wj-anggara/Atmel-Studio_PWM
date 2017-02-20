/*
 * PWM.c
 *
 * Created: 17/02/2017 9:15:11
 * Author : Anggara Wijaya
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int pwmVal=0;

void InitPWM(void)
{
	DDRD |= (1 << PORTD6);
	TCCR0A = (1 << COM0A1) | (1 << WGM00) | (1 << WGM01);
	TIMSK0 = (1 << TOIE0);
	OCR0A = pwmVal;
	sei();
	TCCR0B = (1 << CS00) | (1 << CS02);
}
ISR(TIMER0_OVF_vect)
{
	OCR0A = pwmVal;		//D6
}

int main(void)
{
   InitPWM();
   while(1)
   {
      for(int i=0;i<=255;i++)
      {
         pwmVal=i;
         _delay_ms(5);
	  }
      for(int i=255;i>=0;i--)
      {
         pwmVal=i;
         _delay_ms(5);
      }
   }
}