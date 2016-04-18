//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stm32f0xx_adc.h>
#include "diag/Trace.h"

// ----------------------------------------------------------------------------
//
// Standalone STM32F0 empty sample (trace via $(trace)).
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the $(trace) output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

int
main(int argc, char* argv[])
{
	// Initialize parameters for interfacing with ADXL335
	uint16_t X0,Y0,Z0;		// Initial reading for comparison
	uint16_t X,Y,Z;			// Read x,y,z angle from accel
	uint16_t delta_angle; 	// Pre-defined minimum distance for alarm to sound

	// Enable clock

	// Initialize button

	// Initialize LED/speaker

	// Initialize systick timer

	// Initialize pins for ADC input (pins PA1,PA2,PA3)

	// Initialize ADC
		// ADC_Init()

	// Turn on system (walk away from locked bike...done with app, button code, or fingerprint?)
	// USE button for now...

	// Armed = TRUE;

	// Initial read from ADC into X0,Y0,Z0

	// while (1) {

		// Read from ADC into X,Y,Z

		// Compare read angle with initial to compare tilt

			// if greater than pre-defined magnitude, set off alarm

			// while(~code_correct) {
				// Check for button input to shut off alarm

				// Otherwise keep the alarm sounding


	// }

}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
