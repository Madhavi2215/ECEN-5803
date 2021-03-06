/**
\file dac.cpp

University of Colorado Boulder <br>
ECEN 5803 Mastering Embedded System Architecture <br>

DAC functions for Project 2 Module 4 <br>

*/

#include "mbed.h"
#include "waveform.h"
#include "dac.h"

/**
* Name: dac_init <br>
* Description: This function initializes Timer 3 to PWM the waveform out pin <br>
* @param [in] none
* @param [out] none
*/
void daq_init()
{
    // enable the clock to the timer
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_TIM3_CLK_ENABLE();

    // initialize PA_5 to PWM mode
    GPIOC->MODER |= GPIO_MODER_MODER9_1; //set gpioc_moder_9_1, register and keep others unchanged
    GPIOC->MODER &= ~GPIO_MODER_MODER9_Msk | GPIO_MODER_MODER9_1; //clr 
    GPIOC->AFR[1] |= GPIO_AFRH_AFSEL9_1; 
    GPIOC->AFR[1] &= ~GPIO_AFRH_AFSEL9_Msk | GPIO_AFRH_AFSEL9_1;

    // initialize timer for PWM mode
    TIM3->CR1 = 0; //Contents of preload register are transferred into the shadow register permanently or at each update event (UEV), depending on the auto-reload preload enable bit (ARPE) in TIMx_CR1 register
    TIM3->CR2 = 0;
    TIM3->EGR = TIM_EGR_UG;
    TIM3->CCMR2 = (TIM_CCMR2_OC4M_Msk & (0x6 << TIM_CCMR2_OC4M_Pos)) | TIM_CCMR2_OC4PE;
    TIM3->CCER = TIM_CCER_CC4E;
    TIM3->ARR = 437; // period of ongoing pulse
    TIM3->CCR4 = 100; //contains the duration of the t4_on period of pulse
    TIM3->CR1 |= TIM_CR1_CEN;
}

/**
* Name: dac_write <br>
* Description: This function writes a value from a lookup table to PWM <br>
* @param [in] none
* @param [out] none
*/
void dac_write()
{
    static uint32_t idx = 0;
    
    float val = waveform[idx];
    TIM3->CCR4 = (val / 3.3f * 437);
    
    if(idx == WAVEFORM_LEN){ 
        idx = 0;
    }
    else{
         idx++;
    }
}
