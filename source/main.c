#include "same70.h"                     // Device header
#include "board.h"
#include "delay.h"
#include "usart_same70.h"
#include "watchdogs.h"
#include "serial_stdio.h"
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "os_usart_same70.h"

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

/*----------------------------------------------------------------------------
 *      Thread 2 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/

void Thread2 (void const *argument);                             // thread function
osThreadId tid_Thread2;                                          // thread id
osThreadDef (Thread2, osPriorityNormal, 1, 0);                   // thread object

int Thread2_init(void){
  tid_Thread2 = osThreadCreate (osThread(Thread2), NULL);
  if(!tid_Thread2) return(-1);

  return(0);
}

int thread2_counter;
int thread2_reset_counter;
void Thread2(void const *argument) {
	while(1){
		if(thread2_reset_counter){
			thread2_counter = 0;
			thread2_reset_counter = 0;
		}else{
			thread2_counter++;
		}
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
	Thread2_init();
	//Start kernel and thread switching
	osKernelStart();
	//User application
	char myBuffer[80];
	int lineCounter = 1;

	simple_puts("El dinero es dinero\n");

	while(1){
		serial_printf(os_usart1_puts,"%d$",lineCounter);
		os_usart1_gets(myBuffer);
		serial_printf(os_usart1_puts,">>%s\n",myBuffer);
		serial_printf(os_usart1_puts,"count = %d\n",thread2_counter);
		thread2_reset_counter = 1;
		lineCounter++;
	}
}
