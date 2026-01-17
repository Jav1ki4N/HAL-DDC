/****************************************/
/* *              TIM                   */
/* *         TIM Expansion              */
/* *         Part of HAL-DDC            */
/* *            2026 @i4N               */
/****************************************/

#include "TIMER.hpp"
#include <algorithm>
#include <type_traits>
#include "stm32f411xe.h"

/* * TIMER GENERAL */

void Timer::Start(FUNC func)
{
     if(HTIM == nullptr)return;
     if(func == FUNC::BASE)HAL_TIM_Base_Start(this->HTIM);
     else if(func == FUNC::IT)HAL_TIM_Base_Start_IT(this->HTIM);
}

/* * PWM */

void PWM::Start()
{
    if(HTIM == nullptr)return; 
    HAL_TIM_PWM_Start(this->HTIM, this->Channel);
}

template<typename T>
requires (std::integral<T> || std::floating_point<T>)
void PWM::Set_Duty(T duty) noexcept
{
     uint32_t arr = this->HTIM->Instance->ARR;
     uint32_t ccr{0};

     if(HTIM == nullptr)return;
     if constexpr (std::is_floating_point<T>::value)
     {
          duty = std::clamp<T>(duty,0.0,1.0);
          ccr = static_cast<uint32_t>((arr+1) * duty);
     }
     else if constexpr (std::is_integral<T>::value)
     {
          duty = std::clamp<T>(duty,0,100);
          ccr = static_cast<uint32_t>((arr+1)*(float)(duty*0.01f));
     }
     switch(this->Channel)
     {
          case TIM_CHANNEL_1:this->HTIM->Instance->CCR1 = ccr;break;
          case TIM_CHANNEL_2:this->HTIM->Instance->CCR2 = ccr;break;
          case TIM_CHANNEL_3:this->HTIM->Instance->CCR3 = ccr;break;
          case TIM_CHANNEL_4:this->HTIM->Instance->CCR4 = ccr;break;
          default:break;
     }
}
