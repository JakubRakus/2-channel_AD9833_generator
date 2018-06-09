#ifndef LCD_H_INCLUDED
#define LCD_H_INCLUDED

#define LCD_CTRL_DDR    DDRD
#define LCD_CTRL_PORT   PORTD
#define LCD_RS          _BV(6)
#define LCD_EN          _BV(7)

#define LCD_DATA_DDR    DDRC
#define LCD_DATA_PORT   PORTC
#define LCD_DATA_LSB    _BV(0)
#define LCD_DATA_PINS   (LCD_DATA_LSB|(LCD_DATA_LSB<<1)|(LCD_DATA_LSB<<2)|(LCD_DATA_LSB<<3))

#define LCD_CH_RARROW   0x7E
#define LCD_CH_LARROW   0x7F

void lcd_write_cmd(uint8_t cmd);
void lcd_write_char(char ch);
void lcd_write_string(const char *str);
void lcd_clear(void);
void lcd_set_pos(uint8_t col,
                 uint8_t row);
void lcd_set_character(uint8_t number,
                       uint8_t *tab);
void lcd_go_home(void);
void lcd_cursor_blink(void);
void lcd_cursor_static(void);
void lcd_cursor_hide(void);
void lcd_init(void);

#endif // LCD_H_INCLUDED
