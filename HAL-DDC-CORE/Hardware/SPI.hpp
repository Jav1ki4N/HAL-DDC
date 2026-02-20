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

class SPIBus
{
    public:

    /* * Constructor */

    SPIBus(SPI_HandleTypeDef* hspi)
    :HSPI(hspi)
    {}

    /* * Vars */

    SPI_HandleTypeDef* HSPI = nullptr;

    /* * APIs */

    bool isBusy()
    {
        return (HAL_SPI_GetState(HSPI) != HAL_SPI_STATE_READY);
    }

    void Transmit_Core(byte* data, uint16_t size)
    {
        while(isBusy());
        HAL_SPI_Transmit(HSPI, data, size, HAL_MAX_DELAY);
    }

    /**********************************************************/

    void Transmit_Core_DMA(byte* data, uint16_t size)
    {
        HAL_SPI_Transmit_DMA(HSPI, data, size);
        /* todo */
        //while (HAL_SPI_GetState(HSPI) != HAL_SPI_STATE_READY);
    }
};

class SPIDevice
{
    public:

    enum class Polarity:bool
    {
        ACTIVATE_AT_LOW  = true, // Chip selected at CS low
        ACTIVATE_AT_HIGH = false // Chip selected at CS high
    };

    enum class Line:uint8_t
    {
        FOUR = 4,
        THREE = 3,
    };

    /* * Constructor */
    SPIDevice(SPIBus*       bus,
              uint16_t      rst_pin,
              uint16_t      cs_pin,
              uint16_t      dc_pin,
              GPIO_TypeDef* rst_port,
              Polarity      polarity,
              Line          line,
              GPIO_TypeDef* cs_port  = nullptr,
              GPIO_TypeDef* dc_port  = nullptr
    )
    :spi(bus),
     polarity(polarity), 
     line(line), 
     RST(rst_port, rst_pin), 
     CS((cs_port)?cs_port:rst_port, cs_pin), 
     DC((dc_port)?dc_port:rst_port, dc_pin)
    {
        assert_param(bus!=nullptr);
    }
    

    /* * Vars */

    SPIBus*  spi = nullptr;
    Polarity polarity;
    Line     line;
    

    enum class DataType:bool
    {
        DATA    = true, // sends data
        COMMAND = false // sends command
    };

    /* * APIs */

    template <size_t N>
    void Transmit( byte (&data)[N],
                   DataType type     = DataType::DATA,
                   uint16_t size     = N             )
    {
        if(line == Line::FOUR)(type == DataType::DATA)?DC.High():DC.Low (); // data type
        (polarity == Polarity::ACTIVATE_AT_LOW)?       CS.Low ():CS.High(); // chip selected
        spi->Transmit_Core(data, size);
        (polarity == Polarity::ACTIVATE_AT_LOW)?       CS.High():CS.Low (); // chip deselected
    }

    void Transmit( byte     data,
                   DataType type = DataType::DATA )
    {
        if(line == Line::FOUR)(type == DataType::DATA)?DC.High():DC.Low (); // data type
        (polarity == Polarity::ACTIVATE_AT_LOW)?       CS.Low ():CS.High(); // chip selected
        spi->Transmit_Core(&data, 1);
        (polarity == Polarity::ACTIVATE_AT_LOW)?       CS.High():CS.Low (); // chip deselected
    }

    /***/
    /* todo: DMA */

 protected:

    /* * Vars */
    Pin RST,CS,DC;
};
