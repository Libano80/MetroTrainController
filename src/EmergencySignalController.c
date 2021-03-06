/*----------------------------------------------------------------------------
 * Name:    EmergencySignalController.c
 * Purpose: Definition of the communication specifics with the Emergency 
 * 					Braking signal button
 *----------------------------------------------------------------------------*/

#include <stm32f10x.h>                       /* STM32F103 definitions         */
#include "EmergencySignalController.h"
#include "EXTI_pins_configuration.h"

void initEmergencySignalController(void) {
	Configure_EXTI_GPIOB0();
}
