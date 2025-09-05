/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    CUPS_ER_BLE_app.c
  * @author  MCD Application Team
  * @brief   CUPS_ER_BLE_app application definition.
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
#include "cups_er_ble_app.h"
#include "cups_er_ble.h"
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
  Cups_setpoint_p2_rw_NOTIFICATION_OFF,
  Cups_setpoint_p2_rw_NOTIFICATION_ON,
  /* USER CODE BEGIN Service2_APP_SendInformation_t */

  /* USER CODE END Service2_APP_SendInformation_t */
  CUPS_ER_BLE_APP_SENDINFORMATION_LAST
} CUPS_ER_BLE_APP_SendInformation_t;

typedef struct
{
  CUPS_ER_BLE_APP_SendInformation_t     Cups_setpoint_p2_rw_Notification_Status;
  /* USER CODE BEGIN Service2_APP_Context_t */
  /* USER CODE END Service2_APP_Context_t */
  uint16_t              ConnectionHandle;
} CUPS_ER_BLE_APP_Context_t;

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
static CUPS_ER_BLE_APP_Context_t CUPS_ER_BLE_APP_Context;

uint8_t a_CUPS_ER_BLE_UpdateCharData[247];

/* USER CODE BEGIN PV */
uint8_t lu8UnitP2T2 = 0 ;
uint8_t lu8PosSpan  = 0 ;
uint8_t lu8ValConDir = 0 ;
uint8_t lu8SelValFri  = 0 ;
uint8_t lu8SelValCharSuppo  = 0 ;
uint8_t lu8ConValvePilVal = 0 ;
uint8_t lu8UnitP1T1  = 0 ;
float   lf32SetPointP2 = 0;
float   lf32TimeConst = 0;
float   lf32PidPVal = 0;
float   lf32PidIVal = 0;
float   lf32PidDVal = 0;
float   lf32PidITime = 0;
float   lf32P1MinRange = 0;
float   lf32P1MaxRange = 0;
float   lf32ValConstKV = 0;
float   lf32FlowFactor = 0;
uint16_t lu16PressENDIS = 0;
uint8_t lu8PressENDIS[2] = {0};
uint8_t lu8floatTemp_cups[4]  = {0};

/***************************/
uint8_t lu8UnitP2T2_notify_flag=0;
uint8_t lu8PosSpan_notify_flag  = 0 ;
uint8_t lu8ValConDir_notify_flag = 0 ;
uint8_t lu8SelValFri_notify_flag  = 0 ;
uint8_t lu8SelValCharSuppo_notify_flag  = 0 ;
uint8_t lu8ConValvePilVal_notify_flag = 0 ;
uint8_t lu8UnitP1T1_notify_flag  = 0 ;
uint8_t lf32SetPointP2_notify_flag = 0;
uint8_t lf32TimeConst_notify_flag = 0;
uint8_t lf32PidPVal_notify_flag = 0;
uint8_t lf32PidIVal_notify_flag = 0;
uint8_t lf32PidDVal_notify_flag = 0;
uint8_t lf32PidITime_notify_flag = 0;
uint8_t lf32P1MinRange_notify_flag = 0;
uint8_t lf32P1MaxRange_notify_flag = 0;
uint8_t lf32ValConstKV_notify_flag = 0;
uint8_t lf32FlowFactor_notify_flag = 0;
uint8_t lu16PressENDIS_notify_flag = 0;
		
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static void CUPS_ER_BLE_Cups_setpoint_p2_rw_SendNotification(void);

/* USER CODE BEGIN PFP */
static void CUPS_ER_BLE_APP_Parameters_context_Init(void);
void CUPS_ER_BLE_Cups_unitp2t2_rw_ReadUpdate(void); /* Property ReadResponseUpdate */
void CUPS_ER_BLE_Cups_pos_span_rw_ReadUpdate(void); /* Property ReadResponseUpdate */
void CUPS_ER_BLE_Cups_valve_con_dir_rw_ReadUpdate(void); /* Property ReadResponseUpdate */
void CUPS_ER_BLE_Cups_sel_valve_friction_rw_ReadUpdate(void); /* Property ReadResponseUpdate */
void CUPS_ER_BLE_Cups_sel_valve_char_suppo_rw_ReadUpdate(void); /* Property ReadResponseUpdate */
void CUPS_ER_BLE_Cups_con_valve_pil_valve_rw_ReadUpdate(void); /* Property ReadResponseUpdate */
void CUPS_ER_BLE_Cups_unitp1t1_rw_ReadUpdate(void); /* Property ReadResponseUpdate */
void CUPS_ER_BLE_Cups_setpoint_p2_rw_ReadUpdate(void); /* Property ReadResponseUpdate */
void CUPS_ER_BLE_Cups_time_const_rw_ReadUpdate(void); /* Property ReadResponseUpdate */
void CUPS_ER_BLE_Cups_pid_p_val_rw_ReadUpdate(void); /* Property ReadResponseUpdate */
void CUPS_ER_BLE_Cups_pid_i_val_rw_ReadUpdate(void); /* Property ReadResponseUpdate */
void CUPS_ER_BLE_Cups_pid_d_val_rw_ReadUpdate(void); /* Property ReadResponseUpdate */
void CUPS_ER_BLE_Cups_pid_i_time_rw_ReadUpdate(void); /* Property ReadResponseUpdate */
void CUPS_ER_BLE_Cups_p1_min_range_rw_ReadUpdate(void); /* Property ReadResponseUpdate */
void CUPS_ER_BLE_Cups_p1_max_range_rw_ReadUpdate(void); /* Property ReadResponseUpdate */
void CUPS_ER_BLE_Cups_valve_const_kv_rw_ReadUpdate(void); /* Property ReadResponseUpdate */
void CUPS_ER_BLE_Cups_flow_factor_rw_ReadUpdate(void); /* Property ReadResponseUpdate */
void CUPS_ER_BLE_Cups_pressure_en_dis_rw_ReadUpdate(void); /* Property ReadResponseUpdate */
/* USER CODE END PFP */

/* Functions Definition ------------------------------------------------------*/
void CUPS_ER_BLE_Notification(CUPS_ER_BLE_NotificationEvt_t *p_Notification)
{
  /* USER CODE BEGIN Service2_Notification_1 */

  /* USER CODE END Service2_Notification_1 */
  switch(p_Notification->EvtOpcode)
  {
    /* USER CODE BEGIN Service2_Notification_Service2_EvtOpcode */

    /* USER CODE END Service2_Notification_Service2_EvtOpcode */

    case CUPS_ER_BLE_CUPS_UNITP2T2_RW_READ_EVT:
      /* USER CODE BEGIN Service2Char1_READ_EVT */
			LOG_INFO_APP("CUPS_UNITP2T2 READ\r\n");
			CUPS_ER_BLE_Cups_unitp2t2_rw_ReadUpdate();		
      /* USER CODE END Service2Char1_READ_EVT */
      break;

    case CUPS_ER_BLE_CUPS_UNITP2T2_RW_WRITE_EVT:
      /* USER CODE BEGIN Service2Char1_WRITE_EVT */
			lu8UnitP2T2 = p_Notification->DataTransfered.p_Payload[0];
			LOG_INFO_APP("CUPS_UNITP2T2 WRITE : 0x%02x\r\n",lu8UnitP2T2);
			lu8UnitP2T2_notify_flag =1;  
      /* USER CODE END Service2Char1_WRITE_EVT */
      break;

    case CUPS_ER_BLE_CUPS_POS_SPAN_RW_READ_EVT:
      /* USER CODE BEGIN Service2Char2_READ_EVT */
			LOG_INFO_APP("CUPS_POS_SPAN READ\r\n");
			CUPS_ER_BLE_Cups_pos_span_rw_ReadUpdate();
      /* USER CODE END Service2Char2_READ_EVT */
      break;

    case CUPS_ER_BLE_CUPS_POS_SPAN_RW_WRITE_EVT:
      /* USER CODE BEGIN Service2Char2_WRITE_EVT */
			lu8PosSpan = p_Notification->DataTransfered.p_Payload[0];
			LOG_INFO_APP("CUPS_POS_SPAN WRITE : 0x%02x\r\n",lu8PosSpan);
			lu8PosSpan_notify_flag =1;  
      /* USER CODE END Service2Char2_WRITE_EVT */
      break;

    case CUPS_ER_BLE_CUPS_VALVE_CON_DIR_RW_READ_EVT:
      /* USER CODE BEGIN Service2Char3_READ_EVT */
			LOG_INFO_APP("CUPS_VALVE_CON_DIR READ\r\n");
			CUPS_ER_BLE_Cups_valve_con_dir_rw_ReadUpdate();
      /* USER CODE END Service2Char3_READ_EVT */
      break;

    case CUPS_ER_BLE_CUPS_VALVE_CON_DIR_RW_WRITE_EVT:
      /* USER CODE BEGIN Service2Char3_WRITE_EVT */
			lu8ValConDir = p_Notification->DataTransfered.p_Payload[0];
			LOG_INFO_APP("CUPS_VALVE_CON_DIR WRITE : 0x%02x\r\n",lu8ValConDir);
			lu8ValConDir_notify_flag =1;  
      /* USER CODE END Service2Char3_WRITE_EVT */
      break;

    case CUPS_ER_BLE_CUPS_SEL_VALVE_FRICTION_RW_READ_EVT:
      /* USER CODE BEGIN Service2Char4_READ_EVT */
			LOG_INFO_APP("CUPS_SEL_VALVE_FRICTION READ\r\n");
			CUPS_ER_BLE_Cups_sel_valve_friction_rw_ReadUpdate();
      /* USER CODE END Service2Char4_READ_EVT */
      break;

    case CUPS_ER_BLE_CUPS_SEL_VALVE_FRICTION_RW_WRITE_EVT:
      /* USER CODE BEGIN Service2Char4_WRITE_EVT */
			lu8SelValFri = p_Notification->DataTransfered.p_Payload[0];
			LOG_INFO_APP("CUPS_SEL_VALVE_FRICTION WRITE : 0x%02x\r\n",lu8SelValFri);
			lu8SelValFri_notify_flag =1;  
      /* USER CODE END Service2Char4_WRITE_EVT */
      break;

    case CUPS_ER_BLE_CUPS_SEL_VALVE_CHAR_SUPPO_RW_READ_EVT:
      /* USER CODE BEGIN Service2Char5_READ_EVT */
			LOG_INFO_APP("CUPS_SEL_VALVE_CHAR_SUPPO READ\r\n");
			CUPS_ER_BLE_Cups_sel_valve_char_suppo_rw_ReadUpdate();
      /* USER CODE END Service2Char5_READ_EVT */
      break;

    case CUPS_ER_BLE_CUPS_SEL_VALVE_CHAR_SUPPO_RW_WRITE_EVT:
      /* USER CODE BEGIN Service2Char5_WRITE_EVT */
			lu8SelValCharSuppo = p_Notification->DataTransfered.p_Payload[0];
			LOG_INFO_APP("CUPS_SEL_VALVE_CHAR_SUPPO WRITE : 0x%02x\r\n",lu8SelValCharSuppo);
			lu8SelValCharSuppo_notify_flag =1;  
      /* USER CODE END Service2Char5_WRITE_EVT */
      break;

    case CUPS_ER_BLE_CUPS_CON_VALVE_PIL_VALVE_RW_READ_EVT:
      /* USER CODE BEGIN Service2Char6_READ_EVT */
			LOG_INFO_APP("CUPS_CON_VALVE_PIL_VALVE READ\r\n");
			CUPS_ER_BLE_Cups_con_valve_pil_valve_rw_ReadUpdate();
      /* USER CODE END Service2Char6_READ_EVT */
      break;

    case CUPS_ER_BLE_CUPS_CON_VALVE_PIL_VALVE_RW_WRITE_EVT:
      /* USER CODE BEGIN Service2Char6_WRITE_EVT */
		  lu8ConValvePilVal = p_Notification->DataTransfered.p_Payload[0];
			LOG_INFO_APP("CUPS_CON_VALVE_PIL_VALVE WRITE : 0x%02x\r\n",lu8ConValvePilVal);
			lu8ConValvePilVal_notify_flag =1; 
      /* USER CODE END Service2Char6_WRITE_EVT */
      break;

    case CUPS_ER_BLE_CUPS_UNITP1T1_RW_READ_EVT:
      /* USER CODE BEGIN Service2Char7_READ_EVT */
			LOG_INFO_APP("CUPS_UNITP1T1 READ\r\n");
			CUPS_ER_BLE_Cups_unitp1t1_rw_ReadUpdate();
      /* USER CODE END Service2Char7_READ_EVT */
      break;

    case CUPS_ER_BLE_CUPS_UNITP1T1_RW_WRITE_EVT:
      /* USER CODE BEGIN Service2Char7_WRITE_EVT */
			lu8UnitP1T1 = p_Notification->DataTransfered.p_Payload[0];
			LOG_INFO_APP("CUPS_UNITP1T1 WRITE : 0x%02x\r\n",lu8UnitP1T1);
			lu8UnitP1T1_notify_flag =1; 
      /* USER CODE END Service2Char7_WRITE_EVT */
      break;

    case CUPS_ER_BLE_CUPS_SETPOINT_P2_RW_READ_EVT:
      /* USER CODE BEGIN Service2Char8_READ_EVT */
			LOG_INFO_APP("CUPS_SETPOINT_P2 READ\r\n");
			CUPS_ER_BLE_Cups_setpoint_p2_rw_ReadUpdate();
      /* USER CODE END Service2Char8_READ_EVT */
      break;

    case CUPS_ER_BLE_CUPS_SETPOINT_P2_RW_WRITE_EVT:
      /* USER CODE BEGIN Service2Char8_WRITE_EVT */
			memset(lu8floatTemp_cups,0,sizeof(lu8floatTemp_cups));
			memcpy(lu8floatTemp_cups, p_Notification->DataTransfered.p_Payload,p_Notification->DataTransfered.Length);
      convert_byte_array_to_float(lu8floatTemp_cups, &lf32SetPointP2);
			LOG_INFO_APP("CUPS_SETPOINT_P2 WRITE DATA = %s, LEN = %d\r\n", lu8floatTemp_cups, p_Notification->DataTransfered.Length);
			lf32SetPointP2_notify_flag =1;   
      /* USER CODE END Service2Char8_WRITE_EVT */
      break;

    case CUPS_ER_BLE_CUPS_SETPOINT_P2_RW_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN Service2Char8_NOTIFY_ENABLED_EVT */
      CUPS_ER_BLE_APP_Context.Cups_setpoint_p2_rw_Notification_Status = Cups_setpoint_p2_rw_NOTIFICATION_ON;
      LOG_INFO_APP("CUPS_SETPOINT_P2 NOTIFICATION ENABLED\r\n");
      /* USER CODE END Service2Char8_NOTIFY_ENABLED_EVT */
      break;

    case CUPS_ER_BLE_CUPS_SETPOINT_P2_RW_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN Service2Char8_NOTIFY_DISABLED_EVT */
      CUPS_ER_BLE_APP_Context.Cups_setpoint_p2_rw_Notification_Status = Cups_setpoint_p2_rw_NOTIFICATION_OFF;
      LOG_INFO_APP("CUPS_SETPOINT_P2 NOTIFICATION DISABLED\r\n");
      /* USER CODE END Service2Char8_NOTIFY_DISABLED_EVT */
      break;

    case CUPS_ER_BLE_CUPS_TIME_CONST_RW_READ_EVT:
      /* USER CODE BEGIN Service2Char9_READ_EVT */
			LOG_INFO_APP("CUPS_TIME_CONST READ\r\n");
			CUPS_ER_BLE_Cups_time_const_rw_ReadUpdate();
      /* USER CODE END Service2Char9_READ_EVT */
      break;

    case CUPS_ER_BLE_CUPS_TIME_CONST_RW_WRITE_EVT:
      /* USER CODE BEGIN Service2Char9_WRITE_EVT */
			memset(lu8floatTemp_cups,0,sizeof(lu8floatTemp_cups));
			memcpy(lu8floatTemp_cups, p_Notification->DataTransfered.p_Payload,p_Notification->DataTransfered.Length);
      convert_byte_array_to_float(lu8floatTemp_cups, &lf32TimeConst);
			LOG_INFO_APP("CUPS_TIME_CONST WRITE DATA = %s, LEN = %d\r\n", lu8floatTemp_cups, p_Notification->DataTransfered.Length);
			lf32TimeConst_notify_flag =1;   
      /* USER CODE END Service2Char9_WRITE_EVT */
      break;

    case CUPS_ER_BLE_CUPS_PID_P_VAL_RW_READ_EVT:
      /* USER CODE BEGIN Service2Char10_READ_EVT */
			LOG_INFO_APP("CUPS_PID_P_VAL READ\r\n");
			CUPS_ER_BLE_Cups_pid_p_val_rw_ReadUpdate();
      /* USER CODE END Service2Char10_READ_EVT */
      break;

    case CUPS_ER_BLE_CUPS_PID_P_VAL_RW_WRITE_EVT:
      /* USER CODE BEGIN Service2Char10_WRITE_EVT */
			memset(lu8floatTemp_cups,0,sizeof(lu8floatTemp_cups));
			memcpy(lu8floatTemp_cups, p_Notification->DataTransfered.p_Payload,p_Notification->DataTransfered.Length);
      convert_byte_array_to_float(lu8floatTemp_cups, &lf32PidPVal);
			LOG_INFO_APP("CUPS_PID_P_VAL WRITE DATA = %s, LEN = %d\r\n", lu8floatTemp_cups, p_Notification->DataTransfered.Length);
			lf32PidPVal_notify_flag =1; 
      /* USER CODE END Service2Char10_WRITE_EVT */
      break;

    case CUPS_ER_BLE_CUPS_PID_I_VAL_RW_READ_EVT:
      /* USER CODE BEGIN Service2Char11_READ_EVT */
			LOG_INFO_APP("CUPS_PID_I_VAL READ\r\n");
			CUPS_ER_BLE_Cups_pid_i_val_rw_ReadUpdate();
      /* USER CODE END Service2Char11_READ_EVT */
      break;

    case CUPS_ER_BLE_CUPS_PID_I_VAL_RW_WRITE_EVT:
      /* USER CODE BEGIN Service2Char11_WRITE_EVT */
			memset(lu8floatTemp_cups,0,sizeof(lu8floatTemp_cups));
			memcpy(lu8floatTemp_cups, p_Notification->DataTransfered.p_Payload,p_Notification->DataTransfered.Length);
      convert_byte_array_to_float(lu8floatTemp_cups, &lf32PidIVal);
			LOG_INFO_APP("CUPS_PID_I_VAL WRITE DATA = %s, LEN = %d\r\n", lu8floatTemp_cups, p_Notification->DataTransfered.Length);
			lf32PidIVal_notify_flag =1; 
      /* USER CODE END Service2Char11_WRITE_EVT */
      break;

    case CUPS_ER_BLE_CUPS_PID_D_VAL_RW_READ_EVT:
      /* USER CODE BEGIN Service2Char12_READ_EVT */
			LOG_INFO_APP("CUPS_PID_D_VAL READ\r\n");
			CUPS_ER_BLE_Cups_pid_d_val_rw_ReadUpdate();
      /* USER CODE END Service2Char12_READ_EVT */
      break;

    case CUPS_ER_BLE_CUPS_PID_D_VAL_RW_WRITE_EVT:
      /* USER CODE BEGIN Service2Char12_WRITE_EVT */
			memset(lu8floatTemp_cups,0,sizeof(lu8floatTemp_cups));
			memcpy(lu8floatTemp_cups, p_Notification->DataTransfered.p_Payload,p_Notification->DataTransfered.Length);
      convert_byte_array_to_float(lu8floatTemp_cups, &lf32PidDVal);
			LOG_INFO_APP("CUPS_PID_D_VAL WRITE DATA = %s, LEN = %d\r\n", lu8floatTemp_cups, p_Notification->DataTransfered.Length);
			lf32PidDVal_notify_flag =1; 
      /* USER CODE END Service2Char12_WRITE_EVT */
      break;

    case CUPS_ER_BLE_CUPS_PID_I_TIME_RW_READ_EVT:
      /* USER CODE BEGIN Service2Char13_READ_EVT */
			LOG_INFO_APP("CUPS_PID_I_TIME_VAL READ\r\n");
			CUPS_ER_BLE_Cups_pid_i_time_rw_ReadUpdate();
      /* USER CODE END Service2Char13_READ_EVT */
      break;

    case CUPS_ER_BLE_CUPS_PID_I_TIME_RW_WRITE_EVT:
      /* USER CODE BEGIN Service2Char13_WRITE_EVT */
			memset(lu8floatTemp_cups,0,sizeof(lu8floatTemp_cups));
			memcpy(lu8floatTemp_cups, p_Notification->DataTransfered.p_Payload,p_Notification->DataTransfered.Length);
      convert_byte_array_to_float(lu8floatTemp_cups, &lf32PidITime);
			LOG_INFO_APP("CUPS_PID_I_TIME WRITE DATA = %s, LEN = %d\r\n", lu8floatTemp_cups, p_Notification->DataTransfered.Length);
			lf32PidITime_notify_flag =1; 
      /* USER CODE END Service2Char13_WRITE_EVT */
      break;

    case CUPS_ER_BLE_CUPS_P1_MIN_RANGE_RW_READ_EVT:
      /* USER CODE BEGIN Service2Char14_READ_EVT */
			LOG_INFO_APP("CUPS_P1_MIN_RANGE READ\r\n");
			CUPS_ER_BLE_Cups_p1_min_range_rw_ReadUpdate();
      /* USER CODE END Service2Char14_READ_EVT */
      break;

    case CUPS_ER_BLE_CUPS_P1_MIN_RANGE_RW_WRITE_EVT:
      /* USER CODE BEGIN Service2Char14_WRITE_EVT */
			memset(lu8floatTemp_cups,0,sizeof(lu8floatTemp_cups));
			memcpy(lu8floatTemp_cups, p_Notification->DataTransfered.p_Payload,p_Notification->DataTransfered.Length);
      convert_byte_array_to_float(lu8floatTemp_cups, &lf32P1MinRange);
			LOG_INFO_APP("CUPS_P1_MIN_RANGE WRITE DATA = %s, LEN = %d\r\n", lu8floatTemp_cups, p_Notification->DataTransfered.Length);
			lf32P1MinRange_notify_flag =1; 
      /* USER CODE END Service2Char14_WRITE_EVT */
      break;

    case CUPS_ER_BLE_CUPS_P1_MAX_RANGE_RW_READ_EVT:
      /* USER CODE BEGIN Service2Char15_READ_EVT */
			LOG_INFO_APP("CUPS_P1_MAX_RANGE READ\r\n");
			CUPS_ER_BLE_Cups_p1_max_range_rw_ReadUpdate();
      /* USER CODE END Service2Char15_READ_EVT */
      break;

    case CUPS_ER_BLE_CUPS_P1_MAX_RANGE_RW_WRITE_EVT:
      /* USER CODE BEGIN Service2Char15_WRITE_EVT */
			memset(lu8floatTemp_cups,0,sizeof(lu8floatTemp_cups));
			memcpy(lu8floatTemp_cups, p_Notification->DataTransfered.p_Payload,p_Notification->DataTransfered.Length);
      convert_byte_array_to_float(lu8floatTemp_cups, &lf32P1MaxRange);
			LOG_INFO_APP("CUPS_P1_MAX_RANGE WRITE DATA = %s, LEN = %d\r\n", lu8floatTemp_cups, p_Notification->DataTransfered.Length);
			lf32P1MaxRange_notify_flag =1; 
      /* USER CODE END Service2Char15_WRITE_EVT */
      break;

    case CUPS_ER_BLE_CUPS_VALVE_CONST_KV_RW_READ_EVT:
      /* USER CODE BEGIN Service2Char16_READ_EVT */
			LOG_INFO_APP("CUPS_VALVE_CONST_KV READ\r\n");
			CUPS_ER_BLE_Cups_valve_const_kv_rw_ReadUpdate();
      /* USER CODE END Service2Char16_READ_EVT */
      break;

    case CUPS_ER_BLE_CUPS_VALVE_CONST_KV_RW_WRITE_EVT:
      /* USER CODE BEGIN Service2Char16_WRITE_EVT */
			memset(lu8floatTemp_cups,0,sizeof(lu8floatTemp_cups));
			memcpy(lu8floatTemp_cups, p_Notification->DataTransfered.p_Payload,p_Notification->DataTransfered.Length);
      convert_byte_array_to_float(lu8floatTemp_cups, &lf32ValConstKV);
			LOG_INFO_APP("CUPS_VALVE_CONST_KV WRITE DATA = %s, LEN = %d\r\n", lu8floatTemp_cups, p_Notification->DataTransfered.Length);
			lf32ValConstKV_notify_flag =1; 
      /* USER CODE END Service2Char16_WRITE_EVT */
      break;

    case CUPS_ER_BLE_CUPS_FLOW_FACTOR_RW_READ_EVT:
      /* USER CODE BEGIN Service2Char17_READ_EVT */
			LOG_INFO_APP("CUPS_FLOW_FACTOR READ\r\n");
			CUPS_ER_BLE_Cups_flow_factor_rw_ReadUpdate();
      /* USER CODE END Service2Char17_READ_EVT */
      break;

    case CUPS_ER_BLE_CUPS_FLOW_FACTOR_RW_WRITE_EVT:
      /* USER CODE BEGIN Service2Char17_WRITE_EVT */
			memset(lu8floatTemp_cups,0,sizeof(lu8floatTemp_cups));
			memcpy(lu8floatTemp_cups, p_Notification->DataTransfered.p_Payload,p_Notification->DataTransfered.Length);
      convert_byte_array_to_float(lu8floatTemp_cups, &lf32FlowFactor);
			LOG_INFO_APP("CUPS_FLOW_FACTOR WRITE DATA = %s, LEN = %d\r\n", lu8floatTemp_cups, p_Notification->DataTransfered.Length);
			lf32FlowFactor_notify_flag =1; 
      /* USER CODE END Service2Char17_WRITE_EVT */
      break;

    case CUPS_ER_BLE_CUPS_PRESSURE_EN_DIS_READ_EVT:
      /* USER CODE BEGIN Service2Char18_READ_EVT */
			LOG_INFO_APP("CUPS_PRESSURE_EN_DIS READ\r\n");
			CUPS_ER_BLE_Cups_pressure_en_dis_rw_ReadUpdate();
      /* USER CODE END Service2Char18_READ_EVT */
      break;

    case CUPS_ER_BLE_CUPS_PRESSURE_EN_DIS_WRITE_EVT:
      /* USER CODE BEGIN Service2Char18_WRITE_EVT */
			lu16PressENDIS  = (p_Notification->DataTransfered.p_Payload[0]<<8)|
												(p_Notification->DataTransfered.p_Payload[1])	;
			LOG_INFO_APP("CUPS_FLOW_FACTOR WRITE DATA = %d, LEN = %d\r\n", lu8PressENDIS, p_Notification->DataTransfered.Length);
			lu16PressENDIS_notify_flag =1; 
      /* USER CODE END Service2Char18_WRITE_EVT */
      break;

    default:
      /* USER CODE BEGIN Service2_Notification_default */

      /* USER CODE END Service2_Notification_default */
      break;
  }
  /* USER CODE BEGIN Service2_Notification_2 */

  /* USER CODE END Service2_Notification_2 */
  return;
}

void CUPS_ER_BLE_APP_EvtRx(CUPS_ER_BLE_APP_ConnHandleNotEvt_t *p_Notification)
{
  /* USER CODE BEGIN Service2_APP_EvtRx_1 */

  /* USER CODE END Service2_APP_EvtRx_1 */

  switch(p_Notification->EvtOpcode)
  {
    /* USER CODE BEGIN Service2_APP_EvtRx_Service2_EvtOpcode */

    /* USER CODE END Service2_APP_EvtRx_Service2_EvtOpcode */
    case CUPS_ER_BLE_CONN_HANDLE_EVT :
      /* USER CODE BEGIN Service2_APP_CONN_HANDLE_EVT */

      /* USER CODE END Service2_APP_CONN_HANDLE_EVT */
      break;

    case CUPS_ER_BLE_DISCON_HANDLE_EVT :
      /* USER CODE BEGIN Service2_APP_DISCON_HANDLE_EVT */
			CUPS_ER_BLE_APP_Parameters_context_Init();
      /* USER CODE END Service2_APP_DISCON_HANDLE_EVT */
      break;

    default:
      /* USER CODE BEGIN Service2_APP_EvtRx_default */

      /* USER CODE END Service2_APP_EvtRx_default */
      break;
  }

  /* USER CODE BEGIN Service2_APP_EvtRx_2 */

  /* USER CODE END Service2_APP_EvtRx_2 */

  return;
}

void CUPS_ER_BLE_APP_Init(void)
{
  UNUSED(CUPS_ER_BLE_APP_Context);
  CUPS_ER_BLE_Init();

  /* USER CODE BEGIN Service2_APP_Init */
	UTIL_SEQ_RegTask( 1U << CFG_TASK_SEND_NOTIF_ID_CUPS_SETPOINT_P2_RW, UTIL_SEQ_RFU, CUPS_ER_BLE_Cups_setpoint_p2_rw_SendNotification);
  CUPS_ER_BLE_APP_Context.Cups_setpoint_p2_rw_Notification_Status= Cups_setpoint_p2_rw_NOTIFICATION_OFF;
  CUPS_ER_BLE_APP_Parameters_context_Init();
  /* USER CODE END Service2_APP_Init */
  return;
}

/* USER CODE BEGIN FD */

/* USER CODE END FD */

/*************************************************************
 *
 * LOCAL FUNCTIONS
 *
 *************************************************************/
__USED void CUPS_ER_BLE_Cups_setpoint_p2_rw_SendNotification(void) /* Property Notification */
{
  CUPS_ER_BLE_APP_SendInformation_t notification_on_off = Cups_setpoint_p2_rw_NOTIFICATION_OFF;
  CUPS_ER_BLE_Data_t cups_er_ble_notification_data;

  cups_er_ble_notification_data.p_Payload = (uint8_t*)a_CUPS_ER_BLE_UpdateCharData;
  cups_er_ble_notification_data.Length = 0;

  /* USER CODE BEGIN Service2Char8_NS_1 */
	memset(a_CUPS_ER_BLE_UpdateCharData,0,sizeof(a_CUPS_ER_BLE_UpdateCharData));
	convert_float_to_byte_array(lf32SetPointP2, lu8floatTemp_cups);
  strcpy((char*)a_CUPS_ER_BLE_UpdateCharData, (char*)lu8floatTemp_cups);
  LOG_INFO_APP("CUPS_SETPOINT_P2 NOTIFY DATA : %s\r\n", a_CUPS_ER_BLE_UpdateCharData);
  /* Update notification data length */
  cups_er_ble_notification_data.Length = (cups_er_ble_notification_data.Length) + 4;

  if(CUPS_ER_BLE_APP_Context.Cups_setpoint_p2_rw_Notification_Status == Cups_setpoint_p2_rw_NOTIFICATION_ON)
  {
    LOG_INFO_APP("INFORM CLIENT CUPS_SETPOINT_P2 Changed\r\n");
    notification_on_off = Cups_setpoint_p2_rw_NOTIFICATION_ON;
  }
  else
  {
    LOG_INFO_APP("CAN'T INFORM CLIENT CUPS_SETPOINT_P2- NOTIFICATION DISABLED\r\n");
  }
  /* USER CODE END Service2Char8_NS_1 */

  if (notification_on_off != Cups_setpoint_p2_rw_NOTIFICATION_OFF)
  {
    CUPS_ER_BLE_UpdateValue(CUPS_ER_BLE_CUPS_SETPOINT_P2_RW, &cups_er_ble_notification_data);
  }

  /* USER CODE BEGIN Service2Char8_NS_Last */

  /* USER CODE END Service2Char8_NS_Last */

  return;
}

/* USER CODE BEGIN FD_LOCAL_FUNCTIONS */
static void CUPS_ER_BLE_APP_Parameters_context_Init(void)
{
	return;
}

void CUPS_ER_BLE_Cups_unitp2t2_rw_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CUPS_ER_BLE_Data_t cups_er_ble_readresp_data;

  cups_er_ble_readresp_data.p_Payload = (uint8_t*)a_CUPS_ER_BLE_UpdateCharData;
  cups_er_ble_readresp_data.Length = 0;

  /* USER CODE BEGIN Service2Char1_NS_1 */
	a_CUPS_ER_BLE_UpdateCharData[0] = lu8UnitP2T2;
	LOG_INFO_APP("UNITP2T2 READRESP DATA : %02x\r\n",a_CUPS_ER_BLE_UpdateCharData[0]);
	/* Update readresp data length */
  cups_er_ble_readresp_data.Length = (cups_er_ble_readresp_data.Length) + 1;
	CUPS_ER_BLE_UpdateValue(CUPS_ER_BLE_CUPS_UNITP2T2_RW, &cups_er_ble_readresp_data);
  /* USER CODE END Service2Char1_NS_1 */
  return;
}

void CUPS_ER_BLE_Cups_pos_span_rw_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CUPS_ER_BLE_Data_t cups_er_ble_readresp_data;

  cups_er_ble_readresp_data.p_Payload = (uint8_t*)a_CUPS_ER_BLE_UpdateCharData;
  cups_er_ble_readresp_data.Length = 0;

  /* USER CODE BEGIN Service2Char2_NS_1 */
	a_CUPS_ER_BLE_UpdateCharData[0] = lu8PosSpan;
	LOG_INFO_APP("POS SPAN READRESP DATA : %02x\r\n",a_CUPS_ER_BLE_UpdateCharData[0]);
	/* Update readresp data length */
  cups_er_ble_readresp_data.Length = (cups_er_ble_readresp_data.Length) + 1;
	CUPS_ER_BLE_UpdateValue(CUPS_ER_BLE_CUPS_POS_SPAN_RW, &cups_er_ble_readresp_data);
  /* USER CODE END Service2Char2_NS_1 */
  return;
}


void CUPS_ER_BLE_Cups_valve_con_dir_rw_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CUPS_ER_BLE_Data_t cups_er_ble_readresp_data;

  cups_er_ble_readresp_data.p_Payload = (uint8_t*)a_CUPS_ER_BLE_UpdateCharData;
  cups_er_ble_readresp_data.Length = 0;

  /* USER CODE BEGIN Service2Char3_NS_1 */
	a_CUPS_ER_BLE_UpdateCharData[0] = lu8ValConDir;
	LOG_INFO_APP("VALVE CON DIR READRESP DATA : %02x\r\n",a_CUPS_ER_BLE_UpdateCharData[0]);
	/* Update readresp data length */
  cups_er_ble_readresp_data.Length = (cups_er_ble_readresp_data.Length) + 1;
	CUPS_ER_BLE_UpdateValue(CUPS_ER_BLE_CUPS_VALVE_CON_DIR_RW, &cups_er_ble_readresp_data);
  /* USER CODE END Service2Char3_NS_1 */
  return;
}


void CUPS_ER_BLE_Cups_sel_valve_friction_rw_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CUPS_ER_BLE_Data_t cups_er_ble_readresp_data;

  cups_er_ble_readresp_data.p_Payload = (uint8_t*)a_CUPS_ER_BLE_UpdateCharData;
  cups_er_ble_readresp_data.Length = 0;

  /* USER CODE BEGIN Service2Char4_NS_1 */
	a_CUPS_ER_BLE_UpdateCharData[0] = lu8SelValFri;
	LOG_INFO_APP("SEL VAL FRICTION READRESP DATA : %02x\r\n",a_CUPS_ER_BLE_UpdateCharData[0]);
	/* Update readresp data length */
  cups_er_ble_readresp_data.Length = (cups_er_ble_readresp_data.Length) + 1;
	CUPS_ER_BLE_UpdateValue(CUPS_ER_BLE_CUPS_SEL_VALVE_FRICTION_RW, &cups_er_ble_readresp_data);
  /* USER CODE END Service2Char4_NS_1 */
  return;
}

void CUPS_ER_BLE_Cups_sel_valve_char_suppo_rw_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CUPS_ER_BLE_Data_t cups_er_ble_readresp_data;

  cups_er_ble_readresp_data.p_Payload = (uint8_t*)a_CUPS_ER_BLE_UpdateCharData;
  cups_er_ble_readresp_data.Length = 0;

  /* USER CODE BEGIN Service2Char5_NS_1 */
	a_CUPS_ER_BLE_UpdateCharData[0] = lu8SelValCharSuppo;
	LOG_INFO_APP("SEL VALVE CHAR SUPPO READRESP DATA : %02x\r\n",a_CUPS_ER_BLE_UpdateCharData[0]);
	/* Update readresp data length */
  cups_er_ble_readresp_data.Length = (cups_er_ble_readresp_data.Length) + 1;
	CUPS_ER_BLE_UpdateValue(CUPS_ER_BLE_CUPS_SEL_VALVE_CHAR_SUPPO_RW, &cups_er_ble_readresp_data);
  /* USER CODE END Service2Char5_NS_1 */
  return;
}

void CUPS_ER_BLE_Cups_con_valve_pil_valve_rw_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CUPS_ER_BLE_Data_t cups_er_ble_readresp_data;

  cups_er_ble_readresp_data.p_Payload = (uint8_t*)a_CUPS_ER_BLE_UpdateCharData;
  cups_er_ble_readresp_data.Length = 0;

  /* USER CODE BEGIN Service2Char6_NS_1 */
	a_CUPS_ER_BLE_UpdateCharData[0] = lu8ConValvePilVal;
	LOG_INFO_APP("CONVALVE PIL VALVE READRESP DATA : %02x\r\n",a_CUPS_ER_BLE_UpdateCharData[0]);
	/* Update readresp data length */
  cups_er_ble_readresp_data.Length = (cups_er_ble_readresp_data.Length) + 1;
	CUPS_ER_BLE_UpdateValue(CUPS_ER_BLE_CUPS_CON_VALVE_PIL_VALVE_RW, &cups_er_ble_readresp_data);
  /* USER CODE END Service2Char6_NS_1 */
  return;
}

void CUPS_ER_BLE_Cups_unitp1t1_rw_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CUPS_ER_BLE_Data_t cups_er_ble_readresp_data;

  cups_er_ble_readresp_data.p_Payload = (uint8_t*)a_CUPS_ER_BLE_UpdateCharData;
  cups_er_ble_readresp_data.Length = 0;

  /* USER CODE BEGIN Service2Char7_NS_1 */
	a_CUPS_ER_BLE_UpdateCharData[0] = lu8UnitP1T1;
	LOG_INFO_APP("UNITP1T1 READRESP DATA : %02x\r\n",a_CUPS_ER_BLE_UpdateCharData[0]);
	/* Update readresp data length */
  cups_er_ble_readresp_data.Length = (cups_er_ble_readresp_data.Length) + 1;
	CUPS_ER_BLE_UpdateValue(CUPS_ER_BLE_CUPS_UNITP1T1_RW, &cups_er_ble_readresp_data);
  /* USER CODE END Service2Char7_NS_1 */
  return;
}


void CUPS_ER_BLE_Cups_setpoint_p2_rw_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CUPS_ER_BLE_Data_t cups_er_ble_readresp_data;

  cups_er_ble_readresp_data.p_Payload = (uint8_t*)a_CUPS_ER_BLE_UpdateCharData;
  cups_er_ble_readresp_data.Length = 0;

  /* USER CODE BEGIN Service2Char8_NS_1 */
	memset(a_CUPS_ER_BLE_UpdateCharData,0,sizeof(a_CUPS_ER_BLE_UpdateCharData));
	convert_float_to_byte_array(lf32SetPointP2, lu8floatTemp_cups);
  strcpy((char*)a_CUPS_ER_BLE_UpdateCharData, (char*)lu8floatTemp_cups);
  LOG_INFO_APP("SETPOINT P2 READRESP DATA : %s\r\n", a_CUPS_ER_BLE_UpdateCharData);
	/* Update readresp data length */
  cups_er_ble_readresp_data.Length = (cups_er_ble_readresp_data.Length) + 4;
	CUPS_ER_BLE_UpdateValue(CUPS_ER_BLE_CUPS_SETPOINT_P2_RW, &cups_er_ble_readresp_data);
  /* USER CODE END Service2Char8_NS_1 */
  return;
}

void CUPS_ER_BLE_Cups_time_const_rw_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CUPS_ER_BLE_Data_t cups_er_ble_readresp_data;

  cups_er_ble_readresp_data.p_Payload = (uint8_t*)a_CUPS_ER_BLE_UpdateCharData;
  cups_er_ble_readresp_data.Length = 0;

  /* USER CODE BEGIN Service2Char9_NS_1 */
	memset(a_CUPS_ER_BLE_UpdateCharData,0,sizeof(a_CUPS_ER_BLE_UpdateCharData));
	convert_float_to_byte_array(lf32TimeConst, lu8floatTemp_cups);
  strcpy((char*)a_CUPS_ER_BLE_UpdateCharData, (char*)lu8floatTemp_cups);
  LOG_INFO_APP("TIME CONST READRESP DATA : %s\r\n", a_CUPS_ER_BLE_UpdateCharData);
	/* Update readresp data length */
  cups_er_ble_readresp_data.Length = (cups_er_ble_readresp_data.Length) + 4;
	CUPS_ER_BLE_UpdateValue(CUPS_ER_BLE_CUPS_TIME_CONST_RW, &cups_er_ble_readresp_data);
  /* USER CODE END Service2Char9_NS_1 */
  return;
}

void CUPS_ER_BLE_Cups_pid_p_val_rw_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CUPS_ER_BLE_Data_t cups_er_ble_readresp_data;

  cups_er_ble_readresp_data.p_Payload = (uint8_t*)a_CUPS_ER_BLE_UpdateCharData;
  cups_er_ble_readresp_data.Length = 0;

  /* USER CODE BEGIN Service2Char10_NS_1 */
	memset(a_CUPS_ER_BLE_UpdateCharData,0,sizeof(a_CUPS_ER_BLE_UpdateCharData));
	convert_float_to_byte_array(lf32PidPVal, lu8floatTemp_cups);
  strcpy((char*)a_CUPS_ER_BLE_UpdateCharData, (char*)lu8floatTemp_cups);
  LOG_INFO_APP("PID P VAL READRESP DATA : %s\r\n", a_CUPS_ER_BLE_UpdateCharData);
	/* Update readresp data length */
  cups_er_ble_readresp_data.Length = (cups_er_ble_readresp_data.Length) + 4;
	CUPS_ER_BLE_UpdateValue(CUPS_ER_BLE_CUPS_PID_P_VAL_RW, &cups_er_ble_readresp_data);
  /* USER CODE END Service2Char10_NS_1 */
  return;
}

void CUPS_ER_BLE_Cups_pid_i_val_rw_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CUPS_ER_BLE_Data_t cups_er_ble_readresp_data;

  cups_er_ble_readresp_data.p_Payload = (uint8_t*)a_CUPS_ER_BLE_UpdateCharData;
  cups_er_ble_readresp_data.Length = 0;

  /* USER CODE BEGIN Service2Char11_NS_1 */
	memset(a_CUPS_ER_BLE_UpdateCharData,0,sizeof(a_CUPS_ER_BLE_UpdateCharData));
	convert_float_to_byte_array(lf32PidIVal, lu8floatTemp_cups);
  strcpy((char*)a_CUPS_ER_BLE_UpdateCharData, (char*)lu8floatTemp_cups);
  LOG_INFO_APP("PID I VAL READRESP DATA : %s\r\n", a_CUPS_ER_BLE_UpdateCharData);
	/* Update readresp data length */
  cups_er_ble_readresp_data.Length = (cups_er_ble_readresp_data.Length) + 4;
	CUPS_ER_BLE_UpdateValue(CUPS_ER_BLE_CUPS_PID_I_VAL_RW, &cups_er_ble_readresp_data);
  /* USER CODE END Service2Char11_NS_1 */
  return;
}

void CUPS_ER_BLE_Cups_pid_d_val_rw_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CUPS_ER_BLE_Data_t cups_er_ble_readresp_data;

  cups_er_ble_readresp_data.p_Payload = (uint8_t*)a_CUPS_ER_BLE_UpdateCharData;
  cups_er_ble_readresp_data.Length = 0;

  /* USER CODE BEGIN Service2Char12_NS_1 */
	memset(a_CUPS_ER_BLE_UpdateCharData,0,sizeof(a_CUPS_ER_BLE_UpdateCharData));
	convert_float_to_byte_array(lf32PidDVal, lu8floatTemp_cups);
  strcpy((char*)a_CUPS_ER_BLE_UpdateCharData, (char*)lu8floatTemp_cups);
  LOG_INFO_APP("PID D VAL READRESP DATA : %s\r\n", a_CUPS_ER_BLE_UpdateCharData);
	/* Update readresp data length */
  cups_er_ble_readresp_data.Length = (cups_er_ble_readresp_data.Length) + 4;
	CUPS_ER_BLE_UpdateValue(CUPS_ER_BLE_CUPS_PID_D_VAL_RW, &cups_er_ble_readresp_data);
  /* USER CODE END Service2Char12_NS_1 */
  return;
}


void CUPS_ER_BLE_Cups_pid_i_time_rw_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CUPS_ER_BLE_Data_t cups_er_ble_readresp_data;

  cups_er_ble_readresp_data.p_Payload = (uint8_t*)a_CUPS_ER_BLE_UpdateCharData;
  cups_er_ble_readresp_data.Length = 0;

  /* USER CODE BEGIN Service2Char13_NS_1 */
	memset(a_CUPS_ER_BLE_UpdateCharData,0,sizeof(a_CUPS_ER_BLE_UpdateCharData));
	convert_float_to_byte_array(lf32PidITime, lu8floatTemp_cups);
  strcpy((char*)a_CUPS_ER_BLE_UpdateCharData, (char*)lu8floatTemp_cups);
  LOG_INFO_APP("PID I TIME READRESP DATA : %s\r\n", a_CUPS_ER_BLE_UpdateCharData);
	/* Update readresp data length */
  cups_er_ble_readresp_data.Length = (cups_er_ble_readresp_data.Length) + 4;
	CUPS_ER_BLE_UpdateValue(CUPS_ER_BLE_CUPS_PID_I_TIME_RW, &cups_er_ble_readresp_data);
  /* USER CODE END Service2Char13_NS_1 */
  return;
}

void CUPS_ER_BLE_Cups_p1_min_range_rw_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CUPS_ER_BLE_Data_t cups_er_ble_readresp_data;

  cups_er_ble_readresp_data.p_Payload = (uint8_t*)a_CUPS_ER_BLE_UpdateCharData;
  cups_er_ble_readresp_data.Length = 0;

  /* USER CODE BEGIN Service2Char14_NS_1 */
	memset(a_CUPS_ER_BLE_UpdateCharData,0,sizeof(a_CUPS_ER_BLE_UpdateCharData));
	convert_float_to_byte_array(lf32P1MinRange, lu8floatTemp_cups);
  strcpy((char*)a_CUPS_ER_BLE_UpdateCharData, (char*)lu8floatTemp_cups);
  LOG_INFO_APP("P1 MIN RANGE READRESP DATA : %s\r\n", a_CUPS_ER_BLE_UpdateCharData);
	/* Update readresp data length */
  cups_er_ble_readresp_data.Length = (cups_er_ble_readresp_data.Length) + 4;
	CUPS_ER_BLE_UpdateValue(CUPS_ER_BLE_CUPS_P1_MIN_RANGE_RW, &cups_er_ble_readresp_data);
  /* USER CODE END Service2Char14_NS_1 */
  return;
}

void CUPS_ER_BLE_Cups_p1_max_range_rw_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CUPS_ER_BLE_Data_t cups_er_ble_readresp_data;

  cups_er_ble_readresp_data.p_Payload = (uint8_t*)a_CUPS_ER_BLE_UpdateCharData;
  cups_er_ble_readresp_data.Length = 0;

  /* USER CODE BEGIN Service2Char15_NS_1 */
	memset(a_CUPS_ER_BLE_UpdateCharData,0,sizeof(a_CUPS_ER_BLE_UpdateCharData));
	convert_float_to_byte_array(lf32P1MaxRange, lu8floatTemp_cups);
  strcpy((char*)a_CUPS_ER_BLE_UpdateCharData, (char*)lu8floatTemp_cups);
  LOG_INFO_APP("P1 MAX RANGE READRESP DATA : %s\r\n", a_CUPS_ER_BLE_UpdateCharData);
	/* Update readresp data length */
  cups_er_ble_readresp_data.Length = (cups_er_ble_readresp_data.Length) + 4;
	CUPS_ER_BLE_UpdateValue(CUPS_ER_BLE_CUPS_P1_MAX_RANGE_RW, &cups_er_ble_readresp_data);
  /* USER CODE END Service2Char15_NS_1 */
  return;
}

void CUPS_ER_BLE_Cups_valve_const_kv_rw_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CUPS_ER_BLE_Data_t cups_er_ble_readresp_data;

  cups_er_ble_readresp_data.p_Payload = (uint8_t*)a_CUPS_ER_BLE_UpdateCharData;
  cups_er_ble_readresp_data.Length = 0;

  /* USER CODE BEGIN Service2Char16_NS_1 */
	memset(a_CUPS_ER_BLE_UpdateCharData,0,sizeof(a_CUPS_ER_BLE_UpdateCharData));
	convert_float_to_byte_array(lf32ValConstKV, lu8floatTemp_cups);
  strcpy((char*)a_CUPS_ER_BLE_UpdateCharData, (char*)lu8floatTemp_cups);
  LOG_INFO_APP("VALVE CONST READRESP DATA : %s\r\n", a_CUPS_ER_BLE_UpdateCharData);
	/* Update readresp data length */
  cups_er_ble_readresp_data.Length = (cups_er_ble_readresp_data.Length) + 4;
	CUPS_ER_BLE_UpdateValue(CUPS_ER_BLE_CUPS_VALVE_CONST_KV_RW, &cups_er_ble_readresp_data);
  /* USER CODE END Service2Char16_NS_1 */
  return;
}

void CUPS_ER_BLE_Cups_flow_factor_rw_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CUPS_ER_BLE_Data_t cups_er_ble_readresp_data;

  cups_er_ble_readresp_data.p_Payload = (uint8_t*)a_CUPS_ER_BLE_UpdateCharData;
  cups_er_ble_readresp_data.Length = 0;

  /* USER CODE BEGIN Service2Char17_NS_1 */
	memset(a_CUPS_ER_BLE_UpdateCharData,0,sizeof(a_CUPS_ER_BLE_UpdateCharData));
	convert_float_to_byte_array(lf32FlowFactor, lu8floatTemp_cups);
  strcpy((char*)a_CUPS_ER_BLE_UpdateCharData, (char*)lu8floatTemp_cups);
  LOG_INFO_APP("FLOW FACTOR READRESP DATA : %s\r\n", a_CUPS_ER_BLE_UpdateCharData);
	/* Update readresp data length */
  cups_er_ble_readresp_data.Length = (cups_er_ble_readresp_data.Length) + 4;
	CUPS_ER_BLE_UpdateValue(CUPS_ER_BLE_CUPS_FLOW_FACTOR_RW, &cups_er_ble_readresp_data);
  /* USER CODE END Service2Char17_NS_1 */
  return;
}

void CUPS_ER_BLE_Cups_pressure_en_dis_rw_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CUPS_ER_BLE_Data_t cups_er_ble_readresp_data;

  cups_er_ble_readresp_data.p_Payload = (uint8_t*)a_CUPS_ER_BLE_UpdateCharData;
  cups_er_ble_readresp_data.Length = 0;

  /* USER CODE BEGIN Service2Char18_NS_1 */
	a_CUPS_ER_BLE_UpdateCharData[0] = (lu16PressENDIS & 0xff00)>>8;
	a_CUPS_ER_BLE_UpdateCharData[1] = (lu16PressENDIS & 0x00ff);
	LOG_INFO_APP("PRESSURE EN DIS READRESP DATA : 0x%02x%02x\r\n", 
							a_CUPS_ER_BLE_UpdateCharData[0],a_CUPS_ER_BLE_UpdateCharData[1]);
	/* Update readresp data length */
  cups_er_ble_readresp_data.Length = (cups_er_ble_readresp_data.Length) + 2;
	CUPS_ER_BLE_UpdateValue(CUPS_ER_BLE_CUPS_PRESSURE_EN_DIS, &cups_er_ble_readresp_data);
  /* USER CODE END Service2Char18_NS_1 */
  return;
}
/* USER CODE END FD_LOCAL_FUNCTIONS */
