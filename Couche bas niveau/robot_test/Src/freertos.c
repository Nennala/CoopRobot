/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"

/* USER CODE BEGIN Includes */     
#include <string.h>
#include "cmsis_os.h"
#include "main.h"
#include "stm32f3xx_hal.h"
/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/

/* USER CODE BEGIN Variables */
extern TIM_HandleTypeDef htim3;
extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart2;

int flag_adc = 0;
int deplacement_fini = 0;
uint32_t adcValue = 0;
/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/

/* USER CODE BEGIN FunctionPrototypes */

void alumer_gauche(int sens) {
    HAL_GPIO_WritePin(ain1_GPIO_Port, ain1_Pin, !sens);
    HAL_GPIO_WritePin(ain2_GPIO_Port, ain2_Pin, sens);
}

void alumer_droite(int sens) {
    HAL_GPIO_WritePin(bin1_GPIO_Port, bin1_Pin, !sens);
    HAL_GPIO_WritePin(bin2_GPIO_Port, bin2_Pin, sens);
}

void eteindre_gauche() {
    HAL_GPIO_WritePin(ain1_GPIO_Port, ain1_Pin, 0);
    HAL_GPIO_WritePin(ain2_GPIO_Port, ain2_Pin, 0);
}

void eteindre_droite() {
    HAL_GPIO_WritePin(bin1_GPIO_Port, bin1_Pin, 0);
    HAL_GPIO_WritePin(bin2_GPIO_Port, bin2_Pin, 0);
}

void accelerer() {
    int pwm = 0;
    while (pwm != 100) {
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pwm);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, pwm);
        pwm += 10;
        osDelay(100);
    }
}

void deccelerer() {
    int pwm = 100;
    while (pwm != 0) {
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pwm);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, pwm);
        pwm -= 10;
        osDelay(100);
    }
}

void avancer_robot() {
    alumer_droite(1);
    alumer_gauche(1);
    accelerer();
    osDelay(2000);
    deccelerer();
    eteindre_droite();
    eteindre_gauche();
    deplacement_fini = 1;
}

void reculer_robot() {
    alumer_droite(0);
    alumer_gauche(0);
    accelerer();
    osDelay(2000);
    deccelerer();
    eteindre_droite();
    eteindre_gauche();
    deplacement_fini = 1;
}

void tourner_droite() {
    alumer_gauche(1);
    alumer_droite(0);
    accelerer();
    osDelay(1000);
    deccelerer();
    eteindre_droite();
    eteindre_gauche();
    deplacement_fini = 1;
}

void tourner_gauche() {
    alumer_droite(1);
    alumer_gauche(0);
    accelerer();
    osDelay(1000);
    deccelerer();
    eteindre_droite();
    eteindre_gauche();
    deplacement_fini = 1;
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
    UNUSED(hadc);
    adcValue = HAL_ADC_GetValue(hadc);
    flag = 1;
}

int _write(int file, char *ptr, int len) {
    UNUSED(file);

    HAL_UART_Transmit(&huart2, (uint8_t *) ptr, (uint16_t) len, 10000);
    return len;
}

/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* USER CODE BEGIN Application */
void motor(void const * argument)
{
  /* USER CODE BEGIN motor */
  UNUSED(argument);

  HAL_GPIO_WritePin(stby_GPIO_Port, stby_Pin, 1);
  HAL_TIM_Base_Start(&htim3);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);

  /* Infinite loop */
  for(;;)
  {
    avancer_robot();
    osDelay(500);
    reculer_robot();
    osDelay(500);
    tourner_gauche();
    osDelay(500);
    tourner_droite();
    osDelay(500);
  }
  /* USER CODE END motor */
}

void adcControl(void const * argument)
{
  /* USER CODE BEGIN adcControl */
  /* Infinite loop */
  for(;;)
  {
      HAL_ADC_Start_IT(&hadc1);
      osDelay(1000);
      if (flag == 1) {
          printf("Value : %lu\n\r", adcValue);
          flag = 0;
      }
  }
  /* USER CODE END adcControl */
}

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
