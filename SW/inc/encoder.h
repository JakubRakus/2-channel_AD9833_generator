#ifndef ENCODER_H_INCLUDED
#define ENCODER_H_INCLUDED

#define ENCODER_DDR     DDRD
#define ENCODER_PIN     PIND
#define ENCODER_A       _BV(3)
#define ENCODER_B       _BV(2)
#define ENCODER_SW      _BV(4)

void encoder_init(void);
_Bool encoder_get_switch(void);
int8_t encoder_get_rotation(void);
void encoder_zero(void);

#endif // ENCODER_H_INCLUDED
