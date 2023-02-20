#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
uint16_t count = 0;

void RCC_Config()
{
	RCC-> CR |= 0x00010000;				// HSEON enable
	while(!(RCC-> CR & 0x00020000));    // HSE Ready flag wait
	RCC-> CR |= 0x00080000;				// CSS enable
	RCC->CR |= 0x01000000;				// PLL ON
	RCC-> PLLCFGR |= 0x00400000;		// PLL e HSE seçtik
	RCC-> PLLCFGR |= 0x00000004;		// PLL M = 4
	RCC-> PLLCFGR |= 0x00005A00;		// PLL N = 168
	RCC-> PLLCFGR |= 0x00000000;		// PLL P = 2
	RCC-> CFGR |= 0x000000000;			// AHB Prescaler = 1
	RCC-> CFGR |= 0x00080000;			// APB2 Prescaler = 2
	RCC-> CFGR |= 0x00001400;			// APB1 Prescaler = 4
	RCC-> CIR |= 0x00080000;			// HSERDY flag clear
	RCC-> CIR |= 0x00800000;			// CSS flag clear
}

void TIM_Config()
{
	RCC->APB1ENR |= 1 << 0;           // Tim2 Clock enable

	TIM2-> CR1 |= 0 << 4; 			  // counter mode is up-counter
	TIM2-> CR1 |= 0 << 5;			  // center aligned mode edge-aligned
	TIM2-> CR1 |= 0 << 8;			  // set the clock division to 1
	TIM2-> SMCR |= 0 << 0;			  // internal clock source
	TIM2-> EGR |= 1 << 0;			  // timer update generation
	TIM2-> PSC |= 41999;
	TIM2-> ARR = 4000;
	TIM2-> CR1 |= 1 << 0;			  // timer counter enable

}

int main(void)
{
	RCC_Config();
  while (1)
  {
	  count = TIM2->CNT;
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
