#include <Arduino.h>
#include <Led.h>
#include <LightSensorArray.h>
#include <RingBuffer.h>

#define BUILTIN_LED_PIN GPIO_NUM_2
#define SENSOR_NUM 5
#define SENSOR_SAMPLES 256


Led_t builtinLed = { .pin = BUILTIN_LED_PIN, .state = LOW };
Led_t led1 = { .pin = 13, .state = LOW };

uint8_t lsapins[SENSOR_NUM] = { GPIO_NUM_35,  GPIO_NUM_33, GPIO_NUM_34,  GPIO_NUM_32,  GPIO_NUM_25 };

LSA_t lsa = {
    .pins = lsapins,
    .size = SENSOR_NUM, 
};
uint16_t result[SENSOR_NUM] = { 0 };

//Ring Buffer
uint16_t buffer1[SENSOR_SAMPLES] = { 0 };
RingBuffer rb1 = {.size = SENSOR_SAMPLES, .buffer = buffer1, .index = 0, .ready = RING_BUFF_NOT_READY}; 

uint16_t buffer2[SENSOR_SAMPLES] = { 0 };
RingBuffer rb2 = {.size = SENSOR_SAMPLES, .buffer = buffer2, .index = 0, .ready = RING_BUFF_NOT_READY}; 

uint16_t buffer3[SENSOR_SAMPLES] = { 0 };
RingBuffer rb3 = {.size = SENSOR_SAMPLES, .buffer = buffer3, .index = 0, .ready = RING_BUFF_NOT_READY}; 

uint16_t buffer4[SENSOR_SAMPLES] = { 0 };
RingBuffer rb4 = {.size = SENSOR_SAMPLES, .buffer = buffer4, .index = 0, .ready = RING_BUFF_NOT_READY}; 

uint16_t buffer5[SENSOR_SAMPLES] = { 0 };
RingBuffer rb5 = {.size = SENSOR_SAMPLES, .buffer = buffer5, .index = 0, .ready = RING_BUFF_NOT_READY}; 


void setup() {
    Serial.begin(115200);

    Led_Setup(&builtinLed);
    Led_Setup(&led1);
    LSA_Setup(&lsa);

    RingBuff_Setup(&rb1);
    RingBuff_Setup(&rb2);
    RingBuff_Setup(&rb3);
    RingBuff_Setup(&rb4);
    RingBuff_Setup(&rb5);
}

void loop() {
    // Led_Toggle(&builtinLed);
    // Led_Toggle(&led1);

    LSA_Read(&lsa, result);
    // Serial.printf("Result: %d, %d, %d, %d, %d\n", result[0], result[1], result[2], result[3], result[4]); 

    
    RingBuff_Set(&rb1, result[0]);
    u_int16_t med0 = RingBuff_Median(&rb1);
    
    RingBuff_Set(&rb2, result[1]);
    u_int16_t med1 = RingBuff_Median(&rb2);

    RingBuff_Set(&rb3, result[2]);
    u_int16_t med2 = RingBuff_Median(&rb3);

    RingBuff_Set(&rb4, result[3]);
    u_int16_t med3 = RingBuff_Median(&rb4);

    RingBuff_Set(&rb5, result[4]);
    u_int16_t med4 = RingBuff_Median(&rb5);


    Serial.printf("%d, %d, %d, %d, %d\n", med0, med1, med2, med3, med4);

    delay(1);
    
    return;

}
