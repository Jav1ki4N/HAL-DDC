#include "cppmain.h"
#include "TIMER.hpp"
#include "stm32f411xe.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_tim.h"

extern "C" void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM1)
    {

    }
    if(htim->Instance == TIM2)
    {

    }
    if(htim->Instance == TIM3)
    {
        static uint32_t count = 0;
        count++;
        if(count >= 1000)
        {
            count = 0;
            HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13); 
        }
    }
    if(htim->Instance == TIM4)
    {

    }

    #if defined (TIM5)
    if(htim->Instance == TIM5)
    {

    }
    #endif

    #if defined (TIM6)
    if(htim->Instance == TIM6)
    {

    }
    #endif
}