/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    CAL_app.h
  * @author  MCD Application Team
  * @brief   Header for CAL_app.c
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
#ifndef CAL_APP_H
#define CAL_APP_H

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
  CAL_CONN_HANDLE_EVT,
  CAL_DISCON_HANDLE_EVT,

  /* USER CODE BEGIN Service6_OpcodeNotificationEvt_t */

  /* USER CODE END Service6_OpcodeNotificationEvt_t */

  CAL_LAST_EVT,
} CAL_APP_OpcodeNotificationEvt_t;

typedef struct
{
  CAL_APP_OpcodeNotificationEvt_t          EvtOpcode;
  uint16_t                                 ConnectionHandle;

  /* USER CODE BEGIN CAL_APP_ConnHandleNotEvt_t */

  /* USER CODE END CAL_APP_ConnHandleNotEvt_t */
} CAL_APP_ConnHandleNotEvt_t;
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
void CAL_APP_Init(void);
void CAL_APP_EvtRx(CAL_APP_ConnHandleNotEvt_t *p_Notification);
/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

#ifdef __cplusplus
}
#endif

#endif /*CAL_APP_H */
