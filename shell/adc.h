/*
 * adc.h
 *
 *  Created on: Aug 11, 2024
 *      Author: Mariam
 */

#ifndef ADC_H_
#define ADC_H_

void adc_init(void);
short int read1(u8 channel);
short int read2(u8 channel1);

#endif /* ADC_H_ */
