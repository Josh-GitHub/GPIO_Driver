/*
 * gpio_internal.h
 *
 *  Created on: 17.05.2020
 *      Author: Josh
 * Pin numbers and LED colors are matched to STM32F407G-DISC1 discovery board
 */

#ifndef INC_GPIO_INTERNAL_H_
#define INC_GPIO_INTERNAL_H_

void gpioInit(void){
  //Aktivieren der PortD Clock
  GPIO_PeriClockControl(GPIOD,ENABLE);

  //Initialisierung Gruene LED
  LedGreen.pGPIOx = GPIOD;
  LedGreen.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
  LedGreen.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
  LedGreen.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
  LedGreen.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
  LedGreen.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
  GPIO_Init(&LedGreen);

  //Initialisierung Orangene LED
  LedYellow.pGPIOx = GPIOD;
  LedYellow.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
  LedYellow.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
  LedYellow.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
  LedYellow.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
  LedYellow.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
  GPIO_Init(&LedYellow);

  //Initialisierung Rote LED
  LedRed.pGPIOx = GPIOD;
  LedRed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
  LedRed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
  LedRed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
  LedRed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
  LedRed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
  GPIO_Init(&LedRed);

  LedBlue.pGPIOx = GPIOD;
  LedBlue.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
  LedBlue.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
  LedBlue.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
  LedBlue.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
  LedBlue.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
  GPIO_Init(&LedBlue);

  //Button mit Interrupt
  Button.pGPIOx = GPIOA;
  Button.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
  Button.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_RT;
  Button.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
  GPIO_Init(&Button);
  GPIO_IRQInterruptConfig(IRQ_NO_EXTI0,ENABLE);
}

#endif /* INC_GPIO_INTERNAL_H_ */
