#include "same70.h"                     // Device header
#include "board.h"
#include "delay.h"
#include "usart_same70.h"
#include "watchdogs.h"
#include "serial_stdio.h"
#include <stdlib.h>

int rx_not_complete = 1;
void rx_callback(int nCharRead){
	rx_not_complete = 0;
}

int tx_not_complete = 1;
void tx_callback(void){
	tx_not_complete = 0;
}

void simple_puts(const char* pData){
	tx_not_complete = 1;
	usart1_async_puts(pData,tx_callback);
	while(tx_not_complete);
}

void simple_gets(char* pData){
	rx_not_complete = 1;
	usart1_async_gets(pData, rx_callback);
	while(rx_not_complete);
}

int main(){
	SystemCoreClockUpdate();
	watchdogs_disable_all();
	usart1_init(9600);
	button_init();
	led_init();

	char myBuffer[80];
	int lineCounter = 1;

	simple_puts("El dinero es dinero\n");
	
	while(1){
		simple_gets(myBuffer);
		serial_printf(simple_puts,"%d$%s\n",lineCounter,myBuffer);
		lineCounter++;
	}
}
