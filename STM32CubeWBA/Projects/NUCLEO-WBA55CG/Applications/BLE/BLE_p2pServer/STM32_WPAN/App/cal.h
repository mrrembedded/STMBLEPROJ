/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    CAL.h
  * @author  MCD Application Team
  * @brief   Header for CAL.c
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
#ifndef CAL_H
#define CAL_H

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
  CAL_CS_CALIB_TYPE,
  CAL_CS_CALIB_STATUS,
  CAL_CS_CALIB_RESP_CODE,
  CAL_CS_CALIB_RESERVED,
  /* USER CODE BEGIN Service6_CharOpcode_t */

  /* USER CODE END Service6_CharOpcode_t */
  CAL_CHAROPCODE_LAST
} CAL_CharOpcode_t;

typedef enum
{
  CAL_CS_CALIB_TYPE_READ_EVT,
  CAL_CS_CALIB_TYPE_WRITE_EVT,
  CAL_CS_CALIB_STATUS_READ_EVT,
  CAL_CS_CALIB_STATUS_NOTIFY_ENABLED_EVT,
  CAL_CS_CALIB_STATUS_NOTIFY_DISABLED_EVT,
  CAL_CS_CALIB_RESP_CODE_READ_EVT,
  CAL_CS_CALIB_RESP_CODE_NOTIFY_ENABLED_EVT,
  CAL_CS_CALIB_RESP_CODE_NOTIFY_DISABLED_EVT,
  CAL_CS_CALIB_RESERVED_READ_EVT,
  CAL_CS_CALIB_RESERVED_NOTIFY_ENABLED_EVT,
  CAL_CS_CALIB_RESERVED_NOTIFY_DISABLED_EVT,
  /* USER CODE BEGIN Service6_OpcodeEvt_t */

  /* USER CODE END Service6_OpcodeEvt_t */
  CAL_BOOT_REQUEST_EVT
} CAL_OpcodeEvt_t;

typedef struct
{
  uint8_t *p_Payload;
  uint8_t Length;

  /* USER CODE BEGIN Service6_Data_t */

  /* USER CODE END Service6_Data_t */
} CAL_Data_t;

typedef struct
{
  CAL_OpcodeEvt_t       EvtOpcode;
  CAL_Data_t             DataTransfered;
  uint16_t                ConnectionHandle;
  uint16_t                AttributeHandle;
  uint8_t                 ServiceInstance;
  /* USER CODE BEGIN Service6_NotificationEvt_t */

  /* USER CODE END Service6_NotificationEvt_t */
} CAL_NotificationEvt_t;

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
void CAL_Init(void);
void CAL_Notification(CAL_NotificationEvt_t *p_Notification);
tBleStatus CAL_UpdateValue(CAL_CharOpcode_t CharOpcode, CAL_Data_t *pData);
/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

#ifdef __cplusplus
}
#endif

#endif /*CAL_H */
