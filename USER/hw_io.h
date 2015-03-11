#include <cmsis_os.h>    //зависимости keil rtos
#define Delay(x) 				osDelay(x);  //макрос задрежки в мс, привязанный к задержке rtos
#define SIM800_On()			GPIOA->BSRR |= GPIO_BSRR_BS_1 
#define SIM800_Off()		GPIOA->BRR |= GPIO_BSRR_BS_1 
#define SIM800_Power_On()			GPIOA->BSRR |= GPIO_BSRR_BS_0 
#define SIM800_Power_Off()		GPIOA->BRR |= GPIO_BSRR_BS_0
#define Green_On			GPIOA->BSRR |= GPIO_BSRR_BS_7 
#define Green_Off			GPIOA->BRR |= GPIO_BSRR_BS_7 
#define Red_On			GPIOA->BSRR |= GPIO_BSRR_BS_6 
#define Red_Off		GPIOA->BRR |= GPIO_BSRR_BS_6
extern void SIM800_Command(uint8_t string[], uint8_t lenghth)  ;
extern void RX_Clear(void);
extern void RX2_Clear(void);