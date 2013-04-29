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
 * \file can_config_mcp2515_example.c
 *
 * \date Created: 11.03.2013 06:10:00
 * \author Matthias Kleemann
 *
 * Example configuration with two CAN chips connected via SPI at an ATmega8 with
 * internal 4MHz clock. The CAN chips run also on 4MHz (external clock) with
 * different CAN baudrates.
 **/


#include "can_config_mcp2515.h"


/**
 * \brief internal CAN bitrate setup
 *
 * These values are based on 4Mhz oscillator frequency. Higher CAN bitrates
 * may need a higher clock frequency (bus idle time - see datasheet).
 *
 * Only one sample time is set, wake-up filters too (Wake On CAN).
 */
uint8_t mcp2515_cnf[NUM_OF_CAN_BITRATES][3] = {
   //! CAN_BITRATE_100_KBPS
   {
      0x01,    // CNF1  (1 << BRP0)
      0xA0,    // CNF2  (1 << BTLMODE) | (1 << PHSEG12)
      0x42     // CNF3  (1 << WAKFIL)  | (1 << PHSEG21)
   },
   //! CAN_BITRATE_125_KBPS
   {
      0x01,    // CNF1  (1 << BRP0)
      0x90,    // CNF2  (1 << BTLMODE) | (1 << PHSEG11)
      0x42     // CNF3  (1 << WAKFIL)  | (1 << PHSEG21)
   }
};

/**
 * \brief array of port pins for chip select
 */
portaccess_t mcp2515_cs[NUM_OF_MCP2515]  = { CAN_CS_PORTS };

/**
 * \brief array of port pins for interrupts
 */
portaccess_t mcp2515_int[NUM_OF_MCP2515] = { CAN_INT_PORTS };

/**
 * \brief get pointer to configuration
 * \param bitrate to be used
 * \return pointer to configuration struct
 */
uint8_t * getCanConfiguration(eCanBitRate bitrate)
{
   return mcp2515_cnf[bitrate];
}

/**
 * \brief get the CS port structure
 * \param chip selected
 * \return pointer to structure
 */
portaccess_t * getCSPort(eChipSelect chip)
{
   return &mcp2515_cs[chip];
}

/**
 * \brief get the INT port structure
 * \param chip selected
 * \return pointer to structure
 */
portaccess_t * getINTPort(eChipSelect chip)
{
   return &mcp2515_int[chip];
}
