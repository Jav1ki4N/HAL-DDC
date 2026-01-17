#include "cppmain.h"
#include "GPIO.hpp"
#include "TIMER.hpp"
#include "stm32f411xe.h"
#include "stm32f4xx_hal_gpio.h"
#include "tim.h"

/******************************/
/* *    GLOBAL POINTERS       */
/******************************/

Pin* pled{nullptr};

/******************************/
/* *     MAIN FUNCTION        */
/******************************/

void cppmain()
{
    Pin led(GPIOC, GPIO_PIN_13);
    pled = &led;
    Timer timer(&htim3);
    timer.Start(Timer::FUNC::IT);
    for(;;)
    {
        // HAL_Delay(100);
        // led.Toggle();
    }
}

/*******************************/
/* *    TIMER CALLBACK         */
/*******************************/

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
        if(count >= 50)
        {
            count = 0;
            if(pled)pled->Toggle();
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