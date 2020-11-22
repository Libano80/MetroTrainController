#include "EXTI_pins_info.h"

void Configure_EXTI_GPIOB(EXTI_pins_info EXTI_pin_info) {
	/* Set variables used */
	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	// Enable clock for GPIOB
	
	/* Set pin as input */
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU; // GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Pin = EXTI_pin_info.GPIO_Pin;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, EXTI_pin_info.GPIO_PinSource);     
	
	EXTI_InitStruct.EXTI_Line = EXTI_pin_info.EXTI_Line;	// PB15 is connected to EXTI_Line15
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;	// Enable interrupt
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;	// Interrupt mode
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;	// Triggers on rising edge
	EXTI_Init(&EXTI_InitStruct);		// Add to EXTI

	/* Add IRQ vector to NVIC */
	NVIC_InitStruct.NVIC_IRQChannel = EXTI_pin_info.NVIC_IRQChannel;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;	// Set priority
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x01;		// Set sub priority
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;		// Enable interrupt
	NVIC_Init(&NVIC_InitStruct);				// Add to NVIC
}

void Configure_EXTI_GPIOB2(void) {
	EXTI_pins_info pin_2_EXTI_info = EXTI_pins_info_array[2];
	Configure_EXTI_GPIOB(pin_2_EXTI_info);
}

void Configure_EXTI_GPIOB3(void) {
	EXTI_pins_info pin_3_EXTI_info = EXTI_pins_info_array[3];
	Configure_EXTI_GPIOB(pin_3_EXTI_info);
}

void Configure_EXTI_GPIOB4(void) {
	EXTI_pins_info pin_4_EXTI_info = EXTI_pins_info_array[4];
	Configure_EXTI_GPIOB(pin_4_EXTI_info);
}

void Configure_EXTI_GPIOB5(void) {
	EXTI_pins_info pin_5_EXTI_info = EXTI_pins_info_array[5];
	Configure_EXTI_GPIOB(pin_5_EXTI_info);
}

void Configure_EXTI_GPIOB6(void) {
	EXTI_pins_info pin_6_EXTI_info = EXTI_pins_info_array[6];
	Configure_EXTI_GPIOB(pin_6_EXTI_info);
}

void Configure_EXTI_GPIOB7(void) {
	EXTI_pins_info pin_7_EXTI_info = EXTI_pins_info_array[7];
	Configure_EXTI_GPIOB(pin_7_EXTI_info);
}

void Configure_EXTI_GPIOB8(void) {
	EXTI_pins_info pin_8_EXTI_info = EXTI_pins_info_array[8];
	Configure_EXTI_GPIOB(pin_8_EXTI_info);
}
