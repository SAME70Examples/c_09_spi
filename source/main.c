#include "same70.h"                     // Device header

void led_init(void);
#define LED_ON 1
#define LED_OFF 0
void led_setState(int led_state);
void delay_ms(int time_ms);
void delay_us(int time_us);
void button_init(void);
int button_isPressed(void);

void usart1_init(int baudrate);
void usart1_putc(char c);
char usart1_getc(void);

int main(){
	SystemCoreClockUpdate();
	usart1_init(9600);
	char c;
	while(1){
		//TODO
		c = usart1_getc();
		usart1_putc(c);
	}
}

#define PMC_PCR_CMD_READ (0<<12)
#define PMC_PCR_CMD_WRITE (1<<12)
#define PMC_PCR_PID_PIOA (10)
#define PMC_PCR_PID_PIOB (11)
#define PMC_PCR_PID_PIOC (12)
#define PMC_PCR_PID_USART0 (13)
#define PMC_PCR_PID_USART1 (14)
#define PMC_PCR_PID_USART2 (15)

void usart1_init(int baudrate){
	//Configure pio pins for usart operation PA21:RXD1 PB4:TXD1
	
	MATRIX->CCFG_SYSIO |= CCFG_SYSIO_SYSIO4;//Transfer control from SYSIO:TDI to PIOB 

	PMC->PMC_PCR = (PMC_PCR_EN)|(PMC_PCR_CMD_WRITE)|(PMC_PCR_PID_PIOA);//Enable PIOA Peripheral
	PIOA->PIO_PDR = PIO_PDR_P21;//Disable direct control of PA21
	PIOA->PIO_PUER = PIO_PUER_P21;//Enable pull ups
	PIOA->PIO_PPDDR = PIO_PPDDR_P21;//Disable pull downs
	PIOA->PIO_ABCDSR[0] &= ~(PIO_ABCDSR_P21);//Select peripheral A for RXD1
	PIOA->PIO_ABCDSR[1] &= ~(PIO_ABCDSR_P21);//Select peripheral A for RXD1
	
	PMC->PMC_PCR = (PMC_PCR_EN)|(PMC_PCR_CMD_WRITE)|(PMC_PCR_PID_PIOB);//Enable PIOB Peripheral
	PIOB->PIO_PUDR = PIO_PUDR_P4;//Disable pull ups
	PIOB->PIO_PPDDR = PIO_PPDDR_P4;//Disable pull downs
	PIOB->PIO_ABCDSR[0] |= PIO_ABCDSR_P4;//Select peripheral D for TXD1
	PIOB->PIO_ABCDSR[1] |= PIO_ABCDSR_P4;//Select peripheral D for TXD1
	PIOB->PIO_PDR = PIO_PDR_P4;//Disable direct control of PB4
	
	PMC->PMC_PCR = (PMC_PCR_EN)|(PMC_PCR_CMD_WRITE)|(PMC_PCR_PID_USART1);//Enable USART1 Peripheral
	USART1->US_MR = 0;
	USART1->US_MR = (US_MR_USART_MODE_NORMAL | US_MR_USCLKS_MCK
	| US_MR_CHRL_8_BIT | US_MR_PAR_NO);
	USART1->US_BRGR = (4<<16)|(987<<0);//(fractional divider)|(integer dividier) 9600bps@150Mhz peripheral clock 
	USART1->US_CR = US_CR_RXEN | US_CR_TXEN;//Enable receiver and transmitter
}

void usart1_putc(char c){
	while(!(USART1->US_CSR & US_CSR_TXRDY));
	USART1->US_THR = c;
}

char usart1_getc(void){
	while(!(USART1->US_CSR & US_CSR_RXRDY));
	return USART1->US_RHR;
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
