#ifndef HD44780_H_INCLUDED
#define HD44780_H_INCLUDED

#define HD44780_CLR_DISP            0x01
#define HD44780_RET_HOME            0x02

#define HD44780_EM_DEC              0x04
#define HD44780_EM_INC              0x04|_BV(1)
#define HD44780_EM_SHIFT_CUR        0x04
#define HD44780_EM_SHIFT_DISP       0x04|_BV(0)
    
#define HD44780_DCTRL_DISP_OFF      0x08
#define HD44780_DCTRL_DISP_ON       0x08|_BV(2)
#define HD44780_DCTRL_CUR_OFF       0x08
#define HD44780_DCTRL_CUR_ON        0x08|_BV(1)
#define HD44780_DCTRL_CUR_NOBLINK   0x08
#define HD44780_DCTRL_CUR_BLINK     0x08|_BV(0)
    
#define HD44780_SHIFT_CURSOR        0x10
#define HD44780_SHIFT_DISPLAY       0x10|_BV(3)
#define HD44780_SHIFT_LEFT          0x10
#define HD44780_SHIFT_RIGHT         0x10|_BV(2)
    
#define HD44780_FUNC_BUS_4          0x20
#define HD44780_FUNC_BUS_8          0x20|_BV(4)
#define HD44780_FUNC_LINE_1         0x20
#define HD44780_FUNC_LINE_2         0x20|_BV(3)
#define HD44780_FUNC_DOTS_8         0x20
#define HD44780_FUNC_DOTS_10        0x20|_BV(2)
    
#define HD44780_CGRAM_SET           0x40
#define HD44780_DDRAM_SET           0x80

#endif // HD44780_H_INCLUDED
