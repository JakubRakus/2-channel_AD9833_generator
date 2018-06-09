
#include <avr/io.h>

#include "fsm.h"
#include "clock.h"
#include "uart.h"
#include "spi.h"
#include "encoder.h"

int main(void)
{
    //init base periherals
    clock_init();
    uart_init();
    spi_init();
    encoder_init();
    
    //start finite state machine
    fsm_run(START);
    
    //we should never reach here
    while(1);
}
