# MetroTrainController

Authors: 
 - Selva Stefano
 - Gatto Marco

The MetroTrainController project is a program for the ST 'STM32F103RB' microcontroller
using Keil 'MCBSTM32' Evaluation Board.
Compliant to Cortex Microcontroller Software Interface Standard (CMSIS V2.0).

The details concerning the specification, design and testing phases can be found in the 
'Report Project.pdf' file.

Example functionality:
 - Clock Settings:
   - XTAL    =            8.00 MHz
   - SYSCLK  =           72.00 MHz
   
The program is available in different targets:

 - STM32F103 Simulator:  configured for software Simulator

 - STM32F103 Flash:      configured for on-chip Flash
				(used for production or target debugging)

In order to run the software using the STM32F103 Simulator, the project environment must be configured.

Specifically, you need to:
 - Download the STM32F10x_StdPeriph_Lib library 
	Version used during the development phase: V3.4.0
 - Place the content of the folder Libraries (STM32F10x_StdPeriph_Driver) at the same depth
	of the 'src' project directory.
	 - E.g.
	 
	 	/metrotraincontroller/src
		
	 	/metrotraincontroller/STM32F10x_StdPeriph_Driver
	 	
		..


The automatic testing is disabled by default.

In order to enable the testing mode and use the test cases described in the Project relation, 
	you need to uncomment the TEST_MODE constant in the TestSimulation.h file.

After that, you can choose the test can you want to run by leaving uncommented ONLY ONE of the constants
	defined in the TestInput.h file. The default test case enabled is the one that checks the 
	correctness of the driver lever management.
