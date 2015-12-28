#include "same70.h"                     // Device header
#include "board.h"
#include "delay.h"
#include "usart_same70.h"
#include "watchdogs.h"

int main(){
	SystemCoreClockUpdate();
	watchdogs_disable_all();
	usart1_init(9600);
	button_init();
	led_init();

	char myBuffer[80];
	usart1_iterrupt_blocking_puts("El dinero es dinero\n");
	while(1){
			usart1_iterrupt_blocking_gets(myBuffer);
			usart1_iterrupt_blocking_puts(myBuffer);
			usart1_iterrupt_blocking_puts("\n");
	}
}

