/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    CUPS_ER_BLE.c
  * @author  MCD Application Team
  * @brief   CUPS_ER_BLE definition.
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
#include "cups_er_ble.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/

/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

typedef struct{
  uint16_t  Cups_er_bleSvcHdle;                  /**< Cups_er_ble Service Handle */
  uint16_t  Cups_Unitp2T2_RwCharHdle;                  /**< CUPS_UNITP2T2_RW Characteristic Handle */
  uint16_t  Cups_Pos_Span_RwCharHdle;                  /**< CUPS_POS_SPAN_RW Characteristic Handle */
  uint16_t  Cups_Valve_Con_Dir_RwCharHdle;                  /**< CUPS_VALVE_CON_DIR_RW Characteristic Handle */
  uint16_t  Cups_Sel_Valve_Friction_RwCharHdle;                  /**< CUPS_SEL_VALVE_FRICTION_RW Characteristic Handle */
  uint16_t  Cups_Sel_Valve_Char_Suppo_RwCharHdle;                  /**< CUPS_SEL_VALVE_CHAR_SUPPO_RW Characteristic Handle */
  uint16_t  Cups_Con_Valve_Pil_Valve_RwCharHdle;                  /**< CUPS_CON_VALVE_PIL_VALVE_RW Characteristic Handle */
  uint16_t  Cups_Unitp1T1_RwCharHdle;                  /**< CUPS_UNITP1T1_RW Characteristic Handle */
  uint16_t  Cups_Setpoint_P2_RwCharHdle;                  /**< CUPS_SETPOINT_P2_RW Characteristic Handle */
  uint16_t  Cups_Time_Const_RwCharHdle;                  /**< CUPS_TIME_CONST_RW Characteristic Handle */
  uint16_t  Cups_Pid_P_Val_RwCharHdle;                  /**< CUPS_PID_P_VAL_RW Characteristic Handle */
  uint16_t  Cups_Pid_I_Val_RwCharHdle;                  /**< CUPS_PID_I_VAL_RW Characteristic Handle */
  uint16_t  Cups_Pid_D_Val_RwCharHdle;                  /**< CUPS_PID_D_VAL_RW Characteristic Handle */
  uint16_t  Cups_Pid_I_Time_RwCharHdle;                  /**< CUPS_PID_I_TIME_RW Characteristic Handle */
  uint16_t  Cups_P1_Min_Range_RwCharHdle;                  /**< CUPS_P1_MIN_RANGE_RW Characteristic Handle */
  uint16_t  Cups_P1_Max_Range_RwCharHdle;                  /**< CUPS_P1_MAX_RANGE_RW Characteristic Handle */
  uint16_t  Cups_Valve_Const_Kv_RwCharHdle;                  /**< CUPS_VALVE_CONST_KV_RW Characteristic Handle */
  uint16_t  Cups_Flow_Factor_RwCharHdle;                  /**< CUPS_FLOW_FACTOR_RW Characteristic Handle */
  uint16_t  Cups_Pressure_En_DisCharHdle;                  /**< CUPS_PRESSURE_EN_DIS Characteristic Handle */
/* USER CODE BEGIN Context */
  /* Place holder for Characteristic Descriptors Handle*/

/* USER CODE END Context */
}CUPS_ER_BLE_Context_t;

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
static const uint16_t SizeCups_Unitp2T2_Rw = 1;
static const uint16_t SizeCups_Pos_Span_Rw = 1;
static const uint16_t SizeCups_Valve_Con_Dir_Rw = 1;
static const uint16_t SizeCups_Sel_Valve_Friction_Rw = 1;
static const uint16_t SizeCups_Sel_Valve_Char_Suppo_Rw = 1;
static const uint16_t SizeCups_Con_Valve_Pil_Valve_Rw = 1;
static const uint16_t SizeCups_Unitp1T1_Rw = 1;
static const uint16_t SizeCups_Setpoint_P2_Rw = 4;
static const uint16_t SizeCups_Time_Const_Rw = 4;
static const uint16_t SizeCups_Pid_P_Val_Rw = 4;
static const uint16_t SizeCups_Pid_I_Val_Rw = 4;
static const uint16_t SizeCups_Pid_D_Val_Rw = 4;
static const uint16_t SizeCups_Pid_I_Time_Rw = 4;
static const uint16_t SizeCups_P1_Min_Range_Rw = 4;
static const uint16_t SizeCups_P1_Max_Range_Rw = 4;
static const uint16_t SizeCups_Valve_Const_Kv_Rw = 4;
static const uint16_t SizeCups_Flow_Factor_Rw = 4;
static const uint16_t SizeCups_Pressure_En_Dis = 2;

static CUPS_ER_BLE_Context_t CUPS_ER_BLE_Context;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static SVCCTL_EvtAckStatus_t CUPS_ER_BLE_EventHandler(void *p_pckt);

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
 F364010000B04240BA5005CA45BF8ABC: Service 128bits UUID
 F364010100B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364010200B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364010300B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364010400B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364010500B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364010600B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364010700B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364010800B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364010900B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364010A00B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364010B00B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364010C00B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364010D00B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364010E00B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364010F00B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364011000B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364011100B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364011200B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 */
#define COPY_CUPS_ER_BLE_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x01,0x00,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CUPS_UNITP2T2_RW_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x01,0x01,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CUPS_POS_SPAN_RW_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x01,0x02,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CUPS_VALVE_CON_DIR_RW_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x01,0x03,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CUPS_SEL_VALVE_FRICTION_RW_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x01,0x04,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CUPS_SEL_VALVE_CHAR_SUPPO_RW_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x01,0x05,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CUPS_CON_VALVE_PIL_VALVE_RW_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x01,0x06,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CUPS_UNITP1T1_RW_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x01,0x07,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CUPS_SETPOINT_P2_RW_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x01,0x08,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CUPS_TIME_CONST_RW_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x01,0x09,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CUPS_PID_P_VAL_RW_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x01,0x0a,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CUPS_PID_I_VAL_RW_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x01,0x0b,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CUPS_PID_D_VAL_RW_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x01,0x0c,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CUPS_PID_I_TIME_RW_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x01,0x0d,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CUPS_P1_MIN_RANGE_RW_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x01,0x0e,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CUPS_P1_MAX_RANGE_RW_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x01,0x0f,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CUPS_VALVE_CONST_KV_RW_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x01,0x10,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CUPS_FLOW_FACTOR_RW_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x01,0x11,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CUPS_PRESSURE_EN_DIS_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x01,0x12,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)

/* USER CODE BEGIN PF */

/* USER CODE END PF */

/**
 * @brief  Event handler
 * @param  p_Event: Address of the buffer holding the p_Event
 * @retval Ack: Return whether the p_Event has been managed or not
 */
static SVCCTL_EvtAckStatus_t CUPS_ER_BLE_EventHandler(void *p_Event)
{
  SVCCTL_EvtAckStatus_t return_value;
  hci_event_pckt *p_event_pckt;
  evt_blecore_aci *p_blecore_evt;
  aci_gatt_attribute_modified_event_rp0 *p_attribute_modified;
  aci_gatt_read_permit_req_event_rp0    *p_read_req;
  CUPS_ER_BLE_NotificationEvt_t                 notification;
  /* USER CODE BEGIN Service2_EventHandler_1 */

  /* USER CODE END Service2_EventHandler_1 */

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
          if(p_attribute_modified->Attr_Handle == (CUPS_ER_BLE_Context.Cups_Setpoint_P2_RwCharHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN Service2_Char_8 */

            /* USER CODE END Service2_Char_8 */
            switch(p_attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN Service2_Char_8_attribute_modified */

              /* USER CODE END Service2_Char_8_attribute_modified */

              /* Disabled Notification management */
              case (0x00):
                /* USER CODE BEGIN Service2_Char_8_Disabled_BEGIN */

                /* USER CODE END Service2_Char_8_Disabled_BEGIN */
                notification.EvtOpcode = CUPS_ER_BLE_CUPS_SETPOINT_P2_RW_NOTIFY_DISABLED_EVT;
                CUPS_ER_BLE_Notification(&notification);
                /* USER CODE BEGIN Service2_Char_8_Disabled_END */

                /* USER CODE END Service2_Char_8_Disabled_END */
                break;

              /* Enabled Notification management */
              case GATT_CHAR_UPDATE_SEND_NOTIFICATION:
                /* USER CODE BEGIN Service2_Char_8_COMSVC_Notification_BEGIN */

                /* USER CODE END Service2_Char_8_COMSVC_Notification_BEGIN */
                notification.EvtOpcode = CUPS_ER_BLE_CUPS_SETPOINT_P2_RW_NOTIFY_ENABLED_EVT;
                CUPS_ER_BLE_Notification(&notification);
                /* USER CODE BEGIN Service2_Char_8_COMSVC_Notification_END */

                /* USER CODE END Service2_Char_8_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN Service2_Char_8_default */

                /* USER CODE END Service2_Char_8_default */
                break;
            }
          }

          else if(p_attribute_modified->Attr_Handle == (CUPS_ER_BLE_Context.Cups_Unitp2T2_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CUPS_ER_BLE_CUPS_UNITP2T2_RW_WRITE_EVT;
            /* USER CODE BEGIN Service2_Char_1_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CUPS_UNITP2T2_RW CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service2_Char_1_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CUPS_ER_BLE_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CUPS_ER_BLE_Context.Cups_Pos_Span_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CUPS_ER_BLE_CUPS_POS_SPAN_RW_WRITE_EVT;
            /* USER CODE BEGIN Service2_Char_2_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CUPS_POS_SPAN_RW CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service2_Char_2_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CUPS_ER_BLE_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CUPS_ER_BLE_Context.Cups_Valve_Con_Dir_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CUPS_ER_BLE_CUPS_VALVE_CON_DIR_RW_WRITE_EVT;
            /* USER CODE BEGIN Service2_Char_3_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CUPS_VALVE_CON_DIR_RW CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service2_Char_3_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CUPS_ER_BLE_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CUPS_ER_BLE_Context.Cups_Sel_Valve_Friction_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CUPS_ER_BLE_CUPS_SEL_VALVE_FRICTION_RW_WRITE_EVT;
            /* USER CODE BEGIN Service2_Char_4_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CUPS_SEL_VALVE_FRICTION_RW CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service2_Char_4_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CUPS_ER_BLE_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CUPS_ER_BLE_Context.Cups_Sel_Valve_Char_Suppo_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CUPS_ER_BLE_CUPS_SEL_VALVE_CHAR_SUPPO_RW_WRITE_EVT;
            /* USER CODE BEGIN Service2_Char_5_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CUPS_SEL_VALVE_CCHAR_SUPPO_RW CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service2_Char_5_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CUPS_ER_BLE_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CUPS_ER_BLE_Context.Cups_Con_Valve_Pil_Valve_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CUPS_ER_BLE_CUPS_CON_VALVE_PIL_VALVE_RW_WRITE_EVT;
            /* USER CODE BEGIN Service2_Char_6_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CUPS_CON_PIL_VALVE_RW CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service2_Char_6_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CUPS_ER_BLE_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CUPS_ER_BLE_Context.Cups_Unitp1T1_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CUPS_ER_BLE_CUPS_UNITP1T1_RW_WRITE_EVT;
            /* USER CODE BEGIN Service2_Char_7_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            LOG_INFO_APP("-- GATT : CUPS_UNITP1T1_RW CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service2_Char_7_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CUPS_ER_BLE_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CUPS_ER_BLE_Context.Cups_Setpoint_P2_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CUPS_ER_BLE_CUPS_SETPOINT_P2_RW_WRITE_EVT;
            /* USER CODE BEGIN Service2_Char_8_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CUPS_SETPOINT_P2_RW CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service2_Char_8_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CUPS_ER_BLE_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CUPS_ER_BLE_Context.Cups_Time_Const_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CUPS_ER_BLE_CUPS_TIME_CONST_RW_WRITE_EVT;
            /* USER CODE BEGIN Service2_Char_9_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CUPS_TIME_CONST_RW CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service2_Char_9_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CUPS_ER_BLE_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CUPS_ER_BLE_Context.Cups_Pid_P_Val_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CUPS_ER_BLE_CUPS_PID_P_VAL_RW_WRITE_EVT;
            /* USER CODE BEGIN Service2_Char_10_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CUPS_PID_P_VAL_RW CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service2_Char_10_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CUPS_ER_BLE_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CUPS_ER_BLE_Context.Cups_Pid_I_Val_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CUPS_ER_BLE_CUPS_PID_I_VAL_RW_WRITE_EVT;
            /* USER CODE BEGIN Service2_Char_11_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CUPS_CON_PID_I_VAL_RW CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service2_Char_11_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CUPS_ER_BLE_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CUPS_ER_BLE_Context.Cups_Pid_D_Val_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CUPS_ER_BLE_CUPS_PID_D_VAL_RW_WRITE_EVT;
            /* USER CODE BEGIN Service2_Char_12_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CUPS_PID_D_VAL_RW CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service2_Char_12_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CUPS_ER_BLE_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CUPS_ER_BLE_Context.Cups_Pid_I_Time_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CUPS_ER_BLE_CUPS_PID_I_TIME_RW_WRITE_EVT;
            /* USER CODE BEGIN Service2_Char_13_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CUPS_PID_I_TIME_RW CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service2_Char_13_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CUPS_ER_BLE_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CUPS_ER_BLE_Context.Cups_P1_Min_Range_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CUPS_ER_BLE_CUPS_P1_MIN_RANGE_RW_WRITE_EVT;
            /* USER CODE BEGIN Service2_Char_14_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CUPS_CON_P1_MIN_RANGE_RW CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service2_Char_14_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CUPS_ER_BLE_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CUPS_ER_BLE_Context.Cups_P1_Max_Range_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CUPS_ER_BLE_CUPS_P1_MAX_RANGE_RW_WRITE_EVT;
            /* USER CODE BEGIN Service2_Char_15_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CUPS_P1_MAX_RANGE_RW CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service2_Char_15_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CUPS_ER_BLE_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CUPS_ER_BLE_Context.Cups_Valve_Const_Kv_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CUPS_ER_BLE_CUPS_VALVE_CONST_KV_RW_WRITE_EVT;
            /* USER CODE BEGIN Service2_Char_16_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CUPS_VALVE_CONST_KV_RW CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service2_Char_16_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CUPS_ER_BLE_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CUPS_ER_BLE_Context.Cups_Flow_Factor_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CUPS_ER_BLE_CUPS_FLOW_FACTOR_RW_WRITE_EVT;
            /* USER CODE BEGIN Service2_Char_17_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CUPS_CON_FLOW_FACTOR_RW CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service2_Char_17_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CUPS_ER_BLE_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CUPS_ER_BLE_Context.Cups_Pressure_En_DisCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CUPS_ER_BLE_CUPS_PRESSURE_EN_DIS_WRITE_EVT;
            /* USER CODE BEGIN Service2_Char_18_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CUPS_CON_PRESSURE_EN_DIS_RW CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service2_Char_18_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CUPS_ER_BLE_Notification(&notification);
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
          if(p_read_req->Attribute_Handle == (CUPS_ER_BLE_Context.Cups_Unitp2T2_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service2_Char_1_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service2_Char_1_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service2_Char_1_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CUPS_ER_BLE_CUPS_UNITP2T2_RW_READ_EVT;
            CUPS_ER_BLE_Notification(&notification);
            /*USER CODE END Service2_Char_1_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CUPS_ER_BLE_Context.Cups_Pos_Span_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service2_Char_2_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service2_Char_2_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service2_Char_2_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CUPS_ER_BLE_CUPS_POS_SPAN_RW_READ_EVT;
            CUPS_ER_BLE_Notification(&notification);
            /*USER CODE END Service2_Char_2_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CUPS_ER_BLE_Context.Cups_Valve_Con_Dir_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service2_Char_3_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service2_Char_3_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service2_Char_3_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CUPS_ER_BLE_CUPS_VALVE_CON_DIR_RW_READ_EVT;
            CUPS_ER_BLE_Notification(&notification);
            /*USER CODE END Service2_Char_3_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CUPS_ER_BLE_Context.Cups_Sel_Valve_Friction_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service2_Char_4_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service2_Char_4_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service2_Char_4_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CUPS_ER_BLE_CUPS_SEL_VALVE_FRICTION_RW_READ_EVT;
            CUPS_ER_BLE_Notification(&notification);
            /*USER CODE END Service2_Char_4_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CUPS_ER_BLE_Context.Cups_Sel_Valve_Char_Suppo_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service2_Char_5_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service2_Char_5_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service2_Char_5_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CUPS_ER_BLE_CUPS_SEL_VALVE_CHAR_SUPPO_RW_READ_EVT;
            CUPS_ER_BLE_Notification(&notification);
            /*USER CODE END Service2_Char_5_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CUPS_ER_BLE_Context.Cups_Con_Valve_Pil_Valve_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service2_Char_6_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service2_Char_6_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service2_Char_6_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CUPS_ER_BLE_CUPS_CON_VALVE_PIL_VALVE_RW_READ_EVT;
            CUPS_ER_BLE_Notification(&notification);
            /*USER CODE END Service2_Char_6_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CUPS_ER_BLE_Context.Cups_Unitp1T1_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service2_Char_7_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service2_Char_7_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service2_Char_7_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CUPS_ER_BLE_CUPS_UNITP1T1_RW_READ_EVT;
            CUPS_ER_BLE_Notification(&notification);
            /*USER CODE END Service2_Char_7_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CUPS_ER_BLE_Context.Cups_Setpoint_P2_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service2_Char_8_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service2_Char_8_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service2_Char_8_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CUPS_ER_BLE_CUPS_SETPOINT_P2_RW_READ_EVT;
            CUPS_ER_BLE_Notification(&notification);
            /*USER CODE END Service2_Char_8_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CUPS_ER_BLE_Context.Cups_Time_Const_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service2_Char_9_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service2_Char_9_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service2_Char_9_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
  					aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CUPS_ER_BLE_CUPS_TIME_CONST_RW_READ_EVT;
            CUPS_ER_BLE_Notification(&notification);
            /*USER CODE END Service2_Char_9_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CUPS_ER_BLE_Context.Cups_Pid_P_Val_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service2_Char_10_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service2_Char_10_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service2_Char_10_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CUPS_ER_BLE_CUPS_PID_P_VAL_RW_READ_EVT;
            CUPS_ER_BLE_Notification(&notification);
            /*USER CODE END Service2_Char_10_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CUPS_ER_BLE_Context.Cups_Pid_I_Val_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service2_Char_11_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service2_Char_11_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service2_Char_11_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CUPS_ER_BLE_CUPS_PID_I_VAL_RW_READ_EVT;
            CUPS_ER_BLE_Notification(&notification);
            /*USER CODE END Service2_Char_11_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CUPS_ER_BLE_Context.Cups_Pid_D_Val_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service2_Char_12_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service2_Char_12_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service2_Char_12_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CUPS_ER_BLE_CUPS_PID_D_VAL_RW_READ_EVT;
            CUPS_ER_BLE_Notification(&notification);
            /*USER CODE END Service2_Char_12_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CUPS_ER_BLE_Context.Cups_Pid_I_Time_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service2_Char_13_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service2_Char_13_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service2_Char_13_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CUPS_ER_BLE_CUPS_PID_I_TIME_RW_READ_EVT;
            CUPS_ER_BLE_Notification(&notification);
            /*USER CODE END Service2_Char_13_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CUPS_ER_BLE_Context.Cups_P1_Min_Range_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service2_Char_14_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service2_Char_14_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service2_Char_14_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CUPS_ER_BLE_CUPS_P1_MIN_RANGE_RW_READ_EVT;
            CUPS_ER_BLE_Notification(&notification);		
            /*USER CODE END Service2_Char_14_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CUPS_ER_BLE_Context.Cups_P1_Max_Range_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service2_Char_15_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service2_Char_15_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service2_Char_15_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CUPS_ER_BLE_CUPS_P1_MAX_RANGE_RW_READ_EVT;
            CUPS_ER_BLE_Notification(&notification);
            /*USER CODE END Service2_Char_15_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CUPS_ER_BLE_Context.Cups_Valve_Const_Kv_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service2_Char_16_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service2_Char_16_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service2_Char_16_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CUPS_ER_BLE_CUPS_VALVE_CONST_KV_RW_READ_EVT;
            CUPS_ER_BLE_Notification(&notification);
            /*USER CODE END Service2_Char_16_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CUPS_ER_BLE_Context.Cups_Flow_Factor_RwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service2_Char_17_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service2_Char_17_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service2_Char_17_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
            aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CUPS_ER_BLE_CUPS_FLOW_FACTOR_RW_READ_EVT;
            CUPS_ER_BLE_Notification(&notification);
            /*USER CODE END Service2_Char_17_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CUPS_ER_BLE_Context.Cups_Pressure_En_DisCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service2_Char_18_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service2_Char_18_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service2_Char_18_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CUPS_ER_BLE_CUPS_PRESSURE_EN_DIS_READ_EVT;
            CUPS_ER_BLE_Notification(&notification);
            /*USER CODE END Service2_Char_18_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
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

  /* USER CODE BEGIN Service2_EventHandler_2 */

  /* USER CODE END Service2_EventHandler_2 */

  return(return_value);
}/* end CUPS_ER_BLE_EventHandler */

/* Public functions ----------------------------------------------------------*/

/**
 * @brief  Service initialization
 * @param  None
 * @retval None
 */
void CUPS_ER_BLE_Init(void)
{
  Char_UUID_t  uuid;
  tBleStatus ret;
  uint8_t max_attr_record;

  /* USER CODE BEGIN SVCCTL_InitService2Svc_1 */

  /* USER CODE END SVCCTL_InitService2Svc_1 */

  /**
   *  Register the event handler to the BLE controller
   */
  SVCCTL_RegisterSvcHandler(CUPS_ER_BLE_EventHandler);

  /**
   * CUPS_ER_BLE
   *
   * Max_Attribute_Records = 1 + 2*18 + 1*no_of_char_with_notify_or_indicate_property + 1*no_of_char_with_broadcast_property
   * service_max_attribute_record = 1 for CUPS_ER_BLE +
   *                                2 for CUPS_UNITP2T2_RW +
   *                                2 for CUPS_POS_SPAN_RW +
   *                                2 for CUPS_VALVE_CON_DIR_RW +
   *                                2 for CUPS_SEL_VALVE_FRICTION_RW +
   *                                2 for CUPS_SEL_VALVE_CHAR_SUPPO_RW +
   *                                2 for CUPS_CON_VALVE_PIL_VALVE_RW +
   *                                2 for CUPS_UNITP1T1_RW +
   *                                2 for CUPS_SETPOINT_P2_RW +
   *                                2 for CUPS_TIME_CONST_RW +
   *                                2 for CUPS_PID_P_VAL_RW +
   *                                2 for CUPS_PID_I_VAL_RW +
   *                                2 for CUPS_PID_D_VAL_RW +
   *                                2 for CUPS_PID_I_TIME_RW +
   *                                2 for CUPS_P1_MIN_RANGE_RW +
   *                                2 for CUPS_P1_MAX_RANGE_RW +
   *                                2 for CUPS_VALVE_CONST_KV_RW +
   *                                2 for CUPS_FLOW_FACTOR_RW +
   *                                2 for CUPS_PRESSURE_EN_DIS +
   *                                1 for CUPS_SETPOINT_P2_RW configuration descriptor +
   *                              = 38
   * This value doesn't take into account number of descriptors manually added
   * In case of descriptors added, please update the max_attr_record value accordingly in the next SVCCTL_InitService User Section
   */
  max_attr_record = 38;

  /* USER CODE BEGIN SVCCTL_InitService */
  /* max_attr_record to be updated if descriptors have been added */

  /* USER CODE END SVCCTL_InitService */

  COPY_CUPS_ER_BLE_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_service(UUID_TYPE_128,
                             (Service_UUID_t *) &uuid,
                             PRIMARY_SERVICE,
                             max_attr_record,
                             &(CUPS_ER_BLE_Context.Cups_er_bleSvcHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_service command: CUPS_ER_BLE, error code: 0x%x \n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_service command: Cups_er_bleSvcHdle = 0x%04X\n",CUPS_ER_BLE_Context.Cups_er_bleSvcHdle);
  }

  /**
   * CUPS_UNITP2T2_RW
   */
  COPY_CUPS_UNITP2T2_RW_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CUPS_ER_BLE_Context.Cups_er_bleSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCups_Unitp2T2_Rw,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CUPS_ER_BLE_Context.Cups_Unitp2T2_RwCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CUPS_UNITP2T2_RW, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cups_Unitp2T2_RwCharHdle = 0x%04X\n",CUPS_ER_BLE_Context.Cups_Unitp2T2_RwCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService2Char1 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService2Char1 */

  /**
   * CUPS_POS_SPAN_RW
   */
  COPY_CUPS_POS_SPAN_RW_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CUPS_ER_BLE_Context.Cups_er_bleSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCups_Pos_Span_Rw,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CUPS_ER_BLE_Context.Cups_Pos_Span_RwCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CUPS_POS_SPAN_RW, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cups_Pos_Span_RwCharHdle = 0x%04X\n",CUPS_ER_BLE_Context.Cups_Pos_Span_RwCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService2Char2 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService2Char2 */

  /**
   * CUPS_VALVE_CON_DIR_RW
   */
  COPY_CUPS_VALVE_CON_DIR_RW_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CUPS_ER_BLE_Context.Cups_er_bleSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCups_Valve_Con_Dir_Rw,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CUPS_ER_BLE_Context.Cups_Valve_Con_Dir_RwCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CUPS_VALVE_CON_DIR_RW, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cups_Valve_Con_Dir_RwCharHdle = 0x%04X\n",CUPS_ER_BLE_Context.Cups_Valve_Con_Dir_RwCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService2Char3 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService2Char3 */

  /**
   * CUPS_SEL_VALVE_FRICTION_RW
   */
  COPY_CUPS_SEL_VALVE_FRICTION_RW_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CUPS_ER_BLE_Context.Cups_er_bleSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCups_Sel_Valve_Friction_Rw,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CUPS_ER_BLE_Context.Cups_Sel_Valve_Friction_RwCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CUPS_SEL_VALVE_FRICTION_RW, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cups_Sel_Valve_Friction_RwCharHdle = 0x%04X\n",CUPS_ER_BLE_Context.Cups_Sel_Valve_Friction_RwCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService2Char4 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService2Char4 */

  /**
   * CUPS_SEL_VALVE_CHAR_SUPPO_RW
   */
  COPY_CUPS_SEL_VALVE_CHAR_SUPPO_RW_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CUPS_ER_BLE_Context.Cups_er_bleSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCups_Sel_Valve_Char_Suppo_Rw,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CUPS_ER_BLE_Context.Cups_Sel_Valve_Char_Suppo_RwCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CUPS_SEL_VALVE_CHAR_SUPPO_RW, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cups_Sel_Valve_Char_Suppo_RwCharHdle = 0x%04X\n",CUPS_ER_BLE_Context.Cups_Sel_Valve_Char_Suppo_RwCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService2Char5 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService2Char5 */

  /**
   * CUPS_CON_VALVE_PIL_VALVE_RW
   */
  COPY_CUPS_CON_VALVE_PIL_VALVE_RW_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CUPS_ER_BLE_Context.Cups_er_bleSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCups_Con_Valve_Pil_Valve_Rw,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CUPS_ER_BLE_Context.Cups_Con_Valve_Pil_Valve_RwCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CUPS_CON_VALVE_PIL_VALVE_RW, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cups_Con_Valve_Pil_Valve_RwCharHdle = 0x%04X\n",CUPS_ER_BLE_Context.Cups_Con_Valve_Pil_Valve_RwCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService2Char6 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService2Char6 */

  /**
   * CUPS_UNITP1T1_RW
   */
  COPY_CUPS_UNITP1T1_RW_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CUPS_ER_BLE_Context.Cups_er_bleSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCups_Unitp1T1_Rw,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CUPS_ER_BLE_Context.Cups_Unitp1T1_RwCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CUPS_UNITP1T1_RW, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cups_Unitp1T1_RwCharHdle = 0x%04X\n",CUPS_ER_BLE_Context.Cups_Unitp1T1_RwCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService2Char7 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService2Char7 */

  /**
   * CUPS_SETPOINT_P2_RW
   */
  COPY_CUPS_SETPOINT_P2_RW_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CUPS_ER_BLE_Context.Cups_er_bleSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCups_Setpoint_P2_Rw,
                          CHAR_PROP_READ | CHAR_PROP_WRITE | CHAR_PROP_NOTIFY,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CUPS_ER_BLE_Context.Cups_Setpoint_P2_RwCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CUPS_SETPOINT_P2_RW, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cups_Setpoint_P2_RwCharHdle = 0x%04X\n",CUPS_ER_BLE_Context.Cups_Setpoint_P2_RwCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService2Char8 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService2Char8 */

  /**
   * CUPS_TIME_CONST_RW
   */
  COPY_CUPS_TIME_CONST_RW_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CUPS_ER_BLE_Context.Cups_er_bleSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCups_Time_Const_Rw,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CUPS_ER_BLE_Context.Cups_Time_Const_RwCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CUPS_TIME_CONST_RW, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cups_Time_Const_RwCharHdle = 0x%04X\n",CUPS_ER_BLE_Context.Cups_Time_Const_RwCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService2Char9 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService2Char9 */

  /**
   * CUPS_PID_P_VAL_RW
   */
  COPY_CUPS_PID_P_VAL_RW_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CUPS_ER_BLE_Context.Cups_er_bleSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCups_Pid_P_Val_Rw,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CUPS_ER_BLE_Context.Cups_Pid_P_Val_RwCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CUPS_PID_P_VAL_RW, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cups_Pid_P_Val_RwCharHdle = 0x%04X\n",CUPS_ER_BLE_Context.Cups_Pid_P_Val_RwCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService2Char10 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService2Char10 */

  /**
   * CUPS_PID_I_VAL_RW
   */
  COPY_CUPS_PID_I_VAL_RW_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CUPS_ER_BLE_Context.Cups_er_bleSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCups_Pid_I_Val_Rw,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CUPS_ER_BLE_Context.Cups_Pid_I_Val_RwCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CUPS_PID_I_VAL_RW, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cups_Pid_I_Val_RwCharHdle = 0x%04X\n",CUPS_ER_BLE_Context.Cups_Pid_I_Val_RwCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService2Char11 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService2Char11 */

  /**
   * CUPS_PID_D_VAL_RW
   */
  COPY_CUPS_PID_D_VAL_RW_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CUPS_ER_BLE_Context.Cups_er_bleSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCups_Pid_D_Val_Rw,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CUPS_ER_BLE_Context.Cups_Pid_D_Val_RwCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CUPS_PID_D_VAL_RW, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cups_Pid_D_Val_RwCharHdle = 0x%04X\n",CUPS_ER_BLE_Context.Cups_Pid_D_Val_RwCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService2Char12 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService2Char12 */

  /**
   * CUPS_PID_I_TIME_RW
   */
  COPY_CUPS_PID_I_TIME_RW_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CUPS_ER_BLE_Context.Cups_er_bleSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCups_Pid_I_Time_Rw,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CUPS_ER_BLE_Context.Cups_Pid_I_Time_RwCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CUPS_PID_I_TIME_RW, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cups_Pid_I_Time_RwCharHdle = 0x%04X\n",CUPS_ER_BLE_Context.Cups_Pid_I_Time_RwCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService2Char13 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService2Char13 */

  /**
   * CUPS_P1_MIN_RANGE_RW
   */
  COPY_CUPS_P1_MIN_RANGE_RW_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CUPS_ER_BLE_Context.Cups_er_bleSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCups_P1_Min_Range_Rw,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CUPS_ER_BLE_Context.Cups_P1_Min_Range_RwCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CUPS_P1_MIN_RANGE_RW, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cups_P1_Min_Range_RwCharHdle = 0x%04X\n",CUPS_ER_BLE_Context.Cups_P1_Min_Range_RwCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService2Char14 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService2Char14 */

  /**
   * CUPS_P1_MAX_RANGE_RW
   */
  COPY_CUPS_P1_MAX_RANGE_RW_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CUPS_ER_BLE_Context.Cups_er_bleSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCups_P1_Max_Range_Rw,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CUPS_ER_BLE_Context.Cups_P1_Max_Range_RwCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CUPS_P1_MAX_RANGE_RW, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cups_P1_Max_Range_RwCharHdle = 0x%04X\n",CUPS_ER_BLE_Context.Cups_P1_Max_Range_RwCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService2Char15 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService2Char15 */

  /**
   * CUPS_VALVE_CONST_KV_RW
   */
  COPY_CUPS_VALVE_CONST_KV_RW_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CUPS_ER_BLE_Context.Cups_er_bleSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCups_Valve_Const_Kv_Rw,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CUPS_ER_BLE_Context.Cups_Valve_Const_Kv_RwCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CUPS_VALVE_CONST_KV_RW, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cups_Valve_Const_Kv_RwCharHdle = 0x%04X\n",CUPS_ER_BLE_Context.Cups_Valve_Const_Kv_RwCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService2Char16 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService2Char16 */

  /**
   * CUPS_FLOW_FACTOR_RW
   */
  COPY_CUPS_FLOW_FACTOR_RW_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CUPS_ER_BLE_Context.Cups_er_bleSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCups_Flow_Factor_Rw,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CUPS_ER_BLE_Context.Cups_Flow_Factor_RwCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CUPS_FLOW_FACTOR_RW, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cups_Flow_Factor_RwCharHdle = 0x%04X\n",CUPS_ER_BLE_Context.Cups_Flow_Factor_RwCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService2Char17 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService2Char17 */

  /**
   * CUPS_PRESSURE_EN_DIS
   */
  COPY_CUPS_PRESSURE_EN_DIS_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CUPS_ER_BLE_Context.Cups_er_bleSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCups_Pressure_En_Dis,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CUPS_ER_BLE_Context.Cups_Pressure_En_DisCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CUPS_PRESSURE_EN_DIS, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cups_Pressure_En_DisCharHdle = 0x%04X\n",CUPS_ER_BLE_Context.Cups_Pressure_En_DisCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService2Char18 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService2Char18 */

  /* USER CODE BEGIN SVCCTL_InitService2Svc_2 */

  /* USER CODE END SVCCTL_InitService2Svc_2 */

  return;
}

/**
 * @brief  Characteristic update
 * @param  CharOpcode: Characteristic identifier
 * @param  pData: Structure holding data to update
 *
 */
tBleStatus CUPS_ER_BLE_UpdateValue(CUPS_ER_BLE_CharOpcode_t CharOpcode, CUPS_ER_BLE_Data_t *pData)
{
  tBleStatus ret = BLE_STATUS_INVALID_PARAMS;
  /* USER CODE BEGIN Service2_App_Update_Char_1 */

  /* USER CODE END Service2_App_Update_Char_1 */

  switch(CharOpcode)
  {
    case CUPS_ER_BLE_CUPS_UNITP2T2_RW:
      ret = aci_gatt_update_char_value(CUPS_ER_BLE_Context.Cups_er_bleSvcHdle,
                                       CUPS_ER_BLE_Context.Cups_Unitp2T2_RwCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CUPS_UNITP2T2_RW command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CUPS_UNITP2T2_RW command\n");
      }
      /* USER CODE BEGIN Service2_Char_Value_1 */

      /* USER CODE END Service2_Char_Value_1 */
      break;

    case CUPS_ER_BLE_CUPS_POS_SPAN_RW:
      ret = aci_gatt_update_char_value(CUPS_ER_BLE_Context.Cups_er_bleSvcHdle,
                                       CUPS_ER_BLE_Context.Cups_Pos_Span_RwCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CUPS_POS_SPAN_RW command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CUPS_POS_SPAN_RW command\n");
      }
      /* USER CODE BEGIN Service2_Char_Value_2 */

      /* USER CODE END Service2_Char_Value_2 */
      break;

    case CUPS_ER_BLE_CUPS_VALVE_CON_DIR_RW:
      ret = aci_gatt_update_char_value(CUPS_ER_BLE_Context.Cups_er_bleSvcHdle,
                                       CUPS_ER_BLE_Context.Cups_Valve_Con_Dir_RwCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CUPS_VALVE_CON_DIR_RW command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CUPS_VALVE_CON_DIR_RW command\n");
      }
      /* USER CODE BEGIN Service2_Char_Value_3 */

      /* USER CODE END Service2_Char_Value_3 */
      break;

    case CUPS_ER_BLE_CUPS_SEL_VALVE_FRICTION_RW:
      ret = aci_gatt_update_char_value(CUPS_ER_BLE_Context.Cups_er_bleSvcHdle,
                                       CUPS_ER_BLE_Context.Cups_Sel_Valve_Friction_RwCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CUPS_SEL_VALVE_FRICTION_RW command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CUPS_SEL_VALVE_FRICTION_RW command\n");
      }
      /* USER CODE BEGIN Service2_Char_Value_4 */

      /* USER CODE END Service2_Char_Value_4 */
      break;

    case CUPS_ER_BLE_CUPS_SEL_VALVE_CHAR_SUPPO_RW:
      ret = aci_gatt_update_char_value(CUPS_ER_BLE_Context.Cups_er_bleSvcHdle,
                                       CUPS_ER_BLE_Context.Cups_Sel_Valve_Char_Suppo_RwCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CUPS_SEL_VALVE_CHAR_SUPPO_RW command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CUPS_SEL_VALVE_CHAR_SUPPO_RW command\n");
      }
      /* USER CODE BEGIN Service2_Char_Value_5 */

      /* USER CODE END Service2_Char_Value_5 */
      break;

    case CUPS_ER_BLE_CUPS_CON_VALVE_PIL_VALVE_RW:
      ret = aci_gatt_update_char_value(CUPS_ER_BLE_Context.Cups_er_bleSvcHdle,
                                       CUPS_ER_BLE_Context.Cups_Con_Valve_Pil_Valve_RwCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CUPS_CON_VALVE_PIL_VALVE_RW command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CUPS_CON_VALVE_PIL_VALVE_RW command\n");
      }
      /* USER CODE BEGIN Service2_Char_Value_6 */

      /* USER CODE END Service2_Char_Value_6 */
      break;

    case CUPS_ER_BLE_CUPS_UNITP1T1_RW:
      ret = aci_gatt_update_char_value(CUPS_ER_BLE_Context.Cups_er_bleSvcHdle,
                                       CUPS_ER_BLE_Context.Cups_Unitp1T1_RwCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CUPS_UNITP1T1_RW command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CUPS_UNITP1T1_RW command\n");
      }
      /* USER CODE BEGIN Service2_Char_Value_7 */

      /* USER CODE END Service2_Char_Value_7 */
      break;

    case CUPS_ER_BLE_CUPS_SETPOINT_P2_RW:
      ret = aci_gatt_update_char_value(CUPS_ER_BLE_Context.Cups_er_bleSvcHdle,
                                       CUPS_ER_BLE_Context.Cups_Setpoint_P2_RwCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CUPS_SETPOINT_P2_RW command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CUPS_SETPOINT_P2_RW command\n");
      }
      /* USER CODE BEGIN Service2_Char_Value_8 */

      /* USER CODE END Service2_Char_Value_8 */
      break;

    case CUPS_ER_BLE_CUPS_TIME_CONST_RW:
      ret = aci_gatt_update_char_value(CUPS_ER_BLE_Context.Cups_er_bleSvcHdle,
                                       CUPS_ER_BLE_Context.Cups_Time_Const_RwCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CUPS_TIME_CONST_RW command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CUPS_TIME_CONST_RW command\n");
      }
      /* USER CODE BEGIN Service2_Char_Value_9 */

      /* USER CODE END Service2_Char_Value_9 */
      break;

    case CUPS_ER_BLE_CUPS_PID_P_VAL_RW:
      ret = aci_gatt_update_char_value(CUPS_ER_BLE_Context.Cups_er_bleSvcHdle,
                                       CUPS_ER_BLE_Context.Cups_Pid_P_Val_RwCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CUPS_PID_P_VAL_RW command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CUPS_PID_P_VAL_RW command\n");
      }
      /* USER CODE BEGIN Service2_Char_Value_10 */

      /* USER CODE END Service2_Char_Value_10 */
      break;

    case CUPS_ER_BLE_CUPS_PID_I_VAL_RW:
      ret = aci_gatt_update_char_value(CUPS_ER_BLE_Context.Cups_er_bleSvcHdle,
                                       CUPS_ER_BLE_Context.Cups_Pid_I_Val_RwCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CUPS_PID_I_VAL_RW command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CUPS_PID_I_VAL_RW command\n");
      }
      /* USER CODE BEGIN Service2_Char_Value_11 */

      /* USER CODE END Service2_Char_Value_11 */
      break;

    case CUPS_ER_BLE_CUPS_PID_D_VAL_RW:
      ret = aci_gatt_update_char_value(CUPS_ER_BLE_Context.Cups_er_bleSvcHdle,
                                       CUPS_ER_BLE_Context.Cups_Pid_D_Val_RwCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CUPS_PID_D_VAL_RW command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CUPS_PID_D_VAL_RW command\n");
      }
      /* USER CODE BEGIN Service2_Char_Value_12 */

      /* USER CODE END Service2_Char_Value_12 */
      break;

    case CUPS_ER_BLE_CUPS_PID_I_TIME_RW:
      ret = aci_gatt_update_char_value(CUPS_ER_BLE_Context.Cups_er_bleSvcHdle,
                                       CUPS_ER_BLE_Context.Cups_Pid_I_Time_RwCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CUPS_PID_I_TIME_RW command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CUPS_PID_I_TIME_RW command\n");
      }
      /* USER CODE BEGIN Service2_Char_Value_13 */

      /* USER CODE END Service2_Char_Value_13 */
      break;

    case CUPS_ER_BLE_CUPS_P1_MIN_RANGE_RW:
      ret = aci_gatt_update_char_value(CUPS_ER_BLE_Context.Cups_er_bleSvcHdle,
                                       CUPS_ER_BLE_Context.Cups_P1_Min_Range_RwCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CUPS_P1_MIN_RANGE_RW command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CUPS_P1_MIN_RANGE_RW command\n");
      }
      /* USER CODE BEGIN Service2_Char_Value_14 */

      /* USER CODE END Service2_Char_Value_14 */
      break;

    case CUPS_ER_BLE_CUPS_P1_MAX_RANGE_RW:
      ret = aci_gatt_update_char_value(CUPS_ER_BLE_Context.Cups_er_bleSvcHdle,
                                       CUPS_ER_BLE_Context.Cups_P1_Max_Range_RwCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CUPS_P1_MAX_RANGE_RW command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CUPS_P1_MAX_RANGE_RW command\n");
      }
      /* USER CODE BEGIN Service2_Char_Value_15 */

      /* USER CODE END Service2_Char_Value_15 */
      break;

    case CUPS_ER_BLE_CUPS_VALVE_CONST_KV_RW:
      ret = aci_gatt_update_char_value(CUPS_ER_BLE_Context.Cups_er_bleSvcHdle,
                                       CUPS_ER_BLE_Context.Cups_Valve_Const_Kv_RwCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CUPS_VALVE_CONST_KV_RW command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CUPS_VALVE_CONST_KV_RW command\n");
      }
      /* USER CODE BEGIN Service2_Char_Value_16 */

      /* USER CODE END Service2_Char_Value_16 */
      break;

    case CUPS_ER_BLE_CUPS_FLOW_FACTOR_RW:
      ret = aci_gatt_update_char_value(CUPS_ER_BLE_Context.Cups_er_bleSvcHdle,
                                       CUPS_ER_BLE_Context.Cups_Flow_Factor_RwCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CUPS_FLOW_FACTOR_RW command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CUPS_FLOW_FACTOR_RW command\n");
      }
      /* USER CODE BEGIN Service2_Char_Value_17 */

      /* USER CODE END Service2_Char_Value_17 */
      break;

    case CUPS_ER_BLE_CUPS_PRESSURE_EN_DIS:
      ret = aci_gatt_update_char_value(CUPS_ER_BLE_Context.Cups_er_bleSvcHdle,
                                       CUPS_ER_BLE_Context.Cups_Pressure_En_DisCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CUPS_PRESSURE_EN_DIS command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CUPS_PRESSURE_EN_DIS command\n");
      }
      /* USER CODE BEGIN Service2_Char_Value_18 */

      /* USER CODE END Service2_Char_Value_18 */
      break;

    default:
      break;
  }

  /* USER CODE BEGIN Service2_App_Update_Char_2 */

  /* USER CODE END Service2_App_Update_Char_2 */

  return ret;
}
