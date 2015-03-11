#include "stm32l053xx.h"
#include "SIM800h.h"
#include "hw_config.h"
 

void Init_AD_line(void);
void Init_SIM800_line(void);
void Init_Core(void);
void Init_Interrupts(void);
void Configure_GPIO(void);

void Configure_GPIO_LED(void)
{
  /* (1) Enable the peripheral clock of GPIOA and GPIOB */
  /* (2) Select output mode (01) on GPIOA pin 5 */
  /* (3) Select output mode (01) on GPIOB pin 4 */
  RCC->IOPENR |= RCC_IOPENR_GPIOAEN | RCC_IOPENR_GPIOBEN; /* (1) */  
  GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODE7)) 
               | (GPIO_MODER_MODE7_0); /* (2) */  
  GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODE6)) 
               | (GPIO_MODER_MODE6_0); /* (3) */  
}

void Configure_GPIO(void)
{
  /* (1) Enable the peripheral clock of GPIOA and GPIOB */
  /* (2) Select output mode (01) on GPIOA pin 5 */
  /* (3) Select output mode (01) on GPIOB pin 4 */
 	 GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODE0|GPIO_MODER_MODE1|GPIO_MODER_MODE6|GPIO_MODER_MODE7))\
                 | (GPIO_MODER_MODE0_0 | GPIO_MODER_MODE1_0| GPIO_MODER_MODE6_0| GPIO_MODER_MODE7_0);
}

void Init_AD_line(void)
{

	
  /* GPIO configuration for USART1 signals */
  /* (1) Select AF mode (10) on PA9 and PA10 */
  /* (2) AF4 for USART1 signals */
  GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODE9|GPIO_MODER_MODE10))\
                 | (GPIO_MODER_MODE9_1 | GPIO_MODER_MODE10_1); /* (1) */
  GPIOA->AFR[1] = (GPIOA->AFR[1] &~ (0x0000FF00))\
                  | (4 << (1 * 4)) | (4 << (2 * 4)); /* (2) */
   GPIOA->PUPDR = (GPIOA->PUPDR & ~(GPIO_PUPDR_PUPD10))\
                 | (GPIO_PUPDR_PUPD10_0); /* (1) */
  USART1->BRR = 40000 / 96; /* (1) */
  USART1->CR3 = USART_CR3_DMAT | USART_CR3_DMAR; /* (2) */
  USART1->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE; /* (3) */
  
  while((USART1->ISR & USART_ISR_TC) != USART_ISR_TC)/* polling idle frame Transmission */
  { 
    /* add time out here for a robust application */
  }
  USART1->ICR = USART_ICR_TCCF;/* Clear TC flag */  
	
	DMA1_CSELR->CSELR = (DMA1_CSELR->CSELR & ~DMA_CSELR_C3S) | (3 << (2 * 4)); /* (5) */
  DMA1_Channel3->CPAR = (uint32_t)&(USART1->RDR); /* (6) */
  DMA1_Channel3->CMAR = (uint32_t)AD_Answer; /* (7) */
  DMA1_Channel3->CNDTR = 48; /* (8) */
  DMA1_Channel3->CCR = DMA_CCR_MINC | DMA_CCR_TCIE | DMA_CCR_EN; /* (9) */
}

void Init_SIM800_line(void)
{
  GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODE2|GPIO_MODER_MODE3))\
                 | (GPIO_MODER_MODE2_1 | GPIO_MODER_MODE3_1); /* (1) */
  GPIOA->AFR[0] = (GPIOA->AFR[0] &~ (0x00000FF0))\
                  | (4 << (2 * 4)) | (4 << (3 * 4)); /* (2) */	
	
	USART2->BRR = 40000 / 1152; /* (1) */
  USART2->CR3 = USART_CR3_DMAT | USART_CR3_DMAR; /* (2) */
  USART2->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE; /* (3) */
  
  while((USART2->ISR & USART_ISR_TC) != USART_ISR_TC)/* polling idle frame Transmission */
  { 
    /* add time out here for a robust application */
  }
  USART2->ICR = USART_ICR_TCCF;/* Clear TC flag */
	
	DMA1_CSELR->CSELR = (DMA1_CSELR->CSELR & ~DMA_CSELR_C4S) | (4 << (3 * 4)); /* (5) */
  DMA1_Channel4->CPAR = (uint32_t)&(USART2->TDR); /* (6) */
  DMA1_Channel4->CMAR = (uint32_t)SIM800_data; /* (7) */
  DMA1_Channel4->CNDTR = 15; /* (8) */
  DMA1_Channel4->CCR = DMA_CCR_MINC | DMA_CCR_DIR | DMA_CCR_TCIE; /* (9) */

  DMA1_CSELR->CSELR = (DMA1_CSELR->CSELR & ~DMA_CSELR_C5S) | (4 << (4 * 4)); /* (5) */
  DMA1_Channel5->CPAR = (uint32_t)&(USART2->RDR); /* (6) */
  DMA1_Channel5->CMAR = (uint32_t)SIM800_Answer; /* (7) */
  DMA1_Channel5->CNDTR = 48; /* (8) */
  DMA1_Channel5->CCR = DMA_CCR_MINC | DMA_CCR_TCIE | DMA_CCR_EN; /* (9) */
	
}

void Init_Core(void)
{
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	/* Enable the peripheral clock USART1 */
  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	/* Enable the peripheral clock USART2 */
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
  /* Enable the peripheral clock of GPIOB */
  RCC->IOPENR |= RCC_IOPENR_GPIOBEN;	
	/* Enable the peripheral clock of GPIOA */
  RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
	
	RCC->CR |= RCC_CR_HSION | RCC_CR_HSIDIVEN;                      /* Enable HSI                        */
  while ((RCC->CR & RCC_CR_HSIRDY) == 0);                   /* Wait for HSI Ready                */

  RCC->CFGR = RCC_CFGR_SW_HSI;                              /* HSI is system clock               */
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI);   /* Wait for HSI used as system clock */

  /*  PLL configuration: PLLCLK = (HSI * 6)/3 = 32 MHz */
  RCC->CFGR &= ~(RCC_CFGR_PLLSRC |
                 RCC_CFGR_PLLMUL |
                 RCC_CFGR_PLLDIV  );
  RCC->CFGR |=  (RCC_CFGR_PLLSRC_HSI |
                 RCC_CFGR_PLLMUL4    |
                 RCC_CFGR_PLLDIV4     );

  FLASH->ACR |= FLASH_ACR_PRFTEN;                           /* Enable Prefetch Buffer            */
  FLASH->ACR |= FLASH_ACR_LATENCY;                          /* Flash 1 wait state                */

  RCC->APB1ENR |= RCC_APB1ENR_PWREN;                        /* Enable the PWR APB1 Clock         */
  PWR->CR = PWR_CR_VOS_0;                                   /* Select the Voltage Range 1 (1.8V) */
  while((PWR->CSR & PWR_CSR_VOSF) != 0);                    /* Wait for Voltage Regulator Ready  */

  RCC->CFGR |= RCC_CFGR_HPRE_DIV1;                          /* HCLK = SYSCLK                     */
  RCC->CFGR |= RCC_CFGR_PPRE1_DIV1;                         /* PCLK1 = HCLK                      */
  RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;                         /* PCLK2 = HCLK                      */

  RCC->CR &= ~RCC_CR_PLLON;                                 /* Disable PLL */

  RCC->CR |= RCC_CR_PLLON;                                  /* Enable PLL                        */
  while((RCC->CR & RCC_CR_PLLRDY) == 0) __NOP();            /* Wait till PLL is ready            */

  RCC->CFGR &= ~RCC_CFGR_SW;                                /* Select PLL as system clock source */
  RCC->CFGR |=  RCC_CFGR_SW_PLL;

  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);   /* Wait till PLL is system clock src */
}	

void Init_Interrupts(void)
{
  NVIC_SetPriority(DMA1_Channel2_3_IRQn, 0); /* (10) */
	NVIC_SetPriority(DMA1_Channel4_5_6_7_IRQn, 1); /* (10) */
  NVIC_EnableIRQ(DMA1_Channel4_5_6_7_IRQn); /* (11) */
	NVIC_EnableIRQ(DMA1_Channel2_3_IRQn); /* (11) */
}

void Init_Hardware(void)
{
	Init_Core();

	Init_SIM800_line();
	Configure_GPIO();	
	Init_AD_line();
	Init_Interrupts();
	Configure_GPIO_LED();
}

void DMA1_Channel2_3_IRQHandler(void)
{
  if((DMA1->ISR & DMA_ISR_TCIF2) == DMA_ISR_TCIF2)
  {
    DMA1->IFCR = DMA_IFCR_CTCIF2;/* Clear TC flag */
  }
  else if((DMA1->ISR & DMA_ISR_TCIF3) == DMA_ISR_TCIF3)
  {
    DMA1->IFCR = DMA_IFCR_CTCIF3;/* Clear TC flag */
    DMA1_Channel3->CCR &=~ DMA_CCR_EN;
    DMA1_Channel3->CNDTR = 48;/* Data size */
    DMA1_Channel3->CCR |= DMA_CCR_EN;
  }
  else
  {
    NVIC_DisableIRQ(DMA1_Channel2_3_IRQn);/* Disable DMA1_Channel2_3_IRQn */
  }
}

void DMA1_Channel4_5_6_7_IRQHandler(void)
{
	if((DMA1->ISR & DMA_ISR_TCIF4) == DMA_ISR_TCIF4)
  {
    DMA1->IFCR = DMA_IFCR_CTCIF4;/* Clear TC flag */
  }
	else if((DMA1->ISR & DMA_ISR_TCIF5) == DMA_ISR_TCIF5)
  {
    DMA1->IFCR = DMA_IFCR_CTCIF5;/* Clear TC flag */
    DMA1_Channel5->CCR &=~ DMA_CCR_EN;
    DMA1_Channel5->CNDTR = sizeof(SIM800_Answer);/* Data size */
    DMA1_Channel5->CCR |= DMA_CCR_EN;
  }
  else
  {
    NVIC_DisableIRQ(DMA1_Channel4_5_6_7_IRQn);/* Disable DMA1_Channel2_3_IRQn */
  }
}
