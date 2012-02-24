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
 * CAN2matrix.h
 *
 * Created: 28.11.2011 18:13:35
 *  Author: MKleemann
 */


#ifndef CAN2MATRIX_H_
#define CAN2MATRIX_H_

/***************************************************************************/
/* TYPE DEFINITIONS                                                        */
/***************************************************************************/
typedef enum
{
   INIT           = 0,
   RUNNING        = 1,
   SLEEP_DETECTED = 2,
   SLEEPING       = 3,
   WAKEUP         = 4,
   ERROR          = 5
} state_t;

/***************************************************************************/
/* DEFINITIONS                                                             */
/***************************************************************************/

/*** DEBUGGING *************************************************************/

// use this to cut off all CAN handling
//#define ___SIMULATION___

// use only CAN1 - read messages and put them back on bus with msgId += 10
//#define ___SINGLE_CAN___

/***************************************************************************/
/* INT0 trigger definition                                                 */
/*                                                                         */
/* ISC01 ISC00 Description                                                 */
/*     0     0 The low level of INT0 generates an interrupt request        */
/*     0     1 Any logical change on INT0 generates an interrupt request   */
/*     1     0 The falling edge of INT0 generates an interrupt request     */
/*     1     1 The rising edge of INT0 generates an interrupt request      */
/***************************************************************************/
#define EXTERNAL_INT0_TRIGGER    0
#define EXTERNAL_INT0_ENABLE     (1 << INT0)

/***************************************************************************/
/* INT1 trigger definition                                                 */
/*                                                                         */
/* ISC11 ISC10 Description                                                 */
/*     0     0 The low level of INT1 generates an interrupt request        */
/*     0     1 Any logical change on INT1 generates an interrupt request   */
/*     1     0 The falling edge of INT1 generates an interrupt request     */
/*     1     1 The rising edge of INT1 generates an interrupt request      */
/***************************************************************************/
//#define EXTERNAL_INT1_TRIGGER    (1 << ISC11)
//#define EXTERNAL_INT1_ENABLE     (1 << INT1)

/***************************************************************************/
/* AVR sleep modes: power down                                             */
/*                                                                         */
/* SM2 SM1 SM0 Sleep Mode                                                  */
/*   0   0   0 Idle                                                        */
/*   0   0   1 ADC Noise Reduction                                         */
/*   0   1   0 Power-down                                                  */
/*   0   1   1 Power-save                                                  */
/*   1   1   0 Standby                                                     */
/***************************************************************************/
//#define AVR_SLEEP_MODE           (1 << SM1)
#define AVR_SLEEP_MODE           SLEEP_MODE_PWR_DOWN

/***************************************************************************/
/* STATES OF FSM                                                           */
/***************************************************************************/

/**
 * @brief Go to sleep mode. Deactivate CAN and set the sleep mode.
 */
void sleepDetected(void);


/**
 * @brief enter AVR sleep mode
 */
void sleeping(void);

/**
 * @brief wake up CAN and reinitialize the timers
 */
void wakeUp(void);

/**
 * @brief do all the work.
 */
void run(void);

/**
 * @brief Error state. Call this when an illegal state is reached.
 */
void errorState(void);

/**
 * @brief Initialize LED, Timer and SPI.
 */
void initHardware(void);

/**
 * @brief Initialize the CAN controllers
 *
 * @return true if all is ok. Otherwise false is returned.
 */
bool initCAN(void);

/***************************************************************************/
/* HELPER ROUTINES                                                         */
/***************************************************************************/

#ifndef ___SIMULATION___
/**
 * @brief handles CAN1 reception
 * @param pointer to message struct
 */
void handleCan1Reception(can_t* msg);

/**
 * @brief handles CAN2 reception
 * @param pointer to message struct
 */
void handleCan2Reception(can_t* msg);

/**
 * @brief handle CAN1 transmission
 * @param pointer to message struct
 */
void handleCan1transmission(can_t* msg);

/**
 * @brief handle CAN2 transmission
 * @param pointer to message struct
 */
void handleCan2transmission(can_t* msg);

/**
 * @brief sends message to CAN2 and filling up converted data
 *
 * Note: Set message id before calling this function.
 *
 * @param pointer to CAN message
 */
void sendCan2Message(can_t* msg);
#endif

#endif /* CAN2MATRIX_H_ */