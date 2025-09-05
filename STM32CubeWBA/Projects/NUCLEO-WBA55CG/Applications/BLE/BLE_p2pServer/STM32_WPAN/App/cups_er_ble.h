/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    CUPS_ER_BLE.h
  * @author  MCD Application Team
  * @brief   Header for CUPS_ER_BLE.c
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
#ifndef CUPS_ER_BLE_H
#define CUPS_ER_BLE_H

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
  CUPS_ER_BLE_CUPS_UNITP2T2_RW,
  CUPS_ER_BLE_CUPS_POS_SPAN_RW,
  CUPS_ER_BLE_CUPS_VALVE_CON_DIR_RW,
  CUPS_ER_BLE_CUPS_SEL_VALVE_FRICTION_RW,
  CUPS_ER_BLE_CUPS_SEL_VALVE_CHAR_SUPPO_RW,
  CUPS_ER_BLE_CUPS_CON_VALVE_PIL_VALVE_RW,
  CUPS_ER_BLE_CUPS_UNITP1T1_RW,
  CUPS_ER_BLE_CUPS_SETPOINT_P2_RW,
  CUPS_ER_BLE_CUPS_TIME_CONST_RW,
  CUPS_ER_BLE_CUPS_PID_P_VAL_RW,
  CUPS_ER_BLE_CUPS_PID_I_VAL_RW,
  CUPS_ER_BLE_CUPS_PID_D_VAL_RW,
  CUPS_ER_BLE_CUPS_PID_I_TIME_RW,
  CUPS_ER_BLE_CUPS_P1_MIN_RANGE_RW,
  CUPS_ER_BLE_CUPS_P1_MAX_RANGE_RW,
  CUPS_ER_BLE_CUPS_VALVE_CONST_KV_RW,
  CUPS_ER_BLE_CUPS_FLOW_FACTOR_RW,
  CUPS_ER_BLE_CUPS_PRESSURE_EN_DIS,
  /* USER CODE BEGIN Service2_CharOpcode_t */

  /* USER CODE END Service2_CharOpcode_t */
  CUPS_ER_BLE_CHAROPCODE_LAST
} CUPS_ER_BLE_CharOpcode_t;

typedef enum
{
  CUPS_ER_BLE_CUPS_UNITP2T2_RW_READ_EVT,
  CUPS_ER_BLE_CUPS_UNITP2T2_RW_WRITE_EVT,
  CUPS_ER_BLE_CUPS_POS_SPAN_RW_READ_EVT,
  CUPS_ER_BLE_CUPS_POS_SPAN_RW_WRITE_EVT,
  CUPS_ER_BLE_CUPS_VALVE_CON_DIR_RW_READ_EVT,
  CUPS_ER_BLE_CUPS_VALVE_CON_DIR_RW_WRITE_EVT,
  CUPS_ER_BLE_CUPS_SEL_VALVE_FRICTION_RW_READ_EVT,
  CUPS_ER_BLE_CUPS_SEL_VALVE_FRICTION_RW_WRITE_EVT,
  CUPS_ER_BLE_CUPS_SEL_VALVE_CHAR_SUPPO_RW_READ_EVT,
  CUPS_ER_BLE_CUPS_SEL_VALVE_CHAR_SUPPO_RW_WRITE_EVT,
  CUPS_ER_BLE_CUPS_CON_VALVE_PIL_VALVE_RW_READ_EVT,
  CUPS_ER_BLE_CUPS_CON_VALVE_PIL_VALVE_RW_WRITE_EVT,
  CUPS_ER_BLE_CUPS_UNITP1T1_RW_READ_EVT,
  CUPS_ER_BLE_CUPS_UNITP1T1_RW_WRITE_EVT,
  CUPS_ER_BLE_CUPS_SETPOINT_P2_RW_READ_EVT,
  CUPS_ER_BLE_CUPS_SETPOINT_P2_RW_WRITE_EVT,
  CUPS_ER_BLE_CUPS_SETPOINT_P2_RW_NOTIFY_ENABLED_EVT,
  CUPS_ER_BLE_CUPS_SETPOINT_P2_RW_NOTIFY_DISABLED_EVT,
  CUPS_ER_BLE_CUPS_TIME_CONST_RW_READ_EVT,
  CUPS_ER_BLE_CUPS_TIME_CONST_RW_WRITE_EVT,
  CUPS_ER_BLE_CUPS_PID_P_VAL_RW_READ_EVT,
  CUPS_ER_BLE_CUPS_PID_P_VAL_RW_WRITE_EVT,
  CUPS_ER_BLE_CUPS_PID_I_VAL_RW_READ_EVT,
  CUPS_ER_BLE_CUPS_PID_I_VAL_RW_WRITE_EVT,
  CUPS_ER_BLE_CUPS_PID_D_VAL_RW_READ_EVT,
  CUPS_ER_BLE_CUPS_PID_D_VAL_RW_WRITE_EVT,
  CUPS_ER_BLE_CUPS_PID_I_TIME_RW_READ_EVT,
  CUPS_ER_BLE_CUPS_PID_I_TIME_RW_WRITE_EVT,
  CUPS_ER_BLE_CUPS_P1_MIN_RANGE_RW_READ_EVT,
  CUPS_ER_BLE_CUPS_P1_MIN_RANGE_RW_WRITE_EVT,
  CUPS_ER_BLE_CUPS_P1_MAX_RANGE_RW_READ_EVT,
  CUPS_ER_BLE_CUPS_P1_MAX_RANGE_RW_WRITE_EVT,
  CUPS_ER_BLE_CUPS_VALVE_CONST_KV_RW_READ_EVT,
  CUPS_ER_BLE_CUPS_VALVE_CONST_KV_RW_WRITE_EVT,
  CUPS_ER_BLE_CUPS_FLOW_FACTOR_RW_READ_EVT,
  CUPS_ER_BLE_CUPS_FLOW_FACTOR_RW_WRITE_EVT,
  CUPS_ER_BLE_CUPS_PRESSURE_EN_DIS_READ_EVT,
  CUPS_ER_BLE_CUPS_PRESSURE_EN_DIS_WRITE_EVT,
  /* USER CODE BEGIN Service2_OpcodeEvt_t */

  /* USER CODE END Service2_OpcodeEvt_t */
  CUPS_ER_BLE_BOOT_REQUEST_EVT
} CUPS_ER_BLE_OpcodeEvt_t;

typedef struct
{
  uint8_t *p_Payload;
  uint8_t Length;

  /* USER CODE BEGIN Service2_Data_t */

  /* USER CODE END Service2_Data_t */
} CUPS_ER_BLE_Data_t;

typedef struct
{
  CUPS_ER_BLE_OpcodeEvt_t       EvtOpcode;
  CUPS_ER_BLE_Data_t             DataTransfered;
  uint16_t                ConnectionHandle;
  uint16_t                AttributeHandle;
  uint8_t                 ServiceInstance;
  /* USER CODE BEGIN Service2_NotificationEvt_t */

  /* USER CODE END Service2_NotificationEvt_t */
} CUPS_ER_BLE_NotificationEvt_t;

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
void CUPS_ER_BLE_Init(void);
void CUPS_ER_BLE_Notification(CUPS_ER_BLE_NotificationEvt_t *p_Notification);
tBleStatus CUPS_ER_BLE_UpdateValue(CUPS_ER_BLE_CharOpcode_t CharOpcode, CUPS_ER_BLE_Data_t *pData);
/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

#ifdef __cplusplus
}
#endif

#endif /*CUPS_ER_BLE_H */
