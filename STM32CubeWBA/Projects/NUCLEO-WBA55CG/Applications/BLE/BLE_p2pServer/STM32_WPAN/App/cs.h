/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    CS.h
  * @author  MCD Application Team
  * @brief   Header for CS.c
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
#ifndef CS_H
#define CS_H

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
  CS_CS_FLOWTEMP,
  CS_CS_P2T2,
  CS_CS_P1T1,
  CS_CS_UNIT_P2T2,
  CS_CS_UNIT_P1T1,
  CS_CS_MOD_COM_ERROR,
  CS_CS_DIAG_ERROR,
  CS_CS_DIAG_WARN,
  CS_CS_INLET_PRES_PD1,
  CS_CS_OUTLET_PRES_PD2,
  CS_CS_OPENING_PER,
  CS_CS_OPERATION_MODE,
  CS_CS_LVDT_AMP,
  CS_CS_TOTALIZER,
  CS_CS_RESET_BUTTON,
  CS_CS_TIME_STAMP_HHMM,
  CS_CS_TIME_STAMP_DDMM,
  CS_CS_YEAR_STAMP_YYYY,
  CS_CS_TOTALIZER_LAST_VAL,
  CS_CS_TOTALIZER_UNIT,
  CS_CS_CONNECTION_STATUS,
  /* USER CODE BEGIN Service5_CharOpcode_t */

  /* USER CODE END Service5_CharOpcode_t */
  CS_CHAROPCODE_LAST
} CS_CharOpcode_t;

typedef enum
{
  CS_CS_FLOWTEMP_READ_EVT,
  CS_CS_FLOWTEMP_NOTIFY_ENABLED_EVT,
  CS_CS_FLOWTEMP_NOTIFY_DISABLED_EVT,
  CS_CS_P2T2_READ_EVT,
  CS_CS_P2T2_NOTIFY_ENABLED_EVT,
  CS_CS_P2T2_NOTIFY_DISABLED_EVT,
  CS_CS_P1T1_READ_EVT,
  CS_CS_P1T1_NOTIFY_ENABLED_EVT,
  CS_CS_P1T1_NOTIFY_DISABLED_EVT,
  CS_CS_UNIT_P2T2_READ_EVT,
  CS_CS_UNIT_P2T2_NOTIFY_ENABLED_EVT,
  CS_CS_UNIT_P2T2_NOTIFY_DISABLED_EVT,
  CS_CS_UNIT_P1T1_READ_EVT,
  CS_CS_UNIT_P1T1_NOTIFY_ENABLED_EVT,
  CS_CS_UNIT_P1T1_NOTIFY_DISABLED_EVT,
  CS_CS_MOD_COM_ERROR_READ_EVT,
  CS_CS_MOD_COM_ERROR_NOTIFY_ENABLED_EVT,
  CS_CS_MOD_COM_ERROR_NOTIFY_DISABLED_EVT,
  CS_CS_DIAG_ERROR_READ_EVT,
  CS_CS_DIAG_ERROR_NOTIFY_ENABLED_EVT,
  CS_CS_DIAG_ERROR_NOTIFY_DISABLED_EVT,
  CS_CS_DIAG_WARN_READ_EVT,
  CS_CS_DIAG_WARN_NOTIFY_ENABLED_EVT,
  CS_CS_DIAG_WARN_NOTIFY_DISABLED_EVT,
  CS_CS_INLET_PRES_PD1_READ_EVT,
  CS_CS_INLET_PRES_PD1_NOTIFY_ENABLED_EVT,
  CS_CS_INLET_PRES_PD1_NOTIFY_DISABLED_EVT,
  CS_CS_OUTLET_PRES_PD2_READ_EVT,
  CS_CS_OUTLET_PRES_PD2_NOTIFY_ENABLED_EVT,
  CS_CS_OUTLET_PRES_PD2_NOTIFY_DISABLED_EVT,
  CS_CS_OPENING_PER_READ_EVT,
  CS_CS_OPENING_PER_NOTIFY_ENABLED_EVT,
  CS_CS_OPENING_PER_NOTIFY_DISABLED_EVT,
  CS_CS_OPERATION_MODE_READ_EVT,
  CS_CS_OPERATION_MODE_NOTIFY_ENABLED_EVT,
  CS_CS_OPERATION_MODE_NOTIFY_DISABLED_EVT,
  CS_CS_LVDT_AMP_READ_EVT,
  CS_CS_LVDT_AMP_NOTIFY_ENABLED_EVT,
  CS_CS_LVDT_AMP_NOTIFY_DISABLED_EVT,
  CS_CS_TOTALIZER_READ_EVT,
  CS_CS_TOTALIZER_WRITE_EVT,
  CS_CS_TOTALIZER_NOTIFY_ENABLED_EVT,
  CS_CS_TOTALIZER_NOTIFY_DISABLED_EVT,
  CS_CS_RESET_BUTTON_READ_EVT,
  CS_CS_RESET_BUTTON_WRITE_EVT,
  CS_CS_TIME_STAMP_HHMM_READ_EVT,
  CS_CS_TIME_STAMP_HHMM_WRITE_EVT,
  CS_CS_TIME_STAMP_HHMM_NOTIFY_ENABLED_EVT,
  CS_CS_TIME_STAMP_HHMM_NOTIFY_DISABLED_EVT,
  CS_CS_TIME_STAMP_DDMM_READ_EVT,
  CS_CS_TIME_STAMP_DDMM_WRITE_EVT,
  CS_CS_TIME_STAMP_DDMM_NOTIFY_ENABLED_EVT,
  CS_CS_TIME_STAMP_DDMM_NOTIFY_DISABLED_EVT,
  CS_CS_YEAR_STAMP_YYYY_READ_EVT,
  CS_CS_YEAR_STAMP_YYYY_WRITE_EVT,
  CS_CS_YEAR_STAMP_YYYY_NOTIFY_ENABLED_EVT,
  CS_CS_YEAR_STAMP_YYYY_NOTIFY_DISABLED_EVT,
  CS_CS_TOTALIZER_LAST_VAL_READ_EVT,
  CS_CS_TOTALIZER_LAST_VAL_NOTIFY_ENABLED_EVT,
  CS_CS_TOTALIZER_LAST_VAL_NOTIFY_DISABLED_EVT,
  CS_CS_TOTALIZER_UNIT_READ_EVT,
  CS_CS_TOTALIZER_UNIT_WRITE_EVT,
  CS_CS_TOTALIZER_UNIT_NOTIFY_ENABLED_EVT,
  CS_CS_TOTALIZER_UNIT_NOTIFY_DISABLED_EVT,
  CS_CS_CONNECTION_STATUS_READ_EVT,
  CS_CS_CONNECTION_STATUS_WRITE_EVT,
  /* USER CODE BEGIN Service5_OpcodeEvt_t */

  /* USER CODE END Service5_OpcodeEvt_t */
  CS_BOOT_REQUEST_EVT
} CS_OpcodeEvt_t;

typedef struct
{
  uint8_t *p_Payload;
  uint8_t Length;

  /* USER CODE BEGIN Service5_Data_t */

  /* USER CODE END Service5_Data_t */
} CS_Data_t;

typedef struct
{
  CS_OpcodeEvt_t       EvtOpcode;
  CS_Data_t             DataTransfered;
  uint16_t                ConnectionHandle;
  uint16_t                AttributeHandle;
  uint8_t                 ServiceInstance;
  /* USER CODE BEGIN Service5_NotificationEvt_t */

  /* USER CODE END Service5_NotificationEvt_t */
} CS_NotificationEvt_t;

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
void CS_Init(void);
void CS_Notification(CS_NotificationEvt_t *p_Notification);
tBleStatus CS_UpdateValue(CS_CharOpcode_t CharOpcode, CS_Data_t *pData);
/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

#ifdef __cplusplus
}
#endif

#endif /*CS_H */
