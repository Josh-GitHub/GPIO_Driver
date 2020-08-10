/*
 * main.c
 *  Created on: 17.05.2020
 *      Author: Josh
 * 
 * Basic programm to show functionality of gpio_driver and interrupt routine
 * LED lightup pattern similar to traffic lights
 */


#include"stddef.h"
#include"stdint.h"
#include"stm32f407xx.h"
#include"stm32f407xx_gpio_driver.h"

GPIO_Handle_t LedGreen, LedYellow, LedRed, LedBlue, Button;
#include"gpio_internal.h" //gpio configuration 

uint16_t GPIOWert;

void delay(uint32_t secs) { //Not exact!!
	secs = secs*1000000;
	while(secs>0){
		secs--;
	}
}



int main(void){
	gpioInit();
	  GPIO_WriteToOutputPin(&LedGreen,GPIO_PIN_RESET);
	  GPIO_WriteToOutputPin(&LedYellow,GPIO_PIN_RESET);
	  GPIO_WriteToOutputPin(&LedRed,GPIO_PIN_RESET);
	  GPIO_WriteToOutputPin(&LedBlue,GPIO_PIN_RESET);
	  uint8_t Phase = 0;

		while(true){ //Traffic light Pattern

	    switch(Phase){
	    case 0:
		default:
	      GPIO_WriteToOutputPin(&LedRed,GPIO_PIN_SET);
	      GPIO_WriteToOutputPin(&LedYellow,GPIO_PIN_RESET);
	      GPIO_WriteToOutputPin(&LedGreen,GPIO_PIN_RESET);
	      delay(1);
	      Phase++;
	      break;
	    case 1:
	      GPIO_WriteToOutputPin(&LedYellow,GPIO_PIN_SET);
	      delay(1);
	      Phase++;
	      break;
	    case 2:
	    	GPIO_WriteToOutputPin(&LedRed,GPIO_PIN_RESET);
	    	GPIO_WriteToOutputPin(&LedYellow,GPIO_PIN_RESET);
	    	GPIO_WriteToOutputPin(&LedGreen,GPIO_PIN_SET);
	      delay(1);
	      Phase++;
	      break;
		case 3:
			GPIO_WriteToOutputPin(&LedYellow,GPIO_PIN_SET);
			GPIO_WriteToOutputPin(&LedGreen,GPIO_PIN_RESET);
	      delay(1);
		  Phase=0;
	      break;
		}
	  }

}

void EXTI0_IRQHandler(void)
{	GPIO_IRQHandling(GPIO_PIN_NO_0);
	uint16_t currentValue = GPIO_ReadFromInputPort(GPIOD);
	GPIO_WriteToOutputPort(GPIOD, 0);
	GPIO_WriteToOutputPin(&LedRed,GPIO_PIN_SET);
	delay(3);
	GPIO_WriteToOutputPin(&LedBlue,GPIO_PIN_SET);
	GPIO_WriteToOutputPort(GPIOD, currentValue);
}
