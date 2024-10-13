#ifndef UART_H
#define UART_H

#include <sys/types.h>

void Init_UART(void);
uint8_t Read_USART();
void Write_USART(uint8_t data);

#endif // UART_H
