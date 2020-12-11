/*----------------------------------------------------------------------------
 * Name:    StopSignalController.c
 * Purpose: Definition of the communication specifics with the Stop Signal 
 * 					button
 *----------------------------------------------------------------------------*/

#include <stm32f10x.h>                       /* STM32F103 definitions         */
#include "StopSignalController.h"
#include "EXTI_pins_configuration.h"
#include "pins_definition.h"
#include "TestSimulation.h"

#ifdef TEST_MODE
extern unsigned int stop_signal;
#endif

void initStopSignalController(void) {
	Configure_EXTI_GPIOB1();
}

unsigned int isStopSignalEnabled(void) {
	#ifdef TEST_MODE
	return stop_signal;
	#else
	return GPIOB->IDR & PIN_STOP_SIGNAL;
	#endif
}
