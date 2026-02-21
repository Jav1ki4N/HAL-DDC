/***************************************/
/* *            LVGL_UI                */
/* *         UI Expansion              */
/* *            HAL-DDC                */
/* *           2026 @i4N               */
/***************************************/

#pragma once

/* Series Control */
#include "SERIES.hpp"

/* Third Party */
#include "FreeRTOS.h"
#include "lvgl.h"
#include "src/core/lv_obj.h"
#include "src/hal/lv_hal_disp.h"

class LVGL_UI
{
    public:

    /* * TypeDefs */
   
    using flush_cb = void (*)(       lv_disp_drv_t* disp_drv, // LVGL Driver instance
                               const lv_area_t*     area,     // Area to flush
                                     lv_color_t*    color_p); // pixel to flush

    using pixel = lv_color_t; // LVGL Buffer/Pixel Type

    using res   = uint16_t;
    using coord = int16_t;
    
    
    lv_disp_drv_t      disp_drv;   // LVGL Display Driver Instance
    lv_disp_draw_buf_t render_buf; // LVGL render Buffer info structure/Instance

    /* * Constructor */

    LVGL_UI(){}


    template <size_t N>
    void UI_Init( res      res_h,           // horizontal resolution
                  res      res_v,           // vertical resolution
                  flush_cb flush_cb,        // flush callback function provided by the user
                  pixel    (&buf1)[N],      // render buffer provided by the user
                  pixel     *buf2 = nullptr // optional 2nd buffer for double buffering
    )
    {
        /* * Hardware Initialization must be done before entry */

        static bool isInited{false};
        if(!isInited)lv_init(),isInited = true; // LVGL Library Initialization (only once)

        lv_disp_drv_init(&disp_drv); // register display driver

        lv_disp_draw_buf_init( &render_buf, // initialize the render buffer
                               buf1,        // 1st buffer
                               buf2,        // 2nd buffer (optional)
                               N         );
        
        disp_drv.hor_res   = res_h;        // set horizontal resolution
        disp_drv.ver_res   = res_v;        // set vertical resolution
        disp_drv.user_data = this;       // set user data to this instance (for callback access)
        disp_drv.flush_cb  = flush_cb;    // set flush callback function
        disp_drv.draw_buf  = &render_buf; // set render buffer

        lv_disp_drv_register(&disp_drv);
    }
};