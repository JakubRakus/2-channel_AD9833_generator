
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

#include "encoder.h"
#include "ad9833.h"
#include "lcd.h"
#include "fsm.h"
#include "utils.h"
#include "screen_common.h"
#include "main_screen.h"

#define ACT_FLDS_NUMB   18

static const char wave[3][4] = {"SIN","TRG","SQR"};
static const uint32_t multiplier[7] = {1000000,100000,10000,1000,100,10,1};
static const editable_field_t edit_flds[ACT_FLDS_NUMB] =
{
    {1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0}, //channel 1 frequency
    {11,0},{15,0}, //channel 1 wave shape, channel 1 more options
    {1,1},{2,1},{3,1},{4,1},{5,1},{6,1},{7,1}, //channel 2 frequency
    {11,1},{15,1} //channel 2 wave shape, channel 2 more options
};

static uint8_t active_field;
static char freq_str[2][8];

static void basic_info_show(uint8_t ch)
{
    uint32_to_str(ad9833_get_freq(ch),freq_str[ch],7);
    lcd_write_char(LCD_CH_CH1+ch);
    lcd_write_string(freq_str[ch]);
    lcd_write_string("Hz ");
    lcd_write_string(wave[(uint8_t)ad9833_get_wave(ch)]);
    lcd_write_char(' ');
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
    if((active_field == 8) || (active_field == 17)) return true;
    return false;
}

static void field_edit(int8_t steps)
{
    if(steps != 0)
    {
        //parameters of first channel are placed in first row and second channel in second row
        //so we can get channel number from row number
        uint8_t ch = edit_flds[active_field].row;
        if((active_field < 7) || (active_field > 8 && active_field < 16)) //change frequency
        {
            int32_t f = ad9833_get_freq(ch) + steps * multiplier[active_field - (ch * 9)];
            if(f > 8000000) f = 8000000;
            if(f < 0) f = 0;
            ad9833_set_freq((uint32_t)f,ch);
            uint32_to_str((uint32_t)f,freq_str[ch],7);
            lcd_set_pos(edit_flds[ch * 9].col,edit_flds[ch * 9].row);
            lcd_write_string(freq_str[ch]);
        }
        else if((active_field == 7) || (active_field == 16)) //change wave shape
        {
            uint8_t shape = (uint8_t)ad9833_get_wave(ch);
            shape = (shape + steps + ((INT8_MAX / 3) + 1) * 3) % 3;
            ad9833_set_wave((waveShape_t)shape,ch);
            lcd_write_string(wave[shape]);
        }
        lcd_set_pos(edit_flds[active_field].col,edit_flds[active_field].row);
    }
}

fsm_state_t main_screen_loop(fsm_state_t last_state)
{
    _Bool sw_pos;
    _Bool edit_mode = false;
    _Bool change_screen = false;
    fsm_state_t next_state = MAIN_SCREEN;
    
    lcd_clear();
    basic_info_show(0);
    lcd_set_pos(0,1);
    basic_info_show(1);
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
                //leave main screen and go to channel menu screen
                if(change_screen)
                {
                    //treat row as a channel, like in 'field_edit()'
                    next_state = MENU_CH1 + edit_flds[active_field].row;
                    break;
                }
                //or change mode to field edition
                edit_mode = true;
                lcd_cursor_blink();
                encoder_zero();
            }
        }
    }
    return next_state;
}
