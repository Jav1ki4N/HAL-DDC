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
#include "lvgl.h"
/* * HAL-DDC */
#include "LVGL_UI.hpp"
#include "GLOBAL.h"
#include "GPIO.hpp"
#include "SPI.hpp"
#include "cmsis_os2.h"
#include "stm32f4xx_hal_conf.h"

class ST7789V : public SPIDevice, public LVGL_UI
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

        static constexpr uint16_t ROW_PER_BUFFER = 10;
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

    enum class Rotation : bool
    {
        PORTRAIT  = false,
        LANDSCAPE = true
    };

    /* * Public APIs */

    void Init(Rotation rot = Rotation::LANDSCAPE)
    {
        Hardware_InitSeq(rot);

        UI_Init( SPEC::WIDTH, 
                 SPEC::HEIGHT, 
                 Flush_CallBack, 
                 render_buf_A,
                 render_buf_B  );
    }
    
    protected:

    LVGL_UI::pixel render_buf_A[SPEC::WIDTH*SPEC::ROW_PER_BUFFER], // two row buffer
                   render_buf_B[SPEC::WIDTH*SPEC::ROW_PER_BUFFER];

    void Flush_Core (lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
    {

    }
    static void Flush_CallBack(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);           

    void Set_AddressWindow( coord x0,coord y0,
                            coord x1,coord y1 )
    {
        using enum DataType;
        Transmit(CMD::CASET, COMMAND);

        Transmit((x0 >> 8   ), DATA);
        Transmit((x0 &  0xFF), DATA);
        Transmit((x1 >> 8   ), DATA);
        Transmit((x1 &  0xFF), DATA);
        
        Transmit(CMD::RASET, COMMAND);

        Transmit((y0 >> 8   ), DATA);
        Transmit((y0 &  0xFF), DATA);
        Transmit((y1 >> 8   ), DATA);
        Transmit((y1 &  0xFF), DATA);

        Transmit(CMD::RAMWR, COMMAND);
    }

    void Hardware_InitSeq(Rotation rot = Rotation::LANDSCAPE)
    {
        using enum DataType;
        using enum Rotation;

        RST.Low();
        osDelay(10);
        RST.High();
        osDelay(120);

        Transmit(CMD::SLEEP_OUT,COMMAND);
        osDelay(120);

        /* Rotation */
        Transmit(CMD::MADCTL,COMMAND);
        Transmit((rot == LANDSCAPE)?0x60:0x00);
        
        Transmit(CMD::COLMOD, COMMAND);
        Transmit(0x05);

        Transmit(CMD::PORCTRL, COMMAND);
        Transmit(0x0C);
        Transmit(0x0C);
        Transmit(0x00);
        Transmit(0x33);
        Transmit(0x33);
        Transmit(CMD::GCTRL, COMMAND);
        Transmit(0x46);
        Transmit(CMD::GTADJ, COMMAND);
        Transmit(0x19);

        Transmit(CMD::VCOMS, COMMAND);
        Transmit(0x1B);
        Transmit(CMD::LCMCTRL, COMMAND);
        Transmit(0x2C);
        Transmit(CMD::VDVVRHEN, COMMAND);
        Transmit(0x01);
        Transmit(CMD::VRHS, COMMAND);
        Transmit(0x0F);
        Transmit(CMD::VDVS, COMMAND);
        Transmit(0x20);
        Transmit(CMD::FRCTRL2, COMMAND);    
        Transmit(0x0F);
        Transmit(CMD::PWCTRL1, COMMAND);
        Transmit(0xA4);
        Transmit(0xA1);

        Transmit(CMD::PVGAMCTRL, COMMAND);
        Transmit(0xF0);
        Transmit(0x00);
        Transmit(0x06);
        Transmit(0x04);
        Transmit(0x05);
        Transmit(0x05);
        Transmit(0x31);
        Transmit(0x44);
        Transmit(0x48);
        Transmit(0x36);
        Transmit(0x12);
        Transmit(0x12);
        Transmit(0x2B);
        Transmit(0x34);

        Transmit(CMD::NVGAMCTRL, COMMAND);
        Transmit(0xF0);
        Transmit(0x0B);
        Transmit(0x0F);
        Transmit(0x0D);
        Transmit(0x26);
        Transmit(0x31);
        Transmit(0x43);
        Transmit(0x47);
        Transmit(0x38);
        Transmit(0x14);
        Transmit(0x14);
        Transmit(0x2C);
        Transmit(0x32);

        Transmit(CMD::INVON, COMMAND); 
        Transmit(CMD::DISPON, COMMAND);
    }

    /* * Vars */


    /* * APIs */

};