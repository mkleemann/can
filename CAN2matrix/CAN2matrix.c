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
#include "CAN2matrix.h"
#include "matrix.h"

static volatile uint8_t  send_it  = 0;
static volatile bool     bussleep = false;
static volatile bool     wakeup   = false;

int main(void)
{
   // error LED output (low = on)
   DDRC |= (1 << PINC3) | (1 << PINC2) | (1 << PINC1) | (1 << PINC0);
   PORTC |= (1 << PINC3) | (1 << PINC2) | (1 << PINC1) | (1 << PINC0);

   // set timer for bussleep detection
   initTimer1(TimerCompare);
   startTimer1();
   // set timer for CAN 100ms trigger
   initTimer2(TimerCompare);
   startTimer2();
   // enable all (configured) interrupts
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
         /**** SLEEP *******************************************************/
         if (bussleep == true)
         {
            // disable interrupts for now
            cli();
            // stop timer for now
            stopTimer2();
            // reset global flags
            bussleep = false;
            send_it  = 0;
            // setup wakeup interrupt INT0 trigger
            MCUCR |= EXTERNAL_INT0_TRIGGER;  // set trigger flags
            // setup wakeup interrupt
            GICR  |= EXTERNAL_INT0_ENABLE;   // enable interrupt INT0
            // put MCP2515 to sleep and wait for interrupt
            mcp2515_sleep(CAN_CHIP1, INT_SLEEP_WAKEUP_BY_CAN);
            // debugging ;-)
            PORTC &= ~(1 << PINC1);     // LED on
            // enable interrupts again
            sei();
         } /* end of if no message received for 30 seconds */

         /**** WAKEUP ******************************************************/
         if (wakeup == true)
         {
            // disable all interrupts
            cli();
            // reset flags
            wakeup = false;
            // disable interrupt INT0
            MCUCR &= ~(EXTERNAL_INT0_TRIGGER);     // remove trigger flags
            GICR  &= ~(EXTERNAL_INT0_ENABLE);      // disable interrupt INT0
            // wakeup MCP25*
            mcp2515_wakeup(CAN_CHIP1);
            // start timer
            startTimer2();
            // debugging ;-)
            PORTC |= (1 << PINC1);     // LED off
            // enable all interrupts again
            sei();
         } /* end of if wakeup flag set */


         /**** TESTING *****************************************************/
         can_t msg;

         if (send_it >= 4)    // approx. 100ms 4MHz@1024 prescale factor
         {
            send_it = 0;
            msg.msgId = CANID_2_IGNITION;
            fillInfoToCAN2(&msg);
            // send message every 100ms
            can_send_message(CAN_CHIP1, &msg);

            PORTC ^= (1 << PINC2);     // toggle LED
         } /* end of if  */

         if (can_check_message_received(CAN_CHIP1))
         {
            // try to read message
            if (can_get_message(CAN_CHIP1, &msg))
            {
               PORTC ^= (1 << PINC3);

               // reset timer, since there is activity on master CAN bus
               restartTimer1();

//               fetchInfoFromCAN1(&msg);
//               fillInfoToCAN2(&msg);

               msg.msgId += 10;
               can_send_message(CAN_CHIP1, &msg);
            } /* end of if message read */
         } /* end of if check can message received */

      } /* end of while(1) */
   } /* end of else do it */
} /* end of main() */


/***************************************************************************/
/* INTERRUPT SERVICE ROUTINES                                              */
/***************************************************************************/

#if 0
// Timer0 overflow interrupt handler (~65ms 4MHz@1024 precale factor)
ISR(TIMER0_OVF_vect)
{
}
#endif

// Timer1 input capture interrupt (~15s 4MHz@1024 prescale factor)
ISR(TIMER1_CAPT_vect)
{
   bussleep = true;
}

// Timer2 compare match interrupt handler
// --> set as 25ms (4x25ms = 100ms)
ISR(TIMER2_COMP_vect)
{
   ++send_it;
}

// External Interrupt0 handler
ISR(INT0_vect)
{
   wakeup = true;
}

