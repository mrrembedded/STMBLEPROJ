/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    CS.c
  * @author  MCD Application Team
  * @brief   CS definition.
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
#include "cs.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/

/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

typedef struct{
  uint16_t  CsSvcHdle;                  /**< Cs Service Handle */
  uint16_t  Cs_FlowtempCharHdle;                  /**< CS_FLOWTEMP Characteristic Handle */
  uint16_t  Cs_P2T2CharHdle;                  /**< CS_P2T2 Characteristic Handle */
  uint16_t  Cs_P1T1CharHdle;                  /**< CS_P1T1 Characteristic Handle */
  uint16_t  Cs_Unit_P2T2CharHdle;                  /**< CS_UNIT_P2T2 Characteristic Handle */
  uint16_t  Cs_Unit_P1T1CharHdle;                  /**< CS_UNIT_P1T1 Characteristic Handle */
  uint16_t  Cs_Mod_Com_ErrorCharHdle;                  /**< CS_MOD_COM_ERROR Characteristic Handle */
  uint16_t  Cs_Diag_ErrorCharHdle;                  /**< CS_DIAG_ERROR Characteristic Handle */
  uint16_t  Cs_Diag_WarnCharHdle;                  /**< CS_DIAG_WARN Characteristic Handle */
  uint16_t  Cs_Inlet_Pres_Pd1CharHdle;                  /**< CS_INLET_PRES_PD1 Characteristic Handle */
  uint16_t  Cs_Outlet_Pres_Pd2CharHdle;                  /**< CS_OUTLET_PRES_PD2 Characteristic Handle */
  uint16_t  Cs_Opening_PerCharHdle;                  /**< CS_OPENING_PER Characteristic Handle */
  uint16_t  Cs_Operation_ModeCharHdle;                  /**< CS_OPERATION_MODE Characteristic Handle */
  uint16_t  Cs_Lvdt_AmpCharHdle;                  /**< CS_LVDT_AMP Characteristic Handle */
  uint16_t  Cs_TotalizerCharHdle;                  /**< CS_TOTALIZER Characteristic Handle */
  uint16_t  Cs_Reset_ButtonCharHdle;                  /**< CS_RESET_BUTTON Characteristic Handle */
  uint16_t  Cs_Time_Stamp_HhmmCharHdle;                  /**< CS_TIME_STAMP_HHMM Characteristic Handle */
  uint16_t  Cs_Time_Stamp_DdmmCharHdle;                  /**< CS_TIME_STAMP_DDMM Characteristic Handle */
  uint16_t  Cs_Year_Stamp_YyyyCharHdle;                  /**< CS_YEAR_STAMP_YYYY Characteristic Handle */
  uint16_t  Cs_Totalizer_Last_ValCharHdle;                  /**< CS_TOTALIZER_LAST_VAL Characteristic Handle */
  uint16_t  Cs_Totalizer_UnitCharHdle;                  /**< CS_TOTALIZER_UNIT Characteristic Handle */
  uint16_t  Cs_Connection_StatusCharHdle;                  /**< CS_CONNECTION_STATUS Characteristic Handle */
/* USER CODE BEGIN Context */
  /* Place holder for Characteristic Descriptors Handle*/

/* USER CODE END Context */
}CS_Context_t;

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
static const uint16_t SizeCs_Flowtemp = 4;
static const uint16_t SizeCs_P2T2 = 4;
static const uint16_t SizeCs_P1T1 = 4;
static const uint16_t SizeCs_Unit_P2T2 = 1;
static const uint16_t SizeCs_Unit_P1T1 = 1;
static const uint16_t SizeCs_Mod_Com_Error = 2;
static const uint16_t SizeCs_Diag_Error = 2;
static const uint16_t SizeCs_Diag_Warn = 2;
static const uint16_t SizeCs_Inlet_Pres_Pd1 = 4;
static const uint16_t SizeCs_Outlet_Pres_Pd2 = 4;
static const uint16_t SizeCs_Opening_Per = 4;
static const uint16_t SizeCs_Operation_Mode = 1;
static const uint16_t SizeCs_Lvdt_Amp = 2;
static const uint16_t SizeCs_Totalizer = 4;
static const uint16_t SizeCs_Reset_Button = 1;
static const uint16_t SizeCs_Time_Stamp_Hhmm = 2;
static const uint16_t SizeCs_Time_Stamp_Ddmm = 2;
static const uint16_t SizeCs_Year_Stamp_Yyyy = 2;
static const uint16_t SizeCs_Totalizer_Last_Val = 4;
static const uint16_t SizeCs_Totalizer_Unit = 1;
static const uint16_t SizeCs_Connection_Status = 1;

static CS_Context_t CS_Context;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static SVCCTL_EvtAckStatus_t CS_EventHandler(void *p_pckt);

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
 F364040000B04240BA5005CA45BF8ABC: Service 128bits UUID
 F364040100B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364040200B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364040300B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364040400B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364040500B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364040600B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364040700B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364040800B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364040900B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364040A00B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364040B00B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364040C00B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364040D00B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364040E00B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364040F00B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364041000B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364041100B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364041200B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364041300B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364041400B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364041500B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 */
#define COPY_CS_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x04,0x00,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CS_FLOWTEMP_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x04,0x01,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CS_P2T2_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x04,0x02,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CS_P1T1_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x04,0x03,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CS_UNIT_P2T2_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x04,0x04,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CS_UNIT_P1T1_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x04,0x05,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CS_MOD_COM_ERROR_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x04,0x06,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CS_DIAG_ERROR_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x04,0x07,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CS_DIAG_WARN_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x04,0x08,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CS_INLET_PRES_PD1_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x04,0x09,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CS_OUTLET_PRES_PD2_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x04,0x0a,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CS_OPENING_PER_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x04,0x0b,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CS_OPERATION_MODE_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x04,0x0c,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CS_LVDT_AMP_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x04,0x0d,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CS_TOTALIZER_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x04,0x0e,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CS_RESET_BUTTON_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x04,0x0f,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CS_TIME_STAMP_HHMM_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x04,0x10,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CS_TIME_STAMP_DDMM_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x04,0x11,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CS_YEAR_STAMP_YYYY_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x04,0x12,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CS_TOTALIZER_LAST_VAL_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x04,0x13,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CS_TOTALIZER_UNIT_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x04,0x14,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CS_CONNECTION_STATUS_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x04,0x15,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)

/* USER CODE BEGIN PF */

/* USER CODE END PF */

/**
 * @brief  Event handler
 * @param  p_Event: Address of the buffer holding the p_Event
 * @retval Ack: Return whether the p_Event has been managed or not
 */
static SVCCTL_EvtAckStatus_t CS_EventHandler(void *p_Event)
{
  SVCCTL_EvtAckStatus_t return_value;
  hci_event_pckt *p_event_pckt;
  evt_blecore_aci *p_blecore_evt;
  aci_gatt_attribute_modified_event_rp0 *p_attribute_modified;
  aci_gatt_read_permit_req_event_rp0    *p_read_req;
  CS_NotificationEvt_t                 notification;
  /* USER CODE BEGIN Service5_EventHandler_1 */

  /* USER CODE END Service5_EventHandler_1 */

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
          if(p_attribute_modified->Attr_Handle == (CS_Context.Cs_FlowtempCharHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN Service5_Char_1 */

            /* USER CODE END Service5_Char_1 */
            switch(p_attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN Service5_Char_1_attribute_modified */

              /* USER CODE END Service5_Char_1_attribute_modified */

              /* Disabled Notification management */
              case (0x00):
                /* USER CODE BEGIN Service5_Char_1_Disabled_BEGIN */

                /* USER CODE END Service5_Char_1_Disabled_BEGIN */
                notification.EvtOpcode = CS_CS_FLOWTEMP_NOTIFY_DISABLED_EVT;
                CS_Notification(&notification);
                /* USER CODE BEGIN Service5_Char_1_Disabled_END */

                /* USER CODE END Service5_Char_1_Disabled_END */
                break;

              /* Enabled Notification management */
              case GATT_CHAR_UPDATE_SEND_NOTIFICATION:
                /* USER CODE BEGIN Service5_Char_1_COMSVC_Notification_BEGIN */

                /* USER CODE END Service5_Char_1_COMSVC_Notification_BEGIN */
                notification.EvtOpcode = CS_CS_FLOWTEMP_NOTIFY_ENABLED_EVT;
                CS_Notification(&notification);
                /* USER CODE BEGIN Service5_Char_1_COMSVC_Notification_END */

                /* USER CODE END Service5_Char_1_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN Service5_Char_1_default */

                /* USER CODE END Service5_Char_1_default */
                break;
            }
          }

          else if(p_attribute_modified->Attr_Handle == (CS_Context.Cs_P2T2CharHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN Service5_Char_2 */

            /* USER CODE END Service5_Char_2 */
            switch(p_attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN Service5_Char_2_attribute_modified */

              /* USER CODE END Service5_Char_2_attribute_modified */

              /* Disabled Notification management */
              case (0x00):
                /* USER CODE BEGIN Service5_Char_2_Disabled_BEGIN */

                /* USER CODE END Service5_Char_2_Disabled_BEGIN */
                notification.EvtOpcode = CS_CS_P2T2_NOTIFY_DISABLED_EVT;
                CS_Notification(&notification);
                /* USER CODE BEGIN Service5_Char_2_Disabled_END */

                /* USER CODE END Service5_Char_2_Disabled_END */
                break;

              /* Enabled Notification management */
              case GATT_CHAR_UPDATE_SEND_NOTIFICATION:
                /* USER CODE BEGIN Service5_Char_2_COMSVC_Notification_BEGIN */

                /* USER CODE END Service5_Char_2_COMSVC_Notification_BEGIN */
                notification.EvtOpcode = CS_CS_P2T2_NOTIFY_ENABLED_EVT;
                CS_Notification(&notification);
                /* USER CODE BEGIN Service5_Char_2_COMSVC_Notification_END */

                /* USER CODE END Service5_Char_2_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN Service5_Char_2_default */

                /* USER CODE END Service5_Char_2_default */
                break;
            }
          }

          else if(p_attribute_modified->Attr_Handle == (CS_Context.Cs_P1T1CharHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN Service5_Char_3 */

            /* USER CODE END Service5_Char_3 */
            switch(p_attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN Service5_Char_3_attribute_modified */

              /* USER CODE END Service5_Char_3_attribute_modified */

              /* Disabled Notification management */
              case (0x00):
                /* USER CODE BEGIN Service5_Char_3_Disabled_BEGIN */

                /* USER CODE END Service5_Char_3_Disabled_BEGIN */
                notification.EvtOpcode = CS_CS_P1T1_NOTIFY_DISABLED_EVT;
                CS_Notification(&notification);
                /* USER CODE BEGIN Service5_Char_3_Disabled_END */

                /* USER CODE END Service5_Char_3_Disabled_END */
                break;

              /* Enabled Notification management */
              case GATT_CHAR_UPDATE_SEND_NOTIFICATION:
                /* USER CODE BEGIN Service5_Char_3_COMSVC_Notification_BEGIN */

                /* USER CODE END Service5_Char_3_COMSVC_Notification_BEGIN */
                notification.EvtOpcode = CS_CS_P1T1_NOTIFY_ENABLED_EVT;
                CS_Notification(&notification);
                /* USER CODE BEGIN Service5_Char_3_COMSVC_Notification_END */

                /* USER CODE END Service5_Char_3_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN Service5_Char_3_default */

                /* USER CODE END Service5_Char_3_default */
                break;
            }
          }

          else if(p_attribute_modified->Attr_Handle == (CS_Context.Cs_Unit_P2T2CharHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN Service5_Char_4 */

            /* USER CODE END Service5_Char_4 */
            switch(p_attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN Service5_Char_4_attribute_modified */

              /* USER CODE END Service5_Char_4_attribute_modified */

              /* Disabled Notification management */
              case (0x00):
                /* USER CODE BEGIN Service5_Char_4_Disabled_BEGIN */

                /* USER CODE END Service5_Char_4_Disabled_BEGIN */
                notification.EvtOpcode = CS_CS_UNIT_P2T2_NOTIFY_DISABLED_EVT;
                CS_Notification(&notification);
                /* USER CODE BEGIN Service5_Char_4_Disabled_END */

                /* USER CODE END Service5_Char_4_Disabled_END */
                break;

              /* Enabled Notification management */
              case GATT_CHAR_UPDATE_SEND_NOTIFICATION:
                /* USER CODE BEGIN Service5_Char_4_COMSVC_Notification_BEGIN */

                /* USER CODE END Service5_Char_4_COMSVC_Notification_BEGIN */
                notification.EvtOpcode = CS_CS_UNIT_P2T2_NOTIFY_ENABLED_EVT;
                CS_Notification(&notification);
                /* USER CODE BEGIN Service5_Char_4_COMSVC_Notification_END */

                /* USER CODE END Service5_Char_4_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN Service5_Char_4_default */

                /* USER CODE END Service5_Char_4_default */
                break;
            }
          }

          else if(p_attribute_modified->Attr_Handle == (CS_Context.Cs_Unit_P1T1CharHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN Service5_Char_5 */

            /* USER CODE END Service5_Char_5 */
            switch(p_attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN Service5_Char_5_attribute_modified */

              /* USER CODE END Service5_Char_5_attribute_modified */

              /* Disabled Notification management */
              case (0x00):
                /* USER CODE BEGIN Service5_Char_5_Disabled_BEGIN */

                /* USER CODE END Service5_Char_5_Disabled_BEGIN */
                notification.EvtOpcode = CS_CS_UNIT_P1T1_NOTIFY_DISABLED_EVT;
                CS_Notification(&notification);
                /* USER CODE BEGIN Service5_Char_5_Disabled_END */

                /* USER CODE END Service5_Char_5_Disabled_END */
                break;

              /* Enabled Notification management */
              case GATT_CHAR_UPDATE_SEND_NOTIFICATION:
                /* USER CODE BEGIN Service5_Char_5_COMSVC_Notification_BEGIN */

                /* USER CODE END Service5_Char_5_COMSVC_Notification_BEGIN */
                notification.EvtOpcode = CS_CS_UNIT_P1T1_NOTIFY_ENABLED_EVT;
                CS_Notification(&notification);
                /* USER CODE BEGIN Service5_Char_5_COMSVC_Notification_END */

                /* USER CODE END Service5_Char_5_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN Service5_Char_5_default */

                /* USER CODE END Service5_Char_5_default */
                break;
            }
          }

          else if(p_attribute_modified->Attr_Handle == (CS_Context.Cs_Mod_Com_ErrorCharHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN Service5_Char_6 */

            /* USER CODE END Service5_Char_6 */
            switch(p_attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN Service5_Char_6_attribute_modified */

              /* USER CODE END Service5_Char_6_attribute_modified */

              /* Disabled Notification management */
              case (0x00):
                /* USER CODE BEGIN Service5_Char_6_Disabled_BEGIN */

                /* USER CODE END Service5_Char_6_Disabled_BEGIN */
                notification.EvtOpcode = CS_CS_MOD_COM_ERROR_NOTIFY_DISABLED_EVT;
                CS_Notification(&notification);
                /* USER CODE BEGIN Service5_Char_6_Disabled_END */

                /* USER CODE END Service5_Char_6_Disabled_END */
                break;

              /* Enabled Notification management */
              case GATT_CHAR_UPDATE_SEND_NOTIFICATION:
                /* USER CODE BEGIN Service5_Char_6_COMSVC_Notification_BEGIN */

                /* USER CODE END Service5_Char_6_COMSVC_Notification_BEGIN */
                notification.EvtOpcode = CS_CS_MOD_COM_ERROR_NOTIFY_ENABLED_EVT;
                CS_Notification(&notification);
                /* USER CODE BEGIN Service5_Char_6_COMSVC_Notification_END */

                /* USER CODE END Service5_Char_6_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN Service5_Char_6_default */

                /* USER CODE END Service5_Char_6_default */
                break;
            }
          }

          else if(p_attribute_modified->Attr_Handle == (CS_Context.Cs_Diag_ErrorCharHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN Service5_Char_7 */

            /* USER CODE END Service5_Char_7 */
            switch(p_attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN Service5_Char_7_attribute_modified */

              /* USER CODE END Service5_Char_7_attribute_modified */

              /* Disabled Notification management */
              case (0x00):
                /* USER CODE BEGIN Service5_Char_7_Disabled_BEGIN */

                /* USER CODE END Service5_Char_7_Disabled_BEGIN */
                notification.EvtOpcode = CS_CS_DIAG_ERROR_NOTIFY_DISABLED_EVT;
                CS_Notification(&notification);
                /* USER CODE BEGIN Service5_Char_7_Disabled_END */

                /* USER CODE END Service5_Char_7_Disabled_END */
                break;

              /* Enabled Notification management */
              case GATT_CHAR_UPDATE_SEND_NOTIFICATION:
                /* USER CODE BEGIN Service5_Char_7_COMSVC_Notification_BEGIN */

                /* USER CODE END Service5_Char_7_COMSVC_Notification_BEGIN */
                notification.EvtOpcode = CS_CS_DIAG_ERROR_NOTIFY_ENABLED_EVT;
                CS_Notification(&notification);
                /* USER CODE BEGIN Service5_Char_7_COMSVC_Notification_END */

                /* USER CODE END Service5_Char_7_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN Service5_Char_7_default */

                /* USER CODE END Service5_Char_7_default */
                break;
            }
          }

          else if(p_attribute_modified->Attr_Handle == (CS_Context.Cs_Diag_WarnCharHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN Service5_Char_8 */

            /* USER CODE END Service5_Char_8 */
            switch(p_attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN Service5_Char_8_attribute_modified */

              /* USER CODE END Service5_Char_8_attribute_modified */

              /* Disabled Notification management */
              case (0x00):
                /* USER CODE BEGIN Service5_Char_8_Disabled_BEGIN */

                /* USER CODE END Service5_Char_8_Disabled_BEGIN */
                notification.EvtOpcode = CS_CS_DIAG_WARN_NOTIFY_DISABLED_EVT;
                CS_Notification(&notification);
                /* USER CODE BEGIN Service5_Char_8_Disabled_END */

                /* USER CODE END Service5_Char_8_Disabled_END */
                break;

              /* Enabled Notification management */
              case GATT_CHAR_UPDATE_SEND_NOTIFICATION:
                /* USER CODE BEGIN Service5_Char_8_COMSVC_Notification_BEGIN */

                /* USER CODE END Service5_Char_8_COMSVC_Notification_BEGIN */
                notification.EvtOpcode = CS_CS_DIAG_WARN_NOTIFY_ENABLED_EVT;
                CS_Notification(&notification);
                /* USER CODE BEGIN Service5_Char_8_COMSVC_Notification_END */

                /* USER CODE END Service5_Char_8_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN Service5_Char_8_default */

                /* USER CODE END Service5_Char_8_default */
                break;
            }
          }

          else if(p_attribute_modified->Attr_Handle == (CS_Context.Cs_Inlet_Pres_Pd1CharHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN Service5_Char_9 */

            /* USER CODE END Service5_Char_9 */
            switch(p_attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN Service5_Char_9_attribute_modified */

              /* USER CODE END Service5_Char_9_attribute_modified */

              /* Disabled Notification management */
              case (0x00):
                /* USER CODE BEGIN Service5_Char_9_Disabled_BEGIN */

                /* USER CODE END Service5_Char_9_Disabled_BEGIN */
                notification.EvtOpcode = CS_CS_INLET_PRES_PD1_NOTIFY_DISABLED_EVT;
                CS_Notification(&notification);
                /* USER CODE BEGIN Service5_Char_9_Disabled_END */

                /* USER CODE END Service5_Char_9_Disabled_END */
                break;

              /* Enabled Notification management */
              case GATT_CHAR_UPDATE_SEND_NOTIFICATION:
                /* USER CODE BEGIN Service5_Char_9_COMSVC_Notification_BEGIN */

                /* USER CODE END Service5_Char_9_COMSVC_Notification_BEGIN */
                notification.EvtOpcode = CS_CS_INLET_PRES_PD1_NOTIFY_ENABLED_EVT;
                CS_Notification(&notification);
                /* USER CODE BEGIN Service5_Char_9_COMSVC_Notification_END */

                /* USER CODE END Service5_Char_9_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN Service5_Char_9_default */

                /* USER CODE END Service5_Char_9_default */
                break;
            }
          }

          else if(p_attribute_modified->Attr_Handle == (CS_Context.Cs_Outlet_Pres_Pd2CharHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN Service5_Char_10 */

            /* USER CODE END Service5_Char_10 */
            switch(p_attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN Service5_Char_10_attribute_modified */

              /* USER CODE END Service5_Char_10_attribute_modified */

              /* Disabled Notification management */
              case (0x00):
                /* USER CODE BEGIN Service5_Char_10_Disabled_BEGIN */

                /* USER CODE END Service5_Char_10_Disabled_BEGIN */
                notification.EvtOpcode = CS_CS_OUTLET_PRES_PD2_NOTIFY_DISABLED_EVT;
                CS_Notification(&notification);
                /* USER CODE BEGIN Service5_Char_10_Disabled_END */

                /* USER CODE END Service5_Char_10_Disabled_END */
                break;

              /* Enabled Notification management */
              case GATT_CHAR_UPDATE_SEND_NOTIFICATION:
                /* USER CODE BEGIN Service5_Char_10_COMSVC_Notification_BEGIN */

                /* USER CODE END Service5_Char_10_COMSVC_Notification_BEGIN */
                notification.EvtOpcode = CS_CS_OUTLET_PRES_PD2_NOTIFY_ENABLED_EVT;
                CS_Notification(&notification);
                /* USER CODE BEGIN Service5_Char_10_COMSVC_Notification_END */

                /* USER CODE END Service5_Char_10_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN Service5_Char_10_default */

                /* USER CODE END Service5_Char_10_default */
                break;
            }
          }

          else if(p_attribute_modified->Attr_Handle == (CS_Context.Cs_Opening_PerCharHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN Service5_Char_11 */

            /* USER CODE END Service5_Char_11 */
            switch(p_attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN Service5_Char_11_attribute_modified */

              /* USER CODE END Service5_Char_11_attribute_modified */

              /* Disabled Notification management */
              case (0x00):
                /* USER CODE BEGIN Service5_Char_11_Disabled_BEGIN */

                /* USER CODE END Service5_Char_11_Disabled_BEGIN */
                notification.EvtOpcode = CS_CS_OPENING_PER_NOTIFY_DISABLED_EVT;
                CS_Notification(&notification);
                /* USER CODE BEGIN Service5_Char_11_Disabled_END */

                /* USER CODE END Service5_Char_11_Disabled_END */
                break;

              /* Enabled Notification management */
              case GATT_CHAR_UPDATE_SEND_NOTIFICATION:
                /* USER CODE BEGIN Service5_Char_11_COMSVC_Notification_BEGIN */

                /* USER CODE END Service5_Char_11_COMSVC_Notification_BEGIN */
                notification.EvtOpcode = CS_CS_OPENING_PER_NOTIFY_ENABLED_EVT;
                CS_Notification(&notification);
                /* USER CODE BEGIN Service5_Char_11_COMSVC_Notification_END */

                /* USER CODE END Service5_Char_11_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN Service5_Char_11_default */

                /* USER CODE END Service5_Char_11_default */
                break;
            }
          }

          else if(p_attribute_modified->Attr_Handle == (CS_Context.Cs_Operation_ModeCharHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN Service5_Char_12 */

            /* USER CODE END Service5_Char_12 */
            switch(p_attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN Service5_Char_12_attribute_modified */

              /* USER CODE END Service5_Char_12_attribute_modified */

              /* Disabled Notification management */
              case (0x00):
                /* USER CODE BEGIN Service5_Char_12_Disabled_BEGIN */

                /* USER CODE END Service5_Char_12_Disabled_BEGIN */
                notification.EvtOpcode = CS_CS_OPERATION_MODE_NOTIFY_DISABLED_EVT;
                CS_Notification(&notification);
                /* USER CODE BEGIN Service5_Char_12_Disabled_END */

                /* USER CODE END Service5_Char_12_Disabled_END */
                break;

              /* Enabled Notification management */
              case GATT_CHAR_UPDATE_SEND_NOTIFICATION:
                /* USER CODE BEGIN Service5_Char_12_COMSVC_Notification_BEGIN */

                /* USER CODE END Service5_Char_12_COMSVC_Notification_BEGIN */
                notification.EvtOpcode = CS_CS_OPERATION_MODE_NOTIFY_ENABLED_EVT;
                CS_Notification(&notification);
                /* USER CODE BEGIN Service5_Char_12_COMSVC_Notification_END */

                /* USER CODE END Service5_Char_12_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN Service5_Char_12_default */

                /* USER CODE END Service5_Char_12_default */
                break;
            }
          }

          else if(p_attribute_modified->Attr_Handle == (CS_Context.Cs_Lvdt_AmpCharHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN Service5_Char_13 */

            /* USER CODE END Service5_Char_13 */
            switch(p_attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN Service5_Char_13_attribute_modified */

              /* USER CODE END Service5_Char_13_attribute_modified */

              /* Disabled Notification management */
              case (0x00):
                /* USER CODE BEGIN Service5_Char_13_Disabled_BEGIN */

                /* USER CODE END Service5_Char_13_Disabled_BEGIN */
                notification.EvtOpcode = CS_CS_LVDT_AMP_NOTIFY_DISABLED_EVT;
                CS_Notification(&notification);
                /* USER CODE BEGIN Service5_Char_13_Disabled_END */

                /* USER CODE END Service5_Char_13_Disabled_END */
                break;

              /* Enabled Notification management */
              case GATT_CHAR_UPDATE_SEND_NOTIFICATION:
                /* USER CODE BEGIN Service5_Char_13_COMSVC_Notification_BEGIN */

                /* USER CODE END Service5_Char_13_COMSVC_Notification_BEGIN */
                notification.EvtOpcode = CS_CS_LVDT_AMP_NOTIFY_ENABLED_EVT;
                CS_Notification(&notification);
                /* USER CODE BEGIN Service5_Char_13_COMSVC_Notification_END */

                /* USER CODE END Service5_Char_13_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN Service5_Char_13_default */

                /* USER CODE END Service5_Char_13_default */
                break;
            }
          }

          else if(p_attribute_modified->Attr_Handle == (CS_Context.Cs_TotalizerCharHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN Service5_Char_14 */

            /* USER CODE END Service5_Char_14 */
            switch(p_attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN Service5_Char_14_attribute_modified */

              /* USER CODE END Service5_Char_14_attribute_modified */

              /* Disabled Notification management */
              case (0x00):
                /* USER CODE BEGIN Service5_Char_14_Disabled_BEGIN */

                /* USER CODE END Service5_Char_14_Disabled_BEGIN */
                notification.EvtOpcode = CS_CS_TOTALIZER_NOTIFY_DISABLED_EVT;
                CS_Notification(&notification);
                /* USER CODE BEGIN Service5_Char_14_Disabled_END */

                /* USER CODE END Service5_Char_14_Disabled_END */
                break;

              /* Enabled Notification management */
              case GATT_CHAR_UPDATE_SEND_NOTIFICATION:
                /* USER CODE BEGIN Service5_Char_14_COMSVC_Notification_BEGIN */

                /* USER CODE END Service5_Char_14_COMSVC_Notification_BEGIN */
                notification.EvtOpcode = CS_CS_TOTALIZER_NOTIFY_ENABLED_EVT;
                CS_Notification(&notification);
                /* USER CODE BEGIN Service5_Char_14_COMSVC_Notification_END */

                /* USER CODE END Service5_Char_14_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN Service5_Char_14_default */

                /* USER CODE END Service5_Char_14_default */
                break;
            }
          }

          else if(p_attribute_modified->Attr_Handle == (CS_Context.Cs_Time_Stamp_HhmmCharHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN Service5_Char_16 */

            /* USER CODE END Service5_Char_16 */
            switch(p_attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN Service5_Char_16_attribute_modified */

              /* USER CODE END Service5_Char_16_attribute_modified */

              /* Disabled Notification management */
              case (0x00):
                /* USER CODE BEGIN Service5_Char_16_Disabled_BEGIN */

                /* USER CODE END Service5_Char_16_Disabled_BEGIN */
                notification.EvtOpcode = CS_CS_TIME_STAMP_HHMM_NOTIFY_DISABLED_EVT;
                CS_Notification(&notification);
                /* USER CODE BEGIN Service5_Char_16_Disabled_END */

                /* USER CODE END Service5_Char_16_Disabled_END */
                break;

              /* Enabled Notification management */
              case GATT_CHAR_UPDATE_SEND_NOTIFICATION:
                /* USER CODE BEGIN Service5_Char_16_COMSVC_Notification_BEGIN */

                /* USER CODE END Service5_Char_16_COMSVC_Notification_BEGIN */
                notification.EvtOpcode = CS_CS_TIME_STAMP_HHMM_NOTIFY_ENABLED_EVT;
                CS_Notification(&notification);
                /* USER CODE BEGIN Service5_Char_16_COMSVC_Notification_END */

                /* USER CODE END Service5_Char_16_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN Service5_Char_16_default */

                /* USER CODE END Service5_Char_16_default */
                break;
            }
          }

          else if(p_attribute_modified->Attr_Handle == (CS_Context.Cs_Time_Stamp_DdmmCharHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN Service5_Char_17 */

            /* USER CODE END Service5_Char_17 */
            switch(p_attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN Service5_Char_17_attribute_modified */

              /* USER CODE END Service5_Char_17_attribute_modified */

              /* Disabled Notification management */
              case (0x00):
                /* USER CODE BEGIN Service5_Char_17_Disabled_BEGIN */

                /* USER CODE END Service5_Char_17_Disabled_BEGIN */
                notification.EvtOpcode = CS_CS_TIME_STAMP_DDMM_NOTIFY_DISABLED_EVT;
                CS_Notification(&notification);
                /* USER CODE BEGIN Service5_Char_17_Disabled_END */

                /* USER CODE END Service5_Char_17_Disabled_END */
                break;

              /* Enabled Notification management */
              case GATT_CHAR_UPDATE_SEND_NOTIFICATION:
                /* USER CODE BEGIN Service5_Char_17_COMSVC_Notification_BEGIN */

                /* USER CODE END Service5_Char_17_COMSVC_Notification_BEGIN */
                notification.EvtOpcode = CS_CS_TIME_STAMP_DDMM_NOTIFY_ENABLED_EVT;
                CS_Notification(&notification);
                /* USER CODE BEGIN Service5_Char_17_COMSVC_Notification_END */

                /* USER CODE END Service5_Char_17_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN Service5_Char_17_default */

                /* USER CODE END Service5_Char_17_default */
                break;
            }
          }

          else if(p_attribute_modified->Attr_Handle == (CS_Context.Cs_Year_Stamp_YyyyCharHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN Service5_Char_18 */

            /* USER CODE END Service5_Char_18 */
            switch(p_attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN Service5_Char_18_attribute_modified */

              /* USER CODE END Service5_Char_18_attribute_modified */

              /* Disabled Notification management */
              case (0x00):
                /* USER CODE BEGIN Service5_Char_18_Disabled_BEGIN */

                /* USER CODE END Service5_Char_18_Disabled_BEGIN */
                notification.EvtOpcode = CS_CS_YEAR_STAMP_YYYY_NOTIFY_DISABLED_EVT;
                CS_Notification(&notification);
                /* USER CODE BEGIN Service5_Char_18_Disabled_END */

                /* USER CODE END Service5_Char_18_Disabled_END */
                break;

              /* Enabled Notification management */
              case GATT_CHAR_UPDATE_SEND_NOTIFICATION:
                /* USER CODE BEGIN Service5_Char_18_COMSVC_Notification_BEGIN */

                /* USER CODE END Service5_Char_18_COMSVC_Notification_BEGIN */
                notification.EvtOpcode = CS_CS_YEAR_STAMP_YYYY_NOTIFY_ENABLED_EVT;
                CS_Notification(&notification);
                /* USER CODE BEGIN Service5_Char_18_COMSVC_Notification_END */

                /* USER CODE END Service5_Char_18_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN Service5_Char_18_default */

                /* USER CODE END Service5_Char_18_default */
                break;
            }
          }

          else if(p_attribute_modified->Attr_Handle == (CS_Context.Cs_Totalizer_Last_ValCharHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN Service5_Char_19 */

            /* USER CODE END Service5_Char_19 */
            switch(p_attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN Service5_Char_19_attribute_modified */

              /* USER CODE END Service5_Char_19_attribute_modified */

              /* Disabled Notification management */
              case (0x00):
                /* USER CODE BEGIN Service5_Char_19_Disabled_BEGIN */

                /* USER CODE END Service5_Char_19_Disabled_BEGIN */
                notification.EvtOpcode = CS_CS_TOTALIZER_LAST_VAL_NOTIFY_DISABLED_EVT;
                CS_Notification(&notification);
                /* USER CODE BEGIN Service5_Char_19_Disabled_END */

                /* USER CODE END Service5_Char_19_Disabled_END */
                break;

              /* Enabled Notification management */
              case GATT_CHAR_UPDATE_SEND_NOTIFICATION:
                /* USER CODE BEGIN Service5_Char_19_COMSVC_Notification_BEGIN */

                /* USER CODE END Service5_Char_19_COMSVC_Notification_BEGIN */
                notification.EvtOpcode = CS_CS_TOTALIZER_LAST_VAL_NOTIFY_ENABLED_EVT;
                CS_Notification(&notification);
                /* USER CODE BEGIN Service5_Char_19_COMSVC_Notification_END */

                /* USER CODE END Service5_Char_19_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN Service5_Char_19_default */

                /* USER CODE END Service5_Char_19_default */
                break;
            }
          }

          else if(p_attribute_modified->Attr_Handle == (CS_Context.Cs_Totalizer_UnitCharHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN Service5_Char_20 */

            /* USER CODE END Service5_Char_20 */
            switch(p_attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN Service5_Char_20_attribute_modified */

              /* USER CODE END Service5_Char_20_attribute_modified */

              /* Disabled Notification management */
              case (0x00):
                /* USER CODE BEGIN Service5_Char_20_Disabled_BEGIN */

                /* USER CODE END Service5_Char_20_Disabled_BEGIN */
                notification.EvtOpcode = CS_CS_TOTALIZER_UNIT_NOTIFY_DISABLED_EVT;
                CS_Notification(&notification);
                /* USER CODE BEGIN Service5_Char_20_Disabled_END */

                /* USER CODE END Service5_Char_20_Disabled_END */
                break;

              /* Enabled Notification management */
              case GATT_CHAR_UPDATE_SEND_NOTIFICATION:
                /* USER CODE BEGIN Service5_Char_20_COMSVC_Notification_BEGIN */

                /* USER CODE END Service5_Char_20_COMSVC_Notification_BEGIN */
                notification.EvtOpcode = CS_CS_TOTALIZER_UNIT_NOTIFY_ENABLED_EVT;
                CS_Notification(&notification);
                /* USER CODE BEGIN Service5_Char_20_COMSVC_Notification_END */

                /* USER CODE END Service5_Char_20_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN Service5_Char_20_default */

                /* USER CODE END Service5_Char_20_default */
                break;
            }
          }

          else if(p_attribute_modified->Attr_Handle == (CS_Context.Cs_TotalizerCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CS_CS_TOTALIZER_WRITE_EVT;
            /* USER CODE BEGIN Service5_Char_14_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CS_TOTALIZER CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service5_Char_14_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CS_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CS_Context.Cs_Reset_ButtonCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CS_CS_RESET_BUTTON_WRITE_EVT;
            /* USER CODE BEGIN Service5_Char_15_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CS_RESET_BUTTON CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service5_Char_15_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CS_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CS_Context.Cs_Time_Stamp_HhmmCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CS_CS_TIME_STAMP_HHMM_WRITE_EVT;
            /* USER CODE BEGIN Service5_Char_16_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CS_TIME_STAMP_HHMM CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service5_Char_16_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CS_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CS_Context.Cs_Time_Stamp_DdmmCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CS_CS_TIME_STAMP_DDMM_WRITE_EVT;
            /* USER CODE BEGIN Service5_Char_17_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CS_TIME_STAMP_DDMM CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service5_Char_17_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CS_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CS_Context.Cs_Year_Stamp_YyyyCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CS_CS_YEAR_STAMP_YYYY_WRITE_EVT;
            /* USER CODE BEGIN Service5_Char_18_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
							LOG_INFO_APP("-- GATT : CS_YEAR_STAMP_YYYY CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service5_Char_18_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CS_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CS_Context.Cs_Totalizer_UnitCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CS_CS_TOTALIZER_UNIT_WRITE_EVT;
            /* USER CODE BEGIN Service5_Char_20_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CS_TOTALIZER CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service5_Char_20_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CS_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (CS_Context.Cs_Connection_StatusCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CS_CS_CONNECTION_STATUS_WRITE_EVT;
            /* USER CODE BEGIN Service5_Char_21_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CS_CONNECTION CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service5_Char_21_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CS_Notification(&notification);
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
          if(p_read_req->Attribute_Handle == (CS_Context.Cs_FlowtempCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service5_Char_1_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service5_Char_1_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service5_Char_1_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CS_CS_FLOWTEMP_READ_EVT;  
						CS_Notification(&notification);
            /*USER CODE END Service5_Char_1_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CS_Context.Cs_P2T2CharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service5_Char_2_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service5_Char_2_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service5_Char_2_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CS_CS_P2T2_READ_EVT; 
						CS_Notification(&notification);
            /*USER CODE END Service5_Char_2_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CS_Context.Cs_P1T1CharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service5_Char_3_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service5_Char_3_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service5_Char_3_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CS_CS_P1T1_READ_EVT;
						CS_Notification(&notification);
            /*USER CODE END Service5_Char_3_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CS_Context.Cs_Unit_P2T2CharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service5_Char_4_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service5_Char_4_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service5_Char_4_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CS_CS_UNIT_P2T2_READ_EVT;
						CS_Notification(&notification);
            /*USER CODE END Service5_Char_4_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CS_Context.Cs_Unit_P1T1CharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service5_Char_5_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service5_Char_5_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service5_Char_5_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CS_CS_UNIT_P1T1_READ_EVT;
						CS_Notification(&notification);
            /*USER CODE END Service5_Char_5_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CS_Context.Cs_Mod_Com_ErrorCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service5_Char_6_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service5_Char_6_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service5_Char_6_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CS_CS_MOD_COM_ERROR_READ_EVT;
						CS_Notification(&notification);
            /*USER CODE END Service5_Char_6_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CS_Context.Cs_Diag_ErrorCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service5_Char_7_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service5_Char_7_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service5_Char_7_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CS_CS_DIAG_ERROR_READ_EVT;
						CS_Notification(&notification);
            /*USER CODE END Service5_Char_7_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CS_Context.Cs_Diag_WarnCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service5_Char_8_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service5_Char_8_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service5_Char_8_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CS_CS_DIAG_WARN_READ_EVT; 
						CS_Notification(&notification);
            /*USER CODE END Service5_Char_8_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CS_Context.Cs_Inlet_Pres_Pd1CharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service5_Char_9_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service5_Char_9_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service5_Char_9_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CS_CS_INLET_PRES_PD1_READ_EVT;
						CS_Notification(&notification);
            /*USER CODE END Service5_Char_9_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CS_Context.Cs_Outlet_Pres_Pd2CharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service5_Char_10_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service5_Char_10_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service5_Char_10_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CS_CS_OUTLET_PRES_PD2_READ_EVT;
						CS_Notification(&notification);
            /*USER CODE END Service5_Char_10_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CS_Context.Cs_Opening_PerCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service5_Char_11_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service5_Char_11_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service5_Char_11_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CS_CS_OPENING_PER_READ_EVT;
						CS_Notification(&notification);
            /*USER CODE END Service5_Char_11_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CS_Context.Cs_Operation_ModeCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service5_Char_12_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service5_Char_12_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service5_Char_12_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CS_CS_OPERATION_MODE_READ_EVT;
						CS_Notification(&notification);
            /*USER CODE END Service5_Char_12_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CS_Context.Cs_Lvdt_AmpCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service5_Char_13_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service5_Char_13_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service5_Char_13_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CS_CS_LVDT_AMP_READ_EVT;
						CS_Notification(&notification);
            /*USER CODE END Service5_Char_13_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CS_Context.Cs_TotalizerCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service5_Char_14_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service5_Char_14_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service5_Char_14_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CS_CS_TOTALIZER_READ_EVT;
						CS_Notification(&notification);
            /*USER CODE END Service5_Char_14_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CS_Context.Cs_Reset_ButtonCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service5_Char_15_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service5_Char_15_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service5_Char_15_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CS_CS_RESET_BUTTON_READ_EVT;
						CS_Notification(&notification);
            /*USER CODE END Service5_Char_15_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CS_Context.Cs_Time_Stamp_HhmmCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service5_Char_16_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service5_Char_16_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service5_Char_16_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CS_CS_TIME_STAMP_HHMM_READ_EVT;
						CS_Notification(&notification);
            /*USER CODE END Service5_Char_16_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CS_Context.Cs_Time_Stamp_DdmmCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service5_Char_17_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service5_Char_17_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service5_Char_17_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CS_CS_TIME_STAMP_DDMM_READ_EVT;
						CS_Notification(&notification);
            /*USER CODE END Service5_Char_17_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CS_Context.Cs_Year_Stamp_YyyyCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service5_Char_18_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service5_Char_18_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service5_Char_18_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CS_CS_YEAR_STAMP_YYYY_READ_EVT;
						CS_Notification(&notification);
            /*USER CODE END Service5_Char_18_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CS_Context.Cs_Totalizer_Last_ValCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service5_Char_19_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service5_Char_19_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service5_Char_19_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CS_CS_TOTALIZER_LAST_VAL_READ_EVT;
						CS_Notification(&notification);
            /*USER CODE END Service5_Char_19_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CS_Context.Cs_Totalizer_UnitCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service5_Char_20_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service5_Char_20_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service5_Char_20_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CS_CS_TOTALIZER_UNIT_READ_EVT;
						CS_Notification(&notification);
            /*USER CODE END Service5_Char_20_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CS_Context.Cs_Connection_StatusCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service5_Char_21_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service5_Char_21_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service5_Char_21_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CS_CS_CONNECTION_STATUS_READ_EVT;
						CS_Notification(&notification);
            /*USER CODE END Service5_Char_21_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
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

  /* USER CODE BEGIN Service5_EventHandler_2 */

  /* USER CODE END Service5_EventHandler_2 */

  return(return_value);
}/* end CS_EventHandler */

/* Public functions ----------------------------------------------------------*/

/**
 * @brief  Service initialization
 * @param  None
 * @retval None
 */
void CS_Init(void)
{
  Char_UUID_t  uuid;
  tBleStatus ret;
  uint8_t max_attr_record;

  /* USER CODE BEGIN SVCCTL_InitService5Svc_1 */

  /* USER CODE END SVCCTL_InitService5Svc_1 */

  /**
   *  Register the event handler to the BLE controller
   */
  SVCCTL_RegisterSvcHandler(CS_EventHandler);

  /**
   * CS
   *
   * Max_Attribute_Records = 1 + 2*21 + 1*no_of_char_with_notify_or_indicate_property + 1*no_of_char_with_broadcast_property
   * service_max_attribute_record = 1 for CS +
   *                                2 for CS_FLOWTEMP +
   *                                2 for CS_P2T2 +
   *                                2 for CS_P1T1 +
   *                                2 for CS_UNIT_P2T2 +
   *                                2 for CS_UNIT_P1T1 +
   *                                2 for CS_MOD_COM_ERROR +
   *                                2 for CS_DIAG_ERROR +
   *                                2 for CS_DIAG_WARN +
   *                                2 for CS_INLET_PRES_PD1 +
   *                                2 for CS_OUTLET_PRES_PD2 +
   *                                2 for CS_OPENING_PER +
   *                                2 for CS_OPERATION_MODE +
   *                                2 for CS_LVDT_AMP +
   *                                2 for CS_TOTALIZER +
   *                                2 for CS_RESET_BUTTON +
   *                                2 for CS_TIME_STAMP_HHMM +
   *                                2 for CS_TIME_STAMP_DDMM +
   *                                2 for CS_YEAR_STAMP_YYYY +
   *                                2 for CS_TOTALIZER_LAST_VAL +
   *                                2 for CS_TOTALIZER_UNIT +
   *                                2 for CS_CONNECTION_STATUS +
   *                                1 for CS_FLOWTEMP configuration descriptor +
   *                                1 for CS_P2T2 configuration descriptor +
   *                                1 for CS_P1T1 configuration descriptor +
   *                                1 for CS_UNIT_P2T2 configuration descriptor +
   *                                1 for CS_UNIT_P1T1 configuration descriptor +
   *                                1 for CS_MOD_COM_ERROR configuration descriptor +
   *                                1 for CS_DIAG_ERROR configuration descriptor +
   *                                1 for CS_DIAG_WARN configuration descriptor +
   *                                1 for CS_INLET_PRES_PD1 configuration descriptor +
   *                                1 for CS_OUTLET_PRES_PD2 configuration descriptor +
   *                                1 for CS_OPENING_PER configuration descriptor +
   *                                1 for CS_OPERATION_MODE configuration descriptor +
   *                                1 for CS_LVDT_AMP configuration descriptor +
   *                                1 for CS_TOTALIZER configuration descriptor +
   *                                1 for CS_TIME_STAMP_HHMM configuration descriptor +
   *                                1 for CS_TIME_STAMP_DDMM configuration descriptor +
   *                                1 for CS_YEAR_STAMP_YYYY configuration descriptor +
   *                                1 for CS_TOTALIZER_LAST_VAL configuration descriptor +
   *                                1 for CS_TOTALIZER_UNIT configuration descriptor +
   *                              = 62
   * This value doesn't take into account number of descriptors manually added
   * In case of descriptors added, please update the max_attr_record value accordingly in the next SVCCTL_InitService User Section
   */
  max_attr_record = 62;

  /* USER CODE BEGIN SVCCTL_InitService */
  /* max_attr_record to be updated if descriptors have been added */

  /* USER CODE END SVCCTL_InitService */

  COPY_CS_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_service(UUID_TYPE_128,
                             (Service_UUID_t *) &uuid,
                             PRIMARY_SERVICE,
                             max_attr_record,
                             &(CS_Context.CsSvcHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_service command: CS, error code: 0x%x \n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_service command: CsSvcHdle = 0x%04X\n",CS_Context.CsSvcHdle);
  }

  /**
   * CS_FLOWTEMP
   */
  COPY_CS_FLOWTEMP_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CS_Context.CsSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCs_Flowtemp,
                          CHAR_PROP_READ | CHAR_PROP_NOTIFY,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CS_Context.Cs_FlowtempCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CS_FLOWTEMP, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cs_FlowtempCharHdle = 0x%04X\n",CS_Context.Cs_FlowtempCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService5Char1 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService5Char1 */

  /**
   * CS_P2T2
   */
  COPY_CS_P2T2_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CS_Context.CsSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCs_P2T2,
                          CHAR_PROP_READ | CHAR_PROP_NOTIFY,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CS_Context.Cs_P2T2CharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CS_P2T2, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cs_P2T2CharHdle = 0x%04X\n",CS_Context.Cs_P2T2CharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService5Char2 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService5Char2 */

  /**
   * CS_P1T1
   */
  COPY_CS_P1T1_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CS_Context.CsSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCs_P1T1,
                          CHAR_PROP_READ | CHAR_PROP_NOTIFY,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CS_Context.Cs_P1T1CharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CS_P1T1, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cs_P1T1CharHdle = 0x%04X\n",CS_Context.Cs_P1T1CharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService5Char3 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService5Char3 */

  /**
   * CS_UNIT_P2T2
   */
  COPY_CS_UNIT_P2T2_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CS_Context.CsSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCs_Unit_P2T2,
                          CHAR_PROP_READ | CHAR_PROP_NOTIFY,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CS_Context.Cs_Unit_P2T2CharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CS_UNIT_P2T2, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cs_Unit_P2T2CharHdle = 0x%04X\n",CS_Context.Cs_Unit_P2T2CharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService5Char4 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService5Char4 */

  /**
   * CS_UNIT_P1T1
   */
  COPY_CS_UNIT_P1T1_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CS_Context.CsSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCs_Unit_P1T1,
                          CHAR_PROP_READ | CHAR_PROP_NOTIFY,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CS_Context.Cs_Unit_P1T1CharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CS_UNIT_P1T1, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cs_Unit_P1T1CharHdle = 0x%04X\n",CS_Context.Cs_Unit_P1T1CharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService5Char5 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService5Char5 */

  /**
   * CS_MOD_COM_ERROR
   */
  COPY_CS_MOD_COM_ERROR_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CS_Context.CsSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCs_Mod_Com_Error,
                          CHAR_PROP_READ | CHAR_PROP_NOTIFY,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CS_Context.Cs_Mod_Com_ErrorCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CS_MOD_COM_ERROR, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cs_Mod_Com_ErrorCharHdle = 0x%04X\n",CS_Context.Cs_Mod_Com_ErrorCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService5Char6 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService5Char6 */

  /**
   * CS_DIAG_ERROR
   */
  COPY_CS_DIAG_ERROR_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CS_Context.CsSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCs_Diag_Error,
                          CHAR_PROP_READ | CHAR_PROP_NOTIFY,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CS_Context.Cs_Diag_ErrorCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CS_DIAG_ERROR, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cs_Diag_ErrorCharHdle = 0x%04X\n",CS_Context.Cs_Diag_ErrorCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService5Char7 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService5Char7 */

  /**
   * CS_DIAG_WARN
   */
  COPY_CS_DIAG_WARN_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CS_Context.CsSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCs_Diag_Warn,
                          CHAR_PROP_READ | CHAR_PROP_NOTIFY,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CS_Context.Cs_Diag_WarnCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CS_DIAG_WARN, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cs_Diag_WarnCharHdle = 0x%04X\n",CS_Context.Cs_Diag_WarnCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService5Char8 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService5Char8 */

  /**
   * CS_INLET_PRES_PD1
   */
  COPY_CS_INLET_PRES_PD1_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CS_Context.CsSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCs_Inlet_Pres_Pd1,
                          CHAR_PROP_READ | CHAR_PROP_NOTIFY,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CS_Context.Cs_Inlet_Pres_Pd1CharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CS_INLET_PRES_PD1, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cs_Inlet_Pres_Pd1CharHdle = 0x%04X\n",CS_Context.Cs_Inlet_Pres_Pd1CharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService5Char9 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService5Char9 */

  /**
   * CS_OUTLET_PRES_PD2
   */
  COPY_CS_OUTLET_PRES_PD2_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CS_Context.CsSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCs_Outlet_Pres_Pd2,
                          CHAR_PROP_READ | CHAR_PROP_NOTIFY,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_WRITE_REQ_AND_WAIT_FOR_APPL_RESP | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CS_Context.Cs_Outlet_Pres_Pd2CharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CS_OUTLET_PRES_PD2, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cs_Outlet_Pres_Pd2CharHdle = 0x%04X\n",CS_Context.Cs_Outlet_Pres_Pd2CharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService5Char10 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService5Char10 */

  /**
   * CS_OPENING_PER
   */
  COPY_CS_OPENING_PER_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CS_Context.CsSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCs_Opening_Per,
                          CHAR_PROP_READ | CHAR_PROP_NOTIFY,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CS_Context.Cs_Opening_PerCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CS_OPENING_PER, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cs_Opening_PerCharHdle = 0x%04X\n",CS_Context.Cs_Opening_PerCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService5Char11 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService5Char11 */

  /**
   * CS_OPERATION_MODE
   */
  COPY_CS_OPERATION_MODE_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CS_Context.CsSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCs_Operation_Mode,
                          CHAR_PROP_READ | CHAR_PROP_NOTIFY,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CS_Context.Cs_Operation_ModeCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CS_OPERATION_MODE, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cs_Operation_ModeCharHdle = 0x%04X\n",CS_Context.Cs_Operation_ModeCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService5Char12 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService5Char12 */

  /**
   * CS_LVDT_AMP
   */
  COPY_CS_LVDT_AMP_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CS_Context.CsSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCs_Lvdt_Amp,
                          CHAR_PROP_READ | CHAR_PROP_NOTIFY,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CS_Context.Cs_Lvdt_AmpCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CS_LVDT_AMP, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cs_Lvdt_AmpCharHdle = 0x%04X\n",CS_Context.Cs_Lvdt_AmpCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService5Char13 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService5Char13 */

  /**
   * CS_TOTALIZER
   */
  COPY_CS_TOTALIZER_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CS_Context.CsSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCs_Totalizer,
                          CHAR_PROP_READ | CHAR_PROP_WRITE | CHAR_PROP_NOTIFY,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CS_Context.Cs_TotalizerCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CS_TOTALIZER, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cs_TotalizerCharHdle = 0x%04X\n",CS_Context.Cs_TotalizerCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService5Char14 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService5Char14 */

  /**
   * CS_RESET_BUTTON
   */
  COPY_CS_RESET_BUTTON_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CS_Context.CsSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCs_Reset_Button,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CS_Context.Cs_Reset_ButtonCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CS_RESET_BUTTON, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cs_Reset_ButtonCharHdle = 0x%04X\n",CS_Context.Cs_Reset_ButtonCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService5Char15 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService5Char15 */

  /**
   * CS_TIME_STAMP_HHMM
   */
  COPY_CS_TIME_STAMP_HHMM_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CS_Context.CsSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCs_Time_Stamp_Hhmm,
                          CHAR_PROP_READ | CHAR_PROP_WRITE | CHAR_PROP_NOTIFY,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CS_Context.Cs_Time_Stamp_HhmmCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CS_TIME_STAMP_HHMM, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cs_Time_Stamp_HhmmCharHdle = 0x%04X\n",CS_Context.Cs_Time_Stamp_HhmmCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService5Char16 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService5Char16 */

  /**
   * CS_TIME_STAMP_DDMM
   */
  COPY_CS_TIME_STAMP_DDMM_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CS_Context.CsSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCs_Time_Stamp_Ddmm,
                          CHAR_PROP_READ | CHAR_PROP_WRITE | CHAR_PROP_NOTIFY,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CS_Context.Cs_Time_Stamp_DdmmCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CS_TIME_STAMP_DDMM, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cs_Time_Stamp_DdmmCharHdle = 0x%04X\n",CS_Context.Cs_Time_Stamp_DdmmCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService5Char17 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService5Char17 */

  /**
   * CS_YEAR_STAMP_YYYY
   */
  COPY_CS_YEAR_STAMP_YYYY_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CS_Context.CsSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCs_Year_Stamp_Yyyy,
                          CHAR_PROP_READ | CHAR_PROP_WRITE | CHAR_PROP_NOTIFY,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CS_Context.Cs_Year_Stamp_YyyyCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CS_YEAR_STAMP_YYYY, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cs_Year_Stamp_YyyyCharHdle = 0x%04X\n",CS_Context.Cs_Year_Stamp_YyyyCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService5Char18 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService5Char18 */

  /**
   * CS_TOTALIZER_LAST_VAL
   */
  COPY_CS_TOTALIZER_LAST_VAL_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CS_Context.CsSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCs_Totalizer_Last_Val,
                          CHAR_PROP_READ | CHAR_PROP_NOTIFY,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CS_Context.Cs_Totalizer_Last_ValCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CS_TOTALIZER_LAST_VAL, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cs_Totalizer_Last_ValCharHdle = 0x%04X\n",CS_Context.Cs_Totalizer_Last_ValCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService5Char19 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService5Char19 */

  /**
   * CS_TOTALIZER_UNIT
   */
  COPY_CS_TOTALIZER_UNIT_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CS_Context.CsSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCs_Totalizer_Unit,
                          CHAR_PROP_READ | CHAR_PROP_WRITE | CHAR_PROP_NOTIFY,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CS_Context.Cs_Totalizer_UnitCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CS_TOTALIZER_UNIT, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cs_Totalizer_UnitCharHdle = 0x%04X\n",CS_Context.Cs_Totalizer_UnitCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService5Char20 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService5Char20 */

  /**
   * CS_CONNECTION_STATUS
   */
  COPY_CS_CONNECTION_STATUS_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CS_Context.CsSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCs_Connection_Status,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CS_Context.Cs_Connection_StatusCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CS_CONNECTION_STATUS, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cs_Connection_StatusCharHdle = 0x%04X\n",CS_Context.Cs_Connection_StatusCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService5Char21 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService5Char21 */

  /* USER CODE BEGIN SVCCTL_InitService5Svc_2 */

  /* USER CODE END SVCCTL_InitService5Svc_2 */

  return;
}

/**
 * @brief  Characteristic update
 * @param  CharOpcode: Characteristic identifier
 * @param  pData: Structure holding data to update
 *
 */
tBleStatus CS_UpdateValue(CS_CharOpcode_t CharOpcode, CS_Data_t *pData)
{
  tBleStatus ret = BLE_STATUS_INVALID_PARAMS;
  /* USER CODE BEGIN Service5_App_Update_Char_1 */

  /* USER CODE END Service5_App_Update_Char_1 */

  switch(CharOpcode)
  {
    case CS_CS_FLOWTEMP:
      ret = aci_gatt_update_char_value(CS_Context.CsSvcHdle,
                                       CS_Context.Cs_FlowtempCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CS_FLOWTEMP command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CS_FLOWTEMP command\n");
      }
      /* USER CODE BEGIN Service5_Char_Value_1 */

      /* USER CODE END Service5_Char_Value_1 */
      break;

    case CS_CS_P2T2:
      ret = aci_gatt_update_char_value(CS_Context.CsSvcHdle,
                                       CS_Context.Cs_P2T2CharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CS_P2T2 command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CS_P2T2 command\n");
      }
      /* USER CODE BEGIN Service5_Char_Value_2 */

      /* USER CODE END Service5_Char_Value_2 */
      break;

    case CS_CS_P1T1:
      ret = aci_gatt_update_char_value(CS_Context.CsSvcHdle,
                                       CS_Context.Cs_P1T1CharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CS_P1T1 command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CS_P1T1 command\n");
      }
      /* USER CODE BEGIN Service5_Char_Value_3 */

      /* USER CODE END Service5_Char_Value_3 */
      break;

    case CS_CS_UNIT_P2T2:
      ret = aci_gatt_update_char_value(CS_Context.CsSvcHdle,
                                       CS_Context.Cs_Unit_P2T2CharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CS_UNIT_P2T2 command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CS_UNIT_P2T2 command\n");
      }
      /* USER CODE BEGIN Service5_Char_Value_4 */

      /* USER CODE END Service5_Char_Value_4 */
      break;

    case CS_CS_UNIT_P1T1:
      ret = aci_gatt_update_char_value(CS_Context.CsSvcHdle,
                                       CS_Context.Cs_Unit_P1T1CharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CS_UNIT_P1T1 command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CS_UNIT_P1T1 command\n");
      }
      /* USER CODE BEGIN Service5_Char_Value_5 */

      /* USER CODE END Service5_Char_Value_5 */
      break;

    case CS_CS_MOD_COM_ERROR:
      ret = aci_gatt_update_char_value(CS_Context.CsSvcHdle,
                                       CS_Context.Cs_Mod_Com_ErrorCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CS_MOD_COM_ERROR command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CS_MOD_COM_ERROR command\n");
      }
      /* USER CODE BEGIN Service5_Char_Value_6 */

      /* USER CODE END Service5_Char_Value_6 */
      break;

    case CS_CS_DIAG_ERROR:
      ret = aci_gatt_update_char_value(CS_Context.CsSvcHdle,
                                       CS_Context.Cs_Diag_ErrorCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CS_DIAG_ERROR command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CS_DIAG_ERROR command\n");
      }
      /* USER CODE BEGIN Service5_Char_Value_7 */

      /* USER CODE END Service5_Char_Value_7 */
      break;

    case CS_CS_DIAG_WARN:
      ret = aci_gatt_update_char_value(CS_Context.CsSvcHdle,
                                       CS_Context.Cs_Diag_WarnCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CS_DIAG_WARN command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CS_DIAG_WARN command\n");
      }
      /* USER CODE BEGIN Service5_Char_Value_8 */

      /* USER CODE END Service5_Char_Value_8 */
      break;

    case CS_CS_INLET_PRES_PD1:
      ret = aci_gatt_update_char_value(CS_Context.CsSvcHdle,
                                       CS_Context.Cs_Inlet_Pres_Pd1CharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CS_INLET_PRES_PD1 command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CS_INLET_PRES_PD1 command\n");
      }
      /* USER CODE BEGIN Service5_Char_Value_9 */

      /* USER CODE END Service5_Char_Value_9 */
      break;

    case CS_CS_OUTLET_PRES_PD2:
      ret = aci_gatt_update_char_value(CS_Context.CsSvcHdle,
                                       CS_Context.Cs_Outlet_Pres_Pd2CharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CS_OUTLET_PRES_PD2 command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CS_OUTLET_PRES_PD2 command\n");
      }
      /* USER CODE BEGIN Service5_Char_Value_10 */

      /* USER CODE END Service5_Char_Value_10 */
      break;

    case CS_CS_OPENING_PER:
      ret = aci_gatt_update_char_value(CS_Context.CsSvcHdle,
                                       CS_Context.Cs_Opening_PerCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CS_OPENING_PER command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CS_OPENING_PER command\n");
      }
      /* USER CODE BEGIN Service5_Char_Value_11 */

      /* USER CODE END Service5_Char_Value_11 */
      break;

    case CS_CS_OPERATION_MODE:
      ret = aci_gatt_update_char_value(CS_Context.CsSvcHdle,
                                       CS_Context.Cs_Operation_ModeCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CS_OPERATION_MODE command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CS_OPERATION_MODE command\n");
      }
      /* USER CODE BEGIN Service5_Char_Value_12 */

      /* USER CODE END Service5_Char_Value_12 */
      break;

    case CS_CS_LVDT_AMP:
      ret = aci_gatt_update_char_value(CS_Context.CsSvcHdle,
                                       CS_Context.Cs_Lvdt_AmpCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CS_LVDT_AMP command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CS_LVDT_AMP command\n");
      }
      /* USER CODE BEGIN Service5_Char_Value_13 */

      /* USER CODE END Service5_Char_Value_13 */
      break;

    case CS_CS_TOTALIZER:
      ret = aci_gatt_update_char_value(CS_Context.CsSvcHdle,
                                       CS_Context.Cs_TotalizerCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CS_TOTALIZER command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CS_TOTALIZER command\n");
      }
      /* USER CODE BEGIN Service5_Char_Value_14 */

      /* USER CODE END Service5_Char_Value_14 */
      break;

    case CS_CS_RESET_BUTTON:
      ret = aci_gatt_update_char_value(CS_Context.CsSvcHdle,
                                       CS_Context.Cs_Reset_ButtonCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CS_RESET_BUTTON command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CS_RESET_BUTTON command\n");
      }
      /* USER CODE BEGIN Service5_Char_Value_15 */

      /* USER CODE END Service5_Char_Value_15 */
      break;

    case CS_CS_TIME_STAMP_HHMM:
      ret = aci_gatt_update_char_value(CS_Context.CsSvcHdle,
                                       CS_Context.Cs_Time_Stamp_HhmmCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CS_TIME_STAMP_HHMM command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CS_TIME_STAMP_HHMM command\n");
      }
      /* USER CODE BEGIN Service5_Char_Value_16 */

      /* USER CODE END Service5_Char_Value_16 */
      break;

    case CS_CS_TIME_STAMP_DDMM:
      ret = aci_gatt_update_char_value(CS_Context.CsSvcHdle,
                                       CS_Context.Cs_Time_Stamp_DdmmCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CS_TIME_STAMP_DDMM command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CS_TIME_STAMP_DDMM command\n");
      }
      /* USER CODE BEGIN Service5_Char_Value_17 */

      /* USER CODE END Service5_Char_Value_17 */
      break;

    case CS_CS_YEAR_STAMP_YYYY:
      ret = aci_gatt_update_char_value(CS_Context.CsSvcHdle,
                                       CS_Context.Cs_Year_Stamp_YyyyCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CS_YEAR_STAMP_YYYY command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CS_YEAR_STAMP_YYYY command\n");
      }
      /* USER CODE BEGIN Service5_Char_Value_18 */

      /* USER CODE END Service5_Char_Value_18 */
      break;

    case CS_CS_TOTALIZER_LAST_VAL:
      ret = aci_gatt_update_char_value(CS_Context.CsSvcHdle,
                                       CS_Context.Cs_Totalizer_Last_ValCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CS_TOTALIZER_LAST_VAL command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CS_TOTALIZER_LAST_VAL command\n");
      }
      /* USER CODE BEGIN Service5_Char_Value_19 */

      /* USER CODE END Service5_Char_Value_19 */
      break;

    case CS_CS_TOTALIZER_UNIT:
      ret = aci_gatt_update_char_value(CS_Context.CsSvcHdle,
                                       CS_Context.Cs_Totalizer_UnitCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CS_TOTALIZER_UNIT command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CS_TOTALIZER_UNIT command\n");
      }
      /* USER CODE BEGIN Service5_Char_Value_20 */

      /* USER CODE END Service5_Char_Value_20 */
      break;

    case CS_CS_CONNECTION_STATUS:
      ret = aci_gatt_update_char_value(CS_Context.CsSvcHdle,
                                       CS_Context.Cs_Connection_StatusCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CS_CONNECTION_STATUS command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CS_CONNECTION_STATUS command\n");
      }
      /* USER CODE BEGIN Service5_Char_Value_21 */

      /* USER CODE END Service5_Char_Value_21 */
      break;

    default:
      break;
  }

  /* USER CODE BEGIN Service5_App_Update_Char_2 */

  /* USER CODE END Service5_App_Update_Char_2 */

  return ret;
}
