
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

#include "encoder.h"
#include "ad9833.h"
#include "lcd.h"
#include "fsm.h"
#include "menu.h"

fsm_state_t menu_loop(fsm_state_t last_state)
{
    return last_state;
}
