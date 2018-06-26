
#include <avr/io.h>

#include "utils.h"

void uint32_to_str(uint32_t numb,
                   char *str,
                   uint8_t len)
{
    str[len] = 0;
    while(len--)
    {
        str[len] = (numb % 10) + 48;
        numb /= 10;
        if(numb == 0) break;
    }
    while(len--) str[len] = ' ';
}
