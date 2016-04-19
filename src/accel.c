/*
 * accel.c
 *
 *  Created on: Apr 18, 2016
 *      Author: kyle
 */

#include "accel.h"
#include "stm32f0xx_adc.h"

void ADC_init() {
	// Enable clocks
    RCC->APB2ENR |= RCC_APB2ENR_ADCEN;

    // Enable the proper channels for the ADC pins (PA1, PA2, PA3)
 //   ADC1->CHSELR = ADC_CHSELR_CHSEL1 | ADC_CHSELR_CHSEL2 | ADC_CHSELR_CHSEL3; // Change this!

    // Configure ADC
    ADC_InitTypeDef  ADC_Accel;
    ADC_Accel.ADC_Resolution = ADC_Resolution_12b;
    ADC_Accel.ADC_ContinuousConvMode = DISABLE;
    ADC_Accel.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_Accel.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_Init(ADC1, &ADC_Accel);

    // Calibrate
    ADC1->CR = 0;
    ADC1->CR |= ADC_CR_ADCAL;               // Perform self calibration
    while(ADC1->CR & ADC_CR_ADCAL);         // Delay until calibration is complete

    // Enable
    ADC1->CR |= ADC_CR_ADEN;                // Enable ADC
    while(!(ADC1->ISR & ADC_ISR_ADRDY));    // Wait until ADC ready
    //ADC1->CR |= ADC_CR_ADSTART;             // Signal conversion start
}

//Accelerometer blocking ADC read function. This reads the
//channel sent to the function as ADC_Chan at a rate of
//SampleTime. The function then waits until the conversion
//is complete and returns the converted value!
uint16_t ReadADC(uint32_t channel, uint32_t SampleTime){
	ADC_ChannelConfig(ADC1, channel, SampleTime);
	ADC_StartOfConversion(ADC1);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	return ADC1->DR;;
}
