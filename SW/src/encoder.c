
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#include "encoder.h"
#include "uart.h"

static int8_t rotation;

ISR(INT0_vect)
{
    if(ENCODER_PIN & ENCODER_A) rotation--;
    else rotation++;
}

void encoder_init(void)
{
    ENCODER_DDR &= ~(ENCODER_A|ENCODER_B|ENCODER_SW); //all encoder lines as inputs
    EICRA = _BV(ISC01)|_BV(ISC00); //INT0 - rising edge (INT0 pin = ENCODER_B pin)
    EIMSK = _BV(INT0); //enable INT0
    rotation = 0;
    sei(); //enable interrupts
}

_Bool encoder_get_switch(void)
{
    return ENCODER_PIN & ENCODER_SW;
}

int8_t encoder_get_rotation(void)
{
    cli();
    int8_t temp = rotation;
    rotation = 0;
    sei();
    return temp;
}

void encoder_zero(void)
{
    cli();
    rotation = 0;
    sei();
}
