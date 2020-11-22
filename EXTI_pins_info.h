#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"

typedef struct {
	uint16_t	GPIO_Pin;
	uint8_t GPIO_PinSource;
	uint32_t EXTI_Line;
	uint8_t NVIC_IRQChannel;
	} EXTI_pins_info;

EXTI_pins_info EXTI_pins_info_array[9] = {
				{0, 0, 0, 0},
				{0, 0, 0, 0},
				{GPIO_Pin_2, GPIO_PinSource2, EXTI_Line2, EXTI2_IRQn},
				{GPIO_Pin_3, GPIO_PinSource3, EXTI_Line3, EXTI3_IRQn},
				{GPIO_Pin_4, GPIO_PinSource4, EXTI_Line4, EXTI4_IRQn},
				{0, 0, 0, 0},
				{0, 0, 0, 0},
				{0, 0, 0, 0},
				{0, 0, 0, 0}
};
