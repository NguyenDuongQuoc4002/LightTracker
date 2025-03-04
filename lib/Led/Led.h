#ifndef  __SPX_LED_DRIVER
#define __SPX_LED_DRIVER

#include "Arduino.h"
typedef struct Led {
    uint8_t pin;
    uint8_t state;
} Led_t;

void Led_Toggle(Led_t *led);
void Led_Setup(Led_t *led);

#endif