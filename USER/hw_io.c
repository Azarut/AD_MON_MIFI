#include "stm32l053xx.h"
#include "SIM800h.h"
#include "hw_io.h"
void SIM800_Command(uint8_t string[], uint8_t lenghth)  
{
	  memset(SIM800_Answer, ' ',48);
		DMA1_Channel4->CMAR = (uint32_t)string; /* (3) */
		DMA1_Channel4->CCR &=~ DMA_CCR_EN;
    DMA1_Channel4->CNDTR = lenghth;/* Data size */
    DMA1_Channel4->CCR |= DMA_CCR_EN;
	  DMA1_Channel5->CCR &=~ DMA_CCR_EN;
    DMA1_Channel5->CNDTR = 48;/* Data size */
    DMA1_Channel5->CCR |= DMA_CCR_EN;
}

void RX_Clear(void)
{
	memset(AD_Answer, ' ',48);
	DMA1_Channel3->CCR &=~ DMA_CCR_EN;
  DMA1_Channel3->CNDTR = 48;/* Data size */
  DMA1_Channel3->CCR |= DMA_CCR_EN;	
}

void RX2_Clear(void)
{
		memset(SIM800_Answer, ' ',48);
	  DMA1_Channel5->CCR &=~ DMA_CCR_EN;
    DMA1_Channel5->CNDTR = 48;/* Data size */
    DMA1_Channel5->CCR |= DMA_CCR_EN;
}
