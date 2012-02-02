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
 * spi_config.h
 *
 * Created: 28.11.2011 18:16:39
 *  Author: MKleemann
 */


#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

/* @brief SPI_PRESCALER must have a value which is 2^n (n = 1..7)
 */
#ifndef SPI_PRESCALER
   #define SPI_PRESCALER      8
#endif


/***************************************************************************/
/* PORT PINS FOR SPI - here ATmega8                                        */
/***************************************************************************/
#define P_SCK                 B,5
#define P_MISO                B,4
#define P_MOSI                B,3


#endif /* SPI_CONFIG_H_ */