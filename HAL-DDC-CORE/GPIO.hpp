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

#pragma once

/* * Series Control */
#include "SERIES.hpp"

/* * HAL Libs */
#include "gpio.h"

/* * type defines */
using GPIO_Port = GPIO_TypeDef*;
using GPIO_Pin  = uint16_t;

struct Pin
{
    GPIO_Port port    = nullptr; 
    GPIO_Pin  pin_num = 0;       // GPIO_PIN_x
    Pin() = default;
    Pin(GPIO_Port p, GPIO_Pin n) : port(p), pin_num(n) {}
    void High  ();
    void Low   ();
    void Toggle();
};

Pin GPIO_Register(GPIO_Port   port,
                  GPIO_Pin    pin_num);

