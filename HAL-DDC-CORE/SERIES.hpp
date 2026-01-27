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

#define F4 1
#if F4
    #if defined UNSELECTED
        #include "stm32f4xx.h"
        #undef  UNSELECTED
        #define SELECTED
    #else
        #error "A MCU Series is already selected above"
    #endif
#endif

#define H7 0 
#if H7
    #if defined UNSELECTED
        #include "stm32h7xx.h"
        #undef  UNSELECTED
        #define SELECTED
    #else
        #error "A MCU Series is already selected above"
    #endif
#endif

#ifndef SELECTED
    #error "You must select one MCU Series"
#endif