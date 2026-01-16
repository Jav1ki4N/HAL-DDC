#include "cppmain.h"
#include "GPIO.hpp"
#include "TIMER.hpp"
#include "stm32f411xe.h"
#include "stm32f4xx_hal_gpio.h"
#include "tim.h"

void cppmain()
{
    Pin led(GPIOC, GPIO_PIN_13);
    Timer timer(&htim3);
    timer.Start(Timer::FUNC::IT);
    for(;;)
    {
        // HAL_Delay(100);
        // led.Toggle();
    }
}
