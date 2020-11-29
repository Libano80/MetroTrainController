#include "stm32f10x_it.h"
#include "RTL.h"

extern int E2id;
extern OS_TID T2id;

void EXTI1_IRQHandler(void) {  						// EXTI1_IRQn
	EXTI_ClearFlag(EXTI_Line1);							// Clear EXTI_Line1 update interrupt
	isr_evt_set( E2id, T2id );
}
