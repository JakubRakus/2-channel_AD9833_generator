#ifndef MAIN_SCREEN_H_INCLUDED
#define MAIN_SCREEN_H_INCLUDED

typedef struct editable_field_t {
    uint8_t col;
    uint8_t row;
} editable_field_t;

fsm_state_t main_screen_loop(fsm_state_t last_state);

#endif // MAIN_SCREEN_H_INCLUDED
