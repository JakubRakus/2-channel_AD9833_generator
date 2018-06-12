
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

#include "fsm.h"
#include "ad9833.h"
#include "lcd.h"
#include "screen.h"

static inline void start_app(void)
{
    ad9833_init();
    lcd_init();
    
    lcd_write_string("AD9833 2-channel");
    lcd_set_pos(0,1);
    lcd_write_string("   generator    ");
    _delay_ms(2000);

    ad9833_set_freq(1000,0);
    ad9833_set_freq(1000,1);
    ad9833_set_phase(0,0);
    ad9833_set_phase(0,1);
    ad9833_reset(false);
}

void fsm_run(fsm_state_t first_state)
{
    fsm_state_t state = first_state;
    fsm_state_t last_state = DEFAULT;
    while(1)
    {
        switch(state)
        {
        case(START):
            start_app();
            state = MAIN_SCREEN;
            last_state = START;
            break;
        case(MAIN_SCREEN):
            state = screen_loop(last_state);
            last_state = MAIN_SCREEN;
            break;
        case(MENU):
            state = MAIN_SCREEN;
            last_state = MENU;
            break;
        default:
            state = START;
            last_state = DEFAULT;
        }
    }
}
