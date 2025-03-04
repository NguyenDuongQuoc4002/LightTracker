#include <Arduino.h>
#define RING_BUFF_NOT_READY 0x0
#define RING_BUFF_READY 0x1


struct RingBuffer {
    // Number of node in the ring
    uint16_t size;

    // The buffer data vector
    uint16_t *buffer;

    // The buffer index
    uint16_t index;

    // Indicate if the ring has full data
    uint8_t ready;

    // Median value of the ring
    u_int32_t sum;
};

/**
 * Write the value to the ring
 */
void RingBuff_Set(RingBuffer *rb, uint16_t value);

/**
 * Initialize the ring data
 */
void RingBuff_Setup(RingBuffer *rb);

uint16_t RingBuff_Median(RingBuffer *rb);