/*
 * EXTI.c
 *
 *  Created on: Apr 6, 2022
 *      Author: MahmoudElImbabi
 */
/////////////////////////////INCLUDES//////////////////////////////////////
#include"../../Services/Bit_utils.h"
#include"../../Services/Std_types.h"
#include <avr/io.h>
#include"EXTI.h"
#include"EXTI_Cnfg.h"
#include"EXTI_Prv.h"
///////////////////////////////////////////////////////////////////////////
void Exti_vidInit(void){
#if EXTI_PIN==INT0
	SET_BIT(GICR,EXTI_ENABLE_INT0_BIT);

#elif EXTI_PIN==INT1
	SET_BIT(GICR,EXTI_ENABLE_INT1_BIT);

#elif EXTI_PIN==INT2
	SET_BIT(GICR,EXTI_ENABLE_INT2_BIT);
#endif


#if EXTI_MODE==LowLevel && EXTI_PIN==INT0
	CLR_BIT(MCUCR,0);
	CLR_BIT(MCUCR,1);

#elif EXTI_MODE==OnChange &&  EXTI_PIN==INT0

		SET_BIT(MCUCR,0);
		CLR_BIT(MCUCR,1);

	#elif EXTI_MODE==Failling &&  EXTI_PIN==INT0

			CLR_BIT(MCUCR,0);
			SET_BIT(MCUCR,1);

	#elif EXTI_MODE==Rising &&  EXTI_PIN==INT0

				SET_BIT(MCUCR,0);
				SET_BIT(MCUCR,1);


	#endif

#if EXTI_MODE==LowLevel && EXTI_PIN==INT1
	CLR_BIT(MCUCR,2);
	CLR_BIT(MCUCR,3);

#elif EXTI_MODE==OnChange &&  EXTI_PIN==INT1

		SET_BIT(MCUCR,2);
		CLR_BIT(MCUCR,3);

	#elif EXTI_MODE==Failling &&  EXTI_PIN==INT1

			CLR_BIT(MCUCR,2);
			SET_BIT(MCUCR,3);

	#elif EXTI_MODE==Rising &&  EXTI_PIN==INT1

				SET_BIT(MCUCR,2);
				SET_BIT(MCUCR,3);


	#endif

	#if EXTI_MODE==Failling &&  EXTI_PIN==INT2

			CLR_BIT(MCUCSR,6);

	#elif EXTI_MODE==Rising &&  EXTI_PIN==INT2

			SET_BIT(MCUCSR,6);

	#endif

}
////////////////////////////////////////////////////////////////////////////////////////////////


