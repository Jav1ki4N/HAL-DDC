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

extern "C" void Task_LEDB(void *argument)
{
    /* * Objects */
    //static Pin ledB(GPIOA,GPIO_PIN_0);
    static PWM pwm(&htim2, TIM_CHANNEL_1);
    uint8_t duty = 0;

    /* * Pointer Assignment */
    //pled = &ledB;

    /* * Init */
    pwm.Start();
    /* * Loop */

    for(;;)
    {
        osSemaphoreAcquire(isLEDAFlippedHandle, osWaitForever);
        //osMessageQueueGet(LEDA2LEDBHandle, &duty, 0, osWaitForever);
        
        duty += 20;
        if(duty > 100) duty = 0;
        
        pwm.Set_Duty(duty);  
        
        
        // ledB.Toggle();
        // vTaskDelay(pdMS_TO_TICKS(500));
    }
}