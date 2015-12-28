#ifndef _USART_SAME70_H
#define _USART_SAME70_H

void usart1_init(int baudrate);
void usart1_putc(char c);
char usart1_getc(void);
void usart1_puts(const char* pString);
void usart1_async_puts(const char* pString, void (*tx_complete_callback)(void));
void usart1_async_gets(char* pString, void (*usart1_rx_complete_callback)(int));

#endif// _USART_SAME70_H
