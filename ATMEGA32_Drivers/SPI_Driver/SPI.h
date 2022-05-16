/*
 * SPI.h
 *
 *  Created on: May 12, 2022
 *      Author: MahmoudElImbabi
 */

#ifndef MCAL_SPI_DRIVER_SPI_H_
#define MCAL_SPI_DRIVER_SPI_H_
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//SPI ERROR STATUS ENUM
typedef enum {

	SPI_enuOk, SPI_enuNullPointer, SPI_TimeOut,

} SPI_enuErrorStatus;
//-------------------------------------------------------//

//ENUM FOR FREQUENCY OPTION SELECT
typedef enum {

	SPI_FreqDivby_4,
	SPI_FreqDivby_16,
	SPI_FreqDivby_64,
	SPI_FreqDivby_128,
	SPI_FreqDivby_2 = 256,
	SPI_FreqDivby_8,
	SPI_FreqDivby_32,

} Spi_Frequency_Speed;
//-------------------------------------------------------//

//STRUCT FOR CONFIGURATION OF SPI USER MAKE IN APPLICATION//
typedef struct {

	u8 SPI_DataOrder;

	u8 SPI_MasterSlaveSelect;

	u8 SPI_ClkPolarity;

	u8 SPI_ClkPhase;

	Spi_Frequency_Speed SPI_FreqOption;			//ENUM FOR  FREQUENCY OPTIONS SELECT

} Spi_cfg_t;

typedef void (*SPI_Cbf)(void);		//DATATYPE OF FUNCTION ADDRESS (CALLBACK FUNCTION)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define SPI_INTERRUPT_EN   			   0x80		//SPI INTERRUPT ENABLE MASK
#define SPI_DATA_LSB	   			   0x20		//SPI DATA ORDER LEAST SEGNIFCANT BYTE MASK
#define SPI_DATA_MSB	   			   0x00		//SPI DATA ORDER MOST SEGNIFICANT BYTE MASK
#define SPI_MASTER		   			   0x10		//SPI SELECT TO BE MASTER MASK
#define SPI_SLAVE		   			   0x00		//SPI SELECT TO BE SLAVE MASK
#define SPI_CLKPOL_LEAD_RISE		   0x00		//SPI SELECT CLOCK POLARITY TO LEADDING EDGE RISING MASK
#define SPI_CLKPOL_LEAD_FAILLING	   0x08		//SPI SELECT CLOCK POLARITY TO LEADING EDGE FALLING MASK
#define SPI_CLKPHASE_LEAD_SAMPLE	   0x00		//SPI SELECT CLOCK PHASE TO SAMPLING AT LEADING EDGE MASK
#define SPI_CLKPHASE_LEAD_SETUP 	   0x04		//SPI SELECT CLOCK PHASE TO SETUP AT LEADING EDGE MASK

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//SPI INTIALIZING FUNCTION WITH INPUT PARAMETER ADDRESS OF CONFIGURATION STRUCT//
SPI_enuErrorStatus Spi_vidInit(Spi_cfg_t * Add_pstrSpiCfg);

//SPI REGISTER CALLLBACK FUNCTION WITH INPUT PARAMETER POINTER FOR CALLBACK FUNCTION
SPI_enuErrorStatus SPI_enuRegisterCbf(SPI_Cbf Add_pfNotification);

//SPI SEND AND RECIVE DATA FUNCTION WITH TWO INPUT PARAMETER BYTE YOU WANT TO SEND AND POINTER TO DATA YOU WANT TO RECIVE
SPI_enuErrorStatus SPI_SendRecieveData(u8 Copy_DataByte, pu8 Add_ReciveData);


SPI_enuErrorStatus SPI_SendRecieveDataAsync(u8 Copy_DataByte,pu8 Add_ReciveData);

SPI_enuErrorStatus SPI_RecieveData(pu8 Add_ReciveData);

SPI_enuErrorStatus SPI_RecieveDataAsync(pu8 Add_ReciveData);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif /* MCAL_SPI_DRIVER_SPI_H_ */
