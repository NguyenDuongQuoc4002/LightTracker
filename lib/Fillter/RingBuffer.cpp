#include <RingBuffer.h>


void RingBuff_Set(RingBuffer *rb, uint16_t value) 
{
    rb->sum = (value - rb->buffer[rb->index]) + rb->sum;
    
    rb->buffer[rb->index] = value;
    if(rb->index == rb->size - 1) 
    {
        rb->index = 0;
    } 
    else 
    {
        rb->index++;
    }
    
}

void RingBuff_Setup(RingBuffer *rb) 
{
    rb->sum = 0;
}

uint16_t RingBuff_Median(RingBuffer *rb)
{
    return rb->sum / rb->size;
}