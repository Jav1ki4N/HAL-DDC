/******************/
/* * Example Task */
/* * HAL-DDC      */
/* * 2026 @i4N    */
/******************/

#include "GLOBAL.h"
#include "GPIO.hpp"
#include "TIMER.hpp"
#include "cmsis_os.h"
#include "cmsis_os2.h"
#include "projdefs.h"
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

extern "C" void Task_LEDA(void *argument)
{
    /* * Objects */

    uint8_t duty = 0;
    static Pin ledA(GPIOC,GPIO_PIN_13);
    //static PWM pwm(&htim2, TIM_CHANNEL_1);

    /* * Pointer Assignment */
    
    pled = &ledA;

    /* * Init */
    //pwm.Start();
    //pwm.Set_Duty(0.2f);
    
    /* * Loop */
    for(;;)
    {
        
        ledA.Toggle();
        osSemaphoreRelease(isLEDAFlippedHandle);
        // duty += 20;
        // if(duty > 100) duty = 0;
        // osMessageQueuePut(LEDA2LEDBHandle, &duty, 0, osWaitForever);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}