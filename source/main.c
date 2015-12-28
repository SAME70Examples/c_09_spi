#include "same70.h"                     // Device header
#include "board.h"
#include "delay.h"
#include "usart_same70.h"
#include "watchdogs.h"
#include "serial_stdio.h"
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX

/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/
 
void Thread1 (void const *argument);                             // thread function
osThreadId tid_Thread1;                                          // thread id
osThreadDef (Thread1, osPriorityNormal, 1, 0);                   // thread object

int Thread1_init(void){
  tid_Thread1 = osThreadCreate (osThread(Thread1), NULL);
  if(!tid_Thread1) return(-1);
  
  return(0);
}

void Thread1(void const *argument) {
  while(1){
		//TODO
		led_setState(LED_ON);
    osDelay(500);
		led_setState(LED_OFF);
		osDelay(500);
  }
}


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
	//PreKernelConfigration
	SystemCoreClockUpdate();
	watchdogs_disable_all();
	//Initialize kernel
	osKernelInitialize();
	//Initialized hardware
	usart1_init(9600);
	button_init();
	led_init();
	//Initialize os objects
	Thread1_init();
	//Start kernel and thread switching
	osKernelStart();
	//User application
	char myBuffer[80];
	int lineCounter = 1;

	simple_puts("El dinero es dinero\n");
	
	while(1){
		simple_gets(myBuffer);
		serial_printf(simple_puts,"%d$%s\n",lineCounter,myBuffer);
		lineCounter++;
	}
}
