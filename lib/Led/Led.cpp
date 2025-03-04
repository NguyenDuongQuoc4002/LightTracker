#include "Led.h"

void Led_Toggle(struct Led *led) {
    if (led->state == LOW) {
        led->state = HIGH;
    } else {
        led->state = LOW;
    }
    digitalWrite(led->pin, led->state);
}

void Led_Setup(struct Led *led) {
    pinMode(led->pin, OUTPUT);
}