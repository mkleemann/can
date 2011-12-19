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
   return (!IS_INT_SET(chip));
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
   if (BIT_IS_SET(status, RXB0)) {
      // message in buffer 0
      address = MCP2515_READ_RX;             // Receive Buffer 0, Start at RXB0SIDH
   }
   else if (BIT_IS_SET(status, RXB1)) {
      // message in buffer 1
      address = MCP2515_READ_RX | 0x04;      // Receive Buffer 1, Start at RXB1SIDH
   }
   else {
      // error: no message available
      return 0;
   }

   RESET_CS_PIN(chip);

   // read bytes from address
   spi_putc(address);

   // read standard msg id
   msg->msgId  = (uint16_t) spi_putc(0xFF) << 3;
   msg->msgId |=            spi_putc(0xFF) >> 5;
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
   SET_CS_PIN(chip);

   // clear interrupt flag
   if (BIT_IS_SET(status, RXB0))
   {  // RXB0 was used to receive frame
      bit_modify_mcp2515(chip, CANINTF, (1 << RX0IF), 0);
   }
   else
   {  // RXB1 was used to receive frame
      bit_modify_mcp2515(chip, CANINTF, (1 << RX1IF), 0);
   }

   // return filter match status
   return (status & RXB_FILTERMATCHMASK) + 1;
}




