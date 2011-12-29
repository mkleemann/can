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
 * CAN2matrix.c
 *
 * Created: 28.11.2011 18:12:46
 *  Author: MKleemann
 */

#include <avr/io.h>

#include <util/delay.h>
#include <stdbool.h>
#include <avr/interrupt.h>

#include "util/util.h"
#include "spi/spi.h"
#include "can/can_mcp2515.h"
#include "timer/timer.h"

static volatile uint16_t send_it = 0;

int main(void)
{
   // error LED output (low = on)
   DDRC |= (1 << PINC3) | (1 << PINC2) | (1 << PINC1) | (1 << PINC0);
   PORTC |= (1 << PINC3) | (1 << PINC2) | (1 << PINC1) | (1 << PINC0);

   // set timer
   initTimer0();
   sei();

   // initialize the hardware SPI with default values set in spi/spi_config.h
   spi_pin_init();
   spi_master_init();
   // init can interface 1
   if (false == can_init_mcp2515(CAN_CHIP1, CAN_BITRATE_125_KBPS))
   {
      PORTC &= ~(1 << PINC0);    // error
   }
   else
   {
      while (1)
      {
         can_t msg;

         if (send_it >= 4)    // approx. 260ms 4MHz@1024 prescale factor
         {
            send_it = 0;
            msg.msgId = 0x20B;
            msg.header.len = 2;
            msg.header.rtr = 0;
            msg.data[0] = 0xAF;
            msg.data[1] = 0xFE;
            // send message every 260ms
            can_send_message(CAN_CHIP1, &msg);

            PORTC ^= (1 << PINC2);     // toggle LED
         } /* end of if  */

         if (can_check_message_received(CAN_CHIP1))
         {
            // try to read message
            if (can_get_message(CAN_CHIP1, &msg))
            {
               PORTC ^= (1 << PINC3);
               msg.msgId += 10;
               can_send_message(CAN_CHIP1, &msg);
            } /* end of if message read */
         } /* end of if check can message received */
      }
   } /* end of else do it */
}

ISR(TIMER0_OVF_vect)
{
   ++send_it;
}

