#include "EXTI_pins_info.h"

void Configure_EXTI_GPIOB(EXTI_pins_info EXTI_pin_info) {
	/* Set variables used */
	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);												// Enable clock for GPIOB
	
	/* Set pin as input */
	GPIO_InitStruct.GPIO_Mode		= 	GPIO_Mode_IPD; 															// GPIO_Mode_INPUT_Pull_Down (does not switch on ODR register by default);
	GPIO_InitStruct.GPIO_Pin		= 	EXTI_pin_info.GPIO_Pin;
	GPIO_InitStruct.GPIO_Speed	= 	GPIO_Speed_10MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, EXTI_pin_info.GPIO_PinSource);     
	
	EXTI_InitStruct.EXTI_Line			= EXTI_pin_info.EXTI_Line;										// PB15 is connected to EXTI_Line15
	EXTI_InitStruct.EXTI_LineCmd	= ENABLE;																			// Enable interrupt
	EXTI_InitStruct.EXTI_Mode			= EXTI_Mode_Interrupt;												// Interrupt mode
	EXTI_InitStruct.EXTI_Trigger	= EXTI_Trigger_Rising;												// Triggers on rising edge
	EXTI_Init(&EXTI_InitStruct);																								// Add to EXTI

	/* Add IRQ vector to NVIC */
	NVIC_InitStruct.NVIC_IRQChannel										= EXTI_pin_info.NVIC_IRQChannel;										// Set channel
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = EXTI_pin_info.NVIC_IRQChannelPreemptionPriority;	// Set priority
	NVIC_InitStruct.NVIC_IRQChannelSubPriority				= EXTI_pin_info.NVIC_IRQChannelSubPriority;					// Set sub priority
	NVIC_InitStruct.NVIC_IRQChannelCmd								= ENABLE;																						// Enable interrupt
	NVIC_Init(&NVIC_InitStruct);																																					// Add to NVIC
}

void Configure_EXTI_GPIOB0(void) {
	EXTI_pins_info pin_0_EXTI_info = EXTI_pins_info_array[0];
	Configure_EXTI_GPIOB(pin_0_EXTI_info);
}

void Configure_EXTI_GPIOB1(void) {
	EXTI_pins_info pin_1_EXTI_info = EXTI_pins_info_array[1];
	Configure_EXTI_GPIOB(pin_1_EXTI_info);
}
