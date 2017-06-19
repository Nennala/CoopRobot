void user_pwm_setvalue(uint16_t value)
{
    TIM_OC_InitTypeDef sConfigOC;

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = value;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
}

/* pwmTask function */
void pwmTask(void const * argument)
{

  /* USER CODE BEGIN pwmTask */
  HAL_TIM_Base_Start(&htim3);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);

  /* Infinite loop */
  for(;;)
  {
    if(pwm_value == 0) step = 100;
    if(pwm_value == 2000) step = -100;
    pwm_value += step;
    user_pwm_setvalue(pwm_value);
    osDelay(1);
  }
  /* USER CODE END pwmTask */
}
