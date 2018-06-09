
#include <avr/io.h>

#include "spi.h"

void spi_init(void)
{
    //PB3 - SPI MOSI, out, high; PB5 - SPI SCK, out, high
    DDRB |= _BV(3)|_BV(5);
    PORTB |= _BV(3)|_BV(5);
    SPSR = _BV(SPI2X); //double SPI speed, fSCK=fSYS/2=8MHz
    SPCR = _BV(SPE)|_BV(CPOL)|_BV(MSTR); //enable SPI in master mode, CPOL=1, CPHA=0
}

void spi_send_word(uint16_t *data)
{
    SPDR = (uint8_t)(*data >> 8);
    while(!(SPSR & _BV(SPIF)));
    SPDR = (uint8_t)(*data);
    while(!(SPSR & _BV(SPIF)));
}
