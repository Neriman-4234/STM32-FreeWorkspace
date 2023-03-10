#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void CLK_Config()
{
	RCC-> CR |= 0x00030000;				// HSEON and HSEONRDY enable
	while(!(RCC-> CR & 0x00020000));    // HSE Ready flag wait
	RCC-> CR |= 0x00080000;				// CSS enable
	RCC-> PLLCFGR |= 0x00400000;		// PLL e HSE se?tik
	RCC-> PLLCFGR |= 0x00000004;		// PLL M = 4
	RCC-> PLLCFGR |= 0x00005A00;		// PLL N = 168
	RCC-> PLLCFGR |= 0x00000000;		// PLL P = 2
	RCC-> CFGR |= 0x000000000;			// AHB Prescaler = 1
	RCC-> CFGR |= 0x00080000;			// APB2 Prescaler = 2
	RCC-> CFGR |= 0x00001400;			// APB1 Prescaler = 4
	RCC-> CIR |= 0x00080000;			// HSERDY flag clear
	RCC-> CIR |= 0x00800000;			// CSS flag clear

}

void GPIO_Config()
{

	RCC->AHB1ENR = 0x00000009;			// GPIOA ve GPIOD aktif
	GPIOD->MODER = 0x55000000;			//12,13,14,15 pins digital output
	GPIOD-> OTYPER = 0x00000000;		//12,13,14,15 pins Push pull
	GPIOD-> OSPEEDR = 0xFF000000;		//12,13,14,15 pins 100MHz
	GPIOD-> PUPDR = 0x00000000;			//12,13,14,15 pins no pull
}

void EXTI_Config()
{
RCC->APB2ENR = 0x00004000;  //SYSCFG active (ext ?nterrupt)
SYSCFG->EXTICR[0]= 0x00000000;
NVIC_EnableIRQ(EXTI0_IRQn);
NVIC_EnableIRQ(EXTI1_IRQn);
NVIC_EnableIRQ(EXTI2_IRQn);

NVIC_SetPriority(EXTI0_IRQn, 0);
NVIC_SetPriority(EXTI1_IRQn, 1);
NVIC_SetPriority(EXTI2_IRQn, 2);

EXTI-> IMR = 0x00000007;
EXTI-> RTSR = 0x00000007;

}
void delay (uint32_t time)
{
	while(time--);
}

void EXTI0_IRQHandler()
{
	if(EXTI-> PR & 0x00000001 )
	{
		GPIOD->ODR = 0x00001000;
		delay(33600000);

		EXTI->PR = 0x00000001;
	}
}

void EXTI1_IRQHandler()
{
	if(EXTI-> PR & 0x00000002 )
	{
		GPIOD->ODR = 0x00002000;
		delay(33600000);

		EXTI->PR = 0x00000002;
	}
}

void EXTI2_IRQHandler()
{
	if(EXTI-> PR & 0x00000004 )
	{
		GPIOD->ODR = 0x00004000;
		delay(33600000);

		EXTI->PR = 0x00000004;
	}
}

int main(void)
{
CLK_Config();
GPIO_Config();
EXTI_Config();
  while (1)
  {
GPIOD-> ODR = 0x0000F000;
  }
}


void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
