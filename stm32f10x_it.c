#include "stm32f10x_it.h"
#include "RTL.h"
#include "CommMessageReceiverController.h"

extern int 		STOP_SIGNAL_EVENT_ID, EMERGENCY_BRAKING_EVENT_ID, COMM_MESSAGE_EVENT_ID;
extern OS_TID T2id, T3id, T4id;
extern volatile int T1, T2, T3, T4, T5, TSim, IDLE;
extern char TMC_char_received;

void EXTI0_IRQHandler(void) {  						// EXTI0_IRQn
	EXTI_ClearFlag(EXTI_Line0);							// Clear EXTI_Line0 update interrupt
	isr_evt_set( EMERGENCY_BRAKING_EVENT_ID, T3id );
}

void EXTI1_IRQHandler(void) {  						// EXTI1_IRQn
	EXTI_ClearFlag(EXTI_Line1);							// Clear EXTI_Line1 update interrupt
	isr_evt_set( STOP_SIGNAL_EVENT_ID, T2id );
}

void USART1_IRQHandler(void) {
	//char c;
	T1 = 0; T2 = 0; T3 = 0; T4 = 0;
	T5 = 1; TSim = 0; IDLE = 0;
	//if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {  // if ready to receive
	if(checkAvailableDataToReceive()) {
		//c = USART_ReceiveData(USART1);
		//TMC_char_received = c;
		TMC_char_received = receiveData();
		isr_evt_set(COMM_MESSAGE_EVENT_ID, T4id);
	}
	if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET) {
		// Do nothing...
	}
}
