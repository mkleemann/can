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
   #define UART_BAUDRATE  38400UL
#endif // UART_BAUDRATE

#ifndef F_CPU     // setup a default CPU clock rate, if not set yet
   #define F_CPU     4000000UL
#endif // F_CPU

// calculate UBRRH/UBRRL register values
#define R_UBRR    (uint16_t) ((uint32_t) F_CPU/(16 * UART_BAUDRATE) - 1)

// definition of a newline on various OSs
// Windows: "rn"
// Linux  : "n"
// MacOS  : "r"
#define CR "\r\n"



#endif /* UART_CONFIG_H_ */