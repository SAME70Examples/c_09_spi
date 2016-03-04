#include "spi_same70.h"
#include "same70.h"                     // Device header
#include "extra_defines_same70.h"

void spi0_init(void){
    //Configure pins PD20:SPI0_MISO:B, PD21:SPI0_MOSI:B PD22:SPI1_SPCK:B  PB2:SPI0_NPCS0:D
    PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_CMD_WRITE| PMC_PCR_PID(ID_PIOD);//Enable PIOD Peripheral
	PIOD->PIO_PDR = PIO_PD20 | PIO_PD21 | PIO_PD22;//Disable direct pin control
	PIOD->PIO_ABCDSR[0] |= PIO_PD20 | PIO_PD21 | PIO_PD22;//Select peripheral B
	PIOD->PIO_ABCDSR[1] &= ~(PIO_PD20 | PIO_PD21 | PIO_PD22);
    
    PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_CMD_WRITE| PMC_PCR_PID(ID_PIOB);//Enable PIOB Peripheral
	PIOB->PIO_PDR = PIO_PB2;//Disable direct pin control
	PIOB->PIO_ABCDSR[0] |= PIO_PB2;//Select peripheral D
	PIOB->PIO_ABCDSR[1] |= PIO_PB2;
    
    PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_CMD_WRITE| PMC_PCR_PID(ID_SPI0);//Enable SPI0 Peripheral
    
    //Configure as master
    SPI0->SPI_MR = SPI_MR_MSTR | SPI_MR_PCS(0);
    SPI0->SPI_CSR[0] = SPI_CSR_NCPHA | SPI_CSR_BITS_16_BIT | SPI_CSR_CSNAAT |SPI_CSR_SCBR(150);//
    
    SPI0->SPI_CR = SPI_CR_SPIEN;//Enable spi
}

void spi0_send16(uint16_t data){
    while(!(SPI0->SPI_SR & SPI_SR_TDRE));//Wait transfer data register empty
    SPI0->SPI_TDR = data;
}
