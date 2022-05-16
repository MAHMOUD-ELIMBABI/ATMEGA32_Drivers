/*
 * SPI.c
 *
 *  Created on: May 12, 2022
 *      Author: MahmoudElImbabi
 */

#include"../../Services/Std_types.h"
#include"../../Services/Bit_utils.h"
#include "SPI.h"
#include"SPI_prv.h"

pu8 RecieveDataPtr;
SPI_Cbf Saved_Cbf;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
SPI_enuErrorStatus Spi_vidInit(Spi_cfg_t * Add_pstrSpiCfg) {

	//INTIALIZING LOCAL VARIABLE  OF DATATYPE SPI_enuErrorStatus WITH VALUE SPI_enuOk
	SPI_enuErrorStatus LocErrorStatus = SPI_enuOk;
	//CHECKING ON THE VALUE OF THE Add_pstrSpiCfg POINTER IF EQUAL NULL OR NOT
	if (Add_pstrSpiCfg == NULL) {

		//INTIALIZING LOCAL VARIABLE WITH VALUE  SPI_enuNullPointer
		LocErrorStatus = SPI_enuNullPointer;

	} else {

		//ASSIGNING CONFIGURATION OF THE Add_pstrSpiCfg STRUCT INTO THE CONTROL REGISTER
		SPCR = Add_pstrSpiCfg->SPI_ClkPhase | Add_pstrSpiCfg->SPI_ClkPolarity
				| Add_pstrSpiCfg->SPI_DataOrder
				| (u8) Add_pstrSpiCfg->SPI_FreqOption
				| Add_pstrSpiCfg->SPI_MasterSlaveSelect;

		//ASSIGNING THE DOUBLE SPEED OPTION INTO THE STATUS REGISTER
		SPSR = ((u8) (Add_pstrSpiCfg->SPI_FreqOption >> 8));
	}

	return LocErrorStatus;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
SPI_enuErrorStatus SPI_SendRecieveData(u8 Copy_DataByte, pu8 Add_ReciveData) {

	u16 LocTimeOut = 1000;

	SPI_enuErrorStatus LocErrorStatus = SPI_enuOk;

	SPDR = Copy_DataByte;


	while (!(SPSR & SPI_FLAG_READ) && LocTimeOut--)	;

	if (!(SPSR & SPI_FLAG_READ)) {

		LocErrorStatus = SPI_TimeOut;

	} else {


		*Add_ReciveData = SPDR;

	}

	return LocErrorStatus;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SPI_enuErrorStatus SPI_SendRecieveDataAsync(u8 Copy_DataByte,
		pu8 Add_ReciveData) {
	SPI_enuErrorStatus LocErrorStatus = SPI_enuOk;
	if (Add_ReciveData == NULL) {
		LocErrorStatus = SPI_enuNullPointer;
	} else {
		RecieveDataPtr = Add_ReciveData;
		SPDR = Copy_DataByte;
		SPCR |= SPI_INTERRUPT_EN;
	}

	return LocErrorStatus;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SPI_enuErrorStatus SPI_enuRegisterCbf(SPI_Cbf Add_pfNotification)
{
	SPI_enuErrorStatus LocErrorStatus = SPI_enuOk;
	if (Add_pfNotification == NULL) {
		LocErrorStatus = SPI_enuNullPointer;
	} else {
		Saved_Cbf = Add_pfNotification;
	}

	return LocErrorStatus;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SPI_enuErrorStatus SPI_RecieveData(pu8 Add_ReciveData)
{
	u16 LocTimeOut = 1000;
	SPI_enuErrorStatus LocErrorStatus = SPI_enuOk;
	while (!(SPSR & SPI_FLAG_READ) && LocTimeOut--)
		;
	if (!(SPSR & SPI_FLAG_READ)) {
		LocErrorStatus = SPI_TimeOut;
	} else {

		*Add_ReciveData = SPDR;

	}
	return LocErrorStatus;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SPI_enuErrorStatus SPI_RecieveDataAsync(pu8 Add_ReciveData)
{
	SPI_enuErrorStatus LocErrorStatus = SPI_enuOk;
	if (Add_ReciveData == NULL) {
		LocErrorStatus = SPI_enuNullPointer;
	} else {
		RecieveDataPtr = Add_ReciveData;
		SPCR |= SPI_INTERRUPT_EN;
	}

	return LocErrorStatus;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void __vector_12(void) {
	if(RecieveDataPtr)
	{
		*RecieveDataPtr=SPDR;
	}
	if(Saved_Cbf)
	{
		Saved_Cbf();
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
