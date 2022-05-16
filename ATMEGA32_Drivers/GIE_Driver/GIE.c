/*
 * GIE.c
 *
 *  Created on: Apr 6, 2022
 *      Author: MahmoudElImbabi
 */


#include"../../Services/Bit_utils.h"
#include"../../Services/Std_types.h"
#include <avr/io.h>
#include"GIE.h"
#include"GIE_Cnfg.h"
#include"GIE_Prv.h"
//////////////////////////////////////////////////////////////////////////////////////////////////
GIE_tenuErrorStatus GIE_enuGieStatus(u8 Copy_u8Status){

	GIE_tenuErrorStatus LOC_enuReturnStatus =GIE_enuOk;

	if (Copy_u8Status > GIE_u8NUMBER_OF_STATUS) {

		LOC_enuReturnStatus = GIE_enuStatusRangeError;
	}
	else{

		switch(Copy_u8Status){

		case GIE_ENABLE:

			SET_BIT(SREG,GIE_STATUS_BIT);

			break;


		case GIE_DISABLE:

			CLR_BIT(SREG,GIE_STATUS_BIT);

			break;

		}

	}
	return LOC_enuReturnStatus;
}
//////////////////////////////////////////////////////////////////////////////////////////////
