
#include <avr/io.h>

#include "utils.h"

void uint32_to_str(uint32_t numb,
                   char* str,
                   uint8_t len)
{
    str[len] = 0;
    while(len)
    {
        str[--len] = (numb % 10) + 48;
        numb /= 10;
        if(numb == 0) break;
    }
    while(len) str[--len] = ' ';
}

void int16_to_str(int16_t numb,
                  char* str,
                  uint8_t len_with_sign,
                  _Bool show_plus,
                  _Bool sign_leftmost)
{
    char sign = ' ';
    
    if(numb < 0)
    {
        numb *= (int16_t)-1;
        sign = '-';
    }
    else if((numb > 0) && show_plus) sign = '+';

    str[len_with_sign] = 0;
    while(len_with_sign)
    {
        str[--len_with_sign] = (numb % 10) + 48;
        numb /= 10;
        if(numb == 0) break;
    }
    if(sign_leftmost)
    {
        while(len_with_sign > 1) str[--len_with_sign] = ' ';
        str[--len_with_sign] = sign;
    }
    else
    {
        str[--len_with_sign] = sign;
        while(len_with_sign) str[--len_with_sign] = ' ';
    }
}
