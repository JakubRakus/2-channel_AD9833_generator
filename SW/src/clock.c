
#include <avr/io.h>

void clock_init(void)
{
    CLKPR = _BV(CLKPCE); //enable main clock prescaler change
    CLKPR = 0x00; //set prescaler to 1 (CLKPS[3:0]=0000), fSYS=16MHz
}
