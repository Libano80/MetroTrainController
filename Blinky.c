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
#include "CommMessageReceiverController.h"
#include "CommMessageSenderController.h"

#define TEST_MODE 888

extern volatile int T1 = 0, T2 = 0, T3 = 0, T4 = 0, TSim = 0, IDLE = 1;

volatile int STOP_SIGNAL_EVENT_ID				= 0x02;
volatile int EMERGENCY_BRAKING_EVENT_ID	= 0x04;
volatile int COMM_MESSAGE_EVENT_ID			= 0x08;

OS_TID Tid;         // Task1					(lever_input manager)				id
OS_TID T2id;				// Task2 					(stop_signal manager) 			id
OS_TID T3id;				// Task3 					(emergency_braking manager)	id
OS_TID T4id;				// Task4					(comm_messages manager)			id

char TMC_char_received;

#ifdef TEST_MODE
OS_TID TSimid;			// TaskSimulation (test_cases manager)				id
unsigned int lever_position;
unsigned int stop_signal;
unsigned int emergency_braking_signal;
#endif

__task void Task1(void) {

	unsigned int current_pos;														// Value of the current position of the lever
	unsigned int last_pos = PIN_IDLE_LEVER;							// Value of the last position of the lever
	int ticks_max_accel = -1;
	int ticks_no_input	= -1;
	
	os_itv_set(1);																			// Tick set to last 10ms
	
	while(1) {
		os_itv_wait();																		// Sleep for the duration of a tick
		T1 = 1; T2 = 0; T3 = 0; T4 = 0;
		TSim = 0; IDLE = 0;
		#ifdef TEST_MODE
		current_pos = lever_position;
		#else
		current_pos = getLeverCurrentPosition();					// Update the value of the Pin currently enabled
		#endif
		if(current_pos != last_pos) {
			switch(current_pos) {
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
			last_pos = current_pos;
		}
		
		// If the MAX_ACCEL Pin has been on for 4s (400 * 10ms = 4s)
		if(current_pos == PIN_MAX_ACCEL && (os_time_get() - ticks_max_accel) == 400) {		
			ticks_max_accel = -1;														// Reset the ticks_max_accel variable			
			enableMedEnginePower();													// Set the engine power to MED_POWER
		} 
		
		// If no input is received for more than 3s (300 * 10ms = 3s)
		if(current_pos == NO_INPUT && (os_time_get() - ticks_no_input) == 300) {						
			ticks_no_input = -1;														// Reset the ticks_no_input variable
			disableEngine();
			enableMedEnginePower();
			while(1) {
				// Wait undefinitely until the system is manually reset
			}
		}
	}
}

__task void Task2(void) {
	while(1) {
		os_evt_wait_or(STOP_SIGNAL_EVENT_ID, 0xFFFF);
		T1 = 0; T2 = 1; T3 = 0; T4 = 0;
		TSim = 0; IDLE = 0;
		disableEngine();																	// Disable engine acceleration
		enableMedBrakingPower();													// Enable MED_POWER braking
		#ifdef TEST_MODE
		while(stop_signal == 1) {
			// Wait the STOP_SIGNAL to be cleared...
		}
		while(lever_position != PIN_IDLE_LEVER) {
			// Wait the LEVER to be set in the IDLE position...
		}
		#else
		while(isStopSignalEnabled()) {
			// Wait the STOP_SIGNAL Pin to be cleared...
		}
		while(!isLeverIdle()) {
			// Wait the LEVER to be set in the IDLE position...
		}
		#endif
	}
}

__task void Task3(void) {
	while(1) {
		os_evt_wait_or(EMERGENCY_BRAKING_EVENT_ID, 0xFFFF);
		T1 = 0; T2 = 0; T3 = 1; T4 = 0;
		TSim = 0; IDLE = 0;
		disableEngine();																	// Disable engine acceleration
		enableEmergencyBrakingPower();										// Enable EMERGENCY braking
		while(1) {
			// Wait undefinitely until the system is manually reset
		}
	}
}

__task void Task4(void) {
	while(1) {
		os_evt_wait_or(COMM_MESSAGE_EVENT_ID, 0xFFFF);
		T1 = 0; T2 = 0; T3 = 0; T4 = 1;
		TSim = 0; IDLE = 0;
		sendData(TMC_char_received);
	}
}

#ifdef TEST_MODE
__task void TaskSimulation(void) {
	
	unsigned int evt;
	unsigned int task_nr;
	unsigned int delay;
	unsigned int i = 0;
	
	typedef struct {
		unsigned int evt;
		unsigned int task_nr;
		unsigned int delay;
	} Input_Simulation;
	
	Input_Simulation input_simul_array[10] = {
		{PIN_IDLE_LEVER, 		1, 50},
		{PIN_MIN_BRAKING, 	1, 100},
		{PIN_MED_BRAKING, 	1, 80},
		{PIN_MIN_BRAKING, 	1, 50},
		{PIN_IDLE_LEVER, 		1, 50},
		{PIN_MIN_ACCEL,			1, 50},
		{1,									2, 50},
		//{PIN_MED_ACCEL,			1, 50},
		{0,									2, 50},
		{PIN_IDLE_LEVER,		1, 50},
		{PIN_MIN_ACCEL,			1, 50}
	};
	
	os_dly_wait(100);
	
	while(1) {
		T1 = 0; T2 = 0; T3 = 0; T4 = 0;
		TSim = 1; IDLE = 0;
		
		//read element from test_case input
		evt 			= input_simul_array[i].evt;
		task_nr	= input_simul_array[i].task_nr;
		delay 		= input_simul_array[i].delay;
		i = (i+1)%10;
		
		//simulate input
		if(task_nr == 1) {
			lever_position = evt;
		} else if(task_nr == 2) {
			stop_signal = evt;
			if(evt == 1) {
				os_evt_set(STOP_SIGNAL_EVENT_ID, T2id);
			}
		} else if(task_nr == 3) {
			os_evt_set(evt, T3id);
		} else if(task_nr == 4) {
			TMC_char_received = evt;
			os_evt_set(COMM_MESSAGE_EVENT_ID, T4id);
		}
		
		//sleep for a given amount of time
		os_dly_wait(delay);
	}
}
#endif

__task void TaskInit(void) {	
  Tid			= os_tsk_create( Task1, 10 );
	T2id		= os_tsk_create( Task2, 70 );
	T3id		= os_tsk_create( Task3, 90 );
	T4id		= os_tsk_create( Task4, 5 );
	#ifdef TEST_MODE
	TSimid	= os_tsk_create( TaskSimulation, 99 );
	#endif

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
	
	initCommMessageReceiverController();
	initCommMessageSenderController();
	
	os_sys_init( TaskInit );
}
