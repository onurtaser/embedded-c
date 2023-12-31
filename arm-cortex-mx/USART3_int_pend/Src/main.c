#include <stdint.h>
#include <stdio.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#define USART3_IRQNO 39

int main(void)
{

	//1. Manually pend the pending bit for the USART3 IRQ number in NVIC
	uint32_t *pISPR1 = (uint32_t*) 0XE000E204; //+4 to access ISPR1 because IRQ number is 39.

	*pISPR1 |= ( 1 << (USART3_IRQNO % 32));

	//2. Enable the USART3 IRQ number in NVIC
	uint32_t *pISER1 = (uint32_t*) 0xE000E104;

	*pISER1 |= ( 1 << (USART3_IRQNO % 32));

	//Pending state is cleared automatically at the end. Once it finished the ISR it goes back to the thread mode that is the main code.

	for(;;);
}

void USART3_IRQHandler(void){

	printf("in USART3 isr\n");

}
