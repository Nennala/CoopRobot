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
#include <time.h>
#include <stdlib.h>



/* USER CODE BEGIN Includes */     
#include "main.h"
#include "stm32f3xx_hal.h"
#include "cmsis_os.h"

UART_HandleTypeDef huart1;

osThreadId defaultTaskHandle;
/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/

/* USER CODE BEGIN Variables */

/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void EnvoiMessage(uint8_t data){
      uint8_t eun, b, edeux, equatre, ehuit,eseize, etrentedeux, esoixantequatre, ecentvingthuit, k, z;

      eun = (data & 0x01);
      edeux = (data & 0x02)/2;
      equatre =(data & 0x04)/4;
      ehuit = (data & 0x08)/8;
     eseize = (data & 0x10)/16;
      etrentedeux = (data & 0x20)/32;
      esoixantequatre = (data & 0x40)/64;
      ecentvingthuit = (data & 0x80)/128;

     b =  (ecentvingthuit^etrentedeux)*32 + (ecentvingthuit^esoixantequatre)*16 + (esoixantequatre^etrentedeux)*8 +ecentvingthuit*4 + esoixantequatre*2 + etrentedeux;
     k = (eseize^equatre)*32 +  (eseize^ehuit)*16 + (ehuit^equatre)*8 + eseize*4  + ehuit*2 + equatre;
     z = (0^eun)*32 + (0^edeux)*16 + (eun^edeux)*8 +edeux*2  + eun;

     HAL_UART_Transmit(&huart1, &b, sizeof(data), 0xEEEE);
     osDelay(2);
     HAL_UART_Transmit(&huart1, &k, sizeof(data), 0xEEEE);
     osDelay(2);
     HAL_UART_Transmit(&huart1, &z, sizeof(data), 0xEEEE);
     osDelay(2);

}

int ReceptionMessage(){
   uint8_t r, m, n, v, run, rdeux, rquatre, rhuit, rseize, rtrentedeux, ok, i;
   uint8_t rec[3];
   HAL_UART_Receive(&huart1, &r, sizeof(uint8_t), 0xEEEE);
   HAL_UART_Receive(&huart1, &m, sizeof(uint8_t), 0xEEEE);
   HAL_UART_Receive(&huart1, &n, sizeof(uint8_t), 0xEEEE);

   rec[0] = r;
   rec[1] = m;
   rec[2] = n;
   ok = 1;
    for (i =0; i<3; i++){
    run = (rec[i] & 0x01);
    rdeux = (rec[i] & 0x02)/2;
    rquatre =(rec[i] & 0x04)/4;
    rhuit = (rec[i] & 0x08)/8;
    rseize = (rec[i] & 0x10)/16;
    rtrentedeux = (rec[i] & 0x20)/32;
   if ((run^rdeux) != rhuit) ok =0;
   if ((rdeux^rquatre) != rseize) ok =0;
   if ((rquatre^run) != rtrentedeux) ok = 0;

}
r =  (r & 0x07)*32;
 m =  (m & 0x07)*4;
  n =  (n & 0x07);
v =  r + m + n;
if (ok == 1){
    for(int i = 0; i<5; i++){
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_6);
    osDelay(500);}
  return(v);
}

else
    return(0);

}

   int recoitpos(){
       uint8_t a, x, y, c;
       a = ReceptionMessage();
       x = a & 0xF0;
       y = a & 0x0F;
       c = ReceptionMessage();
       return(x,y,c);
   }
   void envoipos(uint8_t x, uint8_t y, uint8_t c){
            x = x*16 + y;
        EnvoiMessage(x);
        EnvoiMessage(c);

   }
   void Traduction(uint8_t msg){
       if (msg == 0x05){
          /*  envoipos(/* TI-BEAU MET TA FONTION CALCUL DE POS );*/
           }

       if (msg == 0x06){

       }
       if (msg == 0x07){
           if (/*capteurs ok*/){
           /*Fonction pour aller en haut*/
           ok();}
           else Non();
       }
       if (msg == 0x08){
           if (/*capteurs ok*/){
           /*Fonction pour aller en bas*/
           ok();}
           else Non();
       }
       if (msg == 0x09){
           if (/*capteurs ok*/){
           /*Fonction pour aller à Droite*/
           ok();}
           else Non();
       }
       if (msg == 0x0A){
           if (/*capteurs ok*/){
           /*Fonction pour aller à Gauche*/
           ok();}
           else Non();
       }
       if (msg == 0x0B){
     }
       if (msg == 0x0C){
       }
       if (msg == 0x0D){
           uint8_t a;
           srand(time(NULL));
           a = rand()%100;
           EnvoiMessage(a);
      }
       if (msg == 0x10){
   }
       if (msg == 0x11){
       }
       if (msg == 0x12){
   }
       if (msg == 0x13){
       }
  }
  void WaitFor(uint8_t z){
        while (z != ReceptionMessage()) ;
   }

   int TaPosition(){
       EnvoiMessage(0x05);
       return (recoitpos());
   }
   void ok(){
       EnvoiMessage(0x06);
   }
   void Monte(){
       EnvoiMessage(0x07);
       WaitFor(0x06);
   }
   void Descend(){
       EnvoiMessage(0x08);
       WaitFor(0x06);
   }
   void Droite(){
       EnvoiMessage(0x09);
       WaitFor(0x06);
   }
   void Gauche(){
       EnvoiMessage(0x0A);
       WaitFor(0x06);
   }
   void DansUnCoin(){
       EnvoiMessage(0x0B);
   }
   void Trouve(){

       EnvoiMessage(0x0C);
   }
   void Random(){int a, p;
       EnvoiMessage(0x0D);
       srand(time(NULL));
       a = rand()%256;
       if (ReceptionMessage() < a) {p = 1; EnvoiMessage(0x50);}
       else {p=0; EnvoiMessage(0x67);}}
   void Non(){EnvoiMessage(0x10);}
   void MemeCase(){
       EnvoiMessage(0x12);
   }
   void TuEsCoin(){
       EnvoiMessage(0x13);
   }




/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
