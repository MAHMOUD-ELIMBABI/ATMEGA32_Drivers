/*
 * GIE.h
 *
 *  Created on: Apr 6, 2022
 *      Author: MahmoudElImbabi
 */

#ifndef MCAL_GIE_DRIVER_GIE_H_
#define MCAL_GIE_DRIVER_GIE_H_
//////////////////ERROR STATUS///////////////////////////
typedef enum{

	GIE_enuOk,
	GIE_enuStatusRangeError

}GIE_tenuErrorStatus;
//////////////////////MACROS/////////////////////////////
#define GIE_STATUS_BIT     				7
#define GIE_u8NUMBER_OF_STATUS 			1
////////OPTIONS FOR FUNCTION GIE_enuGieStatus////////////
#define GIE_DISABLE			   				0
#define GIE_ENABLE			   				1
///////////////////PROTOTYPES////////////////////////////
GIE_tenuErrorStatus GIE_enuGieStatus(u8 Copy_u8Status);
/////////////////////////////////////////////////////////
#endif /* MCAL_GIE_DRIVER_GIE_H_ */
