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
 * \file can_mcp2515.h
 *
 * \date Created: 28.11.2011 18:15:12
 * \author Matthias Kleemann
 **/



#ifndef CAN_MCP2515_H_
#define CAN_MCP2515_H_

#include <stdbool.h>
#include <util/delay.h>

#include "util/util.h"
#include "spi/spi.h"
#include "can_defs_mcp2515.h"
#include "config/can_config_mcp2515.h"

/**************************************************************************/
/* TYPE DEFINITIONS                                                       */
/**************************************************************************/


/**
 * \addtogroup mcp_sleep_and_wakeup CAN Controller Sleep and Wakeup Functions
 * All necessary functions and means to control power modes of MCP2515 CAN
 * controller.
 * @{
 */

/**
 * \brief MCP2515's waking up reasons from sleep mode
 */
typedef enum
{
   //! wakeup by CAN, do not put MCP2551 to sleep
   INT_SLEEP_WAKEUP_BY_CAN = 0,
   //! wakeup by AVR
   INT_SLEEP_MANUAL_WAKEUP = 1
} eInternalSleepMode;

/*! @} */


/**
 * \brief CAN message format - no extended frame support yet
 */
typedef struct
{
   //! message id (11 bits)
   uint16_t    msgId;
   //! header of CAN message
   struct
   {
      //! remote transmit request frame
      unsigned int rtr : 1;
      //! data length
      unsigned int len : 4;
   } header;
   //! data bytes of CAN message
   uint8_t  data[8];
} can_t;

/**
 * \addtogroup mcp_can_error CAN Error Treatment
 * Functionality to get error status from CAN controller. Error flags will be
 * analysed and result is given by error code.
 * @{
 */

/**
 * \brief CAN error states
 */
typedef enum
{
   //! No Error detected
   CAN_ERR_NO_ERROR     = 0,
   //! Receive Buffer 1 Overflow
   CAN_ERR_RX1_OVERFLOW = 1,
   //! Receive Buffer 0 Overflow
   CAN_ERR_RX0_OVERFLOW = 2,
   //! Bus-Off Error when TEC reaches 255
   CAN_ERR_TX_BUS_OFF   = 3,
   //! Transmit Error-Passive when TEC is equal to or greater than 128
   CAN_ERR_TX_PASSIVE   = 4,
   //! Receive Error-Passive when REC is equal to or greater than 128
   CAN_ERR_RX_PASSIVE   = 5,
   //! Transmit Error Warning when TEC is equal to or greater than 96
   CAN_ERR_TX_WARNING   = 6,
   //! Receive Error Warning when REC is equal to or greater than 96
   CAN_ERR_RX_WARNING   = 7,
   //! Error Warning when TEC or REC is equal to or greater than 96
   CAN_ERR_WARNING      = 8
} can_error_t;

/*! @} */

/**************************************************************************/
/* DEFINITIONS                                                            */
/**************************************************************************/

/**
 * \addtogroup mcp_filters CAN Controller Filter Functions
 * CAN filter functions.
 * @{
 */

/**
 * \def MAX_LENGTH_OF_FILTER_SETUP
 * \brief max number of registers to write a filter or filter mask
 */
#define MAX_LENGTH_OF_FILTER_SETUP        4

/*! @} */

/**
 * \addtogroup mcp_register_access CAN Controller Register Access Functions
 * Access all registers, by reading, writing and bit modification.
 * @{
 */

/**
 * \def MAX_LENGTH_OF_SEQUENTIAL_ACCESS
 * \brief maximum number of registers to write/read in a sequence
 *
 * This means only configuration registers or filters and masks. The CAN
 * messages themselves are read/written seuqntially within the read/write
 * functions.
 */
#define MAX_LENGTH_OF_SEQUENTIAL_ACCESS   12

/*! @} */

/**************************************************************************/
/* MCP2515 REGISTER/INIT FUNCTIONS                                        */
/**************************************************************************/

/**
 * \addtogroup mcp_init CAN Controller Init Functions
 * CAN controller initialisation.
 * @{
 */

/**
 * \brief  initializes MCP2515 selected
 *
 * \par Clock Speed
 * All MCP2515 connected to AVR need to have the same clock speed when
 * using the same bitrate! See array in can_config_mcp2515.c.
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
                      uint8_t mode);

/*! @} */


/**
 * \addtogroup mcp_register_access CAN Controller Register Access Functions
 * Access all registers, by reading, writing and bit modification.
 * @{
 */

/**
 * \brief  write to MCP2515 registers
 *
 * \param  chip      - select chip to use
 * \param  address   - register address of MCP2515
 * \param  data      - data byte
 */
void write_register_mcp2515(eChipSelect   chip,
                            uint8_t       address,
                            uint8_t       data);


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
                                   uint8_t*      data);

/**
 * \brief  read from MCP2515 registers
 *
 * \param  chip      - select chip to use
 * \param  address   - register address of MCP2515
 * \return data      - data byte
 */
uint8_t read_register_mcp2515(eChipSelect chip,
                              uint8_t     address);

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
                        uint8_t     data);


/**
 * \brief  reads MCP2515 status registers
 *
 * \param  chip    - select chip to use
 * \param  command - read quick status command of MCP2515
 * \return value of status register
 */
uint8_t read_status_mcp2515(eChipSelect  chip,
                            uint8_t      command);

/*! @} */


/**
 * \addtogroup mcp_sleep_and_wakeup CAN Controller Sleep and Wakeup Functions
 * All necessary functions and means to control power modes of MCP2515 CAN
 * controller.
 * @{
 */

/**
 * \brief  put MCP2515 (and attached MCP2551) to sleep
 *
 * To put MCP2551 also to sleep, connect RX1BF pin to RS pin of MCP2551. It
 * is not always wanted to wakeup on any CAN activity. Sometimes, with
 * multiple interfaces, the "master bus" should only trigger the wakeup,
 * whereas the "slave" interfaces are woken up by wakeup signal from
 * ATmega.
 *
 * \param  chip - chip to use
 * \param  mode - how/when to activate MCP2515 again
 */
void mcp2515_sleep(eChipSelect         chip,
                   eInternalSleepMode  mode);

/**
 * \brief  wakeup MCP2515 (and attached MCP2551) from sleep mode
 *
 * \param  chip - chip to use
 * \param  mode - how/when to activate MCP2515 again
 *
 * If in manual wakeup mode, a special sequence is needed to wake the
 * MCP2515 up. This is not needed, when activating the controller by CAN
 * bus activity.
 *
 * \note
 * The CAN controller starts in LISTEN ONLY mode after wakeup. The last mode
 * when fully operable will be set after wakeup.
 *
 * \attention
 * The MCP2515 will wake up when bus activity occurs or <b>when the MCU sets,
 * via the SPI interface, the CANINTF.WAKIF bit to 'generate' a wake-up
 * attempt (the CANINTE.WAKIE bit must also be set in order for the wake-up
 * interrupt to occur).</b>
 */
void mcp2515_wakeup(eChipSelect         chip,
                    eInternalSleepMode  mode);

/**
 * \brief  set MCP2515 mode of operation
 *
 * \param  chip - select chip to use
 * \param  mode - mode of operation of MCP2515
 */
void set_mode_mcp2515(eChipSelect   chip,
                      uint8_t       mode);

/*! @} */

/**
 * \addtogroup mcp_filters CAN Controller Filter Functions
 * CAN filter functions.
 * @{
 */

/**
 * \brief clear filters
 * \param chip - select chip to use
 *
 * \note
 * The MCP2515 has to be in configuration mode to set these registers. The
 * function uses sequential write mode to save time and program size.
 *
 * \sa MAX_LENGTH_OF_SEQUENTIAL_ACCESS
 */
void clear_filters(eChipSelect chip);

/**
 * \brief set filters during configuration (static filters)
 * \param chip    - select chip to use
 * \param address - address of filter/mask (start)
 * \param filter  - pointer to filter struct
 *
 * The filter buffer is always MAX_LENGTH_OF_FILTER_SETUP long. The
 * definition is the number of needed filter/masks registers (4).
 *
 * \sa MAX_LENGTH_OF_FILTER_SETUP
 */
void setFilters(eChipSelect chip,
                uint8_t     address,
                uint8_t*    filter);

/*! @} */

/************************************************************************/
/* CAN FUNCTIONS                                                        */
/************************************************************************/

/**
 * \addtogroup mcp_can_access CAN Message Treatment
 * Functions to send/receive CAN messages.
 * @{
 */

/**
 * \brief  send message via CAN
 *
 * \param  chip - select chip to use
 * \param  msg  - pointer to CAN message to send
 * \return address of buffer used to send or 0, if buffer full
 */
uint8_t can_send_message(eChipSelect chip,
                         can_t*      msg);

/**
 * \brief  get received CAN message
 *
 * \param  chip - select chip to use
 * \param  msg  - pointer to CAN message to send
 * \return filter match status + 1
 */
uint8_t can_get_message(eChipSelect chip,
                        can_t*      msg);

/**
 * \brief  checks if any messages are received (via MCP2515's interrupt pin)
 * \param  chip - select chip to use
 * \return true if message was received
 */
bool can_check_message_received(eChipSelect chip);

/**
 * \brief  checks if any tx buffer is free to be loaded with a message
 * \param  chip - select chip to use
 * \return true if a buffer is free
 */
bool can_check_free_tx_buffers(eChipSelect chip);

/**
 * \brief aborting all CAN transmissions
 * \param  chip - select chip to use
 */
void can_abort_all_transmissions(eChipSelect chip);

/*! @} */


/**
 * \addtogroup mcp_can_error CAN Error Treatment
 * Functionality to get error status from CAN controller. Error flags will be
 * analysed and result is given by error code.
 * @{
 */

/**
 * \brief  get TX error state of CAN bus
 * \param  chip - select chip to use
 * \return error state
 *
 * \sa TXBO, TXEP, TXWAR
 */
can_error_t can_get_tx_bus_errors(eChipSelect chip);

/**
 * \brief  get RX error state of CAN bus
 * \param  chip - select chip to use
 * \return error state
 *
 * \sa RX1OVR, RX0OVR, RXEP, RXWAR
 */
can_error_t can_get_rx_bus_errors(eChipSelect chip);

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
can_error_t can_get_general_bus_errors(eChipSelect chip);

/*! @} */

/**************************************************************************/
/* HELPERS                                                                */
/**************************************************************************/

/**
 * \addtogroup mcp_init CAN Controller Init Functions
 * CAN controller initialisation.
 * @{
 */

/**
 * \brief setting up the interrupt pins
 * \param  chip - select chip to use
 */
void setup_interrupt_pins(eChipSelect chip);

/**
 * \brief setting up the chip select pins
 * \param  chip - select chip to use
 */
void setup_cs_pins(eChipSelect chip);

/*! @} */

/**
 * \addtogroup mcp_register_access CAN Controller Register Access Functions
 * Access all registers, by reading, writing and bit modification.
 * @{
 */

/**
 * \brief set chip select for the right chip
 * \param  chip - select chip to use
 */
void set_chip_select(eChipSelect chip);

/**
 * \brief unset chip select for the right chip
 * \param  chip - select chip to use
 */
void unset_chip_select(eChipSelect chip);

/*! @} */

#endif /* CAN_MCP2515_H_ */
