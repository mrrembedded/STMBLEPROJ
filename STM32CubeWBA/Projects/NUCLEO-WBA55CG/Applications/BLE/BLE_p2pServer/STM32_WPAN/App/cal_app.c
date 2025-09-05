/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    CAL_app.c
  * @author  MCD Application Team
  * @brief   CAL_app application definition.
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
#include "cal_app.h"
#include "cal.h"
#include "stm32_rtos.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

typedef enum
{
  Cs_calib_status_NOTIFICATION_OFF,
  Cs_calib_status_NOTIFICATION_ON,
  Cs_calib_resp_code_NOTIFICATION_OFF,
  Cs_calib_resp_code_NOTIFICATION_ON,
  Cs_calib_reserved_NOTIFICATION_OFF,
  Cs_calib_reserved_NOTIFICATION_ON,
  /* USER CODE BEGIN Service6_APP_SendInformation_t */

  /* USER CODE END Service6_APP_SendInformation_t */
  CAL_APP_SENDINFORMATION_LAST
} CAL_APP_SendInformation_t;

typedef struct
{
  CAL_APP_SendInformation_t     Cs_calib_status_Notification_Status;
  CAL_APP_SendInformation_t     Cs_calib_resp_code_Notification_Status;
  CAL_APP_SendInformation_t     Cs_calib_reserved_Notification_Status;
  /* USER CODE BEGIN Service6_APP_Context_t */

  /* USER CODE END Service6_APP_Context_t */
  uint16_t              ConnectionHandle;
} CAL_APP_Context_t;

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
static CAL_APP_Context_t CAL_APP_Context;

uint8_t a_CAL_UpdateCharData[247];

/* USER CODE BEGIN PV */
uint8_t lu8CalibType=0;
uint8_t gu8TempCalibStatus = 0;
uint8_t gu8TempCalibRespCode = 0x0A;
uint8_t gu8TempCalibReserved = 0;

uint8_t lu8CalibType_notify_flag=0;
uint8_t gu8TempCalibStatus_notify_flag = 0;
uint8_t gu8TempCalibRespCode_notify_flag = 0;
uint8_t gu8TempCalibReserved_notify_flag = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static void CAL_Cs_calib_status_SendNotification(void);
static void CAL_Cs_calib_resp_code_SendNotification(void);
static void CAL_Cs_calib_reserved_SendNotification(void);

/* USER CODE BEGIN PFP */
static void CAL_APP_Parameters_context_Init(void);
void CAL_Cs_calib_type_ReadUpdate(void);
void CAL_Cs_calib_status_ReadUpdate(void);
void CAL_Cs_calib_resp_code_ReadUpdate(void);
void CAL_Cs_calib_reserved_ReadUpdate(void);
/* USER CODE END PFP */

/* Functions Definition ------------------------------------------------------*/
void CAL_Notification(CAL_NotificationEvt_t *p_Notification)
{
  /* USER CODE BEGIN Service6_Notification_1 */

  /* USER CODE END Service6_Notification_1 */
  switch(p_Notification->EvtOpcode)
  {
    /* USER CODE BEGIN Service6_Notification_Service6_EvtOpcode */

    /* USER CODE END Service6_Notification_Service6_EvtOpcode */

    case CAL_CS_CALIB_TYPE_READ_EVT:
      /* USER CODE BEGIN Service6Char1_READ_EVT */
			LOG_INFO_APP("CAL_CS_CALIB_TYPE_READ\r\n");
			CAL_Cs_calib_type_ReadUpdate();
      /* USER CODE END Service6Char1_READ_EVT */
      break;

    case CAL_CS_CALIB_TYPE_WRITE_EVT:
      /* USER CODE BEGIN Service6Char1_WRITE_EVT */
			lu8CalibType = p_Notification->DataTransfered.p_Payload[0];
			LOG_INFO_APP("TS_PWM_ON_TIME WRITE : 0x%02x\r\n",lu8CalibType);
			lu8CalibType_notify_flag =1; 
      /* USER CODE END Service6Char1_WRITE_EVT */
      break;

    case CAL_CS_CALIB_STATUS_READ_EVT:
      /* USER CODE BEGIN Service6Char2_READ_EVT */
			LOG_INFO_APP("CAL_CS_CALIB_STATUS_READ\r\n");
			CAL_Cs_calib_status_ReadUpdate();
      /* USER CODE END Service6Char2_READ_EVT */
      break;

    case CAL_CS_CALIB_STATUS_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN Service6Char2_NOTIFY_ENABLED_EVT */
			CAL_APP_Context.Cs_calib_status_Notification_Status = Cs_calib_status_NOTIFICATION_ON;
      LOG_INFO_APP("CS_CALIB_STATUS NOTIFICATION ENABLED\r\n");    
      /* USER CODE END Service6Char2_NOTIFY_ENABLED_EVT */
      break;

    case CAL_CS_CALIB_STATUS_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN Service6Char2_NOTIFY_DISABLED_EVT */
			CAL_APP_Context.Cs_calib_status_Notification_Status = Cs_calib_status_NOTIFICATION_OFF;
      LOG_INFO_APP("CS_CALIB_STATUS NOTIFICATION DISABLED\r\n");    
      /* USER CODE END Service6Char2_NOTIFY_DISABLED_EVT */
      break;

    case CAL_CS_CALIB_RESP_CODE_READ_EVT:
      /* USER CODE BEGIN Service6Char3_READ_EVT */
			LOG_INFO_APP("CAL_CS_CALIB_RESP_CODE_READ\r\n");
			CAL_Cs_calib_resp_code_ReadUpdate();
      /* USER CODE END Service6Char3_READ_EVT */
      break;

    case CAL_CS_CALIB_RESP_CODE_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN Service6Char3_NOTIFY_ENABLED_EVT */
			CAL_APP_Context.Cs_calib_resp_code_Notification_Status = Cs_calib_resp_code_NOTIFICATION_ON;
      LOG_INFO_APP("CS_CALIB_RESP_CODE NOTIFICATION ENABLED\r\n");    
      /* USER CODE END Service6Char3_NOTIFY_ENABLED_EVT */
      break;

    case CAL_CS_CALIB_RESP_CODE_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN Service6Char3_NOTIFY_DISABLED_EVT */
			CAL_APP_Context.Cs_calib_resp_code_Notification_Status = Cs_calib_resp_code_NOTIFICATION_OFF;
      LOG_INFO_APP("CS_CALIB_RESP_CODE NOTIFICATION DISABLED\r\n"); 
      /* USER CODE END Service6Char3_NOTIFY_DISABLED_EVT */
      break;

    case CAL_CS_CALIB_RESERVED_READ_EVT:
      /* USER CODE BEGIN Service6Char4_READ_EVT */
			LOG_INFO_APP("CAL_CS_CALIB_RESERVED_READ\r\n");
			CAL_Cs_calib_reserved_ReadUpdate();
      /* USER CODE END Service6Char4_READ_EVT */
      break;

    case CAL_CS_CALIB_RESERVED_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN Service6Char4_NOTIFY_ENABLED_EVT */
			CAL_APP_Context.Cs_calib_reserved_Notification_Status = Cs_calib_reserved_NOTIFICATION_ON;
      LOG_INFO_APP("CS_CALIB_RESERVED NOTIFICATION ENABLED\r\n");  
      /* USER CODE END Service6Char4_NOTIFY_ENABLED_EVT */
      break;

    case CAL_CS_CALIB_RESERVED_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN Service6Char4_NOTIFY_DISABLED_EVT */
			CAL_APP_Context.Cs_calib_reserved_Notification_Status = Cs_calib_reserved_NOTIFICATION_OFF;
      LOG_INFO_APP("CS_CALIB_RESERVED NOTIFICATION DISABLED\r\n"); 
      /* USER CODE END Service6Char4_NOTIFY_DISABLED_EVT */
      break;

    default:
      /* USER CODE BEGIN Service6_Notification_default */

      /* USER CODE END Service6_Notification_default */
      break;
  }
  /* USER CODE BEGIN Service6_Notification_2 */

  /* USER CODE END Service6_Notification_2 */
  return;
}

void CAL_APP_EvtRx(CAL_APP_ConnHandleNotEvt_t *p_Notification)
{
  /* USER CODE BEGIN Service6_APP_EvtRx_1 */

  /* USER CODE END Service6_APP_EvtRx_1 */

  switch(p_Notification->EvtOpcode)
  {
    /* USER CODE BEGIN Service6_APP_EvtRx_Service6_EvtOpcode */

    /* USER CODE END Service6_APP_EvtRx_Service6_EvtOpcode */
    case CAL_CONN_HANDLE_EVT :
      /* USER CODE BEGIN Service6_APP_CONN_HANDLE_EVT */

      /* USER CODE END Service6_APP_CONN_HANDLE_EVT */
      break;

    case CAL_DISCON_HANDLE_EVT :
      /* USER CODE BEGIN Service6_APP_DISCON_HANDLE_EVT */
			CAL_APP_Parameters_context_Init();
      /* USER CODE END Service6_APP_DISCON_HANDLE_EVT */
      break;

    default:
      /* USER CODE BEGIN Service6_APP_EvtRx_default */

      /* USER CODE END Service6_APP_EvtRx_default */
      break;
  }

  /* USER CODE BEGIN Service6_APP_EvtRx_2 */

  /* USER CODE END Service6_APP_EvtRx_2 */

  return;
}

void CAL_APP_Init(void)
{
  UNUSED(CAL_APP_Context);
  CAL_Init();

  /* USER CODE BEGIN Service6_APP_Init */
	UTIL_SEQ_RegTask( 1U << CFG_TASK_SEND_NOTIF_ID_CS_CALIB_STATUS, UTIL_SEQ_RFU, CAL_Cs_calib_status_SendNotification);
  UTIL_SEQ_RegTask( 1U << CFG_TASK_SEND_NOTIF_ID_CS_CALIB_RESP_CODE, UTIL_SEQ_RFU, CAL_Cs_calib_resp_code_SendNotification);
	UTIL_SEQ_RegTask( 1U << CFG_TASK_SEND_NOTIF_ID_CS_CALIB_RESERVED, UTIL_SEQ_RFU, CAL_Cs_calib_resp_code_SendNotification);
	CAL_APP_Context.Cs_calib_status_Notification_Status = Cs_calib_status_NOTIFICATION_OFF;
	CAL_APP_Context.Cs_calib_resp_code_Notification_Status = Cs_calib_resp_code_NOTIFICATION_OFF;
  CAL_APP_Context.Cs_calib_reserved_Notification_Status = Cs_calib_reserved_NOTIFICATION_OFF;
	CAL_APP_Parameters_context_Init();
  /* USER CODE END Service6_APP_Init */
  return;
}

/* USER CODE BEGIN FD */

/* USER CODE END FD */

/*************************************************************
 *
 * LOCAL FUNCTIONS
 *
 *************************************************************/
__USED void CAL_Cs_calib_status_SendNotification(void) /* Property Notification */
{
  CAL_APP_SendInformation_t notification_on_off = Cs_calib_status_NOTIFICATION_OFF;
  CAL_Data_t cal_notification_data;

  cal_notification_data.p_Payload = (uint8_t*)a_CAL_UpdateCharData;
  cal_notification_data.Length = 0;

  /* USER CODE BEGIN Service6Char2_NS_1 */
	a_CAL_UpdateCharData[0] = gu8TempCalibStatus;
	LOG_INFO_APP("CAL_CS_CALIB_STATUS NOTIFY DATA : %02x\r\n",a_CAL_UpdateCharData[0]);
	/* Update readresp data length */
  cal_notification_data.Length = (cal_notification_data.Length) + 1;

  if(CAL_APP_Context.Cs_calib_status_Notification_Status == Cs_calib_status_NOTIFICATION_ON)
  {
    LOG_INFO_APP("INFORM CLIENT CAL_CS_CALIB_STATUS Changed\r\n");
    notification_on_off = Cs_calib_reserved_NOTIFICATION_ON;
  }
  else
  {
    LOG_INFO_APP("CAN'T INFORM CLIENT CAL_CS_CALIB_STATUS - NOTIFICATION DISABLED\r\n");
  }
  /* USER CODE END Service6Char2_NS_1 */

  if (notification_on_off != Cs_calib_status_NOTIFICATION_OFF)
  {
    CAL_UpdateValue(CAL_CS_CALIB_STATUS, &cal_notification_data);
  }

  /* USER CODE BEGIN Service6Char2_NS_Last */

  /* USER CODE END Service6Char2_NS_Last */

  return;
}

__USED void CAL_Cs_calib_resp_code_SendNotification(void) /* Property Notification */
{
  CAL_APP_SendInformation_t notification_on_off = Cs_calib_resp_code_NOTIFICATION_OFF;
  CAL_Data_t cal_notification_data;

  cal_notification_data.p_Payload = (uint8_t*)a_CAL_UpdateCharData;
  cal_notification_data.Length = 0;

  /* USER CODE BEGIN Service6Char3_NS_1 */
	a_CAL_UpdateCharData[0] = gu8TempCalibRespCode;
	LOG_INFO_APP("CAL_CS_CALIB_RESP_CODE NOTIFY DATA : %02x\r\n",a_CAL_UpdateCharData[0]);
	/* Update readresp data length */
  cal_notification_data.Length = (cal_notification_data.Length) + 1;

  if(CAL_APP_Context.Cs_calib_resp_code_Notification_Status == Cs_calib_resp_code_NOTIFICATION_ON)
  {
    LOG_INFO_APP("INFORM CLIENT CAL_CS_CALIB_RESP_CODE Changed\r\n");
    notification_on_off = Cs_calib_resp_code_NOTIFICATION_ON;
  }
  else
  {
    LOG_INFO_APP("CAN'T INFORM CLIENT CAL_CS_CALIB_RESP_CODE - NOTIFICATION DISABLED\r\n");
  }
  /* USER CODE END Service6Char3_NS_1 */

  if (notification_on_off != Cs_calib_resp_code_NOTIFICATION_OFF)
  {
    CAL_UpdateValue(CAL_CS_CALIB_RESP_CODE, &cal_notification_data);
  }

  /* USER CODE BEGIN Service6Char3_NS_Last */

  /* USER CODE END Service6Char3_NS_Last */

  return;
}

__USED void CAL_Cs_calib_reserved_SendNotification(void) /* Property Notification */
{
  CAL_APP_SendInformation_t notification_on_off = Cs_calib_reserved_NOTIFICATION_OFF;
  CAL_Data_t cal_notification_data;

  cal_notification_data.p_Payload = (uint8_t*)a_CAL_UpdateCharData;
  cal_notification_data.Length = 0;

  /* USER CODE BEGIN Service6Char4_NS_1 */
	a_CAL_UpdateCharData[0] = gu8TempCalibReserved;
	LOG_INFO_APP("CAL_CS_CALIB_RESERVED NOTIFY DATA : %02x\r\n",a_CAL_UpdateCharData[0]);
	/* Update readresp data length */
  cal_notification_data.Length = (cal_notification_data.Length) + 1;

  if(CAL_APP_Context.Cs_calib_reserved_Notification_Status == Cs_calib_reserved_NOTIFICATION_ON)
  {
    LOG_INFO_APP("INFORM CLIENT CAL_CS_CALIB_RESERVED Changed\r\n");
    notification_on_off = Cs_calib_reserved_NOTIFICATION_ON;
  }
  else
  {
    LOG_INFO_APP("CAN'T INFORM CLIENT CAL_CS_CALIB_RESERVED - NOTIFICATION DISABLED\r\n");
  }
  /* USER CODE END Service6Char4_NS_1 */

  if (notification_on_off != Cs_calib_reserved_NOTIFICATION_OFF)
  {
    CAL_UpdateValue(CAL_CS_CALIB_RESERVED, &cal_notification_data);
  }

  /* USER CODE BEGIN Service6Char4_NS_Last */

  /* USER CODE END Service6Char4_NS_Last */

  return;
}

/* USER CODE BEGIN FD_LOCAL_FUNCTIONS */
static void CAL_APP_Parameters_context_Init(void)
{
	return;
}

void CAL_Cs_calib_type_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CAL_Data_t cal_readresp_data;

  cal_readresp_data.p_Payload = (uint8_t*)a_CAL_UpdateCharData;
  cal_readresp_data.Length = 0;

  /* USER CODE BEGIN Service6Char1_NS_1 */
	a_CAL_UpdateCharData[0] = lu8CalibType;
	LOG_INFO_APP("CAL_CS_CALIB_TYPE READRESP DATA : %02x\r\n",a_CAL_UpdateCharData[0]);
	/* Update readresp data length */
  cal_readresp_data.Length = (cal_readresp_data.Length) + 1;
	CAL_UpdateValue(CAL_CS_CALIB_TYPE, &cal_readresp_data);
  /* USER CODE END Service6Char1_NS_1 */
  return;
}

void CAL_Cs_calib_status_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CAL_Data_t cal_readresp_data;

  cal_readresp_data.p_Payload = (uint8_t*)a_CAL_UpdateCharData;
  cal_readresp_data.Length = 0;

  /* USER CODE BEGIN Service6Char2_NS_1 */
	a_CAL_UpdateCharData[0] = gu8TempCalibStatus;
	LOG_INFO_APP("CAL_CS_CALIB_STATUS READRESP DATA : %02x\r\n",a_CAL_UpdateCharData[0]);
	/* Update readresp data length */
  cal_readresp_data.Length = (cal_readresp_data.Length) + 1;
	CAL_UpdateValue(CAL_CS_CALIB_STATUS, &cal_readresp_data);
  /* USER CODE END Service6Char2_NS_1 */
  return;
}

void CAL_Cs_calib_resp_code_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CAL_Data_t cal_readresp_data;

  cal_readresp_data.p_Payload = (uint8_t*)a_CAL_UpdateCharData;
  cal_readresp_data.Length = 0;

  /* USER CODE BEGIN Service6Char3_NS_1 */
	a_CAL_UpdateCharData[0] = gu8TempCalibRespCode;
	LOG_INFO_APP("CAL_CS_CALIB_RESP_CODE READRESP DATA : %02x\r\n",a_CAL_UpdateCharData[0]);
	/* Update readresp data length */
  cal_readresp_data.Length = (cal_readresp_data.Length) + 1;
	CAL_UpdateValue(CAL_CS_CALIB_RESP_CODE, &cal_readresp_data);
  /* USER CODE END Service6Char3_NS_1 */
  return;
}

void CAL_Cs_calib_reserved_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  CAL_Data_t cal_readresp_data;

  cal_readresp_data.p_Payload = (uint8_t*)a_CAL_UpdateCharData;
  cal_readresp_data.Length = 0;

  /* USER CODE BEGIN Service6Char4_NS_1 */
	a_CAL_UpdateCharData[0] = gu8TempCalibReserved;
	LOG_INFO_APP("CAL_CS_CALIB_RESERVED READRESP DATA : %02x\r\n",a_CAL_UpdateCharData[0]);
	/* Update readresp data length */
  cal_readresp_data.Length = (cal_readresp_data.Length) + 1;
	CAL_UpdateValue(CAL_CS_CALIB_RESERVED, &cal_readresp_data);
  /* USER CODE END Service6Char4_NS_1 */
  return;
}
/* USER CODE END FD_LOCAL_FUNCTIONS */
