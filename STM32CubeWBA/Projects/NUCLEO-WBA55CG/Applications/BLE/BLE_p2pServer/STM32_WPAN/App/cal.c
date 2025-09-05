/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    CAL.c
  * @author  MCD Application Team
  * @brief   CAL definition.
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
#include "cal.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/

/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

typedef struct{
  uint16_t  CalSvcHdle;                  /**< Cal Service Handle */
  uint16_t  Cs_Calib_TypeCharHdle;                  /**< CS_CALIB_TYPE Characteristic Handle */
  uint16_t  Cs_Calib_StatusCharHdle;                  /**< CS_CALIB_STATUS Characteristic Handle */
  uint16_t  Cs_Calib_Resp_CodeCharHdle;                  /**< CS_CALIB_RESP_CODE Characteristic Handle */
  uint16_t  Cs_Calib_ReservedCharHdle;                  /**< CS_CALIB_RESERVED Characteristic Handle */
/* USER CODE BEGIN Context */
  /* Place holder for Characteristic Descriptors Handle*/

/* USER CODE END Context */
}CAL_Context_t;

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
static const uint16_t SizeCs_Calib_Type = 1;
static const uint16_t SizeCs_Calib_Status = 1;
static const uint16_t SizeCs_Calib_Resp_Code = 1;
static const uint16_t SizeCs_Calib_Reserved = 1;

static CAL_Context_t CAL_Context;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static SVCCTL_EvtAckStatus_t CAL_EventHandler(void *p_pckt);

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
 F364050000B04240BA5005CA45BF8ABC: Service 128bits UUID
 F364050100B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364050200B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364050300B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 F364050400B04240BA5005CA45BF8ABC: Characteristic 128bits UUID
 */
#define COPY_CAL_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x05,0x00,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CS_CALIB_TYPE_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x05,0x01,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CS_CALIB_STATUS_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x05,0x02,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CS_CALIB_RESP_CODE_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x05,0x03,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)
#define COPY_CS_CALIB_RESERVED_UUID(uuid_struct)       COPY_UUID_128(uuid_struct,0xf3,0x64,0x05,0x04,0x00,0xb0,0x42,0x40,0xba,0x50,0x05,0xca,0x45,0xbf,0x8a,0xbc)

/* USER CODE BEGIN PF */

/* USER CODE END PF */

/**
 * @brief  Event handler
 * @param  p_Event: Address of the buffer holding the p_Event
 * @retval Ack: Return whether the p_Event has been managed or not
 */
static SVCCTL_EvtAckStatus_t CAL_EventHandler(void *p_Event)
{
  SVCCTL_EvtAckStatus_t return_value;
  hci_event_pckt *p_event_pckt;
  evt_blecore_aci *p_blecore_evt;
  aci_gatt_attribute_modified_event_rp0 *p_attribute_modified;
  aci_gatt_read_permit_req_event_rp0    *p_read_req;
  CAL_NotificationEvt_t                 notification;
  /* USER CODE BEGIN Service6_EventHandler_1 */

  /* USER CODE END Service6_EventHandler_1 */

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
          if(p_attribute_modified->Attr_Handle == (CAL_Context.Cs_Calib_StatusCharHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN Service6_Char_2 */

            /* USER CODE END Service6_Char_2 */
            switch(p_attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN Service6_Char_2_attribute_modified */

              /* USER CODE END Service6_Char_2_attribute_modified */

              /* Disabled Notification management */
              case (0x00):
                /* USER CODE BEGIN Service6_Char_2_Disabled_BEGIN */

                /* USER CODE END Service6_Char_2_Disabled_BEGIN */
                notification.EvtOpcode = CAL_CS_CALIB_STATUS_NOTIFY_DISABLED_EVT;
                CAL_Notification(&notification);
                /* USER CODE BEGIN Service6_Char_2_Disabled_END */

                /* USER CODE END Service6_Char_2_Disabled_END */
                break;

              /* Enabled Notification management */
              case GATT_CHAR_UPDATE_SEND_NOTIFICATION:
                /* USER CODE BEGIN Service6_Char_2_COMSVC_Notification_BEGIN */

                /* USER CODE END Service6_Char_2_COMSVC_Notification_BEGIN */
                notification.EvtOpcode = CAL_CS_CALIB_STATUS_NOTIFY_ENABLED_EVT;
                CAL_Notification(&notification);
                /* USER CODE BEGIN Service6_Char_2_COMSVC_Notification_END */

                /* USER CODE END Service6_Char_2_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN Service6_Char_2_default */

                /* USER CODE END Service6_Char_2_default */
                break;
            }
          }

          else if(p_attribute_modified->Attr_Handle == (CAL_Context.Cs_Calib_Resp_CodeCharHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN Service6_Char_3 */

            /* USER CODE END Service6_Char_3 */
            switch(p_attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN Service6_Char_3_attribute_modified */

              /* USER CODE END Service6_Char_3_attribute_modified */

              /* Disabled Notification management */
              case (0x00):
                /* USER CODE BEGIN Service6_Char_3_Disabled_BEGIN */

                /* USER CODE END Service6_Char_3_Disabled_BEGIN */
                notification.EvtOpcode = CAL_CS_CALIB_RESP_CODE_NOTIFY_DISABLED_EVT;
                CAL_Notification(&notification);
                /* USER CODE BEGIN Service6_Char_3_Disabled_END */

                /* USER CODE END Service6_Char_3_Disabled_END */
                break;

              /* Enabled Notification management */
              case GATT_CHAR_UPDATE_SEND_NOTIFICATION:
                /* USER CODE BEGIN Service6_Char_3_COMSVC_Notification_BEGIN */

                /* USER CODE END Service6_Char_3_COMSVC_Notification_BEGIN */
                notification.EvtOpcode = CAL_CS_CALIB_RESP_CODE_NOTIFY_ENABLED_EVT;
                CAL_Notification(&notification);
                /* USER CODE BEGIN Service6_Char_3_COMSVC_Notification_END */

                /* USER CODE END Service6_Char_3_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN Service6_Char_3_default */

                /* USER CODE END Service6_Char_3_default */
                break;
            }
          }

          else if(p_attribute_modified->Attr_Handle == (CAL_Context.Cs_Calib_ReservedCharHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN Service6_Char_4 */

            /* USER CODE END Service6_Char_4 */
            switch(p_attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN Service6_Char_4_attribute_modified */

              /* USER CODE END Service6_Char_4_attribute_modified */

              /* Disabled Notification management */
              case (0x00):
                /* USER CODE BEGIN Service6_Char_4_Disabled_BEGIN */

                /* USER CODE END Service6_Char_4_Disabled_BEGIN */
                notification.EvtOpcode = CAL_CS_CALIB_RESERVED_NOTIFY_DISABLED_EVT;
                CAL_Notification(&notification);
                /* USER CODE BEGIN Service6_Char_4_Disabled_END */

                /* USER CODE END Service6_Char_4_Disabled_END */
                break;

              /* Enabled Notification management */
              case GATT_CHAR_UPDATE_SEND_NOTIFICATION:
                /* USER CODE BEGIN Service6_Char_4_COMSVC_Notification_BEGIN */

                /* USER CODE END Service6_Char_4_COMSVC_Notification_BEGIN */
                notification.EvtOpcode = CAL_CS_CALIB_RESERVED_NOTIFY_ENABLED_EVT;
                CAL_Notification(&notification);
                /* USER CODE BEGIN Service6_Char_4_COMSVC_Notification_END */

                /* USER CODE END Service6_Char_4_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN Service6_Char_4_default */

                /* USER CODE END Service6_Char_4_default */
                break;
            }
          }

          else if(p_attribute_modified->Attr_Handle == (CAL_Context.Cs_Calib_TypeCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;

            notification.EvtOpcode = CAL_CS_CALIB_TYPE_WRITE_EVT;
            /* USER CODE BEGIN Service6_Char_1_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
						LOG_INFO_APP("-- GATT : CAL_CS_CALIB_TYPE CONFIGURATION RECEIVED\n");
            notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
            notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
            /* USER CODE END Service6_Char_1_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
            CAL_Notification(&notification);
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
          if(p_read_req->Attribute_Handle == (CAL_Context.Cs_Calib_TypeCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service6_Char_1_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service6_Char_1_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service6_Char_1_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CAL_CS_CALIB_TYPE_READ_EVT;
            CAL_Notification(&notification);
            /*USER CODE END Service6_Char_1_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CAL_Context.Cs_Calib_StatusCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service6_Char_2_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service6_Char_2_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service6_Char_2_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CAL_CS_CALIB_STATUS_READ_EVT;
            CAL_Notification(&notification);
            /*USER CODE END Service6_Char_2_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CAL_Context.Cs_Calib_Resp_CodeCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service6_Char_3_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service6_Char_3_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service6_Char_3_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CAL_CS_CALIB_RESP_CODE_READ_EVT;
            CAL_Notification(&notification);
            /*USER CODE END Service6_Char_3_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          }
          else if(p_read_req->Attribute_Handle == (CAL_Context.Cs_Calib_ReservedCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN Service6_Char_4_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */

            /*USER CODE END Service6_Char_4_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/

            /*USER CODE BEGIN Service6_Char_4_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
#warning user shall call aci_gatt_allow_read() function if allowed
						aci_gatt_allow_read(p_read_req->Connection_Handle);
            notification.EvtOpcode = CAL_CS_CALIB_RESERVED_READ_EVT;
            CAL_Notification(&notification);
            /*USER CODE END Service6_Char_4_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
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

  /* USER CODE BEGIN Service6_EventHandler_2 */

  /* USER CODE END Service6_EventHandler_2 */

  return(return_value);
}/* end CAL_EventHandler */

/* Public functions ----------------------------------------------------------*/

/**
 * @brief  Service initialization
 * @param  None
 * @retval None
 */
void CAL_Init(void)
{
  Char_UUID_t  uuid;
  tBleStatus ret;
  uint8_t max_attr_record;

  /* USER CODE BEGIN SVCCTL_InitService6Svc_1 */

  /* USER CODE END SVCCTL_InitService6Svc_1 */

  /**
   *  Register the event handler to the BLE controller
   */
  SVCCTL_RegisterSvcHandler(CAL_EventHandler);

  /**
   * CAL
   *
   * Max_Attribute_Records = 1 + 2*4 + 1*no_of_char_with_notify_or_indicate_property + 1*no_of_char_with_broadcast_property
   * service_max_attribute_record = 1 for CAL +
   *                                2 for CS_CALIB_TYPE +
   *                                2 for CS_CALIB_STATUS +
   *                                2 for CS_CALIB_RESP_CODE +
   *                                2 for CS_CALIB_RESERVED +
   *                                1 for CS_CALIB_STATUS configuration descriptor +
   *                                1 for CS_CALIB_RESP_CODE configuration descriptor +
   *                                1 for CS_CALIB_RESERVED configuration descriptor +
   *                              = 12
   * This value doesn't take into account number of descriptors manually added
   * In case of descriptors added, please update the max_attr_record value accordingly in the next SVCCTL_InitService User Section
   */
  max_attr_record = 12;

  /* USER CODE BEGIN SVCCTL_InitService */
  /* max_attr_record to be updated if descriptors have been added */

  /* USER CODE END SVCCTL_InitService */

  COPY_CAL_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_service(UUID_TYPE_128,
                             (Service_UUID_t *) &uuid,
                             PRIMARY_SERVICE,
                             max_attr_record,
                             &(CAL_Context.CalSvcHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_service command: CAL, error code: 0x%x \n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_service command: CalSvcHdle = 0x%04X\n",CAL_Context.CalSvcHdle);
  }

  /**
   * CS_CALIB_TYPE
   */
  COPY_CS_CALIB_TYPE_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CAL_Context.CalSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCs_Calib_Type,
                          CHAR_PROP_READ | CHAR_PROP_WRITE,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CAL_Context.Cs_Calib_TypeCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CS_CALIB_TYPE, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cs_Calib_TypeCharHdle = 0x%04X\n",CAL_Context.Cs_Calib_TypeCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService6Char1 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService6Char1 */

  /**
   * CS_CALIB_STATUS
   */
  COPY_CS_CALIB_STATUS_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CAL_Context.CalSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCs_Calib_Status,
                          CHAR_PROP_READ | CHAR_PROP_NOTIFY,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CAL_Context.Cs_Calib_StatusCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CS_CALIB_STATUS, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cs_Calib_StatusCharHdle = 0x%04X\n",CAL_Context.Cs_Calib_StatusCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService6Char2 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService6Char2 */

  /**
   * CS_CALIB_RESP_CODE
   */
  COPY_CS_CALIB_RESP_CODE_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CAL_Context.CalSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCs_Calib_Resp_Code,
                          CHAR_PROP_READ | CHAR_PROP_NOTIFY,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CAL_Context.Cs_Calib_Resp_CodeCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CS_CALIB_RESP_CODE, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cs_Calib_Resp_CodeCharHdle = 0x%04X\n",CAL_Context.Cs_Calib_Resp_CodeCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService6Char3 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService6Char3 */

  /**
   * CS_CALIB_RESERVED
   */
  COPY_CS_CALIB_RESERVED_UUID(uuid.Char_UUID_128);
  ret = aci_gatt_add_char(CAL_Context.CalSvcHdle,
                          UUID_TYPE_128,
                          (Char_UUID_t *) &uuid,
                          SizeCs_Calib_Reserved,
                          CHAR_PROP_READ | CHAR_PROP_NOTIFY,
                          ATTR_PERMISSION_NONE,
                          GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                          0x10,
                          CHAR_VALUE_LEN_VARIABLE,
                          &(CAL_Context.Cs_Calib_ReservedCharHdle));
  if (ret != BLE_STATUS_SUCCESS)
  {
    LOG_INFO_APP("  Fail   : aci_gatt_add_char command   : CS_CALIB_RESERVED, error code: 0x%2X\n", ret);
  }
  else
  {
    LOG_INFO_APP("  Success: aci_gatt_add_char command   : Cs_Calib_ReservedCharHdle = 0x%04X\n",CAL_Context.Cs_Calib_ReservedCharHdle);
  }

  /* USER CODE BEGIN SVCCTL_InitService6Char4 */
  /* Place holder for Characteristic Descriptors */

  /* USER CODE END SVCCTL_InitService6Char4 */

  /* USER CODE BEGIN SVCCTL_InitService6Svc_2 */

  /* USER CODE END SVCCTL_InitService6Svc_2 */

  return;
}

/**
 * @brief  Characteristic update
 * @param  CharOpcode: Characteristic identifier
 * @param  pData: Structure holding data to update
 *
 */
tBleStatus CAL_UpdateValue(CAL_CharOpcode_t CharOpcode, CAL_Data_t *pData)
{
  tBleStatus ret = BLE_STATUS_INVALID_PARAMS;
  /* USER CODE BEGIN Service6_App_Update_Char_1 */

  /* USER CODE END Service6_App_Update_Char_1 */

  switch(CharOpcode)
  {
    case CAL_CS_CALIB_TYPE:
      ret = aci_gatt_update_char_value(CAL_Context.CalSvcHdle,
                                       CAL_Context.Cs_Calib_TypeCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CS_CALIB_TYPE command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CS_CALIB_TYPE command\n");
      }
      /* USER CODE BEGIN Service6_Char_Value_1 */

      /* USER CODE END Service6_Char_Value_1 */
      break;

    case CAL_CS_CALIB_STATUS:
      ret = aci_gatt_update_char_value(CAL_Context.CalSvcHdle,
                                       CAL_Context.Cs_Calib_StatusCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CS_CALIB_STATUS command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CS_CALIB_STATUS command\n");
      }
      /* USER CODE BEGIN Service6_Char_Value_2 */

      /* USER CODE END Service6_Char_Value_2 */
      break;

    case CAL_CS_CALIB_RESP_CODE:
      ret = aci_gatt_update_char_value(CAL_Context.CalSvcHdle,
                                       CAL_Context.Cs_Calib_Resp_CodeCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CS_CALIB_RESP_CODE command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CS_CALIB_RESP_CODE command\n");
      }
      /* USER CODE BEGIN Service6_Char_Value_3 */

      /* USER CODE END Service6_Char_Value_3 */
      break;

    case CAL_CS_CALIB_RESERVED:
      ret = aci_gatt_update_char_value(CAL_Context.CalSvcHdle,
                                       CAL_Context.Cs_Calib_ReservedCharHdle,
                                       0, /* charValOffset */
                                       pData->Length, /* charValueLen */
                                       (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        LOG_DEBUG_APP("  Fail   : aci_gatt_update_char_value CS_CALIB_RESERVED command, error code: 0x%2X\n", ret);
      }
      else
      {
        LOG_DEBUG_APP("  Success: aci_gatt_update_char_value CS_CALIB_RESERVED command\n");
      }
      /* USER CODE BEGIN Service6_Char_Value_4 */

      /* USER CODE END Service6_Char_Value_4 */
      break;

    default:
      break;
  }

  /* USER CODE BEGIN Service6_App_Update_Char_2 */

  /* USER CODE END Service6_App_Update_Char_2 */

  return ret;
}
