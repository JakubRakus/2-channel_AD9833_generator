#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

void uint32_to_str(uint32_t numb,
                   char *str,
                   uint8_t len);
void int16_to_str(int16_t numb,
                  char* str,
                  uint8_t len_with_sign,
                  _Bool show_plus,
                  _Bool sign_leftmost);

#endif // UTILS_H_INCLUDED
