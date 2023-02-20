#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

int i =0;

void delay(uint32_t time)
{
	while(time--);
}

void RCC_Config()
{
	RCC-> CR |= 0x00010000;				// HSEON enable
	while(!(RCC-> CR & 0x00020000));    // HSE Ready flag wait
	RCC-> CR |= 0x00080000;				// CSS enable
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

void DAC1_Config()
{
	RCC->AHB1ENR |= 0x00000001;
	RCC->APB1ENR |= 0x20000000;
	DAC->CR |= 0x00000001;        // DAC Channel 1 enable
	DAC->SWTRIGR |= 0x00000000;   // DAC Channel 1 software trigger disable
	DAC->DHR12R1 |= 0x00000000;   // DAC Chennel 1 12-bit right-aligned data
}

int main(void)
{

	RCC_Config();
    DAC1_Config();

  while (1)
  {
	  for(; 1<4096 ;i++)
	  {
		  DAC->DHR12R1 = i;
		  delay(16800);
	  }
	  i=0;
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
