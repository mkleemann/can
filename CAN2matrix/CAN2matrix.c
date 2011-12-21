/*
 * CAN2matrix.c
 *
 * Created: 28.11.2011 18:12:46
 *  Author: MKleemann
 */

#include <avr/io.h>

#include <util/delay.h>
#include <stdbool.h>

#include "util/util.h"
#include "spi/spi.h"
#include "can/can_mcp2515.h"

int main(void)
{
   // error LED output
   DDRC |= (1 << PINC2) | (1 << PINC1) | (1 << PINC0);
   PORTC &= ~(1 << PINC0);
   // initialize the hardware SPI with default values set in spi/spi_config.h
   spi_pin_init();
   spi_master_init();
   // init can interface 1
   if (false == can_init_mcp2515(CAN_CHIP1, CAN_BITRATE_125_KBPS))
   {
      PORTC &= ~(1 << PINC2); // error
   }
   else
   {
      while (1)
      {
         if(can_check_message_received(CAN_CHIP1))
         {
            can_t msg;
            // try to read message
            if(can_get_message(CAN_CHIP1, &msg))
            {
               msg.msgId += 10;
               can_send_message(CAN_CHIP1, &msg);
            } /* end of if message read */
         } /* end of if check can message received */
      }
   } /* end of else do it */
}

