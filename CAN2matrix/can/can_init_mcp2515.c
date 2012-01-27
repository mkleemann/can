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
 * can_init_mcp2515.c
 *
 * Acknowlegements:
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
 * Created: 28.11.2011 18:19:00
 *  Author: MKleemann
 */

#include "can_mcp2515.h"



/* @brief internal CAN bitrate setup
 *
 * These values are based on 4Mhz oscillator frequency. Higher CAN bitrates
 * may need a higher clock frequency (bus idle time - see datasheet).
 *
 * Only one sample time is set, wake-up filters too (Wake On CAN).
 */
static uint8_t  mcp2515_cnf[NUM_OF_CAN_BITRATES][3] = {
   // CAN_BITRATE_100_KBPS
   {
      0x01,    // CNF1  (1 << BRP0)
      0xA0,    // CNF2  (1 << BTLMODE) | (1 << PHSEG12)
      0x42     // CNF3  (1 << WAKFIL)  | (1 << PHSEG21)
   },
   // CAN_BITRATE_125_KBPS
   {
      0x01,    // CNF1  (1 << BRP0)
      0x90,    // CNF2  (1 << BTLMODE) | (1 << PHSEG11)
      0x42     // CNF3  (1 << WAKFIL)  | (1 << PHSEG21)
   }
};

/*
 * @brief  initializes MCP2515 selected
 *
 * Note: All MCP2515 connected to AVR need to have the same clock speed when
 *       using the same bitrate! See array in can_init_mcp2515.c.
 *
 * MCP2515 init routine does NOT initializes SPI. This has to be done before.
 *
 * @param  chip select - chip to set up
 * @param  bitrate     - CAN bitrate of chip selected
 * @return true if ok, false if error
 */
bool can_init_mcp2515(eChipSelect chip,
                      eCanBitRate bitrate)
{
   bool retVal = false;
   if ((bitrate < NUM_OF_CAN_BITRATES) && (chip < NUM_OF_MCP2515))
   {
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
      write_register_mcp2515(chip, CNF1, mcp2515_cnf[bitrate][0]);
      write_register_mcp2515(chip, CNF2, mcp2515_cnf[bitrate][1]);
      write_register_mcp2515(chip, CNF3, mcp2515_cnf[bitrate][2]);

      // test if MCP2515 is accessible and CNF set up correctly
      if(read_register_mcp2515(chip, CNF1) != mcp2515_cnf[bitrate][0])
      {
         return false;
      } /* end of if check if MCP2515 is accessible */

      // assume it works
      retVal = true;

      // initialize RX interrupts
      write_register_mcp2515(chip, CANINTE, (1<<RX1IE) | (1<<RX0IE));
#ifdef ___MASTER_CAN_CLKOUT_ENABLE___
      // init CLKOUT on master CAN
      if(CAN_CHIP1 == chip)
      {  // prescaler is CLKPREx = 00 -> fosc/1
         bit_modify_mcp2515(chip, CANCTRL(0), (1 << CLKEN), (1 << CLKEN));
      } /* end of if CLKEN on master CAN */
#endif

      // clear filters
      // TODO: set filters correctly - now all messages are received
      clear_filters(chip);

      // setup PIN functions
      // deactivate RX0BF pin and set to high impedance state;
      // set RX1BF to digital output (0) for MCP2551 sleep mode control
      write_register_mcp2515(chip, BFPCTRL, (1 << B1BFE));
      // setup TXnRTS pins as input
      write_register_mcp2515(chip, TXRTSCTRL, 0);
      // set MCP2515 into normal operations mode (no longer configurable)
      bit_modify_mcp2515(chip, CANCTRL(0), 0xE0, 0);
   } /* end of check CAN bitrates available and available MCP2515 devices */
   return(retVal);
}

/*
 * @brief  write to MCP2515 registers
 *
 * @param  chip select - chip to use
 * @param  address     - register address of MCP2515
 * @param  data        - data byte
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


/*
 * @brief  read from MCP2515 registers
 *
 * @param  chip select - chip to use
 * @param  address     - register address of MCP2515
 * @return data        - data byte
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


/*
 * @brief  write masked bits to MCP2515 registers
 *
 * Note: Not all registers are able to provide this functionality. Mostly
 *       configuration registers do. Read the datasheet for details.
 *
 * @param  chip select - chip to use
 * @param  address     - register address of MCP2515
 * @param  mask        - bit mask for modify
 * @param  data        - data byte
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

/*
 * @brief  reads MCP2515 status registers
 *
 * @param  chip select - chip to use
 * @param  command     - read quick status command of MCP2515
 * @return value of status register
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


/*
 * @brief  set MCP2515 mode of operation
 *
 * @param  chip select - chip to use
 * @param  mode of operation of MCP2515
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
      } /* end of case SLEEP_MODE */
      case LOOPBACK_MODE:
      {
         reg = (1 << REQOP1);
         break;
      } /* end of case LOOPBACK_MODE */
      case LISTEN_ONLY_MODE:
      {
         reg = (1 << REQOP1) | (1 << REQOP0);
         break;
      } /* end of case LISTEN_ONLY_MODE */
      case CONFIG_MODE:
      {
         reg = (1 << REQOP2);
         break;
      } /* end of case CONFIG_MODE */
      // no default, since there is no other mode
   } /* end of switch mode */

   // set the mode selected above
   bit_modify_mcp2515(chip, CANCTRL(0), MODE_SELECT_MASK, reg);
   while ((read_register_mcp2515(chip, CANSTAT(0)) & MODE_SELECT_MASK) != reg)
   {
      // wait for the new mode to become active as advised in datasheet
   }
}

/***************************************************************************/

/* @brief setting up the interrupt pins
 * @param chip selected
 */
void setup_interrupt_pins(eChipSelect chip)
{
   if(CAN_CHIP1 == chip)
   {
      // set interrupt pin to input and internal pull-up resistor
      PIN_SET_PULLUP(CHIP1_INT_PIN);
   } /* end of if CAN1 */
   else
   {
      // set interrupt pin to input and internal pull-up resistor
      PIN_SET_PULLUP(CHIP2_INT_PIN);
   } /* end of else CAN2 */
}

/* @brief setting up the chip select pins
 * @param chip selected
 */
void setup_cs_pins(eChipSelect chip)
{
   if(CAN_CHIP1 == chip)
   {
      // set chip select pins to high to get transition for MCP2515
      SET_PIN(CHIP1_CS_PIN);
      // set /CS to output
      PIN_SET_OUTPUT(CHIP1_CS_PIN);
   } /* end of if CAN1 */
   else
   {
      // set chip select pins to high to get transition for MCP2515
      SET_PIN(CHIP2_CS_PIN);
      // set /CS to output
      PIN_SET_OUTPUT(CHIP2_CS_PIN);
   } /* end of else CAN 2 */
}


/* @brief set chip select for the right chip
 * @param chip selected
 */
void set_chip_select(eChipSelect chip)
{
   if(CAN_CHIP1 == chip)
   {
      // set chip select pins to high to get transition for MCP2515
      SET_PIN(CHIP1_CS_PIN);
   } /* end of if CAN1 */
   else
   {
      // set chip select pins to high to get transition for MCP2515
      SET_PIN(CHIP2_CS_PIN);
   } /* end of else CAN 2 */
}

/* @brief unset chip select for the right chip
 * @param chip selected
 */
void unset_chip_select(eChipSelect chip)
{
   if(CAN_CHIP1 == chip)
   {
      // set chip select pins to high to get transition for MCP2515
      RESET_PIN(CHIP1_CS_PIN);
   } /* end of if CAN1 */
   else
   {
      // set chip select pins to high to get transition for MCP2515
      RESET_PIN(CHIP2_CS_PIN);
   } /* end of else CAN 2 */
}


