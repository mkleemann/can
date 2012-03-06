/**
 * ----------------------------------------------------------------------------
 * "THE ANY BEVERAGE-WARE LICENSE" (Revision 42 - based on beer-ware license):
 * <dev@layer128.net> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a be(ve)er(age) in return. (I don't
 * like beer much.)
 *
 * Matthias Kleemann
 * ----------------------------------------------------------------------------
 **/

/*
 * can_receive_mcp2515.c
 *
 * Created: 28.11.2011 18:19:32
 *  Author: MKleemann
 */

#include "can_mcp2515.h"

/* @brief  checks if any messages are received (via MCP2515's interrupt pin)
 * @param  chip selected
 * @return true if message was received
 */
bool can_check_message_received(eChipSelect chip)
{
   // check if interrupt pin is (logical not) set - interrupt available
   bool retVal = false;

   if (CAN_CHIP1 == chip)
   {
      retVal = IS_SET(CHIP1_INT_PIN);
   }
   else
   {
      retVal = IS_SET(CHIP2_INT_PIN);
   }

   return(retVal);
}

/*
 * @brief  get received CAN message
 *
 * @param  chip select - chip to use
 * @param  msg         - CAN message received
 * @return filter match status + 1
 */
uint8_t can_get_message(eChipSelect chip,
                        can_t*      msg)
{
   // read status
   uint8_t status = read_status_mcp2515(chip, MCP2515_RX_STATUS);
   uint8_t address;

   // determine address from where to read
   // see READ RX BUFFER instruction - datasheet page 65
   if (BIT_IS_SET(status, RXB0))
   {
      // message in buffer 0
      address = MCP2515_READ_RX;             // Receive Buffer 0, Start at RXB0SIDH
   }
   else if (BIT_IS_SET(status, RXB1))
   {
      // message in buffer 1
      address = MCP2515_READ_RX | 0x04;      // Receive Buffer 1, Start at RXB1SIDH
   }
   else
   {
      // no message available
      return(0);
   }

   // reset /CS
   unset_chip_select(chip);

   // read bytes from address
   spi_putc(address);

   // read standard msg id
   uint8_t byte1 = spi_putc(0xFF);
   uint8_t byte2 = spi_putc(0xFF);
   // TODO: implement extended id support
   // check if standard frame - extended frames are not used yet
   if (0 == BIT_IS_SET(byte2, IDE))
   {
      msg->msgId  = (uint16_t) byte1 << 3;
      msg->msgId |=            byte2 >> 5;

      // extended id - not used
      spi_putc(0xFF);
      spi_putc(0xFF);

      // read DLC
      uint8_t length = spi_putc(0xFF) & 0x0F;

      msg->header.len = length;
      msg->header.rtr = (BIT_IS_SET(status, RXB_RTR)) ? 1 : 0;

      // read data bytes
      for (uint8_t i = 0; i < length; ++i)
      {
         msg->data[i] = spi_putc(0xFF);
      }
   }

   // set /CS
   set_chip_select(chip);

   // clear interrupt flag
   if (BIT_IS_SET(status, RXB0))
   {  // RXB0 was used to receive frame
      bit_modify_mcp2515(chip, CANINTF, (1 << RX0IF), 0);
   }
   else
   {  // RXB1 was used to receive frame
      bit_modify_mcp2515(chip, CANINTF, (1 << RX1IF), 0);
   }

   // check frame type (standard/extended)
   if (0 == BIT_IS_SET(byte2, IDE))
   {
      // return filter match status
      return(status & RXB_FILTERMATCHMASK) + 1;
   }
   else
   {
      // extended id not yet supported
      return(0);
   }
}

