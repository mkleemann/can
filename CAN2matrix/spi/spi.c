/*
 * spi.c
 *
 * Created: 28.11.2011 18:16:51
 *  Author: MKleemann
 *
 * @brief common SPI communication
 */

#include <avr/io.h>
#include "spi.h"
#include "../util/util.h"

/* @brief setup of SPI pins
 */
void spi_pin_init(void)
{
   // set all SPI port pins to low
   SCK_PORT  &= ~(1<<SCK_BIT);
   MOSI_PORT &= ~(1<<MOSI_BIT);
   MISO_PORT &= ~(1<<MISO_BIT);

   // set SPI port pins
   SCK_DDR  |=  (1<<SCK_BIT);
   MOSI_DDR |=  (1<<MOSI_BIT);
   MISO_DDR &= ~(1<<MISO_BIT);
}

/* @brief activate SPI interface as master
 */
void spi_master_init(void)
{
   // enable SPI as master; the MSB of the data word is transmitted first
   SPCR = (1<<SPE) | (1<<MSTR) | R_SPCR;
   SPSR = R_SPSR;
}

/* @brief activate SPI interface as slave
 */
void spi_slave_init(void)
{
   // enable SPI as slave; the MSB of the data word is transmitted first
   SPCR = (1<<SPE);
   SPSR = R_SPSR;
}

/* @brief  writes (and reads!) a byte via hardware SPI
 * @param  data byte to send
 * @return data byte received
 */
uint8_t spi_putc(uint8_t data)
{
   // put byte in send-buffer
   SPDR = data;

   // wait until byte was send
   while( !( SPSR & (1<<SPIF) ) )
      ;

   // return value of SPI data register
   return SPDR;
}

