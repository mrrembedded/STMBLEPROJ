/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    p2p_server_app.c
  * @author  MCD Application Team
  * @brief   p2p_server_app application definition.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "p2p_server_app.h"
#include "p2p_server.h"
#include "stm32_rtos.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "app_bsp.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

typedef enum
{
  Mid_NOTIFICATION_OFF,
  Mid_NOTIFICATION_ON,
  Prodname_NOTIFICATION_OFF,
  Prodname_NOTIFICATION_ON,
  Slnm_NOTIFICATION_OFF,
  Slnm_NOTIFICATION_ON,
  Devloc_NOTIFICATION_OFF,
  Devloc_NOTIFICATION_ON,
  Ds_NOTIFICATION_OFF,
  Ds_NOTIFICATION_ON,
  Devmke_NOTIFICATION_OFF,
  Devmke_NOTIFICATION_ON,
  Devmac_NOTIFICATION_OFF,
  Devmac_NOTIFICATION_ON,
  Blestkfw_NOTIFICATION_OFF,
  Blestkfw_NOTIFICATION_ON,
  Appfw_NOTIFICATION_OFF,
  Appfw_NOTIFICATION_ON,
  Advname_NOTIFICATION_OFF,
  Advname_NOTIFICATION_ON,
  /* USER CODE BEGIN Service1_APP_SendInformation_t */

  /* USER CODE END Service1_APP_SendInformation_t */
  P2P_SERVER_APP_SENDINFORMATION_LAST
} P2P_SERVER_APP_SendInformation_t;

typedef struct
{
  P2P_SERVER_APP_SendInformation_t     Mid_Notification_Status;
  P2P_SERVER_APP_SendInformation_t     Prodname_Notification_Status;
  P2P_SERVER_APP_SendInformation_t     Slnm_Notification_Status;
  P2P_SERVER_APP_SendInformation_t     Devloc_Notification_Status;
  P2P_SERVER_APP_SendInformation_t     Ds_Notification_Status;
  P2P_SERVER_APP_SendInformation_t     Devmke_Notification_Status;
  P2P_SERVER_APP_SendInformation_t     Devmac_Notification_Status;
  P2P_SERVER_APP_SendInformation_t     Blestkfw_Notification_Status;
  P2P_SERVER_APP_SendInformation_t     Appfw_Notification_Status;
  P2P_SERVER_APP_SendInformation_t     Advname_Notification_Status;
  /* USER CODE BEGIN Service1_APP_Context_t */


  /* USER CODE END Service1_APP_Context_t */
  uint16_t              ConnectionHandle;
} P2P_SERVER_APP_Context_t;

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN PD */

/*BLE Software version*/
#define Major_version                   2
#define Minor_version                   8
#define Bug_Fix                         1
/*Last modification date*/
#define DD                              27
#define MM                              07
#define YY                              25

/* USER CODE END PD */

/* External variables --------------------------------------------------------*/
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Private macros ------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
static P2P_SERVER_APP_Context_t P2P_SERVER_APP_Context;

uint8_t a_P2P_SERVER_UpdateCharData[247];

/* USER CODE BEGIN PV */
uint8_t             Mid_Value = 0x01;
uint8_t							ProdName_Value[64]="WPRV";
uint16_t						Sn_Value[4] = {0x0102, 0x0304, 0x0506, 0x0708};
uint8_t							DeviceLoc_Value[100]="Munger";
uint8_t             Ds_Value =21;
uint8_t							DeviceMake_Value[100]="MFPL";
uint8_t							DeviceMac_Value[6]={0x01, 0x0A, 0x02, 0x0B, 0x03, 0x0C};
uint8_t							BleStkFw_Value[20]={0};
uint8_t							AppFw_Value[20]={0};
uint8_t							AdvName_Value[20]="WPRVFMRnD";

uint8_t 						DeviceLoc_write_flag =0;
uint8_t 						Ds_write_flag =0;
uint8_t 						DeviceMake_write_flag =0;
uint8_t 						AdvName_write_flag =0;

/*MajerTrol Software Verison Will be updated by MODBUS */
uint8_t Maj_V = 1;
uint8_t Min_V = 20;
uint8_t BugF_V = 2;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static void P2P_SERVER_Mid_SendNotification(void);
static void P2P_SERVER_Prodname_SendNotification(void);
static void P2P_SERVER_Slnm_SendNotification(void);
static void P2P_SERVER_Devloc_SendNotification(void);
static void P2P_SERVER_Ds_SendNotification(void);
static void P2P_SERVER_Devmke_SendNotification(void);
static void P2P_SERVER_Devmac_SendNotification(void);
static void P2P_SERVER_Blestkfw_SendNotification(void);
static void P2P_SERVER_Appfw_SendNotification(void);
static void P2P_SERVER_Advname_SendNotification(void);

/* USER CODE BEGIN PFP */
static void P2P_SERVER_APP_Parameters_context_Init(void);
void P2P_SERVER_Mid_ReadUpdate(void); /* Property ReadResponseUpdate */
void P2P_SERVER_Prodname_ReadUpdate(void); /* Property ReadResponseUpdate */
void P2P_SERVER_Slnm_ReadUpdate(void); /* Property ReadResponseUpdate */
void P2P_SERVER_Devloc_ReadUpdate(void); /* Property ReadResponseUpdate */
void P2P_SERVER_Ds_ReadUpdate(void); /* Property ReadResponseUpdate */
void P2P_SERVER_Devmke_ReadUpdate(void); /* Property ReadResponseUpdate */
void P2P_SERVER_Devmac_ReadUpdate(void); /* Property ReadResponseUpdate */
void P2P_SERVER_Blestkfw_ReadUpdate(void); /* Property ReadResponseUpdate */
void P2P_SERVER_Appfw_ReadUpdate(void); /* Property ReadResponseUpdate */
void P2P_SERVER_Advname_ReadUpdate(void); /* Property ReadResponseUpdate */

/* USER CODE END PFP */

/* Functions Definition ------------------------------------------------------*/
void P2P_SERVER_Notification(P2P_SERVER_NotificationEvt_t *p_Notification)
{
  /* USER CODE BEGIN Service1_Notification_1 */

  /* USER CODE END Service1_Notification_1 */
  switch(p_Notification->EvtOpcode)
  {
    /* USER CODE BEGIN Service1_Notification_Service1_EvtOpcode */

    /* USER CODE END Service1_Notification_Service1_EvtOpcode */

    case P2P_SERVER_MID_READ_EVT:
      /* USER CODE BEGIN Service1Char1_READ_EVT */
			LOG_INFO_APP("MID READ\r\n");
			P2P_SERVER_Mid_ReadUpdate();
		
		//	UTIL_SEQ_SetTask(1 << CFG_TASK_SEND_NOTIF_ID_MID, CFG_SEQ_PRIO_0);
      /* USER CODE END Service1Char1_READ_EVT */
      break;

    case P2P_SERVER_MID_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN Service1Char1_NOTIFY_ENABLED_EVT */
      P2P_SERVER_APP_Context.Mid_Notification_Status = Mid_NOTIFICATION_ON;
      LOG_INFO_APP("MID NOTIFICATION ENABLED\r\n");
      /* USER CODE END Service1Char1_NOTIFY_ENABLED_EVT */
      break;

    case P2P_SERVER_MID_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN Service1Char1_NOTIFY_DISABLED_EVT */
      P2P_SERVER_APP_Context.Mid_Notification_Status = Mid_NOTIFICATION_OFF;
      LOG_INFO_APP("MID NOTIFICATION DISABLED\r\n");
      /* USER CODE END Service1Char1_NOTIFY_DISABLED_EVT */
      break;

    case P2P_SERVER_PRODNAME_READ_EVT:
      /* USER CODE BEGIN Service1Char2_READ_EVT */
			LOG_INFO_APP("-- P2P APPLICATION SERVER : PRODNAME READ\n");
			P2P_SERVER_Prodname_ReadUpdate();
      /* USER CODE END Service1Char2_READ_EVT */
      break;

    case P2P_SERVER_PRODNAME_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN Service1Char2_NOTIFY_ENABLED_EVT */
      P2P_SERVER_APP_Context.Prodname_Notification_Status = Prodname_NOTIFICATION_ON;
      LOG_INFO_APP("PRODNAME NOTIFICATION ENABLED\r\n");
      /* USER CODE END Service1Char2_NOTIFY_ENABLED_EVT */
      break;

    case P2P_SERVER_PRODNAME_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN Service1Char2_NOTIFY_DISABLED_EVT */
      P2P_SERVER_APP_Context.Prodname_Notification_Status = Prodname_NOTIFICATION_OFF;
      LOG_INFO_APP("PRODNAME NOTIFICATION DISABLED\r\n");
      /* USER CODE END Service1Char2_NOTIFY_DISABLED_EVT */
      break;

    case P2P_SERVER_SLNM_READ_EVT:
      /* USER CODE BEGIN Service1Char3_READ_EVT */
			LOG_INFO_APP("SER NUM READ\r\n");
			P2P_SERVER_Slnm_ReadUpdate();
      /* USER CODE END Service1Char3_READ_EVT */
      break;

    case P2P_SERVER_SLNM_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN Service1Char3_NOTIFY_ENABLED_EVT */
      P2P_SERVER_APP_Context.Slnm_Notification_Status = Slnm_NOTIFICATION_ON;
      LOG_INFO_APP("SER NUM NOTIFICATION ENABLED\r\n");
      /* USER CODE END Service1Char3_NOTIFY_ENABLED_EVT */
      break;

    case P2P_SERVER_SLNM_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN Service1Char3_NOTIFY_DISABLED_EVT */
      P2P_SERVER_APP_Context.Slnm_Notification_Status = Slnm_NOTIFICATION_OFF;
      LOG_INFO_APP("SER NUM NOTIFICATION DISABLED\r\n");
      /* USER CODE END Service1Char3_NOTIFY_DISABLED_EVT */
      break;

    case P2P_SERVER_DEVLOC_READ_EVT:
      /* USER CODE BEGIN Service1Char4_READ_EVT */
			LOG_INFO_APP("DEVLOC READ\r\n");
			P2P_SERVER_Devloc_ReadUpdate();
      /* USER CODE END Service1Char4_READ_EVT */
      break;

    case P2P_SERVER_DEVLOC_WRITE_EVT:
      /* USER CODE BEGIN Service1Char4_WRITE_EVT */
				memset(DeviceLoc_Value,0,sizeof(DeviceLoc_Value));
				memcpy(DeviceLoc_Value, p_Notification->DataTransfered.p_Payload,p_Notification->DataTransfered.Length);
        LOG_INFO_APP("DEVLOC WRITE STRING = %s, LEN = %d\r\n", DeviceLoc_Value, p_Notification->DataTransfered.Length);
				DeviceLoc_write_flag =1;      
      /* USER CODE END Service1Char4_WRITE_EVT */
      break;

    case P2P_SERVER_DEVLOC_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN Service1Char4_NOTIFY_ENABLED_EVT */
      P2P_SERVER_APP_Context.Devloc_Notification_Status = Devloc_NOTIFICATION_ON;
      LOG_INFO_APP("DEVLOC NOTIFICATION ENABLED\r\n");
      /* USER CODE END Service1Char4_NOTIFY_ENABLED_EVT */
      break;

    case P2P_SERVER_DEVLOC_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN Service1Char4_NOTIFY_DISABLED_EVT */
      P2P_SERVER_APP_Context.Devloc_Notification_Status = Devloc_NOTIFICATION_OFF;
      LOG_INFO_APP("DEVLOC NOTIFICATION DISABLED\r\n");
      /* USER CODE END Service1Char4_NOTIFY_DISABLED_EVT */
      break;

    case P2P_SERVER_DS_READ_EVT:
      /* USER CODE BEGIN Service1Char5_READ_EVT */
			LOG_INFO_APP("DS READ\r\n");
			P2P_SERVER_Ds_ReadUpdate();
      /* USER CODE END Service1Char5_READ_EVT */
      break;

    case P2P_SERVER_DS_WRITE_EVT:
      /* USER CODE BEGIN Service1Char5_WRITE_EVT */
        Ds_Value = p_Notification->DataTransfered.p_Payload[0];
				LOG_INFO_APP("DSValue : 0x%02x\r\n",Ds_Value);
				Ds_write_flag =1;  
      /* USER CODE END Service1Char5_WRITE_EVT */
      break;

    case P2P_SERVER_DS_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN Service1Char5_NOTIFY_ENABLED_EVT */
      P2P_SERVER_APP_Context.Ds_Notification_Status = Ds_NOTIFICATION_ON;
      LOG_INFO_APP("DS NOTIFICATION ENABLED\n");
      /* USER CODE END Service1Char5_NOTIFY_ENABLED_EVT */
      break;

    case P2P_SERVER_DS_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN Service1Char5_NOTIFY_DISABLED_EVT */
      P2P_SERVER_APP_Context.Ds_Notification_Status = Ds_NOTIFICATION_OFF;
      LOG_INFO_APP("DS NOTIFICATION DISABLED\r\n");
      /* USER CODE END Service1Char5_NOTIFY_DISABLED_EVT */
      break;

    case P2P_SERVER_DEVMKE_READ_EVT:
      /* USER CODE BEGIN Service1Char6_READ_EVT */
			LOG_INFO_APP("DEVMAKE READ\r\n");
			P2P_SERVER_Devmke_ReadUpdate();
      /* USER CODE END Service1Char6_READ_EVT */
      break;

    case P2P_SERVER_DEVMKE_WRITE_EVT:
      /* USER CODE BEGIN Service1Char6_WRITE_EVT */
				memset(DeviceMake_Value,0,sizeof(DeviceMake_Value));
				memcpy(DeviceMake_Value, p_Notification->DataTransfered.p_Payload,p_Notification->DataTransfered.Length);
        LOG_INFO_APP("DEVMAKE WRITE STRING = %s, LEN = %d\r\n", DeviceMake_Value, p_Notification->DataTransfered.Length);
				DeviceMake_write_flag =1;      
      /* USER CODE END Service1Char6_WRITE_EVT */
      break;

    case P2P_SERVER_DEVMKE_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN Service1Char6_NOTIFY_ENABLED_EVT */
      P2P_SERVER_APP_Context.Devmke_Notification_Status = Devmke_NOTIFICATION_ON;
      LOG_INFO_APP("DEVMAKE NOTIFICATION ENABLED\r\n");
      /* USER CODE END Service1Char6_NOTIFY_ENABLED_EVT */
      break;

    case P2P_SERVER_DEVMKE_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN Service1Char6_NOTIFY_DISABLED_EVT */
      P2P_SERVER_APP_Context.Devmke_Notification_Status = Devmke_NOTIFICATION_OFF;
      LOG_INFO_APP("DEVMAKE NOTIFICATION DISABLED\r\n");
      /* USER CODE END Service1Char6_NOTIFY_DISABLED_EVT */
      break;

    case P2P_SERVER_DEVMAC_READ_EVT:
      /* USER CODE BEGIN Service1Char7_READ_EVT */
			LOG_INFO_APP("DEVMAC READ\r\n");
			P2P_SERVER_Devmac_ReadUpdate();
      /* USER CODE END Service1Char7_READ_EVT */
      break;

    case P2P_SERVER_DEVMAC_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN Service1Char7_NOTIFY_ENABLED_EVT */
      P2P_SERVER_APP_Context.Mid_Notification_Status = Devmac_NOTIFICATION_ON;
      LOG_INFO_APP("DEVMAC NOTIFICATION ENABLED\r\n");
      /* USER CODE END Service1Char7_NOTIFY_ENABLED_EVT */
      break;

    case P2P_SERVER_DEVMAC_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN Service1Char7_NOTIFY_DISABLED_EVT */
      P2P_SERVER_APP_Context.Devmac_Notification_Status = Devmac_NOTIFICATION_OFF;
      LOG_INFO_APP("DEVMAC NOTIFICATION DISABLED\r\n");
      /* USER CODE END Service1Char7_NOTIFY_DISABLED_EVT */
      break;

    case P2P_SERVER_BLESTKFW_READ_EVT:
      /* USER CODE BEGIN Service1Char8_READ_EVT */
			LOG_INFO_APP("BLESTKFW READ\r\n");
			P2P_SERVER_Blestkfw_ReadUpdate();
      /* USER CODE END Service1Char8_READ_EVT */
      break;

    case P2P_SERVER_BLESTKFW_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN Service1Char8_NOTIFY_ENABLED_EVT */
      P2P_SERVER_APP_Context.Blestkfw_Notification_Status = Blestkfw_NOTIFICATION_ON;
      LOG_INFO_APP("BLESTKFW NOTIFICATION ENABLED\r\n");
      /* USER CODE END Service1Char8_NOTIFY_ENABLED_EVT */
      break;

    case P2P_SERVER_BLESTKFW_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN Service1Char8_NOTIFY_DISABLED_EVT */
      P2P_SERVER_APP_Context.Blestkfw_Notification_Status = Blestkfw_NOTIFICATION_OFF;
      LOG_INFO_APP("BLESTKFW NOTIFICATION DISABLED\r\n");
      /* USER CODE END Service1Char8_NOTIFY_DISABLED_EVT */
      break;

    case P2P_SERVER_APPFW_READ_EVT:
      /* USER CODE BEGIN Service1Char9_READ_EVT */
			LOG_INFO_APP("APPFW READ\r\n");
			P2P_SERVER_Appfw_ReadUpdate();
      /* USER CODE END Service1Char9_READ_EVT */
      break;

    case P2P_SERVER_APPFW_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN Service1Char9_NOTIFY_ENABLED_EVT */
      P2P_SERVER_APP_Context.Appfw_Notification_Status = Appfw_NOTIFICATION_ON;
      LOG_INFO_APP("APPFW NOTIFICATION ENABLED\r\n");
      /* USER CODE END Service1Char9_NOTIFY_ENABLED_EVT */
      break;

    case P2P_SERVER_APPFW_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN Service1Char9_NOTIFY_DISABLED_EVT */
      P2P_SERVER_APP_Context.Devloc_Notification_Status = Appfw_NOTIFICATION_OFF;
      LOG_INFO_APP("APPFW NOTIFICATION DISABLED\r\n");
      /* USER CODE END Service1Char9_NOTIFY_DISABLED_EVT */
      break;

    case P2P_SERVER_ADVNAME_READ_EVT:
      /* USER CODE BEGIN Service1Char10_READ_EVT */
			LOG_INFO_APP("ADVNAME READ\r\n");
			P2P_SERVER_Advname_ReadUpdate();
      /* USER CODE END Service1Char10_READ_EVT */
      break;

    case P2P_SERVER_ADVNAME_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN Service1Char10_NOTIFY_ENABLED_EVT */
      P2P_SERVER_APP_Context.Advname_Notification_Status = Advname_NOTIFICATION_ON;
      LOG_INFO_APP("ADVNAME NOTIFICATION ENABLED\r\n");
      /* USER CODE END Service1Char10_NOTIFY_ENABLED_EVT */
      break;

    case P2P_SERVER_ADVNAME_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN Service1Char10_NOTIFY_DISABLED_EVT */
      P2P_SERVER_APP_Context.Advname_Notification_Status = Advname_NOTIFICATION_OFF;
      LOG_INFO_APP("ADVNAME NOTIFICATION DISABLED\r\n");
      /* USER CODE END Service1Char10_NOTIFY_DISABLED_EVT */
      break;

    default:
      /* USER CODE BEGIN Service1_Notification_default */

      /* USER CODE END Service1_Notification_default */
      break;
  }
  /* USER CODE BEGIN Service1_Notification_2 */

  /* USER CODE END Service1_Notification_2 */
  return;
}

void P2P_SERVER_APP_EvtRx(P2P_SERVER_APP_ConnHandleNotEvt_t *p_Notification)
{
  /* USER CODE BEGIN Service1_APP_EvtRx_1 */

  /* USER CODE END Service1_APP_EvtRx_1 */

  switch(p_Notification->EvtOpcode)
  {
    /* USER CODE BEGIN Service1_APP_EvtRx_Service1_EvtOpcode */

    /* USER CODE END Service1_APP_EvtRx_Service1_EvtOpcode */
    case P2P_SERVER_CONN_HANDLE_EVT :
      /* USER CODE BEGIN Service1_APP_CONN_HANDLE_EVT */

      /* USER CODE END Service1_APP_CONN_HANDLE_EVT */
      break;

    case P2P_SERVER_DISCON_HANDLE_EVT :
      /* USER CODE BEGIN Service1_APP_DISCON_HANDLE_EVT */
      P2P_SERVER_APP_Parameters_context_Init();
      /* USER CODE END Service1_APP_DISCON_HANDLE_EVT */
      break;

    default:
      /* USER CODE BEGIN Service1_APP_EvtRx_default */

      /* USER CODE END Service1_APP_EvtRx_default */
      break;
  }

  /* USER CODE BEGIN Service1_APP_EvtRx_2 */

  /* USER CODE END Service1_APP_EvtRx_2 */

  return;
}

void P2P_SERVER_APP_Init(void)
{
  UNUSED(P2P_SERVER_APP_Context);
  P2P_SERVER_Init();

  /* USER CODE BEGIN Service1_APP_Init */
	UTIL_SEQ_RegTask( 1U << CFG_TASK_SEND_NOTIF_ID_MID, UTIL_SEQ_RFU, P2P_SERVER_Mid_SendNotification);
  UTIL_SEQ_RegTask( 1U << CFG_TASK_SEND_NOTIF_ID_PRODNAME, UTIL_SEQ_RFU, P2P_SERVER_Prodname_SendNotification);
	UTIL_SEQ_RegTask( 1U << CFG_TASK_SEND_NOTIF_ID_SLNM, UTIL_SEQ_RFU, P2P_SERVER_Slnm_SendNotification);
	UTIL_SEQ_RegTask( 1U << CFG_TASK_SEND_NOTIF_ID_DEVLOC, UTIL_SEQ_RFU, P2P_SERVER_Devloc_SendNotification);
	UTIL_SEQ_RegTask( 1U << CFG_TASK_SEND_NOTIF_ID_DS, UTIL_SEQ_RFU, P2P_SERVER_Ds_SendNotification);
	UTIL_SEQ_RegTask( 1U << CFG_TASK_SEND_NOTIF_ID_DEVMKE, UTIL_SEQ_RFU, P2P_SERVER_Devmke_SendNotification);
	UTIL_SEQ_RegTask( 1U << CFG_TASK_SEND_NOTIF_ID_DEVMAC, UTIL_SEQ_RFU, P2P_SERVER_Devmac_SendNotification);
	UTIL_SEQ_RegTask( 1U << CFG_TASK_SEND_NOTIF_ID_BLESTKFW, UTIL_SEQ_RFU, P2P_SERVER_Blestkfw_SendNotification);
	UTIL_SEQ_RegTask( 1U << CFG_TASK_SEND_NOTIF_ID_APPFW, UTIL_SEQ_RFU, P2P_SERVER_Appfw_SendNotification);
	UTIL_SEQ_RegTask( 1U << CFG_TASK_SEND_NOTIF_ID_ADVNAME, UTIL_SEQ_RFU, P2P_SERVER_Advname_SendNotification);
  /**
   * Initialize LedButton Service
   */
	P2P_SERVER_APP_Context.Mid_Notification_Status= Mid_NOTIFICATION_OFF;
  P2P_SERVER_APP_Context.Ds_Notification_Status= Ds_NOTIFICATION_OFF;
	P2P_SERVER_APP_Context.Devloc_Notification_Status= Devloc_NOTIFICATION_OFF;
	P2P_SERVER_APP_Context.Prodname_Notification_Status = Prodname_NOTIFICATION_OFF;
	P2P_SERVER_APP_Context.Slnm_Notification_Status = Slnm_NOTIFICATION_OFF;
	P2P_SERVER_APP_Context.Devmke_Notification_Status = Devmke_NOTIFICATION_OFF;
	P2P_SERVER_APP_Context.Devmac_Notification_Status = Devmac_NOTIFICATION_OFF;
	P2P_SERVER_APP_Context.Blestkfw_Notification_Status = Blestkfw_NOTIFICATION_OFF;
	P2P_SERVER_APP_Context.Appfw_Notification_Status = Appfw_NOTIFICATION_OFF;
	P2P_SERVER_APP_Context.Advname_Notification_Status = Advname_NOTIFICATION_OFF;
  P2P_SERVER_APP_Parameters_context_Init();
  /* USER CODE END Service1_APP_Init */
  return;
}

/* USER CODE BEGIN FD */

/* USER CODE END FD */

/*************************************************************
 *
 * LOCAL FUNCTIONS
 *
 *************************************************************/
__USED void P2P_SERVER_Mid_SendNotification(void) /* Property Notification */
{
  P2P_SERVER_APP_SendInformation_t notification_on_off = Mid_NOTIFICATION_OFF;
  P2P_SERVER_Data_t p2p_server_notification_data;

  p2p_server_notification_data.p_Payload = (uint8_t*)a_P2P_SERVER_UpdateCharData;
  p2p_server_notification_data.Length = 0;

  /* USER CODE BEGIN Service1Char1_NS_1 */
  a_P2P_SERVER_UpdateCharData[0] = Mid_Value;
	LOG_INFO_APP("MID NOTIFY DATA : %02x\r\n", a_P2P_SERVER_UpdateCharData[0]);
  /* Update notification data length */
  p2p_server_notification_data.Length = (p2p_server_notification_data.Length) + 1;

  if(P2P_SERVER_APP_Context.Mid_Notification_Status == Mid_NOTIFICATION_ON)
  {
    LOG_INFO_APP("INFORM CLIENT MID\r\n");
    notification_on_off = Mid_NOTIFICATION_ON;
  }
  else
  {
    LOG_INFO_APP("CAN'T INFORM CLIENT MID - NOTIFICATION DISABLED\r\n");
  }
  /* USER CODE END Service1Char1_NS_1 */

  if (notification_on_off != Mid_NOTIFICATION_OFF)
  {
    P2P_SERVER_UpdateValue(P2P_SERVER_MID, &p2p_server_notification_data);
  }

  /* USER CODE BEGIN Service1Char1_NS_Last */

  /* USER CODE END Service1Char1_NS_Last */

  return;
}

__USED void P2P_SERVER_Prodname_SendNotification(void) /* Property Notification */
{
  P2P_SERVER_APP_SendInformation_t notification_on_off = Prodname_NOTIFICATION_OFF;
  P2P_SERVER_Data_t p2p_server_notification_data;

  p2p_server_notification_data.p_Payload = (uint8_t*)a_P2P_SERVER_UpdateCharData;
  p2p_server_notification_data.Length = 0;

  /* USER CODE BEGIN Service1Char2_NS_1 */
	memset(a_P2P_SERVER_UpdateCharData,0,sizeof(a_P2P_SERVER_UpdateCharData));
  strcpy((char*)a_P2P_SERVER_UpdateCharData, (char*)ProdName_Value);
  LOG_INFO_APP("PRODNAME NOTIFY STRING : %s\r\n", a_P2P_SERVER_UpdateCharData);
  /* Update notification data length */
  p2p_server_notification_data.Length = (p2p_server_notification_data.Length) + 64;

  if(P2P_SERVER_APP_Context.Prodname_Notification_Status == Prodname_NOTIFICATION_ON)
  {
    LOG_INFO_APP("INFORM CLIENT PRODNAME Changed\r\n");
    notification_on_off = Prodname_NOTIFICATION_ON;
  }
  else
  {
    LOG_INFO_APP("CAN'T INFORM CLIENT PRODNAME - NOTIFICATION DISABLED\r\n");
  }
  /* USER CODE END Service1Char2_NS_1 */

  if (notification_on_off != Prodname_NOTIFICATION_OFF)
  {
    P2P_SERVER_UpdateValue(P2P_SERVER_PRODNAME, &p2p_server_notification_data);
  }

  /* USER CODE BEGIN Service1Char2_NS_Last */

  /* USER CODE END Service1Char2_NS_Last */

  return;
}

__USED void P2P_SERVER_Slnm_SendNotification(void) /* Property Notification */
{
  P2P_SERVER_APP_SendInformation_t notification_on_off = Slnm_NOTIFICATION_OFF;
  P2P_SERVER_Data_t p2p_server_notification_data;

  p2p_server_notification_data.p_Payload = (uint8_t*)a_P2P_SERVER_UpdateCharData;
  p2p_server_notification_data.Length = 0;

  /* USER CODE BEGIN Service1Char3_NS_1 */
	a_P2P_SERVER_UpdateCharData[0] = (Sn_Value[0] & 0xff00)>>8;
	a_P2P_SERVER_UpdateCharData[1] = (Sn_Value[0] & 0x00ff);
	a_P2P_SERVER_UpdateCharData[2] = (Sn_Value[1] & 0xff00)>>8;
	a_P2P_SERVER_UpdateCharData[3] = (Sn_Value[1] & 0x00ff);
	a_P2P_SERVER_UpdateCharData[4] = (Sn_Value[2] & 0xff00)>>8;
	a_P2P_SERVER_UpdateCharData[5] = (Sn_Value[2] & 0x00ff);
	a_P2P_SERVER_UpdateCharData[6] = (Sn_Value[3] & 0xff00)>>8;
	a_P2P_SERVER_UpdateCharData[7] = (Sn_Value[3] & 0x00ff);
  LOG_INFO_APP("SLNM NOTIFY DATA : %02x%02x%02x%02x%02x%02x%02x%02x\r\n", 
	a_P2P_SERVER_UpdateCharData[0],a_P2P_SERVER_UpdateCharData[1],
	a_P2P_SERVER_UpdateCharData[2],a_P2P_SERVER_UpdateCharData[3],
	a_P2P_SERVER_UpdateCharData[4],a_P2P_SERVER_UpdateCharData[5],
	a_P2P_SERVER_UpdateCharData[6],a_P2P_SERVER_UpdateCharData[7]);
  /* Update notification data length */
  p2p_server_notification_data.Length = (p2p_server_notification_data.Length) + 8;

  if(P2P_SERVER_APP_Context.Prodname_Notification_Status == Slnm_NOTIFICATION_ON)
  {
    LOG_INFO_APP("INFORM CLIENT SER NUM Changed\r\n");
    notification_on_off = Slnm_NOTIFICATION_ON;
  }
  else
  {
    LOG_INFO_APP("CAN'T INFORM CLIENT SER NUM - NOTIFICATION DISABLED\r\n");
  }
  /* USER CODE END Service1Char3_NS_1 */

  if (notification_on_off != Slnm_NOTIFICATION_OFF)
  {
    P2P_SERVER_UpdateValue(P2P_SERVER_SLNM, &p2p_server_notification_data);
  }

  /* USER CODE BEGIN Service1Char3_NS_Last */

  /* USER CODE END Service1Char3_NS_Last */

  return;
}

__USED void P2P_SERVER_Devloc_SendNotification(void) /* Property Notification */
{
  P2P_SERVER_APP_SendInformation_t notification_on_off = Devloc_NOTIFICATION_OFF;
  P2P_SERVER_Data_t p2p_server_notification_data;

  p2p_server_notification_data.p_Payload = (uint8_t*)a_P2P_SERVER_UpdateCharData;
  p2p_server_notification_data.Length = 0;

  /* USER CODE BEGIN Service1Char4_NS_1 */
	memset(a_P2P_SERVER_UpdateCharData,0,sizeof(a_P2P_SERVER_UpdateCharData));
  strcpy((char*)a_P2P_SERVER_UpdateCharData, (char*)DeviceLoc_Value);
  LOG_INFO_APP("DEVLOC NOTIFY STRING : %s\r\n", a_P2P_SERVER_UpdateCharData);
  /* Update notification data length */
  p2p_server_notification_data.Length = (p2p_server_notification_data.Length) + 100;

  if(P2P_SERVER_APP_Context.Devloc_Notification_Status == Devloc_NOTIFICATION_ON)
  {
    LOG_INFO_APP("INFORM CLIENT DEVLOC Changed\r\n");
    notification_on_off = Devloc_NOTIFICATION_ON;
  }
  else
  {
    LOG_INFO_APP("CAN'T INFORM CLIENT DEVLOC- NOTIFICATION DISABLED\r\n");
  }
  /* USER CODE END Service1Char4_NS_1 */

  if (notification_on_off != Devloc_NOTIFICATION_OFF)
  {
    P2P_SERVER_UpdateValue(P2P_SERVER_DEVLOC, &p2p_server_notification_data);
  }

  /* USER CODE BEGIN Service1Char4_NS_Last */

  /* USER CODE END Service1Char4_NS_Last */

  return;
}

__USED void P2P_SERVER_Ds_SendNotification(void) /* Property Notification */
{
  P2P_SERVER_APP_SendInformation_t notification_on_off = Ds_NOTIFICATION_OFF;
  P2P_SERVER_Data_t p2p_server_notification_data;

  p2p_server_notification_data.p_Payload = (uint8_t*)a_P2P_SERVER_UpdateCharData;
  p2p_server_notification_data.Length = 0;

  /* USER CODE BEGIN Service1Char5_NS_1 */
	a_P2P_SERVER_UpdateCharData[0] = Ds_Value;
	LOG_INFO_APP("DS NOTIFY DATA : %02x\r\n", a_P2P_SERVER_UpdateCharData[0]);
  /* Update notification data length */
  p2p_server_notification_data.Length = (p2p_server_notification_data.Length) + 1;

  if(P2P_SERVER_APP_Context.Ds_Notification_Status == Ds_NOTIFICATION_ON)
  {
    LOG_INFO_APP("INFORM CLIENT DS Changed\r\n");
    notification_on_off = Ds_NOTIFICATION_ON;
  }
  else
  {
    LOG_INFO_APP(" CAN'T INFORM CLIENT - NOTIFICATION DISABLED\r\n");
  }
  /* USER CODE END Service1Char5_NS_1 */

  if (notification_on_off != Ds_NOTIFICATION_OFF)
  {
    P2P_SERVER_UpdateValue(P2P_SERVER_DS, &p2p_server_notification_data);
  }

  /* USER CODE BEGIN Service1Char5_NS_Last */

  /* USER CODE END Service1Char5_NS_Last */

  return;
}

__USED void P2P_SERVER_Devmke_SendNotification(void) /* Property Notification */
{
  P2P_SERVER_APP_SendInformation_t notification_on_off = Devmke_NOTIFICATION_OFF;
  P2P_SERVER_Data_t p2p_server_notification_data;

  p2p_server_notification_data.p_Payload = (uint8_t*)a_P2P_SERVER_UpdateCharData;
  p2p_server_notification_data.Length = 0;

  /* USER CODE BEGIN Service1Char6_NS_1 */
	memset(a_P2P_SERVER_UpdateCharData,0,sizeof(a_P2P_SERVER_UpdateCharData));
  strcpy((char*)a_P2P_SERVER_UpdateCharData, (char*)DeviceMake_Value);
  LOG_INFO_APP("DEVMAKE NOTIFY STRING : %s\r\n", a_P2P_SERVER_UpdateCharData);
  /* Update notification data length */
  p2p_server_notification_data.Length = (p2p_server_notification_data.Length) + 100;

  if(P2P_SERVER_APP_Context.Devmke_Notification_Status == Devmke_NOTIFICATION_ON)
  {
    LOG_INFO_APP("INFORM CLIENT DEVMAKE Changed\r\n");
    notification_on_off = Devmke_NOTIFICATION_ON;
  }
  else
  {
    LOG_INFO_APP("CAN'T INFORM CLIENT DEVMAKE- NOTIFICATION DISABLED\r\n");
  }
  /* USER CODE END Service1Char6_NS_1 */

  if (notification_on_off != Devmke_NOTIFICATION_OFF)
  {
    P2P_SERVER_UpdateValue(P2P_SERVER_DEVMKE, &p2p_server_notification_data);
  }

  /* USER CODE BEGIN Service1Char6_NS_Last */

  /* USER CODE END Service1Char6_NS_Last */

  return;
}

__USED void P2P_SERVER_Devmac_SendNotification(void) /* Property Notification */
{
  P2P_SERVER_APP_SendInformation_t notification_on_off = Devmac_NOTIFICATION_OFF;
  P2P_SERVER_Data_t p2p_server_notification_data;

  p2p_server_notification_data.p_Payload = (uint8_t*)a_P2P_SERVER_UpdateCharData;
  p2p_server_notification_data.Length = 0;

  /* USER CODE BEGIN Service1Char7_NS_1 */
	a_P2P_SERVER_UpdateCharData[0] = DeviceMac_Value[0];
	a_P2P_SERVER_UpdateCharData[1] = DeviceMac_Value[1];
	a_P2P_SERVER_UpdateCharData[2] = DeviceMac_Value[2];
	a_P2P_SERVER_UpdateCharData[3] = DeviceMac_Value[3];
	a_P2P_SERVER_UpdateCharData[4] = DeviceMac_Value[4];
	a_P2P_SERVER_UpdateCharData[5] = DeviceMac_Value[5];
  LOG_INFO_APP("DEVMAC NOTIFY DATA : %02x%02x%02x%02x%02x%02x\r\n", 
	a_P2P_SERVER_UpdateCharData[0],a_P2P_SERVER_UpdateCharData[1],
	a_P2P_SERVER_UpdateCharData[2],a_P2P_SERVER_UpdateCharData[3],
	a_P2P_SERVER_UpdateCharData[4],a_P2P_SERVER_UpdateCharData[5]);
  /* Update notification data length */
  p2p_server_notification_data.Length = (p2p_server_notification_data.Length) + 6;

  if(P2P_SERVER_APP_Context.Devloc_Notification_Status == Devmac_NOTIFICATION_ON)
  {
    LOG_INFO_APP("INFORM CLIENT DEVMAC Changed\r\n");
    notification_on_off = Devmac_NOTIFICATION_ON;
  }
  else
  {
    LOG_INFO_APP("CAN'T INFORM CLIENT DEVMAC- NOTIFICATION DISABLED\r\n");
  }
  /* USER CODE END Service1Char7_NS_1 */

  if (notification_on_off != Devmac_NOTIFICATION_OFF)
  {
    P2P_SERVER_UpdateValue(P2P_SERVER_DEVMAC, &p2p_server_notification_data);
  }

  /* USER CODE BEGIN Service1Char7_NS_Last */

  /* USER CODE END Service1Char7_NS_Last */

  return;
}

__USED void P2P_SERVER_Blestkfw_SendNotification(void) /* Property Notification */
{
  P2P_SERVER_APP_SendInformation_t notification_on_off = Blestkfw_NOTIFICATION_OFF;
  P2P_SERVER_Data_t p2p_server_notification_data;

  p2p_server_notification_data.p_Payload = (uint8_t*)a_P2P_SERVER_UpdateCharData;
  p2p_server_notification_data.Length = 0;

  /* USER CODE BEGIN Service1Char8_NS_1 */
	memset(a_P2P_SERVER_UpdateCharData,0,sizeof(a_P2P_SERVER_UpdateCharData));
	sprintf((char*)BleStkFw_Value,"%d.%d.%d - %d/%d/%d",Major_version,Minor_version,Bug_Fix,
                                          DD,MM,YY);
  strcpy((char*)a_P2P_SERVER_UpdateCharData, (char*)BleStkFw_Value);
  LOG_INFO_APP("BLESTKFW NOTIFY STRING : %s\r\n", a_P2P_SERVER_UpdateCharData);
  /* Update notification data length */
  p2p_server_notification_data.Length = (p2p_server_notification_data.Length) + 20;

  if(P2P_SERVER_APP_Context.Blestkfw_Notification_Status == Blestkfw_NOTIFICATION_ON)
  {
    LOG_INFO_APP("INFORM CLIENT BLESTKFW Changed\r\n");
    notification_on_off = Blestkfw_NOTIFICATION_ON;
  }
  else
  {
    LOG_INFO_APP("CAN'T INFORM CLIENT BLESTKFW- NOTIFICATION DISABLED\r\n");
  }
  /* USER CODE END Service1Char8_NS_1 */

  if (notification_on_off != Blestkfw_NOTIFICATION_OFF)
  {
    P2P_SERVER_UpdateValue(P2P_SERVER_BLESTKFW, &p2p_server_notification_data);
  }

  /* USER CODE BEGIN Service1Char8_NS_Last */

  /* USER CODE END Service1Char8_NS_Last */

  return;
}

__USED void P2P_SERVER_Appfw_SendNotification(void) /* Property Notification */
{
  P2P_SERVER_APP_SendInformation_t notification_on_off = Appfw_NOTIFICATION_OFF;
  P2P_SERVER_Data_t p2p_server_notification_data;

  p2p_server_notification_data.p_Payload = (uint8_t*)a_P2P_SERVER_UpdateCharData;
  p2p_server_notification_data.Length = 0;

  /* USER CODE BEGIN Service1Char9_NS_1 */
	memset(a_P2P_SERVER_UpdateCharData,0,sizeof(a_P2P_SERVER_UpdateCharData));
	sprintf((char*)AppFw_Value,"%d.%d.%d ",Maj_V,Min_V,BugF_V);	
  strcpy((char*)a_P2P_SERVER_UpdateCharData, (char*)AppFw_Value);
  LOG_INFO_APP("APPFW NOTIFY STRING : %s\r\n", a_P2P_SERVER_UpdateCharData);
  /* Update notification data length */
  p2p_server_notification_data.Length = (p2p_server_notification_data.Length) + 20;

  if(P2P_SERVER_APP_Context.Appfw_Notification_Status == Appfw_NOTIFICATION_ON)
  {
    LOG_INFO_APP("INFORM CLIENT APPFW Changed\r\n");
    notification_on_off = Appfw_NOTIFICATION_ON;
  }
  else
  {
    LOG_INFO_APP("CAN'T INFORM CLIENT APPFW- NOTIFICATION DISABLED\r\n");
  }
  /* USER CODE END Service1Char9_NS_1 */

  if (notification_on_off != Appfw_NOTIFICATION_OFF)
  {
    P2P_SERVER_UpdateValue(P2P_SERVER_APPFW, &p2p_server_notification_data);
  }

  /* USER CODE BEGIN Service1Char9_NS_Last */

  /* USER CODE END Service1Char9_NS_Last */

  return;
}

__USED void P2P_SERVER_Advname_SendNotification(void) /* Property Notification */
{
  P2P_SERVER_APP_SendInformation_t notification_on_off = Advname_NOTIFICATION_OFF;
  P2P_SERVER_Data_t p2p_server_notification_data;

  p2p_server_notification_data.p_Payload = (uint8_t*)a_P2P_SERVER_UpdateCharData;
  p2p_server_notification_data.Length = 0;

  /* USER CODE BEGIN Service1Char10_NS_1 */
	memset(a_P2P_SERVER_UpdateCharData,0,sizeof(a_P2P_SERVER_UpdateCharData));
  strcpy((char*)a_P2P_SERVER_UpdateCharData, (char*)AdvName_Value);
  LOG_INFO_APP("ADVNAME NOTIFY STRING : %s\r\n", a_P2P_SERVER_UpdateCharData);
  /* Update notification data length */
  p2p_server_notification_data.Length = (p2p_server_notification_data.Length) + 20;

  if(P2P_SERVER_APP_Context.Advname_Notification_Status == Advname_NOTIFICATION_ON)
  {
    LOG_INFO_APP("INFORM CLIENT ADVNAME Changed\r\n");
    notification_on_off = Advname_NOTIFICATION_ON;
  }
  else
  {
    LOG_INFO_APP("CAN'T INFORM CLIENT ADVNAME- NOTIFICATION DISABLED\r\n");
  }
  /* USER CODE END Service1Char10_NS_1 */

  if (notification_on_off != Advname_NOTIFICATION_OFF)
  {
    P2P_SERVER_UpdateValue(P2P_SERVER_ADVNAME, &p2p_server_notification_data);
  }

  /* USER CODE BEGIN Service1Char10_NS_Last */

  /* USER CODE END Service1Char10_NS_Last */

  return;
}

/* USER CODE BEGIN FD_LOCAL_FUNCTIONS */
static void P2P_SERVER_APP_Parameters_context_Init(void)
{
	//memset(DeviceLoc_Value,0,sizeof(DeviceLoc_Value));
  //memset(DeviceMake_Value,0,sizeof(DeviceMake_Value));
	return;
}

void P2P_SERVER_Mid_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  P2P_SERVER_Data_t p2p_server_readresp_data;

  p2p_server_readresp_data.p_Payload = (uint8_t*)a_P2P_SERVER_UpdateCharData;
  p2p_server_readresp_data.Length = 0;

  /* USER CODE BEGIN Service1Char1_NS_1 */
	a_P2P_SERVER_UpdateCharData[0] = Mid_Value;
	LOG_INFO_APP("MID READRESP DATA : %02x\r\n",a_P2P_SERVER_UpdateCharData[0]);
	/* Update readresp data length */
  p2p_server_readresp_data.Length = (p2p_server_readresp_data.Length) + 1;
	P2P_SERVER_UpdateValue(P2P_SERVER_MID, &p2p_server_readresp_data);
  /* USER CODE END Service1Char1_NS_1 */
  return;
}

void P2P_SERVER_Prodname_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  P2P_SERVER_Data_t p2p_server_readresp_data;

  p2p_server_readresp_data.p_Payload = (uint8_t*)a_P2P_SERVER_UpdateCharData;
  p2p_server_readresp_data.Length = 0;

  /* USER CODE BEGIN Service1Char2_NS_1 */
	memset(a_P2P_SERVER_UpdateCharData,0,sizeof(a_P2P_SERVER_UpdateCharData));
  strcpy((char*)a_P2P_SERVER_UpdateCharData, (char*)ProdName_Value);
	LOG_INFO_APP("PRODNAME READRESP DATA : %s\r\n",a_P2P_SERVER_UpdateCharData);
	/* Update readresp data length */
  p2p_server_readresp_data.Length = (p2p_server_readresp_data.Length) + 64;
	P2P_SERVER_UpdateValue(P2P_SERVER_PRODNAME, &p2p_server_readresp_data);
  /* USER CODE END Service1Char2_NS_1 */
  return;
}


void P2P_SERVER_Slnm_ReadUpdate(void) /* Property Notification */
{
  P2P_SERVER_Data_t p2p_server_readresp_data;

  p2p_server_readresp_data.p_Payload = (uint8_t*)a_P2P_SERVER_UpdateCharData;
  p2p_server_readresp_data.Length = 0;

  /* USER CODE BEGIN Service1Char3_NS_1 */
	a_P2P_SERVER_UpdateCharData[0] = (Sn_Value[0] & 0xff00)>>8;
	a_P2P_SERVER_UpdateCharData[1] = (Sn_Value[0] & 0x00ff);
	a_P2P_SERVER_UpdateCharData[2] = (Sn_Value[1] & 0xff00)>>8;
	a_P2P_SERVER_UpdateCharData[3] = (Sn_Value[1] & 0x00ff);
	a_P2P_SERVER_UpdateCharData[4] = (Sn_Value[2] & 0xff00)>>8;
	a_P2P_SERVER_UpdateCharData[5] = (Sn_Value[2] & 0x00ff);
	a_P2P_SERVER_UpdateCharData[6] = (Sn_Value[3] & 0xff00)>>8;
	a_P2P_SERVER_UpdateCharData[7] = (Sn_Value[3] & 0x00ff);
  LOG_INFO_APP("SLNM READRESP DATA : %02x%02x%02x%02x%02x%02x%02x%02x\r\n", 
	a_P2P_SERVER_UpdateCharData[0],a_P2P_SERVER_UpdateCharData[1],
	a_P2P_SERVER_UpdateCharData[2],a_P2P_SERVER_UpdateCharData[3],
	a_P2P_SERVER_UpdateCharData[4],a_P2P_SERVER_UpdateCharData[5],
	a_P2P_SERVER_UpdateCharData[6],a_P2P_SERVER_UpdateCharData[7]);
  /* Update readresp data length */
  p2p_server_readresp_data.Length = (p2p_server_readresp_data.Length) + 8;
	P2P_SERVER_UpdateValue(P2P_SERVER_SLNM, &p2p_server_readresp_data);
	 /* USER CODE END Service1Char3_NS_1 */
  return;
}

void P2P_SERVER_Devloc_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  P2P_SERVER_Data_t p2p_server_readresp_data;

  p2p_server_readresp_data.p_Payload = (uint8_t*)a_P2P_SERVER_UpdateCharData;
  p2p_server_readresp_data.Length = 0;

  /* USER CODE BEGIN Service1Char4_NS_1 */
	memset(a_P2P_SERVER_UpdateCharData,0,sizeof(a_P2P_SERVER_UpdateCharData));
  strcpy((char*)a_P2P_SERVER_UpdateCharData, (char*)DeviceLoc_Value);
	LOG_INFO_APP("DEVLOC READRESP DATA : %s\r\n",a_P2P_SERVER_UpdateCharData);
	/* Update readresp data length */
  p2p_server_readresp_data.Length = (p2p_server_readresp_data.Length) + 100;
	P2P_SERVER_UpdateValue(P2P_SERVER_DEVLOC, &p2p_server_readresp_data);
  /* USER CODE END Service1Char4_NS_1 */
  return;
}


void P2P_SERVER_Ds_ReadUpdate(void) /* Property ReadResponseUpdate */
{ 
  P2P_SERVER_Data_t p2p_server_readresp_data;

  p2p_server_readresp_data.p_Payload = (uint8_t*)a_P2P_SERVER_UpdateCharData;
  p2p_server_readresp_data.Length = 0;

  /* USER CODE BEGIN Service1Char5_NS_1 */
	a_P2P_SERVER_UpdateCharData[0] = Ds_Value;
	LOG_INFO_APP("DS READRESP DATA : %02x\r\n",a_P2P_SERVER_UpdateCharData[0]);
	/* Update readresp data length */
  p2p_server_readresp_data.Length = (p2p_server_readresp_data.Length) + 1;
	P2P_SERVER_UpdateValue(P2P_SERVER_DS, &p2p_server_readresp_data);
  /* USER CODE END Service1Char5_NS_1 */
  return;
}

void P2P_SERVER_Devmke_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  P2P_SERVER_Data_t p2p_server_readresp_data;

  p2p_server_readresp_data.p_Payload = (uint8_t*)a_P2P_SERVER_UpdateCharData;
  p2p_server_readresp_data.Length = 0;

  /* USER CODE BEGIN Service1Char6_NS_1 */
	memset(a_P2P_SERVER_UpdateCharData,0,sizeof(a_P2P_SERVER_UpdateCharData));
  strcpy((char*)a_P2P_SERVER_UpdateCharData, (char*)DeviceMake_Value);
	LOG_INFO_APP("DEVMKE READRESP DATA : %s\r\n",a_P2P_SERVER_UpdateCharData);
	/* Update readresp data length */
  p2p_server_readresp_data.Length = (p2p_server_readresp_data.Length) + 100;
	P2P_SERVER_UpdateValue(P2P_SERVER_DEVMKE, &p2p_server_readresp_data);
  /* USER CODE END Service1Char6_NS_1 */
  return;
}


__USED void P2P_SERVER_Devmac_ReadUpdate(void) /* Property Notification */
{
  P2P_SERVER_Data_t p2p_server_readresp_data;

  p2p_server_readresp_data.p_Payload = (uint8_t*)a_P2P_SERVER_UpdateCharData;
  p2p_server_readresp_data.Length = 0;

  /* USER CODE BEGIN Service1Char7_NS_1 */
	a_P2P_SERVER_UpdateCharData[0] = DeviceMac_Value[0];
	a_P2P_SERVER_UpdateCharData[1] = DeviceMac_Value[1];
	a_P2P_SERVER_UpdateCharData[2] = DeviceMac_Value[2];
	a_P2P_SERVER_UpdateCharData[3] = DeviceMac_Value[3];
	a_P2P_SERVER_UpdateCharData[4] = DeviceMac_Value[4];
	a_P2P_SERVER_UpdateCharData[5] = DeviceMac_Value[5];
  LOG_INFO_APP("DEVMAC READRESP DATA : %02x%02x%02x%02x%02x%02x\r\n", 
	a_P2P_SERVER_UpdateCharData[0],a_P2P_SERVER_UpdateCharData[1],
	a_P2P_SERVER_UpdateCharData[2],a_P2P_SERVER_UpdateCharData[3],
	a_P2P_SERVER_UpdateCharData[4],a_P2P_SERVER_UpdateCharData[5]);
  /* Update readresp data length */
  p2p_server_readresp_data.Length = (p2p_server_readresp_data.Length) + 6;
	P2P_SERVER_UpdateValue(P2P_SERVER_DEVMAC, &p2p_server_readresp_data);
  /* USER CODE END Service1Char7_NS_1 */
  return;
}

void P2P_SERVER_Blestkfw_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  P2P_SERVER_Data_t p2p_server_readresp_data;

  p2p_server_readresp_data.p_Payload = (uint8_t*)a_P2P_SERVER_UpdateCharData;
  p2p_server_readresp_data.Length = 0;

  /* USER CODE BEGIN Service1Char8_NS_1 */
	memset(a_P2P_SERVER_UpdateCharData,0,sizeof(a_P2P_SERVER_UpdateCharData));
	sprintf((char*)BleStkFw_Value,"%d.%d.%d - %d/%d/%d",Major_version,Minor_version,Bug_Fix,
                                          DD,MM,YY);
  strcpy((char*)a_P2P_SERVER_UpdateCharData, (char*)BleStkFw_Value);
	LOG_INFO_APP("BLESTKFW READRESP DATA : %s\r\n",a_P2P_SERVER_UpdateCharData);
	/* Update readresp data length */
  p2p_server_readresp_data.Length = (p2p_server_readresp_data.Length) + 20;
	P2P_SERVER_UpdateValue(P2P_SERVER_BLESTKFW, &p2p_server_readresp_data);
  /* USER CODE END Service1Char8_NS_1 */
  return;
}


void P2P_SERVER_Appfw_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  P2P_SERVER_Data_t p2p_server_readresp_data;

  p2p_server_readresp_data.p_Payload = (uint8_t*)a_P2P_SERVER_UpdateCharData;
  p2p_server_readresp_data.Length = 0;

  /* USER CODE BEGIN Service1Char9_NS_1 */
	memset(a_P2P_SERVER_UpdateCharData,0,sizeof(a_P2P_SERVER_UpdateCharData));
	sprintf((char*)AppFw_Value,"%d.%d.%d ",Maj_V,Min_V,BugF_V);	
  strcpy((char*)a_P2P_SERVER_UpdateCharData, (char*)AppFw_Value);
	LOG_INFO_APP("APPFW READRESP DATA : %s\r\n",a_P2P_SERVER_UpdateCharData);
	/* Update readresp data length */
  p2p_server_readresp_data.Length = (p2p_server_readresp_data.Length) + 20;
	P2P_SERVER_UpdateValue(P2P_SERVER_APPFW, &p2p_server_readresp_data);
  /* USER CODE END Service1Char9_NS_1 */
  return;
}


void P2P_SERVER_Advname_ReadUpdate(void) /* Property ReadResponseUpdate */
{
  P2P_SERVER_Data_t p2p_server_readresp_data;

  p2p_server_readresp_data.p_Payload = (uint8_t*)a_P2P_SERVER_UpdateCharData;
  p2p_server_readresp_data.Length = 0;

  /* USER CODE BEGIN Service1Char10_NS_1 */
	memset(a_P2P_SERVER_UpdateCharData,0,sizeof(a_P2P_SERVER_UpdateCharData));
  strcpy((char*)a_P2P_SERVER_UpdateCharData, (char*)AdvName_Value);
	LOG_INFO_APP("ADVNAME READRESP DATA : %s\r\n",a_P2P_SERVER_UpdateCharData);
	/* Update readresp data length */
  p2p_server_readresp_data.Length = (p2p_server_readresp_data.Length) + 20;
	P2P_SERVER_UpdateValue(P2P_SERVER_ADVNAME, &p2p_server_readresp_data);
  /* USER CODE END Service1Char10_NS_1 */
  return;
}


/* USER CODE END FD_LOCAL_FUNCTIONS */
