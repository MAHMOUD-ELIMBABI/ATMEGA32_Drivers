/*
 * UART.h
 *
 *  Created on: May 14, 2022
 *      Author: MahmoudElImbabi
 */

#ifndef MCAL_UART_DRIVER_UART_H_
#define MCAL_UART_DRIVER_UART_H_
///////////////////////////////////////////////////////////////////////////////////////////////
typedef enum {

	USART_enuOk,
	USART_enuNullError,
	USART_enuBaudRateError,
	USART_enuTimeOut,
	USART_enuBusyError,
	USART_enuInvalidData,

} USART_enuErrorStatus;
//-------------------------------------------------//
typedef struct {

	u8 USART_ModeSelect;
	u8 USART_Transmitter;
	u8 USART_Reciever;
	u8 USART_CharacterSize;
	u8 USART_BaudRate;			//ENTER BUADRATE
	u8 USART_ParityMode;
	u8 USART_StopBitSelect;
	u8 USART_Interrupt;
	u8 USART_ClockPolarity;

} USART_cfg_t;

//-------------------------------------------------//

typedef void (*Usart_Cbf_t)(void);
////////////////////////////////////////////////////////////////////////////////////////////////

//MODESELECT//
#define USART_MODE_ASYNC					0x00
#define USART_MODE_SYNC						0x40

//TRANSMITTER//
#define USART_TRANS_EN						0x08
#define USART_TRANS_DIS						0x00

//RECIVER//
#define USART_RECIV_EN						0x10
#define USART_RECIV_DIS						0x00

//CHARACTER SIZE//
#define USART_CHARSIZE_5BIT					0x00
#define USART_CHARSIZE_6BIT					0x02
#define USART_CHARSIZE_7BIT					0x04
#define USART_CHARSIZE_8BIT					0x06
#define USART_CHARSIZE_9BIT					((u16) 0x0406)

//PARITY MODE//
#define	USART_PARITY_DIS				    0x00
#define	USART_PARITY_EN_EVEN			    0x32
#define	USART_PARITY_EN_ODD				    0x48

//STOPBIT SELECT//
#define USART_STOPBIT_1BIT					0x00
#define USART_STOPBIT_2BIT					0x08

//INTERRUPTS//
#define USART_RXC_INTERRUPT_EN				0x80
#define USART_TXC_INTERRUPT_EN				0x40
#define USART_UDR_INTERRUPT_EN				0x20
#define USART_NOINTERRUPT					0x00

//CLEAR FLAGS//
#define USART_RXC_CLEAR_MASK				0x40
#define USART_TXC_CLEAR_MASK				0x80

//CLOCK POLARITY//
#define USART_TRIS_RFAL						0x00
#define USART_TFAL_RRIS						0x01

////////////////////////////////////////////////////////////////////////////////////////////////
USART_enuErrorStatus USART_enuInit(USART_cfg_t *Add_StructCfg);

USART_enuErrorStatus USART_enuSendData(u8 CopyDataByte);

USART_enuErrorStatus USART_enuReciveData(pu8 AddDataByte);

USART_enuErrorStatus USART_enuSendBuffer(Buffer_t * AddBuffer);

USART_enuErrorStatus USART_TxRegisterCbf(Usart_Cbf_t Usart_Cbf);

USART_enuErrorStatus USART_enuRecieveBuffer(Buffer_t * AddBuffer);

USART_enuErrorStatus USART_RxRegisterCbf(Usart_Cbf_t Usart_Cbf);

///////////////////////////////////////////////////////////////////////////////////////////////
#endif /* MCAL_UART_DRIVER_UART_H_ */
