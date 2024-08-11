
#include "LBIT_math.h"
#include "LSTD_types.h"
#include "timers.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


void Timer0_init()
{
	//ctc mode
	CLR_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);
	//prescalar 256
	CLR_BIT(TCCR0,CS00);
	CLR_BIT(TCCR0,CS01);
	SET_BIT(TCCR0,CS02);
	TCNT0 = 200;   //preload for 100ms
	SET_BIT(TIMSK,TOIE0);  //Timer/Counter0 Overflow interrupt is enabled


}

void Timer2_init()
{
	//ctc mode
	CLR_BIT(TCCR2,WGM20);
	SET_BIT(TCCR2,WGM21);
	//prescalar 256
	CLR_BIT(TCCR2,CS20);
	CLR_BIT(TCCR2,CS21);
	SET_BIT(TCCR2,CS22);
	 TCNT2 = 154; //preload for 200ms
	 SET_BIT(TIMSK,TOIE2);//Timer/Counter2 Overflow interrupt is enabled


}

void Timer1_PWM_init() {
	SET_BIT(DDRD,PIN5);//set pin
	SET_BIT(TCCR1A,COM1A1);//non inverting mode
	SET_BIT(TCCR1A,WGM11);//fast pwm
	SET_BIT(TCCR1B,WGM12);//fast pwm
	SET_BIT(TCCR1B,WGM13);//fast pwm
	//prescaler 64
	SET_BIT(TCCR1B,CS10);
	SET_BIT(TCCR1B,CS11);
	CLR_BIT(TCCR1B,CS12);
	ICR1 = 255;  // TOP



}
