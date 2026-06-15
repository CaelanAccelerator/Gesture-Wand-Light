/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include <driver/MockLight.hpp>
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "core/LightController.hpp"
#include "core/GestureDetector.hpp"
#include "driver/ButtonInput.hpp"
#include "core/Animator.hpp"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
extern "C" int _write(int file, char *ptr, int len)
{
    HAL_UART_Transmit(&huart2, (uint8_t *)ptr, len, HAL_MAX_DELAY);
    return len;
}



//static void W5500_Select(void)
//{
//    HAL_GPIO_WritePin(W5500_CS_GPIO_Port, W5500_CS_Pin, GPIO_PIN_RESET);
//}
//
//static void W5500_Unselect(void)
//{
//    HAL_GPIO_WritePin(W5500_CS_GPIO_Port, W5500_CS_Pin, GPIO_PIN_SET);
//}
//
//static void W5500_Reset(void)
//{
//    HAL_GPIO_WritePin(W5500_RST_GPIO_Port, W5500_RST_Pin, GPIO_PIN_RESET);
//    HAL_Delay(10);
//    HAL_GPIO_WritePin(W5500_RST_GPIO_Port, W5500_RST_Pin, GPIO_PIN_SET);
//    HAL_Delay(100);
//}
//
//static uint8_t W5500_ReadCommonReg(uint16_t addr)
//{
//    uint8_t tx[4];
//    uint8_t rx[4];
//
//    tx[0] = (addr >> 8) & 0xFF;
//    tx[1] = addr & 0xFF;
//    tx[2] = 0x00;   // Common register block, read, variable length mode
//    tx[3] = 0xFF;   // dummy byte
//
//    W5500_Select();
//    HAL_SPI_TransmitReceive(&hspi1, tx, rx, 4, 100);
//    W5500_Unselect();
//
//    return rx[3];
//}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  printf("STM32 serial alive! Build ok.\r\n");

  //W5500_Unselect();
  //W5500_Reset();

//  uint8_t version = W5500_ReadCommonReg(0x0039);
//
//  printf("W5500 version = 0x%02X\r\n", version);
//
//  if (version == 0x04)
//  {
//      printf("SPI OK, W5500 detected.\r\n");
//  }
//  else
//  {
//      printf("SPI failed. Check wiring or SPI config.\r\n");
//  }
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  MockLight led;
  Animator anim(&led);
//  LedColor orange = {255, 140, 0};
//  LedColor purple = {128, 0, 255};
//  LedColor pink   = {255, 100, 150};
//  LedColor empty = {0, 0, 0};

//  //full rendering
//  printf("full rendering\r\n");
//  anim.renderGradient(orange, purple,0,16);
//  anim.show();
//
//  //normal
//  printf("normal\r\n");
//  anim.renderGradient(empty,empty,0,16);
//  anim.renderGradient(orange, purple,1,15);
//  anim.show();
//
//  //start out of range
//  printf("start = -1\r\n");
//  anim.renderGradient(empty,empty,0,16);
//  anim.renderGradient(orange, purple,-1,16);
//  anim.show();
//  printf("start = 17\r\n");
//  anim.renderGradient(empty,empty,0,16);
//  anim.renderGradient(orange, purple,17,16);
//  anim.show();
//
//  //end out of range
//  printf("end = -1\r\n");
//  anim.renderGradient(empty,empty,0,16);
//  anim.renderGradient(orange, purple,1,-1);
//  anim.show();
//  printf("end = 17\r\n");
//  anim.renderGradient(empty,empty,0,16);
//  anim.renderGradient(orange, purple,1,17);
//  anim.show();
//
//  //start larger than end
//  printf("start larger than end\r\n");
//  anim.renderGradient(empty,empty,0,16);
//  anim.renderGradient(orange, purple,5,4);
//  anim.show();
//
//  //start = end
//  printf("start == end\r\n");
//  anim.renderGradient(empty,empty,0,16);
//  anim.renderGradient(orange, purple,1,1);
//  anim.show();
//
//  //one pixel
//  printf("one pixel\r\n");
//  anim.renderGradient(empty,empty,0,16);
//  anim.renderGradient(orange, purple,1,2);
//  anim.show();

//  //tripple rendering full
//  printf("tripple rendering full\r\n");
//  anim.renderGradient(empty,empty,0,16);
//  anim.renderGradient(orange, pink, purple,0,7,16);
//  anim.show();
//
//  //tripple rendering partial
//  printf("tripple rendering partial\r\n");
//  anim.renderGradient(empty,empty,0,16);
//  anim.renderGradient(orange, pink, purple,2,7,14);
//  anim.show();
//
//  //tripple rendering invalid
//  printf("tripple rendering invalid start >= mid\r\n");
//  anim.renderGradient(empty,empty,0,16);
//  anim.renderGradient(orange, pink, purple,7,7,14);
//  anim.show();
//
//  printf("tripple rendering invalid mid >= end\r\n");
//  anim.renderGradient(empty,empty,0,16);
//  anim.renderGradient(orange, pink, purple,2,7,7);
//  anim.show();

  //render sunset
//  printf("render sunset\r\n");
//  anim.renderGradient(empty,empty,0,16);
//  anim.renderPalette(Palettes::Sunset);
//  anim.show();
//
//  //render sunset
//  printf("render aurora\r\n");
//  anim.renderGradient(empty,empty,0,16);
//  anim.renderPalette(Palettes::Aurora);
//  anim.show();

  LightController controller(&anim);
  printf("Circle on\r\n");
  controller.handleGesture(Gesture::Circle);
  printf("SwingUp\r\n");
  controller.handleGesture(Gesture::SwingUp);
  printf("SwingDown\r\n");
  controller.handleGesture(Gesture::SwingDown);
  printf("Circle off\r\n");
  controller.handleGesture(Gesture::Circle);
  printf("Circle on\r\n");
  controller.handleGesture(Gesture::Circle);
  printf("SwingSide until go back\r\n");
  controller.handleGesture(Gesture::SwingSide);
  controller.handleGesture(Gesture::SwingSide);
  controller.handleGesture(Gesture::SwingSide);
  controller.handleGesture(Gesture::SwingSide);
  controller.handleGesture(Gesture::SwingSide);

  while (1)
  {
//	  MotionData md;
//	  buttonInput.read(md);
//	  Gesture gs = detector.gestureDetect(md);
//	  controller.handleGesture(gs);
//	  HAL_Delay(100);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, W5500_CS_Pin|W5500_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : W5500_CS_Pin W5500_RST_Pin */
  GPIO_InitStruct.Pin = W5500_CS_Pin|W5500_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
