/*******************************************/
/* *              GPIO                     */
/* *         GPIO Expansion                */
/* *         Part of HAL-DDC               */
/* *            2026 @i4N                  */
/*******************************************/
/* * This is functional only if GPIO is    */
/* * Configured via CubeMX, itself doesn't */
/* * intend to init any hardware           */
/*******************************************/

#pragma once

/* * Series Control */
#include "SERIES.hpp"

/* * HAL Libs */
#include "gpio.h"

/* * C++ */


class Pin
{
    public:

    /* * type defines */
    using GPIO_Port = GPIO_TypeDef*;
    using GPIO_Pin  = uint16_t;

    /* * Costructor */
    Pin(GPIO_Port p, GPIO_Pin n)
    : port(p), pin_num(n)
    {
      
    }
   
    /* * Public APIs */
    void High(){if(port&&pin_num)port->BSRR = pin_num;}

    void Low() {if(port&&pin_num)port->BSRR = (uint32_t)pin_num << 16U;}

    void Toggle(){if(port&&pin_num)port->ODR ^= pin_num;}
    

    protected:
    GPIO_Port port        = nullptr;
    GPIO_Pin  pin_num     = 0;       // GPIO_PIN_x
  
};


