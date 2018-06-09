#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED

#define ACT_FLDS_NUMB   18

typedef struct editable_field_t {
    uint8_t col;
    uint8_t row;
} editable_field_t;

void screen_menu_show(void);
fsm_state_t screen_loop(fsm_state_t last_state);

#endif // SCREEN_H_INCLUDED
