/*
 * ADC.h
 *
 *  Created on: Apr 2, 2022
 *      Author: MahmoudElImbabi
 */

#ifndef MCAL_ADC_DRIVER_ADC_H_
#define MCAL_ADC_DRIVER_ADC_H_


#include "ADC_Cnfg.h"


typedef enum {

	Adc_enuOk,
	Adc_enuNULLPointer,
	Adc_enuNotOk

}Adc_tenuErrorStatus;

/*options for Vref */
#define ADC_AREF_INTERNAL_Vref_TURNED_OFF			0
#define ADC_AVCC									1
#define ADC_INTERNAL_2_56V							2


/*ADJUSTMENT OPTIONS */

#define LEFT_ADJUST       							0
#define RIGHT_ADJUST								1


/*ANALOG CHANNEL OPTIONS & parameter for function Adc_enuRead*/
#define ADC_CHANNEL_0 								0
#define ADC_CHANNEL_1 								1
#define ADC_CHANNEL_2 								2
#define ADC_CHANNEL_3 								3
#define ADC_CHANNEL_4 								4
#define ADC_CHANNEL_5 								5
#define ADC_CHANNEL_6 								6
#define ADC_CHANNEL_7 								7

/*TRIGGER MODE OPTIONS*/

#define ADC_SINGLE_CONVERSION						0
#define ADC_FREE_RUNNING_MODE						1
#define ADC_Analog_Comparator						2
#define ADC_External_Interrupt_Request_0			3
#define ADC_Timer_Counter_0_Compare					4
#define ADC_Timer_Counter_0_Overflow				5
#define ADC_Timer_Counter_Compare_Match_B			6
#define ADC_Timer_Counter_1_Overflow				7
#define ADC_Timer_Counter_1_Capture_Event			8

/*INTERRUPT OPTIONS */
#define DISABLE 									0
#define ENABLE	 									1

/**/
#define ADC_Prescaler_2								1
#define ADC_Prescaler_4								2
#define ADC_Prescaler_8								3
#define ADC_Prescaler_16							4
#define ADC_Prescaler_32							5
#define ADC_Prescaler_64							6
#define ADC_Prescaler_128							7


#define ZERO										0
#define EIGHT										8
#define ADC_INTERRUPTFLAG							4
#define ONE											1
#define ADC_CLEARPIN                                0xE0



//////////////////////////////PROTOTYPES/////////////////////////////////////////////
void ADC_voidInit(void);
Adc_tenuErrorStatus ADC_enuRead(u8 Copy_u8Pin, pu16 Add_pu16AdcValue);
void ADC_Disable(void);

#endif /* MCAL_ADC_DRIVER_ADC_H_ */
