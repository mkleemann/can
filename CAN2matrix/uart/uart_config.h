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

#ifndef F_CPU     // setup a default CPU clock rate, if not set yet
   #warning "F_CPU was not defined yet, and is now set here to some default value!"
   #define F_CPU     4000000UL
#endif // F_CPU

// calculate UBRRH/UBRRL register values
#define R_UBRR     ((F_CPU + UART_BAUDRATE * 8)/(16 * UART_BAUDRATE) - 1)
#define BAUD_REAL  (F_CPU/(16*(R_UBRR + 1)))            // real baudrate
#define BAUD_ERROR ((BAUD_REAL * 1000) / UART_BAUDRATE) // error in per mill, 1000 = no error

#if ((BAUD_ERROR<990) || (BAUD_ERROR>1010))
  #error Systematic error. Baudrate is more than 1%, which is too high!
#endif

// definition of a newline on various OSs
// Windows: "rn"
// Linux  : "n"
// MacOS  : "r"
#define CR "\r\n"



#endif /* UART_CONFIG_H_ */