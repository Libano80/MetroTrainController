#ifndef _EXTI_PINS_INFO_H
#define _EXTI_PINS_INFO_H

#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"

typedef struct {
	uint16_t	GPIO_Pin;
	uint8_t		GPIO_PinSource;
	uint32_t	EXTI_Line;
	uint8_t		NVIC_IRQChannel;
	uint8_t		NVIC_IRQChannelPreemptionPriority;
	uint8_t		NVIC_IRQChannelSubPriority;
	} EXTI_pins_info;

EXTI_pins_info EXTI_pins_info_array[2] = {
				{GPIO_Pin_0, GPIO_PinSource0, EXTI_Line0, EXTI0_IRQn, 0, 0},
				{GPIO_Pin_1, GPIO_PinSource1, EXTI_Line1, EXTI1_IRQn, 2, 0}
};

#endif
