#include "same70.h"                     // Device header

void led_init(void);
#define LED_ON 1
#define LED_OFF 0
void led_setState(int led_state);
void delay_ms(int time_ms);
void delay_us(int time_us);

int main(){
	SystemCoreClockUpdate();
	led_init();
	while(1){
		led_setState(LED_ON);
		delay_ms(500);
		led_setState(LED_OFF);
		delay_ms(500);
	}
}

#define PMC_PCR_CMD_READ (0<<12) 
#define PMC_PCR_CMD_WRITE (1<<12)
#define PMC_PCR_PID_PIOA (10)
#define PMC_PCR_PID_PIOB (11)
#define PMC_PCR_PID_PIOC (12)

/**
	* Initialize led on PC8
	*
**/
void led_init(void){
	PMC->PMC_PCR = (PMC_PCR_EN)|(PMC_PCR_CMD_WRITE)|(PMC_PCR_PID_PIOC);//Enable PIOC Peripheral
	PIOC->PIO_PER = PIO_PER_P8;//Enable direct control of PC8
	PIOC->PIO_MDER = PIO_MDER_P8;//Open drain driver
	PIOC->PIO_PUDR = PIO_PUDR_P8;//Disable pull ups
	PIOC->PIO_PPDDR = PIO_PPDDR_P8;//Disable pull downs
	PIOC->PIO_OER = PIO_OER_P8;//Configure as output
}

void led_setState(int led_state){
	if(led_state == LED_ON){
		PIOC->PIO_CODR = PIO_CODR_P8;//Output low: led on
	}else{
		PIOC->PIO_SODR = PIO_SODR_P8;//Ouput floating: led off
	}
}

void delay_ms(int time_ms){
	delay_us(time_ms*1000);
}

#define DELAY_SCALE_FACTOR_US 2
void delay_us(int time_us){
	unsigned int total_time  = time_us * (SystemCoreClock /(1000000 * DELAY_SCALE_FACTOR_US));
	for(unsigned int i = 0; i< total_time; i++){
	}
}