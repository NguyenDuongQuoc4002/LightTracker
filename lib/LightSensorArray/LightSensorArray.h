#ifndef __LIGHT_SENSOR_ARRAY
#define __LIGHT_SENSOR_ARRAY

#include "Arduino.h"

typedef struct LSA {
    uint8_t *pins;
    uint8_t size;
} LSA_t;

void LSA_Setup(LSA_t *lsa);
void LSA_Read(LSA_t *lsa, uint16_t *result);

#endif // __LIGHT_SENSOR_ARRAY