#ifndef AD9833_H_INCLUDED
#define AD9833_H_INCLUDED

#define AD9833_DDR  DDRB
#define AD9833_PORT PORTB
#define AD9833_FS0  _BV(0)
#define AD9833_FS1  _BV(1)

#define CR_B28      _BV(13)
#define CR_HLB      _BV(12)
#define CR_FSELECT  _BV(11)
#define CR_PSELECT  _BV(10)
#define CR_RESET    _BV(8)
#define CR_SLEEP1   _BV(7)
#define CR_SLEEP12  _BV(6)
#define CR_OPBITEN  _BV(5)
#define CR_DIV2     _BV(3)
#define CR_MODE     _BV(1)

#define FR_FREQ0    _BV(14)
#define FR_FREQ1    _BV(15)

#define PR_PHASE0   _BV(15)|_BV(14)
#define PR_PHASE1   _BV(15)|_BV(14)|_BV(13)

typedef enum {SIN = 0, TRG = 1, SQR = 2} waveShape_t;
typedef struct ad9833generator_t {
    uint8_t pin;
    uint32_t frequency;
    int16_t phase;
    uint16_t control;
} ad9833generator_t;

void ad9833_init(void);
void ad9833_reset(_Bool rst);
void ad9833_set_freq(uint32_t freq,
                     uint8_t ch);
uint32_t ad9833_get_freq(uint8_t ch);
void ad9833_set_phase(int16_t phase,
                      uint8_t ch);
uint16_t ad9833_get_phase(uint8_t ch);
void ad9833_set_wave(waveShape_t shape,
                     uint8_t ch);
waveShape_t ad9833_get_wave(uint8_t ch);

#endif // AD9833_H_INCLUDED
