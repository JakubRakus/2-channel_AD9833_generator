
#include <avr/io.h>
#include <avr/wdt.h>

#include "fsm.h"
#include "clock.h"
#include "uart.h"
#include "spi.h"
#include "encoder.h"

int main(void)
{
    //init base peripherals
    wdt_disable();
    clock_init();
    uart_init();
    spi_init();
    encoder_init();
    
    //run finite state machine
    fsm_run();
    
    //we should never reach here
    wdt_enable(WDTO_15MS);
    while(1);
}
