/******************/
/* * Example Task */
/* * HAL-DDC      */
/* * 2026 @i4N    */
/******************/

#include "GLOBAL.h"
#include "GPIO.hpp"
#include "TIMER.hpp"
#include "cmsis_os2.h"
#include "stm32f411xe.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_tim.h"
#include "stm32f4xx_hal_uart.h"
#include "freertos.h"
#include "task.h"
#include "tim.h"

/***********/
/* * Task  */
/***********/

extern "C" void Task_LED(void *argument)
{
    /* * Objects */

    static Pin led(GPIOC,GPIO_PIN_13);
    static PWM pwm(&htim2, TIM_CHANNEL_1);

    /* * Pointer Assignment */
    
    pled = &led;

    /* * Init */

    pwm.Start();
    pwm.Set_Duty(0.2f);
    
    /* * Loop */

    for(;;)
    {
        led.Toggle();
        osDelay(1000);
    }
}