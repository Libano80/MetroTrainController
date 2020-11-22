#include "stm32f10x_it.h"
#include "RTL.h"
#include "pins_definition.h"

extern int T1, IDLE;
extern int Eid;
extern OS_TID Tid;
extern int current_Pin;

void EXTI2_IRQHandler(void) {  // EXTI2_IRQn
	EXTI_ClearFlag(EXTI_Line2);
	T1 = 0; IDLE = 1;
	current_Pin = PIN_MAX_BRAKING;
	isr_evt_set( Eid, Tid );
}

void EXTI3_IRQHandler(void) {  // EXTI3_IRQn
	EXTI_ClearFlag(EXTI_Line3);
	T1 = 0; IDLE = 1;
	current_Pin = PIN_MED_BRAKING;
	isr_evt_set( Eid, Tid );
}

void EXTI4_IRQHandler(void) {  // EXTI4_IRQn
	EXTI_ClearFlag(EXTI_Line4);
	T1 = 0; IDLE = 1;
	current_Pin = PIN_MIN_BRAKING;
	isr_evt_set( Eid, Tid );
}

void EXTI9_5_IRQHandler(void) {  // EXTI9_5_IRQn
	T1 = 0; IDLE = 1;
	//if statement is needed when other EXTI pin lines are enabled
	if (EXTI_GetITStatus(EXTI_Line5) != RESET) {
		/* Clear interrupt flag */
		EXTI_ClearITPendingBit(EXTI_Line5);
		/* Do your stuff when PB12 is changed */
		current_Pin = PIN_IDLE_LEVER;
		isr_evt_set( Eid, Tid );
	} else if (EXTI_GetITStatus(EXTI_Line6) != RESET) {
		/* Clear interrupt flag */
		EXTI_ClearITPendingBit(EXTI_Line6);
		/* Do your stuff when PB12 is changed */
		current_Pin = PIN_MIN_ACCEL;
		isr_evt_set( Eid, Tid );
	} else if (EXTI_GetITStatus(EXTI_Line7) != RESET) {
		/* Clear interrupt flag */
		EXTI_ClearITPendingBit(EXTI_Line7);
		/* Do your stuff when PB12 is changed */
		current_Pin = PIN_MED_ACCEL;
		isr_evt_set( Eid, Tid );
	} else if (EXTI_GetITStatus(EXTI_Line8) != RESET) {
		/* Clear interrupt flag */
		EXTI_ClearITPendingBit(EXTI_Line8);
		/* Do your stuff when PB12 is changed */
		current_Pin = PIN_MAX_ACCEL;
		isr_evt_set( Eid, Tid );
	}
}
