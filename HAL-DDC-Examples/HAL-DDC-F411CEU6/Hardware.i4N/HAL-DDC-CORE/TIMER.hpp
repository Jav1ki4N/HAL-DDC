/****************************************/
/* *              TIM                   */
/* *         TIM Expansion              */
/* *         Part of HAL-DDC            */
/* *            2026 @i4N               */
/****************************************/

#pragma once

/* * Series Control */
#include "SERIES.hpp"

/* * HAL Libs */
#include "tim.h"

#include <algorithm>
#include <concepts>

class Timer
{
    public:

    /* * Constructor */
    Timer(TIM_HandleTypeDef* htim)
    : HTIM(htim)
    {}

    /* * Public Vars */
    enum class FUNC:uint8_t
    {
        BASE,
        IT
    };
   
    /* * Public APIs */
    void Start(FUNC func = FUNC::BASE);

    protected:
    TIM_HandleTypeDef* HTIM = nullptr;

    private:
};

class PWM : public Timer
{
    public:

    /* * Constructor */
    PWM(TIM_HandleTypeDef* htim, uint32_t channel)
    : Timer(htim), Channel(channel)
    {
        if(this->Channel != TIM_CHANNEL_1 &&
           this->Channel != TIM_CHANNEL_2 &&
           this->Channel != TIM_CHANNEL_3 &&
           this->Channel != TIM_CHANNEL_4)
        {
           this->Channel = TIM_CHANNEL_1;
        }
    }

    /* * Public APIs */
    void Start();

    template<typename T>
    requires (std::integral<T> || std::floating_point<T>)
    void Set_Duty(T duty) noexcept;
    
    protected:
    uint32_t Channel; 
};