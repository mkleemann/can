/*
 * CAN2matrix.c
 *
 * Created: 28.11.2011 18:12:46
 *  Author: MKleemann
 */

#include <avr/io.h>

#include "spi/spi.h"
#include "uart/uart.h"

int main(void)
{
   // initialize the hardware SPI with default values set in spi/spi_config.h
   spi_master_init();
   // initialize the USART
   uart_init();


   while (1)
   {
      //TODO:: Please write your application code
   }
}