#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
extern uint32_t SystemCoreClock;

uint32_t systemClock;

void RCC_Config(void)
{
	RCC-> CR &= ~(1 << 0);				// HSI OFF
	RCC-> CR |= 1 << 16;				// HSE ON
	while(!(RCC->CR & (1 << 17)));		// Wait HSE active
	RCC-> CR |= 1 << 19;
	RCC->PLLCFGR = 0x00000000;			// PLLCFGR Reset
	RCC->PLLCFGR |= (1 << 22);          // PLL Source HSE
	RCC->PLLCFGR |= 4 << 0;				// PLLM 4
	RCC->PLLCFGR |= (168 << 6);  		// PLL N 168

    RCC-> CR |= (1 << 24);				// PLL ON
	while(!(RCC->CR & (1 << 25)));		// Wait PLL active

	RCC-> CFGR &= ~(1 << 0);
	RCC-> CFGR |= (1 << 1); 			// System Clock is PLL
	while(!(RCC-> CFGR & (1 << 1)));    // Selected system clock is PLL clock

    //8 000000 --> 168 000000

}

int main(void)
{
	RCC_Config();
	SystemCoreClockUpdate();
	systemClock = SystemCoreClock;

  while (1)
  {

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
