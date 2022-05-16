/*
 * UART.c
 *
 *  Created on: May 14, 2022
 *      Author: MahmoudElImbabi
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////
#include"../../Services/Std_types.h"
#include"../../Services/Bit_utils.h"
#include"../../MCAL/GIE_Driver/GIE.h"
#include"../../MCAL/UART_Driver/UART.h"
#include"../../MCAL/UART_Driver/UART_prv.h"
#include"../../MCAL/UART_Driver/UART_cfg.h"
//////////////////////////////////////////MACROS////////////////////////////////////////////////////////
#define USART_UCSRC_SETBIT_URSEL					0x80

static u8 Rx_u8BusyFlag;
static u8 Tx_u8BusyFlag;

Usart_Cbf_t Saved_RxCbf;
Usart_Cbf_t Saved_TxCbf;

static Buffer_t * Tx_pstrBuffer;
static Buffer_t * Rx_pstrBuffer;
////////////////////////////////////////////////////////////////////////////////////////////////////////
USART_enuErrorStatus USART_enuInit(USART_cfg_t *Add_StructCfg) {

	USART_enuErrorStatus LocErrorStatus = USART_enuOk;

	u16 BAUDRATE;

	if (Add_StructCfg->USART_ModeSelect) {

		BAUDRATE = (u16) (((u32) USART_FREQ
				/ ((u32) 2 * Add_StructCfg->USART_BaudRate)) - 1);

	}

	else {

		BAUDRATE = (u16) (((u32) USART_FREQ
				/ ((u32) 16 * Add_StructCfg->USART_BaudRate)) - 1);

	}
	if (Add_StructCfg == NULL) {

		LocErrorStatus = USART_enuNullError;

	} else if (((u8) (BAUDRATE >> 8) & (0xF0))) {

		LocErrorStatus = USART_enuBaudRateError;

	} else {

		UBRRH = ((u8) (BAUDRATE >> 8));

		UBRRL = ((u8) BAUDRATE);

		UCSRC = Add_StructCfg->USART_ModeSelect
				| Add_StructCfg->USART_ParityMode
				| Add_StructCfg->USART_StopBitSelect
				| Add_StructCfg->USART_CharacterSize
				| Add_StructCfg->USART_ClockPolarity | USART_UCSRC_SETBIT_URSEL;

		UCSRB = Add_StructCfg->USART_Transmitter | Add_StructCfg->USART_Reciever
				| Add_StructCfg->USART_Interrupt
				| ((u8) (Add_StructCfg->USART_CharacterSize) >> 8);

	}

	return LocErrorStatus;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
USART_enuErrorStatus USART_enuSendData(u16 CopyDataByte) {

	USART_enuErrorStatus LocErrorStatus = USART_enuOk;
	u8 LocTimeOut = 1000;
	u8 Temp = 0;

	while (!GET_BIT(UCSRA, 5) && LocTimeOut--)
		;

	if (GET_BIT(UCSRA, 5)) {

		if (CopyDataByte >> 8 & 0xFE) {

			LocErrorStatus = USART_enuInvalidData;

		} else {

			UCSRB |= CopyDataByte >> 8;

			UDR = CopyDataByte;

		}

	} else {

		LocErrorStatus = USART_enuTimeOut;
	}

	return LocErrorStatus;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
USART_enuErrorStatus USART_enuReciveData(pu16 AddDataByte) {

	USART_enuErrorStatus LocErrorStatue = USART_enuOk;
	u8 LocTimeOut = 1000;

	while (!GET_BIT(UCSRA, 7) && LocTimeOut--)
		;
	if ((GET_BIT(UCSRA, 7))) {

		*AddDataByte = ((GET_BIT(UCSRB, 1)) << 8) | UDR;
	} else {
		LocErrorStatue = USART_enuTimeOut;
	}

	return LocErrorStatue;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
USART_enuErrorStatus USART_enuSendBuffer(Buffer_t * AddBuffer) {

	USART_enuErrorStatus LocErrorStatus = USART_enuOk;

	if (AddBuffer == NULL) {

		LocErrorStatus = USART_enuNullError;

	} else if (Tx_u8BusyFlag == 1) {

		LocErrorStatus = USART_enuBusyError;

	} else {
		UCSRA |= USART_TXC_CLEAR_MASK;
		UCSRB &= ~USART_TXC_INTERRUPT_EN;
		Tx_u8BusyFlag = 1;
		Tx_pstrBuffer->Used = 0;
		Tx_pstrBuffer = AddBuffer;
		UDR = Tx_pstrBuffer->Data[Tx_pstrBuffer->Used];
		Tx_pstrBuffer->Used = 1;
		UCSRB |= USART_TXC_INTERRUPT_EN;

	}

	return LocErrorStatus;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
USART_enuErrorStatus USART_TxRegisterCbf(Usart_Cbf_t Usart_Cbf) {
	USART_enuErrorStatus LocErrorStatus = USART_enuOk;
	if (Usart_Cbf == NULL) {

		LocErrorStatus = USART_enuNullError;

	} else {

		Saved_TxCbf = Usart_Cbf;

	}

	return LocErrorStatus;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
USART_enuErrorStatus USART_enuRecieveBuffer(Buffer_t * AddBuffer) {

	USART_enuErrorStatus LocErrorStatus = USART_enuOk;
	if (AddBuffer == NULL) {
		LocErrorStatus = USART_enuNullError;
	} else if (Rx_u8BusyFlag == 1) {
		LocErrorStatus = USART_enuBusyError;
	} else {
		UCSRA |= USART_TXC_CLEAR_MASK;
		UCSRB &= ~USART_RXC_INTERRUPT_EN;
		Rx_u8BusyFlag = 1;
		Rx_pstrBuffer = AddBuffer;
		AddBuffer->Used = 0;
		UCSRB |= USART_RXC_INTERRUPT_EN;
	}

	return LocErrorStatus;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
USART_enuErrorStatus USART_enuRxRegisterCbf(Usart_Cbf_t Usart_Cbf) {
	USART_enuErrorStatus LocErrorStatus = USART_enuOk;
	if (Usart_Cbf == NULL) {

		LocErrorStatus = USART_enuNullError;

	} else {

		Saved_RxCbf = Usart_Cbf;

	}

	return LocErrorStatus;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void __vector_13(void) {
	if (Rx_u8BusyFlag == 1) {
		if (Rx_pstrBuffer->Used < Rx_pstrBuffer->Size) {
			Rx_pstrBuffer->Data[Rx_pstrBuffer->Used++] = UDR;
		} else {
			Rx_u8BusyFlag = 0;
			Rx_pstrBuffer = NULL;
			if (Saved_RxCbf != NULL) {
				Saved_RxCbf();
			}
		}
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void __vector_15(void) {   //ISR FUNCTION

	if (Tx_pstrBuffer->Used < Tx_pstrBuffer->Size) {

		UDR = Tx_pstrBuffer->Data[Tx_pstrBuffer->Used++];

	} else {

		Tx_u8BusyFlag = 0;
		Tx_pstrBuffer = NULL;
		UCSRB &= ~USART_TXC_INTERRUPT_EN;
		Saved_TxCbf();

	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
