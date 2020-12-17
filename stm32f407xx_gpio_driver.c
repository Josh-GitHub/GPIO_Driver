/*
 * stm32f407xx_gpio_driver.c
 */
#include "stm32f407xx_gpio_driver.h"


void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if (pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN();
		}
		else if (pGPIOx == GPIOB)
		{
			GPIOB_PCLK_EN();
		}
		else if (pGPIOx == GPIOC)
		{
			GPIOC_PCLK_EN();
		}
		else if (pGPIOx == GPIOD)
		{
			GPIOD_PCLK_EN();
		}
		else if (pGPIOx == GPIOE)
		{
			GPIOE_PCLK_EN();
		}
		else if (pGPIOx == GPIOF)
		{
			GPIOF_PCLK_EN();
		}
		else if (pGPIOx == GPIOG)
		{
			GPIOG_PCLK_EN();
		}
		else if (pGPIOx == GPIOH)
		{
			GPIOH_PCLK_EN();
		}
		else if (pGPIOx == GPIOI)
		{
			GPIOI_PCLK_EN();
		}
	}
	else
	{
		if (pGPIOx == GPIOA)
		{
			GPIOA_PCLK_DI();
		}else if (pGPIOx == GPIOB)
		{
			GPIOB_PCLK_DI();
		}else if (pGPIOx == GPIOC)
		{
			GPIOC_PCLK_DI();
		}else if (pGPIOx == GPIOD)
		{
			GPIOD_PCLK_DI();
		}else if (pGPIOx == GPIOE)
		{
			GPIOE_PCLK_DI();
		}else if (pGPIOx == GPIOF)
		{
			GPIOF_PCLK_DI();
		}else if (pGPIOx == GPIOG)
		{
			GPIOG_PCLK_DI();
		}else if (pGPIOx == GPIOH)
		{
			GPIOH_PCLK_DI();
		}else if (pGPIOx == GPIOI)
		{
			GPIOI_PCLK_DI();
		}
	}

}



//Setting registers according to Pin specification
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	 //Enable relevant clock
	 GPIO_PeriClockControl(pGPIOHandle->pGPIOx, ENABLE);


	 //Configurate PIN in INPUT or OUTPUT mode
	 if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG) 
	 {
		 // Normal Pin Mode
		pGPIOHandle->pGPIOx->MODE_REG &= ~(0b11 << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber *2));
		pGPIOHandle->pGPIOx->MODE_REG |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber *2));
	 }
	 else
	 {
		SYSCFG_PCLK_EN();
	    // IRQ-Mode
		pGPIOHandle->pGPIOx->MODE_REG &= ~(0b11 << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber *2)); //reset PIN as Input
		// 1. Configurate Interrupt for rising, falling or both edges
		if((pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT) || (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT))
		{//Falling Edge Trigger
			EXTI->FTSR |= (0b1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else
		{
			EXTI->FTSR &= ~(0b1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}

		if((pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT) || (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT))
		{//Rising Edge Trigger
			EXTI->RTSR |= (0b1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else
		{
			EXTI->RTSR &= ~(0b1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}

		// 2. Configuration of SYSCFG_EXTICR according to GPIO-Port
		SYSCFG->EXTICR[pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4] &= ~(0b1111 << ((pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4) * 4));
		SYSCFG->EXTICR[pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4] |= (GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx) << ((pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4) * 4));

		// 3. Activation of EXTI Interrupt handler in IMR-Register
		EXTI->IMR |= (ENABLE << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	}

	 //Configuration of Output-Speeds
	 pGPIOHandle->pGPIOx->OUTPUT_SPEED &= ~(0b11 << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber *2));
	 pGPIOHandle->pGPIOx->OUTPUT_SPEED |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber *2));
	 //Configurations of Pull-up/down Settings
	 pGPIOHandle->pGPIOx->PULL_UP_DOWN &= ~(0b11 << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber *2));
	 pGPIOHandle->pGPIOx->PULL_UP_DOWN |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber *2));
	 //Configuration of Output modes
	 pGPIOHandle->pGPIOx->OUTPUT_TYPE  &= (0b1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
	 pGPIOHandle->pGPIOx->OUTPUT_TYPE  |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
}

//Resets GPIO Ports
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
	if(pGPIOx == GPIOA)
	{
		GPIOA_REG_RESET();
	}
	else if (pGPIOx == GPIOB)
	{
		GPIOB_REG_RESET();
	}
	else if (pGPIOx == GPIOC)
	{
		GPIOC_REG_RESET();
	}
	else if (pGPIOx == GPIOD)
	{
		GPIOD_REG_RESET();
	}
	else if (pGPIOx == GPIOE)
	{
		GPIOE_REG_RESET();
	}
	else if (pGPIOx == GPIOF)
	{
		GPIOF_REG_RESET();
	}
	else if (pGPIOx == GPIOG)
	{
		GPIOG_REG_RESET();
	}
	else if (pGPIOx == GPIOH)
	{
		GPIOH_REG_RESET();
	}
	else if (pGPIOx == GPIOI)
	{
		GPIOI_REG_RESET();
	}

}


/******************************************************************************************
 *								User Functions											  *
 ******************************************************************************************/

uint8_t GPIO_ReadFromInputPin(GPIO_Handle_t *pGPIO_Handle) 
{
    if (pGPIO_Handle->pGPIOx->INPUT_DATA_REG & (1 << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
	return pGPIOx->INPUT_DATA_REG;
}


void GPIO_WriteToOutputPin(GPIO_Handle_t *pGPIO_Handle, uint8_t Value)
{
	if(Value == 1){
		pGPIO_Handle->pGPIOx->OUTPUT_DATA_REG |= (GPIO_PIN_SET << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);
	}else{
		pGPIO_Handle->pGPIOx->OUTPUT_DATA_REG &=  ~(GPIO_PIN_SET << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);
	}
}


void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value)
{
	pGPIOx->OUTPUT_DATA_REG = Value;
}


void GPIO_ToggleOutputPin(GPIO_Handle_t *pGPIO_Handle)
{
	pGPIO_Handle->pGPIOx->OUTPUT_DATA_REG ^= (0b1 << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);
}

/******************************************************************************************
 *											IRQ											  *
 ******************************************************************************************/
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{

	if(EnorDi == ENABLE)
	{
		*((volatile uint32_t*) NVIC_ISER0) |= (0b1 << IRQNumber);


	}else
	{
		*((volatile uint32_t*) NVIC_ICER0) |= (0b1 << IRQNumber);
	}

}

void GPIO_IRQHandling(uint8_t PinNumber)
{
	//Scanns and resets EXTI-PR bits
	if(EXTI->PR & ( 1 << PinNumber))
	{
		//clear
		EXTI->PR |= ( 1 << PinNumber);
	}

}

