/****************************************/
/* *             SERAIL                 */
/* *         SERIAL Expansion           */
/* *         Part of HAL-DDC            */
/* *            2026 @i4N               */
/****************************************/

#pragma once

/* * Series Control */
#include "SERIES.hpp"

/* * HAL Libs */
#include "gpio.h"
#include "stm32f4xx_hal_uart.h"

/* * C++ */
#include <cstdio>
#include <cstring>
#include <utility>
#include <algorithm>

class SERIAL
{
    public:

    /* * type defines */

    /* * Constructor */

    SERIAL(UART_HandleTypeDef* huart)
    : HUART(huart)
    {}

    /* * Public APIs & Vars */

    enum class MODE : uint8_t
    {
        Blocking,
        Interrupt,
        DMA
    };

    /* * Seria Print */
    /* todo When frequenctly call between different modes, */
    /* todo messages may be mixed or lost. It's suggested  */
    /* todo only use one mode in a certain application     */
    /* todo may fix in future, 2026 1-17                   */

    template<typename... Args>
    void Print(const char*  format, 
               Args&&...    args,
               SERIAL::MODE mode = SERIAL::MODE::Blocking)
    {
        const uint16_t length = std::snprintf(TxBuffer,
                                       MAX_BUFFER_SIZE,
                                       format,
                                       std::forward<Args>(args)...);

        const uint16_t tx_length = (length < MAX_BUFFER_SIZE) ? length : MAX_BUFFER_SIZE - 1;

        if(mode == SERIAL::MODE::Blocking)
        {
            HAL_UART_Transmit(HUART,
                              reinterpret_cast<uint8_t*>(TxBuffer),
                              tx_length,
                              HAL_MAX_DELAY);
        }
        else if(mode == SERIAL::MODE::Interrupt)
        {
            HAL_UART_Transmit_IT(HUART,
                                reinterpret_cast<uint8_t*>(TxBuffer),
                                tx_length);
        }
        else if(mode == SERIAL::MODE::DMA)
        {
            HAL_UART_Transmit_DMA(HUART,
                              reinterpret_cast<uint8_t*>(TxBuffer),
                              tx_length);
        }
    }

    void Receive_Start(MODE mode = SERIAL::MODE::Blocking);
    void Receive(MODE mode = SERIAL::MODE::Blocking);
    void Receive_IDLE_Start(MODE mode = SERIAL::MODE::Blocking);
    void Receive_IDLE(MODE mode = SERIAL::MODE::Blocking);

    protected:

    UART_HandleTypeDef* HUART = nullptr;
    static constexpr uint16_t MAX_BUFFER_SIZE{256};

    char TxBuffer[MAX_BUFFER_SIZE]{0};
    
    /* * FIFO Ring Buffer */
    struct FIFO
    {
        static constexpr uint16_t MAX_FIFO_SIZE{512};
        static_assert((MAX_FIFO_SIZE & (MAX_FIFO_SIZE - 1)) == 0,
                      "MAX_FIFO_SIZE must be power of two");

        uint8_t  Ring[MAX_FIFO_SIZE]{0};
        uint16_t head_index{0};
        uint16_t tail_index{0};

        bool isEmpty()
        {return head_index == tail_index;}

        uint16_t Get_OccupiedSpace()
        {return (head_index + MAX_FIFO_SIZE - tail_index) & (MAX_FIFO_SIZE-1);}

        uint16_t Get_FreeSpace()
        {return MAX_FIFO_SIZE - Get_OccupiedSpace()-1;}

        /* Data in  */
        void Push(uint8_t *data, uint16_t length)
        {
           if(length > Get_FreeSpace()||length == 0)return;

           uint16_t first_chunk = std::min<uint16_t>(length,MAX_FIFO_SIZE - head_index),
                    second_chunk = length - first_chunk;
            std::memcpy(&Ring[head_index],data,first_chunk);
            if(second_chunk > 0)
            {
                std::memcpy(&Ring[0],&data[first_chunk],second_chunk);
            }
            head_index = (head_index + length) & (MAX_FIFO_SIZE-1);
        }

        void Peek(uint8_t *data, uint16_t length)
        {
            if(length > Get_OccupiedSpace()||length == 0)return;
            uint16_t first_chunk = std::min<uint16_t>(length,MAX_FIFO_SIZE - tail_index),
                     second_chunk = length - first_chunk;
            std::memcpy(data,&Ring[tail_index],first_chunk);
            if(second_chunk > 0)
            {
                std::memcpy(&data[first_chunk],&Ring[0],second_chunk);
            }
        }

        void Pop(uint8_t *data, uint16_t length)
        {
            Peek(data,length);
            tail_index = (tail_index + length) & (MAX_FIFO_SIZE-1);
        }

        void Clear()
        {
            head_index = 0;
            tail_index = 0;
        }

        

    }FIFO;

    private:

};
