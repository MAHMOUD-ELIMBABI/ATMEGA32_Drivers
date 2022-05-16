/*
 * ADC.c
 *
 *  Created on: Apr 2, 2022
 *      Author: MahmoudElImbabi
 */

#include "../../Services/Std_types.h"
#include "../../Services/Bit_utils.h"
#include "ADC_PRV.h"
#include "ADC_Cnfg.h"
#include "ADC.h"



void ADC_voidInit(void){

#if   Vref == ADC_AREF_INTERNAL_Vref_TURNED_OFF

	CLR_BIT(ADMUX,6) ;
	CLR_BIT(ADMUX,7) ;

	#elif   Vref == ADC_AVCC

	SET_BIT(ADMUX,6);
	CLR_BIT(ADMUX,7);

	#elif Vref == ADC_INTERNAL_2_56V

	SET_BIT(ADMUX,6);
	SET_BIT(ADMUX,7);

#endif

#if ADJUST == RIGHT_ADJUST

	CLR_BIT(ADMUX,5);

#elif ADJUST == LEFT_ADJUST

	SET_BIT(ADMUX,5);

#endif

#if ADC_CHANNEL >= ADC_CHANNEL_0 && ADC_CHANNEL <= ADC_CHANNEL_7

	 (ADMUX) |= (ADC_CHANNEL);

	#else

		 #warning "wrong ADC Channel"

#endif


#if ADC_Trigger==ADC_SINGLE_CONVERSION
  CLR_BIT(ADCSRA,5);
#elif ADC_Trigger==ADC_FREE_RUNNING_MODE
  SET_BIT(ADCSRA,5);
  CLR_BIT(SFIOR,7); CLR_BIT(SFIOR,6); CLR_BIT(SFIOR,5);
#elif ADC_Trigger==ADC_Analog_Comparator
  SET_BIT(ADCSRA,5);
  CLR_BIT(SFIOR,7); CLR_BIT(SFIOR,6); SET_BIT(SFIOR,5);
#elif ADC_Trigger==ADC_External_Interrupt_Request_0
  SET_BIT(ADCSRA,5);
  CLR_BIT(SFIOR,7); SET_BIT(SFIOR,6); CLR_BIT(SFIOR,5);
#elif ADC_Trigger==ADC_Timer_Counter_0_Compare
  SET_BIT(ADCSRA,5);
  CLR_BIT(SFIOR,7);  SET_BIT(SFIOR,6);  SET_BIT(SFIOR,5);
#elif ADC_Trigger==ADC_Timer_Counter_0_Overflow
  SET_BIT(ADCSRA,5);
  SET_BIT(SFIOR,7);  CLR_BIT(SFIOR,6);  CLR_BIT(SFIOR,5);
#elif ADC_Trigger==ADC_Timer_Counter_Compare_Match_B
  SET_BIT(ADCSRA,5);
  SET_BIT(SFIOR,7);  CLR_BIT(SFIOR,6);  SET_BIT(SFIOR,5);
#elif ADC_Trigger==ADC_Timer_Counter_1_Overflow
  SET_BIT(ADCSRA,5);
  SET_BIT(SFIOR,7);  SET_BIT(SFIOR,6); CLR_BIT(SFIOR,5);
#elif  ADC_Trigger==ADC_Timer_Counter_1_Capture_Event
  SET_BIT(ADCSRA,5);
  SET_BIT(SFIOR,7);  SET_BIT(SFIOR,6);  SET_BIT(SFIOR,5);

  #endif


#if INTERRUPT == ENABLE

  SET_BIT(ADCSRA ,3);

#elif INTERRUPT == DISABLE

  CLR_BIT(ADCSRA ,3);


#endif



#if ADC_Prescaler>=ADC_Prescaler_2 && ADC_Prescaler <=ADC_Prescaler_128
    ADCSRA |= ADC_Prescaler;
#else
      #warning"wrong ADC_Prescaler"

#endif


    SET_BIT(ADCSRA,7);

}

Adc_tenuErrorStatus ADC_enuRead(u8 Copy_u8Pin, pu16 Add_pu16AdcValue)
{
	Adc_tenuErrorStatus Loc_enuReturnStatus = Adc_enuOk;

	if(Add_pu16AdcValue == NULL)
	{
		Loc_enuReturnStatus = Adc_enuNULLPointer;
	}
	else
	{
		u8 Loc_u8Counter = 200;

		ADMUX &= ADC_CLEARPIN;

		ADMUX |= Copy_u8Pin;

		SET_BIT(ADCSRA, ADC_STARTCONVERSIONPIN);

		while((GET_BIT(ADCSRA, ADC_STARTCONVERSIONPIN) == ONE) && (Loc_u8Counter > ZERO))
		{
			Loc_u8Counter--;
		}

		if(Loc_u8Counter == ZERO)
		{
			Loc_enuReturnStatus = Adc_enuNotOk;
		}
		else
		{
			*Add_pu16AdcValue = (u16)ADCL + ((u16)ADCH << EIGHT);

			CLR_BIT(ADCSRA, ADC_INTERRUPTFLAG);

		}

	}

	return Loc_enuReturnStatus;
}

void ADC_Disable(void){
  CLR_BIT(ADCSRA,7);
}

