#include "cppmain.h"
#include "GPIO.hpp"
#include "TIMER.hpp"
#include "SERIAL.hpp"
#include "stm32f411xe.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_uart.h"
#include "tim.h"
#include "usart.h"


/******************************/
/* *    GLOBAL POINTERS       */
/******************************/

Pin* pled{nullptr};
SERIAL* pport{nullptr};

/******************************/
/* *     MAIN FUNCTION        */
/******************************/

void cppmain()
{
    Pin led(GPIOC, GPIO_PIN_13);
    pled = &led;
    Timer timer(&htim3);
    timer.Start(Timer::FUNC::IT);
    SERIAL port(&huart1);
    pport = &port;
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
        //0x42000000 + (offset<<5)+(n<<2);
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
            if(pport){
                pport->Print("Hello from HAL-DDC!\r\n");
            }

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

/*******************************/
/* *     UART CALLBACK         */
/*******************************/

extern "C" void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

}

/* UART IDLE */

extern "C" void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if(huart->Instance == USART1)
    {
        
    }
    if(huart->Instance == USART2)
    {

    }

    # if defined (USART3)
    if(huart->Instance == USART3)
    {

    }
    # endif

    # if defined (UART4)
    if(huart->Instance == UART4)
    {

    }
    # endif
}