#include "stm32f10x_it.h"
#include "RTL.h"

extern int 		STOP_SIGNAL_EVENT_ID, EMERGENCY_BRAKING_EVENT_ID;
extern OS_TID T2id, T3id;

void EXTI0_IRQHandler(void) {  						// EXTI0_IRQn
	EXTI_ClearFlag(EXTI_Line0);							// Clear EXTI_Line0 update interrupt
	isr_evt_set( EMERGENCY_BRAKING_EVENT_ID, T3id );
}

void EXTI1_IRQHandler(void) {  						// EXTI1_IRQn
	EXTI_ClearFlag(EXTI_Line1);							// Clear EXTI_Line1 update interrupt
	isr_evt_set( STOP_SIGNAL_EVENT_ID, T2id );
}
