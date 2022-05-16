/*
 * Port.c
 *
 *  Created on: Mar 4, 2022
 *      Author: MahmoudElImbabi
 */

#include"../../Services/Bit_utils.h"     /*INCLUDING "Bit_utlis.h" HEADER FILE */
#include"../../Services/Std_types.h"	 /*INCLUDING "Std_types.h" HEADER FILE */
#include"Port.h"						 /*INCLUDING "Port.h" HEADER FILE */
#include"Port_cfg.h"					 /*INCLUDING "Port_cfg.h" HEADER FILE */
#include"Port_prv.h"					 /*INCLUDING "Port_prv.h" HEADER FILE */
#include <avr/io.h>						 /*INCLUDING "avr/io.h" HEADER FILE */

void Port_vidInit(void)
{
/*
	DDRB=0xFF;
	DDRD=0xFF;
*/
#undef 	PORT_u8INPUT_FLOATING
#define PORT_u8INPUT_FLOATING	0

#undef 	PORT_u8OUTPUT_LOW
#define PORT_u8OUTPUT_LOW		1

#undef 	PORT_u8INPUT_PULLUP
#define PORT_u8INPUT_PULLUP		0

	DDRA = CONC(PORT_u8MODEPIN07,PORT_u8MODEPIN06,PORT_u8MODEPIN05,PORT_u8MODEPIN04,PORT_u8MODEPIN03,PORT_u8MODEPIN02,PORT_u8MODEPIN01,PORT_u8MODEPIN00);
	DDRB = CONC(PORT_u8MODEPIN15,PORT_u8MODEPIN14,PORT_u8MODEPIN13,PORT_u8MODEPIN12,PORT_u8MODEPIN11,PORT_u8MODEPIN10,PORT_u8MODEPIN09,PORT_u8MODEPIN08);
	DDRC = CONC(PORT_u8MODEPIN23,PORT_u8MODEPIN22,PORT_u8MODEPIN21,PORT_u8MODEPIN20,PORT_u8MODEPIN19,PORT_u8MODEPIN18,PORT_u8MODEPIN17,PORT_u8MODEPIN16);
	DDRD = CONC(PORT_u8MODEPIN31,PORT_u8MODEPIN30,PORT_u8MODEPIN29,PORT_u8MODEPIN28,PORT_u8MODEPIN27,PORT_u8MODEPIN26,PORT_u8MODEPIN25,PORT_u8MODEPIN24);

#undef 	PORT_u8INPUT_FLOATING
#define PORT_u8INPUT_FLOATING	0

#undef 	PORT_u8OUTPUT_LOW
#define PORT_u8OUTPUT_LOW		0

#undef 	PORT_u8INPUT_PULLUP
#define PORT_u8INPUT_PULLUP		1

	PORTA = CONC(PORT_u8MODEPIN07,PORT_u8MODEPIN06,PORT_u8MODEPIN05,PORT_u8MODEPIN04,PORT_u8MODEPIN03,PORT_u8MODEPIN02,PORT_u8MODEPIN01,PORT_u8MODEPIN00);
	PORTB = CONC(PORT_u8MODEPIN15,PORT_u8MODEPIN14,PORT_u8MODEPIN13,PORT_u8MODEPIN12,PORT_u8MODEPIN11,PORT_u8MODEPIN10,PORT_u8MODEPIN09,PORT_u8MODEPIN08);
	PORTC = CONC(PORT_u8MODEPIN23,PORT_u8MODEPIN22,PORT_u8MODEPIN21,PORT_u8MODEPIN20,PORT_u8MODEPIN19,PORT_u8MODEPIN18,PORT_u8MODEPIN17,PORT_u8MODEPIN16);
	PORTD = CONC(PORT_u8MODEPIN31,PORT_u8MODEPIN30,PORT_u8MODEPIN29,PORT_u8MODEPIN28,PORT_u8MODEPIN27,PORT_u8MODEPIN26,PORT_u8MODEPIN25,PORT_u8MODEPIN24);

#undef 	PORT_u8INPUT_PULLUP
#undef 	PORT_u8OUTPUT_LOW
#undef 	PORT_u8INPUT_FLOATING

#define PORT_u8OUTPUT_LOW 		0
#define PORT_u8INPUT_FLOATING 	2
#define PORT_u8INPUT_PULLUP 	3

}


/*IMPLEMENTING  "Port_enuSetPinDirection" FUNCTION WITH RETURNING DATATYPE "Port_tenuErrorStatus" and parameters "(u8 Copy_u8PinNum, u8 Copy_u8PinDirection)" */
Port_tenuErrorStatus Port_enuSetPinDirection(u8 Copy_u8PinNum , u8 Copy_u8PinDirection) {

	/* INTIALIZING A VARIABLE CALLED "LOC_enuReturnStatus" OF DATATYPE "Port_tenuErrorStatus" */
	Port_tenuErrorStatus LOC_enuReturnStatus = Port_enuOk;

	/*DECLARING  LOCAL VARIABLE "LOC_u8Port" */
	u8 LOC_u8Port;

	/*DECLARING  LOCAL VARIABLE "LOC_u8Pin" */
	u8 LOC_u8Pin;

	/*CHECK IF "Copy_u8PinNum" IS GREATER THAN  NUMBER OF PINS OR NOT */
	if (Copy_u8PinNum > PORT_u8NUMBER_OF_PINS) {

		/*IF THE CONDITION IS TRUE THEN THE VARIABLE WHICH IS CALLED "LOC_enuReturnStatus " IS EQUAL "Port_enuPinError" */
		LOC_enuReturnStatus = Port_enuPinError;

		/* CHECK IF "Copy_u8PinDirection" IS GREATER THAN  NUMBER OF DIRECTION OR NOT*/
	} else if (Copy_u8PinDirection > PORT_u8NUMBER_OF_DIRECTION) {

		/*IF THE CONDITION IS TRUE THEN THE VARIABLE WHICH IS CALLED "LOC_enuReturnStatus " IS EQUAL "Port_enuDirectionError" */
		LOC_enuReturnStatus = Port_enuDirectionError;

		/* IF THE TWO PERVIOUS CONDITIONS ARE FALSE THEN... */
	} else {

		/* CALCULATE THIS EQUATION TO  DETECT "Copy_u8PinNum" ON WHICH PORT (A,B,C,D)*/
		LOC_u8Port = Copy_u8PinNum / PORT_u8REGISTER_SIZE;

		/*CALCULATE THIS EQUATION TO DETECT "Copy_u8PinNum" ON WHICH PIN (0,1,2,3,4,5,6,7)*/
		LOC_u8Pin = Copy_u8PinNum % PORT_u8REGISTER_SIZE;

		/*SWITCH BETWEEN CASES ACCORDING PORT*/
		switch (LOC_u8Port) {

		/*CASE 0  IF PIN IS ON PORTA*/
		case PORT_u8PORTA:

			/*CHECK IF THE DIRECTION OF THE GIVEN PIN IS OUTPUT OR NOT*/
			if (Copy_u8PinDirection == PORT_u8OUTPUT) {

				/*IF THE CONDITION IS TRUE SET THE DDRA BIT TO BE OUTPUT FOR PIN "LOC_u8Pin" */
				SET_BIT(DDRA, LOC_u8Pin);

			} else {

				/*IF THE CONDITION IS NOT TRUE CLEAR THE DDRA BIT TO BE INPUT FOR PIN "LOC_u8Pin" */
				CLR_BIT(DDRA, LOC_u8Pin);
			}
			break;

			/*CASE 1  IF PIN IS ON PORTB*/
		case PORT_u8PORTB:

			/*CHECK IF THE DIRECTION OF THE GIVEN PIN IS OUTPUT OR NOT*/
			if (Copy_u8PinDirection == PORT_u8OUTPUT) {

				/*IF THE CONDITION IS TRUE SET THE DDRB BIT TO BE OUTPUT FOR PIN "LOC_u8Pin" */
				SET_BIT(DDRB, LOC_u8Pin);

			} else {

				/*IF THE CONDITION IS NOT TRUE CLEAR THE DDRB BIT TO BE INPUT FOR PIN "LOC_u8Pin" */
				CLR_BIT(DDRB, LOC_u8Pin);
			}

			break;
			/*CASE 2  IF PIN IS ON PORTC*/
		case PORT_u8PORTC:

			/*CHECK IF THE DIRECTION OF THE GIVEN PIN IS OUTPUT OR NOT*/
			if (Copy_u8PinDirection == PORT_u8OUTPUT) {

				/*IF THE CONDITION IS TRUE SET THE DDRC BIT TO BE OUTPUT FOR PIN "LOC_u8Pin" */
				SET_BIT(DDRC, LOC_u8Pin);

			} else {

				/*IF THE CONDITION IS NOT TRUE CLEAR THE DDRC BIT TO BE INPUT FOR PIN "LOC_u8Pin" */
				CLR_BIT(DDRC, LOC_u8Pin);

			}

			break;
			/*CASE 3  IF PIN IS ON PORTD*/
		case PORT_u8PORTD:

			/*CHECK IF THE DIRECTION OF THE GIVEN PIN IS OUTPUT OR NOT*/
			if (Copy_u8PinDirection == PORT_u8OUTPUT) {

				/*IF THE CONDITION IS TRUE SET THE DDRD BIT TO BE OUTPUT FOR PIN "LOC_u8Pin" */
				SET_BIT(DDRD, LOC_u8Pin);

			} else {

				/*IF THE CONDITION IS NOT TRUE CLEAR THE DDRD BIT TO BE INPUT FOR PIN "LOC_u8Pin" */
				CLR_BIT(DDRD, LOC_u8Pin);

			}

			break;
		}
	}

	/*RETURN ERROR STATUS*/
	return LOC_enuReturnStatus;
}

/*IMPLEMENTING  "Port_enuSetPinMode" FUNCTION WITH RETURNING DATATYPE "Port_tenuErrorStatus" and parameters "(u8 Copy_u8PinNum, u8 Copy_u8PinDirection)" */
Port_tenuErrorStatus Port_enuSetPinMode(u8 Copy_u8PinNum, u8 Copy_u8PinMode) {

	/* INTIALIZING A VARIABLE CALLED "LOC_enuReturnStatus" OF DATATYPE "Port_tenuErrorStatus" */
	Port_tenuErrorStatus LOC_enuReturnStatus = Port_enuOk;

	/*DECLARING  LOCAL VARIABLE "LOC_u8Port" */
	u8 LOC_u8Port;

	/*DECLARING  LOCAL VARIABLE "LOC_u8Pin" */
	u8 LOC_u8Pin;

	/*CHECK IF "Copy_u8PinNum" IS GREATER THAN  NUMBER OF PINS OR NOT */
	if (Copy_u8PinNum > PORT_u8NUMBER_OF_PINS) {

		/*IF THE CONDITION IS TRUE THEN THE VARIABLE WHICH IS CALLED "LOC_enuReturnStatus " IS EQUAL "Port_enuPinError" */
		LOC_enuReturnStatus = Port_enuPinError;

		/* CHECK IF "Copy_u8PinDirection" IS GREATER THAN  NUMBER OF MODES OR NOT*/
	} else if (Copy_u8PinMode > PORT_u8INPUT_PULLUP) {

		/*IF THE CONDITION IS TRUE THEN THE VARIABLE WHICH IS CALLED "LOC_enuReturnStatus " IS EQUAL "Port_enuDirectionError" */
		LOC_enuReturnStatus = Port_enuDirectionError;

		/* IF THE TWO PERVIOUS CONDITIONS ARE FALSE THEN... */
	} else {

		/* CALCULATE THIS EQUATION TO  DETECT "Copy_u8PinNum" ON WHICH PORT (A,B,C,D)*/
		LOC_u8Port = Copy_u8PinNum / PORT_u8REGISTER_SIZE;

		/*CALCULATE THIS EQUATION TO DETECT "Copy_u8PinNum" ON WHICH PIN (0,1,2,3,4,5,6,7)*/
		LOC_u8Pin = Copy_u8PinNum % PORT_u8REGISTER_SIZE;

		/*SWITCH BETWEEN CASES ACCORDING PORT*/
		switch (LOC_u8Port) {

////////////////////////////////////////////////////////////////

		/*CASE 0  IF PIN IS ON PORTA*/
		case PORT_u8PORTA:
			/* SWITCH BETWEEN PINMODES (PORT_u8OUTPUT_LOW ,  PORT_u8OUTPUT_HIGH , PORT_u8INPUT_FLOATING , PORT_u8INPUT_PULLUP )*/
			switch (Copy_u8PinMode) {
			/*CASE 0 IF PINMODE EQUAL "PORT_u8OUTPUT_LOW" */
			case PORT_u8OUTPUT_LOW:
/* SET PIN */
				SET_BIT(DDRA, LOC_u8Pin);

				CLR_BIT(PORTA, LOC_u8Pin);

				break;

			case PORT_u8OUTPUT_HIGH:

				SET_BIT(DDRA, LOC_u8Pin);

				SET_BIT(PORTA, LOC_u8Pin);

				break;

			case PORT_u8INPUT_FLOATING:

				CLR_BIT(DDRA, LOC_u8Pin);

				CLR_BIT(PORTA, LOC_u8Pin);

				break;

			case PORT_u8INPUT_PULLUP:

				CLR_BIT(DDRA, LOC_u8Pin);

				SET_BIT(PORTA, LOC_u8Pin);

				break;
			}

			break;

//////////////////////////////////////////////////////////////////////////

			/*CASE 1  IF PIN IS ON PORTB*/
		case PORT_u8PORTB:

			switch (Copy_u8PinMode) {

			case PORT_u8OUTPUT_LOW:

				SET_BIT(DDRB, LOC_u8Pin);

				CLR_BIT(PORTB, LOC_u8Pin);

				break;

			case PORT_u8OUTPUT_HIGH:

				SET_BIT(DDRB, LOC_u8Pin);

				SET_BIT(PORTB, LOC_u8Pin);

				break;

			case PORT_u8INPUT_FLOATING:

				CLR_BIT(DDRB, LOC_u8Pin);

				CLR_BIT(PORTB, LOC_u8Pin);

				break;

			case PORT_u8INPUT_PULLUP:

				CLR_BIT(DDRB, LOC_u8Pin);

				SET_BIT(PORTB, LOC_u8Pin);

				break;

			}
			break;
////////////////////////////////////////////////////////////////////////

			/*CASE 2  IF PIN IS ON PORTC*/
		case PORT_u8PORTC:

			switch (Copy_u8PinMode) {

			case PORT_u8OUTPUT_LOW:

				SET_BIT(DDRC, LOC_u8Pin);

				CLR_BIT(PORTC, LOC_u8Pin);

				break;

			case PORT_u8OUTPUT_HIGH:

				SET_BIT(DDRC, LOC_u8Pin);

				SET_BIT(PORTC, LOC_u8Pin);

				break;

			case PORT_u8INPUT_FLOATING:

				CLR_BIT(DDRC, LOC_u8Pin);

				CLR_BIT(PORTC, LOC_u8Pin);

				break;

			case PORT_u8INPUT_PULLUP:

				CLR_BIT(DDRC, LOC_u8Pin);

				SET_BIT(PORTC, LOC_u8Pin);

				break;

			}

			break;
///////////////////////////////////////////////////////////////////////

			/*CASE 3  IF PIN IS ON PORTD*/
		case PORT_u8PORTD:

			switch (Copy_u8PinMode) {

			case PORT_u8OUTPUT_LOW:

				SET_BIT(DDRD, LOC_u8Pin);

				CLR_BIT(PORTD, LOC_u8Pin);

				break;

			case PORT_u8OUTPUT_HIGH:

				SET_BIT(DDRD, LOC_u8Pin);

				SET_BIT(PORTD, LOC_u8Pin);

				break;

			case PORT_u8INPUT_FLOATING:

				CLR_BIT(DDRD, LOC_u8Pin);

				CLR_BIT(PORTD, LOC_u8Pin);

				break;

			case PORT_u8INPUT_PULLUP:

				CLR_BIT(DDRD, LOC_u8Pin);

				SET_BIT(PORTD, LOC_u8Pin);

				break;

			}

			break;
		}
	}

	/*RETURN ERROR STATUS*/
	return LOC_enuReturnStatus;
}

