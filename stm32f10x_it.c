#include "stm32f10x_it.h"
#include "pins_definition.h"

extern int IN_INT;

void EXTI2_IRQHandler(void) {  // EXTI2_IRQn
	unsigned int in_pin		= 1<<PIN_MAX_BRAKING;
	unsigned int out_pin	= 1<<OUT_MAX_BRAKING;	
	EXTI_ClearFlag(EXTI_Line2);
  IN_INT=-3;

	if(GPIOB->IDR & in_pin) {
      GPIOC->ODR |= out_pin;                 // switch LED ON
	} else {
      GPIOC->ODR &= ~out_pin;                 // switch LED OFF
	}
}

void EXTI3_IRQHandler(void) {  // EXTI3_IRQn
	unsigned int in_pin		= 1<<PIN_MED_BRAKING;
	unsigned int out_pin	= 1<<OUT_MED_BRAKING;	
	EXTI_ClearFlag(EXTI_Line3);
  IN_INT=-2;

	if(GPIOB->IDR & in_pin) {
      GPIOC->ODR |= out_pin;                 // switch LED ON
	} else {
      GPIOC->ODR &= ~out_pin;                 // switch LED OFF
	}
}

void EXTI4_IRQHandler(void) {  // EXTI4_IRQn
	unsigned int in_pin		= 1<<PIN_MIN_BRAKING;
	unsigned int out_pin	= 1<<OUT_MIN_BRAKING;	
	EXTI_ClearFlag(EXTI_Line4);
  IN_INT=-1;

	if(GPIOB->IDR & in_pin) {
      GPIOC->ODR |= out_pin;                 // switch LED ON
	} else {
      GPIOC->ODR &= ~out_pin;                 // switch LED OFF
	}
}
