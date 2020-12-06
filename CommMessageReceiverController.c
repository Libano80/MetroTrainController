#include <stm32f10x.h>                     /* STM32F103 definitions         	*/
#include "CommMessageReceiverController.h"
#include "stm32f10x_usart.h"

void USART1_Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* Enable peripheral clocks for USART1 on GPIOA */
	RCC_APB2PeriphClockCmd(
			RCC_APB2Periph_USART1 |
			RCC_APB2Periph_GPIOA |
			RCC_APB2Periph_AFIO, ENABLE);
			
	/* Configure PA9 and PA10 as USART1 TX/RX */

	/* PA9 = alternate function push/pull output */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* PA10 = floating input */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure and initialize usart... */
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
			
	USART_Init(USART1, &USART_InitStructure);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); 						//Open receive interrupt
	USART_Cmd(USART1, ENABLE);
}

void NVIC_USART1_Init(void) {
	NVIC_InitTypeDef NVIC_InitStructureUSART;
	
  /* Configure two bits for preemption priority */
  //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitStructureUSART.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructureUSART.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructureUSART.NVIC_IRQChannelSubPriority				= 0;
  NVIC_InitStructureUSART.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructureUSART);
}

void initCommMessageReceiverController(void) {
	USART1_Init();
	NVIC_USART1_Init();
}

int checkAvailableDataToReceive(void) {
	return USART_GetITStatus(USART1, USART_IT_RXNE) != RESET;
}

char receiveData(void) {
	return USART_ReceiveData(USART1);
}
