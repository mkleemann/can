/*
 * leds_config.h
 *
 * Created: 28.11.2011 18:18:23
 *  Author: MKleemann
 */


#ifndef LEDS_CONFIG_H_
#define LEDS_CONFIG_H_

// define LEDs connected to your controller - name them as you wish, but keep
// in mind that it matches the port/pin definitions below.
enum eLED
{
   rxLED = 0,
   txLED,
   led3,
   led4
};

// number of LEDS defined above in eLEDs
#define NUM_OF_LEDS  4

// type of led control struct
typedef struct { pvuint8_t ddr;
                 pvuint8_t port;
                 uint8_t   pin;
               } ledType;

// define global array to access port pins directly via port address
// dim1: port address
// dim2: pin
ledType ledPins[NUM_OF_LEDS] = { {&DDR(D), &PORT(D), 1},    // 0
                                 {&DDR(D), &PORT(D), 2},
                                 {&DDR(C), &PORT(C), 1},
                                 {&DDR(C), &PORT(C), 2}     // NUM_OF_LEDS - 1
                               };

#endif /* LEDS_CONFIG_H_ */