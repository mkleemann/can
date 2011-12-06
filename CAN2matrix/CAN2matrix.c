/*
 * CAN2matrix.c
 *
 * Created: 28.11.2011 18:12:46
 *  Author: MKleemann
 */

#include <avr/io.h>

#define ___DEBUG_LEVEL___

#include "spi/spi.h"
#include "util/util.h"
#include "leds/leds.h"

int main(void)
{
   // initialize the hardware SPI with default values set in spi/spi_config.h
   spi_master_init();
   // initialize the USART in case of debugging
   #ifdef ___DEBUG_LEVEL___
   DEBUG_INIT();
   DEBUG_PRINT("Testing!" CR);
   #endif // ___DEBUG_LEVEL___
   led_init();
   while (1)
   {
      //TODO:: Please write your application code
   }
}