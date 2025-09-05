/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    CSP_ER_BLE_app.c
  * @author  MCD Application Team
  * @brief   CSP_ER_BLE_app application definition.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "app_common.h"
#include "log_module.h"
#include "app_ble.h"
#include "ll_sys_if.h"
#include "dbg_trace.h"
#include "csp_er_ble_app.h"
#include "csp_er_ble.h"
#include "stm32_rtos.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "user_utils.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

typedef enum
{
  /* USER CODE BEGIN Service3_APP_SendInformation_t */

  /* USER CODE END Service3_APP_SendInformation_t */
  CSP_ER_BLE_APP_SENDINFORMATION_LAST
} CSP_ER_BLE_APP_SendInformation_t;

typedef struct
{
  /* USER CODE BEGIN Service3_APP_Context_t */

  /* USER CODE END Service3_APP_Context_t */
  uint16_t              ConnectionHandle;
} CSP_ER_BLE_APP_Context_t;

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* External variables --------------------------------------------------------*/
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Private macros ------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
static CSP_ER_BLE_APP_Context_t CSP_ER_BLE_APP_Context;

uint8_t a_CSP_ER_BLE_UpdateCharData[247];

/* USER CODE BEGIN PV */
uint8_t lu8ModStaID = 0 ;
uint8_t lu8ProcParaSel  = 0 ;
uint8_t lu8LvdtSenScalType = 0 ;
uint8_t lu8PidValForPosAftEn  = 0 ;
uint8_t lu8BaudRate  = 0 ;
uint8_t lu8ParityStopBit = 0 ;
float   lf32PidUpPVal = 0;
float   lf32PidUpIVal = 0;
float   lf32PidUpDVal = 0;
float   lf32PidUpITime = 0;    
float   lf32PidDownPVal = 0;
float   lf32PidDownIVal = 0;
float   lf32PidDownDVal = 0;
float   lf32PidDownITime = 0;
float   lf32PtrP1Min = 0;
float   lf32PtrP1Max = 0;
float   lf32PtrP2Min = 0;
float   lf32PtrP2Max = 0;
uint8_t lu8floatTemp_csp[4]  = {0};

uint8_t lu8ModStaID_notify_flag=0;
uint8_t lu8ProcParaSel_notify_flag=0;
uint8_t lu8LvdtSenScalType_notify_flag = 0 ;
uint8_t lu8PidValForPosAftEn_notify_flag  = 0 ;
uint8_t lu8BaudRate_notify_flag  = 0 ;
uint8_t lu8ParityStopBit_notify_flag = 0 ;
uint8_t lf32PidUpPVal_notify_flag = 0;
uint8_t lf32PidUpIVal_notify_flag = 0;
uint8_t lf32PidUpDVal_notify_flag = 0;
uint8_t lf32PidUpITime_notify_flag = 0;    
uint8_t lf32PidDownPVal_notify_flag = 0;
uint8_t lf32PidDownIVal_notify_flag = 0;
uint8_t lf32PidDownDVal_notify_flag = 0;
uint8_t lf32PidDownITime_notify_flag = 0;
uint8_t lf32PtrP1Min_notify_flag = 0;
uint8_t lf32PtrP1Max_notify_flag = 0;
uint8_t lf32PtrP2Min_notify_flag = 0;
uint8_t lf32PtrP2Max_notify_flag = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

/* USER CODE BEGIN PFP */
static void CSP_ER_BLE_APP_Parameters_context_Init(void);
void CUPS_ER_BLE_Csp_mod_sta_id_rw_ReadUpdate(void); /* Property ReadResponseUpdate */
void CUPS_ER_BLE_Csp_proc_para_sel_rw_ReadUpdate(void); /* Property ReadResponseUpdate */
void CUPS_ER_BLE_Csp_lvdt_sensor_scale_type_rw_ReadUpdate(void); /* Property ReadResponseUpdate */
void CUPS_ER_BLE_Csp_pid_val_for_pos_aft_en_rw_ReadUpdate(void); /* Property ReadResponseUpdate */
void CUPS_ER_BLE_Csp_baud_rate_rw_ReadUpdate(void); /* Property ReadResponseUpdate */
void CUPS_ER_BLE_Csp_parity_stop_bit_rw_ReadUpdate(void); /* Property ReadResponseUpdate */
void CUPS_ER_BLE_Csp_svp_pid_up_p_val_rw_ReadUpdate(void); /* Property ReadResponseUpdate */
void CUPS_ER_BLE_Csp_svp_pid_up_i_val_rw_ReadUpdate(void); /* Property ReadResponseUpdate */
void CUPS_ER_BLE_Csp_svp_pid_up_d_val_rw_ReadUpdate(void); /* Property ReadResponseUpdate */
void CUPS_ER_BLE_Csp_svp_pid_up_i_time_rw_ReadUpdate(void); /* Property ReadResponseUpdate */
void CUPS_ER_BLE_Csp_svp_pid_down_p_val_rw_ReadUpdate(void); /* Property ReadResponseUpdate */
void CUPS_ER_BLE_Csp_svp_pid_down_i_val_rw_ReadUpdate(void); /* Property ReadResponseUpdate */
void CUPS_ER_BLE_Csp_svp_pid_down_d_val_rw_ReadUpdate(void); /* Property ReadResponseUpdate */
void CUPS_ER_BLE_Csp_svp_pid_down_i_time_rw_ReadUpdate(void); /* Property ReadResponseUpdate */
void CUPS_ER_BLE_Csp_ptr_p1_min_rw_ReadUpdate(void); /* Property ReadResponseUpdate */
void CUPS_ER_BLE_Csp_ptr_p1_max_rw_ReadUpdate(void); /* Property ReadResponseUpdate */
void CUPS_ER_BLE_Csp_ptr_p2_min_rw_ReadUpdate(void); /* Property ReadResponseUpdate */
void CUPS_ER_BLE_Csp_ptr_p2_max_rw_ReadUpdate(void); /* Property ReadResponseUpdate */
/* USER CODE END PFP */

/* Functions Definition ------------------------------------------------------*/
void CSP_ER_BLE_Notification(CSP_ER_BLE_NotificationEvt_t *p_Notification)
{
  /* USER CODE BEGIN Service3_Notification_1 */

  /* USER CODE END Service3_Notification_1 */
  switch(p_Notification->EvtOpcode)
  {
    /* USER CODE BEGIN Service3_Notification_Service3_EvtOpcode */

    /* USER CODE END Service3_Notification_Service3_EvtOpcode */

    case CSP_ER_BLE_CSP_MOD_STA_ID_RW_READ_EVT:
      /* USER CODE BEGIN Service3Char1_READ_EVT */
			LOG_INFO_APP("CSP_MOD_STA_ID READ \r\n");
			CUPS_ER_BLE_Csp_mod_sta_id_rw_ReadUpdate();
      /* USER CODE END Service3Char1_READ_EVT */
      break;

    case CSP_ER_BLE_CSP_MOD_STA_ID_RW_WRITE_EVT:
      /* USER CODE BEGIN Service3Char1_WRITE_EVT */
			lu8ModStaID = p_Notification->DataTransfered.p_Payload[0];
			LOG_INFO_APP("CSP_MOD_STA_ID WRITE : 0x%02x\r\n",lu8ModStaID);
			lu8ModStaID_notify_flag =1; 
      /* USER CODE END Service3Char1_WRITE_EVT */
      break;

    case CSP_ER_BLE_CSP_PROC_PARA_SEL_RW_READ_EVT:
      /* USER CODE BEGIN Service3Char2_READ_EVT */
			LOG_INFO_APP("CSP_PROC_PARA_SEL READ \r\n");
			CUPS_ER_BLE_Csp_proc_para_sel_rw_ReadUpdate();
      /* USER CODE END Service3Char2_READ_EVT */
      break;

    case CSP_ER_BLE_CSP_PROC_PARA_SEL_RW_WRITE_EVT:
      /* USER CODE BEGIN Service3Char2_WRITE_EVT */
			lu8ProcParaSel = p_Notification->DataTransfered.p_Payload[0];
			LOG_INFO_APP("CSP_PROC_PARA_SEL WRITE : 0x%02x\r\n",lu8ProcParaSel);
			lu8ProcParaSel_notify_flag =1; 
      /* USER CODE END Service3Char2_WRITE_EVT */
      break;

    case CSP_ER_BLE_CSP_LVDT_SENSOR_SCALE_TYPE_RW_READ_EVT:
      /* USER CODE BEGIN Service3Char3_READ_EVT */
			LOG_INFO_APP("CSP_LVDT_SENSOR_SCALE_TYPE READ \r\n");
			CUPS_ER_BLE_Csp_lvdt_sensor_scale_type_rw_ReadUpdate();
      /* USER CODE END Service3Char3_READ_EVT */
      break;

    case CSP_ER_BLE_CSP_LVDT_SENSOR_SCALE_TYPE_RW_WRITE_EVT:
      /* USER CODE BEGIN Service3Char3_WRITE_EVT */
			lu8LvdtSenScalType = p_Notification->DataTransfered.p_Payload[0];
			LOG_INFO_APP("CSP_LVDT_SENSOR_SCALE_TYPE WRITE : 0x%02x\r\n",lu8LvdtSenScalType);
			lu8LvdtSenScalType_notify_flag = 1 ;
      /* USER CODE END Service3Char3_WRITE_EVT */
      break;

    case CSP_ER_BLE_CSP_PID_VAL_FOR_POS_AFT_EN_RW_READ_EVT:
      /* USER CODE BEGIN Service3Char4_READ_EVT */
			LOG_INFO_APP("CSP_PID_VAL_FOR_POS_AFT_EN READ \r\n");
			CUPS_ER_BLE_Csp_pid_val_for_pos_aft_en_rw_ReadUpdate();
      /* USER CODE END Service3Char4_READ_EVT */
      break;

    case CSP_ER_BLE_CSP_PID_VAL_FOR_POS_AFT_EN_RW_WRITE_EVT:
      /* USER CODE BEGIN Service3Char4_WRITE_EVT */
			lu8PidValForPosAftEn = p_Notification->DataTransfered.p_Payload[0];
			LOG_INFO_APP("CSP_PID_VAL_FOR_POS_AFT_EN WRITE : 0x%02x\r\n",lu8PidValForPosAftEn);
			lu8PidValForPosAftEn_notify_flag  = 1 ;
      /* USER CODE END Service3Char4_WRITE_EVT */
      break;

    case CSP_ER_BLE_CSP_BAUD_RATE_RW_READ_EVT:
      /* USER CODE BEGIN Service3Char5_READ_EVT */
			LOG_INFO_APP("CSP_BAUD_RATE READ \r\n");
			CUPS_ER_BLE_Csp_baud_rate_rw_ReadUpdate();
      /* USER CODE END Service3Char5_READ_EVT */
      break;

    case CSP_ER_BLE_CSP_BAUD_RATE_RW_WRITE_EVT:
      /* USER CODE BEGIN Service3Char5_WRITE_EVT */
			lu8BaudRate = p_Notification->DataTransfered.p_Payload[0];
			LOG_INFO_APP("CSP_BAUD_RATE WRITE : 0x%02x\r\n",lu8BaudRate);
			lu8BaudRate_notify_flag  = 1 ;
      /* USER CODE END Service3Char5_WRITE_EVT */
      break;

    case CSP_ER_BLE_CSP_PARITY_STOP_BIT_RW_READ_EVT:
      /* USER CODE BEGIN Service3Char6_READ_EVT */
			LOG_INFO_APP("CSP_PARITY_STOP_BIT READ \r\n");
			CUPS_ER_BLE_Csp_parity_stop_bit_rw_ReadUpdate();
      /* USER CODE END Service3Char6_READ_EVT */
      break;

    case CSP_ER_BLE_CSP_PARITY_STOP_BIT_RW_WRITE_EVT:
      /* USER CODE BEGIN Service3Char6_WRITE_EVT */
			lu8ParityStopBit = p_Notification->DataTransfered.p_Payload[0];
			LOG_INFO_APP("CSP_BAUD_RATE WRITE : 0x%02x\r\n",lu8ParityStopBit);
			lu8ParityStopBit_notify_flag = 1 ;
      /* USER CODE END Service3Char6_WRITE_EVT */
      break;

    case CSP_ER_BLE_CSP_SVP_PID_UP_P_VAL_RW_READ_EVT:
      /* USER CODE BEGIN Service3Char7_READ_EVT */
			LOG_INFO_APP("CSP_SVP_PID_UP_P_VAL READ \r\n");
			CUPS_ER_BLE_Csp_svp_pid_up_p_val_rw_ReadUpdate();
      /* USER CODE END Service3Char7_READ_EVT */
      break;

    case CSP_ER_BLE_CSP_SVP_PID_UP_P_VAL_RW_WRITE_EVT:
      /* USER CODE BEGIN Service3Char7_WRITE_EVT */
			memset(lu8floatTemp_csp,0,sizeof(lu8floatTemp_csp));
			memcpy(lu8floatTemp_csp, p_Notification->DataTransfered.p_Payload,p_Notification->DataTransfered.Length);
      convert_byte_array_to_float(lu8floatTemp_csp, &lf32PidUpPVal);
			LOG_INFO_APP("CSP_SVP_PID_UP_P_VAL WRITE DATA = %s, FLT = %f, LEN = %d\r\n", lu8floatTemp_csp, lf32PidUpPVal, p_Notification->DataTransfered.Length);
			lf32PidUpPVal_notify_flag =1;
      /* USER CODE END Service3Char7_WRITE_EVT */
      break;

    case CSP_ER_BLE_CSP_SVP_PID_UP_I_VAL_RW_READ_EVT:
      /* USER CODE BEGIN Service3Char8_READ_EVT */
			LOG_INFO_APP("CSP_SVP_PID_UP_I_VAL READ \r\n");
			CUPS_ER_BLE_Csp_svp_pid_up_i_val_rw_ReadUpdate();
      /* USER CODE END Service3Char8_READ_EVT */
      break;

    case CSP_ER_BLE_CSP_SVP_PID_UP_I_VAL_RW_WRITE_EVT:
      /* USER CODE BEGIN Service3Char8_WRITE_EVT */
			memset(lu8floatTemp_csp,0,sizeof(lu8floatTemp_csp));
			memcpy(lu8floatTemp_csp, p_Notification->DataTransfered.p_Payload,p_Notification->DataTransfered.Length);
      convert_byte_array_to_float(lu8floatTemp_csp, &lf32PidUpIVal);
			LOG_INFO_APP("CSP_SVP_PID_UP_I_VAL WRITE DATA = %s, FLT = %f, LEN = %d\r\n", lu8floatTemp_csp, lf32PidUpIVal, p_Notification->DataTransfered.Length);
			lf32PidUpIVal_notify_flag =1;
      /* USER CODE END Service3Char8_WRITE_EVT */
      break;

    case CSP_ER_BLE_CSP_SVP_PID_UP_D_VAL_RW_READ_EVT:
      /* USER CODE BEGIN Service3Char9_READ_EVT */
			LOG_INFO_APP("CSP_SVP_PID_UP_D_VAL READ \r\n");
			CUPS_ER_BLE_Csp_svp_pid_up_d_val_rw_ReadUpdate();
      /* USER CODE END Service3Char9_READ_EVT */
      break;

    case CSP_ER_BLE_CSP_SVP_PID_UP_D_VAL_RW_WRITE_EVT:
      /* USER CODE BEGIN Service3Char9_WRITE_EVT */
			memset(lu8floatTemp_csp,0,sizeof(lu8floatTemp_csp));
			memcpy(lu8floatTemp_csp, p_Notification->DataTransfered.p_Payload,p_Notification->DataTransfered.Length);
      convert_byte_array_to_float(lu8floatTemp_csp, &lf32PidUpDVal);
			LOG_INFO_APP("CSP_SVP_PID_UP_D_VAL WRITE DATA = %s, FLT = %f, LEN = %d\r\n", lu8floatTemp_csp, lf32PidUpDVal, p_Notification->DataTransfered.Length);
			lf32PidUpDVal_notify_flag =1;
      /* USER CODE END Service3Char9_WRITE_EVT */
      break;

    case CSP_ER_BLE_CSP_SVP_PID_UP_I_TIME_RW_READ_EVT:
      /* USER CODE BEGIN Service3Char10_READ_EVT */
			LOG_INFO_APP("CSP_SVP_PID_UP_I_TIME READ \r\n");
			CUPS_ER_BLE_Csp_svp_pid_up_i_time_rw_ReadUpdate();
      /* USER CODE END Service3Char10_READ_EVT */
      break;

    case CSP_ER_BLE_CSP_SVP_PID_UP_I_TIME_RW_WRITE_EVT:
      /* USER CODE BEGIN Service3Char10_WRITE_EVT */
			memset(lu8floatTemp_csp,0,sizeof(lu8floatTemp_csp));
			memcpy(lu8floatTemp_csp, p_Notification->DataTransfered.p_Payload,p_Notification->DataTransfered.Length);
      convert_byte_array_to_float(lu8floatTemp_csp, &lf32PidUpITime);
			LOG_INFO_APP("CSP_SVP_PID_UP_I_TIME WRITE DATA = %s, FLT = %f, LEN = %d\r\n", lu8floatTemp_csp, lf32PidUpITime, p_Notification->DataTransfered.Length);
			lf32PidUpITime_notify_flag =1;
      /* USER CODE END Service3Char10_WRITE_EVT */
      break;

    case CSP_ER_BLE_CSP_SVP_PID_DOWN_P_VAL_RW_READ_EVT:
      /* USER CODE BEGIN Service3Char11_READ_EVT */
			LOG_INFO_APP("CSP_SVP_PID_DOWN_P_VAL READ \r\n");
			CUPS_ER_BLE_Csp_svp_pid_down_p_val_rw_ReadUpdate();
      /* USER CODE END Service3Char11_READ_EVT */
      break;

    case CSP_ER_BLE_CSP_SVP_PID_DOWN_P_VAL_RW_WRITE_EVT:
      /* USER CODE BEGIN Service3Char11_WRITE_EVT */
			memset(lu8floatTemp_csp,0,sizeof(lu8floatTemp_csp));
			memcpy(lu8floatTemp_csp, p_Notification->DataTransfered.p_Payload,p_Notification->DataTransfered.Length);
      convert_byte_array_to_float(lu8floatTemp_csp, &lf32PidDownPVal);
			LOG_INFO_APP("CSP_SVP_PID_DOWN_P_VAL WRITE DATA = %s, FLT= %f, LEN = %d\r\n", lu8floatTemp_csp, lf32PidDownPVal, p_Notification->DataTransfered.Length);
			lf32PidDownPVal_notify_flag =1;
      /* USER CODE END Service3Char11_WRITE_EVT */
      break;

    case CSP_ER_BLE_CSP_SVP_PID_DOWN_I_VAL_RW_READ_EVT:
      /* USER CODE BEGIN Service3Char12_READ_EVT */
			LOG_INFO_APP("CSP_SVP_PID_DOWN_I_VAL READ \r\n");
			CUPS_ER_BLE_Csp_svp_pid_down_i_val_rw_ReadUpdate();
      /* USER CODE END Service3Char12_READ_EVT */
      break;

    case CSP_ER_BLE_CSP_SVP_PID_DOWN_I_VAL_RW_WRITE_EVT:
      /* USER CODE BEGIN Service3Char12_WRITE_EVT */
			memset(lu8floatTemp_csp,0,sizeof(lu8floatTemp_csp));
			memcpy(lu8floatTemp_csp, p_Notification->DataTransfered.p_Payload,p_Notification->DataTransfered.Length);
      convert_byte_array_to_float(lu8floatTemp_csp, &lf32PidDownIVal);
			LOG_INFO_APP("CSP_SVP_PID_DOWN_I_VAL WRITE DATA = %s, FLT = %f, LEN = %d\r\n", lu8floatTemp_csp, lf32PidDownIVal, p_Notification->DataTransfered.Length);
			lf32PidDownIVal_notify_flag =1;
      /* USER CODE END Service3Char12_WRITE_EVT */
      break;

    case CSP_ER_BLE_CSP_SVP_PID_DOWN_D_VAL_RW_READ_EVT:
      /* USER CODE BEGIN Service3Char13_READ_EVT */
			LOG_INFO_APP("CSP_SVP_PID_DOWN_D_VAL READ \r\n");
			CUPS_ER_BLE_Csp_svp_pid_down_d_val_rw_ReadUpdate();
      /* USER CODE END Service3Char13_READ_EVT */
      break;

    case CSP_ER_BLE_CSP_SVP_PID_DOWN_D_VAL_RW_WRITE_EVT:
      /* USER CODE BEGIN Service3Char13_WRITE_EVT */
			memset(lu8floatTemp_csp,0,sizeof(lu8floatTemp_csp));
			memcpy(lu8floatTemp_csp, p_Notification->DataTransfered.p_Payload,p_Notification->DataTransfered.Length);
      convert_byte_array_to_float(lu8floatTemp_csp, &lf32PidDownDVal);
			LOG_INFO_APP("CSP_SVP_PID_DOWN_D_VAL WRITE DATA = %s, FLT = %f, LEN = %d\r\n", lu8floatTemp_csp, lf32PidDownDVal, p_Notification->DataTransfered.Length);
			lf32PidDownDVal_notify_flag =1;
      /* USER CODE END Service3Char13_WRITE_EVT */
      break;

    case CSP_ER_BLE_CSP_SVP_PID_DOWN_I_TIME_RW_READ_EVT:
      /* USER CODE BEGIN Service3Char14_READ_EVT */
			LOG_INFO_APP("CSP_SVP_PID_DOWN_I_TIME READ \r\n");
			CUPS_ER_BLE_Csp_svp_pid_down_i_time_rw_ReadUpdate();
      /* USER CODE END Service3Char14_READ_EVT */
      break;

    case CSP_ER_BLE_CSP_SVP_PID_DOWN_I_TIME_RW_WRITE_EVT:
      /* USER CODE BEGIN Service3Char14_WRITE_EVT */
			memset(lu8floatTemp_csp,0,sizeof(lu8floatTemp_csp));
			memcpy(lu8floatTemp_csp, p_Notification->DataTransfered.p_Payload,p_Notification->DataTransfered.Length);
      convert_byte_array_to_float(lu8floatTemp_csp, &lf32PidDownITime);
			LOG_INFO_APP("CSP_SVP_PID_DOWN_I_TIME WRITE DATA = %s, FLT = %f, LEN = %d\r\n", lu8floatTemp_csp, lf32PidDownITime, p_Notification->DataTransfered.Length);
			lf32PidDownITime_notify_flag =1;
      /* USER CODE END Service3Char14_WRITE_EVT */
      break;

    case CSP_ER_BLE_CSP_PTR_P1_MIN_RW_READ_EVT:
      /* USER CODE BEGIN Service3Char15_READ_EVT */
			LOG_INFO_APP("CSP_PTR_P1_MIN READ \r\n");
			CUPS_ER_BLE_Csp_ptr_p1_min_rw_ReadUpdate();
      /* USER CODE END Service3Char15_READ_EVT */
      break;

    case CSP_ER_BLE_CSP_PTR_P1_MIN_RW_WRITE_EVT:
      /* USER CODE BEGIN Service3Char15_WRITE_EVT */
			memset(lu8floatTemp_csp,0,sizeof(lu8floatTemp_csp));
			memcpy(lu8floatTemp_csp, p_Notification->DataTransfered.p_Payload,p_Notification->DataTransfered.Length);
      convert_byte_array_to_float(lu8floatTemp_csp, &lf32PtrP1Min);
			LOG_INFO_APP("CSP_PTR_P1_MIN WRITE DATA = %s, FLT = %f, LEN = %d\r\n", lu8floatTemp_csp, lf32PtrP1Min, p_Notification->DataTransfered.Length);
			lf32PtrP1Min_notify_flag = 1;
      /* USER CODE END Service3Char15_WRITE_EVT */
      break;

    case CSP_ER_BLE_CSP_PTR_P1_MAX_RW_READ_EVT:
      /* USER CODE BEGIN Service3Char16_READ_EVT */
			LOG_INFO_APP("CSP_PTR_P1_MAX READ \r\n");
			CUPS_ER_BLE_Csp_ptr_p1_max_rw_ReadUpdate();
      /* USER CODE END Service3Char16_READ_EVT */
      break;

    case CSP_ER_BLE_CSP_PTR_P1_MAX_RW_WRITE_EVT:
      /* USER CODE BEGIN Service3Char16_WRITE_EVT */
			memset(lu8floatTemp_csp,0,sizeof(lu8floatTemp_csp));
			memcpy(lu8floatTemp_csp, p_Notification->DataTransfered.p_Payload,p_Notification->DataTransfered.Length);
      convert_byte_array_to_float(lu8floatTemp_csp, &lf32PtrP1Max);
			LOG_INFO_APP("CSP_PTR_P1_MAX WRITE DATA = %s, FLT = %f, LEN = %d\r\n", lu8floatTemp_csp, lf32PtrP1Max, p_Notification->DataTransfered.Length);
			lf32PtrP1Max_notify_flag = 1;
      /* USER CODE END Service3Char16_WRITE_EVT */
      break;

    case CSP_ER_BLE_CSP_PTR_P2_MIN_RW_READ_EVT:
      /* USER CODE BEGIN Service3Char17_READ_EVT */
			LOG_INFO_APP("CSP_PTR_P2_MIN READ \r\n");
			CUPS_ER_BLE_Csp_ptr_p2_min_rw_ReadUpdate();
      /* USER CODE END Service3Char17_READ_EVT */
      break;

    case CSP_ER_BLE_CSP_PTR_P2_MIN_RW_WRITE_EVT:
      /* USER CODE BEGIN Service3Char17_WRITE_EVT */
			memset(lu8floatTemp_csp,0,sizeof(lu8floatTemp_csp));
			memcpy(lu8floatTemp_csp, p_Notification->DataTransfered.p_Payload,p_Notification->DataTransfered.Length);
      convert_byte_array_to_float(lu8floatTemp_csp, &lf32PtrP2Min);
			LOG_INFO_APP("CSP_PTR_P2_MIN WRITE DATA = %s, FLT = %f, LEN = %d\r\n", lu8floatTemp_csp, lf32PtrP2Min, p_Notification->DataTransfered.Length);
			lf32PtrP2Min_notify_flag = 1;
      /* USER CODE END Service3Char17_WRITE_EVT */
      break;

    case CSP_ER_BLE_CSP_PTR_P2_MAX_RW_READ_EVT:
      /* USER CODE BEGIN Service3Char18_READ_EVT */
			LOG_INFO_APP("CSP_PTR_P2_MAX READ \r\n");
			CUPS_ER_BLE_Csp_ptr_p2_max_rw_ReadUpdate();
      /* USER CODE END Service3Char18_READ_EVT */
      break;

    case CSP_ER_BLE_CSP_PTR_P2_MAX_RW_WRITE_EVT:
      /* USER CODE BEGIN Service3Char18_WRITE_EVT */
			memset(lu8floatTemp_csp,0,sizeof(lu8floatTemp_csp));
			memcpy(lu8floatTemp_csp, p_Notification->DataTransfered.p_Payload,p_Notification->DataTransfered.Length);
      convert_byte_array_to_float(lu8floatTemp_csp, &lf32PtrP2Max);
			LOG_INFO_APP("CSP_PTR_P2_MIN WRITE DATA = %s, FLT = %f, LEN = %d\r\n", lu8floatTemp_csp, lf32PtrP2Max, p_Notification->DataTransfered.Length);
			lf32PtrP2Max_notify_flag = 1;
      /* USER CODE END Service3Char18_WRITE_EVT */
      break;

    default:
      /* USER CODE BEGIN Service3_Notification_default */

      /* USER CODE END Service3_Notification_default */
      break;
  }
  /* USER CODE BEGIN Service3_Notification_2 */

  /* USER CODE END Service3_Notification_2 */
  return;
}

void CSP_ER_BLE_APP_EvtRx(CSP_ER_BLE_APP_ConnHandleNotEvt_t *p_Notification)
{
  /* USER CODE BEGIN Service3_APP_EvtRx_1 */

  /* USER CODE END Service3_APP_EvtRx_1 */

  switch(p_Notification->EvtOpcode)
  {
    /* USER CODE BEGIN Service3_APP_EvtRx_Service3_EvtOpcode */

    /* USER CODE END Service3_APP_EvtRx_Service3_EvtOpcode */
    case CSP_ER_BLE_CONN_HANDLE_EVT :
      /* USER CODE BEGIN Service3_APP_CONN_HANDLE_EVT */

      /* USER CODE END Service3_APP_CONN_HANDLE_EVT */
      break;

    case CSP_ER_BLE_DISCON_HANDLE_EVT :
      /* USER CODE BEGIN Service3_APP_DISCON_HANDLE_EVT */
			CSP_ER_BLE_APP_Parameters_context_Init();
      /* USER CODE END Service3_APP_DISCON_HANDLE_EVT */
      break;

    default:
      /* USER CODE BEGIN Service3_APP_EvtRx_default */

      /* USER CODE END Service3_APP_EvtRx_default */
      break;
  }

  /* USER CODE BEGIN Service3_APP_EvtRx_2 */

  /* USER CODE END Service3_APP_EvtRx_2 */

  return;
}

void CSP_ER_BLE_APP_Init(void)
{
  UNUSED(CSP_ER_BLE_APP_Context);
  CSP_ER_BLE_Init();

  /* USER CODE BEGIN Service3_APP_Init */
	CSP_ER_BLE_APP_Parameters_context_Init();
  /* USER CODE END Service3_APP_Init */
  return;
}

/* USER CODE BEGIN FD */

/* USER CODE END FD */

/*************************************************************
 *
 * LOCAL FUNCTIONS
 *
 *************************************************************/

/* USER CODE BEGIN FD_LOCAL_FUNCTIONS */
static void CSP_ER_BLE_APP_Parameters_context_Init(void)
{
	return;
}

void CUPS_ER_BLE_Csp_mod_sta_id_rw_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CSP_ER_BLE_Data_t csp_er_ble_readresp_data;

  csp_er_ble_readresp_data.p_Payload = (uint8_t*)a_CSP_ER_BLE_UpdateCharData;
  csp_er_ble_readresp_data.Length = 0;

  /* USER CODE BEGIN Service3Char1_NS_1 */
	a_CSP_ER_BLE_UpdateCharData[0] = lu8ModStaID;
	LOG_INFO_APP("MOD STA ID READRESP DATA : %02x\r\n",a_CSP_ER_BLE_UpdateCharData[0]);
	/* Update readresp data length */
  csp_er_ble_readresp_data.Length = (csp_er_ble_readresp_data.Length) + 1;
	CSP_ER_BLE_UpdateValue(CSP_ER_BLE_CSP_MOD_STA_ID_RW, &csp_er_ble_readresp_data);
  /* USER CODE END Service3Char1_NS_1 */
  return;
}

void CUPS_ER_BLE_Csp_proc_para_sel_rw_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CSP_ER_BLE_Data_t csp_er_ble_readresp_data;

  csp_er_ble_readresp_data.p_Payload = (uint8_t*)a_CSP_ER_BLE_UpdateCharData;
  csp_er_ble_readresp_data.Length = 0;

  /* USER CODE BEGIN Service3Char2_NS_1 */
	a_CSP_ER_BLE_UpdateCharData[0] = lu8ProcParaSel;
	LOG_INFO_APP("PROC PARA SEL READRESP DATA : %02x\r\n",a_CSP_ER_BLE_UpdateCharData[0]);
	/* Update readresp data length */
  csp_er_ble_readresp_data.Length = (csp_er_ble_readresp_data.Length) + 1;
	CSP_ER_BLE_UpdateValue(CSP_ER_BLE_CSP_PROC_PARA_SEL_RW, &csp_er_ble_readresp_data);
  /* USER CODE END Service3Char2_NS_1 */
  return;
}

void CUPS_ER_BLE_Csp_lvdt_sensor_scale_type_rw_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CSP_ER_BLE_Data_t csp_er_ble_readresp_data;

  csp_er_ble_readresp_data.p_Payload = (uint8_t*)a_CSP_ER_BLE_UpdateCharData;
  csp_er_ble_readresp_data.Length = 0;

  /* USER CODE BEGIN Service3Char3_NS_1 */
	a_CSP_ER_BLE_UpdateCharData[0] = lu8LvdtSenScalType;
	LOG_INFO_APP("LVDT SENSOR SCALE TYPE READRESP DATA : %02x\r\n",a_CSP_ER_BLE_UpdateCharData[0]);
	/* Update readresp data length */
  csp_er_ble_readresp_data.Length = (csp_er_ble_readresp_data.Length) + 1;
	CSP_ER_BLE_UpdateValue(CSP_ER_BLE_CSP_LVDT_SENSOR_SCALE_TYPE_RW, &csp_er_ble_readresp_data);
  /* USER CODE END Service3Char3_NS_1 */
  return;
}

void CUPS_ER_BLE_Csp_pid_val_for_pos_aft_en_rw_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CSP_ER_BLE_Data_t csp_er_ble_readresp_data;

  csp_er_ble_readresp_data.p_Payload = (uint8_t*)a_CSP_ER_BLE_UpdateCharData;
  csp_er_ble_readresp_data.Length = 0;

  /* USER CODE BEGIN Service3Char4_NS_1 */
	a_CSP_ER_BLE_UpdateCharData[0] = lu8PidValForPosAftEn;
	LOG_INFO_APP("PID VAL FOR POS AFT EN READRESP DATA : %02x\r\n",a_CSP_ER_BLE_UpdateCharData[0]);
	/* Update readresp data length */
  csp_er_ble_readresp_data.Length = (csp_er_ble_readresp_data.Length) + 1;
	CSP_ER_BLE_UpdateValue(CSP_ER_BLE_CSP_PID_VAL_FOR_POS_AFT_EN_RW, &csp_er_ble_readresp_data);
  /* USER CODE END Service3Char4_NS_1 */
  return;
}

void CUPS_ER_BLE_Csp_baud_rate_rw_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CSP_ER_BLE_Data_t csp_er_ble_readresp_data;

  csp_er_ble_readresp_data.p_Payload = (uint8_t*)a_CSP_ER_BLE_UpdateCharData;
  csp_er_ble_readresp_data.Length = 0;

  /* USER CODE BEGIN Service3Char5_NS_1 */
	a_CSP_ER_BLE_UpdateCharData[0] = lu8BaudRate;
	LOG_INFO_APP("CSP BAUD RATE READRESP DATA : %02x\r\n",a_CSP_ER_BLE_UpdateCharData[0]);
	/* Update readresp data length */
  csp_er_ble_readresp_data.Length = (csp_er_ble_readresp_data.Length) + 1;
	CSP_ER_BLE_UpdateValue(CSP_ER_BLE_CSP_BAUD_RATE_RW, &csp_er_ble_readresp_data);
  /* USER CODE END Service3Char5_NS_1 */
  return;
}

void CUPS_ER_BLE_Csp_parity_stop_bit_rw_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CSP_ER_BLE_Data_t csp_er_ble_readresp_data;

  csp_er_ble_readresp_data.p_Payload = (uint8_t*)a_CSP_ER_BLE_UpdateCharData;
  csp_er_ble_readresp_data.Length = 0;

  /* USER CODE BEGIN Service3Char6_NS_1 */
	a_CSP_ER_BLE_UpdateCharData[0] = lu8ParityStopBit;
	LOG_INFO_APP("PARITY STOP BIT READRESP DATA : %02x\r\n",a_CSP_ER_BLE_UpdateCharData[0]);
	/* Update readresp data length */
  csp_er_ble_readresp_data.Length = (csp_er_ble_readresp_data.Length) + 1;
	CSP_ER_BLE_UpdateValue(CSP_ER_BLE_CSP_PARITY_STOP_BIT_RW, &csp_er_ble_readresp_data);
  /* USER CODE END Service3Char6_NS_1 */
  return;
}

void CUPS_ER_BLE_Csp_svp_pid_up_p_val_rw_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CSP_ER_BLE_Data_t csp_er_ble_readresp_data;

  csp_er_ble_readresp_data.p_Payload = (uint8_t*)a_CSP_ER_BLE_UpdateCharData;
  csp_er_ble_readresp_data.Length = 0;

  /* USER CODE BEGIN Service3Char7_NS_1 */
	memset(a_CSP_ER_BLE_UpdateCharData,0,sizeof(a_CSP_ER_BLE_UpdateCharData));
	convert_float_to_byte_array(lf32PidUpPVal, lu8floatTemp_csp);
  strcpy((char*)a_CSP_ER_BLE_UpdateCharData, (char*)lu8floatTemp_csp);
  LOG_INFO_APP("PID UP P VAL READRESP DATA : %s\r\n", a_CSP_ER_BLE_UpdateCharData);
	/* Update readresp data length */
  csp_er_ble_readresp_data.Length = (csp_er_ble_readresp_data.Length) + 1;
	CSP_ER_BLE_UpdateValue(CSP_ER_BLE_CSP_SVP_PID_UP_P_VAL_RW, &csp_er_ble_readresp_data);
  /* USER CODE END Service3Char7_NS_1 */
  return;
}

void CUPS_ER_BLE_Csp_svp_pid_up_i_val_rw_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CSP_ER_BLE_Data_t csp_er_ble_readresp_data;

  csp_er_ble_readresp_data.p_Payload = (uint8_t*)a_CSP_ER_BLE_UpdateCharData;
  csp_er_ble_readresp_data.Length = 0;

  /* USER CODE BEGIN Service3Char8_NS_1 */
	memset(a_CSP_ER_BLE_UpdateCharData,0,sizeof(a_CSP_ER_BLE_UpdateCharData));
	convert_float_to_byte_array(lf32PidUpIVal, lu8floatTemp_csp);
  strcpy((char*)a_CSP_ER_BLE_UpdateCharData, (char*)lu8floatTemp_csp);
  LOG_INFO_APP("PID UP I VAL READRESP DATA : %s\r\n", a_CSP_ER_BLE_UpdateCharData);
	/* Update readresp data length */
  csp_er_ble_readresp_data.Length = (csp_er_ble_readresp_data.Length) + 4;
	CSP_ER_BLE_UpdateValue(CSP_ER_BLE_CSP_SVP_PID_UP_I_VAL_RW, &csp_er_ble_readresp_data);
  /* USER CODE END Service3Char8_NS_1 */
  return;
}

void CUPS_ER_BLE_Csp_svp_pid_up_d_val_rw_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CSP_ER_BLE_Data_t csp_er_ble_readresp_data;

  csp_er_ble_readresp_data.p_Payload = (uint8_t*)a_CSP_ER_BLE_UpdateCharData;
  csp_er_ble_readresp_data.Length = 0;

  /* USER CODE BEGIN Service3Char9_NS_1 */
	memset(a_CSP_ER_BLE_UpdateCharData,0,sizeof(a_CSP_ER_BLE_UpdateCharData));
	convert_float_to_byte_array(lf32PidUpDVal, lu8floatTemp_csp);
  strcpy((char*)a_CSP_ER_BLE_UpdateCharData, (char*)lu8floatTemp_csp);
  LOG_INFO_APP("PID UP D VAL READRESP DATA : %s\r\n", a_CSP_ER_BLE_UpdateCharData);
	/* Update readresp data length */
  csp_er_ble_readresp_data.Length = (csp_er_ble_readresp_data.Length) + 4;
	CSP_ER_BLE_UpdateValue(CSP_ER_BLE_CSP_SVP_PID_UP_D_VAL_RW, &csp_er_ble_readresp_data);
  /* USER CODE END Service3Char9_NS_1 */
  return;
}

void CUPS_ER_BLE_Csp_svp_pid_up_i_time_rw_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CSP_ER_BLE_Data_t csp_er_ble_readresp_data;

  csp_er_ble_readresp_data.p_Payload = (uint8_t*)a_CSP_ER_BLE_UpdateCharData;
  csp_er_ble_readresp_data.Length = 0;

  /* USER CODE BEGIN Service3Char10_NS_1 */
	memset(a_CSP_ER_BLE_UpdateCharData,0,sizeof(a_CSP_ER_BLE_UpdateCharData));
	convert_float_to_byte_array(lf32PidUpITime, lu8floatTemp_csp);
  strcpy((char*)a_CSP_ER_BLE_UpdateCharData, (char*)lu8floatTemp_csp);
  LOG_INFO_APP("PID UP I TIME READRESP DATA : %s\r\n", a_CSP_ER_BLE_UpdateCharData);
	/* Update readresp data length */
  csp_er_ble_readresp_data.Length = (csp_er_ble_readresp_data.Length) + 4;
	CSP_ER_BLE_UpdateValue(CSP_ER_BLE_CSP_SVP_PID_UP_I_TIME_RW, &csp_er_ble_readresp_data);
  /* USER CODE END Service3Char10_NS_1 */
  return;
}

void CUPS_ER_BLE_Csp_svp_pid_down_p_val_rw_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CSP_ER_BLE_Data_t csp_er_ble_readresp_data;

  csp_er_ble_readresp_data.p_Payload = (uint8_t*)a_CSP_ER_BLE_UpdateCharData;
  csp_er_ble_readresp_data.Length = 0;

  /* USER CODE BEGIN Service3Char11_NS_1 */
	memset(a_CSP_ER_BLE_UpdateCharData,0,sizeof(a_CSP_ER_BLE_UpdateCharData));
	convert_float_to_byte_array(lf32PidDownPVal, lu8floatTemp_csp);
  strcpy((char*)a_CSP_ER_BLE_UpdateCharData, (char*)lu8floatTemp_csp);
  LOG_INFO_APP("PID DOWN P VAL READRESP DATA : %s\r\n", a_CSP_ER_BLE_UpdateCharData);
	/* Update readresp data length */
  csp_er_ble_readresp_data.Length = (csp_er_ble_readresp_data.Length) + 4;
	CSP_ER_BLE_UpdateValue(CSP_ER_BLE_CSP_SVP_PID_DOWN_P_VAL_RW, &csp_er_ble_readresp_data);
  /* USER CODE END Service3Char11_NS_1 */
  return;
}

void CUPS_ER_BLE_Csp_svp_pid_down_i_val_rw_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CSP_ER_BLE_Data_t csp_er_ble_readresp_data;

  csp_er_ble_readresp_data.p_Payload = (uint8_t*)a_CSP_ER_BLE_UpdateCharData;
  csp_er_ble_readresp_data.Length = 0;

  /* USER CODE BEGIN Service3Char12_NS_1 */
	memset(a_CSP_ER_BLE_UpdateCharData,0,sizeof(a_CSP_ER_BLE_UpdateCharData));
	convert_float_to_byte_array(lf32PidDownIVal, lu8floatTemp_csp);
  strcpy((char*)a_CSP_ER_BLE_UpdateCharData, (char*)lu8floatTemp_csp);
  LOG_INFO_APP("PID DOWN I VAL READRESP DATA : %s\r\n", a_CSP_ER_BLE_UpdateCharData);
	/* Update readresp data length */
  csp_er_ble_readresp_data.Length = (csp_er_ble_readresp_data.Length) + 4;
	CSP_ER_BLE_UpdateValue(CSP_ER_BLE_CSP_SVP_PID_DOWN_I_VAL_RW, &csp_er_ble_readresp_data);
  /* USER CODE END Service3Char12_NS_1 */
  return;
}

void CUPS_ER_BLE_Csp_svp_pid_down_d_val_rw_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CSP_ER_BLE_Data_t csp_er_ble_readresp_data;

  csp_er_ble_readresp_data.p_Payload = (uint8_t*)a_CSP_ER_BLE_UpdateCharData;
  csp_er_ble_readresp_data.Length = 0;

  /* USER CODE BEGIN Service3Char13_NS_1 */
	memset(a_CSP_ER_BLE_UpdateCharData,0,sizeof(a_CSP_ER_BLE_UpdateCharData));
	convert_float_to_byte_array(lf32PidDownDVal, lu8floatTemp_csp);
  strcpy((char*)a_CSP_ER_BLE_UpdateCharData, (char*)lu8floatTemp_csp);
  LOG_INFO_APP("PID DOWN D VAL READRESP DATA : %s\r\n", a_CSP_ER_BLE_UpdateCharData);
	/* Update readresp data length */
  csp_er_ble_readresp_data.Length = (csp_er_ble_readresp_data.Length) + 4;
	CSP_ER_BLE_UpdateValue(CSP_ER_BLE_CSP_SVP_PID_DOWN_D_VAL_RW, &csp_er_ble_readresp_data);
  /* USER CODE END Service3Char13_NS_1 */
  return;
}

void CUPS_ER_BLE_Csp_svp_pid_down_i_time_rw_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CSP_ER_BLE_Data_t csp_er_ble_readresp_data;

  csp_er_ble_readresp_data.p_Payload = (uint8_t*)a_CSP_ER_BLE_UpdateCharData;
  csp_er_ble_readresp_data.Length = 0;

  /* USER CODE BEGIN Service3Char14_NS_1 */
	memset(a_CSP_ER_BLE_UpdateCharData,0,sizeof(a_CSP_ER_BLE_UpdateCharData));
	convert_float_to_byte_array(lf32PidDownITime, lu8floatTemp_csp);
  strcpy((char*)a_CSP_ER_BLE_UpdateCharData, (char*)lu8floatTemp_csp);
  LOG_INFO_APP("PID DOWN I TIME READRESP DATA : %s\r\n", a_CSP_ER_BLE_UpdateCharData);
	/* Update readresp data length */
  csp_er_ble_readresp_data.Length = (csp_er_ble_readresp_data.Length) + 4;
	CSP_ER_BLE_UpdateValue(CSP_ER_BLE_CSP_SVP_PID_DOWN_I_TIME_RW, &csp_er_ble_readresp_data);
  /* USER CODE END Service3Char14_NS_1 */
  return;
}

void CUPS_ER_BLE_Csp_ptr_p1_min_rw_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CSP_ER_BLE_Data_t csp_er_ble_readresp_data;

  csp_er_ble_readresp_data.p_Payload = (uint8_t*)a_CSP_ER_BLE_UpdateCharData;
  csp_er_ble_readresp_data.Length = 0;

  /* USER CODE BEGIN Service3Char15_NS_1 */
	memset(a_CSP_ER_BLE_UpdateCharData,0,sizeof(a_CSP_ER_BLE_UpdateCharData));
	convert_float_to_byte_array(lf32PtrP1Min, lu8floatTemp_csp);
  strcpy((char*)a_CSP_ER_BLE_UpdateCharData, (char*)lu8floatTemp_csp);
  LOG_INFO_APP("PTR P1 MIN READRESP DATA : %s\r\n", a_CSP_ER_BLE_UpdateCharData);
	/* Update readresp data length */
  csp_er_ble_readresp_data.Length = (csp_er_ble_readresp_data.Length) + 4;
	CSP_ER_BLE_UpdateValue(CSP_ER_BLE_CSP_PTR_P1_MIN_RW, &csp_er_ble_readresp_data);
  /* USER CODE END Service3Char15_NS_1 */
  return;
}

void CUPS_ER_BLE_Csp_ptr_p1_max_rw_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CSP_ER_BLE_Data_t csp_er_ble_readresp_data;

  csp_er_ble_readresp_data.p_Payload = (uint8_t*)a_CSP_ER_BLE_UpdateCharData;
  csp_er_ble_readresp_data.Length = 0;

  /* USER CODE BEGIN Service3Char16_NS_1 */
	memset(a_CSP_ER_BLE_UpdateCharData,0,sizeof(a_CSP_ER_BLE_UpdateCharData));
	convert_float_to_byte_array(lf32PtrP1Max, lu8floatTemp_csp);
  strcpy((char*)a_CSP_ER_BLE_UpdateCharData, (char*)lu8floatTemp_csp);
  LOG_INFO_APP("PTR P1 MAX READRESP DATA : %s\r\n", a_CSP_ER_BLE_UpdateCharData);
	/* Update readresp data length */
  csp_er_ble_readresp_data.Length = (csp_er_ble_readresp_data.Length) + 4;
	CSP_ER_BLE_UpdateValue(CSP_ER_BLE_CSP_PTR_P1_MAX_RW, &csp_er_ble_readresp_data);
  /* USER CODE END Service3Char16_NS_1 */
  return;
}

void CUPS_ER_BLE_Csp_ptr_p2_min_rw_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CSP_ER_BLE_Data_t csp_er_ble_readresp_data;

  csp_er_ble_readresp_data.p_Payload = (uint8_t*)a_CSP_ER_BLE_UpdateCharData;
  csp_er_ble_readresp_data.Length = 0;

  /* USER CODE BEGIN Service3Char17_NS_1 */
	memset(a_CSP_ER_BLE_UpdateCharData,0,sizeof(a_CSP_ER_BLE_UpdateCharData));
	convert_float_to_byte_array(lf32PtrP2Min, lu8floatTemp_csp);
  strcpy((char*)a_CSP_ER_BLE_UpdateCharData, (char*)lu8floatTemp_csp);
  LOG_INFO_APP("PTR P2 MIN READRESP DATA : %s\r\n", a_CSP_ER_BLE_UpdateCharData);
	/* Update readresp data length */
  csp_er_ble_readresp_data.Length = (csp_er_ble_readresp_data.Length) + 4;
	CSP_ER_BLE_UpdateValue(CSP_ER_BLE_CSP_PTR_P2_MIN_RW, &csp_er_ble_readresp_data);
  /* USER CODE END Service3Char17_NS_1 */
  return;
}

void CUPS_ER_BLE_Csp_ptr_p2_max_rw_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CSP_ER_BLE_Data_t csp_er_ble_readresp_data;

  csp_er_ble_readresp_data.p_Payload = (uint8_t*)a_CSP_ER_BLE_UpdateCharData;
  csp_er_ble_readresp_data.Length = 0;

  /* USER CODE BEGIN Service3Char18_NS_1 */
	memset(a_CSP_ER_BLE_UpdateCharData,0,sizeof(a_CSP_ER_BLE_UpdateCharData));
	convert_float_to_byte_array(lf32PtrP2Max, lu8floatTemp_csp);
  strcpy((char*)a_CSP_ER_BLE_UpdateCharData, (char*)lu8floatTemp_csp);
  LOG_INFO_APP("PTR P2 MAX READRESP DATA : %s\r\n", a_CSP_ER_BLE_UpdateCharData);
	/* Update readresp data length */
  csp_er_ble_readresp_data.Length = (csp_er_ble_readresp_data.Length) + 4;
	CSP_ER_BLE_UpdateValue(CSP_ER_BLE_CSP_PTR_P2_MAX_RW, &csp_er_ble_readresp_data);
  /* USER CODE END Service3Char18_NS_1 */
  return;
}
/* USER CODE END FD_LOCAL_FUNCTIONS */
