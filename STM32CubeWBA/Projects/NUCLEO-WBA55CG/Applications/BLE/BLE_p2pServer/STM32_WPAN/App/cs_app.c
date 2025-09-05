/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    CS_app.c
  * @author  MCD Application Team
  * @brief   CS_app application definition.
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
#include "cs_app.h"
#include "cs.h"
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
  Cs_flowtemp_NOTIFICATION_OFF,
  Cs_flowtemp_NOTIFICATION_ON,
  Cs_p2t2_NOTIFICATION_OFF,
  Cs_p2t2_NOTIFICATION_ON,
  Cs_p1t1_NOTIFICATION_OFF,
  Cs_p1t1_NOTIFICATION_ON,
  Cs_unit_p2t2_NOTIFICATION_OFF,
  Cs_unit_p2t2_NOTIFICATION_ON,
  Cs_unit_p1t1_NOTIFICATION_OFF,
  Cs_unit_p1t1_NOTIFICATION_ON,
  Cs_mod_com_error_NOTIFICATION_OFF,
  Cs_mod_com_error_NOTIFICATION_ON,
  Cs_diag_error_NOTIFICATION_OFF,
  Cs_diag_error_NOTIFICATION_ON,
  Cs_diag_warn_NOTIFICATION_OFF,
  Cs_diag_warn_NOTIFICATION_ON,
  Cs_inlet_pres_pd1_NOTIFICATION_OFF,
  Cs_inlet_pres_pd1_NOTIFICATION_ON,
  Cs_outlet_pres_pd2_NOTIFICATION_OFF,
  Cs_outlet_pres_pd2_NOTIFICATION_ON,
  Cs_opening_per_NOTIFICATION_OFF,
  Cs_opening_per_NOTIFICATION_ON,
  Cs_operation_mode_NOTIFICATION_OFF,
  Cs_operation_mode_NOTIFICATION_ON,
  Cs_lvdt_amp_NOTIFICATION_OFF,
  Cs_lvdt_amp_NOTIFICATION_ON,
  Cs_totalizer_NOTIFICATION_OFF,
  Cs_totalizer_NOTIFICATION_ON,
  Cs_time_stamp_hhmm_NOTIFICATION_OFF,
  Cs_time_stamp_hhmm_NOTIFICATION_ON,
  Cs_time_stamp_ddmm_NOTIFICATION_OFF,
  Cs_time_stamp_ddmm_NOTIFICATION_ON,
  Cs_year_stamp_yyyy_NOTIFICATION_OFF,
  Cs_year_stamp_yyyy_NOTIFICATION_ON,
  Cs_totalizer_last_val_NOTIFICATION_OFF,
  Cs_totalizer_last_val_NOTIFICATION_ON,
  Cs_totalizer_unit_NOTIFICATION_OFF,
  Cs_totalizer_unit_NOTIFICATION_ON,
  /* USER CODE BEGIN Service5_APP_SendInformation_t */

  /* USER CODE END Service5_APP_SendInformation_t */
  CS_APP_SENDINFORMATION_LAST
} CS_APP_SendInformation_t;

typedef struct
{
  CS_APP_SendInformation_t     Cs_flowtemp_Notification_Status;
  CS_APP_SendInformation_t     Cs_p2t2_Notification_Status;
  CS_APP_SendInformation_t     Cs_p1t1_Notification_Status;
  CS_APP_SendInformation_t     Cs_unit_p2t2_Notification_Status;
  CS_APP_SendInformation_t     Cs_unit_p1t1_Notification_Status;
  CS_APP_SendInformation_t     Cs_mod_com_error_Notification_Status;
  CS_APP_SendInformation_t     Cs_diag_error_Notification_Status;
  CS_APP_SendInformation_t     Cs_diag_warn_Notification_Status;
  CS_APP_SendInformation_t     Cs_inlet_pres_pd1_Notification_Status;
  CS_APP_SendInformation_t     Cs_outlet_pres_pd2_Notification_Status;
  CS_APP_SendInformation_t     Cs_opening_per_Notification_Status;
  CS_APP_SendInformation_t     Cs_operation_mode_Notification_Status;
  CS_APP_SendInformation_t     Cs_lvdt_amp_Notification_Status;
  CS_APP_SendInformation_t     Cs_totalizer_Notification_Status;
  CS_APP_SendInformation_t     Cs_time_stamp_hhmm_Notification_Status;
  CS_APP_SendInformation_t     Cs_time_stamp_ddmm_Notification_Status;
  CS_APP_SendInformation_t     Cs_year_stamp_yyyy_Notification_Status;
  CS_APP_SendInformation_t     Cs_totalizer_last_val_Notification_Status;
  CS_APP_SendInformation_t     Cs_totalizer_unit_Notification_Status;
  /* USER CODE BEGIN Service5_APP_Context_t */

  /* USER CODE END Service5_APP_Context_t */
  uint16_t              ConnectionHandle;
} CS_APP_Context_t;

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
static CS_APP_Context_t CS_APP_Context;

uint8_t a_CS_UpdateCharData[247];

/* USER CODE BEGIN PV */
float gf32TempFlowTemp = 0;
float gf32TempP2T2 = 0;
float gf32TempP1T1 = 0;
uint8_t gu8TempUnitP2T2 = 0;
uint8_t gu8TempUnitP1T1 = 0;
uint16_t gu16TempModComErr = 0;
uint16_t gu16DiagErr = 0;
uint16_t gu16DiagWarn = 0;
float f32Inlet_air_pressure_PD1 = 0;
float f32Outlet_air_pressure_PD2 = 0;
float f32OpeningPercentage = 0;
uint8_t u8ModeOfOperation = 0;
uint16_t u16LVDT_Amplitude = 0;
unsigned long gu32total = 0;
uint8_t u8ResetTotalizerVal  = 0;
uint16_t gu16TimeHHMM = 0;
uint16_t gu16TimeDDMM = 0;
uint16_t gu16YearYYYY = 0;
unsigned long gu32LastTotal = 0;
uint8_t gu8TotalizerUnit = 0;
uint8_t lu8connection_status  = 0;

uint8_t lu8floatTemp_cs[4]  = {0};

uint8_t gf32TempFlowTemp_notify_flag = 0;
uint8_t gf32TempP2T2_notify_flag = 0;
uint8_t gf32TempP1T1_notify_flag = 0;
uint8_t gu8TempUnitP2T2_notify_flag = 0;
uint8_t gu8TempUnitP1T1_notify_flag = 0;
uint8_t gu16TempModComErr_notify_flag = 0;
uint8_t gu16DiagErr_notify_flag = 0;
uint8_t gu16DiagWarn_notify_flag = 0;
uint8_t f32Inlet_air_pressure_PD1_notify_flag = 0;
uint8_t f32Outlet_air_pressure_PD2_notify_flag = 0;
uint8_t f32OpeningPercentage_notify_flag = 0;
uint8_t u8ModeOfOperation_notify_flag = 0;
uint8_t u16LVDT_Amplitude_notify_flag = 0;
uint8_t gu32total_notify_flag = 0;
uint8_t u8ResetTotalizerVal_notify_flag  = 0;
uint8_t gu16TimeHHMM_notify_flag = 0;
uint8_t gu16TimeDDMM_notify_flag = 0;
uint8_t gu16YearYYYY_notify_flag = 0;
uint8_t gu32LastTotal_notify_flag = 0;
uint8_t gu8TotalizerUnit_notify_flag = 0;
uint8_t lu8connection_status_notify_flag  = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static void CS_Cs_flowtemp_SendNotification(void);
static void CS_Cs_p2t2_SendNotification(void);
static void CS_Cs_p1t1_SendNotification(void);
static void CS_Cs_unit_p2t2_SendNotification(void);
static void CS_Cs_unit_p1t1_SendNotification(void);
static void CS_Cs_mod_com_error_SendNotification(void);
static void CS_Cs_diag_error_SendNotification(void);
static void CS_Cs_diag_warn_SendNotification(void);
static void CS_Cs_inlet_pres_pd1_SendNotification(void);
static void CS_Cs_outlet_pres_pd2_SendNotification(void);
static void CS_Cs_opening_per_SendNotification(void);
static void CS_Cs_operation_mode_SendNotification(void);
static void CS_Cs_lvdt_amp_SendNotification(void);
static void CS_Cs_totalizer_SendNotification(void);
static void CS_Cs_time_stamp_hhmm_SendNotification(void);
static void CS_Cs_time_stamp_ddmm_SendNotification(void);
static void CS_Cs_year_stamp_yyyy_SendNotification(void);
static void CS_Cs_totalizer_last_val_SendNotification(void);
static void CS_Cs_totalizer_unit_SendNotification(void);

/* USER CODE BEGIN PFP */
static void CS_APP_Parameters_context_Init(void);
void CS_Cs_flowtemp_ReadUpdate(void);
void CS_Cs_p2t2_ReadUpdate(void);
void CS_Cs_p1t1_ReadUpdate(void);
void CS_Cs_unit_p2t2_ReadUpdate(void);
void CS_Cs_unit_p1t1_ReadUpdate(void);
void CS_Cs_mod_com_error_ReadUpdate(void);
void CS_Cs_diag_error_ReadUpdate(void);
void CS_Cs_diag_warn_ReadUpdate(void);
void CS_Cs_inlet_pres_pd1_ReadUpdate(void);
void CS_Cs_outlet_pres_pd2_ReadUpdate(void);
void CS_Cs_opening_per_ReadUpdate(void);
void CS_Cs_operation_mode_ReadUpdate(void);
void CS_Cs_lvdt_amp_ReadUpdate(void);
void CS_Cs_totalizer_ReadUpdate(void);
void CS_Cs_reset_button_ReadUpdate(void);
void CS_Cs_time_stamp_hhmm_ReadUpdate(void);
void CS_Cs_time_stamp_ddmm_ReadUpdate(void);
void CS_Cs_year_stamp_yyyy_ReadUpdate(void);
void CS_Cs_totalizer_last_val_ReadUpdate(void);
void CS_Cs_totalizer_unit_ReadUpdate(void);
void CS_Cs_connection_status_ReadUpdate(void);
/* USER CODE END PFP */

/* Functions Definition ------------------------------------------------------*/
void CS_Notification(CS_NotificationEvt_t *p_Notification)
{
  /* USER CODE BEGIN Service5_Notification_1 */

  /* USER CODE END Service5_Notification_1 */
  switch(p_Notification->EvtOpcode)
  {
    /* USER CODE BEGIN Service5_Notification_Service5_EvtOpcode */

    /* USER CODE END Service5_Notification_Service5_EvtOpcode */

    case CS_CS_FLOWTEMP_READ_EVT:
      /* USER CODE BEGIN Service5Char1_READ_EVT */
			LOG_INFO_APP("CS_FLOWTEMP READ \r\n");
			CS_Cs_flowtemp_ReadUpdate();
      /* USER CODE END Service5Char1_READ_EVT */
      break;

    case CS_CS_FLOWTEMP_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN Service5Char1_NOTIFY_ENABLED_EVT */
			CS_APP_Context.Cs_flowtemp_Notification_Status = Cs_flowtemp_NOTIFICATION_ON;
      LOG_INFO_APP("CS_FLOWTEMP NOTIFICATION ENABLED\r\n");    
      /* USER CODE END Service5Char1_NOTIFY_ENABLED_EVT */
      break;

    case CS_CS_FLOWTEMP_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN Service5Char1_NOTIFY_DISABLED_EVT */
			CS_APP_Context.Cs_flowtemp_Notification_Status = Cs_flowtemp_NOTIFICATION_OFF;
      LOG_INFO_APP("CS_FLOWTEMP NOTIFICATION DISABLED\r\n");    
      /* USER CODE END Service5Char1_NOTIFY_DISABLED_EVT */
      break;

    case CS_CS_P2T2_READ_EVT:
      /* USER CODE BEGIN Service5Char2_READ_EVT */
			LOG_INFO_APP("CS_P2T2 READ \r\n");
			CS_Cs_p2t2_ReadUpdate();
      /* USER CODE END Service5Char2_READ_EVT */
      break;

    case CS_CS_P2T2_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN Service5Char2_NOTIFY_ENABLED_EVT */
			CS_APP_Context.Cs_p2t2_Notification_Status = Cs_p2t2_NOTIFICATION_ON;
      LOG_INFO_APP("CS_P2T2 NOTIFICATION ENABLED\r\n");
      /* USER CODE END Service5Char2_NOTIFY_ENABLED_EVT */
      break;

    case CS_CS_P2T2_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN Service5Char2_NOTIFY_DISABLED_EVT */
			CS_APP_Context.Cs_p2t2_Notification_Status = Cs_p2t2_NOTIFICATION_OFF;
			LOG_INFO_APP("CS_P2T2 NOTIFICATION DISABLED\r\n");        
      /* USER CODE END Service5Char2_NOTIFY_DISABLED_EVT */
      break;

    case CS_CS_P1T1_READ_EVT:
      /* USER CODE BEGIN Service5Char3_READ_EVT */
			LOG_INFO_APP("CS_P1T1 READ \r\n");
			CS_Cs_p1t1_ReadUpdate();
      /* USER CODE END Service5Char3_READ_EVT */
      break;

    case CS_CS_P1T1_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN Service5Char3_NOTIFY_ENABLED_EVT */
			CS_APP_Context.Cs_p1t1_Notification_Status = Cs_p1t1_NOTIFICATION_ON;
      LOG_INFO_APP("CS_P1T1 NOTIFICATION ENABLED\r\n");
      /* USER CODE END Service5Char3_NOTIFY_ENABLED_EVT */
      break;

    case CS_CS_P1T1_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN Service5Char3_NOTIFY_DISABLED_EVT */
			CS_APP_Context.Cs_p1t1_Notification_Status = Cs_p1t1_NOTIFICATION_OFF;
			LOG_INFO_APP("CS_P1T1 NOTIFICATION DISABLED\r\n"); 
      /* USER CODE END Service5Char3_NOTIFY_DISABLED_EVT */
      break;

    case CS_CS_UNIT_P2T2_READ_EVT:
      /* USER CODE BEGIN Service5Char4_READ_EVT */
			LOG_INFO_APP("CS_UNIT_P2T2 READ \r\n");
			CS_Cs_unit_p2t2_ReadUpdate();
      /* USER CODE END Service5Char4_READ_EVT */
      break;

    case CS_CS_UNIT_P2T2_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN Service5Char4_NOTIFY_ENABLED_EVT */
			CS_APP_Context.Cs_unit_p2t2_Notification_Status = Cs_unit_p2t2_NOTIFICATION_ON;
			LOG_INFO_APP("CS_UNIT_P2T2 NOTIFICATION ENABLED\r\n"); 
      /* USER CODE END Service5Char4_NOTIFY_ENABLED_EVT */
      break;

    case CS_CS_UNIT_P2T2_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN Service5Char4_NOTIFY_DISABLED_EVT */
			CS_APP_Context.Cs_unit_p2t2_Notification_Status = Cs_unit_p2t2_NOTIFICATION_OFF;
			LOG_INFO_APP("CS_UNIT_P2T2 NOTIFICATION DISABLED\r\n"); 
      /* USER CODE END Service5Char4_NOTIFY_DISABLED_EVT */
      break;

    case CS_CS_UNIT_P1T1_READ_EVT:
      /* USER CODE BEGIN Service5Char5_READ_EVT */
			LOG_INFO_APP("CS_P1T1 READ \r\n");
			CS_Cs_unit_p1t1_ReadUpdate();
      /* USER CODE END Service5Char5_READ_EVT */
      break;

    case CS_CS_UNIT_P1T1_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN Service5Char5_NOTIFY_ENABLED_EVT */
			CS_APP_Context.Cs_unit_p1t1_Notification_Status = Cs_unit_p1t1_NOTIFICATION_ON;
			LOG_INFO_APP("CS_UNIT_P1T1 NOTIFICATION ENABLED\r\n"); 
      /* USER CODE END Service5Char5_NOTIFY_ENABLED_EVT */
      break;

    case CS_CS_UNIT_P1T1_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN Service5Char5_NOTIFY_DISABLED_EVT */
			CS_APP_Context.Cs_unit_p1t1_Notification_Status = Cs_unit_p1t1_NOTIFICATION_OFF;
			LOG_INFO_APP("CS_UNIT_P1T1 NOTIFICATION DISABLED\r\n"); 
      /* USER CODE END Service5Char5_NOTIFY_DISABLED_EVT */
      break;

    case CS_CS_MOD_COM_ERROR_READ_EVT:
      /* USER CODE BEGIN Service5Char6_READ_EVT */
			LOG_INFO_APP("CS_MOD_COM_ERROR READ \r\n");
			CS_Cs_mod_com_error_ReadUpdate();
      /* USER CODE END Service5Char6_READ_EVT */
      break;

    case CS_CS_MOD_COM_ERROR_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN Service5Char6_NOTIFY_ENABLED_EVT */
			CS_APP_Context.Cs_mod_com_error_Notification_Status = Cs_mod_com_error_NOTIFICATION_ON;
			LOG_INFO_APP("CS_MOD_COM_ERROR NOTIFICATION ENABLED\r\n");
      /* USER CODE END Service5Char6_NOTIFY_ENABLED_EVT */
      break;

    case CS_CS_MOD_COM_ERROR_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN Service5Char6_NOTIFY_DISABLED_EVT */
			CS_APP_Context.Cs_mod_com_error_Notification_Status = Cs_mod_com_error_NOTIFICATION_OFF;
			LOG_INFO_APP("CS_MOD_COM_ERROR NOTIFICATION DISABLED\r\n");
      /* USER CODE END Service5Char6_NOTIFY_DISABLED_EVT */
      break;

    case CS_CS_DIAG_ERROR_READ_EVT:
      /* USER CODE BEGIN Service5Char7_READ_EVT */
			LOG_INFO_APP("CS_DIAG_ERROR READ \r\n");
			CS_Cs_diag_error_ReadUpdate();
      /* USER CODE END Service5Char7_READ_EVT */
      break;

    case CS_CS_DIAG_ERROR_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN Service5Char7_NOTIFY_ENABLED_EVT */
			CS_APP_Context.Cs_diag_error_Notification_Status = Cs_diag_error_NOTIFICATION_ON;
			LOG_INFO_APP("CS_DIAG_ERRORR NOTIFICATION ENABLED\r\n");
      /* USER CODE END Service5Char7_NOTIFY_ENABLED_EVT */
      break;

    case CS_CS_DIAG_ERROR_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN Service5Char7_NOTIFY_DISABLED_EVT */
			CS_APP_Context.Cs_diag_error_Notification_Status = Cs_diag_error_NOTIFICATION_OFF;
			LOG_INFO_APP("CS_DIAG_ERRORR NOTIFICATION DISABLED\r\n");
      /* USER CODE END Service5Char7_NOTIFY_DISABLED_EVT */
      break;

    case CS_CS_DIAG_WARN_READ_EVT:
      /* USER CODE BEGIN Service5Char8_READ_EVT */
			LOG_INFO_APP("CS_DIAG_WARN READ \r\n");
			CS_Cs_diag_warn_ReadUpdate();
      /* USER CODE END Service5Char8_READ_EVT */
      break;

    case CS_CS_DIAG_WARN_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN Service5Char8_NOTIFY_ENABLED_EVT */
			CS_APP_Context.Cs_diag_warn_Notification_Status = Cs_diag_warn_NOTIFICATION_ON;
			LOG_INFO_APP("CS_DIAG_WARN NOTIFICATION ENABLED\r\n");
      /* USER CODE END Service5Char8_NOTIFY_ENABLED_EVT */
      break;

    case CS_CS_DIAG_WARN_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN Service5Char8_NOTIFY_DISABLED_EVT */
			CS_APP_Context.Cs_diag_warn_Notification_Status = Cs_diag_warn_NOTIFICATION_OFF;
			LOG_INFO_APP("CS_DIAG_WARN NOTIFICATION DISABLED\r\n");
      /* USER CODE END Service5Char8_NOTIFY_DISABLED_EVT */
      break;

    case CS_CS_INLET_PRES_PD1_READ_EVT:
      /* USER CODE BEGIN Service5Char9_READ_EVT */
			LOG_INFO_APP("CS_INLET_PRES_PD1 READ \r\n");
			CS_Cs_inlet_pres_pd1_ReadUpdate();
      /* USER CODE END Service5Char9_READ_EVT */
      break;

    case CS_CS_INLET_PRES_PD1_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN Service5Char9_NOTIFY_ENABLED_EVT */
			CS_APP_Context.Cs_inlet_pres_pd1_Notification_Status = Cs_inlet_pres_pd1_NOTIFICATION_ON;
			LOG_INFO_APP("CS_INLET_PRES_PD1 NOTIFICATION ENABLED\r\n");
      /* USER CODE END Service5Char9_NOTIFY_ENABLED_EVT */
      break;

    case CS_CS_INLET_PRES_PD1_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN Service5Char9_NOTIFY_DISABLED_EVT */
			CS_APP_Context.Cs_inlet_pres_pd1_Notification_Status = Cs_inlet_pres_pd1_NOTIFICATION_OFF;
			LOG_INFO_APP("CS_INLET_PRES_PD1 NOTIFICATION DISABLED\r\n");
      /* USER CODE END Service5Char9_NOTIFY_DISABLED_EVT */
      break;

    case CS_CS_OUTLET_PRES_PD2_READ_EVT:
      /* USER CODE BEGIN Service5Char10_READ_EVT */
			LOG_INFO_APP("CS_OUTLET_PRES_PD2 READ \r\n");
			CS_Cs_outlet_pres_pd2_ReadUpdate();
      /* USER CODE END Service5Char10_READ_EVT */
      break;

    case CS_CS_OUTLET_PRES_PD2_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN Service5Char10_NOTIFY_ENABLED_EVT */
			CS_APP_Context.Cs_outlet_pres_pd2_Notification_Status = Cs_outlet_pres_pd2_NOTIFICATION_ON;
			LOG_INFO_APP("CS_OUTLET_PRES_PD21 NOTIFICATION ENABLED\r\n");
      /* USER CODE END Service5Char10_NOTIFY_ENABLED_EVT */
      break;

    case CS_CS_OUTLET_PRES_PD2_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN Service5Char10_NOTIFY_DISABLED_EVT */
			CS_APP_Context.Cs_outlet_pres_pd2_Notification_Status = Cs_outlet_pres_pd2_NOTIFICATION_OFF;
			LOG_INFO_APP("CS_OUTLET_PRES_PD21 NOTIFICATION DISABLED\r\n");
      /* USER CODE END Service5Char10_NOTIFY_DISABLED_EVT */
      break;

    case CS_CS_OPENING_PER_READ_EVT:
      /* USER CODE BEGIN Service5Char11_READ_EVT */
			LOG_INFO_APP("CS_OPENING_PER READ \r\n");
			CS_Cs_opening_per_ReadUpdate();
      /* USER CODE END Service5Char11_READ_EVT */
      break;

    case CS_CS_OPENING_PER_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN Service5Char11_NOTIFY_ENABLED_EVT */
			CS_APP_Context.Cs_opening_per_Notification_Status = Cs_opening_per_NOTIFICATION_ON;
			LOG_INFO_APP("CS_OPENING_PER NOTIFICATION ENABLED\r\n");
      /* USER CODE END Service5Char11_NOTIFY_ENABLED_EVT */
      break;

    case CS_CS_OPENING_PER_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN Service5Char11_NOTIFY_DISABLED_EVT */
			CS_APP_Context.Cs_opening_per_Notification_Status = Cs_opening_per_NOTIFICATION_OFF;
			LOG_INFO_APP("CS_OPENING_PER NOTIFICATION DISABLED\r\n");
      /* USER CODE END Service5Char11_NOTIFY_DISABLED_EVT */
      break;

    case CS_CS_OPERATION_MODE_READ_EVT:
      /* USER CODE BEGIN Service5Char12_READ_EVT */
			LOG_INFO_APP("CS_OPERATION_MODE READ \r\n");
			CS_Cs_operation_mode_ReadUpdate();
      /* USER CODE END Service5Char12_READ_EVT */
      break;

    case CS_CS_OPERATION_MODE_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN Service5Char12_NOTIFY_ENABLED_EVT */
			CS_APP_Context.Cs_operation_mode_Notification_Status = Cs_opening_per_NOTIFICATION_ON;
			LOG_INFO_APP("CS_OPERATION_MOD NOTIFICATION ENABLED\r\n");
      /* USER CODE END Service5Char12_NOTIFY_ENABLED_EVT */
      break;

    case CS_CS_OPERATION_MODE_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN Service5Char12_NOTIFY_DISABLED_EVT */
			CS_APP_Context.Cs_operation_mode_Notification_Status = Cs_opening_per_NOTIFICATION_OFF;
			LOG_INFO_APP("CS_OPERATION_MOD NOTIFICATION DISABLED\r\n");
      /* USER CODE END Service5Char12_NOTIFY_DISABLED_EVT */
      break;

    case CS_CS_LVDT_AMP_READ_EVT:
      /* USER CODE BEGIN Service5Char13_READ_EVT */
			LOG_INFO_APP("CS_LVDT_AMP READ \r\n");
			CS_Cs_lvdt_amp_ReadUpdate();
      /* USER CODE END Service5Char13_READ_EVT */
      break;

    case CS_CS_LVDT_AMP_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN Service5Char13_NOTIFY_ENABLED_EVT */
			CS_APP_Context.Cs_lvdt_amp_Notification_Status = Cs_lvdt_amp_NOTIFICATION_ON;
			LOG_INFO_APP("CS_LVDT_AMP NOTIFICATION ENABLED\r\n");
      /* USER CODE END Service5Char13_NOTIFY_ENABLED_EVT */
      break;

    case CS_CS_LVDT_AMP_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN Service5Char13_NOTIFY_DISABLED_EVT */
			CS_APP_Context.Cs_lvdt_amp_Notification_Status = Cs_lvdt_amp_NOTIFICATION_OFF;
			LOG_INFO_APP("CS_LVDT_AMP NOTIFICATION DISABLED\r\n");
      /* USER CODE END Service5Char13_NOTIFY_DISABLED_EVT */
      break;

    case CS_CS_TOTALIZER_READ_EVT:
      /* USER CODE BEGIN Service5Char14_READ_EVT */
			LOG_INFO_APP("CS_TOTALIZER READ \r\n");
			CS_Cs_totalizer_ReadUpdate();
      /* USER CODE END Service5Char14_READ_EVT */
      break;

    case CS_CS_TOTALIZER_WRITE_EVT:
      /* USER CODE BEGIN Service5Char14_WRITE_EVT */
			gu32total  = (p_Notification->DataTransfered.p_Payload[0]<<24)|
												(p_Notification->DataTransfered.p_Payload[1]<<16)|
												(p_Notification->DataTransfered.p_Payload[2]<<8)|
												(p_Notification->DataTransfered.p_Payload[3])	;
			LOG_INFO_APP("CS_TOTALIZER WRITE DATA = %ld, LEN = %d\r\n", gu32total, p_Notification->DataTransfered.Length);
			gu32total_notify_flag =1; 
			CS_Cs_totalizer_SendNotification();
      /* USER CODE END Service5Char14_WRITE_EVT */
      break;

    case CS_CS_TOTALIZER_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN Service5Char14_NOTIFY_ENABLED_EVT */
			CS_APP_Context.Cs_totalizer_Notification_Status = Cs_totalizer_NOTIFICATION_ON;
			LOG_INFO_APP("CS_TOTALIZER NOTIFICATION ENABLED\r\n");
      /* USER CODE END Service5Char14_NOTIFY_ENABLED_EVT */
      break;

    case CS_CS_TOTALIZER_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN Service5Char14_NOTIFY_DISABLED_EVT */
			CS_APP_Context.Cs_totalizer_Notification_Status = Cs_totalizer_NOTIFICATION_OFF;
			LOG_INFO_APP("CS_TOTALIZER NOTIFICATION DISABLED\r\n");
      /* USER CODE END Service5Char14_NOTIFY_DISABLED_EVT */
      break;

    case CS_CS_RESET_BUTTON_READ_EVT:
      /* USER CODE BEGIN Service5Char15_READ_EVT */
			LOG_INFO_APP("CS_RESET_BUTTON READ \r\n");
			CS_Cs_reset_button_ReadUpdate();
      /* USER CODE END Service5Char15_READ_EVT */
      break;

    case CS_CS_RESET_BUTTON_WRITE_EVT:
      /* USER CODE BEGIN Service5Char15_WRITE_EVT */
			u8ResetTotalizerVal  = p_Notification->DataTransfered.p_Payload[0];
			LOG_INFO_APP("CS_RESET_BUTTON WRITE : 0x%02x\r\n",u8ResetTotalizerVal);	
			u8ResetTotalizerVal_notify_flag =1; 
      /* USER CODE END Service5Char15_WRITE_EVT */
      break;

    case CS_CS_TIME_STAMP_HHMM_READ_EVT:
      /* USER CODE BEGIN Service5Char16_READ_EVT */
			LOG_INFO_APP("CS_TIME_STAMP_HHMM READ \r\n");
			CS_Cs_time_stamp_hhmm_ReadUpdate();
      /* USER CODE END Service5Char16_READ_EVT */
      break;

    case CS_CS_TIME_STAMP_HHMM_WRITE_EVT:
      /* USER CODE BEGIN Service5Char16_WRITE_EVT */
			gu16TimeHHMM  = (p_Notification->DataTransfered.p_Payload[0]<<8)|
												(p_Notification->DataTransfered.p_Payload[1])	;
			LOG_INFO_APP("CS_TIME_STAMP_HHMM WRITE DATA = %d, LEN = %d\r\n", gu16TimeHHMM, p_Notification->DataTransfered.Length);
			gu16TimeHHMM_notify_flag =1; 
      /* USER CODE END Service5Char16_WRITE_EVT */
      break;

    case CS_CS_TIME_STAMP_HHMM_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN Service5Char16_NOTIFY_ENABLED_EVT */
			CS_APP_Context.Cs_time_stamp_hhmm_Notification_Status = Cs_time_stamp_hhmm_NOTIFICATION_ON;
			LOG_INFO_APP("CS_TIME_STAMP_HHMM NOTIFICATION ENABLED\r\n");
      /* USER CODE END Service5Char16_NOTIFY_ENABLED_EVT */
      break;

    case CS_CS_TIME_STAMP_HHMM_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN Service5Char16_NOTIFY_DISABLED_EVT */
			CS_APP_Context.Cs_time_stamp_hhmm_Notification_Status = Cs_time_stamp_hhmm_NOTIFICATION_OFF;
			LOG_INFO_APP("CS_TIME_STAMP_HHMM NOTIFICATION DISABLED\r\n");
      /* USER CODE END Service5Char16_NOTIFY_DISABLED_EVT */
      break;

    case CS_CS_TIME_STAMP_DDMM_READ_EVT:
      /* USER CODE BEGIN Service5Char17_READ_EVT */
			LOG_INFO_APP("CS_TIME_STAMP_DDMM READ \r\n");
			CS_Cs_time_stamp_ddmm_ReadUpdate();
      /* USER CODE END Service5Char17_READ_EVT */
      break;

    case CS_CS_TIME_STAMP_DDMM_WRITE_EVT:
      /* USER CODE BEGIN Service5Char17_WRITE_EVT */
			gu16TimeDDMM  = (p_Notification->DataTransfered.p_Payload[0]<<8)|
												(p_Notification->DataTransfered.p_Payload[1])	;
			LOG_INFO_APP("CS_TIME_STAMP_DDMM WRITE DATA = %d, LEN = %d\r\n", gu16TimeDDMM, p_Notification->DataTransfered.Length);
			gu16TimeDDMM_notify_flag =1; 
      /* USER CODE END Service5Char17_WRITE_EVT */
      break;

    case CS_CS_TIME_STAMP_DDMM_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN Service5Char17_NOTIFY_ENABLED_EVT */
			CS_APP_Context.Cs_time_stamp_ddmm_Notification_Status = Cs_time_stamp_ddmm_NOTIFICATION_ON;
			LOG_INFO_APP("CS_TIME_STAMP_DDMM NOTIFICATION ENABLED\r\n");
      /* USER CODE END Service5Char17_NOTIFY_ENABLED_EVT */
      break;

    case CS_CS_TIME_STAMP_DDMM_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN Service5Char17_NOTIFY_DISABLED_EVT */
			CS_APP_Context.Cs_time_stamp_ddmm_Notification_Status = Cs_time_stamp_ddmm_NOTIFICATION_OFF;
			LOG_INFO_APP("CS_TIME_STAMP_DDMM NOTIFICATION DISABLED\r\n");
      /* USER CODE END Service5Char17_NOTIFY_DISABLED_EVT */
      break;

    case CS_CS_YEAR_STAMP_YYYY_READ_EVT:
      /* USER CODE BEGIN Service5Char18_READ_EVT */
			LOG_INFO_APP("CS_YEAR_STAMP_YYYY READ \r\n");
			CS_Cs_year_stamp_yyyy_ReadUpdate();
      /* USER CODE END Service5Char18_READ_EVT */
      break;

    case CS_CS_YEAR_STAMP_YYYY_WRITE_EVT:
      /* USER CODE BEGIN Service5Char18_WRITE_EVT */
		  gu16YearYYYY  = (p_Notification->DataTransfered.p_Payload[0]<<8)|
												(p_Notification->DataTransfered.p_Payload[1])	;
			LOG_INFO_APP("CS_YEAR_STAMP_YYYY WRITE DATA = %d, LEN = %d\r\n", gu16YearYYYY, p_Notification->DataTransfered.Length);
			gu16YearYYYY_notify_flag =1; 
      /* USER CODE END Service5Char18_WRITE_EVT */
      break;

    case CS_CS_YEAR_STAMP_YYYY_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN Service5Char18_NOTIFY_ENABLED_EVT */
			CS_APP_Context.Cs_year_stamp_yyyy_Notification_Status = Cs_year_stamp_yyyy_NOTIFICATION_ON;
			LOG_INFO_APP("CS_YEAR_STAMP_YYYY NOTIFICATION ENABLED\r\n");
      /* USER CODE END Service5Char18_NOTIFY_ENABLED_EVT */
      break;

    case CS_CS_YEAR_STAMP_YYYY_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN Service5Char18_NOTIFY_DISABLED_EVT */
			CS_APP_Context.Cs_year_stamp_yyyy_Notification_Status = Cs_year_stamp_yyyy_NOTIFICATION_OFF;
			LOG_INFO_APP("CS_YEAR_STAMP_YYYY NOTIFICATION DISABLED\r\n");
      /* USER CODE END Service5Char18_NOTIFY_DISABLED_EVT */
      break;

    case CS_CS_TOTALIZER_LAST_VAL_READ_EVT:
      /* USER CODE BEGIN Service5Char19_READ_EVT */
			LOG_INFO_APP("CS_TOTALIZER_LAST_VAL READ \r\n");
			CS_Cs_totalizer_last_val_ReadUpdate();
      /* USER CODE END Service5Char19_READ_EVT */
      break;

    case CS_CS_TOTALIZER_LAST_VAL_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN Service5Char19_NOTIFY_ENABLED_EVT */
			CS_APP_Context.Cs_totalizer_last_val_Notification_Status = Cs_totalizer_last_val_NOTIFICATION_ON;
			LOG_INFO_APP("CS_TOTALIZER_LAST_VAL NOTIFICATION ENABLED\r\n");
      /* USER CODE END Service5Char19_NOTIFY_ENABLED_EVT */
      break;

    case CS_CS_TOTALIZER_LAST_VAL_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN Service5Char19_NOTIFY_DISABLED_EVT */
			CS_APP_Context.Cs_totalizer_last_val_Notification_Status = Cs_totalizer_last_val_NOTIFICATION_OFF;
			LOG_INFO_APP("CS_TOTALIZER_LAST_VAL NOTIFICATION DISABLED\r\n");
      /* USER CODE END Service5Char19_NOTIFY_DISABLED_EVT */
      break;

    case CS_CS_TOTALIZER_UNIT_READ_EVT:
      /* USER CODE BEGIN Service5Char20_READ_EVT */
			LOG_INFO_APP("CS_TOTALIZER_UNIT READ \r\n");
			CS_Cs_totalizer_unit_ReadUpdate();
      /* USER CODE END Service5Char20_READ_EVT */
      break;

    case CS_CS_TOTALIZER_UNIT_WRITE_EVT:
      /* USER CODE BEGIN Service5Char20_WRITE_EVT */
			gu8TotalizerUnit  = p_Notification->DataTransfered.p_Payload[0];
			LOG_INFO_APP("CS_CS_TOTALIZER_UNIT WRITE : 0x%02x\r\n",gu8TotalizerUnit);	
			gu8TotalizerUnit_notify_flag =1; 
      /* USER CODE END Service5Char20_WRITE_EVT */
      break;

    case CS_CS_TOTALIZER_UNIT_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN Service5Char20_NOTIFY_ENABLED_EVT */
			CS_APP_Context.Cs_totalizer_unit_Notification_Status = Cs_totalizer_unit_NOTIFICATION_ON;
			LOG_INFO_APP("CS_TOTALIZER_UNIT NOTIFICATION ENABLED\r\n");
      /* USER CODE END Service5Char20_NOTIFY_ENABLED_EVT */
      break;

    case CS_CS_TOTALIZER_UNIT_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN Service5Char20_NOTIFY_DISABLED_EVT */
			CS_APP_Context.Cs_totalizer_unit_Notification_Status = Cs_totalizer_unit_NOTIFICATION_OFF;
			LOG_INFO_APP("CS_TOTALIZER_UNIT NOTIFICATION ENABLED\r\n");
      /* USER CODE END Service5Char20_NOTIFY_DISABLED_EVT */
      break;

    case CS_CS_CONNECTION_STATUS_READ_EVT:
      /* USER CODE BEGIN Service5Char21_READ_EVT */
			LOG_INFO_APP("CONNECTION_STATUS READ \r\n");
			CS_Cs_connection_status_ReadUpdate();
      /* USER CODE END Service5Char21_READ_EVT */
      break;

    case CS_CS_CONNECTION_STATUS_WRITE_EVT:
      /* USER CODE BEGIN Service5Char21_WRITE_EVT */
			lu8connection_status  = p_Notification->DataTransfered.p_Payload[0];
			LOG_INFO_APP("CS_CS_CONNECTION_STATUS WRITE : 0x%02x\r\n",lu8connection_status);	
			lu8connection_status_notify_flag =1; 
      /* USER CODE END Service5Char21_WRITE_EVT */
      break;

    default:
      /* USER CODE BEGIN Service5_Notification_default */

      /* USER CODE END Service5_Notification_default */
      break;
  }
  /* USER CODE BEGIN Service5_Notification_2 */

  /* USER CODE END Service5_Notification_2 */
  return;
}

void CS_APP_EvtRx(CS_APP_ConnHandleNotEvt_t *p_Notification)
{
  /* USER CODE BEGIN Service5_APP_EvtRx_1 */

  /* USER CODE END Service5_APP_EvtRx_1 */

  switch(p_Notification->EvtOpcode)
  {
    /* USER CODE BEGIN Service5_APP_EvtRx_Service5_EvtOpcode */

    /* USER CODE END Service5_APP_EvtRx_Service5_EvtOpcode */
    case CS_CONN_HANDLE_EVT :
      /* USER CODE BEGIN Service5_APP_CONN_HANDLE_EVT */

      /* USER CODE END Service5_APP_CONN_HANDLE_EVT */
      break;

    case CS_DISCON_HANDLE_EVT :
      /* USER CODE BEGIN Service5_APP_DISCON_HANDLE_EVT */
			CS_APP_Parameters_context_Init();
      /* USER CODE END Service5_APP_DISCON_HANDLE_EVT */
      break;

    default:
      /* USER CODE BEGIN Service5_APP_EvtRx_default */

      /* USER CODE END Service5_APP_EvtRx_default */
      break;
  }

  /* USER CODE BEGIN Service5_APP_EvtRx_2 */

  /* USER CODE END Service5_APP_EvtRx_2 */

  return;
}

void CS_APP_Init(void)
{
  UNUSED(CS_APP_Context);
  CS_Init();

  /* USER CODE BEGIN Service5_APP_Init */
	UTIL_SEQ_RegTask( 1U << CFG_TASK_SEND_NOTIF_ID_CS_FLOWTEMP,UTIL_SEQ_RFU, CS_Cs_flowtemp_SendNotification);
  UTIL_SEQ_RegTask( 1U << CFG_TASK_SEND_NOTIF_ID_CS_P2T2,UTIL_SEQ_RFU, CS_Cs_p2t2_SendNotification);
  UTIL_SEQ_RegTask( 1U << CFG_TASK_SEND_NOTIF_ID_CS_P1T1,UTIL_SEQ_RFU, CS_Cs_p1t1_SendNotification);
  UTIL_SEQ_RegTask( 1U << CFG_TASK_SEND_NOTIF_ID_CS_UNIT_P2T2,UTIL_SEQ_RFU, CS_Cs_unit_p2t2_SendNotification);
  UTIL_SEQ_RegTask( 1U << CFG_TASK_SEND_NOTIF_ID_CS_UNIT_P1T1,UTIL_SEQ_RFU, CS_Cs_unit_p1t1_SendNotification);
  UTIL_SEQ_RegTask( 1U << CFG_TASK_SEND_NOTIF_ID_CS_MOD_COM_ERROR,UTIL_SEQ_RFU, CS_Cs_mod_com_error_SendNotification);
  UTIL_SEQ_RegTask( 1U << CFG_TASK_SEND_NOTIF_ID_CS_DIAG_ERROR,UTIL_SEQ_RFU, CS_Cs_diag_error_SendNotification);
  UTIL_SEQ_RegTask( 1U << CFG_TASK_SEND_NOTIF_ID_CS_DIAG_WARN,UTIL_SEQ_RFU, CS_Cs_diag_warn_SendNotification);
  UTIL_SEQ_RegTask( 1U << CFG_TASK_SEND_NOTIF_ID_CS_INLET_PRES_PD1,UTIL_SEQ_RFU, CS_Cs_inlet_pres_pd1_SendNotification);
  UTIL_SEQ_RegTask( 1U << CFG_TASK_SEND_NOTIF_ID_CS_OUTLET_PRES_PD2,UTIL_SEQ_RFU, CS_Cs_outlet_pres_pd2_SendNotification);
  UTIL_SEQ_RegTask( 1U << CFG_TASK_SEND_NOTIF_ID_CS_OPENING_PER,UTIL_SEQ_RFU, CS_Cs_opening_per_SendNotification);
  UTIL_SEQ_RegTask( 1U << CFG_TASK_SEND_NOTIF_ID_CS_OPERATION_MODE,UTIL_SEQ_RFU, CS_Cs_operation_mode_SendNotification);
  UTIL_SEQ_RegTask( 1U << CFG_TASK_SEND_NOTIF_ID_CS_LVDT_AMP,UTIL_SEQ_RFU, CS_Cs_lvdt_amp_SendNotification);
//  UTIL_SEQ_RegTask( 1U << CFG_TASK_SEND_NOTIF_ID_CS_TOTALIZER,UTIL_SEQ_RFU, CS_Cs_totalizer_SendNotification);
//  UTIL_SEQ_RegTask( 1U << CFG_TASK_SEND_NOTIF_ID_CS_TIME_STAMP_HHMM,UTIL_SEQ_RFU,CS_Cs_time_stamp_hhmm_SendNotification );
//	UTIL_SEQ_RegTask( 1U << CFG_TASK_SEND_NOTIF_ID_CS_TIME_STAMP_DDMM,UTIL_SEQ_RFU, CS_Cs_time_stamp_ddmm_SendNotification);
//	UTIL_SEQ_RegTask( 1U << CFG_TASK_SEND_NOTIF_ID_CS_YEAR_STAMP_YYYY,UTIL_SEQ_RFU, CS_Cs_year_stamp_yyyy_SendNotification);
//	UTIL_SEQ_RegTask( 1U << CFG_TASK_SEND_NOTIF_ID_CS_TOTALIZER_LAST_VAL,UTIL_SEQ_RFU, CS_Cs_totalizer_last_val_SendNotification);
//	UTIL_SEQ_RegTask( 1U << CFG_TASK_SEND_NOTIF_ID_CS_TOTALIZER_UNIT,UTIL_SEQ_RFU, CS_Cs_totalizer_unit_SendNotification);
	CS_APP_Context.Cs_flowtemp_Notification_Status = Cs_flowtemp_NOTIFICATION_OFF;
  CS_APP_Context.Cs_p2t2_Notification_Status = Cs_p2t2_NOTIFICATION_OFF;
  CS_APP_Context.Cs_p1t1_Notification_Status = Cs_p1t1_NOTIFICATION_OFF;
  CS_APP_Context.Cs_unit_p2t2_Notification_Status = Cs_unit_p2t2_NOTIFICATION_OFF;
  CS_APP_Context.Cs_unit_p1t1_Notification_Status = Cs_unit_p1t1_NOTIFICATION_OFF;
  CS_APP_Context.Cs_mod_com_error_Notification_Status = Cs_mod_com_error_NOTIFICATION_OFF;
  CS_APP_Context.Cs_diag_error_Notification_Status = Cs_diag_error_NOTIFICATION_OFF;
  CS_APP_Context.Cs_diag_warn_Notification_Status = Cs_diag_warn_NOTIFICATION_OFF;
  CS_APP_Context.Cs_inlet_pres_pd1_Notification_Status = Cs_inlet_pres_pd1_NOTIFICATION_OFF;
  CS_APP_Context.Cs_outlet_pres_pd2_Notification_Status = Cs_outlet_pres_pd2_NOTIFICATION_OFF;
  CS_APP_Context.Cs_opening_per_Notification_Status = Cs_opening_per_NOTIFICATION_OFF;
  CS_APP_Context.Cs_operation_mode_Notification_Status = Cs_operation_mode_NOTIFICATION_OFF;
  CS_APP_Context.Cs_lvdt_amp_Notification_Status = Cs_lvdt_amp_NOTIFICATION_OFF;
  CS_APP_Context.Cs_totalizer_Notification_Status = Cs_totalizer_NOTIFICATION_OFF;
  CS_APP_Context.Cs_time_stamp_hhmm_Notification_Status = Cs_time_stamp_hhmm_NOTIFICATION_OFF;
  CS_APP_Context.Cs_time_stamp_ddmm_Notification_Status = Cs_time_stamp_ddmm_NOTIFICATION_OFF;
  CS_APP_Context.Cs_year_stamp_yyyy_Notification_Status = Cs_year_stamp_yyyy_NOTIFICATION_OFF;  
  CS_APP_Context.Cs_totalizer_last_val_Notification_Status = Cs_totalizer_last_val_NOTIFICATION_OFF;
  CS_APP_Context.Cs_totalizer_unit_Notification_Status = Cs_totalizer_unit_NOTIFICATION_OFF;
	CS_APP_Parameters_context_Init();
  /* USER CODE END Service5_APP_Init */
  return;
}

/* USER CODE BEGIN FD */

/* USER CODE END FD */

/*************************************************************
 *
 * LOCAL FUNCTIONS
 *
 *************************************************************/
__USED void CS_Cs_flowtemp_SendNotification(void) /* Property Notification */
{
  CS_APP_SendInformation_t notification_on_off = Cs_flowtemp_NOTIFICATION_OFF;
  CS_Data_t cs_notification_data;

  cs_notification_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_notification_data.Length = 0;

  /* USER CODE BEGIN Service5Char1_NS_1 */
	memset(a_CS_UpdateCharData,0,sizeof(a_CS_UpdateCharData));
	convert_float_to_byte_array(gf32TempFlowTemp, lu8floatTemp_cs);
  strcpy((char*)a_CS_UpdateCharData, (char*)lu8floatTemp_cs);
  LOG_INFO_APP("CS_FLOWTEMP NOTIFY DATA : %s\r\n", a_CS_UpdateCharData);
  /* Update notification data length */
  cs_notification_data.Length = (cs_notification_data.Length) + 4;

  if(CS_APP_Context.Cs_flowtemp_Notification_Status == Cs_flowtemp_NOTIFICATION_ON)
  {
    LOG_INFO_APP("INFORM CLIENT CS_FLOWTEMP Changed\r\n");
    notification_on_off = Cs_flowtemp_NOTIFICATION_ON;
  }
  else
  {
    LOG_INFO_APP("CAN'T INFORM CLIENT CS_FLOWTEMP - NOTIFICATION DISABLED\r\n");
  }
  /* USER CODE END Service5Char1_NS_1 */

  if (notification_on_off != Cs_flowtemp_NOTIFICATION_OFF)
  {
    CS_UpdateValue(CS_CS_FLOWTEMP, &cs_notification_data);
  }

  /* USER CODE BEGIN Service5Char1_NS_Last */

  /* USER CODE END Service5Char1_NS_Last */

  return;
}

__USED void CS_Cs_p2t2_SendNotification(void) /* Property Notification */
{
  CS_APP_SendInformation_t notification_on_off = Cs_p2t2_NOTIFICATION_OFF;
  CS_Data_t cs_notification_data;

  cs_notification_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_notification_data.Length = 0;

  /* USER CODE BEGIN Service5Char2_NS_1 */
	memset(a_CS_UpdateCharData,0,sizeof(a_CS_UpdateCharData));
	convert_float_to_byte_array(gf32TempP2T2, lu8floatTemp_cs);
  strcpy((char*)a_CS_UpdateCharData, (char*)lu8floatTemp_cs);
  LOG_INFO_APP("CS_P2T2 NOTIFY DATA : %s\r\n", a_CS_UpdateCharData);
  /* Update notification data length */
  cs_notification_data.Length = (cs_notification_data.Length) + 4;

  if(CS_APP_Context.Cs_p2t2_Notification_Status == Cs_p2t2_NOTIFICATION_ON)
  {
    LOG_INFO_APP("INFORM CLIENT CS_P2T2 Changed\r\n");
    notification_on_off = Cs_p2t2_NOTIFICATION_ON;
  }
  else
  {
    LOG_INFO_APP("CAN'T INFORM CLIENT CS_P2T2 - NOTIFICATION DISABLED\r\n");
  }
  /* USER CODE END Service5Char2_NS_1 */

  if (notification_on_off != Cs_p2t2_NOTIFICATION_OFF)
  {
    CS_UpdateValue(CS_CS_P2T2, &cs_notification_data);
  }

  /* USER CODE BEGIN Service5Char2_NS_Last */

  /* USER CODE END Service5Char2_NS_Last */

  return;
}

__USED void CS_Cs_p1t1_SendNotification(void) /* Property Notification */
{
  CS_APP_SendInformation_t notification_on_off = Cs_p1t1_NOTIFICATION_OFF;
  CS_Data_t cs_notification_data;

  cs_notification_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_notification_data.Length = 0;

  /* USER CODE BEGIN Service5Char3_NS_1 */
	memset(a_CS_UpdateCharData,0,sizeof(a_CS_UpdateCharData));
	convert_float_to_byte_array(gf32TempP1T1, lu8floatTemp_cs);
  strcpy((char*)a_CS_UpdateCharData, (char*)lu8floatTemp_cs);
  LOG_INFO_APP("CS_P1T1 NOTIFY DATA : %s\r\n", a_CS_UpdateCharData);
  /* Update notification data length */
  cs_notification_data.Length = (cs_notification_data.Length) + 4;

  if(CS_APP_Context.Cs_p1t1_Notification_Status == Cs_p1t1_NOTIFICATION_ON)
  {
    LOG_INFO_APP("INFORM CLIENT CS_P1T1 Changed\r\n");
    notification_on_off = Cs_p1t1_NOTIFICATION_ON;
  }
  else
  {
    LOG_INFO_APP("CAN'T INFORM CLIENT CS_P1T1 - NOTIFICATION DISABLED\r\n");
  }
  /* USER CODE END Service5Char3_NS_1 */

  if (notification_on_off != Cs_p1t1_NOTIFICATION_OFF)
  {
    CS_UpdateValue(CS_CS_P1T1, &cs_notification_data);
  }

  /* USER CODE BEGIN Service5Char3_NS_Last */

  /* USER CODE END Service5Char3_NS_Last */

  return;
}

__USED void CS_Cs_unit_p2t2_SendNotification(void) /* Property Notification */
{
  CS_APP_SendInformation_t notification_on_off = Cs_unit_p2t2_NOTIFICATION_OFF;
  CS_Data_t cs_notification_data;

  cs_notification_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_notification_data.Length = 0;

  /* USER CODE BEGIN Service5Char4_NS_1 */
	a_CS_UpdateCharData[0] = gu8TempUnitP2T2;
	LOG_INFO_APP("CS_UNIT_P2T2 NOTIFY DATA : %02x\r\n",a_CS_UpdateCharData[0]);
	/* Update notification data length */
  cs_notification_data.Length = (cs_notification_data.Length) + 1;

  if(CS_APP_Context.Cs_unit_p2t2_Notification_Status == Cs_unit_p2t2_NOTIFICATION_ON)
  {
    LOG_INFO_APP("INFORM CLIENT CS_UNIT_P2T2 Changed\r\n");
    notification_on_off = Cs_unit_p2t2_NOTIFICATION_ON;
  }
  else
  {
    LOG_INFO_APP("CAN'T INFORM CLIENT CS_UNIT_P2T2 - NOTIFICATION DISABLED\r\n");
  }
  /* USER CODE END Service5Char4_NS_1 */

  if (notification_on_off != Cs_unit_p2t2_NOTIFICATION_OFF)
  {
    CS_UpdateValue(CS_CS_UNIT_P2T2, &cs_notification_data);
  }

  /* USER CODE BEGIN Service5Char4_NS_Last */

  /* USER CODE END Service5Char4_NS_Last */

  return;
}

__USED void CS_Cs_unit_p1t1_SendNotification(void) /* Property Notification */
{
  CS_APP_SendInformation_t notification_on_off = Cs_unit_p1t1_NOTIFICATION_OFF;
  CS_Data_t cs_notification_data;

  cs_notification_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_notification_data.Length = 0;

  /* USER CODE BEGIN Service5Char5_NS_1 */
	a_CS_UpdateCharData[0] = gu8TempUnitP1T1;
	LOG_INFO_APP("CS_UNIT_P1T1 NOTIFY DATA : %02x\r\n",a_CS_UpdateCharData[0]);
	/* Update notification data length */
  cs_notification_data.Length = (cs_notification_data.Length) + 1;

  if(CS_APP_Context.Cs_unit_p1t1_Notification_Status == Cs_unit_p1t1_NOTIFICATION_ON)
  {
    LOG_INFO_APP("INFORM CLIENT CS_UNIT_P1T1 Changed\r\n");
    notification_on_off = Cs_unit_p1t1_NOTIFICATION_ON;
  }
  else
  {
    LOG_INFO_APP("CAN'T INFORM CLIENT CS_UNIT_P1T1 - NOTIFICATION DISABLED\r\n");
  }
  /* USER CODE END Service5Char5_NS_1 */

  if (notification_on_off != Cs_unit_p1t1_NOTIFICATION_OFF)
  {
    CS_UpdateValue(CS_CS_UNIT_P1T1, &cs_notification_data);
  }

  /* USER CODE BEGIN Service5Char5_NS_Last */

  /* USER CODE END Service5Char5_NS_Last */

  return;
}

__USED void CS_Cs_mod_com_error_SendNotification(void) /* Property Notification */
{
  CS_APP_SendInformation_t notification_on_off = Cs_mod_com_error_NOTIFICATION_OFF;
  CS_Data_t cs_notification_data;

  cs_notification_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_notification_data.Length = 0;

  /* USER CODE BEGIN Service5Char6_NS_1 */
	a_CS_UpdateCharData[0] = (gu16TempModComErr & 0xff00)>>8;
	a_CS_UpdateCharData[1] = (gu16TempModComErr & 0x00ff);
	LOG_INFO_APP("CS_MOD_COM_ERROR NOTIFY DATA : 0x%02x%02x\r\n", 
							a_CS_UpdateCharData[0],a_CS_UpdateCharData[1]);
	/* Update notification data length */
  cs_notification_data.Length = (cs_notification_data.Length) + 2;
	
	if(CS_APP_Context.Cs_mod_com_error_Notification_Status == Cs_mod_com_error_NOTIFICATION_ON)
  {
    LOG_INFO_APP("INFORM CLIENT CS_MOD_COM_ERROR Changed\r\n");
    notification_on_off = Cs_mod_com_error_NOTIFICATION_ON;
  }
  else
  {
    LOG_INFO_APP("CAN'T INFORM CLIENT CS_MOD_COM_ERROR- NOTIFICATION DISABLED\r\n");
  }
  /* USER CODE END Service5Char6_NS_1 */

  if (notification_on_off != Cs_mod_com_error_NOTIFICATION_OFF)
  {
    CS_UpdateValue(CS_CS_MOD_COM_ERROR, &cs_notification_data);
  }

  /* USER CODE BEGIN Service5Char6_NS_Last */

  /* USER CODE END Service5Char6_NS_Last */

  return;
}

__USED void CS_Cs_diag_error_SendNotification(void) /* Property Notification */
{
  CS_APP_SendInformation_t notification_on_off = Cs_diag_error_NOTIFICATION_OFF;
  CS_Data_t cs_notification_data;

  cs_notification_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_notification_data.Length = 0;

  /* USER CODE BEGIN Service5Char7_NS_1 */
	a_CS_UpdateCharData[0] = (gu16DiagErr & 0xff00)>>8;
	a_CS_UpdateCharData[1] = (gu16DiagErr & 0x00ff);
	LOG_INFO_APP("CS_DIAG_ERROR NOTIFY DATA : 0x%02x%02x\r\n", 
							a_CS_UpdateCharData[0],a_CS_UpdateCharData[1]);
	/* Update notification data length */
  cs_notification_data.Length = (cs_notification_data.Length) + 2;
	
	if(CS_APP_Context.Cs_diag_error_Notification_Status == Cs_diag_error_NOTIFICATION_ON)
  {
    LOG_INFO_APP("INFORM CLIENT CS_DIAG_ERROR Changed\r\n");
    notification_on_off = Cs_diag_error_NOTIFICATION_ON;
  }
  else
  {
    LOG_INFO_APP("CAN'T INFORM CLIENT CS_DIAG_ERROR- NOTIFICATION DISABLED\r\n");
  }	
  /* USER CODE END Service5Char7_NS_1 */

  if (notification_on_off != Cs_diag_error_NOTIFICATION_OFF)
  {
    CS_UpdateValue(CS_CS_DIAG_ERROR, &cs_notification_data);
  }

  /* USER CODE BEGIN Service5Char7_NS_Last */

  /* USER CODE END Service5Char7_NS_Last */

  return;
}

__USED void CS_Cs_diag_warn_SendNotification(void) /* Property Notification */
{
  CS_APP_SendInformation_t notification_on_off = Cs_diag_warn_NOTIFICATION_OFF;
  CS_Data_t cs_notification_data;

  cs_notification_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_notification_data.Length = 0;

  /* USER CODE BEGIN Service5Char8_NS_1 */
	a_CS_UpdateCharData[0] = (gu16DiagWarn & 0xff00)>>8;
	a_CS_UpdateCharData[1] = (gu16DiagWarn & 0x00ff);
	LOG_INFO_APP("CS_DIAG_WARN NOTIFY DATA : 0x%02x%02x\r\n", 
							a_CS_UpdateCharData[0],a_CS_UpdateCharData[1]);
	/* Update notification data length */
  cs_notification_data.Length = (cs_notification_data.Length) + 2;
	
	if(CS_APP_Context.Cs_diag_warn_Notification_Status == Cs_diag_warn_NOTIFICATION_ON)
  {
    LOG_INFO_APP("INFORM CLIENT CS_DIAG_WARN Changed\r\n");
    notification_on_off = Cs_diag_warn_NOTIFICATION_ON;
  }
  else
  {
    LOG_INFO_APP("CAN'T INFORM CLIENT CS_DIAG_WARN- NOTIFICATION DISABLED\r\n");
  }	
  /* USER CODE END Service5Char8_NS_1 */

  if (notification_on_off != Cs_diag_warn_NOTIFICATION_OFF)
  {
    CS_UpdateValue(CS_CS_DIAG_WARN, &cs_notification_data);
  }

  /* USER CODE BEGIN Service5Char8_NS_Last */

  /* USER CODE END Service5Char8_NS_Last */

  return;
}

__USED void CS_Cs_inlet_pres_pd1_SendNotification(void) /* Property Notification */
{
  CS_APP_SendInformation_t notification_on_off = Cs_inlet_pres_pd1_NOTIFICATION_OFF;
  CS_Data_t cs_notification_data;

  cs_notification_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_notification_data.Length = 0;

  /* USER CODE BEGIN Service5Char9_NS_1 */
	memset(a_CS_UpdateCharData,0,sizeof(a_CS_UpdateCharData));
	convert_float_to_byte_array(f32Inlet_air_pressure_PD1, lu8floatTemp_cs);
  strcpy((char*)a_CS_UpdateCharData, (char*)lu8floatTemp_cs);
  LOG_INFO_APP("CS_INLET_PRES_PD1 NOTIFY DATA : %s\r\n", a_CS_UpdateCharData);
  /* Update notification data length */
  cs_notification_data.Length = (cs_notification_data.Length) + 4;

  if(CS_APP_Context.Cs_inlet_pres_pd1_Notification_Status == Cs_inlet_pres_pd1_NOTIFICATION_ON)
  {
    LOG_INFO_APP("INFORM CLIENT CS_INLET_PRES_PD1 Changed\r\n");
    notification_on_off = Cs_inlet_pres_pd1_NOTIFICATION_ON;
  }
  else
  {
    LOG_INFO_APP("CAN'T INFORM CLIENT CS_INLET_PRES_PD1 - NOTIFICATION DISABLED\r\n");
  }
  /* USER CODE END Service5Char9_NS_1 */

  if (notification_on_off != Cs_inlet_pres_pd1_NOTIFICATION_OFF)
  {
    CS_UpdateValue(CS_CS_INLET_PRES_PD1, &cs_notification_data);
  }

  /* USER CODE BEGIN Service5Char9_NS_Last */

  /* USER CODE END Service5Char9_NS_Last */

  return;
}

__USED void CS_Cs_outlet_pres_pd2_SendNotification(void) /* Property Notification */
{
  CS_APP_SendInformation_t notification_on_off = Cs_outlet_pres_pd2_NOTIFICATION_OFF;
  CS_Data_t cs_notification_data;

  cs_notification_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_notification_data.Length = 0;

  /* USER CODE BEGIN Service5Char10_NS_1 */
	memset(a_CS_UpdateCharData,0,sizeof(a_CS_UpdateCharData));
	convert_float_to_byte_array(f32Outlet_air_pressure_PD2, lu8floatTemp_cs);
  strcpy((char*)a_CS_UpdateCharData, (char*)lu8floatTemp_cs);
  LOG_INFO_APP("CS_OUTLET_PRES_PD2 NOTIFY DATA : %s\r\n", a_CS_UpdateCharData);
  /* Update notification data length */
  cs_notification_data.Length = (cs_notification_data.Length) + 4;

  if(CS_APP_Context.Cs_outlet_pres_pd2_Notification_Status == Cs_outlet_pres_pd2_NOTIFICATION_ON)
  {
    LOG_INFO_APP("INFORM CLIENT CS_OUTLET_PRES_PD2 Changed\r\n");
    notification_on_off = Cs_outlet_pres_pd2_NOTIFICATION_ON;
  }
  else
  {
    LOG_INFO_APP("CAN'T INFORM CLIENT CS_OUTLET_PRES_PD2 - NOTIFICATION DISABLED\r\n");
  }
  /* USER CODE END Service5Char10_NS_1 */

  if (notification_on_off != Cs_outlet_pres_pd2_NOTIFICATION_OFF)
  {
    CS_UpdateValue(CS_CS_OUTLET_PRES_PD2, &cs_notification_data);
  }

  /* USER CODE BEGIN Service5Char10_NS_Last */

  /* USER CODE END Service5Char10_NS_Last */

  return;
}

__USED void CS_Cs_opening_per_SendNotification(void) /* Property Notification */
{
  CS_APP_SendInformation_t notification_on_off = Cs_opening_per_NOTIFICATION_OFF;
  CS_Data_t cs_notification_data;

  cs_notification_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_notification_data.Length = 0;

  /* USER CODE BEGIN Service5Char11_NS_1 */
	memset(a_CS_UpdateCharData,0,sizeof(a_CS_UpdateCharData));
	convert_float_to_byte_array(f32OpeningPercentage, lu8floatTemp_cs);
  strcpy((char*)a_CS_UpdateCharData, (char*)lu8floatTemp_cs);
  LOG_INFO_APP("CS_OPENING_PER NOTIFY DATA : %s\r\n", a_CS_UpdateCharData);
  /* Update notification data length */
  cs_notification_data.Length = (cs_notification_data.Length) + 4;

  if(CS_APP_Context.Cs_opening_per_Notification_Status == Cs_opening_per_NOTIFICATION_ON)
  {
    LOG_INFO_APP("INFORM CLIENT CS_OPENING_PER Changed\r\n");
    notification_on_off = Cs_opening_per_NOTIFICATION_ON;
  }
  else
  {
    LOG_INFO_APP("CAN'T INFORM CLIENT CS_OPENING_PER - NOTIFICATION DISABLED\r\n");
  }
  /* USER CODE END Service5Char11_NS_1 */

  if (notification_on_off != Cs_opening_per_NOTIFICATION_OFF)
  {
    CS_UpdateValue(CS_CS_OPENING_PER, &cs_notification_data);
  }

  /* USER CODE BEGIN Service5Char11_NS_Last */

  /* USER CODE END Service5Char11_NS_Last */

  return;
}

__USED void CS_Cs_operation_mode_SendNotification(void) /* Property Notification */
{
  CS_APP_SendInformation_t notification_on_off = Cs_operation_mode_NOTIFICATION_OFF;
  CS_Data_t cs_notification_data;

  cs_notification_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_notification_data.Length = 0;

  /* USER CODE BEGIN Service5Char12_NS_1 */
	a_CS_UpdateCharData[0] = u8ModeOfOperation;
	LOG_INFO_APP("CS_OPERATION_MODE NOTIFY DATA : %02x\r\n",a_CS_UpdateCharData[0]);
	/* Update notification data length */
  cs_notification_data.Length = (cs_notification_data.Length) + 1;

  if(CS_APP_Context.Cs_operation_mode_Notification_Status == Cs_operation_mode_NOTIFICATION_ON)
  {
    LOG_INFO_APP("INFORM CLIENT CS_OPERATION_MODE Changed\r\n");
    notification_on_off = Cs_operation_mode_NOTIFICATION_ON;
  }
  else
  {
    LOG_INFO_APP("CAN'T INFORM CLIENT CS_OPERATION_MODE - NOTIFICATION DISABLED\r\n");
  }
  /* USER CODE END Service5Char12_NS_1 */

  if (notification_on_off != Cs_operation_mode_NOTIFICATION_OFF)
  {
    CS_UpdateValue(CS_CS_OPERATION_MODE, &cs_notification_data);
  }

  /* USER CODE BEGIN Service5Char12_NS_Last */

  /* USER CODE END Service5Char12_NS_Last */

  return;
}

__USED void CS_Cs_lvdt_amp_SendNotification(void) /* Property Notification */
{
  CS_APP_SendInformation_t notification_on_off = Cs_lvdt_amp_NOTIFICATION_OFF;
  CS_Data_t cs_notification_data;

  cs_notification_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_notification_data.Length = 0;

  /* USER CODE BEGIN Service5Char13_NS_1 */
	a_CS_UpdateCharData[0] = (u16LVDT_Amplitude & 0xff00)>>8;
	a_CS_UpdateCharData[1] = (u16LVDT_Amplitude & 0x00ff);
	LOG_INFO_APP("CS_LVDT_AMP NOTIFY DATA : 0x%02x%02x\r\n", 
							a_CS_UpdateCharData[0],a_CS_UpdateCharData[1]);
	/* Update notification data length */
  cs_notification_data.Length = (cs_notification_data.Length) + 2;
	
	if(CS_APP_Context.Cs_lvdt_amp_Notification_Status == Cs_lvdt_amp_NOTIFICATION_ON)
  {
    LOG_INFO_APP("INFORM CLIENT CS_LVDT_AMP Changed\r\n");
    notification_on_off = Cs_lvdt_amp_NOTIFICATION_ON;
  }
  else
  {
    LOG_INFO_APP("CAN'T INFORM CLIENT CS_LVDT_AMP - NOTIFICATION DISABLED\r\n");
  }	
  /* USER CODE END Service5Char13_NS_1 */

  if (notification_on_off != Cs_lvdt_amp_NOTIFICATION_OFF)
  {
    CS_UpdateValue(CS_CS_LVDT_AMP, &cs_notification_data);
  }

  /* USER CODE BEGIN Service5Char13_NS_Last */

  /* USER CODE END Service5Char13_NS_Last */

  return;
}

__USED void CS_Cs_totalizer_SendNotification(void) /* Property Notification */
{
  CS_APP_SendInformation_t notification_on_off = Cs_totalizer_NOTIFICATION_OFF;
  CS_Data_t cs_notification_data;

  cs_notification_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_notification_data.Length = 0;

  /* USER CODE BEGIN Service5Char14_NS_1 */
	a_CS_UpdateCharData[0] = (gu32total & 0xff000000)>>24;
	a_CS_UpdateCharData[1] = (gu32total & 0x00ff0000)>>16;
	a_CS_UpdateCharData[2] = (gu32total & 0x0000ff00)>>8;
	a_CS_UpdateCharData[3] = (gu32total & 0x000000ff);
	LOG_INFO_APP("CS_TOTALIZER NOTIFY DATA : 0x%02x%02x02x%02x\r\n", 
							a_CS_UpdateCharData[0],a_CS_UpdateCharData[1],
							a_CS_UpdateCharData[2],a_CS_UpdateCharData[3]
							);
	/* Update notification data length */
  cs_notification_data.Length = (cs_notification_data.Length) + 4;
	
	if(CS_APP_Context.Cs_totalizer_Notification_Status == Cs_totalizer_NOTIFICATION_ON)
  {
    LOG_INFO_APP("INFORM CLIENT CS_TOTALIZER Changed\r\n");
    notification_on_off = Cs_totalizer_NOTIFICATION_ON;
  }
  else
  {
    LOG_INFO_APP("CAN'T INFORM CLIENT CS_TOTALIZER - NOTIFICATION DISABLED\r\n");
  }
  /* USER CODE END Service5Char14_NS_1 */

  if (notification_on_off != Cs_totalizer_NOTIFICATION_OFF)
  {
    CS_UpdateValue(CS_CS_TOTALIZER, &cs_notification_data);
  }

  /* USER CODE BEGIN Service5Char14_NS_Last */

  /* USER CODE END Service5Char14_NS_Last */

  return;
}

__USED void CS_Cs_time_stamp_hhmm_SendNotification(void) /* Property Notification */
{
  CS_APP_SendInformation_t notification_on_off = Cs_time_stamp_hhmm_NOTIFICATION_OFF;
  CS_Data_t cs_notification_data;

  cs_notification_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_notification_data.Length = 0;

  /* USER CODE BEGIN Service5Char16_NS_1 */
	a_CS_UpdateCharData[0] = (gu16TimeHHMM & 0xff00)>>8;
	a_CS_UpdateCharData[1] = (gu16TimeHHMM & 0x00ff);
	LOG_INFO_APP("CS_TIME_STAMP_HHMM NOTIFY DATA : 0x%02x%02x\r\n", 
							a_CS_UpdateCharData[0],a_CS_UpdateCharData[1]);
	/* Update notification data length */
  cs_notification_data.Length = (cs_notification_data.Length) + 2;
	
	if(CS_APP_Context.Cs_time_stamp_hhmm_Notification_Status == Cs_time_stamp_hhmm_NOTIFICATION_ON)
  {
    LOG_INFO_APP("INFORM CLIENT CS_TIME_STAMP_HHMM Changed\r\n");
    notification_on_off = Cs_time_stamp_hhmm_NOTIFICATION_ON;
  }
  else
  {
    LOG_INFO_APP("CAN'T INFORM CLIENT CS_TIME_STAMP_HHMM - NOTIFICATION DISABLED\r\n");
  }	
  /* USER CODE END Service5Char16_NS_1 */

  if (notification_on_off != Cs_time_stamp_hhmm_NOTIFICATION_OFF)
  {
    CS_UpdateValue(CS_CS_TIME_STAMP_HHMM, &cs_notification_data);
  }

  /* USER CODE BEGIN Service5Char16_NS_Last */

  /* USER CODE END Service5Char16_NS_Last */

  return;
}

__USED void CS_Cs_time_stamp_ddmm_SendNotification(void) /* Property Notification */
{
  CS_APP_SendInformation_t notification_on_off = Cs_time_stamp_ddmm_NOTIFICATION_OFF;
  CS_Data_t cs_notification_data;

  cs_notification_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_notification_data.Length = 0;

  /* USER CODE BEGIN Service5Char17_NS_1 */
	a_CS_UpdateCharData[0] = (gu16TimeDDMM & 0xff00)>>8;
	a_CS_UpdateCharData[1] = (gu16TimeDDMM & 0x00ff);
	LOG_INFO_APP("CS_TIME_STAMP_DDMM NOTIFY DATA : 0x%02x%02x\r\n", 
							a_CS_UpdateCharData[0],a_CS_UpdateCharData[1]);
	/* Update notification data length */
  cs_notification_data.Length = (cs_notification_data.Length) + 2;
	
	if(CS_APP_Context.Cs_time_stamp_ddmm_Notification_Status == Cs_time_stamp_ddmm_NOTIFICATION_ON)
  {
    LOG_INFO_APP("INFORM CLIENT CS_TIME_STAMP_DDMM Changed\r\n");
    notification_on_off = Cs_time_stamp_ddmm_NOTIFICATION_ON;
  }
  else
  {
    LOG_INFO_APP("CAN'T INFORM CLIENT CS_TIME_STAMP_DDMM - NOTIFICATION DISABLED\r\n");
  }	
  /* USER CODE END Service5Char17_NS_1 */

  if (notification_on_off != Cs_time_stamp_ddmm_NOTIFICATION_OFF)
  {
    CS_UpdateValue(CS_CS_TIME_STAMP_DDMM, &cs_notification_data);
  }

  /* USER CODE BEGIN Service5Char17_NS_Last */

  /* USER CODE END Service5Char17_NS_Last */

  return;
}

__USED void CS_Cs_year_stamp_yyyy_SendNotification(void) /* Property Notification */
{
  CS_APP_SendInformation_t notification_on_off = Cs_year_stamp_yyyy_NOTIFICATION_OFF;
  CS_Data_t cs_notification_data;

  cs_notification_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_notification_data.Length = 0;

  /* USER CODE BEGIN Service5Char18_NS_1 */
	a_CS_UpdateCharData[0] = (gu16YearYYYY & 0xff00)>>8;
	a_CS_UpdateCharData[1] = (gu16YearYYYY & 0x00ff);
	LOG_INFO_APP("CS_YEAR_STAMP_YYYY NOTIFY DATA : 0x%02x%02x\r\n", 
							a_CS_UpdateCharData[0],a_CS_UpdateCharData[1]);
	/* Update notification data length */
  cs_notification_data.Length = (cs_notification_data.Length) + 2;
	
	if(CS_APP_Context.Cs_year_stamp_yyyy_Notification_Status == Cs_year_stamp_yyyy_NOTIFICATION_ON)
  {
    LOG_INFO_APP("INFORM CLIENT CS_YEAR_STAMP_YYYY Changed\r\n");
    notification_on_off = Cs_year_stamp_yyyy_NOTIFICATION_ON;
  }
  else
  {
    LOG_INFO_APP("CAN'T INFORM CLIENT CS_YEAR_STAMP_YYYY - NOTIFICATION DISABLED\r\n");
  }
  /* USER CODE END Service5Char18_NS_1 */

  if (notification_on_off != Cs_year_stamp_yyyy_NOTIFICATION_OFF)
  {
    CS_UpdateValue(CS_CS_YEAR_STAMP_YYYY, &cs_notification_data);
  }

  /* USER CODE BEGIN Service5Char18_NS_Last */

  /* USER CODE END Service5Char18_NS_Last */

  return;
}

__USED void CS_Cs_totalizer_last_val_SendNotification(void) /* Property Notification */
{
  CS_APP_SendInformation_t notification_on_off = Cs_totalizer_last_val_NOTIFICATION_OFF;
  CS_Data_t cs_notification_data;

  cs_notification_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_notification_data.Length = 0;

  /* USER CODE BEGIN Service5Char19_NS_1 */
	a_CS_UpdateCharData[0] = (gu32LastTotal & 0xff000000)>>24;
	a_CS_UpdateCharData[1] = (gu32LastTotal & 0x00ff0000)>>16;
	a_CS_UpdateCharData[2] = (gu32LastTotal & 0x0000ff00)>>8;
	a_CS_UpdateCharData[3] = (gu32LastTotal & 0x000000ff);
	LOG_INFO_APP("CS_TOTALIZER_LAST_VAL NOTIFY DATA : 0x%02x%02x02x%02x\r\n", 
							a_CS_UpdateCharData[0],a_CS_UpdateCharData[1],
							a_CS_UpdateCharData[2],a_CS_UpdateCharData[3]
							);
	/* Update notification data length */
  cs_notification_data.Length = (cs_notification_data.Length) + 4;
	
	if(CS_APP_Context.Cs_totalizer_last_val_Notification_Status == Cs_totalizer_last_val_NOTIFICATION_ON)
  {
    LOG_INFO_APP("INFORM CLIENT CS_TOTALIZER_LAST_VAL Changed\r\n");
    notification_on_off = Cs_totalizer_last_val_NOTIFICATION_ON;
  }
  else
  {
    LOG_INFO_APP("CAN'T INFORM CLIENT CS_TOTALIZER_LAST_VAL - NOTIFICATION DISABLED\r\n");
  }
  /* USER CODE END Service5Char19_NS_1 */

  if (notification_on_off != Cs_totalizer_last_val_NOTIFICATION_OFF)
  {
    CS_UpdateValue(CS_CS_TOTALIZER_LAST_VAL, &cs_notification_data);
  }

  /* USER CODE BEGIN Service5Char19_NS_Last */

  /* USER CODE END Service5Char19_NS_Last */

  return;
}

__USED void CS_Cs_totalizer_unit_SendNotification(void) /* Property Notification */
{
  CS_APP_SendInformation_t notification_on_off = Cs_totalizer_unit_NOTIFICATION_OFF;
  CS_Data_t cs_notification_data;

  cs_notification_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_notification_data.Length = 0;

  /* USER CODE BEGIN Service5Char20_NS_1 */
	a_CS_UpdateCharData[0] = gu8TotalizerUnit;
	LOG_INFO_APP("CS_TOTALIZER_UNIT NOTIFY DATA : %02x\r\n",a_CS_UpdateCharData[0]);
	/* Update notification data length */
  cs_notification_data.Length = (cs_notification_data.Length) + 1;

  if(CS_APP_Context.Cs_totalizer_unit_Notification_Status == Cs_totalizer_unit_NOTIFICATION_ON)
  {
    LOG_INFO_APP("INFORM CLIENT CS_TOTALIZER_UNIT Changed\r\n");
    notification_on_off = Cs_totalizer_unit_NOTIFICATION_ON;
  }
  else
  {
    LOG_INFO_APP("CAN'T INFORM CLIENT CS_TOTALIZER_UNIT - NOTIFICATION DISABLED\r\n");
  }
  /* USER CODE END Service5Char20_NS_1 */

  if (notification_on_off != Cs_totalizer_unit_NOTIFICATION_OFF)
  {
    CS_UpdateValue(CS_CS_TOTALIZER_UNIT, &cs_notification_data);
  }

  /* USER CODE BEGIN Service5Char20_NS_Last */

  /* USER CODE END Service5Char20_NS_Last */

  return;
}

/* USER CODE BEGIN FD_LOCAL_FUNCTIONS */
static void CS_APP_Parameters_context_Init(void)
{
	return;
}

void CS_Cs_flowtemp_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CS_Data_t cs_readresp_data;

  cs_readresp_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_readresp_data.Length = 0;

  /* USER CODE BEGIN Service5Char1_NS_1 */
	memset(a_CS_UpdateCharData,0,sizeof(a_CS_UpdateCharData));
	convert_float_to_byte_array(gf32TempFlowTemp, lu8floatTemp_cs);
  strcpy((char*)a_CS_UpdateCharData, (char*)lu8floatTemp_cs);
  LOG_INFO_APP("CS_FLOWTEMP READRESP DATA : %s\r\n", a_CS_UpdateCharData);
  /* Update readresp data length */
  cs_readresp_data.Length = (cs_readresp_data.Length) + 4;
	CS_UpdateValue(CS_CS_FLOWTEMP, &cs_readresp_data);
	/* USER CODE END Service5Char1_NS_1 */
  return;
}

void CS_Cs_p2t2_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CS_Data_t cs_readresp_data;

  cs_readresp_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_readresp_data.Length = 0;

  /* USER CODE BEGIN Service5Char2_NS_1 */
	memset(a_CS_UpdateCharData,0,sizeof(a_CS_UpdateCharData));
	convert_float_to_byte_array(gf32TempP2T2, lu8floatTemp_cs);
  strcpy((char*)a_CS_UpdateCharData, (char*)lu8floatTemp_cs);
  LOG_INFO_APP("CS_P2T2 READRESP DATA : %s\r\n", a_CS_UpdateCharData);
  /* Update readresp data length */
  cs_readresp_data.Length = (cs_readresp_data.Length) + 4;
  CS_UpdateValue(CS_CS_P2T2, &cs_readresp_data);
	/* USER CODE END Service5Char2_NS_1 */
  return;
}

void CS_Cs_p1t1_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CS_Data_t cs_readresp_data;

  cs_readresp_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_readresp_data.Length = 0;

  /* USER CODE BEGIN Service5Char3_NS_1 */
	memset(a_CS_UpdateCharData,0,sizeof(a_CS_UpdateCharData));
	convert_float_to_byte_array(gf32TempP1T1, lu8floatTemp_cs);
  strcpy((char*)a_CS_UpdateCharData, (char*)lu8floatTemp_cs);
  LOG_INFO_APP("CS_P1T1 READRESP DATA : %s\r\n", a_CS_UpdateCharData);
  /* Update readresp data length */
  cs_readresp_data.Length = (cs_readresp_data.Length) + 4;
  CS_UpdateValue(CS_CS_P1T1, &cs_readresp_data);
	/* USER CODE END Service5Char3_NS_1 */
  return;
}

void CS_Cs_unit_p2t2_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CS_Data_t cs_readresp_data;

  cs_readresp_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_readresp_data.Length = 0;

  /* USER CODE BEGIN Service5Char4_NS_1 */
	a_CS_UpdateCharData[0] = gu8TempUnitP2T2;
	LOG_INFO_APP("CS_UNIT_P2T2 READRESP DATA : %02x\r\n",a_CS_UpdateCharData[0]);
	/* Update readresp data length */
  cs_readresp_data.Length = (cs_readresp_data.Length) + 1;
	CS_UpdateValue(CS_CS_UNIT_P2T2, &cs_readresp_data);
	/* USER CODE END Service5Char4_NS_1 */
  return;
}

void CS_Cs_unit_p1t1_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CS_Data_t cs_readresp_data;

  cs_readresp_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_readresp_data.Length = 0;

  /* USER CODE BEGIN Service5Char5_NS_1 */
	a_CS_UpdateCharData[0] = gu8TempUnitP1T1;
	LOG_INFO_APP("CS_UNIT_P1T1 READRESP DATA : %02x\r\n",a_CS_UpdateCharData[0]);
	/* Update readresp data length */
  cs_readresp_data.Length = (cs_readresp_data.Length) + 1;
	CS_UpdateValue(CS_CS_UNIT_P1T1, &cs_readresp_data);
	/* USER CODE END Service5Char5_NS_1 */
  return;
}

void CS_Cs_mod_com_error_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CS_Data_t cs_readresp_data;

  cs_readresp_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_readresp_data.Length = 0;

  /* USER CODE BEGIN Service5Char6_NS_1 */
	a_CS_UpdateCharData[0] = (gu16TempModComErr & 0xff00)>>8;
	a_CS_UpdateCharData[1] = (gu16TempModComErr & 0x00ff);
	LOG_INFO_APP("CS_MOD_COM_ERROR READRESP DATA : 0x%02x%02x\r\n", 
							a_CS_UpdateCharData[0],a_CS_UpdateCharData[1]);
	/* Update readresp data length */
  cs_readresp_data.Length = (cs_readresp_data.Length) + 2;
  CS_UpdateValue(CS_CS_MOD_COM_ERROR, &cs_readresp_data);
	/* USER CODE END Service5Char6_NS_1 */
  return;
}

void CS_Cs_diag_error_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CS_Data_t cs_readresp_data;

  cs_readresp_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_readresp_data.Length = 0;

  /* USER CODE BEGIN Service5Char7_NS_1 */
	a_CS_UpdateCharData[0] = (gu16DiagErr & 0xff00)>>8;
	a_CS_UpdateCharData[1] = (gu16DiagErr & 0x00ff);
	LOG_INFO_APP("CS_DIAG_ERROR READRESP DATA : 0x%02x%02x\r\n", 
							a_CS_UpdateCharData[0],a_CS_UpdateCharData[1]);
	/* Update readresp data length */
  cs_readresp_data.Length = (cs_readresp_data.Length) + 2;  
  CS_UpdateValue(CS_CS_DIAG_ERROR, &cs_readresp_data);
	/* USER CODE END Service5Char7_NS_1 */
  return;
}

void CS_Cs_diag_warn_ReadUpdate(void) /* Property ReadResponseUpdate */
{
	CS_Data_t cs_readresp_data;

  cs_readresp_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_readresp_data.Length = 0;

  /* USER CODE BEGIN Service5Char8_NS_1 */
	a_CS_UpdateCharData[0] = (gu16DiagWarn & 0xff00)>>8;
	a_CS_UpdateCharData[1] = (gu16DiagWarn & 0x00ff);
	LOG_INFO_APP("CS_DIAG_WARN READRESP DATA : 0x%02x%02x\r\n", 
							a_CS_UpdateCharData[0],a_CS_UpdateCharData[1]);
	/* Update readresp data length */
  cs_readresp_data.Length = (cs_readresp_data.Length) + 2;	
  CS_UpdateValue(CS_CS_DIAG_WARN, &cs_readresp_data); 
	/* USER CODE END Service5Char8_NS_1 */
  return;
}

void CS_Cs_inlet_pres_pd1_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CS_Data_t cs_readresp_data;

  cs_readresp_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_readresp_data.Length = 0;

  /* USER CODE BEGIN Service5Char9_NS_1 */
	memset(a_CS_UpdateCharData,0,sizeof(a_CS_UpdateCharData));
	convert_float_to_byte_array(f32Inlet_air_pressure_PD1, lu8floatTemp_cs);
  strcpy((char*)a_CS_UpdateCharData, (char*)lu8floatTemp_cs);
  LOG_INFO_APP("CS_INLET_PRES_PD1 READRESP DATA : %s\r\n", a_CS_UpdateCharData);
  /* Update readresp data length */
  cs_readresp_data.Length = (cs_readresp_data.Length) + 4;
  CS_UpdateValue(CS_CS_INLET_PRES_PD1, &cs_readresp_data);
	/* USER CODE END Service5Char9_NS_1 */
  return;
}

void CS_Cs_outlet_pres_pd2_ReadUpdate(void) /* Property ReadResponseUpdate */
{
	CS_Data_t cs_readresp_data;

  cs_readresp_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_readresp_data.Length = 0;

  /* USER CODE BEGIN Service5Char10_NS_1 */
	memset(a_CS_UpdateCharData,0,sizeof(a_CS_UpdateCharData));
	convert_float_to_byte_array(f32Outlet_air_pressure_PD2, lu8floatTemp_cs);
  strcpy((char*)a_CS_UpdateCharData, (char*)lu8floatTemp_cs);
  LOG_INFO_APP("CS_OUTLET_PRES_PD2 READRESP DATA : %s\r\n", a_CS_UpdateCharData);
  /* Update readresp data length */
  cs_readresp_data.Length = (cs_readresp_data.Length) + 4;
  CS_UpdateValue(CS_CS_OUTLET_PRES_PD2, &cs_readresp_data);
	/* USER CODE END Service5Char10_NS_1 */
  return;
}

void CS_Cs_opening_per_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CS_Data_t cs_readresp_data;

  cs_readresp_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_readresp_data.Length = 0;

  /* USER CODE BEGIN Service5Char11_NS_1 */
	memset(a_CS_UpdateCharData,0,sizeof(a_CS_UpdateCharData));
	convert_float_to_byte_array(f32OpeningPercentage, lu8floatTemp_cs);
  strcpy((char*)a_CS_UpdateCharData, (char*)lu8floatTemp_cs);
  LOG_INFO_APP("CS_OPENING_PER READRESP DATA : %s\r\n", a_CS_UpdateCharData);
  /* Update readresp data length */
  cs_readresp_data.Length = (cs_readresp_data.Length) + 4;
  CS_UpdateValue(CS_CS_OPENING_PER, &cs_readresp_data);
	/* USER CODE END Service5Char11_NS_1 */	
  return;
}

void CS_Cs_operation_mode_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CS_Data_t cs_readresp_data;

  cs_readresp_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_readresp_data.Length = 0;

  /* USER CODE BEGIN Service5Char12_NS_1 */
	a_CS_UpdateCharData[0] = u8ModeOfOperation;
	LOG_INFO_APP("CS_OPERATION_MODE READRESP DATA : %02x\r\n",a_CS_UpdateCharData[0]);
	/* Update readresp data length */
  cs_readresp_data.Length = (cs_readresp_data.Length) + 1;
	CS_UpdateValue(CS_CS_OPERATION_MODE, &cs_readresp_data);
	/* USER CODE END Service5Char12_NS_1 */
  return;
}

void CS_Cs_lvdt_amp_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CS_Data_t cs_readresp_data;

  cs_readresp_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_readresp_data.Length = 0;

  /* USER CODE BEGIN Service5Char13_NS_1 */
	a_CS_UpdateCharData[0] = (u16LVDT_Amplitude & 0xff00)>>8;
	a_CS_UpdateCharData[1] = (u16LVDT_Amplitude & 0x00ff);
	LOG_INFO_APP("CS_LVDT_AMP READRESP DATA : 0x%02x%02x\r\n", 
							a_CS_UpdateCharData[0],a_CS_UpdateCharData[1]);
	/* Update readresp data length */
  cs_readresp_data.Length = (cs_readresp_data.Length) + 2;
  CS_UpdateValue(CS_CS_LVDT_AMP, &cs_readresp_data);
	/* USER CODE END Service5Char13_NS_1 */
  return;
}

void CS_Cs_totalizer_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CS_Data_t cs_readresp_data;

  cs_readresp_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_readresp_data.Length = 0;

  /* USER CODE BEGIN Service5Char14_NS_1 */
	a_CS_UpdateCharData[0] = (gu32total & 0xff000000)>>24;
	a_CS_UpdateCharData[1] = (gu32total & 0x00ff0000)>>16;
	a_CS_UpdateCharData[2] = (gu32total & 0x0000ff00)>>8;
	a_CS_UpdateCharData[3] = (gu32total & 0x000000ff);
	LOG_INFO_APP("CS_TOTALIZER READRESP DATA : 0x%02x%02x%02x%02x\r\n", 
							a_CS_UpdateCharData[0],a_CS_UpdateCharData[1],
							a_CS_UpdateCharData[2],a_CS_UpdateCharData[3]
							);
	/* Update readresp data length */
  cs_readresp_data.Length = (cs_readresp_data.Length) + 4;
	CS_UpdateValue(CS_CS_TOTALIZER, &cs_readresp_data);
	/* USER CODE END Service5Char14_NS_1 */
  return;
}

void CS_Cs_reset_button_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CS_Data_t cs_readresp_data;

  cs_readresp_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_readresp_data.Length = 0;

	
  /* USER CODE BEGIN Service5Char15_NS_1 */
	a_CS_UpdateCharData[0] = u8ResetTotalizerVal;
	LOG_INFO_APP("CS_RESET_BUTTON READRESP DATA : %02x\r\n",a_CS_UpdateCharData[0]);
	/* Update readresp data length */
  cs_readresp_data.Length = (cs_readresp_data.Length) + 1;
	CS_UpdateValue(CS_CS_RESET_BUTTON, &cs_readresp_data);
	/* USER CODE END Service5Char15_NS_1 */
  return;
}

void CS_Cs_time_stamp_hhmm_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CS_Data_t cs_readresp_data;

  cs_readresp_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_readresp_data.Length = 0;

  /* USER CODE BEGIN Service5Char16_NS_1 */
	a_CS_UpdateCharData[0] = (gu16TimeHHMM & 0xff00)>>8;
	a_CS_UpdateCharData[1] = (gu16TimeHHMM & 0x00ff);
	LOG_INFO_APP("CS_TIME_STAMP_HHMM READRESP DATA : 0x%02x%02x\r\n", 
							a_CS_UpdateCharData[0],a_CS_UpdateCharData[1]);
	/* Update readresp data length */
  cs_readresp_data.Length = (cs_readresp_data.Length) + 2;
	CS_UpdateValue(CS_CS_TIME_STAMP_HHMM, &cs_readresp_data);
	/* USER CODE END Service5Char16_NS_1 */
  return;
}

void CS_Cs_time_stamp_ddmm_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CS_Data_t cs_readresp_data;

  cs_readresp_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_readresp_data.Length = 0;

  /* USER CODE BEGIN Service5Char17_NS_1 */
	a_CS_UpdateCharData[0] = (gu16TimeDDMM & 0xff00)>>8;
	a_CS_UpdateCharData[1] = (gu16TimeDDMM & 0x00ff);
	LOG_INFO_APP("CS_TIME_STAMP_DDMM READRESP DATA : 0x%02x%02x\r\n", 
							a_CS_UpdateCharData[0],a_CS_UpdateCharData[1]);
	/* Update readresp data length */
  cs_readresp_data.Length = (cs_readresp_data.Length) + 2;
  CS_UpdateValue(CS_CS_TIME_STAMP_DDMM, &cs_readresp_data);
	/* USER CODE END Service5Char17_NS_1 */
  return;
}

void CS_Cs_year_stamp_yyyy_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CS_Data_t cs_readresp_data;

  cs_readresp_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_readresp_data.Length = 0;

  /* USER CODE BEGIN Service5Char18_NS_1 */
	a_CS_UpdateCharData[0] = (gu16YearYYYY & 0xff00)>>8;
	a_CS_UpdateCharData[1] = (gu16YearYYYY & 0x00ff);
	LOG_INFO_APP("CS_YEAR_STAMP_YYYY READRESP DATA : 0x%02x%02x\r\n", 
							a_CS_UpdateCharData[0],a_CS_UpdateCharData[1]);
	/* Update readresp data length */
  cs_readresp_data.Length = (cs_readresp_data.Length) + 2;
  CS_UpdateValue(CS_CS_YEAR_STAMP_YYYY, &cs_readresp_data);
	/* USER CODE END Service5Char18_NS_1 */
  return;
}

__USED void CS_Cs_totalizer_last_val_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CS_Data_t cs_readresp_data;
	
	cs_readresp_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_readresp_data.Length = 0;

  /* USER CODE BEGIN Service5Char19_NS_1 */
	a_CS_UpdateCharData[0] = (gu32LastTotal & 0xff000000)>>24;
	a_CS_UpdateCharData[1] = (gu32LastTotal & 0x00ff0000)>>16;
	a_CS_UpdateCharData[2] = (gu32LastTotal & 0x0000ff00)>>8;
	a_CS_UpdateCharData[3] = (gu32LastTotal & 0x000000ff);
	LOG_INFO_APP("CS_TOTALIZER_LAST_VAL READRESP DATA : 0x%02x%02x%02x%02x\r\n", 
							a_CS_UpdateCharData[0],a_CS_UpdateCharData[1],
							a_CS_UpdateCharData[2],a_CS_UpdateCharData[3]
							);
	/* Update readresp data length */
  cs_readresp_data.Length = (cs_readresp_data.Length) + 4;
	CS_UpdateValue(CS_CS_TOTALIZER_LAST_VAL, &cs_readresp_data);
  /* USER CODE END Service5Char19_NS_1 */
  return;
}

void CS_Cs_totalizer_unit_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CS_Data_t cs_readresp_data;

  cs_readresp_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_readresp_data.Length = 0;

  /* USER CODE BEGIN Service5Char20_NS_1 */
	a_CS_UpdateCharData[0] = gu8TotalizerUnit;
	LOG_INFO_APP("CS_TOTALIZER_UNIT READRESP DATA : %02x\r\n",a_CS_UpdateCharData[0]);
	/* Update readresp data length */
  cs_readresp_data.Length = (cs_readresp_data.Length) + 1;
  CS_UpdateValue(CS_CS_TOTALIZER_UNIT, &cs_readresp_data);
	/* USER CODE END Service5Char20_NS_1 */
  return;
}

void CS_Cs_connection_status_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CS_Data_t cs_readresp_data;

  cs_readresp_data.p_Payload = (uint8_t*)a_CS_UpdateCharData;
  cs_readresp_data.Length = 0;

  /* USER CODE BEGIN Service5Char21_NS_1 */
	a_CS_UpdateCharData[0] = lu8connection_status;
	LOG_INFO_APP("CS_CONNECTION_STATUS READRESP DATA : %02x\r\n",a_CS_UpdateCharData[0]);
	/* Update readresp data length */
  cs_readresp_data.Length = (cs_readresp_data.Length) + 1;
  CS_UpdateValue(CS_CS_CONNECTION_STATUS, &cs_readresp_data);
	/* USER CODE END Service5Char21_NS_1 */
  return;
}
/* USER CODE END FD_LOCAL_FUNCTIONS */
