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
 * can_send_mcp2515.c
 *
 * Created: 28.11.2011 18:19:15
 *  Author: MKleemann
 */

#include "can_mcp2515.h"


/* @brief  checks if any tx buffer is free to be loaded with a message
 * @param  chip selected
 * @return true if a buffer is free
 */
bool can_check_free_tx_buffers(eChipSelect chip)
{
   uint8_t status = read_status_mcp2515(chip, MCP2515_READ_STATUS);

   // (1<<TXB2CNTRL_TXREQ) | (1<<TXB1CNTRL_TXREQ) | (1<<TXB0CNTRL_TXREQ) => 0x54
   if ((status & 0x54) == 0x54) {
      // all buffers used
      return false;
   }

   return true;
}

/*
 * @brief  send message via CAN
 *
 * @param  chip select - chip to use
 * @param  msg         - CAN message to send
 * @return address of buffer used to send
 */
uint8_t can_send_message(eChipSelect   chip,
                         can_t*        msg)
{
   // read quick status to get tx buffer information
   uint8_t status = read_status_mcp2515(chip, MCP2515_READ_STATUS);
   uint8_t address;

   // determine tx buffer to be used to send message
   if (BIT_IS_UNSET(status, TXB0CNTRL_TXREQ)) {
      address = TXB0ADDR;
   }
   else if (BIT_IS_UNSET(status, TXB1CNTRL_TXREQ)) {
      address = TXB1ADDR;
   }
   else if (BIT_IS_UNSET(status, TXB2CNTRL_TXREQ)) {
      address = TXB2ADDR;
   }
   else {
      // all buffers used - could not send message
      return 0;
   }

   // now write message to registers
   // MCP2515 allows to write more than one byte at a time. Starting with
   // the first address, it put the write pointer to the next byte - and
   // in most cases - the next register to be written. This fasten up the
   // message handling.
   unset_chip_select(chip);
   spi_putc(MCP2515_LOAD_TX | address);

   // standard msg id
   spi_putc(msg->msgId >> 3);                // TXBxSIDH
   spi_putc(msg->msgId << 5);                // TXBxSIDL
   // extended id - not used
   spi_putc(0);                              // TXBxEID8
   spi_putc(0);                              // TXBxEID0

   uint8_t length = msg->header.len & 0x0F;

   // DLC and data
   if (msg->header.rtr) {
      // a rtr frame has a length, but contains no data
      spi_putc((1<<RTR) | length);           // TXBxDLC
   }
   else
   {
      // set message length
      spi_putc(length);                      // TXBxDLC

      // data
      for (uint8_t i = 0; i < length; ++i)
      {
         spi_putc(msg->data[i]);             // TXBxDn
      }
   }
   set_chip_select(chip);

   // wait a little before sending the next command
   _delay_us(1);

   // request to send message in buffer written above
   unset_chip_select(chip);
   address = (address == 0) ? 1 : address;   // set correct RTS bit (0 -> 1)
   spi_putc(MCP2515_RTS | address);
   set_chip_select(chip);

   return address;
}



