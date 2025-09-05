/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    TS.h
  * @author  MCD Application Team
  * @brief   Header for TS.c
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef TS_H
#define TS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ble_types.h"
#include "ble_core.h"
#include "svc_ctl.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported defines ----------------------------------------------------------*/
/* USER CODE BEGIN ED */

/* USER CODE END ED */

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  TS_TS_TEST_TYPE,
  TS_TS_POS_PER_VAL,
  TS_TS_PWM_ON_TIME,
  TS_TS_TEST_STATUS,
  TS_TS_TEST_RESP_CODE,
  /* USER CODE BEGIN Service4_CharOpcode_t */

  /* USER CODE END Service4_CharOpcode_t */
  TS_CHAROPCODE_LAST
} TS_CharOpcode_t;

typedef enum
{
  TS_TS_TEST_TYPE_READ_EVT,
  TS_TS_TEST_TYPE_WRITE_EVT,
  TS_TS_POS_PER_VAL_READ_EVT,
  TS_TS_POS_PER_VAL_WRITE_EVT,
  TS_TS_PWM_ON_TIME_READ_EVT,
  TS_TS_PWM_ON_TIME_WRITE_EVT,
  TS_TS_TEST_STATUS_READ_EVT,
  TS_TS_TEST_STATUS_NOTIFY_ENABLED_EVT,
  TS_TS_TEST_STATUS_NOTIFY_DISABLED_EVT,
  TS_TS_TEST_RESP_CODE_READ_EVT,
  TS_TS_TEST_RESP_CODE_NOTIFY_ENABLED_EVT,
  TS_TS_TEST_RESP_CODE_NOTIFY_DISABLED_EVT,
  /* USER CODE BEGIN Service4_OpcodeEvt_t */

  /* USER CODE END Service4_OpcodeEvt_t */
  TS_BOOT_REQUEST_EVT
} TS_OpcodeEvt_t;

typedef struct
{
  uint8_t *p_Payload;
  uint8_t Length;

  /* USER CODE BEGIN Service4_Data_t */

  /* USER CODE END Service4_Data_t */
} TS_Data_t;

typedef struct
{
  TS_OpcodeEvt_t       EvtOpcode;
  TS_Data_t             DataTransfered;
  uint16_t                ConnectionHandle;
  uint16_t                AttributeHandle;
  uint8_t                 ServiceInstance;
  /* USER CODE BEGIN Service4_NotificationEvt_t */

  /* USER CODE END Service4_NotificationEvt_t */
} TS_NotificationEvt_t;

/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* External variables --------------------------------------------------------*/
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Exported macros -----------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void TS_Init(void);
void TS_Notification(TS_NotificationEvt_t *p_Notification);
tBleStatus TS_UpdateValue(TS_CharOpcode_t CharOpcode, TS_Data_t *pData);
/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

#ifdef __cplusplus
}
#endif

#endif /*TS_H */
