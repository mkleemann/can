/**
 * ----------------------------------------------------------------------------
 *
 * "THE ANY BEVERAGE-WARE LICENSE" (Revision 42 - based on beer-ware license):
 * <dev@layer128.net> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a be(ve)er(age) in return. (I don't
 * like beer much.)
 *
 * Matthias Kleemann
 *
 * ----------------------------------------------------------------------------
 *
 * \file can_sleep_mcp2515.c
 *
 * \date Created: 28.11.2011 18:19:45
 * \author Matthias Kleemann
 **/


#include "can_mcp2515.h"

/**
 * \brief saved working mode before sleeping
 *
 * When waking up, the CAN controller will automatically set the LISTEN_ONLY_MODE
 * mode. The mode will changed to the one used before, which is not all the
 * time NORMAL_MODE.
 */
uint8_t volatile savedMCP2515WorkingMode = LISTEN_ONLY_MODE;

/**
 * \brief  put MCP2515 (and attached MCP2551) to sleep
 *
 * To put MCP2551 also to sleep, connect RX1BF pin to RS pin of MCP2551. It
 * is not always wanted to wakeup on any CAN activity. Sometimes, with
 * multiple interfaces, the "master bus" should only trigger the wakeup,
 * whereas the "slave" interfaces are woken up by wakeup signal from
 * ATmega.
 *
 * \param  chip - chip to use
 * \param  mode - how/when to activate MCP2515 again
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

   // save the current working mode for wakeup
   savedMCP2515WorkingMode = read_register_mcp2515(chip, CANSTAT(0)) & MODE_SELECT_MASK;

   // put the 2515 in sleep mode
   set_mode_mcp2515(chip, SLEEP_MODE);

   if(INT_SLEEP_WAKEUP_BY_CAN == mode)
   {
      // enable generating an interrupt for wakeup when activity on bus
      bit_modify_mcp2515(chip, CANINTE, (1 << WAKIE), (1 << WAKIE));
   }
}


/**
 * \brief  wakeup MCP2515 (and attached MCP2551) from sleep mode
 *
 * \param  chip - chip to use
 * \param  mode - how/when to activate MCP2515 again
 *
 * If in manual wakeup mode, a special sequence is needed to wake the
 * MCP2515 up. This is not needed, when activating the controller by CAN
 * bus activity.
 *
 * \note
 * The CAN controller starts in LISTEN ONLY mode after wakeup. The last mode
 * when fully operable will be set after wakeup.
 *
 * \attention
 * The MCP2515 will wake up when bus activity occurs or <b>when the MCU sets,
 * via the SPI interface, the CANINTF.WAKIF bit to 'generate' a wake-up
 * attempt (the CANINTE.WAKIE bit must also be set in order for the wake-up
 * interrupt to occur).</b>
 */
void mcp2515_wakeup(eChipSelect         chip,
                    eInternalSleepMode  mode)
{
   if(INT_SLEEP_MANUAL_WAKEUP == mode)
   {
      // "generate" a wakeup interrupt, if MCP2515 is in manual
      // wakeup mode
      bit_modify_mcp2515(chip, CANINTF, (1 << WAKIF), (1 << WAKIF));
      bit_modify_mcp2515(chip, CANINTE, (1 << WAKIE), (1 << WAKIE));

      // wait for "interrupt" to be ready
      _delay_ms(1);
   }

   // reset int enable and remove the interrupt flag
   bit_modify_mcp2515(chip, CANINTE, (1 << WAKIE), 0);
   bit_modify_mcp2515(chip, CANINTF, (1 << WAKIF), 0);

   // wakeup the attached MCP2551, if connected
   bit_modify_mcp2515(chip, BFPCTRL, (1 << B1BFS), 0);

   // When we get out of sleep mode, we are in listen mode.
   // Return now into normal mode again.
   set_mode_mcp2515(chip, savedMCP2515WorkingMode);
}


