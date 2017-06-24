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

#include <time.h>
#include <stdlib.h>

#define PWM_MAX 320
#define DELAY 1000
#define OK 0x06
/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/

/* USER CODE BEGIN Variables */
extern TIM_HandleTypeDef htim3;
extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart1;

int flag_adc = 0;
uint32_t adcValue = 0;

int flag_deplacement_fini = 0;
int flag_rotation_finie =0;

int flag_haut = 0;
int flag_bas = 0;
int flag_droite = 0;
int flag_gauche = 0;
int flag_distance = 0;
int flag_cap =0;
int flag_present = 0;

struct Robot {
    int posx;
    int posy;
    int orientation;
};

struct Robot robot1, robot2; // Nous sommes robot1 et l'autre robot est  robot2

/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/

/* USER CODE BEGIN FunctionPrototypes */

/* BEGIN Fonctions pour les moteurs */
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

void pwm_max() {
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, PWM_MAX);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, PWM_MAX);
}

void accelerer() {
    int pwm = 0;
    while (pwm != PWM_MAX) {
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pwm);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, pwm);
        pwm += 20;
        osDelay(50);
    }
}

void deccelerer() {
    int pwm = PWM_MAX;
    while (pwm != 0) {
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pwm);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, pwm);
        pwm -= 20;
        osDelay(50);
    }
}

void avancer_robot() {
    alumer_droite(0);
    alumer_gauche(0);
    accelerer();
    osDelay(470);//robot2 : 470 robot1 : 850
    deccelerer();
    eteindre_droite();
    eteindre_gauche();
}

void reculer_robot() {
    alumer_droite(1);
    alumer_gauche(1);
    accelerer();
    osDelay(470);//robot2 : 470 robot1 : 850
    deccelerer();
    eteindre_droite();
    eteindre_gauche();
}


void pivoter_gauche() {
    pwm_max();
    alumer_gauche(1);
    alumer_droite(0);
    osDelay(40);//robot 2 : 40 robot1 : 130
    deccelerer();
    eteindre_droite();
    eteindre_gauche();
}

void pivoter_droite() {
    pwm_max();
    alumer_droite(1);
    alumer_gauche(0);
    osDelay(40);
    deccelerer();
    eteindre_droite();
    eteindre_gauche();
}

void gestion_moteurs()
{
    if (flag_distance > 0) {
      avancer_robot();
      flag_distance --;
    }

    if (flag_distance < 0) {
      reculer_robot();
      flag_distance ++;
    }

    if(flag_distance == 0){
      flag_deplacement_fini = 1;
    }

    if (flag_cap > 0) {
      pivoter_droite();
      flag_cap --;
    }

    if (flag_cap < 0) {
      pivoter_gauche();
      flag_cap ++;
    }

    if(flag_cap == 0){
      flag_rotation_finie = 1;
    }
}

/* END Fonctions pour les moteurs */

/* BEGIN Fonctions ADC */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
    UNUSED(hadc);
    adcValue = HAL_ADC_GetValue(hadc);
    flag_adc = 1;
}

int _write(int file, char *ptr, int len) {
    UNUSED(file);

    HAL_UART_Transmit(&huart2, (uint8_t *) ptr, (uint16_t) len, 10000);
    return len;
}

int distance() {
    int value = 0;
    if (adcValue >= 3800) {
        value = 6;
    }
    if (adcValue >= 3750 && adcValue < 3800) {
        value = 7;
    }
    if (adcValue >= 3430 && adcValue < 3750) {
        value = 8;
    }
    if (adcValue >= 3140 && adcValue < 3420) {
        value = 9;
    }
    if (adcValue >= 2880 && adcValue < 3140) {
        value = 10;
    }
    if (adcValue >= 2690 && adcValue < 2880) {
        value = 11;
    }
    if (adcValue >= 2510 && adcValue < 2690) {
        value = 12;
    }
    if (adcValue >= 2460 && adcValue < 2510) {
        value = 13;
    }
    if (adcValue >= 2250 && adcValue < 2460) {
        value = 14;
    }
    if (adcValue >= 2140 && adcValue < 2250) {
        value = 15;
    }
    if (adcValue >= 2070 && adcValue < 2140) {
        value = 16;
    }
    if (adcValue >= 1970 && adcValue < 2070) {
        value = 17;
    }
    if (adcValue >= 1910 && adcValue < 1970) {
        value = 18;
    }
    if (adcValue >= 1850 && adcValue < 1910) {
        value = 19;
    }
    if (adcValue >= 1780 && adcValue < 1850) {
        value = 20;
    }
     //printf(" %d\n\r", adcValue);
     //printf(" %d\n\r", value);
    return(value);
}

void estPresent() {
    int value;
    value = distance();
    if (value != 0 && value <= 20) {
        flag_present = 1;
    }
    else{
        flag_present = 0;
    }
     //printf("%d\n\r", flag_present);
}

/* END Fonctions ADC */

/* BEGIN Fonctions UART */
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
        for (i =0; i<3; i++) {
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
        if (ok == 1) {
            for (i = 0; i<5; i++)
            {
                HAL_GPIO_TogglePin(led_GPIO_Port, led_Pin);
                osDelay(500);
            }
            return(v);
        }
        else return(0);
    }

    void recoitpos(){
        uint8_t a, x, y, c;
        a = ReceptionMessage();
        x = a & 0xF0;
        y = a & 0x0F;
        c = ReceptionMessage();
        robot2.posx = x;
        robot2.posy = y;
        robot2.orientation = c;
    }

    void envoipos(uint8_t x, uint8_t y , uint8_t c){
         x = x*16 + y;
         EnvoiMessage(x);
         EnvoiMessage(c);
    }

    void Traduction(uint8_t msg){
        if (msg == 0x05) {
           envoipos(robot1.posx, robot1.posy, robot1.orientation);
        }

        if (msg == 0x06) {

        }

        if (msg == 0x07) {
            flag_haut = 1;
        }

        if (msg == 0x08) {
            flag_bas = 1;
        }

        if (msg == 0x09) {
            flag_droite = 1;
        }

        if (msg == 0x0A) {
            flag_gauche = 1;
        }

        if (msg == 0x0B) {
        }

        if (msg == 0x0C) {
        }

        if (msg == 0x0D) {
            uint8_t a;
            srand(time(NULL));
            a = rand()%100;
            EnvoiMessage(a);
        }

        if (msg == 0x10) {
        }

        if (msg == 0x11) {
        }

        if (msg == 0x12) {
        }

        if (msg == 0x13) {
        }
    }

    void WaitFor(uint8_t z) {
        while (z != ReceptionMessage()) ;
    }

    void TaPosition() {
        EnvoiMessage(0x05);
    }

    void ok() {
        EnvoiMessage(0x06);
    }

    void Monte() {
        EnvoiMessage(0x07);
        WaitFor(0x06);
    }

    void Descend() {
        EnvoiMessage(0x08);
        WaitFor(0x06);
    }

    void Droite() {
        EnvoiMessage(0x09);
        WaitFor(0x06);
    }

    void Gauche() {
        EnvoiMessage(0x0A);
        WaitFor(0x06);
    }

    void DansUnCoin() {
        EnvoiMessage(0x0B);
    }

    void Trouve() {
        EnvoiMessage(0x0C);
    }

    int Random() {
        int a, p;
        EnvoiMessage(0x0D);
        srand(time(NULL));
        a = rand()%256;
        if (ReceptionMessage() < a) {
            p = 1;
            EnvoiMessage(0x50);
        }
        else {
            p = 0;
            EnvoiMessage(0x67);
        }
        return(p);
    }

    void Non(){
        EnvoiMessage(0x10);
    }

    void MemeCase() {
        EnvoiMessage(0x12);
    }

    void TuEsCoin(){
    EnvoiMessage(0x13);
}
/* END Fonctions UART */

/* BEGIN Fonctions IA */

/* Permet la gestion des déplacements dans la tache IA, elle prend deux arguments,
 * une distance et un cap dont au moins un des deux est nul. Elle modifie les flags
 * rotation_distance et cap, rotation_finie et deplacement_fini.
 * Une distance positive signifie que l'on souhaite avancer, une distance négative signifie que l'on souhaite reculer
 * Une cap positif indique un pivot à droite, un cpa négatif un pivot à gauche */
void deplacement(int distance, int cap)
{
  if(cap == 0)//si l'on souhaite modifier la distance, l'argument cap est alors nul
  {
      while(flag_rotation_finie != 1);//On attent que le flag_rotation_finie sont à 0, donc que le robot ne pivote plus
      flag_deplacement_fini = 0;//On remet le flag_deplacement_fini à 0 car on va ordoner un nouveau déplacement
      flag_distance += distance;//On incrémente le flag_distance du nombre de case que l'on souhaite avancer
  }

  if(distance == 0)//si l'on souhaite modifier le cap, l'argument distance est alors nul
  {
      while(flag_deplacement_fini != 1);//on vérifie que l'on avance plus avant d'ordoner une rotation
      flag_rotation_finie = 0;//on met remet le flag_rotation_finie à 0 car on va de nouveau pivoter
      flag_cap += cap;//on incrémente le cap d'autant de quart de tour que l'on souhaite faire
  }
}

/*Fonction de test et de démonstration de la communication, elle ne prend aucun arguments
 *Cette fonction diffèrent légèrement d'un robot à l'autre car/ il faut que l'un des deux initie la manoeuvre
 *Le premier robot scrute la présence d'un message "OK" le canal de communication, ce message signifiant que
 * l'action a été effectué avec succès.
 * Le second robot avance puis emet un message OK à la fin de son déplacement.
 * Ensuite les rôles s'inverse et l'on fait la même manoeuvre mais en reculant afin de revenir aux positions initiales*/
void test_communication()
{
    WaitFor(OK);//uniquement le robot 1

    /*première partie de la manoeuvre*/

    deplacement(1,0);//on avance d'une case
    while(flag_deplacement_fini != 1)//On attent la fin du deplacement avant d'envoyer le message
    {
        osDelay(1000);
    }

    /* Echanges de message OK*/

    ok();//uniquement le robot 1
    WaitFor(OK);//uniquement le robot 1

    WaitFor(OK);//uniquement le robot 2
    ok();//uniquement le robot 2

    /*seconde partie de la manoeuvre*/

    deplacement(-1,0);
    while(flag_deplacement_fini != 1)//on attent la fin de second déplacement avant de finir la fonction
    {
        osDelay(1000);
    }
}

/* Cette fonction est une fonction de démonstration visant à évaluer la présision de déplacements et rotation
 * si les déplacements du robot sont précis et correctement réglés le robot devrait revenir sur sa position initiale
 * Cette fonction ne prend aucun argument, appelle la fonction deplacement et modifie directement la valeur du
 * flag_deplacement_fini;
 * Le robot dessine un carré au sol en avançant puis pivotant quatre fois
 * Il est possible d'appeler plusieurs fois cette fonction pour observer la dérive au bout d'un plus grand nombre de
 *  déplacements*/
void carre(){
    int i =0;
    for(i=0; i<4; i++)
    {
        deplacement(1,0);
        while(flag_deplacement_fini != 1)
        {
            osDelay(1000);
        }

        deplacement(0,1);
        while(flag_deplacement_fini != 1)
        {
            osDelay(1000);
        }
    }
}

/*Cette fonction ne prend aucun argument, fais appel à la fonction avancer_robot, utilise la valeur du flag_present
 * et modifie la valeur des flags distance et deplacement_fini
 * Suite à l'appel de cette fonction le robot avance jusqu'à ce que le capteur unidirectionel signale une présence.*/
void avance_bloque()
{
    while(!flag_present)
    {
        avancer_robot();
    }
    flag_distance = 0;
    flag_deplacement_fini = 1;
}

/*Cette fonction ne prend pas d'argument, elle n'est pas finie d'être developée non plus
 * le but final étant de mener le robot dans un des quatre coin du terrain, pour l'instant le robot avance jusqu'à
 * detecter une presence et puis tourne à droite. Par la suite cette fonction ferait appel à une autre qui testerai
 * si le robot est dans un coin ou non.*/
void test(){
    for(;;)//la fonction est composée d'une boucle infinie
    {
        avance_block();//faisant avancer le robot jusqu'à ce qu'il détecte une présence
        pivoter_droite();//puis le fais pivoter à droite
    }
}

/* END Fonctions IA */

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
    gestion_moteurs();
  }
  /* USER CODE END motor */
}

void adcControl(void const * argument){
  /* USER CODE BEGIN adcControl */
  /* Infinite loop */
for(;;)
 {
   HAL_ADC_Start_IT(&hadc1);
   estPresent();
 }
}  /* USER CODE END adcControl */

void uart(void const * argument)
{
  /* USER CODE BEGIN uart */
  /* Infinite loop */
  for(;;)
  {

    //pivoter_droite();
    //ok();
    //WaitFor(OK);

   /* WaitFor(OK);
    pivoter_droite();
    ok();

    osDelay(1);*/
  }
  /* USER CODE END uart */
}

/*le code ia fait pour l'instant appel aux fonctions de démonstration écrites plus haut et devrait à terme
 * enchainer des routines
 * aller dans un coin
 * vérifier sa position et celle du coéquipier
 * définir d'un point de rendez-vous
 * se rendre au point de rendez-vous
 * réaliser l'action finale */
void ia(void const * argument)
{
  /* USER CODE BEGIN ia */
  /* Infinite loop */

    //écrire les appels de fonction ici
}
  /* USER CODE END ia */


/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
