
/********************/
/* *    HAL-DDC     */
/* *   @i4N 2026    */
/********************/

#pragma once

/* No headers, in case reading C++ codes from C */
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

inline Pin* pled{nullptr};

/*******************/
/* * Global Types  */
/*******************/

using byte = uint8_t;
using word = uint16_t;