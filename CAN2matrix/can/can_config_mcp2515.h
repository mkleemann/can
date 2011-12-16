/*
 * can_config_mcp2515.h
 *
 * Here you can add the configuration(s) you need. Some of them are not
 * to be changed without the need of adapting the code itself. Most likely
 * any type definitions you find here.
 *
 * Created: 28.11.2011 18:35:54
 *  Author: MKleemann
 */


#ifndef CAN_CONFIG_MCP2515_H_
#define CAN_CONFIG_MCP2515_H_

/**************************************************************************/
/* TYPEDEFINITIONS                                                        */
/*                                                                        */
/* Note: Add here what you need to add, but keep the naming scheme the    */
/*       same. You may need to adapt the source - so be careful.          */
/**************************************************************************/

/* @brief index of internal CAN bitrate setup
 *
 * Any adaption here may need to adapt the source. If you keep the naming
 * scheme like CAN_BITRATE_xxx_KBPS, it's easier because of existing macros.
 */
typedef enum
{
   CAN_BITRATE_100_KBPS = 0,
   CAN_BITRATE_125_KBPS = 1,
   NUM_OF_CAN_BITRATES  = 3         // always the last one!
} eCanBitRate;

/* @brief index of MCP2515 chips connected
 *
 * Any adaption here may need to adapt the source. If you keep the naming
 * scheme like CAN_CHIPx, it's easier because of existing macros.
 */
typedef enum
{
   CAN_CHIP1      = 0,
   CAN_CHIP2      = 1,
   NUM_OF_MCP2515 = 3               // always the last one!
} eChipSelect;

/* type of chip select control struct
 */
typedef struct { pvuint8_t ddr;
                 pvuint8_t port;
                 uint8_t   pin;
               } csType;


/**************************************************************************/
/* SETTINGS                                                               */
/**************************************************************************/

/* @brief Oscillator frequency used for MCP2515
 */
#ifndef MCP_CLOCK          // clock rate of MCP2515
   #define MCP_CLOCK       4000000UL
#endif // MCP_CLOCK

/* @brief Chip Select pins of the chips set above
 */

/* define global array to access chip select pins directly via port address
 */
static csType csPins[NUM_OF_MCP2515] = { {&DDR(B), &PORT(B), 0},    // 0
                                         {&DDR(B), &PORT(B), 1}     // NUM_OF_MCP2515 - 1
                                       };



#endif /* CAN_CONFIG_MCP2515_H_ */