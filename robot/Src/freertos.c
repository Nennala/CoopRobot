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
#include "cmsis_os.h"
#include "main.h"
#include "stm32f3xx_hal.h"
#include "stm32f3xx_hal_tim_ex.h"
/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/

/* USER CODE BEGIN Variables */
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef huart2;
/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/

/* USER CODE BEGIN FunctionPrototypes */
void alumer_gauche();
void eteindre_gauche();

void alumer_droite();
void eteindre_droite();

void avancer_dix_cm();
void reculer_dix_cm();
void tourner_droite();
void tourner_gauche();

void accelerer();
void deccelerer();

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

void avancer_dix_cm() {
    alumer_droite(1);
    alumer_gauche(1);
    accelerer();
    osDelay(2000);
    deccelerer();
    eteindre_droite();
    eteindre_gauche();
}

void reculer_dix_cm() {
    alumer_droite(0);
    alumer_gauche(0);
    accelerer();
    osDelay(2000);
    deccelerer();
    eteindre_droite();
    eteindre_gauche();

}

void tourner_droite() {
    alumer_gauche(1);
    alumer_droite(0);
    accelerer();
    osDelay(1000);
    deccelerer();
    eteindre_droite();
    eteindre_gauche();
}

void tourner_gauche() {
    alumer_droite(1);
    alumer_gauche(0);
    accelerer();
    osDelay(1000);
    deccelerer();
    eteindre_droite();
    eteindre_gauche();
}

void accelerer() {
    int pwm = 0;
    while (pwm != 320) {
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pwm);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, pwm);
        pwm += 20;
        osDelay(100);
    }
}

void deccelerer() {
    int pwm = 320;
    while (pwm != 0) {
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pwm);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, pwm);
        pwm -= 20;
        osDelay(100);
    }
}

/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* USER CODE BEGIN Application */

/* pcCommunication function */
void pcCommunication(void const * argument)
{
  /* USER CODE BEGIN pcCommunication */
  char *msg = "Hello Nucleo Fun\n\r";
  HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), 0xFFFF);
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END pcCommunication */
}
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
