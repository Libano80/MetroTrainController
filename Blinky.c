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
#include "EmergencySignalController.h"

extern volatile int T1 = 0, T2 = 0, T3 = 0, T4, IDLE = 1;

volatile int STOP_SIGNAL_EVENT_ID				= 0x02;
volatile int EMERGENCY_BRAKING_EVENT_ID = 0x03;
volatile int SYSTEM_LOCK_EVENT_ID				= 0x04;

OS_TID Tid;         // Task1 (lever_input manager)				id
OS_TID T2id;				// Task2 (stop_signal manager) 				id
OS_TID T3id;				// Task3 (emergency_braking manager)	id
OS_TID T4id;				// Task4 (system_lock)								id

__task void Task1(void) {

	unsigned int current_position;
	unsigned int last_position = PIN_IDLE_LEVER;				// Value of the last Pin enabled
	int ticks_max_accel = -1;
	int ticks_no_input	= -1;
	
	os_itv_set(1);																			// Tick set to last 10ms
	
	while(1) {
		os_itv_wait();																		// Sleep for the duration of a tick
		T1 = 1; T2 = 0; T3 = 0; T4 = 0; IDLE = 0;
		current_position = getLeverCurrentPosition();			// Update the value of the Pin currently enabled
		if(current_position != last_position) {
			switch(current_position) {
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
					ticks_max_accel = -1;												// Reset the number of ticks (probably useless)
					break;
				case PIN_MAX_ACCEL:
					enableMaxEnginePower();
					ticks_max_accel = os_time_get();
					break;
				case NO_INPUT:
					ticks_no_input = os_time_get();
			}
			last_position = current_position;
		}
		
		// If the MAX_ACCEL Pin has been on for 4s (400 * 10ms = 4s)
		if(current_position == PIN_MAX_ACCEL && (os_time_get() - ticks_max_accel) == 400) {		
			ticks_max_accel = -1;														// Reset the ticks_max_accel variable			
			enableMedEnginePower();													// Set the engine power to MED_POWER
		} 
		
		// If no input is received for more than 3s (300 * 10ms = 3s)
		if(current_position == NO_INPUT && (os_time_get() - ticks_no_input) == 300) {						
			ticks_no_input = -1;														// Reset the ticks_no_input variable
			disableEngine();
			enableMedEnginePower();
			os_evt_set(SYSTEM_LOCK_EVENT_ID, T4id);
		}
	}
}

__task void Task2(void) {
	while(1) {
		os_evt_wait_or(STOP_SIGNAL_EVENT_ID, 0xFFFF);
		T1 = 0; T2 = 1; T3 = 0; T4 = 0; IDLE = 0;
		disableEngine();																	// Disable engine acceleration
		enableMedBrakingPower();													// Enable MED_POWER braking
		while(isStopSignalEnabled()) {
			// Wait the STOP_SIGNAL Pin to be cleared...
		}
		while(!isLeverIdle()) {
			// Wait the LEVER to be set in the IDLE position...
		}
	}
}

__task void Task3(void) {
	while(1) {
		os_evt_wait_or(EMERGENCY_BRAKING_EVENT_ID, 0xFFFF);
		T1 = 0; T2 = 0; T3 = 1; T4 = 0; IDLE = 0;
		disableEngine();																	// Disable engine acceleration
		enableEmergencyBrakingPower();										// Enable EMERGENCY braking
		os_evt_set(SYSTEM_LOCK_EVENT_ID, T4id);
	}
}

__task void Task4(void) {
	os_evt_wait_or(SYSTEM_LOCK_EVENT_ID, 0xFFFF);
	T1 = 0; T2 = 0; T3 = 0; T4 = 1; IDLE = 0;
	while(1) {
		// Wait undefinitely (until the system is manually reset)...
	}
}

__task void TestSimulation(void) {
	//...
}

__task void TaskInit(void) {	
  Tid		= os_tsk_create( Task1, 10 );
	T2id	= os_tsk_create( Task2, 70 );
	T3id	= os_tsk_create( Task3, 90 );
	T4id 	= os_tsk_create( Task4, 95 );
  //TBid = os_tsk_create( TaskB, 1 );
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
	initEmergencySignalController();
	
	os_sys_init( TaskInit );
}
