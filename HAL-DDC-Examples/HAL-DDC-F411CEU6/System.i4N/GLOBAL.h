
/********************/
/* *    HAL-DDC     */
/* *   @i4N 2026    */
/********************/

#pragma once

/* No headers, in case reading C++ codes from C */
#include "cmsis_os2.h"
#ifdef __cplusplus
extern "C"{
#endif

    /* This function is to be called in main.c and cppmain.cpp */
    /*               So the linkage must be C                  */
	//void cppmain();

#ifdef __cplusplus
}
#endif

/***********************************************************/
/* *                   Global Pointers                     */
/***********************************************************/
/* *   Objects created in tasks must have a global pointer */
/* *           to be accessible from other tasks           */
/***********************************************************/

#include "GPIO.hpp"
#include "cmsis_os.h"
#include "FreeRTOS.h"

inline Pin* pled{nullptr};

/**********************/
/* * FreeRTOS Handles */
/**********************/
extern "C"
{
    extern osMessageQueueId_t LEDA2LEDBHandle;
    extern osSemaphoreId_t isLEDAFlippedHandle;
}

/*******************/
/* * Global Types  */
/*******************/

using byte = uint8_t;
using word = uint16_t;

using command = byte;