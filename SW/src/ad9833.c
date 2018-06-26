
#include <avr/io.h>
#include <avr/cpufunc.h>
#include <stdbool.h>

#include "ad9833.h"
#include "spi.h"

static ad9833generator_t generator[2] = {{AD9833_FS0,0,0,0},{AD9833_FS1,0,0,0}};

static inline void fsync_hi(uint8_t pins)
{
    AD9833_PORT |= pins;
}

static inline void fsync_lo(uint8_t pins)
{
    AD9833_PORT &= ~pins;
}

void ad9833_init(void)
{
    AD9833_DDR |= AD9833_FS0|AD9833_FS1; //config FSYNC lines as outputs
    fsync_hi(AD9833_FS0|AD9833_FS1);
    _NOP();
    ad9833_reset(true);
}

void ad9833_reset(_Bool rst)
{
    uint16_t ctrl_reg = CR_B28;
    
    if(rst) ctrl_reg = CR_RESET|CR_B28;
    fsync_lo(AD9833_FS0|AD9833_FS1);
    spi_send_word(&ctrl_reg);
    fsync_hi(AD9833_FS0|AD9833_FS1);
    generator[0].control = ctrl_reg;
    generator[1].control = ctrl_reg;
}

void ad9833_set_freq(uint32_t freq,
                     uint8_t ch)
{
    uint64_t freq_word;
    uint16_t lsb, msb;
    
    freq_word = ((uint64_t)freq * 16384ULL) / 1000;
    lsb = FR_FREQ0 | ((uint16_t)freq_word & 0x3FFF);
    msb = FR_FREQ0 | ((uint16_t)(freq_word >> 14) & 0x3FFF);
    
    fsync_lo(generator[ch].pin);
    spi_send_word(&generator[ch].control);
    spi_send_word(&lsb); //write 28-bit word in two 14-bit consecutive writes
    spi_send_word(&msb);
    fsync_hi(generator[ch].pin);
    generator[ch].frequency = freq;
}

uint32_t ad9833_get_freq(uint8_t ch)
{
    return generator[ch].frequency;
}

void ad9833_set_phase(uint16_t phase,
                      uint8_t ch)
{
    uint16_t phase_word;
    
    phase_word = PR_PHASE0 | ((((uint32_t)phase * 512UL) / 45) & 0x0FFF);
    fsync_lo(generator[ch].pin);
    spi_send_word(&phase_word);
    fsync_hi(generator[ch].pin);
    generator[ch].phase = phase;
}

uint16_t ad9833_get_phase(uint8_t ch)
{
    return generator[ch].phase;
}

void ad9833_set_wave(waveShape_t shape,
                     uint8_t ch)
{
    uint16_t ctrl_reg = generator[ch].control;
    
    switch(shape)
    {
    case SIN:
        ctrl_reg &= ~(CR_MODE|CR_OPBITEN|CR_DIV2);
        break;
    case TRG:
        ctrl_reg &= ~(CR_OPBITEN|CR_DIV2);
        ctrl_reg |= CR_MODE;
        break;
    case SQR:
        //TODO: square wave from AD9833 output is very coarse
        //it should be generated from sin wave by hardware comparator controled with GPIOs
        ctrl_reg &= ~(CR_MODE);
        ctrl_reg |= (CR_OPBITEN|CR_DIV2);
        break;
    default:
        break;
    }
    fsync_lo(generator[ch].pin);
    spi_send_word(&ctrl_reg);
    fsync_hi(generator[ch].pin);
    generator[ch].control = ctrl_reg;
}

waveShape_t ad9833_get_wave(uint8_t ch)
{
    if(generator[ch].control & CR_MODE) return TRG;
    else if(generator[ch].control & (CR_OPBITEN|CR_DIV2)) return SQR;
    else return SIN;
}
