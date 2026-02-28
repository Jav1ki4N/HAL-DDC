/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for LEDA */
osThreadId_t LEDAHandle;
const osThreadAttr_t LEDA_attributes = {
  .name = "LEDA",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for LEDB */
osThreadId_t LEDBHandle;
const osThreadAttr_t LEDB_attributes = {
  .name = "LEDB",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for LEDA2LEDB */
osMessageQueueId_t LEDA2LEDBHandle;
const osMessageQueueAttr_t LEDA2LEDB_attributes = {
  .name = "LEDA2LEDB"
};
/* Definitions for isLEDAFlipped */
osSemaphoreId_t isLEDAFlippedHandle;
const osSemaphoreAttr_t isLEDAFlipped_attributes = {
  .name = "isLEDAFlipped"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void Task_LEDA(void *argument);
void Task_LEDB(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of isLEDAFlipped */
  isLEDAFlippedHandle = osSemaphoreNew(1, 0, &isLEDAFlipped_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of LEDA2LEDB */
  LEDA2LEDBHandle = osMessageQueueNew (16, sizeof(uint8_t), &LEDA2LEDB_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of LEDA */
  LEDAHandle = osThreadNew(Task_LEDA, NULL, &LEDA_attributes);

  /* creation of LEDB */
  LEDBHandle = osThreadNew(Task_LEDB, NULL, &LEDB_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_Task_LEDA */
/**
* @brief Function implementing the LEDA thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task_LEDA */
__weak void Task_LEDA(void *argument)
{
  /* USER CODE BEGIN Task_LEDA */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Task_LEDA */
}

/* USER CODE BEGIN Header_Task_LEDB */
/**
* @brief Function implementing the LEDB thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task_LEDB */
__weak void Task_LEDB(void *argument)
{
  /* USER CODE BEGIN Task_LEDB */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Task_LEDB */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
/* * Tasks above are marked as __weak and are overridden respectively in each's .cpp file */
/* * See System.i4N\Task_xxx.cpp  */
/* USER CODE END Application */

