#include "same70.h"                     // Device header
#include "board.h"
#include "delay.h"
#include "usart_same70.h"

void disable_wdt(void){
	WDT->WDT_CR = WDT_CR_KEY_PASSWD;
	WDT->WDT_MR = WDT_MR_WDDIS;
}

void disable_rswdt(void){
	RSWDT->RSWDT_CR = RSWDT_CR_KEY_PASSWD;
	RSWDT->RSWDT_MR = RSWDT_MR_WDDIS | RSWDT_MR_ALLONES_Msk;
}

int main(){
	SystemCoreClockUpdate();
	disable_wdt();
	disable_rswdt();
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

