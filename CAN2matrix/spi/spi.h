/*
 * spi.h
 *
 * Created: 28.11.2011 18:16:21
 *  Author: MKleemann
 */


#ifndef SPI_H_
#define SPI_H_

#include "spi_config.h"

/* @brief activate SPI interface as master
 *
 */
void spi_master_init(void);


/* @brief activate SPI interface as slave
 *
 */
void spi_slave_init(void);

/* @brief writes (and reads!) a byte via hardware SPI
 *
 */
uint8_t spi_putc(uint8_t data);


#endif /* SPI_H_ */