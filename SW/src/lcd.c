
#include <avr/io.h>
#include <util/delay.h>

#include "lcd.h"
#include "hd44780.h"

static const uint8_t custom_chars[24] = 
{
    0x00,0x00,0x08,0x15,0x15,0x02,0x00,0x00, //sinus
    0x00,0x00,0x07,0x05,0x05,0x1D,0x00,0x00, //square
    0x00,0x00,0x00,0x04,0x0A,0x11,0x00,0x00  //triangle
};

static inline void ctrl_hi(uint8_t pins)
{
    LCD_CTRL_PORT |= pins;
}

static inline void ctrl_lo(uint8_t pins)
{
    LCD_CTRL_PORT &= ~pins;
}

static void write_nibble(uint8_t nibble)
{
    ctrl_hi(LCD_EN);
    LCD_DATA_PORT = (LCD_DATA_PORT & ~(LCD_DATA_PINS)) | ((nibble << (LCD_DATA_LSB - 1)) & LCD_DATA_PINS);
    ctrl_lo(LCD_EN);
}

static void write_custom_chars(const uint8_t* tab)
{
    uint8_t i = 24;
    
    lcd_write_cmd(HD44780_CGRAM_SET);
    while(i--) lcd_write_char(*tab++);
    //set internal pointer back to address of first visible character
    lcd_go_home();
}

void lcd_write_cmd(uint8_t cmd)
{
    ctrl_lo(LCD_RS); //RS line low -> command mode
    write_nibble(cmd >> 4);
    write_nibble(cmd);
    _delay_us(40);
    ctrl_hi(LCD_RS);
}

void lcd_write_char(char ch)
{
    write_nibble(ch >> 4);
    write_nibble(ch);
    _delay_us(40);
}

void lcd_write_string(const char* str)
{
    while(*str) lcd_write_char(*str++);
}

void lcd_clear(void)
{
    lcd_write_cmd(HD44780_CLR_DISP);
    _delay_us(1500);
}

void lcd_set_pos(uint8_t col,
                 uint8_t row)
{
    lcd_write_cmd(HD44780_DDRAM_SET | (col + (0x40 * row)));
}

void lcd_go_home(void)
{
    lcd_write_cmd(HD44780_RET_HOME);
    _delay_ms(2);
}

void lcd_cursor_blink(void)
{
    lcd_write_cmd(HD44780_DCTRL_DISP_ON | HD44780_DCTRL_CUR_ON | HD44780_DCTRL_CUR_BLINK);
}

void lcd_cursor_static(void)
{
    lcd_write_cmd(HD44780_DCTRL_DISP_ON | HD44780_DCTRL_CUR_ON | HD44780_DCTRL_CUR_NOBLINK);
}

void lcd_cursor_hide(void)
{
    lcd_write_cmd(HD44780_DCTRL_DISP_ON | HD44780_DCTRL_CUR_OFF | HD44780_DCTRL_CUR_NOBLINK);
}

void lcd_init(void)
{
    LCD_DATA_DDR |= LCD_DATA_PINS; //all LCD lines as outputs
    LCD_CTRL_DDR |= (LCD_EN|LCD_RS);
    LCD_DATA_PORT &= ~(LCD_DATA_PINS); //set all LCD lines low
    ctrl_lo(LCD_EN|LCD_RS);

    //switch from default 8-bit mode to 4-bit mode
    write_nibble(0x03);
    _delay_ms(5);
    write_nibble(0x03);
    _delay_us(160);
    write_nibble(0x03);
    _delay_us(160);
    write_nibble(0x02);
    _delay_ms(1);
    
    //4-bit interface, 2 lines, characters 8 dots height
    lcd_write_cmd(HD44780_FUNC_DOTS_8 | HD44780_FUNC_LINE_2 | HD44780_FUNC_BUS_4);
    lcd_write_cmd(HD44780_DCTRL_DISP_OFF);
    lcd_clear();
    //cursor position and DDRAM adress increments automatically
    lcd_write_cmd(HD44780_EM_SHIFT_CUR | HD44780_EM_INC);
    lcd_cursor_hide();
    //write characters to CGRAM
    write_custom_chars(custom_chars);
}
