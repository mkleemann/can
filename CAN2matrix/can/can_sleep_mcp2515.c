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
 * can_sleep_mcp2515.c
 *
 * Created: 28.11.2011 18:19:45
 *  Author: MKleemann
 */

#include "can_mcp2515.h"

/*
 * @brief  put MCP2515 (and attached MCP2551) to sleep
 *
 * To put MCP2551 also to sleep connect RX1BF pin to RS pin of MCP2551. It
 * is not always wanted to wakeup on any CAN activity. Sometimes, with
 * multiple interfaces, the "master bus" should only trigger the wakeup,
 * whereas the "slave" interfaces are woken up by wakeup signal from
 * ATmega.
 *
 * @param  chip select - chip to use
 * @param  sleep mode  - when to activate MCP2515 again
 */
void mcp2515_sleep(eChipSelect         chip,
                   eInternalSleepMode  mode)
{
   // put also the 2551 in standby mode, but only when waking it up manually
   if(INT_SLEEP_MANUAL_WAKEUP == mode)
   {
      // for this, connect RX1BF to the RS pin of the MCP2551
      bit_modify_mcp2515(chip, BFPCTRL, (1 << B1BFS), (1 << B1BFS));
   }

   // put the 2515 in sleep mode
   set_mode_mcp2515(chip, SLEEP_MODE);

   if(INT_SLEEP_WAKEUP_BY_CAN == mode)
   {
      // enable generating an interrupt for wakeup when activity on bus
      bit_modify_mcp2515(chip, CANINTE, (1 << WAKIE), (1 << WAKIE));
   } /* end of how to wakeup */
}


/*
 * @brief  wakeup MCP2515 (and attached MCP2551) from sleep mode
 *
 * @param  chip select - chip to use
 */
void mcp2515_wakeup(eChipSelect   chip)
{
   // reset int enable and remove the interrupt flag
   bit_modify_mcp2515(chip, CANINTE, (1 << WAKIE), 0);
   bit_modify_mcp2515(chip, CANINTF, (1 << WAKIF), 0);

   // wakeup the attached MCP2551, if connected
   bit_modify_mcp2515(chip, BFPCTRL, (1 << B1BFS), 0);

   // When we get out of sleep mode, we are in listen mode.
   // Return now into normal mode again.
   set_mode_mcp2515(chip, NORMAL_MODE);
}

