#include <stm32f10x.h>                       /* STM32F103 definitions         */
#include "StopSignalController.h"
#include "EXTI_pins_configuration.h"
#include "pins_definition.h"

void initStopSignalController(void) {
	Configure_EXTI_GPIOB1();
}

unsigned int isStopSignalEnabled(void) {
	return GPIOB->IDR & PIN_STOP_SIGNAL;
}
