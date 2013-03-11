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
 * \file can_init_mcp2515.c
 *
 * \par Acknowlegements
 *
 * Most functions and sequences are based on CAN tutorial by Fabian Greif
 * (http://www.kreatives-chaos.com) and his CAN library. I took the freedom
 * to adapt and re-write, so I could learn and not only take it as is. You
 * may have still the feeling, that I did not understand some things fully.
 * You could be right ;-)
 * Nevertheless, without Fabians work, this little project would have taken
 * much, much longer or may never even finished.
 *
 * Thanks!
 *
 * \date Created: 28.11.2011 18:19:00
 * \author Matthias Kleemann
 **/


#include "can_mcp2515.h"


/**
 * \brief  initializes MCP2515 selected
 *
 * \par Clock Speed
 * All MCP2515 connected to AVR need to have the same clock speed when
 * using the same bitrate! See array in can_init_mcp2515.c.
 *
 * \par SPI
 * MCP2515 init routine does NOT initializes SPI. This has to be done before.
 *
 * \par Filters
 * The filters are cleared here, to allow simply every CAN message to be
 * received, which is for testing purposes the right choice. Any special
 * filter needs to be set up by the main program. The mode of operation needs
 * to be the configuration mode for that.
 *
 * \param  chip      - select chip to use
 * \param  bitrate   - CAN bitrate of chip selected
 * \param  mode      - mode of operation of MCP2515 after init
 * \return true if ok, false if error
 */
bool can_init_mcp2515(eChipSelect chip,
                      eCanBitRate bitrate,
                      uint8_t mode)
{
   bool retVal = false;
   uint8_t *cnf = 0;

   if ((bitrate < NUM_OF_CAN_BITRATES) && (chip < NUM_OF_MCP2515))
   {
      cnf = getCanConfiguration(bitrate);

      // set interrupt pins
      setup_interrupt_pins(chip);
      // set chip select pins
      setup_cs_pins(chip);
      // wait for MCP2515 to get pin status
      _delay_ms(10);

      // software reset MCP2515 to change it to configuration mode
      unset_chip_select(chip);
      spi_putc(MCP2515_RESET);
      _delay_ms(1);  // wait a little bit
      set_chip_select(chip);
      // wait for MCP2515 to reset itself
      _delay_ms(10);

      // setup configuration registers
      write_register_mcp2515(chip, CNF1, cnf[0]);
      write_register_mcp2515(chip, CNF2, cnf[1]);
      write_register_mcp2515(chip, CNF3, cnf[2]);

      // test if MCP2515 is accessible and CNF set up correctly
      if(read_register_mcp2515(chip, CNF1) != cnf[0])
      {
         return false;
      }

      // assume it works
      retVal = true;

      // initialize RX interrupts
      write_register_mcp2515(chip, CANINTE, (1<<RX1IE) | (1<<RX0IE));

#ifdef ___MASTER_CAN_CLKOUT_ENABLE___
      // init CLKOUT on master CAN
      if(CAN_CHIP1 == chip)
      {  // prescaler is CLKPREx = 00 -> fosc/1
         bit_modify_mcp2515(chip, CANCTRL(0), (1 << CLKEN), (1 << CLKEN));
      }
#endif

      // clear filters: Now all messages are received. Any other filters need
      // to be set up by main program.
      clear_filters(chip);

      // setup PIN functions
      // deactivate RX0BF pin and set to high impedance state;
      // set RX1BF to digital output (0) for MCP2551 sleep mode control
      write_register_mcp2515(chip, BFPCTRL, (1 << B1BFE));
      // setup TXnRTS pins as input
      write_register_mcp2515(chip, TXRTSCTRL, 0);
      // set MCP2515 into normal operations mode (no longer configurable)
      set_mode_mcp2515(chip, mode);
   }

   return(retVal);
}

/**
 * \brief  write to MCP2515 registers
 *
 * \param  chip      - select chip to use
 * \param  address   - register address of MCP2515
 * \param  data      - data byte
 */
void write_register_mcp2515(eChipSelect   chip,
                            uint8_t       address,
                            uint8_t       data)
{
   // /CS of MCP2515 to Low
   unset_chip_select(chip);

   spi_putc(MCP2515_WRITE);
   spi_putc(address);
   spi_putc(data);

   // /CS of MCP2515 to High
   set_chip_select(chip);
}

/**
 * \brief  write sequential to MCP2515 registers
 *
 * \param  chip      - select chip to use
 * \param  length    - length of buffer
 * \param  address   - register address of MCP2515 (start)
 * \param  data      - data buffer
 */
void write_multi_registers_mcp2515(eChipSelect   chip,
                                   uint8_t       length,
                                   uint8_t       address,
                                   uint8_t*      data)
{
   uint8_t i;

   // /CS of MCP2515 to Low
   unset_chip_select(chip);

   spi_putc(MCP2515_WRITE);
   spi_putc(address);
   for(i = 0; i < length; ++i)
   {
      spi_putc(data[i]);
   }

   // /CS of MCP2515 to High
   set_chip_select(chip);
}


/**
 * \brief  read from MCP2515 registers
 *
 * \param  chip      - select chip to use
 * \param  address   - register address of MCP2515
 * \return data      - data byte
 */
uint8_t read_register_mcp2515(eChipSelect chip,
                              uint8_t     address)
{
   uint8_t data;

   // /CS of MCP2515 to Low
   unset_chip_select(chip);

   spi_putc(MCP2515_READ);
   spi_putc(address);
   // write something to SPI, so the byte can be read from SPI
   data = spi_putc(0xFF);

   // /CS of MCP2515 to High
   set_chip_select(chip);

   return (data);
}


/**
 * \brief  write masked bits to MCP2515 registers
 *
 * Note: Not all registers are able to provide this functionality. Mostly
 *       configuration registers do. Read the datasheet for details.
 *
 * \param  chip      - select chip to use
 * \param  address   - register address of MCP2515
 * \param  mask      - bit mask for modify
 * \param  data      - data byte
 */
void bit_modify_mcp2515(eChipSelect chip,
                        uint8_t     address,
                        uint8_t     mask,
                        uint8_t     data)
{
   // /CS of MCP2515 to Low
   unset_chip_select(chip);

   spi_putc(MCP2515_BITMODIFY);
   spi_putc(address);
   spi_putc(mask);
   spi_putc(data);

   // /CS of MCP2515 to High
   set_chip_select(chip);
}

/**
 * \brief  reads MCP2515 status registers
 *
 * \param  chip    - select chip to use
 * \param  command - read quick status command of MCP2515
 * \return value of status register
 */
uint8_t read_status_mcp2515(eChipSelect  chip,
                            uint8_t      command)
{
   uint8_t data;

   // /CS of MCP2515 to Low
   unset_chip_select(chip);

   // status commend to use
   spi_putc(command);
   // write something to SPI, so the byte can be read from SPI
   data = spi_putc(0xFF);

   // /CS of MCP2515 to High
   set_chip_select(chip);

   return (data);
}


/**
 * \brief  set MCP2515 mode of operation
 *
 * \param  chip - select chip to use
 * \param  mode - mode of operation of MCP2515
 */
void set_mode_mcp2515(eChipSelect   chip,
                      uint8_t       mode)
{
   uint8_t reg = NORMAL_MODE;

   switch(mode & MODE_SELECT_MASK)
   {
      case SLEEP_MODE:
      {
         reg = (1 << REQOP0);
         break;
      }

      case LOOPBACK_MODE:
      {
         reg = (1 << REQOP1);
         break;
      }

      case LISTEN_ONLY_MODE:
      {
         reg = (1 << REQOP1) | (1 << REQOP0);
         break;
      }

      case CONFIG_MODE:
      {
         reg = (1 << REQOP2);
         break;
      }

      // no default, since there is no other mode
   }

   // set the mode selected above
   bit_modify_mcp2515(chip, CANCTRL(0), MODE_SELECT_MASK, reg);
   while ((read_register_mcp2515(chip, CANSTAT(0)) & MODE_SELECT_MASK) != reg)
   {
      // wait for the new mode to become active as advised in datasheet
   }
}

/***************************************************************************/

/**
 * \brief setting up the interrupt pins
 * \param  chip - select chip to use
 */
void setup_interrupt_pins(eChipSelect chip)
{
   portaccess_t * intPort = getINTPort(chip);

   // set interrupt pin to input and internal pull-up resistor
   *(intPort->ddr)  &= ~(1 << intPort->pin);
   *(intPort->port) |=  (1 << intPort->pin);
}

/**
 * \brief setting up the chip select pins
 * \param chip selected
 */
void setup_cs_pins(eChipSelect chip)
{
   portaccess_t * csPort = getCSPort(chip);

   // set chip select pins to high to get transition for MCP2515
   *(csPort->port) |= (1 << csPort->pin);
   // set /CS to output
   *(csPort->ddr)  |= (1 << csPort->pin);
}


/**
 * \brief set chip select for the right chip
 * \param  chip - select chip to use
 */
void set_chip_select(eChipSelect chip)
{
   portaccess_t * csPort = getCSPort(chip);
   // set chip select pins to high to get transition for MCP2515
   *(csPort->port) |= (1 << csPort->pin);
}

/**
 * \brief unset chip select for the right chip
 * \param  chip - select chip to use
 */
void unset_chip_select(eChipSelect chip)
{
   portaccess_t * csPort = getCSPort(chip);
   // set chip select pins to low to get transition for MCP2515
   *(csPort->port) &= ~(1 << csPort->pin);
}


