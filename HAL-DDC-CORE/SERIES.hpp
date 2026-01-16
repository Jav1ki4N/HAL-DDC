/*******************************************/
/* *            SERIES.hpp                 */
/* *   MCU Series Selection & Control      */
/* *         Part of HAL-DDC               */
/* *            2026 @i4N                  */
/*******************************************/

#pragma once

/* * This macro is by default defined */
/* * Once one serie is selected it will be undefined */
#define UNSELECTED

#define F411 1 
#if F411
    #if defined UNSELECTED
        #include "stm32f411xe.h"
        #undef UNSELECTED
    #else
        #error "A MCU Series is already selected above"
    #endif
#endif

#define H743 0 
#if H743
    #if defined UNSELECTED
        #include "stm32h743xx.h"
        #undef UNSELECTED
    #else
        #error "A MCU Series is already selected above"
    #endif
#endif