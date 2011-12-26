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
 * Only one sample time is set, no wake-up filter.
 */
static uint8_t  mcp2515_cnf[NUM_OF_CAN_BITRATES][3] = {
   // CAN_BITRATE_100_KBPS
   {
      0x01,    // CNF1  (1 << BRP0)
      0xA0,    // CNF2  (1 << BTLMODE) | (1 << PHSEG12)
      0x02     // CNF3  (1 << PHSEG21)
   },
   // CAN_BITRATE_125_KBPS
   {
      0x01,    // CNF1  (1 << BRP0)
      0x90,    // CNF2  (1 << BTLMODE) | (1 << PHSEG11)
      0x02     // CNF3  (1 << PHSEG21)
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

      // clear filters
      // TODO: set filters correctly - now all messages are received
      clear_filters(chip);

      // setup PIN functions
      // deactivate RXxBF pins and set to high impedance state
      write_register_mcp2515(chip, BFPCTRL, 0);
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
 * @brief  put MCP2515 (and attached MCP2551) to sleep
 *
 * To put MCP2551 also to sleep connect RX1BF pin to RS pin of MCP2551. It
 * is not always wanted to wakeup on any CAN activity. Sometimes, with
 * multiple interfaces, the "master bus" should only trigger the wakeup,
 * whereas the "slave" interfaces are woken up by wakeup signal from
 * atmega.
 *
 * @param  chip select - chip to use
 * @param  sleep mode  - when to activate MCP2515 again
 */
void mcp2515_sleep(eChipSelect   chip,
                   uint8_t       mode)
{
   // put also the 2551 in standby mode
   // for this, connect RX1BF to the RS pin of the 2551
   bit_modify_mcp2515(chip, BFPCTRL, (1 << B1BFS), (1 << B1BFS));

   // put the 2515 in sleep more
   set_mode_mcp2515(chip, mode);

   // enable generating an interrupt for wakeup when activity on bus
   bit_modify_mcp2515(chip, CANINTE, (1 << WAKIE), (1 << WAKIE));
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

   // wakeup the attached MCP2551
   bit_modify_mcp2515(chip, BFPCTRL, (1 << B1BFS), 0);

   // When we get out of sleep mode, we are in listen mode.
   // Return now into normal mode again.
   set_mode_mcp2515(chip, NORMAL_MODE);
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
      // set interrupt pin to input
      PIN_SET_INPUT(CHIP1_INT_PIN);
      // set /INT to high to get transitions
      SET_PIN(CHIP1_INT_PIN);
   } /* end of if CAN1 */
   else
   {
      // set interrupt pin to input
      PIN_SET_INPUT(CHIP2_INT_PIN);
      // set /INT to high to get transitions
      SET_PIN(CHIP2_INT_PIN);
   } /* end of else CAN 2 */
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

/**
 * @brief clear filters
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

