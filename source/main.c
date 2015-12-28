#include "same70.h"                     // Device header
#include "board.h"
#include "delay.h"
#include "usart_same70.h"
#include "watchdogs.h"
#include <stdlib.h>

int rx_not_complete = 1;
void rx_callback(int nCharRead){
	rx_not_complete = 0;
}

int tx_not_complete = 1;
void tx_callback(void){
	tx_not_complete = 0;
}


int main(){
	SystemCoreClockUpdate();
	watchdogs_disable_all();
	usart1_init(9600);
	button_init();
	led_init();

	char myBuffer[80];
	tx_not_complete = 1;
	usart1_async_puts("El dinero es dinero\n",tx_callback);
	while(tx_not_complete);

	while(1){
		rx_not_complete = 1;
		usart1_async_gets(myBuffer, rx_callback);
		while(rx_not_complete);

		tx_not_complete = 1;
		usart1_async_puts(myBuffer,tx_callback);
		while(tx_not_complete);

		tx_not_complete = 1;
		usart1_async_puts("\n",tx_callback);
		while(tx_not_complete);
	}
}
