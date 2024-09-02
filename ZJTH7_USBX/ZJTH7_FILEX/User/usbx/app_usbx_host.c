/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_usbx_host.c
  * @author  MCD Application Team
  * @brief   USBX host applicative file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020-2021 STMicroelectronics.
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
#include "app_usbx_host.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define HID_INSTANCE     3

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

static TX_THREAD ux_host_app_thread;

/* USER CODE BEGIN PV */
TX_THREAD                  keyboard_app_thread;
TX_THREAD                  mouse_app_thread;
UX_HOST_CLASS_HID           *hid_instance[HID_INSTANCE];
UX_HOST_CLASS_HID_MOUSE    *mouse;
UX_HOST_CLASS_HID_KEYBOARD *keyboard;
UINT                        hid_index;
UX_HOST_CLASS_HUB           *hub_instance;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static VOID app_ux_host_thread_entry(ULONG thread_input);
static UINT ux_host_event_callback(ULONG event, UX_HOST_CLASS *current_class, VOID *current_instance);
static VOID ux_host_error_callback(UINT system_level, UINT system_context, UINT error_code);
/* USER CODE BEGIN PFP */
/* USER CODE END PFP */
/* USBX动态内存分配 */

#define UX_HOST_APP_MEM_POOL_SIZE                1024 * 28

__attribute__((section(".UsbxPoolSection"))) __ALIGN_BEGIN static uint8_t ux_host_byte_pool_buffer[UX_HOST_APP_MEM_POOL_SIZE] __ALIGN_END;
static TX_BYTE_POOL ux_host_app_byte_pool;

/**
  * @brief  Application USBX Host Initialization.
  * @param  memory_ptr: memory pointer
  * @retval status
  */
  
UINT MX_USBX_Host_Init()
{
	UINT ret = UX_SUCCESS;  // 初始化返回值为成功
    UCHAR *pointer;  // 定义指针用于分配内存
    TX_BYTE_POOL *byte_pool;
    VOID *memory_ptr;
    if (tx_byte_pool_create(&ux_host_app_byte_pool, "Ux App memory pool", ux_host_byte_pool_buffer, UX_HOST_APP_MEM_POOL_SIZE) != TX_SUCCESS)
    {
    /* USER CODE BEGIN UX_Byte_Pool_Error */

    /* USER CODE END UX_Byte_Pool_Error */
    }
    else
    {
        memory_ptr = (VOID *)&ux_host_app_byte_pool;
        byte_pool = (TX_BYTE_POOL*)memory_ptr;  // 将传入的内存指针转换为字节池类型
        /* 为 USBX 内存分配堆栈空间 */
        if (tx_byte_allocate(byte_pool, (VOID **) &pointer,
                             USBX_HOST_MEMORY_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
        {
            // 如果内存分配失败，返回错误码 TX_POOL_ERROR
            /* USER CODE BEGIN USBX_ALLOCATE_STACK_ERORR */
            return TX_POOL_ERROR;
            /* USER CODE END USBX_ALLOCATE_STACK_ERORR */
        }
        
        /* 初始化 USBX 内存 */
        if (ux_system_initialize(pointer, USBX_HOST_MEMORY_STACK_SIZE, UX_NULL, 0) != UX_SUCCESS)
        {
            // 如果 USBX 系统初始化失败，返回错误码 UX_ERROR
            /* USER CODE BEGIN USBX_SYSTEM_INITIALIZE_ERORR */
            return UX_ERROR;
            /* USER CODE END USBX_SYSTEM_INITIALIZE_ERORR */
        }     
        /* 安装 USBX 主机部分 */
        if (ux_host_stack_initialize(ux_host_event_callback) != UX_SUCCESS)
        {
            // 如果 USBX 主机堆栈初始化失败，返回错误码 UX_ERROR
            /* USER CODE BEGIN USBX_HOST_INITIALIZE_ERORR */
            return UX_ERROR;
            /* USER CODE END USBX_HOST_INITIALIZE_ERORR */
        }
        
        /* 注册错误回调函数 */
        ux_utility_error_callback_register(&ux_host_error_callback);

        /* 初始化主机 HID 类 */
        if (ux_host_stack_class_register(_ux_system_host_class_hid_name,
                                         ux_host_class_hid_entry) != UX_SUCCESS)
        {
            // 如果 HID 类注册失败，返回错误码 UX_ERROR
            /* USER CODE BEGIN USBX_HSOT_HID_REGISTER_ERORR */
            return UX_ERROR;
            /* USER CODE END USBX_HSOT_HID_REGISTER_ERORR */
        }
        /* 初始化主机 HID 鼠标客户端 */
        if (ux_host_class_hid_client_register(_ux_system_host_class_hid_client_mouse_name,
                                              ux_host_class_hid_mouse_entry) != UX_SUCCESS)
        {
            // 如果 HID 鼠标客户端注册失败，返回错误码 UX_ERROR
            /* USER CODE BEGIN USBX_HOST_HID_MOUSE_REGISTER_ERORR */
            return UX_ERROR;
            /* USER CODE END USBX_HOST_HID_MOUSE_REGISTER_ERORR */
        }        
        /* 初始化主机 HID 键盘客户端 */
        if (ux_host_class_hid_client_register(_ux_system_host_class_hid_client_keyboard_name,
                                              ux_host_class_hid_keyboard_entry) != UX_SUCCESS)
        {
            // 如果 HID 键盘客户端注册失败，返回错误码 UX_ERROR
            /* USER CODE BEGIN USBX_HOST_HID_KEYBOARD_REGISTER_ERORR */
            return UX_ERROR;
            /* USER CODE END USBX_HOST_HID_KEYBOARD_REGISTER_ERORR */
        }  
        
        /* 初始化主机集线器类 */
        if (ux_host_stack_class_register(_ux_system_host_class_hub_name,
                                         ux_host_class_hub_entry) != UX_SUCCESS)
        {
            /* 如果注册主机集线器类失败，返回UX_ERROR错误码 */
            /* USER CODE BEGIN USBX_HOST_HUB_REGISTER_ERROR */
            return UX_ERROR;
            /* USER CODE END USBX_HOST_HUB_REGISTER_ERROR */
        }
        /* 为主应用程序线程分配堆栈空间 */
        if (tx_byte_allocate(byte_pool, (VOID **) &pointer, UX_HOST_APP_THREAD_STACK_SIZE,
                             TX_NO_WAIT) != TX_SUCCESS)
        {
            // 如果堆栈空间分配失败，返回错误码 TX_POOL_ERROR
            /* USER CODE BEGIN MAIN_THREAD_ALLOCATE_STACK_ERORR */
            return TX_POOL_ERROR;
            /* USER CODE END MAIN_THREAD_ALLOCATE_STACK_ERORR */
        }
        /* 创建主应用程序线程 */
        if (tx_thread_create(&ux_host_app_thread, UX_HOST_APP_THREAD_NAME, app_ux_host_thread_entry,
                             0, pointer, UX_HOST_APP_THREAD_STACK_SIZE, UX_HOST_APP_THREAD_PRIO,
                             UX_HOST_APP_THREAD_PREEMPTION_THRESHOLD, UX_HOST_APP_THREAD_TIME_SLICE,
                             UX_HOST_APP_THREAD_START_OPTION) != TX_SUCCESS)
        {
            // 如果线程创建失败，返回错误码 TX_THREAD_ERROR
            /* USER CODE BEGIN MAIN_THREAD_CREATE_ERORR */
            return TX_THREAD_ERROR;
            /* USER CODE END MAIN_THREAD_CREATE_ERORR */
        }
        /* USER CODE BEGIN MX_USBX_Host_Init1 */

        /* 为 HID 鼠标应用程序线程分配堆栈空间 */
        if (tx_byte_allocate(byte_pool, (VOID **) &pointer,
                             UX_HOST_APP_THREAD_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
        {
            // 如果堆栈空间分配失败，返回错误码 TX_POOL_ERROR
            return TX_POOL_ERROR;
        }
        /* 创建 HID 鼠标应用程序线程 */
        if (tx_thread_create(&mouse_app_thread, "HID mouse App thread", hid_mouse_thread_entry,
                             0, pointer, UX_HOST_APP_THREAD_STACK_SIZE, 30, 30, 1, TX_AUTO_START) != TX_SUCCESS)
        {
            // 如果线程创建失败，返回错误码 TX_THREAD_ERROR
            return TX_THREAD_ERROR;
        }     
        /* 为 HID 键盘应用程序线程分配堆栈空间 */
        if (tx_byte_allocate(byte_pool, (VOID **) &pointer,
                             UX_HOST_APP_THREAD_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
        {
            // 如果堆栈空间分配失败，返回错误码 TX_POOL_ERROR
            return TX_POOL_ERROR;
        }

        /* 创建 HID 键盘应用程序线程 */
        if (tx_thread_create(&keyboard_app_thread, "HID Keyboard App thread", hid_keyboard_thread_entry,
                             0, pointer, UX_HOST_APP_THREAD_STACK_SIZE, 30, 30, 1, TX_AUTO_START) != TX_SUCCESS)
        {
            // 如果线程创建失败，返回错误码 TX_THREAD_ERROR
            return TX_THREAD_ERROR;
        }


          
    }

	/* USER CODE END MX_USBX_Host_Init1 */

	return UX_SUCCESS;  // 返回最终状态，默认是成功

}

/**
  * @brief  Function implementing app_ux_host_thread_entry.
  * @param  thread_input: User thread input parameter.
  * @retval none
  */
static VOID app_ux_host_thread_entry(ULONG thread_input)
{
  /* USER CODE BEGIN app_ux_host_thread_entry */

  /* Initialization of USB host */
  USBX_APP_Host_Init();

  /* USER CODE END app_ux_host_thread_entry */
}

/**
  * @brief  ux_host_event_callback
  *         This callback is invoked to notify application of instance changes.
  * @param  event: event code.
  * @param  current_class: Pointer to class.
  * @param  current_instance: Pointer to class instance.
  * @retval status
  */
UINT ux_host_event_callback(ULONG event, UX_HOST_CLASS *current_class, VOID *current_instance)
{
  UINT status = UX_SUCCESS;

  /* USER CODE BEGIN ux_host_event_callback0 */

  /* Get current Hid Client */
  UX_HOST_CLASS_HID_CLIENT *client  = (UX_HOST_CLASS_HID_CLIENT *)current_instance;
  UINT idx;

  /* USER CODE END ux_host_event_callback0 */

  switch (event)
  {
    case UX_DEVICE_INSERTION:

      /* USER CODE BEGIN UX_DEVICE_INSERTION */

      /* Get current HUB Class */
      if (current_class -> ux_host_class_entry_function == ux_host_class_hub_entry)
      {
        if (hub_instance == UX_NULL)
        {
          /* Get current Hid Instance */
          hub_instance = (UX_HOST_CLASS_HUB *)current_instance;

          USBH_UsrLog("HUB_Device");
          USBH_UsrLog("PID: %#x ", (UINT)hub_instance ->ux_host_class_hub_device->ux_device_descriptor.idProduct);
          USBH_UsrLog("VID: %#x ", (UINT)hub_instance ->ux_host_class_hub_device->ux_device_descriptor.idVendor);
          USBH_UsrLog("USB HUB Host App\n\n");
        }
      }

      /* Get current Hid Class */
      if (current_class -> ux_host_class_entry_function == ux_host_class_hid_entry)
      {
        for (idx = 0; idx < HID_INSTANCE; )
        {
          if (hid_instance[idx] != NULL)
          {
            /* Move to next HID instance */
            idx ++;
          }
          else
          {
            /* Get current Storage Instance */
            hid_instance[idx] = (UX_HOST_CLASS_HID *)current_instance;
            hid_index = idx;
            break;
          }
        }
      }
      /* USER CODE END UX_DEVICE_INSERTION */

      break;

    case UX_DEVICE_REMOVAL:

      /* USER CODE BEGIN UX_DEVICE_REMOVAL */

      /* Free HUB Instance */
      if ((VOID*)hub_instance == current_instance)
      {
        hub_instance = UX_NULL;

        USBH_UsrLog("\nHUB Device Unplugged");
      }


      /* Clear hid instance*/
      for (hid_index = 0; hid_index < HID_INSTANCE; hid_index++)
      {
        if ((VOID*)hid_instance[hid_index] == current_instance)
        {
          /* Free HID Instance */
          hid_instance[hid_index] = UX_NULL;
        }
      }

      /* USER CODE END UX_DEVICE_REMOVAL */

      break;

    case UX_HID_CLIENT_INSERTION:

      /* USER CODE BEGIN UX_HID_CLIENT_INSERTION */

      USBH_UsrLog("\nHID Client Plugged");

      /* Check the HID_client if this is a HID keyboard device */
      if (client -> ux_host_class_hid_client_handler == ux_host_class_hid_keyboard_entry)
      {
        /* Get current Hid Client */
        if (keyboard == UX_NULL)
        {
          keyboard = client -> ux_host_class_hid_client_local_instance;

          USBH_UsrLog("HID_Keyboard_Device");
          USBH_UsrLog("PID: %#x ", (UINT)keyboard ->ux_host_class_hid_keyboard_hid->ux_host_class_hid_device->ux_device_descriptor.idProduct);
          USBH_UsrLog("VID: %#x ", (UINT)keyboard ->ux_host_class_hid_keyboard_hid->ux_host_class_hid_device->ux_device_descriptor.idVendor);
          USBH_UsrLog("USB HID Host Keyboard App...");
          USBH_UsrLog("keyboard is ready...\n");
        }
      }

      /* Check the HID_client if this is a HID mouse device */
      if (client -> ux_host_class_hid_client_handler == ux_host_class_hid_mouse_entry)
      {
        /* Get current Hid Client */
        if (mouse == UX_NULL)
        {
          mouse = client -> ux_host_class_hid_client_local_instance;

          USBH_UsrLog("HID_Mouse_Device");
          USBH_UsrLog("PID: %#x ", (UINT)mouse ->ux_host_class_hid_mouse_hid->ux_host_class_hid_device->ux_device_descriptor.idProduct);
          USBH_UsrLog("VID: %#x ", (UINT)mouse ->ux_host_class_hid_mouse_hid->ux_host_class_hid_device->ux_device_descriptor.idVendor);
          USBH_UsrLog("USB HID Host Mouse App...");
          USBH_UsrLog("Mouse is ready...\n");
        }
      }

      /* USER CODE END UX_HID_CLIENT_INSERTION */

      break;

    case UX_HID_CLIENT_REMOVAL:

      /* USER CODE BEGIN UX_HID_CLIENT_REMOVAL */

      /* Clear hid client local instance */
      if ((VOID*)keyboard == client -> ux_host_class_hid_client_local_instance)
      {
        /* Clear hid keyboard instance */
        keyboard = UX_NULL;
        USBH_UsrLog("\nHID Client Keyboard Unplugged");
      }

      if ((VOID*)mouse == client -> ux_host_class_hid_client_local_instance)
      {
        /* Clear hid mouse instance */
        mouse = UX_NULL;
        USBH_UsrLog("\nHID Client Mouse Unplugged");
      }

      /* USER CODE END UX_HID_CLIENT_REMOVAL */

      break;

#if defined (UX_HOST_CLASS_STORAGE_NO_FILEX)
    case UX_STORAGE_MEDIA_INSERTION:

      /* USER CODE BEGIN UX_STORAGE_MEDIA_INSERTION */

      /* USER CODE END UX_STORAGE_MEDIA_INSERTION */

      break;

    case UX_STORAGE_MEDIA_REMOVAL:

      /* USER CODE BEGIN UX_STORAGE_MEDIA_REMOVAL */

      /* USER CODE END UX_STORAGE_MEDIA_REMOVAL */

      break;
#endif

    case UX_DEVICE_CONNECTION:

      /* USER CODE BEGIN UX_DEVICE_CONNECTION */

      /* USER CODE END UX_DEVICE_CONNECTION */

      break;

    case UX_DEVICE_DISCONNECTION:

      /* USER CODE BEGIN UX_DEVICE_DISCONNECTION */

      /* USER CODE END UX_DEVICE_DISCONNECTION */

      break;

    default:

      /* USER CODE BEGIN EVENT_DEFAULT */

      /* USER CODE END EVENT_DEFAULT */

      break;
  }

  /* USER CODE BEGIN ux_host_event_callback1 */

  /* USER CODE END ux_host_event_callback1 */

  return status;
}

/**
  * @brief ux_host_error_callback
  *         This callback is invoked to notify application of error changes.
  * @param  system_level: system level parameter.
  * @param  system_context: system context code.
  * @param  error_code: error event code.
  * @retval Status
  */
VOID ux_host_error_callback(UINT system_level, UINT system_context, UINT error_code)
{
  /* USER CODE BEGIN ux_host_error_callback0 */

  /* USER CODE END ux_host_error_callback0 */

  switch (error_code)
  {
    case UX_DEVICE_ENUMERATION_FAILURE:

      /* USER CODE BEGIN UX_DEVICE_ENUMERATION_FAILURE */

      USBH_UsrLog("USB Device Enumeration Failure");

      /* USER CODE END UX_DEVICE_ENUMERATION_FAILURE */

      break;

    case  UX_NO_DEVICE_CONNECTED:

      /* USER CODE BEGIN UX_NO_DEVICE_CONNECTED */

      USBH_UsrLog("USB Device disconnected");

      /* USER CODE END UX_NO_DEVICE_CONNECTED */

      break;

    default:

      /* USER CODE BEGIN ERROR_DEFAULT */

      /* USER CODE END ERROR_DEFAULT */

      break;
  }

  /* USER CODE BEGIN ux_host_error_callback1 */

  /* USER CODE END ux_host_error_callback1 */
}

/* USER CODE BEGIN 1 */
/**

  * @brief  USBX_APP_Host_Init
  *         Initialization of USB host.
  * @param  none
  * @retval none
  */
VOID USBX_APP_Host_Init(VOID)
{
  /* USER CODE BEGIN USB_Host_Init_PreTreatment_0 */

  /* USER CODE END USB_Host_Init_PreTreatment_0 */

  /* Initialize the LL driver */
  MX_USB_OTG_HS_HCD_Init();

  /* Initialize the host controller driver */
  ux_host_stack_hcd_register(_ux_system_host_hcd_stm32_name,
                             _ux_hcd_stm32_initialize, (ULONG)USB_OTG_HS,
                             (ULONG)&hhcd_USB_OTG_HS);

//  /* Drive vbus */
//  USBH_DriverVBUS(USB_VBUS_TRUE);

  /* Enable USB Global Interrupt */
  HAL_HCD_Start(&hhcd_USB_OTG_HS);

  /* USER CODE BEGIN USB_Host_Init_PostTreatment1 */

  /* Start Application Message */
  USBH_UsrLog("**** USB OTG HS HUB HID MSC Host **** \n");
  USBH_UsrLog("USB Host library started.\n");

  /* Wait for Device to be attached */
  USBH_UsrLog("Starting HUB Application");
  USBH_UsrLog("Connect your HUB Device");

  /* USER CODE END USB_Host_Init_PostTreatment1 */
}
/* USER CODE END 1 */
