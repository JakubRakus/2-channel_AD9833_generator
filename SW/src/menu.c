
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

#include "encoder.h"
#include "ad9833.h"
#include "lcd.h"
#include "fsm.h"
#include "utils.h"
#include "screen_common.h"
#include "menu.h"

#define ACT_FLDS_NUMB   4

static const uint32_t multiplier[3] = {100,10,1};
static const editable_field_t edit_flds[ACT_FLDS_NUMB] =
{
    {4,0},{5,0},{6,0}, //phase
    {15,1} //more options
};

static uint8_t channel;
static uint8_t active_field;
static char phase_str[4];

static void additional_info_show(void)
{
    uint32_to_str(ad9833_get_phase(channel),phase_str,3);
    lcd_write_char(LCD_CH_CH1+channel);
    lcd_write_char(' ');
    lcd_write_char(LCD_CH_PHI);
    lcd_write_char(':');
    lcd_write_string(phase_str);
    lcd_write_char(LCD_CH_DEGREE);
    lcd_set_pos(15,1);
    lcd_write_char(LCD_CH_RARROW);
}

static _Bool field_move(int8_t steps)
{
    if(steps != 0)
    {
        active_field = (active_field + steps + ((INT8_MAX / ACT_FLDS_NUMB) + 1) * ACT_FLDS_NUMB) % ACT_FLDS_NUMB;
        lcd_set_pos(edit_flds[active_field].col,edit_flds[active_field].row);
    }
    //cursor at 'change screen' field
    if(active_field == 3) return true;
    return false;
}

static void field_edit(int8_t steps)
{
    if(steps != 0)
    {
        if(active_field < 3) //change phase
        {
            int16_t p = ad9833_get_phase(channel) + steps * multiplier[active_field];
            if(p > 360) p = 360;
            if(p < 0) p = 0;
            ad9833_set_phase((uint16_t)p,channel);
            uint32_to_str((uint32_t)p,phase_str,3);
            lcd_set_pos(edit_flds[0].col,edit_flds[0].row);
            lcd_write_string(phase_str);
        }
        lcd_set_pos(edit_flds[active_field].col,edit_flds[active_field].row);
    }
}

fsm_state_t menu_loop(fsm_state_t current_state,
                      fsm_state_t last_state)
{
    _Bool sw_pos;
    _Bool edit_mode = false;
    _Bool change_screen = false;
    
    channel = 0;
    if(current_state == MENU_CH2) channel = 1;
    
    lcd_clear();
    additional_info_show();
    active_field = 0;
    lcd_set_pos(edit_flds[active_field].col,edit_flds[active_field].row);
    lcd_cursor_static();
    encoder_zero();
    while(1)
    {
        if(edit_mode == true)
        {
            field_edit(encoder_get_rotation());
            sw_pos = encoder_get_switch();
            _delay_ms(10);
            if(sw_pos == false && encoder_get_switch() == true)
            {
                //change mode to cursor moving
                edit_mode = false;
                lcd_cursor_static();
                encoder_zero();
            }
        }
        else
        {
            change_screen = field_move(encoder_get_rotation());
            sw_pos = encoder_get_switch();
            _delay_ms(10);
            if(sw_pos == false && encoder_get_switch() == true)
            {
                //leave channel menu screen and go back to main screen
                if(change_screen) break;
                //or change mode to field edition
                edit_mode = true;
                lcd_cursor_blink();
                encoder_zero();
            }
        }
    }
    return last_state;
}
