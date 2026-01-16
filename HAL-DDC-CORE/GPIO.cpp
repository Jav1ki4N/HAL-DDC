/*******************************************/
/* *              GPIO                     */
/* *         GPIO Expansion                */
/* *         Part of HAL-DDC               */
/* *            2026 @i4N                  */
/*******************************************/
/* * Personally I don't think GPIO should  */
/* * have a class                          */
/*******************************************/
/* * This is functional only if GPIO is    */
/* * Configured via CubeMX, itself doesn't */
/* * intend to init any hardware           */
/*******************************************/

#include "GPIO.hpp"

void Pin::High() 
{
    if(port&&pin_num)
    {
        port->BSRR = pin_num;
    }
   
}

void Pin::Low() 
{
    if(port&&pin_num)
    {
        port->BSRR = (uint32_t)pin_num << 16U;
    }   
}

void Pin::Toggle() 
{
    if(port&&pin_num)
    {
        port->ODR ^= pin_num;
    }
}

Pin GPIO_Register(GPIO_Port port, GPIO_Pin pin_num)
{
    return Pin{port, pin_num};
}