/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    p2p_server.c
  * @author  MCD Application Team
  * @brief   p2p_server definition.
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
#include "log_module.h"
#include "p2p_server.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/

/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

typedef struct{
  uint16_t  P2p_serverSvcHdle;                  /**< P2p_server Service Handle */
  uint16_t  MidCharHdle;                  /**< MID Characteristic Handle */
  uint16_t  ProdnameCharHdle;                  /**< PRODNAME Characteristic Handle */
  uint16_t  SlnmCharHdle;                  /**< SLNM Characteristic Handle */
  uint16_t  DevlocCharHdle;                  /**< DEVLOC Characteristic Handle */
  uint16_t  DsCharHdle;                  /**< DS Characteristic Handle */
  uint16_t  DevmkeCharHdle;                  /**< DEVMKE Characteristic Handle */
  uint16_t  DevmacCharHdle;                  /**< DEVMAC Characteristic Handle */
  uint16_t  BlestkfwCharHdle;                  /**< BLESTKFW Characteristic Handle */
  uint16_t  AppfwCharHdle;                  /**< APPFW Characteristic Handle */
  uint16_t  AdvnameCharHdle;                  /**< ADVNAME Characteristic Handle */
/* USER CODE BEGIN Context */
  /* Place holder for Characteristic Descriptors Handle*/

/* USER CODE END Context */
}P2P_SERVER_Context_t;

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
static const uint16_t SizeMid = 1;
static const uint16_t SizeProdname = 64;
static const uint16_t SizeSlnm = 8;
static const uint16_t SizeDevloc = 100;
static const uint16_t SizeDs = 1;
static const uint16_t SizeDevmke = 100;
static const uint16_t SizeDevmac = 6;
static const uint16_t SizeBlestkfw = 20;
static const uint16_t SizeAppfw = 20;
static const uint16_t SizeAdvname = 20;

static P2P_SERVER_Context_t P2P_SERVER_Context;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static SVCCTL_EvtAckStatus_t P2P_SERVER_EventHandler(void *p_pckt);

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
 F364000000B04240BA5005CA45BF8ABC: Service 128bits UUID
 F364000100B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364000200B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364000300B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364000400B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364000500B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364000600B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364000700B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364000800B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364000900B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364000A00B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 */
#define COPY_P2P_SERVER_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x00,0x00,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_MID_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x00,0x01,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_PRODNAME_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x00,0x02,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_SLNM_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x00,0x03,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_DEVLOC_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x00,0x04,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_DS_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x00,0x05,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_DEVMKE_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x00,0x06,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_DEVMAC_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x00,0x07,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_BLESTKFW_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x00,0x08,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_APPFW_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x00,0x09,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_ADVNAME_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x00,0x0a,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)

/* USER CODE BEGIN PF */

/* USER CODE END PF */

/**
 * @brief  Event handler
 * @param  p_Event: Address of the buffer holding the p_Event
 * @retval Ack: Return whether the p_Event has been managed or not
 */
static SVCCTL_EvtAckStatus_t P2P_SERVER_EventHandler(void *p_Event)
{
  SVCCTL_EvtAckStatus_t return_value;
  hci_event_pckt *p_event_pckt;
  evt_blecore_aci *p_blecore_evt;
  aci_gatt_attribute_modified_event_rp0 *p_attribute_modified;
  aci_gatt_read_permit_req_event_rp0    *p_read_req;
  P2P_SERVER_NotificationEvt_t                 notification;
  /* USER CODE BEGIN Service1_EventHandler_1 */

  /* USER CODE END Service1_EventHandler_1 */

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
          if(p_attribute_modified->Attr_Handle == (P2P_SERVER_Context.MidCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = P2P_SERVER_MID_WRITE_EVT;
            /* USER CODE BEGIN Service1_Char_1_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            LOG_INFO_APP("-- GATT : MID CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service1_Char_1_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            P2P_SERVER_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (P2P_SERVER_Context.DevlocCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = P2P_SERVER_DEVLOC_WRITE_EVT;
            /* USER CODE BEGIN Service1_Char_4_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            LOG_INFO_APP("-- GATT : DEVICELOC CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service1_Char_4_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            P2P_SERVER_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (P2P_SERVER_Context.DsCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = P2P_SERVER_DS_WRITE_EVT;
            /* USER CODE BEGIN Service1_Char_5_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            LOG_INFO_APP("-- GATT : DS CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service1_Char_5_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            P2P_SERVER_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (P2P_SERVER_Context.DevmkeCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = P2P_SERVER_DEVMKE_WRITE_EVT;
            /* USER CODE BEGIN Service1_Char_6_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            LOG_INFO_APP("-- GATT : DEVICEMAKE CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service1_Char_6_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            P2P_SERVER_Notification(&notification);
          }
          else if(p_attribute_modified->Attr_Handle == (P2P_SERVER_Context.AdvnameCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = P2P_SERVER_ADVNAME_WRITE_EVT;
            /* USER CODE BEGIN Service1_Char_10_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            LOG_INFO_APP("-- GATT : ADVNAME CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service1_Char_10_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            P2P_SERVER_Notification(&notification);
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
          if(p_read_req->Attribute_Handle == (P2P_SERVER_Context.MidCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service1_Char_1_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service1_Char_1_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service1_Char_1_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
//#warning user shall call aci_gatt_allow_read() function if allowed
            aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = P2P_SERVER_MID_READ_EVT;
            P2P_SERVER_Notification(&notification);
            /*USER CODE END Service1_Char_1_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (P2P_SERVER_Context.ProdnameCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service1_Char_2_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service1_Char_2_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service1_Char_2_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
//#warning user shall call aci_gatt_allow_read() function if allowed
            aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = P2P_SERVER_PRODNAME_READ_EVT;
            P2P_SERVER_Notification(&notification);
            /*USER CODE END Service1_Char_2_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (P2P_SERVER_Context.SlnmCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service1_Char_3_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service1_Char_3_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service1_Char_3_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
//#warning user shall call aci_gatt_allow_read() function if allowed
            aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = P2P_SERVER_SLNM_READ_EVT;
            P2P_SERVER_Notification(&notification);
            /*USER CODE END Service1_Char_3_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (P2P_SERVER_Context.DevlocCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service1_Char_4_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service1_Char_4_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service1_Char_4_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
//#warning user shall call aci_gatt_allow_read() function if allowed
            aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = P2P_SERVER_DEVLOC_READ_EVT;
            P2P_SERVER_Notification(&notification);
            /*USER CODE END Service1_Char_4_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (P2P_SERVER_Context.DsCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service1_Char_5_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service1_Char_5_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service1_Char_5_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
//#warning user shall call aci_gatt_allow_read() function if allowed
            aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = P2P_SERVER_DS_READ_EVT;
            P2P_SERVER_Notification(&notification);
            /*USER CODE END Service1_Char_5_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (P2P_SERVER_Context.DevmkeCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service1_Char_6_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service1_Char_6_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service1_Char_6_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
//#warning user shall call aci_gatt_allow_read() function if allowed
            aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = P2P_SERVER_DEVMKE_READ_EVT;
            P2P_SERVER_Notification(&notification);
            /*USER CODE END Service1_Char_6_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (P2P_SERVER_Context.DevmacCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service1_Char_7_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service1_Char_7_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service1_Char_7_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
//#warning user shall call aci_gatt_allow_read() function if allowed
            aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = P2P_SERVER_DEVMAC_READ_EVT;
            P2P_SERVER_Notification(&notification);
            /*USER CODE END Service1_Char_7_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (P2P_SERVER_Context.AppfwCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service1_Char_9_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service1_Char_9_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service1_Char_9_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
//#warning user shall call aci_gatt_allow_read() function if allowed
            aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = P2P_SERVER_APPFW_READ_EVT;
            P2P_SERVER_Notification(&notification);
            /*USER CODE END Service1_Char_9_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (P2P_SERVER_Context.AdvnameCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service1_Char_10_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service1_Char_10_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service1_Char_10_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
//#warning user shall call aci_gatt_allow_read() function if allowed
            aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = P2P_SERVER_ADVNAME_READ_EVT;
            P2P_SERVER_Notification(&notification);
            /*USER CODE END Service1_Char_10_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
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
        /* Manage ACI_GATT_INDICATION_VSEVT_CODE occurring on Android 12 */
        case ACI_GATT_INDICATION_VSEVT_CODE:
          {
            aci_gatt_indication_event_rp0 *pr = (void*)p_blecore_evt->data;
            tBleStatus status = aci_gatt_confirm_indication(pr->Connection_Handle);
            if (status != BLE_STATUS_SUCCESS)
            {
              LOG_INFO_APP("  Fail   : aci_gatt_confirm_indication command, result: 0x%x \n", status);
            }
            else
            {
              LOG_INFO_APP("  Success: aci_gatt_confirm_indication command\n");
            }
          }
          break; /* end ACI_GATT_NOTIFICATION_VSEVT_CODE */

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

  /* USER CODE BEGIN Service1_EventHandler_2 */

  /* USER CODE END Service1_EventHandler_2 */

  return(return_value);
}/* end P2P_SERVER_EventHandler */

/* Public functions ----------------------------------------------------------*/

/**
 * @brief  Service initialization
 * @param  None
 * @retval None
 */
void P2P_SERVER_Init(void)
{
  Char_UUID_t  uuid;
  tBleStatus ret;
  uint8_t max_attr_record;

  /* USER CODE BEGIN SVCCTL_InitService1Svc_1 */

  /* USER CODE END SVCCTL_InitService1Svc_1 */

  /**
   *  Register the event handler to the BLE controller
   */
  SVCCTL_RegisterSvcHandler(P2P_SERVER_EventHandler);

  /**
   * P2P_Server
   *
   * Max_Attribute_Records = 1 + 2*10 + 1*no_of_char_with_notify_or_indicate_property + 1*no_of_char_with_broadcast_property
   * service_max_attribute_record = 1 for P2P_Server +
   *                                2 for MID +
   *                                2 for PRODNAME +
   *                                2 for SLNM +
   *                                2 for DEVLOC +
   *                                2 for DS +
   *                                2 for DEVMKE +
   *                                2 for DEVMAC +
   *                                2 for BLESTKFW +
   *                                2 for APPFW +
   *                                2 for ADVNAME +
   *                              = 21
   * This value doesn't take into account number of descriptors manually added
   * In case of descriptors added, please update the max_attr_record value accordingly in the next SVCCTL_InitService User Section
   */
  max_attr_record = 21;

  /* USER CODE BEGIN SVCCTL_InitService */
  /* max_attr_record to be updated if descriptors have been added */

  /* USER CODE END SVCCTL_InitService */

  COPY_P2P_SERVER_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_service(UUID_TYPE_128,
                             (Service_UUID_t *) &uuid,
                             PRIMARY_SERVICE,
                             max_attr_record,
                             &(P2P_SERVER_Context.P2p_serverSvcHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_service command: P2P_Server, error code: 0x%x \n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_service command: P2p_serverSvcHdle = 0x%04X\n",P2P_SERVER_Context.P2p_serverSvcHdle);
  }

  /**
   * MID
   */
  COPY_MID_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(P2P_SERVER_Context.P2p_serverSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeMid,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(P2P_SERVER_Context.MidCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : MID, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : MidCharHdle = 0x%04X\n",P2P_SERVER_Context.MidCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService1Char1 */

  /* USER CODE END SVCCTL_InitService1Char1 */

  /**
   * PRODNAME
   */
  COPY_PRODNAME_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(P2P_SERVER_Context.P2p_serverSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeProdname,
                          CHAR_PROP_READ,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(P2P_SERVER_Context.ProdnameCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : PRODNAME, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : ProdnameCharHdle = 0x%04X\n",P2P_SERVER_Context.ProdnameCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService1Char2 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService1Char2 */

  /**
   * SLNM
   */
  COPY_SLNM_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(P2P_SERVER_Context.P2p_serverSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeSlnm,
                          CHAR_PROP_READ,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(P2P_SERVER_Context.SlnmCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : SLNM, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : SlnmCharHdle = 0x%04X\n",P2P_SERVER_Context.SlnmCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService1Char3 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService1Char3 */

  /**
   * DEVLOC
   */
  COPY_DEVLOC_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(P2P_SERVER_Context.P2p_serverSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeDevloc,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(P2P_SERVER_Context.DevlocCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : DEVLOC, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : DevlocCharHdle = 0x%04X\n",P2P_SERVER_Context.DevlocCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService1Char4 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService1Char4 */

  /**
   * DS
   */
  COPY_DS_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(P2P_SERVER_Context.P2p_serverSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeDs,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(P2P_SERVER_Context.DsCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : DS, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : DsCharHdle = 0x%04X\n",P2P_SERVER_Context.DsCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService1Char5 */

  /* USER CODE END SVCCTL_InitService1Char5 */

  /**
   * DEVMKE
   */
  COPY_DEVMKE_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(P2P_SERVER_Context.P2p_serverSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeDevmke,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(P2P_SERVER_Context.DevmkeCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : DEVMKE, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : DevmkeCharHdle = 0x%04X\n",P2P_SERVER_Context.DevmkeCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService1Char6 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService1Char6 */

  /**
   * DEVMAC
   */
  COPY_DEVMAC_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(P2P_SERVER_Context.P2p_serverSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeDevmac,
                          CHAR_PROP_READ,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(P2P_SERVER_Context.DevmacCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : DEVMAC, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : DevmacCharHdle = 0x%04X\n",P2P_SERVER_Context.DevmacCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService1Char7 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService1Char7 */

  /**
   * BLESTKFW
   */
  COPY_BLESTKFW_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(P2P_SERVER_Context.P2p_serverSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeBlestkfw,
                          CHAR_PROP_READ,
                          ATTR_PERMISSION_AUTHEN_WRITE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(P2P_SERVER_Context.BlestkfwCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : BLESTKFW, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : BlestkfwCharHdle = 0x%04X\n",P2P_SERVER_Context.BlestkfwCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService1Char8 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService1Char8 */

  /**
   * APPFW
   */
  COPY_APPFW_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(P2P_SERVER_Context.P2p_serverSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeAppfw,
                          CHAR_PROP_READ,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(P2P_SERVER_Context.AppfwCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : APPFW, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : AppfwCharHdle = 0x%04X\n",P2P_SERVER_Context.AppfwCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService1Char9 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService1Char9 */

  /**
   * ADVNAME
   */
  COPY_ADVNAME_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(P2P_SERVER_Context.P2p_serverSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeAdvname,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(P2P_SERVER_Context.AdvnameCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : ADVNAME, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : AdvnameCharHdle = 0x%04X\n",P2P_SERVER_Context.AdvnameCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService1Char10 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService1Char10 */

  /* USER CODE BEGIN SVCCTL_InitService1Svc_2 */

  /* USER CODE END SVCCTL_InitService1Svc_2 */

  return;
}

/**
 * @brief  Characteristic update
 * @param  CharOpcode: Characteristic identifier
 * @param  pData: Structure holding data to update
 *
 */
tBleStatus P2P_SERVER_UpdateValue(P2P_SERVER_CharOpcode_t CharOpcode, P2P_SERVER_Data_t *pData)
{
  tBleStatus ret = BLE_STATUS_INVALID_PARAMS;
  /* USER CODE BEGIN Service1_App_Update_Char_1 */

  /* USER CODE END Service1_App_Update_Char_1 */

  switch(CharOpcode)
  {
    case P2P_SERVER_MID:
      ret = aci_gatt_update_char_value(P2P_SERVER_Context.P2p_serverSvcHdle,
                                       P2P_SERVER_Context.MidCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value MID command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value MID command\n");
      }
      /* USER CODE BEGIN Service1_Char_Value_1 */

      /* USER CODE END Service1_Char_Value_1 */
      break;

    case P2P_SERVER_PRODNAME:
      ret = aci_gatt_update_char_value(P2P_SERVER_Context.P2p_serverSvcHdle,
                                       P2P_SERVER_Context.ProdnameCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value PRODNAME command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value PRODNAME command\n");
      }
      /* USER CODE BEGIN Service1_Char_Value_2 */

      /* USER CODE END Service1_Char_Value_2 */
      break;

    case P2P_SERVER_SLNM:
      ret = aci_gatt_update_char_value(P2P_SERVER_Context.P2p_serverSvcHdle,
                                       P2P_SERVER_Context.SlnmCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value SLNM command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value SLNM command\n");
      }
      /* USER CODE BEGIN Service1_Char_Value_3 */

      /* USER CODE END Service1_Char_Value_3 */
      break;

    case P2P_SERVER_DEVLOC:
      ret = aci_gatt_update_char_value(P2P_SERVER_Context.P2p_serverSvcHdle,
                                       P2P_SERVER_Context.DevlocCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value DEVLOC command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value DEVLOC command\n");
      }
      /* USER CODE BEGIN Service1_Char_Value_4 */

      /* USER CODE END Service1_Char_Value_4 */
      break;

    case P2P_SERVER_DS:
      ret = aci_gatt_update_char_value(P2P_SERVER_Context.P2p_serverSvcHdle,
                                       P2P_SERVER_Context.DsCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value DS command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value DS command\n");
      }
      /* USER CODE BEGIN Service1_Char_Value_5 */

      /* USER CODE END Service1_Char_Value_5 */
      break;

    case P2P_SERVER_DEVMKE:
      ret = aci_gatt_update_char_value(P2P_SERVER_Context.P2p_serverSvcHdle,
                                       P2P_SERVER_Context.DevmkeCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value DEVMKE command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value DEVMKE command\n");
      }
      /* USER CODE BEGIN Service1_Char_Value_6 */

      /* USER CODE END Service1_Char_Value_6 */
      break;

    case P2P_SERVER_DEVMAC:
      ret = aci_gatt_update_char_value(P2P_SERVER_Context.P2p_serverSvcHdle,
                                       P2P_SERVER_Context.DevmacCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value DEVMAC command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value DEVMAC command\n");
      }
      /* USER CODE BEGIN Service1_Char_Value_7 */

      /* USER CODE END Service1_Char_Value_7 */
      break;

    case P2P_SERVER_BLESTKFW:
      ret = aci_gatt_update_char_value(P2P_SERVER_Context.P2p_serverSvcHdle,
                                       P2P_SERVER_Context.BlestkfwCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value BLESTKFW command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value BLESTKFW command\n");
      }
      /* USER CODE BEGIN Service1_Char_Value_8 */

      /* USER CODE END Service1_Char_Value_8 */
      break;

    case P2P_SERVER_APPFW:
      ret = aci_gatt_update_char_value(P2P_SERVER_Context.P2p_serverSvcHdle,
                                       P2P_SERVER_Context.AppfwCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value APPFW command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value APPFW command\n");
      }
      /* USER CODE BEGIN Service1_Char_Value_9 */

      /* USER CODE END Service1_Char_Value_9 */
      break;

    case P2P_SERVER_ADVNAME:
      ret = aci_gatt_update_char_value(P2P_SERVER_Context.P2p_serverSvcHdle,
                                       P2P_SERVER_Context.AdvnameCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value ADVNAME command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value ADVNAME command\n");
      }
      /* USER CODE BEGIN Service1_Char_Value_10 */

      /* USER CODE END Service1_Char_Value_10 */
      break;

    default:
      break;
  }

  /* USER CODE BEGIN Service1_App_Update_Char_2 */

  /* USER CODE END Service1_App_Update_Char_2 */

  return ret;
}
