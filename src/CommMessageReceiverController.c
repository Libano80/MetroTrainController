/*----------------------------------------------------------------------------
 * Name:    CommMessageReceiverController.c
 * Purpose: Definition of the communication specifics with the Traffic 
 * 					Management Center
 *----------------------------------------------------------------------------*/

#include <stm32f10x.h>                     /* STM32F103 definitions         	*/
#include "CommMessageReceiverController.h"

void USART1_Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* Enable GPIOA, AFIO and USART1 clock */
	RCC_APB2PeriphClockCmd(
			RCC_APB2Periph_USART1 |
			RCC_APB2Periph_GPIOA |
			RCC_APB2Periph_AFIO, ENABLE);
			
	/* Configure USART Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure USART Rx as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* USART1 configured as follow:
			- BaudRate = 115200 baud
			- Word Length = 8 Bits
			- One Stop Bit
			- No parity
			- Hardware flow control disabled (RTS and CTS signals)
			- Receive and transmit enabled
  */
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	/* USART initialization */
	USART_Init(USART1, &USART_InitStructure);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); 						//Open receive interrupt
	USART_Cmd(USART1, ENABLE);
}

void NVIC_USART1_Init(void) {
	NVIC_InitTypeDef NVIC_InitStructureUSART;
	
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
