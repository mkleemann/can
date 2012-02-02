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
 * uart_config.h
 *
 * Created: 28.11.2011 18:17:15
 *  Author: MKleemann
 */


#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

// USART is setup without interrupt usage!

// set numeric values as UL, otherwise errors may occur in any calculation
#ifndef UART_BAUDRATE  // setup a default baud rate, if not yet set otherwise
   #define UART_BAUDRATE  9600UL
#endif // UART_BAUDRATE

// definition of a newline on various OSs
// Windows: "rn"
// Linux  : "n"
// MacOS  : "r"
#define CR "\r\n"


#endif /* UART_CONFIG_H_ */
