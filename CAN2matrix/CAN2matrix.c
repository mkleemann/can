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
#include <avr/sleep.h>

#include "util/util.h"
#include "spi/spi.h"
#include "can/can_mcp2515.h"
#include "timer/timer.h"
#include "leds/leds.h"
#include "CAN2matrix.h"
#include "matrix.h"

static volatile uint8_t send_it     = 0;
static volatile bool    send100ms    = false;
static volatile bool    send500ms    = false;
static volatile bool    bussleep     = false;
static volatile bool    wakeup       = false;

int main(void)
{
   // init LED output
   led_init();
   // show startup
   led_on(sleepLed);

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
   if (false == can_init_mcp2515(CAN_CHIP1, CAN_BITRATE_100_KBPS))
   {
      // signal error on initialization
      led_on(errCan1LED);
   } /* end of init CAN1 failed */
   else if(false == can_init_mcp2515(CAN_CHIP2, CAN_BITRATE_125_KBPS))
   {
      // signal error on initialization
      led_on(errCan2LED);
   } /* end of else init failed CAN2 */
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
            // put MCP2515 to sleep and wait for activity interrupt
            mcp2515_sleep(CAN_CHIP1, INT_SLEEP_WAKEUP_BY_CAN);
            // put MCP25* to sleep for CAN2 and activate after activity on CAN1
            mcp2515_sleep(CAN_CHIP2, INT_SLEEP_MANUAL_WAKEUP);
            // low power consumption
            led_all_off();
            // enable all interrupts again
            sei();
            // enable wakeup interrupt
            GICR  |= EXTERNAL_INT0_ENABLE;   // enable interrupt INT0
#if ___AVR_SLEEP_ON___
            // let's sleep...
            set_sleep_mode(SLEEP_MODE_PWR_DOWN);
            sleep_mode();
#endif
         } /* end of if no message received for 30 seconds */

         /**** WAKEUP ******************************************************/
         if (wakeup == true)
         {
            // disable all interrupts
            cli();
            // reset flags
            wakeup = false;
            // wakeup all CAN busses
            mcp2515_wakeup(CAN_CHIP1);
            mcp2515_wakeup(CAN_CHIP2);
            // start timer
            startTimer2();
            // debugging ;-)
            led_on(sleepLed);
            // enable all interrupts again
            sei();
         } /* end of if wakeup flag set */

         if((false == wakeup) && (false == bussleep))
         {
            /**** GET MESSAGES FROM CAN1 ***********************************/
            can_t msg;

            if(can_check_message_received(CAN_CHIP1))
            {
               // try to read message
               if (can_get_message(CAN_CHIP1, &msg))
               {
                  // reset timer, since there is activity on master CAN bus
                  restartTimer1();
                  // fetch information from CAN1
                  fetchInfoFromCAN1(&msg);
                  // signal activity
                  led_toggle(rxCan1LED);
               } /* end of if message is read */
            } /* end of if check message received on CAN1 */

            /**** PUT MESSAGES ON CAN2 *************************************/

            if (send100ms)    // approx. 100ms 4MHz@1024 prescale factor
            {
               send100ms = false;
               msg.msgId = CANID_2_IGNITION;
               sendCan2Message(&msg);
               msg.msgId = CANID_2_WHEEL_DATA;  // should be 50ms, but keep it
               sendCan2Message(&msg);
            } /* end of if 100ms tick */

            if(send500ms)    // approx. 500ms 4MHz@1024 prescale factor
            {
               send500ms = false;
               msg.msgId = CANID_2_REVERSE_GEAR;
               sendCan2Message(&msg);
            } /* end of if 500ms tick */

            /**** GET MESSAGES FROM CAN2 ***********************************/

            // empty read buffers and get information
            if(can_check_message_received(CAN_CHIP2))
            {
               // try to read message
               if (can_get_message(CAN_CHIP2, &msg))
               {
                  // fetch information from CAN2
                  fetchInfoFromCAN2(&msg);
               } /* end of if message is read */
            } /* end of if check message received on CAN2 */
         } /* end of if no bussleep and no wakeup running */

      } /* end of while(1) */
   } /* end of else do it */

   // error handling, if CAN initialization failed
   stopTimer2();
   while(1)
   {
      if(send500ms)    // approx. 500ms 4MHz@1024 prescale factor
      {
         led_toggle(sleepLed);
      } /* end of if 500ms tick */
   } /* end of while(1) - error handling */
} /* end of main() */


/***************************************************************************/
/* HELPER ROUTINES                                                         */
/***************************************************************************/

/**
 * @brief sends message to CAN2 and filling up converted data
 *
 * Note: Set message id before calling this function.
 *
 * @param pointer to CAN message
 */
void sendCan2Message(can_t* msg)
{
   fillInfoToCAN2(msg);
   // send message
   can_send_message(CAN_CHIP2, msg);
   // signal activity
   led_toggle(txCan2LED);
}

/***************************************************************************/
/* INTERRUPT SERVICE ROUTINES                                              */
/***************************************************************************/

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
   send100ms = (0 == (send_it % 4));   // ~100ms
   send500ms = (0 == (send_it % 20));  // ~500ms
}

// External Interrupt0 handler to wake up from CAN activity
ISR(INT0_vect)
{
#if ___AVR_SLEEP_ON___
   // disable interrupt: caution if signal lies too long on pin
   GICR  &= ~(EXTERNAL_INT0_ENABLE);
   // remove interrupt possible trigger INT0 to use pin for CAN signalling
   MCUCR &= ~((1 << ISC01) | (1 << ISC00));
#endif
   wakeup = true;
}

