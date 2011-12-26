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

static volatile uint16_t send_it = 0;

int main(void)
{
   // error LED output
   DDRC |= (1 << PINC3) | (1 << PINC2) | (1 << PINC1) | (1 << PINC0);
   PORTC |= (1 << PINC3) | (1 << PINC2) | (1 << PINC1) | (1 << PINC0);
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
      #if 0
      // set timer
      TIMSK |= (1 << TOIE0);                    // interrupt enable
      TCCR0 |= (1 << CS02) | (1 << CS00);       // 1/1024 prescaler
      sei();
      #endif

      while (1)
      {
         can_t msg;

         if(send_it == 0xFFFF)
         {
            send_it = 0;
            msg.msgId = 0x20B;
            msg.header.len = 2;
            msg.header.rtr = 0;
            msg.data[0] = 0xAF;
            msg.data[1] = 0xFE;

            can_send_message(CAN_CHIP1, &msg);
         } /* end of if  */

         if(can_check_message_received(CAN_CHIP1))
         {
            // try to read message
            if(can_get_message(CAN_CHIP1, &msg))
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
   PORTC ^= (1 << PINC1);
}

