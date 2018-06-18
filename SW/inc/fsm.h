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

typedef struct
{
    fsm_state_t last;
    fsm_state_t current;
    fsm_state_t next;
} fsm_state_set_t;

void fsm_run(void);

#endif // FSM_H_INCLUDED
