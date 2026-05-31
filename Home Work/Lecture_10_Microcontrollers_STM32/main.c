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
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdint.h>
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define FLASH_APP_START_ADDRESS   0x08007000UL
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
typedef struct
{
    uint8_t  byte_count;
    uint16_t address;
    uint8_t  record_type;
    uint8_t  data[32];
    uint8_t  checksum;
} IntelHexRecord;

const char *hex_file[] =
{
    ":100000000102030405060708090A0B0C0D0E0F1068",
    ":10001000112233445566778899AABBCCDDEEFF00E8",
    ":100020000A0B0C0D0E0F1011121314151617181948",
    ":10003000A1A2A3A4A5A6A7A8A9AAABACADAEAFB0D8",
    ":04004000556677886A",
    ":00000001FF"
};

#define HEX_LINES_COUNT   (sizeof(hex_file) / sizeof(hex_file[0]))

static uint8_t hex_char_to_value(char c);
static uint8_t hex_byte_to_value(char high, char low);
static uint8_t parse_hex_line(const char *line, IntelHexRecord *record);
static uint8_t check_hex_checksum(const IntelHexRecord *record);
static HAL_StatusTypeDef flash_erase_page(uint32_t page_address);
static HAL_StatusTypeDef flash_write_data(uint32_t address, uint8_t *data, uint8_t length);


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  /* USER CODE BEGIN 2 */
  IntelHexRecord record;

  HAL_FLASH_Unlock();

  flash_erase_page(FLASH_APP_START_ADDRESS);

  for (uint32_t i = 0; i < HEX_LINES_COUNT; i++)
  {
      if (parse_hex_line(hex_file[i], &record) == 0)
      {
          while (1);
      }

      if (check_hex_checksum(&record) == 0)
      {
          while (1);
      }

      if (record.record_type == 0x00)
      {
          uint32_t flash_address = FLASH_APP_START_ADDRESS + record.address;

          if (flash_write_data(flash_address, record.data, record.byte_count) != HAL_OK)
          {
              while (1);
          }
      }
      else if (record.record_type == 0x01)
      {
          break;
      }
  }

  HAL_FLASH_Lock();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
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
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA9 */
  GPIO_InitStruct.Pin = GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
static uint8_t hex_char_to_value(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';

    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;

    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;

    return 0;
}

static uint8_t hex_byte_to_value(char high, char low)
{
    return (hex_char_to_value(high) << 4) | hex_char_to_value(low);
}

static uint8_t parse_hex_line(const char *line, IntelHexRecord *record)
{
    if (line[0] != ':')
        return 0;

    record->byte_count = hex_byte_to_value(line[1], line[2]);

    record->address = 0;
    record->address |= ((uint16_t)hex_byte_to_value(line[3], line[4]) << 8);
    record->address |=  (uint16_t)hex_byte_to_value(line[5], line[6]);

    record->record_type = hex_byte_to_value(line[7], line[8]);

    uint32_t index = 9;

    for (uint8_t i = 0; i < record->byte_count; i++)
    {
        record->data[i] = hex_byte_to_value(line[index], line[index + 1]);
        index += 2;
    }

    record->checksum = hex_byte_to_value(line[index], line[index + 1]);

    return 1;
}

static uint8_t check_hex_checksum(const IntelHexRecord *record)
{
    uint32_t sum = 0;

    sum += record->byte_count;
    sum += (record->address >> 8) & 0xFF;
    sum += record->address & 0xFF;
    sum += record->record_type;

    for (uint8_t i = 0; i < record->byte_count; i++)
    {
        sum += record->data[i];
    }

    sum += record->checksum;

    if ((sum & 0xFF) == 0)
        return 1;
    else
        return 0;
}

static HAL_StatusTypeDef flash_erase_page(uint32_t page_address)
{
    FLASH_EraseInitTypeDef erase;
    uint32_t page_error = 0;

    erase.TypeErase = FLASH_TYPEERASE_PAGES;
    erase.PageAddress = page_address;
    erase.NbPages = 1;

    return HAL_FLASHEx_Erase(&erase, &page_error);
}

static HAL_StatusTypeDef flash_write_data(uint32_t address, uint8_t *data, uint8_t length)
{
    HAL_StatusTypeDef status = HAL_OK;

    for (uint8_t i = 0; i < length; i += 2)
    {
        uint16_t half_word = 0xFFFF;

        half_word = data[i];

        if ((i + 1) < length)
        {
            half_word |= ((uint16_t)data[i + 1] << 8);
        }
        else
        {
            half_word |= 0xFF00;
        }

        status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,
                                   address + i,
                                   half_word);

        if (status != HAL_OK)
        {
            return status;
        }
    }

    return HAL_OK;
}
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
