/***************************************/
/* *              SPI                  */
/* *         SPI Expansion             */
/* *            HAL-DDC                */
/* *           2026 @i4N               */
/***************************************/

#pragma once

/* * Series Control */
#include "SERIES.hpp"

/* * HAL Libs */
#include "spi.h"
#include "stm32f411xe.h"

/* * C++ */

/* * HAL-DDC */
#include "GLOBAL.h"
#include "GPIO.hpp"


class SPI
{
    public:

    /* * Constructor */
    SPI(SPI_HandleTypeDef* hspi)
    :HSPI(hspi)
    {}

    /* * Public Vars */

    enum class Polarity:bool
    {
        ACTIVATE_AT_LOW  = true, // Chip selected at CS low
        ACTIVATE_AT_HIGH = false // Chip selected at CS high
    };

    enum class DataType:bool
    {
        DATA    = true, // sends data
        COMMAND = false // sends command
    };

    enum class LINE:uint8_t
    {
        FOUR = 4,
        THREE = 3,
    };

    /* * Public APIs */
    
    void Register_RST(GPIO_TypeDef*p, uint16_t n)
    {RST = Pin(p, n);}
    
    void Register_CS(GPIO_TypeDef*p, uint16_t n)
    {CS = Pin(p, n);}

    void Register_DC(GPIO_TypeDef*p, uint16_t n)
    {DC = Pin(p, n);}

    protected:

    /* * Vars */

    SPI_HandleTypeDef* HSPI = nullptr;
    Pin RST, // Reset
        CS,  // Chip Select 
        DC;  // Data/Command

    void SendCore(){}

    private:
};