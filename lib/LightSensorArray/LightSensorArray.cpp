#include "LightSensorArray.h"

#define __LSA_GAIN 8
#define __LSA_MAX UINT8_MAX
#define __LSA_SAMPLES 2048

void LSA_Setup(LSA_t *lsa) 
{
}

void LSA_Read(LSA_t *lsa, uint16_t *result)
{
    for (uint8_t i = 0; i < lsa->size; i++) {
        result[i] = analogRead(lsa->pins[i]);
    } 
}