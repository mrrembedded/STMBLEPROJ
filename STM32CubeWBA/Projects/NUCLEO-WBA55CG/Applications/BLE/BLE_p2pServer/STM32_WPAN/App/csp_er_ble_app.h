/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    CSP_ER_BLE_app.h
  * @author  MCD Application Team
  * @brief   Header for CSP_ER_BLE_app.c
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
#ifndef CSP_ER_BLE_APP_H
#define CSP_ER_BLE_APP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ble_types.h"
#include "ble_core.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  CSP_ER_BLE_CONN_HANDLE_EVT,
  CSP_ER_BLE_DISCON_HANDLE_EVT,

  /* USER CODE BEGIN Service3_OpcodeNotificationEvt_t */

  /* USER CODE END Service3_OpcodeNotificationEvt_t */

  CSP_ER_BLE_LAST_EVT,
} CSP_ER_BLE_APP_OpcodeNotificationEvt_t;

typedef struct
{
  CSP_ER_BLE_APP_OpcodeNotificationEvt_t          EvtOpcode;
  uint16_t                                 ConnectionHandle;

  /* USER CODE BEGIN CSP_ER_BLE_APP_ConnHandleNotEvt_t */

  /* USER CODE END CSP_ER_BLE_APP_ConnHandleNotEvt_t */
} CSP_ER_BLE_APP_ConnHandleNotEvt_t;
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
void CSP_ER_BLE_APP_Init(void);
void CSP_ER_BLE_APP_EvtRx(CSP_ER_BLE_APP_ConnHandleNotEvt_t *p_Notification);
/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

#ifdef __cplusplus
}
#endif

#endif /*CSP_ER_BLE_APP_H */
