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


/**************************************************************************/
/* SETTINGS                                                               */
/**************************************************************************/

/* @brief Oscillator frequency used for MCP2515
 *
 * NOT YET USED!
 */
#ifndef MCP_CLOCK          // clock rate of MCP2515
   #define MCP_CLOCK       4000000UL
#endif // MCP_CLOCK

/* @brief Port definitions to access the two MCP2515
 */
#define CHIP1_CS_PIN       B,2
#define CHIP1_INT_PIN      D,2

#define CHIP2_CS_PIN       B,1
#define CHIP2_INT_PIN      D,3

#endif /* CAN_CONFIG_MCP2515_H_ */