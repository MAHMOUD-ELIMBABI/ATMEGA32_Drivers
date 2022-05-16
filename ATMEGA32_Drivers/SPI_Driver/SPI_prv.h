/*
 * SPI_prv.h
 *
 *  Created on: May 12, 2022
 *      Author: MahmoudElImbabi
 */

#ifndef MCAL_SPI_DRIVER_SPI_PRV_H_
#define MCAL_SPI_DRIVER_SPI_PRV_H_

#define SPDR             * ((volatile u8 *) 0x2F)
#define SPSR             * ((volatile u8 *) 0x2E)
#define SPCR             * ((volatile u8 *) 0x2D)

#define SPI_ENABLE			0x64
#define SPI_FLAG_READ		0x80

void __vector_12(void) __attribute__((signal,used));
#endif /* MCAL_SPI_DRIVER_SPI_PRV_H_ */
