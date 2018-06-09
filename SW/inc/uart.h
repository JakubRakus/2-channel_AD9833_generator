#ifndef UART_H_INCLUDED
#define UART_H_INCLUDED

void uart_init(void);
void uart_send_char(char ch);
void uart_send_string(const char *ch);

#endif // UART_H_INCLUDED
