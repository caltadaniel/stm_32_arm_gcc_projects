/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/main.c 
  * @author  Daniele Caltabiano
  * @version V1.8.0
  * @date    04-November-2016
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  * 
  * @description
  * This software is made to control the magnetic tile
  * PINOUT
  * AOUT -> PC2 (CH 7 ADC)
  * CLR  -> PE12
  * CLK  -> PE13
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdio.h>

/** @addtogroup Template_Project
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static __IO uint32_t uwTimingDelay;
RCC_ClocksTypeDef RCC_Clocks;
int pixelOrder[] = {26, 27, 18, 19, 10, 11, 2, 3, 1, 0, 9, 8, 17, 16, 25, 24};
int subtileOrder[] = {0, 2, 1, 3};
int subtileOffset[] = {0, 4, 32, 36};
uint16_t frame[64];

/* Private function prototypes -----------------------------------------------*/
static void Delay(__IO uint32_t nTime);
void InitGPIO(void);
void SelectNextMagel(void);
void ResetCounter(void);
void ReadArray(void);


/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
 
 /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       files before to branch to application main.
       To reconfigure the default setting of SystemInit() function, 
       refer to system_stm32f4xx.c file */

  /* SysTick end of count event each 10ms */
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 10000);
  
  /* Add your application code here */
  /* Insert 50 ms delay */
  Delay(5);
  
  /* Output HSE clock on MCO1 pin(PA8) ****************************************/ 
  /* Enable the GPIOA peripheral */ 
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  
  /* Configure MCO1 pin(PA8) in alternate function */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
  GPIO_Init(GPIOA, &GPIO_InitStructure);
    
  /* HSE clock selected to output on MCO1 pin(PA8)*/
  RCC_MCO1Config(RCC_MCO1Source_HSE, RCC_MCO1Div_1);
  
  
  /* Output SYSCLK/4 clock on MCO2 pin(PC9) ***********************************/ 
  /* Enable the GPIOACperipheral */ 
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  
  /* Configure MCO2 pin(PC9) in alternate function */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
  GPIO_Init(GPIOC, &GPIO_InitStructure);
    
  /* SYSCLK/4 clock selected to output on MCO2 pin(PC9)*/
  RCC_MCO2Config(RCC_MCO2Source_SYSCLK, RCC_MCO2Div_4);
  
  InitGPIO();
  
  setbuf(stdout, NULL);
  printf("Entering the machine\r\n");
  
  /* Infinite loop */
  while (1)
  {
    ReadArray();
    Delay(10);
    
    
  }
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{ 
  uwTimingDelay = nTime;

  while(uwTimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (uwTimingDelay != 0x00)
  { 
    uwTimingDelay--;
  }
}


void InitGPIO(void)
{
	/* enable the peripheral clock for the GPIOe
	 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 |GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOE, GPIO_Pin_12 | GPIO_Pin_13|GPIO_Pin_15);
  GPIO_SetBits(GPIOE, GPIO_Pin_10 |GPIO_Pin_11 |GPIO_Pin_14);
}

/**
  * @brief  Select the next magel in the array.
  * @param  None
  * @retval None
  */
void SelectNextMagel(void)
{
  GPIO_SetBits(GPIOE, GPIO_Pin_13);
  /* just wait*/
  Delay(1);
  GPIO_ResetBits(GPIOE, GPIO_Pin_13);
  
}
void ResetCounter(void)
{
  GPIO_SetBits(GPIOE, GPIO_Pin_12);
  Delay(1);
  GPIO_ResetBits(GPIOE, GPIO_Pin_12);
}

void ReadArray(void)
{
    ResetCounter();
    SelectNextMagel();
    uint16_t arrPos = 0;
    for (int curSubtileIdx = 0; curSubtileIdx < 4; curSubtileIdx++) {
      //printf("Actual subtile: %d\r\n", curSubtileIdx);
      for (int curIdx = 0; curIdx < 16; curIdx++) {
        // Read value
        int value = arrPos;

        //terminal.println(value);
        //delay(10);

        // Store value in correct frame location
        int frameOffset = pixelOrder[curIdx] + subtileOffset[subtileOrder[curSubtileIdx]];
        //terminal.println(frameOffset);
        //delay(25);
        frame[frameOffset] = value;

        // Increment to next pixel
        SelectNextMagel();
        arrPos ++;
      }
    }
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
