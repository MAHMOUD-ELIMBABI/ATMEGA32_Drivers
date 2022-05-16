/*
 * Dio.c
 *
 *  Created on: Mar 4, 2022
 *      Author: MahmoudElImbabi
 */

#include"../../Services/Bit_utils.h"     /*INCLUDING "Bit_utlis.h" HEADER FILE */
#include"../../Services/Std_types.h"	 /*INCLUDING "Std_types.h" HEADER FILE */
#include"Dio.h"						 /*INCLUDING "Port.h" HEADER FILE */
#include"Dio_prv.h"					 /*INCLUDING "Port_prv.h" HEADER FILE */
#include"Dio_cfg.h"					 /*INCLUDING "Port_cfg.h" HEADER FILE */
#include <avr/io.h>						 /*INCLUDING "avr/io.h" HEADER FILE */

Dio_tenuErrorStatus Dio_enuWriteChannel(u8 Copy_u8ChannelId, u8 Copy_u8Level) {

	Dio_tenuErrorStatus LOC_enuReturnStatus = Dio_enuOk;

	u8 LOC_u8Port;

	u8 LOC_u8Pin;

	if (Copy_u8ChannelId > DIO_u8NUMBER_OF_CHANNELS) {

		LOC_enuReturnStatus = Dio_enuChannelError;
	}

	else if (Copy_u8Level > DIO_u8NUMBER_OF_LEVELS) {

		LOC_enuReturnStatus = Dio_enuLevelError;
	}

	else {

		LOC_u8Port = Copy_u8ChannelId / DIO_u8REGISTER_SIZE;
		LOC_u8Pin = Copy_u8ChannelId % DIO_u8REGISTER_SIZE;

		switch (LOC_u8Port) {

		case DIO_u8PORTA:
			if (GET_BIT(DDRA,LOC_u8Pin) == DIO_u8OUTPUT) {
				switch (Copy_u8Level) {

				case DIO_u8LEVEL_HIGH:
					SET_BIT(PORTA, LOC_u8Pin);
					break;

				case DIO_u8LEVEL_LOW:
					CLR_BIT(PORTA, LOC_u8Pin);
					break;

				}
			} else {
				LOC_enuReturnStatus = Dio_enuDirectionError;
			}
			break;

		case DIO_u8PORTB:

			if (GET_BIT(DDRB,LOC_u8Pin) == DIO_u8OUTPUT) {
				switch (Copy_u8Level) {

				case DIO_u8LEVEL_HIGH:
					SET_BIT(PORTB, LOC_u8Pin);
					break;

				case DIO_u8LEVEL_LOW:
					CLR_BIT(PORTB, LOC_u8Pin);
					break;

				}
			} else {
				LOC_enuReturnStatus = Dio_enuDirectionError;
			}

			break;

		case DIO_u8PORTC:

			if (GET_BIT(DDRC,LOC_u8Pin) == DIO_u8OUTPUT) {
				switch (Copy_u8Level) {

				case DIO_u8LEVEL_HIGH:
					SET_BIT(PORTC, LOC_u8Pin);
					break;

				case DIO_u8LEVEL_LOW:
					CLR_BIT(PORTC, LOC_u8Pin);
					break;

				}
			} else {
				LOC_enuReturnStatus = Dio_enuDirectionError;
			}
			break;

		case DIO_u8PORTD:

			if (GET_BIT(DDRD,LOC_u8Pin) == DIO_u8OUTPUT) {
				switch (Copy_u8Level) {

				case DIO_u8LEVEL_HIGH:
					SET_BIT(PORTD, LOC_u8Pin);
					break;

				case DIO_u8LEVEL_LOW:
					CLR_BIT(PORTD, LOC_u8Pin);
					break;

				}
			} else {
				LOC_enuReturnStatus = Dio_enuDirectionError;
			}
			break;

		}

	}
	return LOC_enuReturnStatus;
}

Dio_tenuErrorStatus Dio_enuReadChannel(u8 Copy_u8ChannelId,
		pu8 Add_pu8ChannelLevel) {

	Dio_tenuErrorStatus LOC_enuReturnStatus = Dio_enuOk;

	u8 LOC_u8Port;

	u8 LOC_u8Pin;

	if (Copy_u8ChannelId > DIO_u8NUMBER_OF_CHANNELS) {

		LOC_enuReturnStatus = Dio_enuChannelError;
	}

	else if (Add_pu8ChannelLevel == NULL) {

		LOC_enuReturnStatus = Dio_enuNullPointerError;
	}

	else {

		LOC_u8Port = Copy_u8ChannelId / DIO_u8REGISTER_SIZE;
		LOC_u8Pin = Copy_u8ChannelId % DIO_u8REGISTER_SIZE;

		switch (LOC_u8Port) {

		case DIO_u8PORTA:
			if (GET_BIT(DDRA,LOC_u8Pin) == DIO_u8INPUT) {

				*Add_pu8ChannelLevel = GET_BIT(PINA, LOC_u8Pin);

			} else {
				LOC_enuReturnStatus = Dio_enuDirectionError;
			}
			break;

		case DIO_u8PORTB:
			if (GET_BIT(DDRB,LOC_u8Pin) == DIO_u8INPUT) {

				*Add_pu8ChannelLevel = GET_BIT(PINB, LOC_u8Pin);

			} else {
				LOC_enuReturnStatus = Dio_enuDirectionError;
			}

			break;

		case DIO_u8PORTC:
			if (GET_BIT(DDRC,LOC_u8Pin) == DIO_u8INPUT) {

				*Add_pu8ChannelLevel = GET_BIT(PINC, LOC_u8Pin);

			} else {
				LOC_enuReturnStatus = Dio_enuDirectionError;
			}

			break;

		case DIO_u8PORTD:

			if (GET_BIT(DDRD,LOC_u8Pin) == DIO_u8INPUT) {

				*Add_pu8ChannelLevel = GET_BIT(PIND, LOC_u8Pin);

			} else {
				LOC_enuReturnStatus = Dio_enuDirectionError;
			}

			break;

		}
	}
	return LOC_enuReturnStatus;
}

Dio_tenuErrorStatus Dio_enuWritePort(u8 Copy_u8PortId, u8 Copy_u8Value) {

	Dio_tenuErrorStatus LOC_enuReturnStatus = Dio_enuOk;

	if (Copy_u8PortId > DIO_u8NUMBER_OF_PORTS) {

		LOC_enuReturnStatus = Dio_enuPortRangeError;
	}

	else {

		switch (Copy_u8PortId) {

		case DIO_u8PORTA:

			ASSIGN_REG(PORTA, Copy_u8Value);

			break;

		case DIO_u8PORTB:

			ASSIGN_REG(PORTB, Copy_u8Value);

			break;

		case DIO_u8PORTC:

			ASSIGN_REG(PORTC, Copy_u8Value);

			break;

		case DIO_u8PORTD:

			ASSIGN_REG(PORTD, Copy_u8Value);

			break;

		}

	}

	return LOC_enuReturnStatus;
}

Dio_tenuErrorStatus Dio_enuReadPort(u8 Copy_u8PortId, pu8 Add_pu8PortValue) {

	Dio_tenuErrorStatus LOC_enuReturnStatus = Dio_enuOk;

	if (Add_pu8PortValue == NULL) {

		LOC_enuReturnStatus = Dio_enuNullPointerError;
	}

	else if (Copy_u8PortId > DIO_u8NUMBER_OF_PORTS) {

		LOC_enuReturnStatus = Dio_enuPortRangeError;
	}

	else {

		switch (Copy_u8PortId) {

		case DIO_u8PORTA:

			*Add_pu8PortValue = PINA;

			break;

		case DIO_u8PORTB:

			*Add_pu8PortValue = PINB;

			break;

		case DIO_u8PORTC:

			*Add_pu8PortValue = PINC;

			break;

		case DIO_u8PORTD:

			*Add_pu8PortValue = PIND;

			break;

		}

	}
	return LOC_enuReturnStatus;
}

Dio_tenuErrorStatus Dio_enuFlipChannel(u8 Copy_u8ChannelId) {

	Dio_tenuErrorStatus LOC_enuReturnStatus = Dio_enuOk;
	u8 LOC_u8Port;
	u8 LOC_u8Pin;

	if (Copy_u8ChannelId > DIO_u8NUMBER_OF_CHANNELS) {

		LOC_enuReturnStatus = Dio_enuChannelError;
	}

	else {
		LOC_u8Port = Copy_u8ChannelId / DIO_u8REGISTER_SIZE;
		LOC_u8Pin = Copy_u8ChannelId % DIO_u8REGISTER_SIZE;

		switch (LOC_u8Port) {

		case DIO_u8PORTA:

			if (GET_BIT(DDRA,LOC_u8Pin) == DIO_u8OUTPUT) {

				TGL_BIT(PORTA, LOC_u8Pin);

			}
			break;

		case DIO_u8PORTB:

			if (GET_BIT(DDRB,LOC_u8Pin) == DIO_u8OUTPUT) {

				TGL_BIT(PORTB, LOC_u8Pin);

			}
			break;

		case DIO_u8PORTC:

			if (GET_BIT(DDRC,LOC_u8Pin) == DIO_u8OUTPUT) {

				TGL_BIT(PORTC, LOC_u8Pin);

			}
			break;

		case DIO_u8PORTD:

			if (GET_BIT(DDRD,LOC_u8Pin) == DIO_u8OUTPUT) {

				TGL_BIT(PORTD, LOC_u8Pin);

			}
			break;

		}

	}
	return LOC_enuReturnStatus;
}
