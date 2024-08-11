/*
 * adc.c
 *
 *  Created on: Aug 11, 2024
 *      Author: Mariam
 */
#include "LBIT_math.h"
#include "LSTD_types.h"
#include "adc.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void adc_init(void)
{

	//for choosing AVCC
CLR_BIT(ADMUX ,REFS1);
SET_BIT(ADMUX,REFS0);

  //for choosing prescalar 128

SET_BIT(ADCSRA,ADPS0);

SET_BIT(ADCSRA,ADPS1);

SET_BIT(ADCSRA,ADPS2);
// to enable adc
SET_BIT(ADCSRA,ADEN );


}
short int read1(u8 channel)
{
	//for choosing adc0
	CLR_BIT(ADMUX,MUX0);

	CLR_BIT(ADMUX,MUX1);

	CLR_BIT(ADMUX,MUX2);

	CLR_BIT(ADMUX,MUX3);

	CLR_BIT(ADMUX,MUX4);
	  // start conversion

	SET_BIT(ADCSRA,ADSC);
//check for conversion finishes
	while(GET_BIT(ADCSRA, ADIF)==0);//if adif==1 then conversion finishes

	SET_BIT(ADCSRA, ADIF);//make sure adif is cleared

	return (ADCW);//adcw is ADCL and ADCH together

}

short int read2(u8 channel1)
{
	//for choosing adc1
	SET_BIT(ADMUX,MUX0);

	CLR_BIT(ADMUX,MUX1);

	CLR_BIT(ADMUX,MUX2);

	CLR_BIT(ADMUX,MUX3);

	CLR_BIT(ADMUX,MUX4);

	SET_BIT(ADCSRA,ADSC);

	while(GET_BIT(ADCSRA, ADIF)==0);

	SET_BIT(ADCSRA, ADIF);

	return (ADCW);

}


