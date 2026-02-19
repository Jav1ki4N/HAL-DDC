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
#include "stm32f4xx_hal_spi.h"


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

    /***********************************************************/

    /* Core of none-DMA send sequence */
    void SendCore( byte*    data,
                   uint16_t size,
                   DataType type,
                   Polarity polarity = Polarity::ACTIVATE_AT_LOW,
                   LINE     line     = LINE::FOUR               )
    {
        if(line == LINE::FOUR)(type == DataType::DATA) ? DC.High() : DC.Low();
        (polarity == Polarity::ACTIVATE_AT_LOW) ?        CS.Low()  : CS.High();
        HAL_SPI_Transmit(HSPI, data, size, HAL_MAX_DELAY);
        (polarity == Polarity::ACTIVATE_AT_LOW) ?        CS.High() : CS.Low();
    }

    /* normal none-DMA send function, data can be single or string/array */
    template<size_t N>
    void Send( byte     (&data)[N],
               DataType type,
               uint16_t size = N,
               Polarity polarity = Polarity::ACTIVATE_AT_LOW,
               LINE     line     = LINE::FOUR               )
    {
        SendCore(data,size,type,polarity,line);
    }

    void Send( byte     data,
			   DataType type,
			   Polarity polarity = Polarity::ACTIVATE_AT_LOW,
			   LINE     line     = LINE::FOUR               )
	{
		SendCore(&data,1,type,polarity,line);
	}
    
    /***************************************************************/

    /* Core of DMA send sequence */
    void SendCore_DMA( byte*    data,
                       uint16_t size,
                       DataType type,
                       Polarity polarity = Polarity::ACTIVATE_AT_LOW,
                       LINE     line     = LINE::FOUR               )
    {
        if(line == LINE::FOUR)(type == DataType::DATA) ? DC.High() : DC.Low();
        (polarity == Polarity::ACTIVATE_AT_LOW) ?        CS.Low()  : CS.High();
        HAL_SPI_Transmit_DMA(HSPI, data, size);
        // Chip unselect is handled in the DMA complete callback
        while (HAL_SPI_GetState(HSPI) != HAL_SPI_STATE_READY);
    }

    /* normal DMA send function, data can be single or string/array */
    template<size_t N>
    void Send_DMA( byte     (&data)[N],
               DataType type,
               uint16_t size = N,
               Polarity polarity = Polarity::ACTIVATE_AT_LOW,
               LINE     line     = LINE::FOUR               )
    {
        SendCore_DMA(data,size,type,polarity,line);
    }

    void Send_DMA( byte     data,
			   DataType type,
			   Polarity polarity = Polarity::ACTIVATE_AT_LOW,
			   LINE     line     = LINE::FOUR               )
	{
		SendCore_DMA(&data,1,type,polarity,line);
	}

    /* Chip unselect function on DMA completion */
    void On_DMAComplete(Polarity polarity = Polarity::ACTIVATE_AT_LOW)
    {
        (polarity == Polarity::ACTIVATE_AT_LOW) ? CS.High() : CS.Low();
    }

    protected:

    /* * Vars */

    SPI_HandleTypeDef* HSPI = nullptr;
    Pin RST, // Reset
        CS,  // Chip Select 
        DC;  // Data/Command
    private:
};