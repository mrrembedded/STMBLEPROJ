/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    CSP_ER_BLE.c
  * @author  MCD Application Team
  * @brief   CSP_ER_BLE definition.
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
#include "log_module.h"
#include "csp_er_ble.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/

/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

typedef struct{
  uint16_t  Csp_er_bleSvcHdle;                  /**< Csp_er_ble Service Handle */
  uint16_t  Csp_Mod_Sta_Id_RwCharHdle;                  /**< CSP_MOD_STA_ID_RW Characteristic Handle */
  uint16_t  Csp_Proc_Para_Sel_RwCharHdle;                  /**< CSP_PROC_PARA_SEL_RW Characteristic Handle */
  uint16_t  Csp_Lvdt_Sensor_Scale_Type_RwCharHdle;                  /**< CSP_LVDT_SENSOR_SCALE_TYPE_RW Characteristic Handle */
  uint16_t  Csp_Pid_Val_For_Pos_Aft_En_RwCharHdle;                  /**< CSP_PID_VAL_FOR_POS_AFT_EN_RW Characteristic Handle */
  uint16_t  Csp_Baud_Rate_RwCharHdle;                  /**< CSP_BAUD_RATE_RW Characteristic Handle */
  uint16_t  Csp_Parity_Stop_Bit_RwCharHdle;                  /**< CSP_PARITY_STOP_BIT_RW Characteristic Handle */
  uint16_t  Csp_Svp_Pid_Up_P_Val_RwCharHdle;                  /**< CSP_SVP_PID_UP_P_VAL_RW Characteristic Handle */
  uint16_t  Csp_Svp_Pid_Up_I_Val_RwCharHdle;                  /**< CSP_SVP_PID_UP_I_VAL_RW Characteristic Handle */
  uint16_t  Csp_Svp_Pid_Up_D_Val_RwCharHdle;                  /**< CSP_SVP_PID_UP_D_VAL_RW Characteristic Handle */
  uint16_t  Csp_Svp_Pid_Up_I_Time_RwCharHdle;                  /**< CSP_SVP_PID_UP_I_TIME_RW Characteristic Handle */
  uint16_t  Csp_Svp_Pid_Down_P_Val_RwCharHdle;                  /**< CSP_SVP_PID_DOWN_P_VAL_RW Characteristic Handle */
  uint16_t  Csp_Svp_Pid_Down_I_Val_RwCharHdle;                  /**< CSP_SVP_PID_DOWN_I_VAL_RW Characteristic Handle */
  uint16_t  Csp_Svp_Pid_Down_D_Val_RwCharHdle;                  /**< CSP_SVP_PID_DOWN_D_VAL_RW Characteristic Handle */
  uint16_t  Csp_Svp_Pid_Down_I_Time_RwCharHdle;                  /**< CSP_SVP_PID_DOWN_I_TIME_RW Characteristic Handle */
  uint16_t  Csp_Ptr_P1_Min_RwCharHdle;                  /**< CSP_PTR_P1_MIN_RW Characteristic Handle */
  uint16_t  Csp_Ptr_P1_Max_RwCharHdle;                  /**< CSP_PTR_P1_MAX_RW Characteristic Handle */
  uint16_t  Csp_Ptr_P2_Min_RwCharHdle;                  /**< CSP_PTR_P2_MIN_RW Characteristic Handle */
  uint16_t  Csp_Ptr_P2_Max_RwCharHdle;                  /**< CSP_PTR_P2_MAX_RW Characteristic Handle */
/* USER CODE BEGIN Context */
  /* Place holder for Characteristic Descriptors Handle*/

/* USER CODE END Context */
}CSP_ER_BLE_Context_t;

/* Private defines -----------------------------------------------------------*/
#define UUID_128_SUPPORTED  1

#if (UUID_128_SUPPORTED == 1)
#define BM_UUID_LENGTH  UUID_TYPE_128
#else
#define BM_UUID_LENGTH  UUID_TYPE_16
#endif

#define BM_REQ_CHAR_SIZE    (3)

/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* External variables --------------------------------------------------------*/
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Private macros ------------------------------------------------------------*/
#define CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET         2
#define CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET              1
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
static const uint16_t SizeCsp_Mod_Sta_Id_Rw = 1;
static const uint16_t SizeCsp_Proc_Para_Sel_Rw = 1;
static const uint16_t SizeCsp_Lvdt_Sensor_Scale_Type_Rw = 1;
static const uint16_t SizeCsp_Pid_Val_For_Pos_Aft_En_Rw = 1;
static const uint16_t SizeCsp_Baud_Rate_Rw = 1;
static const uint16_t SizeCsp_Parity_Stop_Bit_Rw = 1;
static const uint16_t SizeCsp_Svp_Pid_Up_P_Val_Rw = 4;
static const uint16_t SizeCsp_Svp_Pid_Up_I_Val_Rw = 4;
static const uint16_t SizeCsp_Svp_Pid_Up_D_Val_Rw = 4;
static const uint16_t SizeCsp_Svp_Pid_Up_I_Time_Rw = 4;
static const uint16_t SizeCsp_Svp_Pid_Down_P_Val_Rw = 4;
static const uint16_t SizeCsp_Svp_Pid_Down_I_Val_Rw = 4;
static const uint16_t SizeCsp_Svp_Pid_Down_D_Val_Rw = 4;
static const uint16_t SizeCsp_Svp_Pid_Down_I_Time_Rw = 4;
static const uint16_t SizeCsp_Ptr_P1_Min_Rw = 4;
static const uint16_t SizeCsp_Ptr_P1_Max_Rw = 4;
static const uint16_t SizeCsp_Ptr_P2_Min_Rw = 4;
static const uint16_t SizeCsp_Ptr_P2_Max_Rw = 4;

static CSP_ER_BLE_Context_t CSP_ER_BLE_Context;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static SVCCTL_EvtAckStatus_t CSP_ER_BLE_EventHandler(void *p_pckt);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Functions Definition ------------------------------------------------------*/
/* USER CODE BEGIN PFD */

/* USER CODE END PFD */

/* Private functions ----------------------------------------------------------*/

#define COPY_UUID_128(uuid_struct, uuid_15, uuid_14, uuid_13, uuid_12, uuid_11, uuid_10, uuid_9, uuid_8, uuid_7, uuid_6, uuid_5, uuid_4, uuid_3, uuid_2, uuid_1, uuid_0) \
do {\
    uuid_struct[0] = uuid_0; uuid_struct[1] = uuid_1; uuid_struct[2] = uuid_2; uuid_struct[3] = uuid_3; \
    uuid_struct[4] = uuid_4; uuid_struct[5] = uuid_5; uuid_struct[6] = uuid_6; uuid_struct[7] = uuid_7; \
    uuid_struct[8] = uuid_8; uuid_struct[9] = uuid_9; uuid_struct[10] = uuid_10; uuid_struct[11] = uuid_11; \
    uuid_struct[12] = uuid_12; uuid_struct[13] = uuid_13; uuid_struct[14] = uuid_14; uuid_struct[15] = uuid_15; \
}while(0)

/*
 The following 128bits UUIDs have been generated from the random UUID
 generator:
 F364020000B04240BA5005CA45BF8ABC: Service 128bits UUID
 F364020100B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364020200B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364020300B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364020400B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364020500B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364020600B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364020700B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364020800B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364020900B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364020A00B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364020B00B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364020C00B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364020D00B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364020E00B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364020F00B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364021000B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364021100B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364021200B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 */
#define COPY_CSP_ER_BLE_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x02,0x00,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CSP_MOD_STA_ID_RW_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x02,0x01,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CSP_PROC_PARA_SEL_RW_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x02,0x02,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CSP_LVDT_SENSOR_SCALE_TYPE_RW_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x02,0x03,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CSP_PID_VAL_FOR_POS_AFT_EN_RW_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x02,0x04,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CSP_BAUD_RATE_RW_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x02,0x05,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CSP_PARITY_STOP_BIT_RW_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x02,0x06,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CSP_SVP_PID_UP_P_VAL_RW_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x02,0x07,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CSP_SVP_PID_UP_I_VAL_RW_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x02,0x08,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CSP_SVP_PID_UP_D_VAL_RW_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x02,0x09,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CSP_SVP_PID_UP_I_TIME_RW_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x02,0x0a,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CSP_SVP_PID_DOWN_P_VAL_RW_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x02,0x0b,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CSP_SVP_PID_DOWN_I_VAL_RW_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x02,0x0c,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CSP_SVP_PID_DOWN_D_VAL_RW_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x02,0x0d,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CSP_SVP_PID_DOWN_I_TIME_RW_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x02,0x0e,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CSP_PTR_P1_MIN_RW_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x02,0x0f,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CSP_PTR_P1_MAX_RW_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x02,0x10,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CSP_PTR_P2_MIN_RW_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x02,0x11,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CSP_PTR_P2_MAX_RW_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x02,0x12,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)

/* USER CODE BEGIN PF */

/* USER CODE END PF */

/**
 * @brief  Event handler
 * @param  p_Event: Address of the buffer holding the p_Event
 * @retval Ack: Return whether the p_Event has been managed or not
 */
static SVCCTL_EvtAckStatus_t CSP_ER_BLE_EventHandler(void *p_Event)
{
  SVCCTL_EvtAckStatus_t return_value;
  hci_event_pckt *p_event_pckt;
  evt_blecore_aci *p_blecore_evt;
  aci_gatt_attribute_modified_event_rp0 *p_attribute_modified;
  aci_gatt_read_permit_req_event_rp0    *p_read_req;
  CSP_ER_BLE_NotificationEvt_t                 notification;
  /* USER CODE BEGIN Service3_EventHandler_1 */

  /* USER CODE END Service3_EventHandler_1 */

  return_value = SVCCTL_EvtNotAck;
  p_event_pckt = (hci_event_pckt *)(((hci_uart_pckt*)p_Event)->data);

  switch(p_event_pckt->evt)
  {
    case HCI_VENDOR_SPECIFIC_DEBUG_EVT_CODE:
      p_blecore_evt = (evt_blecore_aci*)p_event_pckt->data;
      switch(p_blecore_evt->ecode)
      {
        case ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE:
        {
          /* USER CODE BEGIN EVT_BLUE_GATT_ATTRIBUTE_MODIFIED_BEGIN */

          /* USER CODE END EVT_BLUE_GATT_ATTRIBUTE_MODIFIED_BEGIN */
          p_attribute_modified = (aci_gatt_attribute_modified_event_rp0*)p_blecore_evt->data;
          notification.ConnectionHandle         = p_attribute_modified->Connection_Handle;
          notification.AttributeHandle          = p_attribute_modified->Attr_Handle;
          notification.DataTransfered.Length    = p_attribute_modified->Attr_Data_Length;
          notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
          if(p_attribute_modified->Attr_Handle == (CSP_ER_BLE_Context.Csp_Mod_Sta_Id_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CSP_ER_BLE_CSP_MOD_STA_ID_RW_WRITE_EVT;
            /* USER CODE BEGIN Service3_Char_1_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CSP_MOD_STA_ID_RW CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service3_Char_1_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CSP_ER_BLE_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CSP_ER_BLE_Context.Csp_Proc_Para_Sel_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CSP_ER_BLE_CSP_PROC_PARA_SEL_RW_WRITE_EVT;
            /* USER CODE BEGIN Service3_Char_2_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CSP_PROC_PARA_SEL_RW CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service3_Char_2_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CSP_ER_BLE_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CSP_ER_BLE_Context.Csp_Lvdt_Sensor_Scale_Type_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CSP_ER_BLE_CSP_LVDT_SENSOR_SCALE_TYPE_RW_WRITE_EVT;
            /* USER CODE BEGIN Service3_Char_3_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CSP_LVDT_SENSOR_SCALE_TYPE_RW CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service3_Char_3_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CSP_ER_BLE_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CSP_ER_BLE_Context.Csp_Pid_Val_For_Pos_Aft_En_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CSP_ER_BLE_CSP_PID_VAL_FOR_POS_AFT_EN_RW_WRITE_EVT;
            /* USER CODE BEGIN Service3_Char_4_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CSP_PID_VAL_FOR_POS_AFT_EN_RW CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service3_Char_4_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CSP_ER_BLE_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CSP_ER_BLE_Context.Csp_Baud_Rate_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CSP_ER_BLE_CSP_BAUD_RATE_RW_WRITE_EVT;
            /* USER CODE BEGIN Service3_Char_5_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CSP_BAUD_RATE_RW CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service3_Char_5_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CSP_ER_BLE_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CSP_ER_BLE_Context.Csp_Parity_Stop_Bit_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CSP_ER_BLE_CSP_PARITY_STOP_BIT_RW_WRITE_EVT;
            /* USER CODE BEGIN Service3_Char_6_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CSP_PARITY_STOP_BIT_RW CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service3_Char_6_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CSP_ER_BLE_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CSP_ER_BLE_Context.Csp_Svp_Pid_Up_P_Val_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CSP_ER_BLE_CSP_SVP_PID_UP_P_VAL_RW_WRITE_EVT;
            /* USER CODE BEGIN Service3_Char_7_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CSP_SVP_PID_UP_P_VAL_RW CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service3_Char_7_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CSP_ER_BLE_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CSP_ER_BLE_Context.Csp_Svp_Pid_Up_I_Val_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CSP_ER_BLE_CSP_SVP_PID_UP_I_VAL_RW_WRITE_EVT;
            /* USER CODE BEGIN Service3_Char_8_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CSP_SVP_PID_UP_I_VAL_RW CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service3_Char_8_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CSP_ER_BLE_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CSP_ER_BLE_Context.Csp_Svp_Pid_Up_D_Val_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CSP_ER_BLE_CSP_SVP_PID_UP_D_VAL_RW_WRITE_EVT;
            /* USER CODE BEGIN Service3_Char_9_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CSP_SVP_PID_UP_D_VAL_RW CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service3_Char_9_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CSP_ER_BLE_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CSP_ER_BLE_Context.Csp_Svp_Pid_Up_I_Time_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CSP_ER_BLE_CSP_SVP_PID_UP_I_TIME_RW_WRITE_EVT;
            /* USER CODE BEGIN Service3_Char_10_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CSP_SVP_PID_UP_I_TIME_RW CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service3_Char_10_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CSP_ER_BLE_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CSP_ER_BLE_Context.Csp_Svp_Pid_Down_P_Val_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CSP_ER_BLE_CSP_SVP_PID_DOWN_P_VAL_RW_WRITE_EVT;
            /* USER CODE BEGIN Service3_Char_11_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CSP_SVP_PID_DOWN_P_VAL_RW CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service3_Char_11_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CSP_ER_BLE_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CSP_ER_BLE_Context.Csp_Svp_Pid_Down_I_Val_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CSP_ER_BLE_CSP_SVP_PID_DOWN_I_VAL_RW_WRITE_EVT;
            /* USER CODE BEGIN Service3_Char_12_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CSP_SVP_PID_DOWN_I_VAL_RW CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service3_Char_12_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CSP_ER_BLE_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CSP_ER_BLE_Context.Csp_Svp_Pid_Down_D_Val_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CSP_ER_BLE_CSP_SVP_PID_DOWN_D_VAL_RW_WRITE_EVT;
            /* USER CODE BEGIN Service3_Char_13_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CSP_SVP_PID_DOWN_D_VAL_RW CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service3_Char_13_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CSP_ER_BLE_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CSP_ER_BLE_Context.Csp_Svp_Pid_Down_I_Time_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CSP_ER_BLE_CSP_SVP_PID_DOWN_I_TIME_RW_WRITE_EVT;
            /* USER CODE BEGIN Service3_Char_14_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CSP_SVP_PID_DOWN_I_TIME_RW CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service3_Char_14_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CSP_ER_BLE_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CSP_ER_BLE_Context.Csp_Ptr_P1_Min_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CSP_ER_BLE_CSP_PTR_P1_MIN_RW_WRITE_EVT;
            /* USER CODE BEGIN Service3_Char_15_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CSP_PTR_P1_MIN_RW CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service3_Char_15_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CSP_ER_BLE_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CSP_ER_BLE_Context.Csp_Ptr_P1_Max_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CSP_ER_BLE_CSP_PTR_P1_MAX_RW_WRITE_EVT;
            /* USER CODE BEGIN Service3_Char_16_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CSP_PTR_P1_MAX_RW CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service3_Char_16_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CSP_ER_BLE_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CSP_ER_BLE_Context.Csp_Ptr_P2_Min_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CSP_ER_BLE_CSP_PTR_P2_MIN_RW_WRITE_EVT;
            /* USER CODE BEGIN Service3_Char_17_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CSP_PTR_P2_MIN_RW CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service3_Char_17_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CSP_ER_BLE_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CSP_ER_BLE_Context.Csp_Ptr_P2_Max_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CSP_ER_BLE_CSP_PTR_P2_MAX_RW_WRITE_EVT;
            /* USER CODE BEGIN Service3_Char_18_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CSP_PTR_P2_MAX_RW CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service3_Char_18_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CSP_ER_BLE_Notification(&notification);
          }

          /* USER CODE BEGIN EVT_BLUE_GATT_ATTRIBUTE_MODIFIED_END */

          /* USER CODE END EVT_BLUE_GATT_ATTRIBUTE_MODIFIED_END */
          break;/* ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
        }
        case ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE :
        {
          /* USER CODE BEGIN EVT_BLUE_GATT_READ_PERMIT_REQ_BEGIN */

          /* USER CODE END EVT_BLUE_GATT_READ_PERMIT_REQ_BEGIN */
          p_read_req = (aci_gatt_read_permit_req_event_rp0*)p_blecore_evt->data;
          if(p_read_req->Attribute_Handle == (CSP_ER_BLE_Context.Csp_Mod_Sta_Id_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service3_Char_1_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service3_Char_1_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service3_Char_1_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CSP_ER_BLE_CSP_MOD_STA_ID_RW_READ_EVT;
						CSP_ER_BLE_Notification(&notification);
            /*USER CODE END Service3_Char_1_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CSP_ER_BLE_Context.Csp_Proc_Para_Sel_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service3_Char_2_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service3_Char_2_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service3_Char_2_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CSP_ER_BLE_CSP_PROC_PARA_SEL_RW_READ_EVT;
						CSP_ER_BLE_Notification(&notification);
            /*USER CODE END Service3_Char_2_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CSP_ER_BLE_Context.Csp_Lvdt_Sensor_Scale_Type_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service3_Char_3_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service3_Char_3_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service3_Char_3_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CSP_ER_BLE_CSP_LVDT_SENSOR_SCALE_TYPE_RW_READ_EVT;
						CSP_ER_BLE_Notification(&notification);
            /*USER CODE END Service3_Char_3_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CSP_ER_BLE_Context.Csp_Pid_Val_For_Pos_Aft_En_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service3_Char_4_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service3_Char_4_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service3_Char_4_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CSP_ER_BLE_CSP_PID_VAL_FOR_POS_AFT_EN_RW_READ_EVT;
						CSP_ER_BLE_Notification(&notification);
            /*USER CODE END Service3_Char_4_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CSP_ER_BLE_Context.Csp_Baud_Rate_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service3_Char_5_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service3_Char_5_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service3_Char_5_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CSP_ER_BLE_CSP_BAUD_RATE_RW_READ_EVT;
						CSP_ER_BLE_Notification(&notification);
            /*USER CODE END Service3_Char_5_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CSP_ER_BLE_Context.Csp_Parity_Stop_Bit_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service3_Char_6_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */
			
            /*USER CODE END Service3_Char_6_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service3_Char_6_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CSP_ER_BLE_CSP_PARITY_STOP_BIT_RW_READ_EVT;
						CSP_ER_BLE_Notification(&notification);
            /*USER CODE END Service3_Char_6_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CSP_ER_BLE_Context.Csp_Svp_Pid_Up_P_Val_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service3_Char_7_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service3_Char_7_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service3_Char_7_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CSP_ER_BLE_CSP_SVP_PID_UP_P_VAL_RW_READ_EVT;
						CSP_ER_BLE_Notification(&notification);
            /*USER CODE END Service3_Char_7_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CSP_ER_BLE_Context.Csp_Svp_Pid_Up_I_Val_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service3_Char_8_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service3_Char_8_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service3_Char_8_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CSP_ER_BLE_CSP_SVP_PID_UP_I_VAL_RW_READ_EVT;
						CSP_ER_BLE_Notification(&notification);
            /*USER CODE END Service3_Char_8_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CSP_ER_BLE_Context.Csp_Svp_Pid_Up_D_Val_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service3_Char_9_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service3_Char_9_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service3_Char_9_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CSP_ER_BLE_CSP_SVP_PID_UP_D_VAL_RW_READ_EVT;
						CSP_ER_BLE_Notification(&notification);
            /*USER CODE END Service3_Char_9_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CSP_ER_BLE_Context.Csp_Svp_Pid_Up_I_Time_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service3_Char_10_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service3_Char_10_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service3_Char_10_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CSP_ER_BLE_CSP_SVP_PID_UP_I_TIME_RW_READ_EVT;
						CSP_ER_BLE_Notification(&notification);
            /*USER CODE END Service3_Char_10_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CSP_ER_BLE_Context.Csp_Svp_Pid_Down_P_Val_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service3_Char_11_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service3_Char_11_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service3_Char_11_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CSP_ER_BLE_CSP_SVP_PID_DOWN_P_VAL_RW_READ_EVT;
						CSP_ER_BLE_Notification(&notification);
            /*USER CODE END Service3_Char_11_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CSP_ER_BLE_Context.Csp_Svp_Pid_Down_I_Val_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service3_Char_12_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service3_Char_12_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service3_Char_12_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CSP_ER_BLE_CSP_SVP_PID_DOWN_I_VAL_RW_READ_EVT;
						CSP_ER_BLE_Notification(&notification);
            /*USER CODE END Service3_Char_12_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CSP_ER_BLE_Context.Csp_Svp_Pid_Down_D_Val_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service3_Char_13_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service3_Char_13_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service3_Char_13_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CSP_ER_BLE_CSP_SVP_PID_DOWN_D_VAL_RW_READ_EVT;
						CSP_ER_BLE_Notification(&notification);
            /*USER CODE END Service3_Char_13_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CSP_ER_BLE_Context.Csp_Svp_Pid_Down_I_Time_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service3_Char_14_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service3_Char_14_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service3_Char_14_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CSP_ER_BLE_CSP_SVP_PID_DOWN_I_TIME_RW_READ_EVT;
						CSP_ER_BLE_Notification(&notification);
            /*USER CODE END Service3_Char_14_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CSP_ER_BLE_Context.Csp_Ptr_P1_Min_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service3_Char_15_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service3_Char_15_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service3_Char_15_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CSP_ER_BLE_CSP_PTR_P1_MIN_RW_READ_EVT;
						CSP_ER_BLE_Notification(&notification);
            /*USER CODE END Service3_Char_15_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CSP_ER_BLE_Context.Csp_Ptr_P1_Max_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service3_Char_16_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service3_Char_16_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service3_Char_16_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CSP_ER_BLE_CSP_PTR_P1_MAX_RW_READ_EVT;
						CSP_ER_BLE_Notification(&notification);
            /*USER CODE END Service3_Char_16_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CSP_ER_BLE_Context.Csp_Ptr_P2_Min_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service3_Char_17_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service3_Char_17_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service3_Char_17_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CSP_ER_BLE_CSP_PTR_P2_MIN_RW_READ_EVT;
						CSP_ER_BLE_Notification(&notification);
            /*USER CODE END Service3_Char_17_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CSP_ER_BLE_Context.Csp_Ptr_P2_Max_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service3_Char_18_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service3_Char_18_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service3_Char_18_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CSP_ER_BLE_CSP_PTR_P2_MAX_RW_READ_EVT;
						CSP_ER_BLE_Notification(&notification);
            /*USER CODE END Service3_Char_18_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }

          /* USER CODE BEGIN EVT_BLUE_GATT_READ_PERMIT_REQ_END */

          /* USER CODE END EVT_BLUE_GATT_READ_PERMIT_REQ_END */
          break;/* ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE */
        }
        case ACI_GATT_WRITE_PERMIT_REQ_VSEVT_CODE:
        {
          /* USER CODE BEGIN EVT_BLUE_GATT_WRITE_PERMIT_REQ_BEGIN */

          /* USER CODE END EVT_BLUE_GATT_WRITE_PERMIT_REQ_BEGIN */

          /* USER CODE BEGIN EVT_BLUE_GATT_WRITE_PERMIT_REQ_END */

          /* USER CODE END EVT_BLUE_GATT_WRITE_PERMIT_REQ_END */
          break;/* ACI_GATT_WRITE_PERMIT_REQ_VSEVT_CODE */
        }
        case ACI_GATT_TX_POOL_AVAILABLE_VSEVT_CODE:
        {
          aci_gatt_tx_pool_available_event_rp0 *p_tx_pool_available_event;
          p_tx_pool_available_event = (aci_gatt_tx_pool_available_event_rp0 *) p_blecore_evt->data;
          UNUSED(p_tx_pool_available_event);

          /* USER CODE BEGIN ACI_GATT_TX_POOL_AVAILABLE_VSEVT_CODE */

          /* USER CODE END ACI_GATT_TX_POOL_AVAILABLE_VSEVT_CODE */
          break;/* ACI_GATT_TX_POOL_AVAILABLE_VSEVT_CODE*/
        }
        case ACI_ATT_EXCHANGE_MTU_RESP_VSEVT_CODE:
        {
          aci_att_exchange_mtu_resp_event_rp0 *p_exchange_mtu;
          p_exchange_mtu = (aci_att_exchange_mtu_resp_event_rp0 *)  p_blecore_evt->data;
          UNUSED(p_exchange_mtu);

          /* USER CODE BEGIN ACI_ATT_EXCHANGE_MTU_RESP_VSEVT_CODE */

          /* USER CODE END ACI_ATT_EXCHANGE_MTU_RESP_VSEVT_CODE */
          break;/* ACI_ATT_EXCHANGE_MTU_RESP_VSEVT_CODE */
        }
        /* USER CODE BEGIN BLECORE_EVT */

        /* USER CODE END BLECORE_EVT */
        default:
          /* USER CODE BEGIN EVT_DEFAULT */

          /* USER CODE END EVT_DEFAULT */
          break;
      }
      /* USER CODE BEGIN EVT_VENDOR */

      /* USER CODE END EVT_VENDOR */
      break; /* HCI_VENDOR_SPECIFIC_DEBUG_EVT_CODE */

      /* USER CODE BEGIN EVENT_PCKT_CASES */

      /* USER CODE END EVENT_PCKT_CASES */

    default:
      /* USER CODE BEGIN EVENT_PCKT */

      /* USER CODE END EVENT_PCKT */
      break;
  }

  /* USER CODE BEGIN Service3_EventHandler_2 */

  /* USER CODE END Service3_EventHandler_2 */

  return(return_value);
}/* end CSP_ER_BLE_EventHandler */

/* Public functions ----------------------------------------------------------*/

/**
 * @brief  Service initialization
 * @param  None
 * @retval None
 */
void CSP_ER_BLE_Init(void)
{
  Char_UUID_t  uuid;
  tBleStatus ret;
  uint8_t max_attr_record;

  /* USER CODE BEGIN SVCCTL_InitService3Svc_1 */

  /* USER CODE END SVCCTL_InitService3Svc_1 */

  /**
   *  Register the event handler to the BLE controller
   */
  SVCCTL_RegisterSvcHandler(CSP_ER_BLE_EventHandler);

  /**
   * CSP_ER_BLE
   *
   * Max_Attribute_Records = 1 + 2*18 + 1*no_of_char_with_notify_or_indicate_property + 1*no_of_char_with_broadcast_property
   * service_max_attribute_record = 1 for CSP_ER_BLE +
   *                                2 for CSP_MOD_STA_ID_RW +
   *                                2 for CSP_PROC_PARA_SEL_RW +
   *                                2 for CSP_LVDT_SENSOR_SCALE_TYPE_RW +
   *                                2 for CSP_PID_VAL_FOR_POS_AFT_EN_RW +
   *                                2 for CSP_BAUD_RATE_RW +
   *                                2 for CSP_PARITY_STOP_BIT_RW +
   *                                2 for CSP_SVP_PID_UP_P_VAL_RW +
   *                                2 for CSP_SVP_PID_UP_I_VAL_RW +
   *                                2 for CSP_SVP_PID_UP_D_VAL_RW +
   *                                2 for CSP_SVP_PID_UP_I_TIME_RW +
   *                                2 for CSP_SVP_PID_DOWN_P_VAL_RW +
   *                                2 for CSP_SVP_PID_DOWN_I_VAL_RW +
   *                                2 for CSP_SVP_PID_DOWN_D_VAL_RW +
   *                                2 for CSP_SVP_PID_DOWN_I_TIME_RW +
   *                                2 for CSP_PTR_P1_MIN_RW +
   *                                2 for CSP_PTR_P1_MAX_RW +
   *                                2 for CSP_PTR_P2_MIN_RW +
   *                                2 for CSP_PTR_P2_MAX_RW +
   *                              = 37
   * This value doesn't take into account number of descriptors manually added
   * In case of descriptors added, please update the max_attr_record value accordingly in the next SVCCTL_InitService User Section
   */
  max_attr_record = 37;

  /* USER CODE BEGIN SVCCTL_InitService */
  /* max_attr_record to be updated if descriptors have been added */

  /* USER CODE END SVCCTL_InitService */

  COPY_CSP_ER_BLE_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_service(UUID_TYPE_128,
                             (Service_UUID_t *) &uuid,
                             PRIMARY_SERVICE,
                             max_attr_record,
                             &(CSP_ER_BLE_Context.Csp_er_bleSvcHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_service command: CSP_ER_BLE, error code: 0x%x \n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_service command: Csp_er_bleSvcHdle = 0x%04X\n",CSP_ER_BLE_Context.Csp_er_bleSvcHdle);
  }

  /**
   * CSP_MOD_STA_ID_RW
   */
  COPY_CSP_MOD_STA_ID_RW_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CSP_ER_BLE_Context.Csp_er_bleSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCsp_Mod_Sta_Id_Rw,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CSP_ER_BLE_Context.Csp_Mod_Sta_Id_RwCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CSP_MOD_STA_ID_RW, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Csp_Mod_Sta_Id_RwCharHdle = 0x%04X\n",CSP_ER_BLE_Context.Csp_Mod_Sta_Id_RwCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService3Char1 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService3Char1 */

  /**
   * CSP_PROC_PARA_SEL_RW
   */
  COPY_CSP_PROC_PARA_SEL_RW_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CSP_ER_BLE_Context.Csp_er_bleSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCsp_Proc_Para_Sel_Rw,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CSP_ER_BLE_Context.Csp_Proc_Para_Sel_RwCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CSP_PROC_PARA_SEL_RW, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Csp_Proc_Para_Sel_RwCharHdle = 0x%04X\n",CSP_ER_BLE_Context.Csp_Proc_Para_Sel_RwCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService3Char2 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService3Char2 */

  /**
   * CSP_LVDT_SENSOR_SCALE_TYPE_RW
   */
  COPY_CSP_LVDT_SENSOR_SCALE_TYPE_RW_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CSP_ER_BLE_Context.Csp_er_bleSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCsp_Lvdt_Sensor_Scale_Type_Rw,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CSP_ER_BLE_Context.Csp_Lvdt_Sensor_Scale_Type_RwCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CSP_LVDT_SENSOR_SCALE_TYPE_RW, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Csp_Lvdt_Sensor_Scale_Type_RwCharHdle = 0x%04X\n",CSP_ER_BLE_Context.Csp_Lvdt_Sensor_Scale_Type_RwCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService3Char3 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService3Char3 */

  /**
   * CSP_PID_VAL_FOR_POS_AFT_EN_RW
   */
  COPY_CSP_PID_VAL_FOR_POS_AFT_EN_RW_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CSP_ER_BLE_Context.Csp_er_bleSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCsp_Pid_Val_For_Pos_Aft_En_Rw,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CSP_ER_BLE_Context.Csp_Pid_Val_For_Pos_Aft_En_RwCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CSP_PID_VAL_FOR_POS_AFT_EN_RW, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Csp_Pid_Val_For_Pos_Aft_En_RwCharHdle = 0x%04X\n",CSP_ER_BLE_Context.Csp_Pid_Val_For_Pos_Aft_En_RwCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService3Char4 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService3Char4 */

  /**
   * CSP_BAUD_RATE_RW
   */
  COPY_CSP_BAUD_RATE_RW_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CSP_ER_BLE_Context.Csp_er_bleSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCsp_Baud_Rate_Rw,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CSP_ER_BLE_Context.Csp_Baud_Rate_RwCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CSP_BAUD_RATE_RW, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Csp_Baud_Rate_RwCharHdle = 0x%04X\n",CSP_ER_BLE_Context.Csp_Baud_Rate_RwCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService3Char5 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService3Char5 */

  /**
   * CSP_PARITY_STOP_BIT_RW
   */
  COPY_CSP_PARITY_STOP_BIT_RW_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CSP_ER_BLE_Context.Csp_er_bleSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCsp_Parity_Stop_Bit_Rw,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CSP_ER_BLE_Context.Csp_Parity_Stop_Bit_RwCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CSP_PARITY_STOP_BIT_RW, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Csp_Parity_Stop_Bit_RwCharHdle = 0x%04X\n",CSP_ER_BLE_Context.Csp_Parity_Stop_Bit_RwCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService3Char6 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService3Char6 */

  /**
   * CSP_SVP_PID_UP_P_VAL_RW
   */
  COPY_CSP_SVP_PID_UP_P_VAL_RW_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CSP_ER_BLE_Context.Csp_er_bleSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCsp_Svp_Pid_Up_P_Val_Rw,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CSP_ER_BLE_Context.Csp_Svp_Pid_Up_P_Val_RwCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CSP_SVP_PID_UP_P_VAL_RW, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Csp_Svp_Pid_Up_P_Val_RwCharHdle = 0x%04X\n",CSP_ER_BLE_Context.Csp_Svp_Pid_Up_P_Val_RwCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService3Char7 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService3Char7 */

  /**
   * CSP_SVP_PID_UP_I_VAL_RW
   */
  COPY_CSP_SVP_PID_UP_I_VAL_RW_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CSP_ER_BLE_Context.Csp_er_bleSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCsp_Svp_Pid_Up_I_Val_Rw,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CSP_ER_BLE_Context.Csp_Svp_Pid_Up_I_Val_RwCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CSP_SVP_PID_UP_I_VAL_RW, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Csp_Svp_Pid_Up_I_Val_RwCharHdle = 0x%04X\n",CSP_ER_BLE_Context.Csp_Svp_Pid_Up_I_Val_RwCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService3Char8 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService3Char8 */

  /**
   * CSP_SVP_PID_UP_D_VAL_RW
   */
  COPY_CSP_SVP_PID_UP_D_VAL_RW_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CSP_ER_BLE_Context.Csp_er_bleSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCsp_Svp_Pid_Up_D_Val_Rw,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CSP_ER_BLE_Context.Csp_Svp_Pid_Up_D_Val_RwCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CSP_SVP_PID_UP_D_VAL_RW, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Csp_Svp_Pid_Up_D_Val_RwCharHdle = 0x%04X\n",CSP_ER_BLE_Context.Csp_Svp_Pid_Up_D_Val_RwCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService3Char9 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService3Char9 */

  /**
   * CSP_SVP_PID_UP_I_TIME_RW
   */
  COPY_CSP_SVP_PID_UP_I_TIME_RW_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CSP_ER_BLE_Context.Csp_er_bleSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCsp_Svp_Pid_Up_I_Time_Rw,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CSP_ER_BLE_Context.Csp_Svp_Pid_Up_I_Time_RwCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CSP_SVP_PID_UP_I_TIME_RW, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Csp_Svp_Pid_Up_I_Time_RwCharHdle = 0x%04X\n",CSP_ER_BLE_Context.Csp_Svp_Pid_Up_I_Time_RwCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService3Char10 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService3Char10 */

  /**
   * CSP_SVP_PID_DOWN_P_VAL_RW
   */
  COPY_CSP_SVP_PID_DOWN_P_VAL_RW_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CSP_ER_BLE_Context.Csp_er_bleSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCsp_Svp_Pid_Down_P_Val_Rw,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CSP_ER_BLE_Context.Csp_Svp_Pid_Down_P_Val_RwCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CSP_SVP_PID_DOWN_P_VAL_RW, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Csp_Svp_Pid_Down_P_Val_RwCharHdle = 0x%04X\n",CSP_ER_BLE_Context.Csp_Svp_Pid_Down_P_Val_RwCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService3Char11 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService3Char11 */

  /**
   * CSP_SVP_PID_DOWN_I_VAL_RW
   */
  COPY_CSP_SVP_PID_DOWN_I_VAL_RW_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CSP_ER_BLE_Context.Csp_er_bleSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCsp_Svp_Pid_Down_I_Val_Rw,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CSP_ER_BLE_Context.Csp_Svp_Pid_Down_I_Val_RwCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CSP_SVP_PID_DOWN_I_VAL_RW, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Csp_Svp_Pid_Down_I_Val_RwCharHdle = 0x%04X\n",CSP_ER_BLE_Context.Csp_Svp_Pid_Down_I_Val_RwCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService3Char12 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService3Char12 */

  /**
   * CSP_SVP_PID_DOWN_D_VAL_RW
   */
  COPY_CSP_SVP_PID_DOWN_D_VAL_RW_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CSP_ER_BLE_Context.Csp_er_bleSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCsp_Svp_Pid_Down_D_Val_Rw,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CSP_ER_BLE_Context.Csp_Svp_Pid_Down_D_Val_RwCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CSP_SVP_PID_DOWN_D_VAL_RW, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Csp_Svp_Pid_Down_D_Val_RwCharHdle = 0x%04X\n",CSP_ER_BLE_Context.Csp_Svp_Pid_Down_D_Val_RwCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService3Char13 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService3Char13 */

  /**
   * CSP_SVP_PID_DOWN_I_TIME_RW
   */
  COPY_CSP_SVP_PID_DOWN_I_TIME_RW_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CSP_ER_BLE_Context.Csp_er_bleSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCsp_Svp_Pid_Down_I_Time_Rw,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CSP_ER_BLE_Context.Csp_Svp_Pid_Down_I_Time_RwCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CSP_SVP_PID_DOWN_I_TIME_RW, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Csp_Svp_Pid_Down_I_Time_RwCharHdle = 0x%04X\n",CSP_ER_BLE_Context.Csp_Svp_Pid_Down_I_Time_RwCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService3Char14 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService3Char14 */

  /**
   * CSP_PTR_P1_MIN_RW
   */
  COPY_CSP_PTR_P1_MIN_RW_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CSP_ER_BLE_Context.Csp_er_bleSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCsp_Ptr_P1_Min_Rw,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CSP_ER_BLE_Context.Csp_Ptr_P1_Min_RwCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CSP_PTR_P1_MIN_RW, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Csp_Ptr_P1_Min_RwCharHdle = 0x%04X\n",CSP_ER_BLE_Context.Csp_Ptr_P1_Min_RwCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService3Char15 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService3Char15 */

  /**
   * CSP_PTR_P1_MAX_RW
   */
  COPY_CSP_PTR_P1_MAX_RW_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CSP_ER_BLE_Context.Csp_er_bleSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCsp_Ptr_P1_Max_Rw,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CSP_ER_BLE_Context.Csp_Ptr_P1_Max_RwCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CSP_PTR_P1_MAX_RW, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Csp_Ptr_P1_Max_RwCharHdle = 0x%04X\n",CSP_ER_BLE_Context.Csp_Ptr_P1_Max_RwCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService3Char16 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService3Char16 */

  /**
   * CSP_PTR_P2_MIN_RW
   */
  COPY_CSP_PTR_P2_MIN_RW_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CSP_ER_BLE_Context.Csp_er_bleSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCsp_Ptr_P2_Min_Rw,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CSP_ER_BLE_Context.Csp_Ptr_P2_Min_RwCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CSP_PTR_P2_MIN_RW, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Csp_Ptr_P2_Min_RwCharHdle = 0x%04X\n",CSP_ER_BLE_Context.Csp_Ptr_P2_Min_RwCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService3Char17 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService3Char17 */

  /**
   * CSP_PTR_P2_MAX_RW
   */
  COPY_CSP_PTR_P2_MAX_RW_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CSP_ER_BLE_Context.Csp_er_bleSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCsp_Ptr_P2_Max_Rw,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CSP_ER_BLE_Context.Csp_Ptr_P2_Max_RwCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CSP_PTR_P2_MAX_RW, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Csp_Ptr_P2_Max_RwCharHdle = 0x%04X\n",CSP_ER_BLE_Context.Csp_Ptr_P2_Max_RwCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService3Char18 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService3Char18 */

  /* USER CODE BEGIN SVCCTL_InitService3Svc_2 */

  /* USER CODE END SVCCTL_InitService3Svc_2 */

  return;
}

/**
 * @brief  Characteristic update
 * @param  CharOpcode: Characteristic identifier
 * @param  pData: Structure holding data to update
 *
 */
tBleStatus CSP_ER_BLE_UpdateValue(CSP_ER_BLE_CharOpcode_t CharOpcode, CSP_ER_BLE_Data_t *pData)
{
  tBleStatus ret = BLE_STATUS_INVALID_PARAMS;
  /* USER CODE BEGIN Service3_App_Update_Char_1 */

  /* USER CODE END Service3_App_Update_Char_1 */

  switch(CharOpcode)
  {
    case CSP_ER_BLE_CSP_MOD_STA_ID_RW:
      ret = aci_gatt_update_char_value(CSP_ER_BLE_Context.Csp_er_bleSvcHdle,
                                       CSP_ER_BLE_Context.Csp_Mod_Sta_Id_RwCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CSP_MOD_STA_ID_RW command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CSP_MOD_STA_ID_RW command\n");
      }
      /* USER CODE BEGIN Service3_Char_Value_1 */

      /* USER CODE END Service3_Char_Value_1 */
      break;

    case CSP_ER_BLE_CSP_PROC_PARA_SEL_RW:
      ret = aci_gatt_update_char_value(CSP_ER_BLE_Context.Csp_er_bleSvcHdle,
                                       CSP_ER_BLE_Context.Csp_Proc_Para_Sel_RwCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CSP_PROC_PARA_SEL_RW command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CSP_PROC_PARA_SEL_RW command\n");
      }
      /* USER CODE BEGIN Service3_Char_Value_2 */

      /* USER CODE END Service3_Char_Value_2 */
      break;

    case CSP_ER_BLE_CSP_LVDT_SENSOR_SCALE_TYPE_RW:
      ret = aci_gatt_update_char_value(CSP_ER_BLE_Context.Csp_er_bleSvcHdle,
                                       CSP_ER_BLE_Context.Csp_Lvdt_Sensor_Scale_Type_RwCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CSP_LVDT_SENSOR_SCALE_TYPE_RW command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CSP_LVDT_SENSOR_SCALE_TYPE_RW command\n");
      }
      /* USER CODE BEGIN Service3_Char_Value_3 */

      /* USER CODE END Service3_Char_Value_3 */
      break;

    case CSP_ER_BLE_CSP_PID_VAL_FOR_POS_AFT_EN_RW:
      ret = aci_gatt_update_char_value(CSP_ER_BLE_Context.Csp_er_bleSvcHdle,
                                       CSP_ER_BLE_Context.Csp_Pid_Val_For_Pos_Aft_En_RwCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CSP_PID_VAL_FOR_POS_AFT_EN_RW command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CSP_PID_VAL_FOR_POS_AFT_EN_RW command\n");
      }
      /* USER CODE BEGIN Service3_Char_Value_4 */

      /* USER CODE END Service3_Char_Value_4 */
      break;

    case CSP_ER_BLE_CSP_BAUD_RATE_RW:
      ret = aci_gatt_update_char_value(CSP_ER_BLE_Context.Csp_er_bleSvcHdle,
                                       CSP_ER_BLE_Context.Csp_Baud_Rate_RwCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CSP_BAUD_RATE_RW command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CSP_BAUD_RATE_RW command\n");
      }
      /* USER CODE BEGIN Service3_Char_Value_5 */

      /* USER CODE END Service3_Char_Value_5 */
      break;

    case CSP_ER_BLE_CSP_PARITY_STOP_BIT_RW:
      ret = aci_gatt_update_char_value(CSP_ER_BLE_Context.Csp_er_bleSvcHdle,
                                       CSP_ER_BLE_Context.Csp_Parity_Stop_Bit_RwCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CSP_PARITY_STOP_BIT_RW command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CSP_PARITY_STOP_BIT_RW command\n");
      }
      /* USER CODE BEGIN Service3_Char_Value_6 */

      /* USER CODE END Service3_Char_Value_6 */
      break;

    case CSP_ER_BLE_CSP_SVP_PID_UP_P_VAL_RW:
      ret = aci_gatt_update_char_value(CSP_ER_BLE_Context.Csp_er_bleSvcHdle,
                                       CSP_ER_BLE_Context.Csp_Svp_Pid_Up_P_Val_RwCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CSP_SVP_PID_UP_P_VAL_RW command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CSP_SVP_PID_UP_P_VAL_RW command\n");
      }
      /* USER CODE BEGIN Service3_Char_Value_7 */

      /* USER CODE END Service3_Char_Value_7 */
      break;

    case CSP_ER_BLE_CSP_SVP_PID_UP_I_VAL_RW:
      ret = aci_gatt_update_char_value(CSP_ER_BLE_Context.Csp_er_bleSvcHdle,
                                       CSP_ER_BLE_Context.Csp_Svp_Pid_Up_I_Val_RwCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CSP_SVP_PID_UP_I_VAL_RW command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CSP_SVP_PID_UP_I_VAL_RW command\n");
      }
      /* USER CODE BEGIN Service3_Char_Value_8 */

      /* USER CODE END Service3_Char_Value_8 */
      break;

    case CSP_ER_BLE_CSP_SVP_PID_UP_D_VAL_RW:
      ret = aci_gatt_update_char_value(CSP_ER_BLE_Context.Csp_er_bleSvcHdle,
                                       CSP_ER_BLE_Context.Csp_Svp_Pid_Up_D_Val_RwCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CSP_SVP_PID_UP_D_VAL_RW command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CSP_SVP_PID_UP_D_VAL_RW command\n");
      }
      /* USER CODE BEGIN Service3_Char_Value_9 */

      /* USER CODE END Service3_Char_Value_9 */
      break;

    case CSP_ER_BLE_CSP_SVP_PID_UP_I_TIME_RW:
      ret = aci_gatt_update_char_value(CSP_ER_BLE_Context.Csp_er_bleSvcHdle,
                                       CSP_ER_BLE_Context.Csp_Svp_Pid_Up_I_Time_RwCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CSP_SVP_PID_UP_I_TIME_RW command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CSP_SVP_PID_UP_I_TIME_RW command\n");
      }
      /* USER CODE BEGIN Service3_Char_Value_10 */

      /* USER CODE END Service3_Char_Value_10 */
      break;

    case CSP_ER_BLE_CSP_SVP_PID_DOWN_P_VAL_RW:
      ret = aci_gatt_update_char_value(CSP_ER_BLE_Context.Csp_er_bleSvcHdle,
                                       CSP_ER_BLE_Context.Csp_Svp_Pid_Down_P_Val_RwCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CSP_SVP_PID_DOWN_P_VAL_RW command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CSP_SVP_PID_DOWN_P_VAL_RW command\n");
      }
      /* USER CODE BEGIN Service3_Char_Value_11 */

      /* USER CODE END Service3_Char_Value_11 */
      break;

    case CSP_ER_BLE_CSP_SVP_PID_DOWN_I_VAL_RW:
      ret = aci_gatt_update_char_value(CSP_ER_BLE_Context.Csp_er_bleSvcHdle,
                                       CSP_ER_BLE_Context.Csp_Svp_Pid_Down_I_Val_RwCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CSP_SVP_PID_DOWN_I_VAL_RW command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CSP_SVP_PID_DOWN_I_VAL_RW command\n");
      }
      /* USER CODE BEGIN Service3_Char_Value_12 */

      /* USER CODE END Service3_Char_Value_12 */
      break;

    case CSP_ER_BLE_CSP_SVP_PID_DOWN_D_VAL_RW:
      ret = aci_gatt_update_char_value(CSP_ER_BLE_Context.Csp_er_bleSvcHdle,
                                       CSP_ER_BLE_Context.Csp_Svp_Pid_Down_D_Val_RwCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CSP_SVP_PID_DOWN_D_VAL_RW command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CSP_SVP_PID_DOWN_D_VAL_RW command\n");
      }
      /* USER CODE BEGIN Service3_Char_Value_13 */

      /* USER CODE END Service3_Char_Value_13 */
      break;

    case CSP_ER_BLE_CSP_SVP_PID_DOWN_I_TIME_RW:
      ret = aci_gatt_update_char_value(CSP_ER_BLE_Context.Csp_er_bleSvcHdle,
                                       CSP_ER_BLE_Context.Csp_Svp_Pid_Down_I_Time_RwCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CSP_SVP_PID_DOWN_I_TIME_RW command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CSP_SVP_PID_DOWN_I_TIME_RW command\n");
      }
      /* USER CODE BEGIN Service3_Char_Value_14 */

      /* USER CODE END Service3_Char_Value_14 */
      break;

    case CSP_ER_BLE_CSP_PTR_P1_MIN_RW:
      ret = aci_gatt_update_char_value(CSP_ER_BLE_Context.Csp_er_bleSvcHdle,
                                       CSP_ER_BLE_Context.Csp_Ptr_P1_Min_RwCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CSP_PTR_P1_MIN_RW command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CSP_PTR_P1_MIN_RW command\n");
      }
      /* USER CODE BEGIN Service3_Char_Value_15 */

      /* USER CODE END Service3_Char_Value_15 */
      break;

    case CSP_ER_BLE_CSP_PTR_P1_MAX_RW:
      ret = aci_gatt_update_char_value(CSP_ER_BLE_Context.Csp_er_bleSvcHdle,
                                       CSP_ER_BLE_Context.Csp_Ptr_P1_Max_RwCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CSP_PTR_P1_MAX_RW command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CSP_PTR_P1_MAX_RW command\n");
      }
      /* USER CODE BEGIN Service3_Char_Value_16 */

      /* USER CODE END Service3_Char_Value_16 */
      break;

    case CSP_ER_BLE_CSP_PTR_P2_MIN_RW:
      ret = aci_gatt_update_char_value(CSP_ER_BLE_Context.Csp_er_bleSvcHdle,
                                       CSP_ER_BLE_Context.Csp_Ptr_P2_Min_RwCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CSP_PTR_P2_MIN_RW command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CSP_PTR_P2_MIN_RW command\n");
      }
      /* USER CODE BEGIN Service3_Char_Value_17 */

      /* USER CODE END Service3_Char_Value_17 */
      break;

    case CSP_ER_BLE_CSP_PTR_P2_MAX_RW:
      ret = aci_gatt_update_char_value(CSP_ER_BLE_Context.Csp_er_bleSvcHdle,
                                       CSP_ER_BLE_Context.Csp_Ptr_P2_Max_RwCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CSP_PTR_P2_MAX_RW command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CSP_PTR_P2_MAX_RW command\n");
      }
      /* USER CODE BEGIN Service3_Char_Value_18 */

      /* USER CODE END Service3_Char_Value_18 */
      break;

    default:
      break;
  }

  /* USER CODE BEGIN Service3_App_Update_Char_2 */

  /* USER CODE END Service3_App_Update_Char_2 */

  return ret;
}
