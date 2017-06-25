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

/**
 * *********************************************************************
 * Auteurs : Daphné Porteries, Victor Cazaux et Thibault Vernay
 * Date de création : 12 juin 2017
 * Date de dernière modification : 25 juin 2017
 * *********************************************************************
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

/* Cette fonction permet d'allumer le moteur gauche. Elle prend en argument la variable sens qui est à 1 quand
 * le moteur avance et à 0 quand celui-ci recule. Voir la datasheet du driver moteur pour les valeurs de ain1
 * et ain2 */
void alumer_gauche(int sens) {
    HAL_GPIO_WritePin(ain1_GPIO_Port, ain1_Pin, sens);
    HAL_GPIO_WritePin(ain2_GPIO_Port, ain2_Pin, !sens);
}

/* Cette fonction permet d'allumer le moteur droit. Elle prend en argument la variable sens qui est à 1 quand
 * le moteur avance et à 0 quand celui-ci recule. Voir la datasheet du driver moteur pour les valeurs de ain1
 * et ain2 */
void alumer_droite(int sens) {
    HAL_GPIO_WritePin(bin1_GPIO_Port, bin1_Pin, sens);
    HAL_GPIO_WritePin(bin2_GPIO_Port, bin2_Pin, !sens);
}

/* Cette fonction permet d'éteindre le moteur gauche. */
void eteindre_gauche() {
    HAL_GPIO_WritePin(ain1_GPIO_Port, ain1_Pin, 0);
    HAL_GPIO_WritePin(ain2_GPIO_Port, ain2_Pin, 0);
}

/* Cette fonction permet d'éteindre le moteur droit. */
void eteindre_droite() {
    HAL_GPIO_WritePin(bin1_GPIO_Port, bin1_Pin, 0);
    HAL_GPIO_WritePin(bin2_GPIO_Port, bin2_Pin, 0);
}

/* Cette fonction permet de mettre au max décidé dans l'entête la valeur du rapport PWM. Elle fait appel à des
 * fonctions de la HAL qui permettent de changer la valeur du CCR pour le timer3. */
void pwm_max() {
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, PWM_MAX);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, PWM_MAX);
}

/* Cette fonction permet de changer la valeur du CCR du timer3 pour changer le rapport du PWM avec une temporisation
 * pour le faire s'incrémenter jusqu'à la valeur finale définie dans l'entête du fichier. */
void accelerer() {
    int pwm = 0;
    while (pwm != PWM_MAX) {
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pwm);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, pwm);
        pwm += 20;
        osDelay(50);
    }
}

/* Cette fonction permet de changer la valeur du CCR du timer3 pour changer le rapport du PWM avec une temporisation
 * pour le faire se décrémenter jusqu'à 0 et provoquer l'arrêt du moteur. */
void deccelerer() {
    int pwm = PWM_MAX;
    while (pwm != 0) {
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pwm);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, pwm);
        pwm -= 20;
        osDelay(50);
    }
}

/* Cette fonction permet d'avancer de 15 cm. Les paramètres de temporisation sont différents selons les robots. Elle 
 * utilise les fonctions allumer et éteindre ainsi que les fonctions d'accélérations et de décélération avant d'éteindre
 * les moteurs. */
void avancer_robot() {
    // sens est à 1 pour avancer
    alumer_droite(1);
    alumer_gauche(1);
    accelerer();
    osDelay(470); // robot2 : 470 robot1 : 850
    deccelerer();
    eteindre_droite();
    eteindre_gauche();
}

/* Cette fonction permet de reculer de 15 cm. Les paramètres de temporisation sont différents selons les robots. Elle 
 * utilise les fonctions allumer et éteindre ainsi que les fonctions d'accélérations et de décélération avant d'éteindre
 * les moteurs. */
void reculer_robot() {
    // sens est à 0 pour reculer
    alumer_droite(0);
    alumer_gauche(0);
    accelerer();
    osDelay(470); // robot2 : 470 robot1 : 850
    deccelerer();
    eteindre_droite();
    eteindre_gauche();
}

/* Cette fonction permet de pivoter à gauche de 90°. Les temporisation changent d'un robot à l'autre et ici on met le
 * rapport du PWM au max avant d'effectuer la routine, de décélérer et de le remettre à 0 avant d'éteindre les moteurs. */
void pivoter_gauche() {
    pwm_max();
    alumer_gauche(1);
    alumer_droite(0);
    osDelay(40); // robot2 : 40 robot1 : 130
    deccelerer();
    eteindre_droite();
    eteindre_gauche();
}

/* Cette fonction permet de pivoter à droite de 90°. Les temporisation changent d'un robot à l'autre et ici on met le
 * rapport du PWM au max avant d'effectuer la routine, de décélérer et de le remettre à 0 avant d'éteindre les moteurs. */
void pivoter_droite() {
    pwm_max();
    alumer_droite(1);
    alumer_gauche(0);
    osDelay(40); // robot2 : 40 robot1 : 130
    deccelerer();
    eteindre_droite();
    eteindre_gauche();
}

/* Cette fonction permet en fonction de la valeur des indicateurs d'état flag_cap et flag_distance de définir les déplacements
 * à effectuer et de décrémenter cette valeur. Elle permet également quand tous les déplacements et changements de cap sont finis
 * de mettre l'indicateur d'état flag_deplacement_fini à 1. */
void gestion_moteurs() {
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

/* Cette fonction est la fonction d'interruption de l'ADC, elle permet de mettre l'indicateur
 * d'état flag_adc à 1 et à récupérer la valeur de l'ADC */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
    UNUSED(hadc);
    adcValue = HAL_ADC_GetValue(hadc);
    flag_adc = 1;
}

/* Cette fonction est utile pour la fonction printf su l'UART2 (UART connecté au PC) écrire
 * facilement les valeurs numériques sur cet UART */
int _write(int file, char *ptr, int len) {
    UNUSED(file);

    HAL_UART_Transmit(&huart2, (uint8_t *) ptr, (uint16_t) len, 10000);
    return len;
}

/* Cette fonction est un étalonnage de l'ADC, il permet d'associer une distance à la valeur
 * de retour de l'ADC. Les valeurs sont des fourchettes, l'ADC ayant un retour qui fluctue
 * autour d'une distance. */
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
    return(value);
}

/* Cette fonction permet de définir pour quelle distance on considère qu'un objet est présent devant le
 * capteur et met l'indicateur d'état flag_present à 1 si c'est le cas. Il le remet à 0 dans le cas
 * contraire. */
void estPresent() {
    int value;
    value = distance();
    if (value != 0 && value <= 20) {
        flag_present = 1;
    }
    else{
        flag_present = 0;
    }
}

/* END Fonctions ADC */

/* BEGIN Fonctions UART */

/* Cette fonction prend en argument le message à transmettre et met en place la sécurisation par la
 * méthode de XOR entre les bits et transmet trois octets avec la sécurisation. */
    void EnvoiMessage(uint8_t data){
        uint8_t eun, b, edeux, equatre, ehuit,eseize, etrentedeux, esoixantequatre, ecentvingthuit, k, z;

        eun = (data & 0x01); /*MASK pour récupérer la valeur de chanque bit */
        edeux = (data & 0x02)/2;
        equatre =(data & 0x04)/4;
        ehuit = (data & 0x08)/8;
        eseize = (data & 0x10)/16;
        etrentedeux = (data & 0x20)/32;
        esoixantequatre = (data & 0x40)/64;
        ecentvingthuit = (data & 0x80)/128;
        
        /*Mise en place des XOR et des 3 paquets*/
        b =  (ecentvingthuit^etrentedeux)*32 + (ecentvingthuit^esoixantequatre)*16 + (esoixantequatre^etrentedeux)*8 +ecentvingthuit*4 + esoixantequatre*2 + etrentedeux;
        k = (eseize^equatre)*32 +  (eseize^ehuit)*16 + (ehuit^equatre)*8 + eseize*4  + ehuit*2 + equatre;
        z = (0^eun)*32 + (0^edeux)*16 + (eun^edeux)*8 +edeux*2  + eun;
        
        /*Envoi des paquets */
        HAL_UART_Transmit(&huart1, &b, sizeof(data), 0xEEEE);
        osDelay(2);
        HAL_UART_Transmit(&huart1, &k, sizeof(data), 0xEEEE);
        osDelay(2);
        HAL_UART_Transmit(&huart1, &z, sizeof(data), 0xEEEE);
        osDelay(2);
    }
    
/* Cette fonction ne prend pas d'arguments, elle récupère les trois octets qui sont transmis par l'autre
 * robot, vérifie la sécurisation et extrait les données pour refaire l'octet original. */
    int ReceptionMessage(){
        uint8_t r, m, n, v, run, rdeux, rquatre, rhuit, rseize, rtrentedeux, ok, i;
        uint8_t rec[3];
        
        /*Récupération des messages*/
        HAL_UART_Receive(&huart1, &r, sizeof(uint8_t), 0xEEEE);
        HAL_UART_Receive(&huart1, &m, sizeof(uint8_t), 0xEEEE);
        HAL_UART_Receive(&huart1, &n, sizeof(uint8_t), 0xEEEE);

        rec[0] = r;
        rec[1] = m;
        rec[2] = n;
        ok = 1;
        for (i =0; i<3; i++) { /*MASK pour récupérer chaque bit*/
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
        
        /*Recréation message original*/
        v =  r + m + n;
        if (ok == 1) {
            for (i = 0; i<5; i++)
            {
                /* Indicateur visuel pour la réception */
                HAL_GPIO_TogglePin(led_GPIO_Port, led_Pin); 
                osDelay(500);
            }
            return(v);
        }
        else return(0);
    }

    /* Cette fonction récupère la position et la stocke dans la structure robot correspondante */
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

    /* Cette fonction envoie deux octets, un contenant à la fois la position x et y et l'autre contenant l'orientation. */
    void envoipos(uint8_t x, uint8_t y , uint8_t c){
         x = x*16 + y;
         EnvoiMessage(x);
         EnvoiMessage(c);
    }

    /* Cette fonction sert à affecter à chaque message reçu un comportement, pour le moment pas tous les messages
     * ont un comportement associé. */
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

    /* Attend de reçevoir un certain message fournit en argument */
    void WaitFor(uint8_t z) {
        while (z != ReceptionMessage()) ;
    }

    /* Les fonctions suivantes sont des fonctions avec un nom explicite pour l'IA permettant d'envoyer le
     * message correspondant. */
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

    /* Cette fonction particulière se démarque des autres. Elle permet de définir qui devient le maître dans les
     * décisions, le tirage aléatoire donne la priorité à celui qui a le plus grand nombre. Cette fonction renvoie
     un indicateur p permettant de savoir si on a gagné le tir ou pas. */
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
