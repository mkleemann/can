/*
 * can_init_mcp2515.c
 *
 * Created: 28.11.2011 18:19:00
 *  Author: MKleemann
 */

#include <util/delay.h>

#include "can_mcp2515.h"
#include "can_defs_mcp2515.h"
#include "can_config_mcp2515.h"
#include "../spi/spi.h"



/* @brief internal CAN bitrate setup
 *
 * These values are based on 4Mhz oscillator frequency. Higher frequencies
 * may need a higher clock frequency (bus idle time).
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
      // set direction of /CS pins to output
      *(csPins[chip].ddr) |= (1<<csPins[chip].pin);
      // software reset MCP2515 to change it to configuration mode
      *(csPins[chip].port) &= ~(1<<csPins[chip].pin);
      spi_putc(MCP2515_RESET);
      _delay_ms(1);  // wait a little bit
      *(csPins[chip].port) |= (1<<csPins[chip].pin);
      // wait for MCP2515 to reset itself
      _delay_ms(10);
      // setup configuration registers
      write_register_mcp2515(chip, CNF1, mcp2515_cnf[bitrate][0]);
      write_register_mcp2515(chip, CNF2, mcp2515_cnf[bitrate][1]);
      write_register_mcp2515(chip, CNF3, mcp2515_cnf[bitrate][2]);
      // initialize RX interrupts
      write_register_mcp2515(chip, CANINTE, (1<<RX1IE) | (1<<RX0IE));
      // setup filters
      // TODO: set filters correctly - now all messages are received
      // set buffers to receive all messages
      write_register_mcp2515(chip, RXB0CTRL, (1<<RXM1) | (1<<RXM0));
      write_register_mcp2515(chip, RXB1CTRL, (1<<RXM1) | (1<<RXM0));
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
   *(csPins[chip].port) &= ~(1<<csPins[chip].pin);

   spi_putc(MCP2515_WRITE);
   spi_putc(address);
   spi_putc(data);

   // /CS of MCP2515 to High
   *(csPins[chip].port) |= (1<<csPins[chip].pin);
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
   *(csPins[chip].port) &= ~(1<<csPins[chip].pin);

   spi_putc(MCP2515_READ);
   spi_putc(address);
   // write something to SPI, so the byte can be read from SPI
   data = spi_putc(0xFF);

   // /CS of MCP2515 to High
   *(csPins[chip].port) |= (1<<csPins[chip].pin);

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
   *(csPins[chip].port) &= ~(1<<csPins[chip].pin);

   spi_putc(MCP2515_BITMODIFY);
   spi_putc(address);
   spi_putc(mask);
   spi_putc(data);

   // /CS of MCP2515 to High
   *(csPins[chip].port) |= (1<<csPins[chip].pin);
}

