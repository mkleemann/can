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
 * \file can_error_mcp2515.c
 *
 * \date Created: 18.07.2012 18:23:45
 * \author Matthias Kleemann
 **/


#include "can_mcp2515.h"



/**
 * \brief  get TX error state of CAN bus
 * \param  chip - select chip to use
 * \return error state
 *
 * \sa TXBO, TXEP, TXWAR
 */
can_error_t can_get_tx_bus_errors(eChipSelect chip)
{
   can_error_t error = CAN_ERR_NO_ERROR;
   uint8_t errFlags = read_register_mcp2515(chip, EFLG);

   if(errFlags & (1 << TXBO))
   {
      // Bus-Off Error
      error = CAN_ERR_TX_BUS_OFF;
   }
   else if(errFlags & (1 << TXEP))
   {
      // TX Error-Passive
      error = CAN_ERR_TX_PASSIVE;
   }
   else if(errFlags & (1 << TXWAR))
   {
      // TX Error Warning
      error = CAN_ERR_TX_WARNING;
   }

   return error;
}

/**
 * \brief  get RX error state of CAN bus
 * \param  chip - select chip to use
 * \return error state
 *
 * \sa RX1OVR, RX0OVR, RXEP, RXWAR
 */
can_error_t can_get_rx_bus_errors(eChipSelect chip)
{
   can_error_t error = CAN_ERR_NO_ERROR;
   uint8_t errFlags = read_register_mcp2515(chip, EFLG);

   if(errFlags & (1 << RX1OVR))
   {
      // RX buffer 1 overflow
      error = CAN_ERR_RX1_OVERFLOW;
      // reset flag
      bit_modify_mcp2515(chip, EFLG, RX1OVR, 0);
      // if interrupt enabled, reset it here
      bit_modify_mcp2515(chip, CANINTF, RX1IF, 0);
   }
   else if(errFlags & (1 << RX0OVR))
   {
      // RX buffer 1 overflow
      error = CAN_ERR_RX0_OVERFLOW;
      // reset flag
      bit_modify_mcp2515(chip, EFLG, RX0OVR, 0);
      // if interrupt enabled, reset it here
      bit_modify_mcp2515(chip, CANINTF, RX0IF, 0);
   }
   else if(errFlags & (1 << RXEP))
   {
      // RX Error-Passive
      error = CAN_ERR_RX_PASSIVE;
   }
   else if(errFlags & (1 << RXWAR))
   {
      // RX Error Warning
      error = CAN_ERR_RX_WARNING;
   }

   return error;
}

/**
 * \brief detect any unusual error count (TEC/REC)
 * \param  chip - select chip to use
 * \return error state
 *
 * Set when TEC or REC is equal to or greater than 96 (TXWAR or RXWAR = 1)
 * and reset when both REC and TEC are less than 96.
 *
 * \sa EWARN, TXWAR, RXWAR
 */
can_error_t can_get_general_bus_errors(eChipSelect chip)
{
   can_error_t error = CAN_ERR_NO_ERROR;

   if(read_register_mcp2515(chip, EFLG) & (1 << EWARN))
   {
      // set warning
      error = CAN_ERR_WARNING;
   }

   return error;
}

