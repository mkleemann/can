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
 * \file can_config_mcp2515_example.h
 *
 * Here you can add the configuration(s) you need. Some of them are not
 * to be changed without the need of adapting the code itself. Most likely
 * any type definitions you find here.
 *
 * \date Created: 28.11.2011 18:35:54
 * \author Matthias Kleemann
 **/



#ifndef CAN_CONFIG_MCP2515_H_
#define CAN_CONFIG_MCP2515_H_

#include "util/util.h"

/**************************************************************************/
/* TYPEDEFINITIONS                                                        */
/*                                                                        */
/* Note: Add here what you need to add, but keep the naming scheme the    */
/*       same. You may need to adapt the source - so be careful.          */
/**************************************************************************/

/**
 * \addtogroup mcp_init CAN Controller Init Functions
 * CAN controller initialisation.
 * @{
 */

/**
 * \brief index of internal CAN bitrate setup
 *
 * The bitrate enum is directly connected to the CNF array in the configuration
 * source file (can_config_mcp2515.c).
 */
typedef enum
{
   //! 100kbps
   CAN_BITRATE_100_KBPS = 0,
   //! 125kbps
   CAN_BITRATE_125_KBPS = 1,
   //! maximum index of possible CAN bitrates
   NUM_OF_CAN_BITRATES  = 2         // always the last one!
} eCanBitRate;

/**
 * \brief index of MCP2515 chips connected
 *
 * The chips are "named" here, so the selection can be done via function
 * parameters. The CS and INT port macros depend on the enumeration.
 */
typedef enum
{
   //! chip 1 (master CAN)
   CAN_CHIP1      = 0,
   //! chip 2 (slave CAN)
   CAN_CHIP2      = 1,
   //! always the last one!
   NUM_OF_MCP2515 = 2
} eChipSelect;

/**************************************************************************/
/* SETTINGS                                                               */
/**************************************************************************/

// Port definitions to access the defined MCP2515

/**
 * \def CAN_CS_PORTS
 * \brief definition of cs port pins for each can chip
 *
 * These pins are used for chip select signal to each MCP2515. This
 * structure has to correspond with the chip select enumeration.
 * \sa eChipSelect
 */
#define CAN_CS_PORTS  SET_PORT_PTR(B,2), \
                      SET_PORT_PTR(B,1)

/**
 * \def CAN_INT_PORTS
 * \brief definition of int port pins for each can chip
 *
 * These pins are used for interrupt signal of each MCP2515. This
 * structure has to correspond with the chip select enumeration.
 * \sa eChipSelect
 */
#define CAN_INT_PORTS SET_PORT_PTR(D,2), \
                      SET_PORT_PTR(D,3)

/*! @} */


/**************************************************************************/

/**************************************************************************/
/* GETTER                                                                 */
/**************************************************************************/

/**
 * \brief get pointer to configuration
 * \param bitrate to be used
 * \return pointer to configuration struct
 */
uint8_t * getCanConfiguration(eCanBitRate bitrate);

/**
 * \brief get the CS port structure
 * \param chip selected
 * \return pointer to structure
 */
portaccess_t * getCSPort(eChipSelect chip);

/**
 * \brief get the INT port structure
 * \param chip selected
 * \return pointer to structure
 */
portaccess_t * getINTPort(eChipSelect chip);

#endif /* CAN_CONFIG_MCP2515_H_ */
