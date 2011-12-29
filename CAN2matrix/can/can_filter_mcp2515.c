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
 * can_filter_mcp2515.c
 *
 * Created: 28.11.2011 18:37:21
 *  Author: MKleemann
 */

#include "can_mcp2515.h"

/**
 * @brief clear all filters
 *
 * Note: The MCP2515 has to be in configuration mode to set these registers.
 *
 * @param chip selected
 */
void clear_filters(eChipSelect chip)
{
   // set buffers to receive all messages
   write_register_mcp2515(chip, RXB0CTRL, (1<<RXM1) | (1<<RXM0));
   write_register_mcp2515(chip, RXB1CTRL, (1<<RXM1) | (1<<RXM0));

   // TODO: use possibility to set registers in a row
   // remove all bits from reception filter masks to receive all messages
   // buffer 0
   write_register_mcp2515(chip, RXM0SIDH, 0);
   write_register_mcp2515(chip, RXM0SIDL, 0);
   write_register_mcp2515(chip, RXM0EID8, 0);
   write_register_mcp2515(chip, RXM0EID0, 0);
   // buffer 1
   write_register_mcp2515(chip, RXM1SIDH, 0);
   write_register_mcp2515(chip, RXM1SIDL, 0);
   write_register_mcp2515(chip, RXM1EID8, 0);
   write_register_mcp2515(chip, RXM1EID0, 0);
   // filter 0
   write_register_mcp2515(chip, RXF0SIDH, 0);
   write_register_mcp2515(chip, RXF0SIDL, 0);
   write_register_mcp2515(chip, RXF0EID8, 0);
   write_register_mcp2515(chip, RXF0EID0, 0);
   // filter 1
   write_register_mcp2515(chip, RXF1SIDH, 0);
   write_register_mcp2515(chip, RXF1SIDL, 0);
   write_register_mcp2515(chip, RXF1EID8, 0);
   write_register_mcp2515(chip, RXF1EID0, 0);
   // filter 2
   write_register_mcp2515(chip, RXF2SIDH, 0);
   write_register_mcp2515(chip, RXF2SIDL, 0);
   write_register_mcp2515(chip, RXF2EID8, 0);
   write_register_mcp2515(chip, RXF2EID0, 0);
   // filter 3
   write_register_mcp2515(chip, RXF3SIDH, 0);
   write_register_mcp2515(chip, RXF3SIDL, 0);
   write_register_mcp2515(chip, RXF3EID8, 0);
   write_register_mcp2515(chip, RXF3EID0, 0);
   // filter 4
   write_register_mcp2515(chip, RXF4SIDH, 0);
   write_register_mcp2515(chip, RXF4SIDL, 0);
   write_register_mcp2515(chip, RXF4EID8, 0);
   write_register_mcp2515(chip, RXF4EID0, 0);
   // filter 5
   write_register_mcp2515(chip, RXF5SIDH, 0);
   write_register_mcp2515(chip, RXF5SIDL, 0);
   write_register_mcp2515(chip, RXF5EID8, 0);
   write_register_mcp2515(chip, RXF5EID0, 0);
}

/**
 * @brief set filters during configuration (static filters)
 * @param chip selected
 * @param pointer to filter struct
 */
void setFilters(eChipSelect   chip,
                uint8_t*      filter)
{
   // TODO: add filter setup implementation
}

