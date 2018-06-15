#ifndef FSM_H_INCLUDED
#define FSM_H_INCLUDED

typedef enum
{
    DEFAULT = 0,
    START = 1,
    MAIN_SCREEN = 2,
    MENU_CH1 = 3,
    MENU_CH2 = 4
} fsm_state_t;

void fsm_run(fsm_state_t first_state);

#endif // FSM_H_INCLUDED
