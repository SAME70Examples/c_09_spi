#include "same70.h"                     // Device header
#include "board.h"
#include "delay.h"
#include "usart_same70.h"

int main(){
	SystemCoreClockUpdate();
	usart1_init(9600);
	button_init();
	led_init();

	while(1){
		if(button_isPressed()){
			led_setState(LED_ON);
			usart1_iterrupt_blocking_puts("El dinero es dinero\n");
		}else{
			led_setState(LED_OFF);
		}
	}
}

