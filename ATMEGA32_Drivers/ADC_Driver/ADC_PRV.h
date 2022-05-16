/*
 * ADC_PRV.h
 *
 *  Created on: Apr 2, 2022
 *      Author: MahmoudElImbabi
 */

#ifndef MCAL_ADC_DRIVER_ADC_PRV_H_
#define MCAL_ADC_DRIVER_ADC_PRV_H_

#define ADMUX 		*((volatile u8 *)0x27)
#define ADCSRA 		*((volatile u8 *)0x26)
#define ADCH 		*((volatile u8 *)0x25)
#define ADCL 		*((volatile u8 *)0x24)
#define SFIOR 		*((volatile u8 *)0x50)

#define ADC_STARTCONVERSIONPIN			6

#endif /* MCAL_ADC_DRIVER_ADC_PRV_H_ */
