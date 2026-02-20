/**********************/
/* * ST7789V TFT LCD  */
/* *     HAL-DDC      */
/* *    2026 @i4N     */
/**********************/ 

#pragma once

/* * Series Control */
/* * HAL Libs */
/* * C++ */
/* * Third Party */
#include "FreeRTOS.h"
/* * HAL-DDC */
#include "GLOBAL.h"
#include "GPIO.hpp"
#include "SPI.hpp"
#include "cmsis_os2.h"
#include "stm32f4xx_hal_conf.h"

class ST7789V : public SPIDevice
{
    public:

    /* * Constructor */
    ST7789V(SPIBus*       bus,     // a SPI bus instance required
            uint16_t      rst_pin,
            uint16_t      cs_pin,
            uint16_t      dc_pin,
            GPIO_TypeDef* rst_port,
            Polarity      polarity = Polarity::ACTIVATE_AT_LOW,
            Line          line     = Line::FOUR,
            GPIO_TypeDef* cs_port  = nullptr,
            GPIO_TypeDef* dc_port  = nullptr
    )
    :SPIDevice(bus, rst_pin, cs_pin, dc_pin, rst_port, polarity, line, cs_port, dc_port)
    {}

    /* * Public vars */

    struct SPEC
    {
        static constexpr uint16_t XS = 0,      // Address window min & max
                                  XE = 239,
                                  YS = 0,
                                  YE = 319;

        static constexpr uint16_t WIDTH  = 240,
                                  HEIGHT = 320;
    };

    struct CMD
    {
        static constexpr command SLEEP_OUT {0x11},
                                 INVON     {0x21},
                                 MADCTL    {0x36},
                                 COLMOD    {0X3A},
                                 PORCTRL   {0xB2},
                                 GCTRL     {0xB7},
                                 GTADJ     {0xB8},
                                 VCOMS     {0xBB},
                                 LCMCTRL   {0xC0},
                                 VDVVRHEN  {0xC2},
                                 VRHS      {0xC3},
                                 VDVS      {0xC4},
                                 FRCTRL2   {0xC6},
                                 PWCTRL1   {0xD0},
                                 PVGAMCTRL {0xE0},
                                 NVGAMCTRL {0xE1},
                                 DISPON    {0x29},

                                 CASET     {0x2A},
                                 RASET     {0x2B},
                                 RAMWR     {0x2C};
    };

    /* * Public APIs */

    protected:

    void Init_Seq()
    {
        RST.Low();
        osDelay(10);
        RST.High();
        osDelay(120);

        Transmit(CMD::SLEEP_OUT, DataType::COMMAND);
        osDelay(120);
    }

    /* * Vars */


    /* * APIs */

    void Hardware_InitSeq()
    {

    }
};