#ifndef FSM_H_INCLUDED
#define FSM_H_INCLUDED

typedef enum {DEFAULT, START, MAIN_SCREEN, MENU} fsm_state_t;

void fsm_run(fsm_state_t first_state);

#endif // FSM_H_INCLUDED
