/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    CSP_ER_BLE.h
  * @author  MCD Application Team
  * @brief   Header for CSP_ER_BLE.c
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
#ifndef CSP_ER_BLE_H
#define CSP_ER_BLE_H

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
  CSP_ER_BLE_CSP_MOD_STA_ID_RW,
  CSP_ER_BLE_CSP_PROC_PARA_SEL_RW,
  CSP_ER_BLE_CSP_LVDT_SENSOR_SCALE_TYPE_RW,
  CSP_ER_BLE_CSP_PID_VAL_FOR_POS_AFT_EN_RW,
  CSP_ER_BLE_CSP_BAUD_RATE_RW,
  CSP_ER_BLE_CSP_PARITY_STOP_BIT_RW,
  CSP_ER_BLE_CSP_SVP_PID_UP_P_VAL_RW,
  CSP_ER_BLE_CSP_SVP_PID_UP_I_VAL_RW,
  CSP_ER_BLE_CSP_SVP_PID_UP_D_VAL_RW,
  CSP_ER_BLE_CSP_SVP_PID_UP_I_TIME_RW,
  CSP_ER_BLE_CSP_SVP_PID_DOWN_P_VAL_RW,
  CSP_ER_BLE_CSP_SVP_PID_DOWN_I_VAL_RW,
  CSP_ER_BLE_CSP_SVP_PID_DOWN_D_VAL_RW,
  CSP_ER_BLE_CSP_SVP_PID_DOWN_I_TIME_RW,
  CSP_ER_BLE_CSP_PTR_P1_MIN_RW,
  CSP_ER_BLE_CSP_PTR_P1_MAX_RW,
  CSP_ER_BLE_CSP_PTR_P2_MIN_RW,
  CSP_ER_BLE_CSP_PTR_P2_MAX_RW,
  /* USER CODE BEGIN Service3_CharOpcode_t */

  /* USER CODE END Service3_CharOpcode_t */
  CSP_ER_BLE_CHAROPCODE_LAST
} CSP_ER_BLE_CharOpcode_t;

typedef enum
{
  CSP_ER_BLE_CSP_MOD_STA_ID_RW_READ_EVT,
  CSP_ER_BLE_CSP_MOD_STA_ID_RW_WRITE_EVT,
  CSP_ER_BLE_CSP_PROC_PARA_SEL_RW_READ_EVT,
  CSP_ER_BLE_CSP_PROC_PARA_SEL_RW_WRITE_EVT,
  CSP_ER_BLE_CSP_LVDT_SENSOR_SCALE_TYPE_RW_READ_EVT,
  CSP_ER_BLE_CSP_LVDT_SENSOR_SCALE_TYPE_RW_WRITE_EVT,
  CSP_ER_BLE_CSP_PID_VAL_FOR_POS_AFT_EN_RW_READ_EVT,
  CSP_ER_BLE_CSP_PID_VAL_FOR_POS_AFT_EN_RW_WRITE_EVT,
  CSP_ER_BLE_CSP_BAUD_RATE_RW_READ_EVT,
  CSP_ER_BLE_CSP_BAUD_RATE_RW_WRITE_EVT,
  CSP_ER_BLE_CSP_PARITY_STOP_BIT_RW_READ_EVT,
  CSP_ER_BLE_CSP_PARITY_STOP_BIT_RW_WRITE_EVT,
  CSP_ER_BLE_CSP_SVP_PID_UP_P_VAL_RW_READ_EVT,
  CSP_ER_BLE_CSP_SVP_PID_UP_P_VAL_RW_WRITE_EVT,
  CSP_ER_BLE_CSP_SVP_PID_UP_I_VAL_RW_READ_EVT,
  CSP_ER_BLE_CSP_SVP_PID_UP_I_VAL_RW_WRITE_EVT,
  CSP_ER_BLE_CSP_SVP_PID_UP_D_VAL_RW_READ_EVT,
  CSP_ER_BLE_CSP_SVP_PID_UP_D_VAL_RW_WRITE_EVT,
  CSP_ER_BLE_CSP_SVP_PID_UP_I_TIME_RW_READ_EVT,
  CSP_ER_BLE_CSP_SVP_PID_UP_I_TIME_RW_WRITE_EVT,
  CSP_ER_BLE_CSP_SVP_PID_DOWN_P_VAL_RW_READ_EVT,
  CSP_ER_BLE_CSP_SVP_PID_DOWN_P_VAL_RW_WRITE_EVT,
  CSP_ER_BLE_CSP_SVP_PID_DOWN_I_VAL_RW_READ_EVT,
  CSP_ER_BLE_CSP_SVP_PID_DOWN_I_VAL_RW_WRITE_EVT,
  CSP_ER_BLE_CSP_SVP_PID_DOWN_D_VAL_RW_READ_EVT,
  CSP_ER_BLE_CSP_SVP_PID_DOWN_D_VAL_RW_WRITE_EVT,
  CSP_ER_BLE_CSP_SVP_PID_DOWN_I_TIME_RW_READ_EVT,
  CSP_ER_BLE_CSP_SVP_PID_DOWN_I_TIME_RW_WRITE_EVT,
  CSP_ER_BLE_CSP_PTR_P1_MIN_RW_READ_EVT,
  CSP_ER_BLE_CSP_PTR_P1_MIN_RW_WRITE_EVT,
  CSP_ER_BLE_CSP_PTR_P1_MAX_RW_READ_EVT,
  CSP_ER_BLE_CSP_PTR_P1_MAX_RW_WRITE_EVT,
  CSP_ER_BLE_CSP_PTR_P2_MIN_RW_READ_EVT,
  CSP_ER_BLE_CSP_PTR_P2_MIN_RW_WRITE_EVT,
  CSP_ER_BLE_CSP_PTR_P2_MAX_RW_READ_EVT,
  CSP_ER_BLE_CSP_PTR_P2_MAX_RW_WRITE_EVT,
  /* USER CODE BEGIN Service3_OpcodeEvt_t */

  /* USER CODE END Service3_OpcodeEvt_t */
  CSP_ER_BLE_BOOT_REQUEST_EVT
} CSP_ER_BLE_OpcodeEvt_t;

typedef struct
{
  uint8_t *p_Payload;
  uint8_t Length;

  /* USER CODE BEGIN Service3_Data_t */

  /* USER CODE END Service3_Data_t */
} CSP_ER_BLE_Data_t;

typedef struct
{
  CSP_ER_BLE_OpcodeEvt_t       EvtOpcode;
  CSP_ER_BLE_Data_t             DataTransfered;
  uint16_t                ConnectionHandle;
  uint16_t                AttributeHandle;
  uint8_t                 ServiceInstance;
  /* USER CODE BEGIN Service3_NotificationEvt_t */

  /* USER CODE END Service3_NotificationEvt_t */
} CSP_ER_BLE_NotificationEvt_t;

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
void CSP_ER_BLE_Init(void);
void CSP_ER_BLE_Notification(CSP_ER_BLE_NotificationEvt_t *p_Notification);
tBleStatus CSP_ER_BLE_UpdateValue(CSP_ER_BLE_CharOpcode_t CharOpcode, CSP_ER_BLE_Data_t *pData);
/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

#ifdef __cplusplus
}
#endif

#endif /*CSP_ER_BLE_H */
