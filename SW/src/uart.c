
#include <avr/io.h>

#include "uart.h"

void uart_init(void)
{
    UBRR0H = 0; //baudrate 250kbps, UBRR0=(fSYS/16/250000)-1=3
    UBRR0L = 3;
    UCSR0B = _BV(RXEN0)|_BV(TXEN0); //enable receiver and transmitter
    UCSR0C = _BV(UCSZ00)|_BV(UCSZ01); //8 data bits, 1 stop bit
}

void uart_send_char(char ch)
{
    while(!(UCSR0A & _BV(UDRE0))); //wait for empty buffer
    UDR0 = ch;
}

void uart_send_string(const char *str)
{
    while(*str) uart_send_char(*str++);
}
