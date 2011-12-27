/**
 * ----------------------------------------------------------------------------
 * "THE ANY BEVERAGE-WARE LICENSE" (Revision 42 - based on beer-ware license):
 * <m.kleemann@gmx.net> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a be(ve)er(age) in return. (I don't
 * like beer much.)
 *
 * Matthias Kleemann
 * ----------------------------------------------------------------------------
 **/

/*
 * spi.h
 *
 * Created: 28.11.2011 18:16:21
 *  Author: MKleemann
 */


#ifndef SPI_H_
#define SPI_H_

#include "spi_config.h"

/* @brief activate SPI pins of AVR
 */
void spi_pin_init(void);


/* @brief activate SPI interface as master
 */
void spi_master_init(void);


/* @brief activate SPI interface as slave
 */
void spi_slave_init(void);

/* @brief  writes (and reads!) a byte via hardware SPI
 * @param  data byte to send
 * @return data byte received
 */
uint8_t spi_putc(uint8_t data);


#endif /* SPI_H_ */