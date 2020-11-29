/*----------------------------------------------------------------------------
 * Name:    BlinkySingleLED_commanded_IE.c
 * Purpose: Turn on/off LED depending on input, managed via interrupt
 *----------------------------------------------------------------------------*/

#include <stm32f10x.h>                       /* STM32F103 definitions         */
#include "stm32f10x_it.h"
#include "misc.h"
#include "RTL.h"
#include "pins_definition.h"
#include "BrakingController.h"
#include "EngineController.h"
#include "LeverController.h"
#include "StopSignalController.h"

extern volatile int T1 = 0, T2 = 0, IDLE = 1;

//volatile int Eid = 0x01;
volatile int E2id = 0x02;

OS_TID Tid;         // Task1 (lever_input manager) id
OS_TID T2id;				// Task2 (stop_signal manager) id

volatile int current_Pin;

__task void Task1(void) {

	unsigned int last_Pin = PIN_IDLE_LEVER;					// Value of the last Pin enabled
	int ticks_max_accel = -1;
	int ticks_no_input	= -1;
	
	os_itv_set(1);																	// Tick set to last 10ms
	
	while(1) {
		os_itv_wait();																// Sleep for the duration of a tick
		T1 = 1; T2 = 0; IDLE = 0;
		current_Pin = GPIOB->IDR;											// Update the value of the Pin currently enabled
		if(current_Pin != last_Pin) {
			switch(current_Pin) {
				case PIN_MAX_BRAKING:
					enableMaxBrakingPower();
					break;
				case PIN_MED_BRAKING:
					enableMedBrakingPower();
					break;
				case PIN_MIN_BRAKING:
					enableMinBrakingPower();
					break;
				case PIN_IDLE_LEVER:
					disableBraking();
					disableEngine();
					break;
				case PIN_MIN_ACCEL:
					enableMinEnginePower();
					break;
				case PIN_MED_ACCEL:
					enableMedEnginePower();
					ticks_max_accel = -1;										// Reset the number of ticks (probably useless)
					break;
				case PIN_MAX_ACCEL:
					enableMaxEnginePower();
					ticks_max_accel = os_time_get();
					break;
				case NO_INPUT:
					ticks_no_input = os_time_get();
			}
			last_Pin = current_Pin;
		}
		
		if(current_Pin == PIN_MAX_ACCEL && (os_time_get() - ticks_max_accel) == 400) {			// If the MAX_ACCEL Pin has been on for 4s (400 * 10ms = 4s)
			enableMedEnginePower();																												// Set the engine power to MED_POWER
			ticks_max_accel = -1;																													// Reset the ticks_max_accel variable
		} 
		
		if(current_Pin == NO_INPUT && (os_time_get() - ticks_no_input) == 500) {
			disableEngine();
			enableMedBrakingPower();
			ticks_no_input = -1;
			// Eventually, we can consider to invoke the stop signal procedure
		}
	}
}

__task void Task2(void) {
	while(1) {
		os_evt_wait_or(E2id, 0xFFFF);
		T1 = 0; T2 = 1; IDLE = 0;
		disableEngine();									// Disable engine acceleration
		enableMedBrakingPower();					// Enable MED_POWER braking
		while(isStopSignalEnabled()) {
			// Wait the STOP_SIGNAL Pin to be cleared...
		}
		while(!isLeverIdle()) {
			// Wait the LEVER to be set in the IDLE position...
		}
	}
}

__task void TaskInit(void) {	
  Tid = os_tsk_create( Task1, 10 );
	T2id = os_tsk_create( Task2, 70 );
  //TBid = os_tsk_create( TaskB, 1 );
  //T3id = os_tsk_create( Task3, 80 );
	//TsimIdm = os_tsk_create( TaskSim, 99 );

  os_tsk_delete_self();      // kills self
}


/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/

int main(void) {
	
	initBrakingController();
	initEngineController();
	initLeverController();
	
	initStopSignalController();
	
	os_sys_init( TaskInit );
}
