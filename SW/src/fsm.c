
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

#include "fsm.h"
#include "ad9833.h"
#include "lcd.h"
#include "main_screen.h"
#include "menu.h"

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

void fsm_run(void)
{
    fsm_state_set_t state = {START,START,START};
    
    while(1)
    {
        switch(state.current)
        {
        case(START):
            start_app();
            state.next = MAIN_SCREEN;
            break;
        case(MAIN_SCREEN):
            state.next = main_screen_loop(state.last);
            break;
        case(MENU_CH1):
        case(MENU_CH2):
            state.next = menu_loop(state.current,state.last);
            break;
        default:
            state.next = START;
            state.current = DEFAULT;
        }
        state.last = state.current;
        state.current = state.next;
    }
}
