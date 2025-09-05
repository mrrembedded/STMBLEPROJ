/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    TS_app.c
  * @author  MCD Application Team
  * @brief   TS_app application definition.
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
#include "ts_app.h"
#include "ts.h"
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
  Ts_test_status_NOTIFICATION_OFF,
  Ts_test_status_NOTIFICATION_ON,
  Ts_test_resp_code_NOTIFICATION_OFF,
  Ts_test_resp_code_NOTIFICATION_ON,
  /* USER CODE BEGIN Service4_APP_SendInformation_t */

  /* USER CODE END Service4_APP_SendInformation_t */
  TS_APP_SENDINFORMATION_LAST
} TS_APP_SendInformation_t;

typedef struct
{
  TS_APP_SendInformation_t     Ts_test_status_Notification_Status;
  TS_APP_SendInformation_t     Ts_test_resp_code_Notification_Status;
  /* USER CODE BEGIN Service4_APP_Context_t */

  /* USER CODE END Service4_APP_Context_t */
  uint16_t              ConnectionHandle;
} TS_APP_Context_t;

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
static TS_APP_Context_t TS_APP_Context;

uint8_t a_TS_UpdateCharData[247];

/* USER CODE BEGIN PV */
uint8_t 	lu8TestType = 0 ;
float   	lf32PosPerVal = 0;
uint8_t 	lu8PwmOnTime  = 0;
uint16_t 	gu16TempTestStatus = 0;
uint8_t 	gu8TempTestRespCode = 0x0A;
uint8_t 	lu8floatTemp_ts[4]  = {0};

uint8_t 	lu8TestType_notify_flag = 0 ;
uint8_t   lf32PosPerVal_notify_flag = 0;
uint8_t 	lu8PwmOnTime_notify_flag  = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static void TS_Ts_test_status_SendNotification(void);
static void TS_Ts_test_resp_code_SendNotification(void);

/* USER CODE BEGIN PFP */
static void TS_APP_Parameters_context_Init(void);
void TS_Ts_test_type_ReadUpdate(void); /* Property ReadResponseUpdate */
void TS_Ts_pos_per_val_ReadUpdate(void); /* Property ReadResponseUpdate */
void TS_Ts_pwm_on_time_ReadUpdate(void); /* Property ReadResponseUpdate */
void TS_Ts_test_status_ReadUpdate(void); /* Property ReadResponseUpdate */
void TS_Ts_test_resp_code_ReadUpdate(void); /* Property ReadResponseUpdate */

/* USER CODE END PFP */

/* Functions Definition ------------------------------------------------------*/
void TS_Notification(TS_NotificationEvt_t *p_Notification)
{
  /* USER CODE BEGIN Service4_Notification_1 */

  /* USER CODE END Service4_Notification_1 */
  switch(p_Notification->EvtOpcode)
  {
    /* USER CODE BEGIN Service4_Notification_Service4_EvtOpcode */

    /* USER CODE END Service4_Notification_Service4_EvtOpcode */

    case TS_TS_TEST_TYPE_READ_EVT:
      /* USER CODE BEGIN Service4Char1_READ_EVT */
			LOG_INFO_APP("TS_TEST_TYPE_READ\r\n");
			TS_Ts_test_type_ReadUpdate();
      /* USER CODE END Service4Char1_READ_EVT */
      break;

    case TS_TS_TEST_TYPE_WRITE_EVT:
      /* USER CODE BEGIN Service4Char1_WRITE_EVT */
			lu8TestType = p_Notification->DataTransfered.p_Payload[0];
			LOG_INFO_APP("TS_TEST_TYPE WRITE DATA: 0x%02x\r\n",lu8TestType);
			lu8TestType_notify_flag =1; 
      /* USER CODE END Service4Char1_WRITE_EVT */
      break;

    case TS_TS_POS_PER_VAL_READ_EVT:
      /* USER CODE BEGIN Service4Char2_READ_EVT */
			LOG_INFO_APP("TS_POS_PER_VAL_READ\r\n");
			TS_Ts_pos_per_val_ReadUpdate();
      /* USER CODE END Service4Char2_READ_EVT */
      break;

    case TS_TS_POS_PER_VAL_WRITE_EVT:
      /* USER CODE BEGIN Service4Char2_WRITE_EVT */
			memset(lu8floatTemp_ts,0,sizeof(lu8floatTemp_ts));
			memcpy(lu8floatTemp_ts, p_Notification->DataTransfered.p_Payload,p_Notification->DataTransfered.Length);
      convert_byte_array_to_float(lu8floatTemp_ts, &lf32PosPerVal);
			LOG_INFO_APP("TS_TS_POS_PER_VAL_WRITE DATA = %s, FLT = %f, LEN = %d\r\n", lu8floatTemp_ts, lf32PosPerVal, p_Notification->DataTransfered.Length);
			lf32PosPerVal_notify_flag =1;      
      /* USER CODE END Service4Char2_WRITE_EVT */
      break;

    case TS_TS_PWM_ON_TIME_READ_EVT:
      /* USER CODE BEGIN Service4Char3_READ_EVT */
			LOG_INFO_APP("TS_PWM_ON_TIME_READ\r\n");
			TS_Ts_pwm_on_time_ReadUpdate();
      /* USER CODE END Service4Char3_READ_EVT */
      break;

    case TS_TS_PWM_ON_TIME_WRITE_EVT:
      /* USER CODE BEGIN Service4Char3_WRITE_EVT */
			lu8PwmOnTime = p_Notification->DataTransfered.p_Payload[0];
			LOG_INFO_APP("TS_PWM_ON_TIME WRITE : 0x%02x\r\n",lu8PwmOnTime);
			lu8PwmOnTime_notify_flag =1; 
      /* USER CODE END Service4Char3_WRITE_EVT */
      break;

    case TS_TS_TEST_STATUS_READ_EVT:
      /* USER CODE BEGIN Service4Char4_READ_EVT */
			LOG_INFO_APP("TS_TEST_STATUS_READ\r\n");
			TS_Ts_test_status_ReadUpdate();
      /* USER CODE END Service4Char4_READ_EVT */
      break;

    case TS_TS_TEST_STATUS_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN Service4Char4_NOTIFY_ENABLED_EVT */
			TS_APP_Context.Ts_test_status_Notification_Status = Ts_test_status_NOTIFICATION_ON;
      LOG_INFO_APP("TS_TEST_STATUS NOTIFICATION ENABLED\r\n");     
      /* USER CODE END Service4Char4_NOTIFY_ENABLED_EVT */
      break;

    case TS_TS_TEST_STATUS_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN Service4Char4_NOTIFY_DISABLED_EVT */
			TS_APP_Context.Ts_test_status_Notification_Status = Ts_test_status_NOTIFICATION_OFF;
      LOG_INFO_APP("TS_TEST_STATUS NOTIFICATION DISABLED\r\n");    
      /* USER CODE END Service4Char4_NOTIFY_DISABLED_EVT */
      break;

    case TS_TS_TEST_RESP_CODE_READ_EVT:
      /* USER CODE BEGIN Service4Char5_READ_EVT */
			LOG_INFO_APP("TS_TEST_RESP_CODE_READ\r\n");
			TS_Ts_test_resp_code_ReadUpdate();
      /* USER CODE END Service4Char5_READ_EVT */
      break;

    case TS_TS_TEST_RESP_CODE_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN Service4Char5_NOTIFY_ENABLED_EVT */
			TS_APP_Context.Ts_test_resp_code_Notification_Status = Ts_test_resp_code_NOTIFICATION_ON;
      LOG_INFO_APP("TS_TEST_RESP_CODE NOTIFICATION ENABLED\r\n");
      /* USER CODE END Service4Char5_NOTIFY_ENABLED_EVT */
      break;

    case TS_TS_TEST_RESP_CODE_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN Service4Char5_NOTIFY_DISABLED_EVT */
			TS_APP_Context.Ts_test_resp_code_Notification_Status = Ts_test_resp_code_NOTIFICATION_OFF;
      LOG_INFO_APP("TS_TEST_RESP_CODE NOTIFICATION DISABLED\r\n");
      /* USER CODE END Service4Char5_NOTIFY_DISABLED_EVT */
      break;

    default:
      /* USER CODE BEGIN Service4_Notification_default */

      /* USER CODE END Service4_Notification_default */
      break;
  }
  /* USER CODE BEGIN Service4_Notification_2 */

  /* USER CODE END Service4_Notification_2 */
  return;
}

void TS_APP_EvtRx(TS_APP_ConnHandleNotEvt_t *p_Notification)
{
  /* USER CODE BEGIN Service4_APP_EvtRx_1 */

  /* USER CODE END Service4_APP_EvtRx_1 */

  switch(p_Notification->EvtOpcode)
  {
    /* USER CODE BEGIN Service4_APP_EvtRx_Service4_EvtOpcode */

    /* USER CODE END Service4_APP_EvtRx_Service4_EvtOpcode */
    case TS_CONN_HANDLE_EVT :
      /* USER CODE BEGIN Service4_APP_CONN_HANDLE_EVT */

      /* USER CODE END Service4_APP_CONN_HANDLE_EVT */
      break;

    case TS_DISCON_HANDLE_EVT :
      /* USER CODE BEGIN Service4_APP_DISCON_HANDLE_EVT */
			TS_APP_Parameters_context_Init();
      /* USER CODE END Service4_APP_DISCON_HANDLE_EVT */
      break;

    default:
      /* USER CODE BEGIN Service4_APP_EvtRx_default */

      /* USER CODE END Service4_APP_EvtRx_default */
      break;
  }

  /* USER CODE BEGIN Service4_APP_EvtRx_2 */

  /* USER CODE END Service4_APP_EvtRx_2 */

  return;
}

void TS_APP_Init(void)
{
  UNUSED(TS_APP_Context);
  TS_Init();

  /* USER CODE BEGIN Service4_APP_Init */
	UTIL_SEQ_RegTask( 1U << CFG_TASK_SEND_NOTIF_ID_TS_TEST_STATUS, UTIL_SEQ_RFU, TS_Ts_test_status_SendNotification);
  UTIL_SEQ_RegTask( 1U << CFG_TASK_SEND_NOTIF_ID_TS_TEST_RESP_CODE, UTIL_SEQ_RFU, TS_Ts_test_resp_code_SendNotification);
	TS_APP_Context.Ts_test_status_Notification_Status = Ts_test_status_NOTIFICATION_OFF;
	TS_APP_Context.Ts_test_resp_code_Notification_Status = Ts_test_resp_code_NOTIFICATION_OFF;
  TS_APP_Parameters_context_Init();
  /* USER CODE END Service4_APP_Init */
  return;
}

/* USER CODE BEGIN FD */

/* USER CODE END FD */

/*************************************************************
 *
 * LOCAL FUNCTIONS
 *
 *************************************************************/
__USED void TS_Ts_test_status_SendNotification(void) /* Property Notification */
{
  TS_APP_SendInformation_t notification_on_off = Ts_test_status_NOTIFICATION_OFF;
  TS_Data_t ts_notification_data;

  ts_notification_data.p_Payload = (uint8_t*)a_TS_UpdateCharData;
  ts_notification_data.Length = 0;

  /* USER CODE BEGIN Service4Char4_NS_1 */
	a_TS_UpdateCharData[0] = (gu16TempTestStatus & 0xff00)>>8;
	a_TS_UpdateCharData[1] = (gu16TempTestStatus & 0x00ff);
	LOG_INFO_APP("TS_TEST_STATUS NOTIFY DATA : 0x%02x%02x\r\n", 
							a_TS_UpdateCharData[0],a_TS_UpdateCharData[1]);
	/* Update notification data length */
  ts_notification_data.Length = (ts_notification_data.Length) + 2;
	
	if(TS_APP_Context.Ts_test_status_Notification_Status == Ts_test_status_NOTIFICATION_ON)
  {
    LOG_INFO_APP("INFORM CLIENT TS_TEST_STATUS Changed\r\n");
    notification_on_off = Ts_test_status_NOTIFICATION_ON;
  }
  else
  {
    LOG_INFO_APP("CAN'T INFORM CLIENT TS_TEST_STATUS- NOTIFICATION DISABLED\r\n");
  }	
  /* USER CODE END Service4Char4_NS_1 */

  if (notification_on_off != Ts_test_status_NOTIFICATION_OFF)
  {
    TS_UpdateValue(TS_TS_TEST_STATUS, &ts_notification_data);
  }

  /* USER CODE BEGIN Service4Char4_NS_Last */

  /* USER CODE END Service4Char4_NS_Last */

  return;
}

__USED void TS_Ts_test_resp_code_SendNotification(void) /* Property Notification */
{
  TS_APP_SendInformation_t notification_on_off = Ts_test_resp_code_NOTIFICATION_OFF;
  TS_Data_t ts_notification_data;

  ts_notification_data.p_Payload = (uint8_t*)a_TS_UpdateCharData;
  ts_notification_data.Length = 0;

  /* USER CODE BEGIN Service4Char5_NS_1 */
	a_TS_UpdateCharData[0] = gu8TempTestRespCode;
	LOG_INFO_APP("TS_TEST_RESP_CODE NOTIFY DATA : %02x\r\n",a_TS_UpdateCharData[0]);
	/* Update notification data length */
  ts_notification_data.Length = (ts_notification_data.Length) + 1;

  if(TS_APP_Context.Ts_test_resp_code_Notification_Status == Ts_test_resp_code_NOTIFICATION_ON)
  {
    LOG_INFO_APP("INFORM CLIENT TS_TEST_RESP Changed\r\n");
    notification_on_off = Ts_test_resp_code_NOTIFICATION_ON;
  }
  else
  {
    LOG_INFO_APP("CAN'T INFORM CLIENT TS TEST RESPCODE- NOTIFICATION DISABLED\r\n");
  }
  /* USER CODE END Service4Char5_NS_1 */

  if (notification_on_off != Ts_test_resp_code_NOTIFICATION_OFF)
  {
    TS_UpdateValue(TS_TS_TEST_RESP_CODE, &ts_notification_data);
  }

  /* USER CODE BEGIN Service4Char5_NS_Last */

  /* USER CODE END Service4Char5_NS_Last */

  return;
}

/* USER CODE BEGIN FD_LOCAL_FUNCTIONS */
static void TS_APP_Parameters_context_Init(void)
{
	return;
}

void TS_Ts_test_type_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  TS_Data_t ts_readresp_data;

  ts_readresp_data.p_Payload = (uint8_t*)a_TS_UpdateCharData;
  ts_readresp_data.Length = 0;

  /* USER CODE BEGIN Service2Char1_NS_1 */
	a_TS_UpdateCharData[0] = lu8TestType;
	LOG_INFO_APP("TS_TEST_TYPE READRESP DATA : %02x\r\n",a_TS_UpdateCharData[0]);
	/* Update readresp data length */
  ts_readresp_data.Length = (ts_readresp_data.Length) + 1;
	TS_UpdateValue(TS_TS_TEST_TYPE, &ts_readresp_data);
  /* USER CODE END Service2Char1_NS_1 */
  return;
}


void TS_Ts_pos_per_val_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  TS_Data_t ts_readresp_data;

  ts_readresp_data.p_Payload = (uint8_t*)a_TS_UpdateCharData;
  ts_readresp_data.Length = 0;

  /* USER CODE BEGIN Service2Char2_NS_1 */
	memset(a_TS_UpdateCharData,0,sizeof(a_TS_UpdateCharData));
	convert_float_to_byte_array(lf32PosPerVal, lu8floatTemp_ts);
  strcpy((char*)a_TS_UpdateCharData, (char*)lu8floatTemp_ts);
  LOG_INFO_APP("TS_POS_PER_VAL READRESP DATA : %s\r\n", a_TS_UpdateCharData);
	/* Update readresp data length */
  ts_readresp_data.Length = (ts_readresp_data.Length) + 4;
	TS_UpdateValue(TS_TS_POS_PER_VAL, &ts_readresp_data);
  /* USER CODE END Service2Char2_NS_1 */
  return;
}

void TS_Ts_pwm_on_time_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  TS_Data_t ts_readresp_data;

  ts_readresp_data.p_Payload = (uint8_t*)a_TS_UpdateCharData;
  ts_readresp_data.Length = 0;

  /* USER CODE BEGIN Service2Char3_NS_1 */
	a_TS_UpdateCharData[0] = lu8PwmOnTime;
	LOG_INFO_APP("TS_PWM_ON_TIME READRESP DATA : %02x\r\n",a_TS_UpdateCharData[0]);
	/* Update readresp data length */
  ts_readresp_data.Length = (ts_readresp_data.Length) + 1;
	TS_UpdateValue(TS_TS_PWM_ON_TIME, &ts_readresp_data);
  /* USER CODE END Service2Char3_NS_1 */
  return;
}

void TS_Ts_test_status_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  TS_Data_t ts_readresp_data;

  ts_readresp_data.p_Payload = (uint8_t*)a_TS_UpdateCharData;
  ts_readresp_data.Length = 0;

  /* USER CODE BEGIN Service4Char4_NS_1 */
	a_TS_UpdateCharData[0] = (gu16TempTestStatus & 0xff00)>>8;
	a_TS_UpdateCharData[1] = (gu16TempTestStatus & 0x00ff);
	LOG_INFO_APP("TS_TEST_STATUS READRESP DATA : 0x%02x%02x\r\n", 
							a_TS_UpdateCharData[0],a_TS_UpdateCharData[1]);
	/* Update readresp data length */
  ts_readresp_data.Length = (ts_readresp_data.Length) + 2;
	TS_UpdateValue(TS_TS_TEST_STATUS, &ts_readresp_data);
  /* USER CODE END Service4Char4_NS_1 */
  return;
}

void TS_Ts_test_resp_code_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  TS_Data_t ts_readresp_data;

  ts_readresp_data.p_Payload = (uint8_t*)a_TS_UpdateCharData;
  ts_readresp_data.Length = 0;

  /* USER CODE BEGIN Service2Char5_NS_1 */
	a_TS_UpdateCharData[0] = gu8TempTestRespCode;
	LOG_INFO_APP("TS_TEST_RESP_CODE READRESP DATA : %02x\r\n",a_TS_UpdateCharData[0]);
	/* Update readresp data length */
  ts_readresp_data.Length = (ts_readresp_data.Length) + 1;
	TS_UpdateValue(TS_TS_TEST_RESP_CODE, &ts_readresp_data);
  /* USER CODE END Service2Char5_NS_1 */
  return;
}
/* USER CODE END FD_LOCAL_FUNCTIONS */
