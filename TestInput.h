#ifndef _TEST_INPUT_H
#define _TEST_INPUT_H

#include "TestSimulation.h"
#include "pins_definition.h"

#ifdef TEST_MODE

#define SIMPLE_LEVER_SIM
//#define NO_INPUT_LEVER_SIM
//#define STOP_SIGNAL_SIM
//#define EMERGENCY_BRAKING_SIM
//#define COMM_MESSAGES_SIM

typedef struct {
	unsigned int evt;
	unsigned int task_nr;
	unsigned int delay;
} Input_Simulation;

#ifdef SIMPLE_LEVER_SIM
extern Input_Simulation input_simulation_array[10] = {
		{PIN_IDLE_LEVER, 						1, 50},
		{PIN_MIN_ACCEL, 						1, 50},
		{PIN_MED_ACCEL, 						1, 50},
		{PIN_MAX_ACCEL, 						1, 500},
		{PIN_MED_ACCEL, 						1, 50},
		{PIN_MIN_ACCEL,							1, 50},
		{PIN_IDLE_LEVER,						1, 50},
		{PIN_MIN_BRAKING,						1, 50},
		{PIN_MED_BRAKING,						1, 50},
		{PIN_MAX_BRAKING,						1, 50}
	};
#endif		//	#ifdef SIMPLE_LEVER_SIM

#ifdef NO_INPUT_LEVER_SIM
extern Input_Simulation input_simulation_array[10] = {
		{PIN_IDLE_LEVER, 						1, 50},
		{PIN_MIN_ACCEL, 						1, 50},
		{PIN_MED_ACCEL, 						1, 50},
		{PIN_MAX_ACCEL, 						1, 50},
		{PIN_MED_ACCEL, 						1, 50},
		{PIN_MIN_ACCEL,							1, 50},
		{NO_INPUT,									1, 350},		// The system does not receive inputs for more than 3s (350 * 10ms = 3,5s)
		{PIN_IDLE_LEVER,						1, 50},
		{PIN_MAX_ACCEL,							1, 50},
		{PIN_MIN_BRAKING,						1, 50}
	};
#endif		//	#ifdef NO_INPUT_LEVER_SIM

#ifdef STOP_SIGNAL_SIM
extern Input_Simulation input_simulation_array[10] = {
		{PIN_MIN_BRAKING, 					1, 50},
		{PIN_MED_BRAKING, 					1, 50},
		{PIN_MIN_BRAKING, 					1, 50},
		{PIN_IDLE_LEVER, 						1, 50},
		{PIN_MIN_ACCEL,							1, 50},
		{STOP_SIGNAL_ENABLED,				2, 50},			// The system receives a stop signal
		{PIN_MIN_BRAKING,						1, 50},
		{STOP_SIGNAL_DISABLED,			2, 50},			// The stop signal is cleared
		{PIN_IDLE_LEVER,						1, 50},			// The lever is set in idle position
		{PIN_MIN_BRAKING,						1, 50}
	};
#endif		//	#ifdef STOP_SIGNAL_SIM

#ifdef EMERGENCY_BRAKING_SIM
extern Input_Simulation input_simulation_array[10] = {
		{PIN_MIN_BRAKING, 					1, 50},
		{PIN_MED_BRAKING, 					1, 50},
		{PIN_MAX_BRAKING, 					1, 50},
		{PIN_MED_BRAKING, 					1, 50},
		{PIN_MIN_BRAKING,						1, 50},
		{PIN_IDLE_LEVER,						1, 50},
		{PIN_MIN_BRAKING,						1, 50},
		{EMERGENCY_SIGNAL_ENABLED,	3, 50},			// The system receives an emergency braking signal
		{PIN_MIN_BRAKING,						1, 50},
		{PIN_MIN_ACCEL,							1, 50}
	};
#endif		//	#ifdef EMERGENCY_BRAKING_SIM

#ifdef COMM_MESSAGES_SIM
extern Input_Simulation input_simulation_array[10] = {
		{PIN_MAX_ACCEL,	 						1, 50},
		{'T', 											4, 50},			// The system receives an char from the TMC
		{'e',												4, 50},
		{'s',												4, 50},
		{'t',												4, 50},
		{'i',												4, 50},
		{'n',												4, 50},
		{'g',												4, 50},
		{'.',												4, 50},
		{PIN_IDLE_LEVER, 						1, 50}
	};
#endif		//	#ifdef COMM_MESSAGES_SIM

#endif		//	#ifdef TEST_MODE

#endif		//	#ifndef _TEST_INPUT_H
