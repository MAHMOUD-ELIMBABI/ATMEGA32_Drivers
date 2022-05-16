/*
 * UART_prv.h
 *
 *  Created on: May 14, 2022
 *      Author: MahmoudElImbabi
 */

#ifndef MCAL_UART_DRIVER_UART_PRV_H_
#define MCAL_UART_DRIVER_UART_PRV_H_

#define UBRRH			*((volatile u8*) 0x40)
#define UCSRC			*((volatile u8*) 0x40)
#define UDR				*((volatile u8*) 0x2C)
#define UCSRA			*((volatile u8*) 0x2B)
#define UCSRB 			*((volatile u8*) 0x2A)
#define UBRRL			*((volatile u8*) 0x29)

void __vector_13(void)__attribute__((signal,used));
void __vector_15(void)__attribute__((signal,used));

#endif /* MCAL_UART_DRIVER_UART_PRV_H_ */
