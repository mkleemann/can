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
   NUM_OF_CAN_BITRATES  = 2         // always the last one!
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
   NUM_OF_MCP2515 = 2               // always the last one!
} eChipSelect;

/* type of atmega pin control struct
 */
typedef struct
{
   pvuint8_t ddr;
   pvuint8_t port;
   uint8_t   pin;
} pinType;


/**************************************************************************/
/* SETTINGS                                                               */
/**************************************************************************/

/* @brief Oscillator frequency used for MCP2515
 */
#ifndef MCP_CLOCK          // clock rate of MCP2515
   #define MCP_CLOCK       4000000UL
#endif // MCP_CLOCK

/* define global array to access chip select pins directly via port address
 */
static pinType csPins[NUM_OF_MCP2515] = { {&DDR(B), &PORT(B), PINB0},    // 0
                                          {&DDR(B), &PORT(B), PINB1}     // NUM_OF_MCP2515 - 1
                                        };

/* define global array to access RX interrupt pins directly via port address
 */
static pinType intPins[NUM_OF_MCP2515] = { {&DDR(D), &PORT(D), PIND2},    // 0
                                           {&DDR(D), &PORT(D), PIND3}     // NUM_OF_MCP2515 - 1
                                         };



#endif /* CAN_CONFIG_MCP2515_H_ */