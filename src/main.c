#include <stdio.h>
#include <stdlib.h>
#include <stm32f0xx_adc.h>
#include "diag/Trace.h"
#include "delay.h"
#include "accel.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

volatile uint32_t debouncer;
uint16_t armed;

void LED_init(void){
    // Initialize PC8 and PC9 for LED's
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;                                          // Enable peripheral clock to GPIOC
    GPIOC->MODER |= GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0;                  // Set PC8 & PC9 to outputs
    GPIOC->OTYPER &= ~(GPIO_OTYPER_OT_8 | GPIO_OTYPER_OT_9);                    // Set to push-pull output type
    GPIOC->OSPEEDR &= ~((GPIO_OSPEEDR_OSPEEDR8_0 | GPIO_OSPEEDR_OSPEEDR8_1) |
                        (GPIO_OSPEEDR_OSPEEDR9_0 | GPIO_OSPEEDR_OSPEEDR9_1));   // Set to low speed
    GPIOC->PUPDR &= ~((GPIO_PUPDR_PUPDR8_0 | GPIO_PUPDR_PUPDR8_1) |
                      (GPIO_PUPDR_PUPDR9_0 | GPIO_PUPDR_PUPDR9_1));             // Set to no pull-up/down
    GPIOC->ODR &= ~(GPIO_ODR_8 | GPIO_ODR_9);
}

void button_init(void){
    // Initialize PA0 for button input
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;                                          // Enable peripheral clock to GPIOA
    GPIOA->MODER &= ~(GPIO_MODER_MODER0_0 | GPIO_MODER_MODER0_1);               // Set PA0 to input
    GPIOC->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEEDR0_0 | GPIO_OSPEEDR_OSPEEDR0_1);     // Set to low speed
    GPIOC->PUPDR |= GPIO_PUPDR_PUPDR0_1;                                        // Set to pull-down
}

/* Called by SysTick Interrupt
 * Performs button debouncing, changes wave type on button rising edge
 * Updates frequency output from ADC value
 */
void debounce_button(void) {
    debouncer = (debouncer << 1);
    if(GPIOA->IDR & (1 << 0)) {
        debouncer |= 0x1;
    }
    if(debouncer == 0x7FFFFFFF) {
        switch(armed) {
            case 0:
                armed = 1;
                break;
            case 1:
                armed = 0;
        }
        //synth_setWave(wave);
    }
    //synth_updateFrequency();
}

 //TODO: timer 6 and interrupt handler for reading ADC inputs

int
main(int argc, char* argv[])
{
	// Initialize parameters for interfacing with ADXL335
	uint16_t X0,Y0,Z0;		// Initial reading for comparison
	uint16_t X,Y,Z;			// Read x,y,z angle from accel
	uint16_t delta_angle; 	// Pre-defined minimum distance for alarm to sound

	// Initialize button
	button_init();

	// Initialize LED/speaker
	LED_init();

	// Initialize systick timer
//    SysTick_setCallback(&debounce_button);  // Register callback to debounce and manage button

	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000);

	// Initialize pins for ADC input (pins PA1,PA2,PA3)
	GPIOA -> MODER |= GPIO_MODER_MODER1 | GPIO_MODER_MODER2 | GPIO_MODER_MODER3;  // Set PA1-3 to analog mode

	// Initialize ADC
	ADC_init();

	// Turn on system (walk away from locked bike...done with app, button, or fingerprint?)
	// USE button for now...have it switch 'armed' from true to false with each press

	// Armed = TRUE;

	uint16_t start=1;

	while (1) {

		// Read from ADC into X,Y,Z
		X = ReadADC(ADC_CHSELR_CHSEL1,1);
		Y = ReadADC(ADC_CHSELR_CHSEL2,1);
		Z = ReadADC(ADC_CHSELR_CHSEL3,1);

		// Compare read angle with initial to compare tilt
		if (~start) {
			// compare X,Y,Z to X0,Y0,Z0 (previous values)



		} else {
			start=0;
		}
			// if greater than pre-defined magnitude, set off alarm

			// while(~code_correct) {
				// Check for button input to shut off alarm

				// Otherwise keep the alarm sounding
		X0 = X;
		Y0 = Y;
		Z0 = Z;

	}

}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
