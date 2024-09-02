/**************************************************************************/
/*                                                                        */
/*       Copyright (c) Microsoft Corporation. All rights reserved.        */
/*                                                                        */
/*       This software is licensed under the Microsoft Software License   */
/*       Terms for Microsoft Azure RTOS. Full text of the license can be  */
/*       found in the LICENSE file at https://aka.ms/AzureRTOS_EULA       */
/*       and in the root directory of this software.                      */
/*                                                                        */
/**************************************************************************/


/**************************************************************************/
/**************************************************************************/
/**                                                                       */
/** NetX 组件                                                            */
/**                                                                       */
/**   MQTT (消息队列遥测传输协议)                                         */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/


/**************************************************************************/
/*                                                                        */
/*  应用程序接口定义                                      发布版          */
/*                                                                        */
/*    nxd_mqtt_client.h                                   可移植的 C 语言  */
/*                                                           6.1.2        */
/*  作者                                                                  */
/*                                                                        */
/*    Yuxin Zhou, Microsoft Corporation                                   */
/*                                                                        */
/*  描述                                                                  */
/*                                                                        */
/*    本文件定义了 NetX MQTT 客户端组件，包括所有数据类型和外部引用。假设  */
/*    已经包含了 nx_api.h 和 nx_port.h 文件。                            */
/*                                                                        */
/*  发布历史                                                              */
/*                                                                        */
/*    日期              姓名                      描述                    */
/*                                                                        */
/*  05-19-2020     Yuxin Zhou               初始版本 6.0                   */
/*  09-30-2020     Yuxin Zhou               修改了注释，并添加了 ACK 接收  */
/*                                            通知，版本升级到 6.1         */
/*  11-09-2020     Yuxin Zhou               修改了注释，并添加了数据包 ID  */
/*                                            参数，版本升级到 6.1.2       */
/*                                                                        */
/**************************************************************************/

#ifndef _NXD_MQTT_CLIENT_H_
#define _NXD_MQTT_CLIENT_H_

/* 判断是否使用了 C++ 编译器。如果是，确保使用标准 C 处理 API 信息。 */

#ifdef   __cplusplus

/* 是的，C++ 编译器存在。使用标准 C。 */
extern   "C" {

#endif

#ifdef NX_SECURE_ENABLE
#include "nx_secure_tls_api.h"
#endif /* NX_SECURE_ENABLE */

#ifdef NXD_MQTT_CLOUD_ENABLE
#include "nx_cloud.h"
#endif /* NXD_MQTT_CLOUD_ENABLE */

#ifdef NXD_MQTT_REQUIRE_TLS
#ifndef NX_SECURE_ENABLE
#error "该功能 NXD_MQTT_REQUIRE_TLS 需要启用 NX_SECURE_ENABLE。"
#endif /* NX_SECURE_ENABLE */
#endif /* NXD_MQTT_REQUIRE_TLS */

/* 定义在内部使用的 memcpy、memset 和 memcmp 函数。 */
#ifndef NXD_MQTT_SECURE_MEMCPY
#define NXD_MQTT_SECURE_MEMCPY                                         memcpy
#endif /* NXD_MQTT_SECURE_MEMCPY */

#ifndef NXD_MQTT_SECURE_MEMCMP
#define NXD_MQTT_SECURE_MEMCMP                                         memcmp
#endif /* NXD_MQTT_SECURE_MEMCMP */

#ifndef NXD_MQTT_SECURE_MEMSET
#define NXD_MQTT_SECURE_MEMSET                                         memset
#endif /* NXD_SECURE_MEMSET */

#ifndef NXD_MQTT_SECURE_MEMMOVE
#define NXD_MQTT_SECURE_MEMMOVE                                        memmove
#endif /* NXD_MQTT_SECURE_MEMMOVE */

/* 定义默认的 MQTT 非 TLS（非安全）端口号 */
#define NXD_MQTT_PORT                                                  1883

/* 定义默认的 TCP 套接字窗口大小。 */
#ifndef NXD_MQTT_CLIENT_SOCKET_WINDOW_SIZE
#define NXD_MQTT_CLIENT_SOCKET_WINDOW_SIZE                             8192
#endif /* NXD_MQTT_CLIENT_SOCKET_WINDOW_SIZE */

/* 定义默认的 MQTT 线程时间片。 */
#ifndef NXD_MQTT_CLIENT_THREAD_TIME_SLICE
#define NXD_MQTT_CLIENT_THREAD_TIME_SLICE                              2
#endif

/* 设置保持活动计时器的默认计时速率，单位为 ThreadX 定时器滴答。默认值为一秒。 */
#ifndef NXD_MQTT_KEEPALIVE_TIMER_RATE
#define NXD_MQTT_KEEPALIVE_TIMER_RATE                                  (NX_IP_PERIODIC_RATE)
#endif

/* 设置 PING 响应的默认超时时间。*/
/* 在发送 MQTT Ping 请求后，如果客户端在此时间内未收到 Ping 响应，则客户端将断开与服务器的连接。默认值为一秒。 */
#ifndef NXD_MQTT_PING_TIMEOUT_DELAY
#define NXD_MQTT_PING_TIMEOUT_DELAY                                    (NX_IP_PERIODIC_RATE)
#endif

/* 已弃用。此符号定义用于兼容性。 */
#ifndef NXD_MQTT_MAX_TOPIC_NAME_LENGTH
#define NXD_MQTT_MAX_TOPIC_NAME_LENGTH                                 12
#endif

/* 已弃用。此符号定义用于兼容性。 */
#ifndef NXD_MQTT_MAX_MESSAGE_LENGTH
#define NXD_MQTT_MAX_MESSAGE_LENGTH                                    32
#endif

#ifndef NXD_MQTT_INITIAL_PACKET_ID_VALUE
#define NXD_MQTT_INITIAL_PACKET_ID_VALUE                               1
#endif

/* 为套接字操作（发送、接收、断开连接）设置超时时间。 */
#ifndef NXD_MQTT_SOCKET_TIMEOUT
#define NXD_MQTT_SOCKET_TIMEOUT                                         NX_WAIT_FOREVER
#endif

/* 定义默认的 MQTT TLS（安全）端口号 */
#define NXD_MQTT_TLS_PORT                                              8883


// 定义 MQTT 协议版本
#define MQTT_PROTOCOL_LEVEL                                            4

/* 定义 CONNECT 数据包中使用的位字段和常量值。 */
// 用户名标志，表示在 CONNECT 数据包中包含用户名
#define MQTT_CONNECT_FLAGS_USERNAME                                    (1 << 7)
// 密码标志，表示在 CONNECT 数据包中包含密码
#define MQTT_CONNECT_FLAGS_PASSWORD                                    (1 << 6)
// 保留标志，表示保留最后一条消息
#define MQTT_CONNECT_FLAGS_WILL_RETAIN                                 (1 << 5)
// 将要发布的消息的 QoS 等级 0
#define MQTT_CONNECT_FLAGS_WILL_QOS_0                                  0
// 将要发布的消息的 QoS 等级 1
#define MQTT_CONNECT_FLAGS_WILL_QOS_1                                  (1 << 3)
// 将要发布的消息的 QoS 等级 2
#define MQTT_CONNECT_FLAGS_WILL_QOS_2                                  (2 << 3)
// 将要发布的标志，表示是否包含遗嘱消息
#define MQTT_CONNECT_FLAGS_WILL_FLAG                                   (1 << 2)
// 清除会话标志，表示是否清除之前的会话
#define MQTT_CONNECT_FLAGS_CLEAN_SESSION                               (1 << 1)
// 将要发布的 QoS 字段，用于表示消息的 QoS 等级
#define MQTT_CONNECT_FLAGS_WILL_QOS_FIELD                              (3 << 3)

/* 定义 CONNACK 数据包中使用的位字段和常量值。 */
// 服务提供标志
#define MQTT_CONNACK_CONNECT_FLAGS_SP                                  (1)
// 连接返回码：已接受
#define MQTT_CONNACK_CONNECT_RETURN_CODE_ACCEPTED                      (0)
// 连接返回码：不接受的协议版本
#define MQTT_CONNACK_CONNECT_RETURN_CODE_UNACCEPTABLE_PROTOCOL_VERSION (1)
// 连接返回码：标识符被拒绝
#define MQTT_CONNACK_CONNECT_RETURN_CODE_IDENTIFIER_REJECTED           (2)
// 连接返回码：服务器不可用
#define MQTT_CONNACK_CONNECT_RETURN_CODE_SERVER_UNAVAILABLE            (3)
// 连接返回码：错误的用户名或密码
#define MQTT_CONNACK_CONNECT_RETURN_CODE_BAD_USERNAME_PASSWORD         (4)
// 连接返回码：未授权
#define MQTT_CONNACK_CONNECT_RETURN_CODE_NOT_AUTHORIZED                (5)

/* 定义 PUBLISH 数据包中使用的位字段和常量值。 */
// 重发标志，表示消息是否为重复发送
#define MQTT_PUBLISH_DUP_FLAG                                          (1 << 3)
// 发布的 QoS 等级 0
#define MQTT_PUBLISH_QOS_LEVEL_0                                       (0)
// 发布的 QoS 等级 1
#define MQTT_PUBLISH_QOS_LEVEL_1                                       (1 << 1)
// 发布的 QoS 等级 2
#define MQTT_PUBLISH_QOS_LEVEL_2                                       (2 << 1)
// QoS 等级字段，用于表示消息的 QoS 等级
#define MQTT_PUBLISH_QOS_LEVEL_FIELD                                   (3 << 1)
// 保留标志，表示消息应被保留
#define MQTT_PUBLISH_RETAIN                                            (1)

// 控制报文类型字段掩码
#define MQTT_CONTROL_PACKET_TYPE_FIELD                                 0xF0

// 定义固定头部大小
#define MQTT_FIXED_HEADER_SIZE                                         2

// 控制报文类型定义
#define MQTT_CONTROL_PACKET_TYPE_CONNECT                               (1)  // CONNECT 报文
#define MQTT_CONTROL_PACKET_TYPE_CONNACK                               (2)  // CONNACK 报文
#define MQTT_CONTROL_PACKET_TYPE_PUBLISH                               (3)  // PUBLISH 报文
#define MQTT_CONTROL_PACKET_TYPE_PUBACK                                (4)  // PUBACK 报文
#define MQTT_CONTROL_PACKET_TYPE_PUBREC                                (5)  // PUBREC 报文
#define MQTT_CONTROL_PACKET_TYPE_PUBREL                                (6)  // PUBREL 报文
#define MQTT_CONTROL_PACKET_TYPE_PUBCOMP                               (7)  // PUBCOMP 报文
#define MQTT_CONTROL_PACKET_TYPE_SUBSCRIBE                             (8)  // SUBSCRIBE 报文
#define MQTT_CONTROL_PACKET_TYPE_SUBACK                                (9)  // SUBACK 报文
#define MQTT_CONTROL_PACKET_TYPE_UNSUBSCRIBE                           (10) // UNSUBSCRIBE 报文
#define MQTT_CONTROL_PACKET_TYPE_UNSUBACK                              (11) // UNSUBACK 报文
#define MQTT_CONTROL_PACKET_TYPE_PINGREQ                               (12) // PINGREQ 报文
#define MQTT_CONTROL_PACKET_TYPE_PINGRESP                              (13) // PINGRESP 报文
#define MQTT_CONTROL_PACKET_TYPE_DISCONNECT                            (14) // DISCONNECT 报文

/* 判断是否使用了 C++ 编译器。如果是，完成上面启动的标准 C 条件编译。 */


/* MQTT CONNACK 数据包结构体定义 */
/* 用于表示服务端对客户端连接请求的响应数据包 */
typedef struct MQTT_PACKET_CONNACK_STRUCT
{
    UCHAR mqtt_connack_packet_header;             /* CONNACK 数据包的固定头部 */
    UCHAR mqtt_connack_packet_remaining_length;   /* 剩余长度字段，表示CONNACK数据包的字节数，不包括固定头部 */
    UCHAR mqtt_connack_packet_ack_flags;          /* 确认标志字段，用于指示连接的会话状态 */
    UCHAR mqtt_connack_packet_return_code;        /* 返回码，指示连接请求的结果 */
} MQTT_PACKET_CONNACK;

/* MQTT PUBLISH 数据包结构体定义 */
/* 用于表示客户端或服务端发布的消息数据包 */
typedef struct MQTT_PACKET_PUBLISH_STRUCT
{
    UCHAR mqtt_publish_packet_header;             /* PUBLISH 数据包的固定头部 */
    UCHAR mqtt_publish_packet_remaining_length;   /* 剩余长度字段，表示 PUBLISH 数据包的字节数，不包括固定头部 */
} MQTT_PACKET_PUBLISH;

/* MQTT PUBLISH 响应数据包结构体定义 */
/* 用于表示针对发布请求的响应数据包，如 PUBACK、PUBREC、PUBREL、PUBCOMP */
typedef struct MQTT_PACKET_PUBLISH_RESPONSE_STRUCT
{
    UCHAR mqtt_publish_response_packet_header;                /* PUBLISH 响应数据包的固定头部 */
    UCHAR mqtt_publish_response_packet_remaining_length;      /* 剩余长度字段，表示 PUBLISH 响应数据包的字节数，不包括固定头部 */
    UCHAR mqtt_publish_response_packet_packet_identifier_msb; /* 数据包标识符的高字节，用于唯一标识数据包 */
    UCHAR mqtt_publish_response_packet_packet_identifier_lsb; /* 数据包标识符的低字节 */
} MQTT_PACKET_PUBLISH_RESPONSE;

/* MQTT SUBSCRIBE 数据包结构体定义 */
/* 用于表示客户端向服务端发送的订阅请求数据包 */
typedef struct MQTT_PACKET_SUBSCRIBE_STRUCT
{
    UCHAR mqtt_subscribe_packet_header;                     /* SUBSCRIBE 数据包的固定头部 */
    UCHAR mqtt_subscribe_packet_remaining_length;           /* 剩余长度字段，表示 SUBSCRIBE 数据包的字节数，不包括固定头部 */
    UCHAR mqtt_subscribe_packet_packet_identifier_msb;      /* 数据包标识符的高字节，用于唯一标识数据包 */
    UCHAR mqtt_subscribe_packet_packet_identifier_lsb;      /* 数据包标识符的低字节 */
} MQTT_PACKET_SUBSCRIBE;

/* MQTT PING 请求数据包结构体定义 */
/* 用于表示客户端向服务端发送的心跳请求数据包 */
typedef struct MQTT_PACKET_PING_STRUCT
{
    UCHAR mqtt_ping_packet_header;                /* PINGREQ 数据包的固定头部 */
    UCHAR mqtt_ping_packet_remaining_length;      /* 剩余长度字段，表示 PINGREQ 数据包的字节数，不包括固定头部 */
} MQTT_PACKET_PING;

/* MQTT DISCONNECT 数据包结构体定义 */
/* 用于表示客户端或服务端发送的断开连接请求数据包 */
typedef struct MQTT_PACKET_DISCONNECT_STRUCT
{
    UCHAR mqtt_disconnect_packet_header;          /* DISCONNECT 数据包的固定头部 */
    UCHAR mqtt_disconnect_packet_remaining_length;/* 剩余长度字段，表示 DISCONNECT 数据包的字节数，不包括固定头部 */
} MQTT_PACKET_DISCONNECT;


/* 定义 NetX MQTT 客户端标识符 */
#define NXD_MQTT_CLIENT_ID                   0x4D515454

/* 定义默认的 MQTT 非 TLS（非安全）端口号 */
#define NXD_MQTT_CLIENT_NONTLS_PORT          1883

/* 定义默认的 MQTT TLS（安全）端口号 */
#define NXD_MQTT_CLIENT_TLS_PORT             8883

/* 定义 MQTT 客户端状态 */
#define NXD_MQTT_CLIENT_STATE_INITIALIZE     0  /* 初始化状态 */
#define NXD_MQTT_CLIENT_STATE_IDLE           1  /* 空闲状态 */
#define NXD_MQTT_CLIENT_STATE_CONNECTING     2  /* 正在连接状态 */
#define NXD_MQTT_CLIENT_STATE_CONNECTED      3  /* 已连接状态 */

/* 定义 MQTT 操作的返回状态码 */
#define NXD_MQTT_SUCCESS                     0x0     /* 操作成功 */
#define NXD_MQTT_ALREADY_CONNECTED           0x10001 /* 已经连接 */
#define NXD_MQTT_NOT_CONNECTED               0x10002 /* 未连接 */
#define NXD_MQTT_MUTEX_FAILURE               0x10003 /* 互斥锁操作失败 */
#define NXD_MQTT_INTERNAL_ERROR              0x10004 /* 内部错误 */
#define NXD_MQTT_CONNECT_FAILURE             0x10005 /* 连接失败 */
#define NXD_MQTT_PACKET_POOL_FAILURE         0x10006 /* 数据包池分配失败 */
#define NXD_MQTT_COMMUNICATION_FAILURE       0x10007 /* 通信失败 */
#define NXD_MQTT_SERVER_MESSAGE_FAILURE      0x10008 /* 服务器消息处理失败 */
#define NXD_MQTT_INVALID_PARAMETER           0x10009 /* 无效的参数 */
#define NXD_MQTT_NO_MESSAGE                  0x1000A /* 没有消息 */
#define NXD_MQTT_PACKET_POOL_EMPTY           0x1000B /* 数据包池为空 */
#define NXD_MQTT_QOS2_NOT_SUPPORTED          0x1000C /* 不支持 QoS 2 */
#define NXD_MQTT_INSUFFICIENT_BUFFER_SPACE   0x1000D /* 缓冲区空间不足 */
#define NXD_MQTT_CLIENT_NOT_RUNNING          0x1000E /* 客户端未运行 */
#define NXD_MQTT_INVALID_PACKET              0x1000F /* 无效的数据包 */
#define NXD_MQTT_PARTIAL_PACKET              0x10010 /* 数据包不完整 */
#define NXD_MQTT_CONNECTING                  0x10011 /* 正在连接中 */
#define NXD_MQTT_INVALID_STATE               0x10012 /* 无效的状态 */

/* 以下错误码与 CONNACK 消息中的连接返回码相匹配 */
#define NXD_MQTT_ERROR_CONNECT_RETURN_CODE   0x10080 /* 连接返回码错误 */
#define NXD_MQTT_ERROR_UNACCEPTABLE_PROTOCOL 0x10081 /* 不可接受的协议版本 */
#define NXD_MQTT_ERROR_IDENTIFYIER_REJECTED  0x10082 /* 标识符被拒绝 */
#define NXD_MQTT_ERROR_SERVER_UNAVAILABLE    0x10083 /* 服务器不可用 */
#define NXD_MQTT_ERROR_BAD_USERNAME_PASSWORD 0x10084 /* 用户名或密码错误 */
#define NXD_MQTT_ERROR_NOT_AUTHORIZED        0x10085 /* 未授权 */


typedef struct NXD_MQTT_CLIENT_STRUCT
{
    CHAR *nxd_mqtt_client_name;                       /* MQTT 客户端名称。 */
    CHAR *nxd_mqtt_client_id;                         /* 客户端的 MQTT ID。 */
    UINT nxd_mqtt_client_id_length;                   /* 客户端 ID 的长度。 */
    CHAR *nxd_mqtt_client_username;                   /* 客户端的用户名。 */
    USHORT nxd_mqtt_client_username_length;           /* 用户名的长度。 */
    CHAR *nxd_mqtt_client_password;                   /* 客户端的密码。 */
    USHORT nxd_mqtt_client_password_length;           /* 密码的长度。 */
    UCHAR nxd_mqtt_client_will_qos_retain;            /* 客户端遗嘱消息的 QoS 级别和保留标志。 */
    const UCHAR *nxd_mqtt_client_will_topic;          /* 遗嘱消息的主题。 */
    UINT nxd_mqtt_client_will_topic_length;           /* 遗嘱消息主题的长度。 */
    const UCHAR *nxd_mqtt_client_will_message;        /* 遗嘱消息的内容。 */
    UINT nxd_mqtt_client_will_message_length;         /* 遗嘱消息内容的长度。 */
    NX_IP *nxd_mqtt_client_ip_ptr;                    /* 指向关联的 IP 结构的指针。 */
    NX_PACKET_POOL *nxd_mqtt_client_packet_pool_ptr;  /* 指向客户端数据包池的指针。 */
    TX_MUTEX *nxd_mqtt_client_mutex_ptr;              /* 指向客户端互斥锁的指针。 */
    TX_TIMER nxd_mqtt_timer;                          /* MQTT 客户端定时器。 */
    
#ifndef NXD_MQTT_CLOUD_ENABLE
    TX_MUTEX nxd_mqtt_protection;                     /* MQTT 客户端保护互斥锁。 */
    TX_THREAD nxd_mqtt_thread;                        /* MQTT 客户端线程。 */
    TX_EVENT_FLAGS_GROUP nxd_mqtt_events;             /* MQTT 事件标志组。 */
#else
    NX_CLOUD *nxd_mqtt_client_cloud_ptr;              /* 指向关联的云结构的指针。 */
    NX_CLOUD nxd_mqtt_client_cloud;                   /* MQTT 云实例。 */
    NX_CLOUD_MODULE nxd_mqtt_client_cloud_module;     /* 在云助手线程上运行的 MQTT 模块。 */
#endif /* NXD_MQTT_CLOUD_ENABLE */

    UINT nxd_mqtt_ping_timeout;                       /* PING 操作的超时时间。 */
    UINT nxd_mqtt_ping_not_responded;                 /* 标志指示 PING 是否已响应。 */
    UINT nxd_mqtt_ping_sent_time;                     /* 发送 PING 消息时的 TX 计时器刻度。 */
    UINT nxd_mqtt_timeout;                            /* 下次超时时的 TX 计时器刻度。 */
    UINT nxd_mqtt_timer_value;                        /* MQTT 客户端周期性定时器的刻度值。 */
    UINT nxd_mqtt_keepalive;                          /* 保持活动的值，转换为 TX 刻度。 */
    UINT nxd_mqtt_clean_session;                      /* 清除会话标志。 */
    UINT nxd_mqtt_client_state;                       /* 记录客户端状态。 */
    NX_TCP_SOCKET nxd_mqtt_client_socket;             /* 客户端的 TCP 套接字。 */
    struct NXD_MQTT_CLIENT_STRUCT *nxd_mqtt_client_next; /* 指向下一个客户端结构的指针。 */
    UINT nxd_mqtt_client_packet_identifier;           /* 客户端数据包标识符。 */
    NX_PACKET *nxd_mqtt_client_processing_packet;     /* 正在处理的数据包。 */
    NX_PACKET *message_transmit_queue_head;           /* 消息发送队列的头指针。 */
    NX_PACKET *message_transmit_queue_tail;           /* 消息发送队列的尾指针。 */
    NX_PACKET *message_receive_queue_head;            /* 消息接收队列的头指针。 */
    NX_PACKET *message_receive_queue_tail;            /* 消息接收队列的尾指针。 */
    UINT message_receive_queue_depth;                 /* 消息接收队列的深度。 */
    VOID (*nxd_mqtt_client_receive_notify)(struct NXD_MQTT_CLIENT_STRUCT *client_ptr, UINT number_of_messages); /* 消息接收通知的回调函数。 */
    VOID (*nxd_mqtt_connect_notify)(struct NXD_MQTT_CLIENT_STRUCT *client_ptr, UINT status, VOID *context);      /* 连接状态的通知回调函数。 */
    VOID *nxd_mqtt_connect_context;                   /* 连接状态回调的上下文指针。 */
    VOID (*nxd_mqtt_disconnect_notify)(struct NXD_MQTT_CLIENT_STRUCT *client_ptr); /* 断开连接状态的通知回调函数。 */
    UINT (*nxd_mqtt_packet_receive_notify)(struct NXD_MQTT_CLIENT_STRUCT *client_ptr, NX_PACKET *packet_ptr, VOID *context); /* 数据包接收通知的回调函数。 */
    VOID *nxd_mqtt_packet_receive_context;            /* 数据包接收回调的上下文指针。 */
    VOID (*nxd_mqtt_ack_receive_notify)(struct NXD_MQTT_CLIENT_STRUCT *client_ptr, UINT type, USHORT packet_id, NX_PACKET *transmit_packet_ptr, VOID *context); /* 确认消息接收通知的回调函数。 */
    VOID *nxd_mqtt_ack_receive_context;               /* 确认消息接收回调的上下文指针。 */
    
#ifdef NX_SECURE_ENABLE
    UINT nxd_mqtt_client_use_tls;                     /* 指示客户端是否使用 TLS。 */
    UINT (*nxd_mqtt_tls_setup)(struct NXD_MQTT_CLIENT_STRUCT *, NX_SECURE_TLS_SESSION *, NX_SECURE_X509_CERT *, NX_SECURE_X509_CERT *); /* TLS 设置的回调函数。 */
    NX_SECURE_X509_CERT nxd_mqtt_tls_certificate;     /* 客户端 TLS 证书。 */
    NX_SECURE_X509_CERT nxd_mqtt_tls_trusted_certificate; /* 受信任的 TLS 证书。 */
    NX_SECURE_TLS_SESSION nxd_mqtt_tls_session;       /* TLS 会话。 */
    UINT nxd_mqtt_tls_in_progress;                    /* TLS 正在进行中的标志。 */
#endif
} NXD_MQTT_CLIENT;


#ifndef NXD_MQTT_CLIENT_SOURCE_CODE

/* 应用程序调用者存在时，执行 API 映射。 */

/* 确定是否需要进行错误检查。如果需要，将 API 函数映射到适当的错误检查前端。
   否则，将 API 函数映射到实际执行工作的核心函数。
   注意：默认启用错误检查。 */

#ifdef NX_DISABLE_ERROR_CHECKING

#define nxd_mqtt_client_create                _nxd_mqtt_client_create
#define nxd_mqtt_client_login_set             _nxd_mqtt_client_login_set
#define nxd_mqtt_client_will_message_set      _nxd_mqtt_client_will_message_set
#define nxd_mqtt_client_delete                _nxd_mqtt_client_delete
#define nxd_mqtt_client_connect               _nxd_mqtt_client_connect
#define nxd_mqtt_client_secure_connect        _nxd_mqtt_client_secure_connect
#define nxd_mqtt_client_publish               _nxd_mqtt_client_publish
#define nxd_mqtt_client_subscribe             _nxd_mqtt_client_subscribe
#define nxd_mqtt_client_unsubscribe           _nxd_mqtt_client_unsubscribe
#define nxd_mqtt_client_disconnect            _nxd_mqtt_client_disconnect
#define nxd_mqtt_client_receive_notify_set    _nxd_mqtt_client_receive_notify_set
#define nxd_mqtt_client_message_get           _nxd_mqtt_client_message_get
#define nxd_mqtt_client_disconnect_notify_set _nxd_mqtt_client_disconnect_notify_set

/* 如果禁用了错误检查，API 函数直接映射到核心函数。
   例如：nxd_mqtt_client_create 映射到 _nxd_mqtt_client_create，
   它是实际执行创建 MQTT 客户端的核心函数。 */

#else /* 如果未禁用错误检查 */

#define nxd_mqtt_client_create                _nxde_mqtt_client_create
#define nxd_mqtt_client_login_set             _nxde_mqtt_client_login_set
#define nxd_mqtt_client_will_message_set      _nxde_mqtt_client_will_message_set
#define nxd_mqtt_client_delete                _nxde_mqtt_client_delete
#define nxd_mqtt_client_connect               _nxde_mqtt_client_connect
#define nxd_mqtt_client_secure_connect        _nxde_mqtt_client_secure_connect
#define nxd_mqtt_client_publish               _nxde_mqtt_client_publish
#define nxd_mqtt_client_subscribe             _nxde_mqtt_client_subscribe
#define nxd_mqtt_client_unsubscribe           _nxde_mqtt_client_unsubscribe
#define nxd_mqtt_client_disconnect            _nxde_mqtt_client_disconnect
#define nxd_mqtt_client_receive_notify_set    _nxde_mqtt_client_receive_notify_set
#define nxd_mqtt_client_message_get           _nxde_mqtt_client_message_get
#define nxd_mqtt_client_disconnect_notify_set _nxde_mqtt_client_disconnect_notify_set

/* 如果启用了错误检查，API 函数映射到带有错误检查功能的函数。
   例如：nxd_mqtt_client_create 映射到 _nxde_mqtt_client_create，
   它在调用核心函数之前进行错误检查。 */

#endif /* NX_DISABLE_ERROR_CHECKING */


/**
 * @brief 创建一个 MQTT 客户端。
 * 
 * @param client_ptr 指向要创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param client_name 客户端名称的字符串指针。
 * @param client_id 客户端 ID 的字符串指针。
 * @param client_id_length 客户端 ID 的长度。
 * @param ip_ptr 指向与该客户端关联的 IP 结构体的指针。
 * @param pool_ptr 指向用于客户端的包池的指针。
 * @param stack_ptr 指向用于 MQTT 客户端的线程栈的指针。
 * @param stack_size 线程栈的大小。
 * @param mqtt_thread_priority MQTT 线程的优先级。
 * @param memory_ptr 指向用于 MQTT 客户端的内存的指针。
 * @param memory_size 用于 MQTT 客户端的内存大小。
 * 
 * @return 返回创建操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT nxd_mqtt_client_create(NXD_MQTT_CLIENT *client_ptr, CHAR *client_name, CHAR *client_id, UINT client_id_length,
                            NX_IP *ip_ptr, NX_PACKET_POOL *pool_ptr, VOID *stack_ptr, ULONG stack_size, UINT mqtt_thread_priority,
                            VOID *memory_ptr, ULONG memory_size);

/**
 * @brief 连接到 MQTT 服务器。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param server_ip 指向服务器 IP 地址的指针。
 * @param server_port 服务器的端口号。
 * @param keepalive 保持连接的心跳时间（秒）。
 * @param clean_session 清除会话标志，如果为 1，则在连接时清除以前的会话数据。
 * @param timeout 连接超时时间（毫秒）。
 * 
 * @return 返回连接操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT nxd_mqtt_client_connect(NXD_MQTT_CLIENT *client_ptr, NXD_ADDRESS *server_ip, UINT server_port,
                             UINT keepalive, UINT clean_session, ULONG timeout);

/**
 * @brief 设置 MQTT 客户端的登录信息（用户名和密码）。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param username 用户名字符串指针。
 * @param username_length 用户名的长度。
 * @param password 密码字符串指针。
 * @param password_length 密码的长度。
 * 
 * @return 返回设置操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT nxd_mqtt_client_login_set(NXD_MQTT_CLIENT *client_ptr,
                               CHAR *username, UINT username_length, CHAR *password, UINT password_length);

/**
 * @brief 设置 MQTT 客户端的遗嘱消息。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param will_topic 遗嘱消息的主题字符串指针。
 * @param will_topic_length 遗嘱消息主题的长度。
 * @param will_message 遗嘱消息的内容字符串指针。
 * @param will_message_length 遗嘱消息内容的长度。
 * @param will_retain_flag 遗嘱消息的保留标志。
 * @param will_QoS 遗嘱消息的 QoS 等级。
 * 
 * @return 返回设置操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT nxd_mqtt_client_will_message_set(NXD_MQTT_CLIENT *client_ptr,
                                      const UCHAR *will_topic, UINT will_topic_length, UCHAR *will_message, UINT will_message_length,
                                      UINT will_retain_flag, UINT will_QoS);

#ifdef NX_SECURE_ENABLE
/**
 * @brief 安全连接到 MQTT 服务器（使用 TLS）。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param server_ip 指向服务器 IP 地址的指针。
 * @param server_port 服务器的端口号。
 * @param tls_setup 指向用于 TLS 设置的回调函数指针。
 * @param keepalive 保持连接的心跳时间（秒）。
 * @param clean_session 清除会话标志，如果为 1，则在连接时清除以前的会话数据。
 * @param timeout 连接超时时间（毫秒）。
 * 
 * @return 返回连接操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT nxd_mqtt_client_secure_connect(NXD_MQTT_CLIENT *client_ptr, NXD_ADDRESS *server_ip, UINT server_port,
                                    UINT (*tls_setup)(NXD_MQTT_CLIENT *client_ptr, NX_SECURE_TLS_SESSION *, NX_SECURE_X509_CERT *, NX_SECURE_X509_CERT *),
                                    UINT keepalive, UINT clean_session, ULONG timeout);
#endif
									  
/**
 * @brief 发布消息到指定主题。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param topic_name 要发布消息的主题名称字符串指针。
 * @param topic_name_length 主题名称的长度。
 * @param message 要发布的消息内容字符串指针。
 * @param message_length 消息内容的长度。
 * @param retain 是否保留消息的标志，1 表示保留，0 表示不保留。
 * @param QoS 消息的 QoS 等级（0、1 或 2）。
 * @param timeout 发布操作的超时时间（毫秒）。
 * 
 * @return 返回发布操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT nxd_mqtt_client_publish(NXD_MQTT_CLIENT *client_ptr, CHAR *topic_name, UINT topic_name_length, CHAR *message, UINT message_length,
                             UINT retain, UINT QoS, ULONG timeout);

/**
 * @brief 订阅指定主题。
 * 
 * @param mqtt_client_pr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param topic_name 要订阅的主题名称字符串指针。
 * @param topic_name_length 主题名称的长度。
 * @param QoS 订阅时的 QoS 等级（0、1 或 2）。
 * 
 * @return 返回订阅操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT nxd_mqtt_client_subscribe(NXD_MQTT_CLIENT *mqtt_client_pr, CHAR *topic_name, UINT topic_name_length, UINT QoS);

/**
 * @brief 取消订阅指定主题。
 * 
 * @param mqtt_client_pr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param topic_name 要取消订阅的主题名称字符串指针。
 * @param topic_name_length 主题名称的长度。
 * 
 * @return 返回取消订阅操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT nxd_mqtt_client_unsubscribe(NXD_MQTT_CLIENT *mqtt_client_pr, CHAR *topic_name, UINT topic_name_length);

/**
 * @brief 设置接收通知的回调函数，当接收到消息时会调用该函数。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param receive_notify 接收通知的回调函数指针，参数包括 MQTT 客户端指针和接收到的消息数量。
 * 
 * @return 返回设置操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT nxd_mqtt_client_receive_notify_set(NXD_MQTT_CLIENT *client_ptr,
                                        VOID (*receive_notify)(NXD_MQTT_CLIENT *client_ptr, UINT number_of_messages));

/**
 * @brief 获取接收到的消息。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param topic_buffer 用于存放主题名称的缓冲区指针。
 * @param topic_buffer_size 主题名称缓冲区的大小。
 * @param actual_topic_length 实际主题名称的长度，输出参数。
 * @param message_buffer 用于存放消息内容的缓冲区指针。
 * @param message_buffer_size 消息内容缓冲区的大小。
 * @param actual_message_length 实际消息内容的长度，输出参数。
 * 
 * @return 返回获取操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT nxd_mqtt_client_message_get(NXD_MQTT_CLIENT *client_ptr, UCHAR *topic_buffer, UINT topic_buffer_size, UINT *actual_topic_length,
                                 UCHAR *message_buffer, UINT message_buffer_size, UINT *actual_message_length);

/**
 * @brief 与 MQTT 服务器断开连接。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * 
 * @return 返回断开连接操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT nxd_mqtt_client_disconnect(NXD_MQTT_CLIENT *client_ptr);

/**
 * @brief 删除 MQTT 客户端，释放相关资源。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * 
 * @return 返回删除操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT nxd_mqtt_client_delete(NXD_MQTT_CLIENT *client_ptr);

/**
 * @brief 设置断开连接通知的回调函数，当与服务器断开连接时会调用该函数。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param disconnect_notify 断开连接通知的回调函数指针。
 * 
 * @return 返回设置操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT nxd_mqtt_client_disconnect_notify_set(NXD_MQTT_CLIENT *client_ptr, VOID (*disconnect_notify)(NXD_MQTT_CLIENT *));

#else /* ifdef NXD_MQTT_CLIENT_SOURCE_CODE */

/**
 * @brief 建立与 MQTT 服务器的连接。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param server_ip 指向服务器 IP 地址的 NXD_ADDRESS 结构体指针。
 * @param server_port 服务器的端口号。
 * @param keepalive 保持连接的心跳时间（秒）。
 * @param clean_session 是否清除会话标志，1 表示清除，0 表示保留。
 * @param wait_option 等待选项，指定操作的超时时间。
 * 
 * @return 返回连接操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT _nxd_mqtt_client_connect(NXD_MQTT_CLIENT *client_ptr, NXD_ADDRESS *server_ip, UINT server_port,
                              UINT keepalive, UINT clean_session, ULONG wait_option);

/**
 * @brief 创建一个 MQTT 客户端实例。
 * 
 * @param client_ptr 指向要创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param client_name 客户端名称字符串指针。
 * @param client_id 客户端 ID 字符串指针。
 * @param client_id_length 客户端 ID 的长度。
 * @param ip_ptr 指向关联的 NX_IP 结构体的指针。
 * @param pool_ptr 指向用于客户端的 NX_PACKET_POOL 结构体的指针。
 * @param stack_ptr 指向线程栈的指针。
 * @param stack_size 线程栈的大小。
 * @param mqtt_thread_priority MQTT 线程的优先级。
 * @param memory_ptr 用于分配客户端内存的指针。
 * @param memory_size 要分配的内存大小。
 * 
 * @return 返回创建操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT _nxd_mqtt_client_create(NXD_MQTT_CLIENT *client_ptr, CHAR *client_name,
                             CHAR *client_id, UINT client_id_length,
                             NX_IP *ip_ptr, NX_PACKET_POOL *pool_ptr,
                             VOID *stack_ptr, ULONG stack_size, UINT mqtt_thread_priority,
                             VOID *memory_ptr, ULONG memory_size);

/**
 * @brief 删除 MQTT 客户端，释放相关资源。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * 
 * @return 返回删除操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT _nxd_mqtt_client_delete(NXD_MQTT_CLIENT *client_ptr);

/**
 * @brief 与 MQTT 服务器断开连接。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * 
 * @return 返回断开连接操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT _nxd_mqtt_client_disconnect(NXD_MQTT_CLIENT *client_ptr);

/**
 * @brief 设置断开连接通知的回调函数，当与服务器断开连接时会调用该函数。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param disconnect_notify 断开连接通知的回调函数指针。
 * 
 * @return 返回设置操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT _nxd_mqtt_client_disconnect_notify_set(NXD_MQTT_CLIENT *client_ptr, VOID (*disconnect_notify)(NXD_MQTT_CLIENT *));

/**
 * @brief 设置客户端的用户名和密码，用于连接 MQTT 服务器时的身份验证。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param username 用户名字符串指针。
 * @param username_length 用户名的长度。
 * @param password 密码字符串指针。
 * @param password_length 密码的长度。
 * 
 * @return 返回设置操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT _nxd_mqtt_client_login_set(NXD_MQTT_CLIENT *client_ptr,
                                CHAR *username, UINT username_length, CHAR *password, UINT password_length);
/**
 * @brief 获取接收到的消息及其主题。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param topic_buffer 用于存储主题的缓冲区。
 * @param topic_buffer_size 主题缓冲区的大小。
 * @param actual_topic_length 实际主题长度的指针，函数返回时会设置该值。
 * @param message_buffer 用于存储消息的缓冲区。
 * @param message_buffer_size 消息缓冲区的大小。
 * @param actual_message_length 实际消息长度的指针，函数返回时会设置该值。
 * 
 * @return 返回获取消息操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT _nxd_mqtt_client_message_get(NXD_MQTT_CLIENT *client_ptr, UCHAR *topic_buffer, UINT topic_buffer_size, UINT *actual_topic_length,
                                  UCHAR *message_buffer, UINT message_buffer_size, UINT *actual_message_length);

/**
 * @brief 发送 MQTT 发布数据包。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param packet_ptr 指向要发送的 NX_PACKET 数据包的指针。
 * @param packet_id 消息包的标识符。
 * @param QoS 消息的服务质量等级。
 * @param wait_option 等待选项，指定操作的超时时间。
 * 
 * @return 返回发送操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT _nxd_mqtt_client_publish_packet_send(NXD_MQTT_CLIENT *client_ptr, NX_PACKET *packet_ptr,
                                          USHORT packet_id, UINT QoS, ULONG wait_option);

/**
 * @brief 发布消息到指定主题。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param topic_name 发布消息的主题字符串指针。
 * @param topic_name_length 主题名称的长度。
 * @param message 要发布的消息字符串指针。
 * @param message_length 消息的长度。
 * @param retain 是否保留消息标志，1 表示保留，0 表示不保留。
 * @param QoS 消息的服务质量等级。
 * @param timeout 超时设置，指定操作的超时时间。
 * 
 * @return 返回发布操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT _nxd_mqtt_client_publish(NXD_MQTT_CLIENT *client_ptr, CHAR *topic_name, UINT topic_name_length,
                              CHAR *message, UINT message_length, UINT retain, UINT QoS, ULONG timeout);

/**
 * @brief 设置接收消息的通知回调函数，当接收到消息时会调用该函数。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param receive_notify 接收消息通知的回调函数指针。
 * 
 * @return 返回设置操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT _nxd_mqtt_client_receive_notify_set(NXD_MQTT_CLIENT *client_ptr,
                                         VOID (*receive_notify)(NXD_MQTT_CLIENT *client_ptr, UINT message_count));

/**
 * @brief 设置内存释放回调函数，用于在消息接收后释放内存。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param memory_release_function 内存释放函数的指针。
 * 
 * @return 返回设置操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT _nxd_mqtt_client_release_callback_set(NXD_MQTT_CLIENT *client_ptr, VOID (*memory_release_function)(CHAR *, UINT));

/**
 * @brief 订阅或取消订阅主题。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param op 操作类型，订阅或取消订阅的标识。
 * @param topic_name 主题名称字符串指针。
 * @param topic_name_length 主题名称的长度。
 * @param packet_id_ptr 消息包标识符的指针。
 * @param QoS 消息的服务质量等级。
 * 
 * @return 返回操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT _nxd_mqtt_client_sub_unsub(NXD_MQTT_CLIENT *client_ptr, UINT op,
                                CHAR *topic_name, UINT topic_name_length, USHORT *packet_id_ptr, UINT QoS);

/**
 * @brief 订阅指定主题。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param topic_name 主题名称字符串指针。
 * @param topic_name_length 主题名称的长度。
 * @param QoS 消息的服务质量等级。
 * 
 * @return 返回订阅操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT _nxd_mqtt_client_subscribe(NXD_MQTT_CLIENT *client_ptr, CHAR *topic_name, UINT topic_name_length, UINT QoS);

/**
 * @brief 取消订阅指定主题。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param topic_name 主题名称字符串指针。
 * @param topic_name_length 主题名称的长度。
 * 
 * @return 返回取消订阅操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT _nxd_mqtt_client_unsubscribe(NXD_MQTT_CLIENT *client_ptr, CHAR *topic_name, UINT topic_name_length);

/**
 * @brief 设置遗嘱消息，用于在客户端意外断开时向服务器发布。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param will_topic 遗嘱消息的主题字符串指针。
 * @param will_topic_length 遗嘱主题的长度。
 * @param will_message 遗嘱消息字符串指针。
 * @param will_message_length 遗嘱消息的长度。
 * @param will_retain_flag 是否保留遗嘱消息标志，1 表示保留，0 表示不保留。
 * @param will_QoS 遗嘱消息的服务质量等级。
 * 
 * @return 返回设置操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT _nxd_mqtt_client_will_message_set(NXD_MQTT_CLIENT *client_ptr,
                                       const UCHAR *will_topic, UINT will_topic_length, const UCHAR *will_message,
                                       UINT will_message_length, UINT will_retain_flag, UINT will_QoS);
/**
 * @brief 从接收到的数据包中读取剩余长度。
 * 
 * @param packet_ptr 指向接收的 NX_PACKET 数据包的指针。
 * @param remaining_length 存储剩余长度的指针，函数返回时会设置该值。
 * @param offset_ptr 存储当前读取偏移量的指针，函数返回时会设置该值。
 * 
 * @return 返回读取操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT _nxd_mqtt_read_remaining_length(NX_PACKET *packet_ptr, UINT *remaining_length, ULONG *offset_ptr);

/**
 * @brief 设置 MQTT 数据包的固定头部。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param packet_ptr 指向要设置的 NX_PACKET 数据包的指针。
 * @param control_header 控制头部字段，指示消息类型和标志。
 * @param length 数据包的总长度。
 * @param wait_option 等待选项，指定操作的超时时间。
 * 
 * @return 返回设置操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT _nxd_mqtt_client_set_fixed_header(NXD_MQTT_CLIENT *client_ptr, NX_PACKET *packet_ptr, UCHAR control_header, UINT length, UINT wait_option);

/**
 * @brief 向 MQTT 数据包中附加消息。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param packet_ptr 指向要附加消息的 NX_PACKET 数据包的指针。
 * @param message 要附加的消息字符串指针。
 * @param length 消息的长度。
 * @param wait_option 等待选项，指定操作的超时时间。
 * 
 * @return 返回附加消息操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT _nxd_mqtt_client_append_message(NXD_MQTT_CLIENT *client_ptr, NX_PACKET *packet_ptr, CHAR *message, UINT length, ULONG wait_option);

/**
 * @brief 结束与 MQTT 服务器的连接。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param wait_option 等待选项，指定操作的超时时间。
 */
VOID _nxd_mqtt_client_connection_end(NXD_MQTT_CLIENT *client_ptr, ULONG wait_option);

/**
 * @brief 处理接收到的发布数据包。
 * 
 * @param packet_ptr 指向接收到的 NX_PACKET 数据包的指针。
 * @param topic_offset_ptr 存储主题偏移量的指针，函数返回时会设置该值。
 * @param topic_length_ptr 存储主题长度的指针，函数返回时会设置该值。
 * @param message_offset_ptr 存储消息偏移量的指针，函数返回时会设置该值。
 * @param message_length_ptr 存储消息长度的指针，函数返回时会设置该值。
 * 
 * @return 返回处理操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT _nxd_mqtt_process_publish_packet(NX_PACKET *packet_ptr, ULONG *topic_offset_ptr, USHORT *topic_length_ptr,
                                      ULONG *message_offset_ptr, ULONG *message_length_ptr);

/**
 * @brief 创建与 MQTT 服务器的连接，并进行身份验证。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param server_ip 指向服务器 IP 地址的指针。
 * @param server_port 服务器端口号。
 * @param keepalive 保持活动的时间间隔。
 * @param clean_session 清除会话的标志，1 表示清除，0 表示不清除。
 * @param timeout 超时设置，指定操作的超时时间。
 * 
 * @return 返回连接操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT _nxde_mqtt_client_connect(NXD_MQTT_CLIENT *client_ptr, NXD_ADDRESS *server_ip, UINT server_port,
                               UINT keepalive, UINT clean_session, ULONG timeout);

/**
 * @brief 创建 MQTT 客户端实例并初始化。
 * 
 * @param client_ptr 指向要创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param client_name 客户端名称字符串指针。
 * @param client_id 客户端 ID 字符串指针。
 * @param client_id_length 客户端 ID 的长度。
 * @param ip_ptr 指向关联的 NX_IP 结构体的指针。
 * @param pool_ptr 指向用于 MQTT 客户端的 NX_PACKET_POOL 的指针。
 * @param stack_ptr 指向客户端线程栈的指针。
 * @param stack_size 客户端线程栈的大小。
 * @param mqtt_thread_priority MQTT 客户端线程的优先级。
 * @param memory_ptr 指向用于客户端的内存的指针。
 * @param memory_size 客户端所需内存的大小。
 * 
 * @return 返回创建操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT _nxde_mqtt_client_create(NXD_MQTT_CLIENT *client_ptr, CHAR *client_name, CHAR *client_id, UINT client_id_length,
                              NX_IP *ip_ptr, NX_PACKET_POOL *pool_ptr,
                              VOID *stack_ptr, ULONG stack_size, UINT mqtt_thread_priority,
                              VOID *memory_ptr, ULONG memory_size);
/**
 * @brief 删除 MQTT 客户端实例，释放相关资源。
 * 
 * @param client_ptr 指向要删除的 NXD_MQTT_CLIENT 结构体的指针。
 * 
 * @return 返回删除操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT _nxde_mqtt_client_delete(NXD_MQTT_CLIENT *client_ptr);

/**
 * @brief 设置 MQTT 客户端的断开连接通知回调函数。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param disconnect_notify 断开连接时调用的回调函数指针。
 * 
 * @return 返回设置操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT _nxde_mqtt_client_disconnect_notify_set(NXD_MQTT_CLIENT *client_ptr, VOID (*disconnect_notify)(NXD_MQTT_CLIENT *));

/**
 * @brief 断开与 MQTT 服务器的连接。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * 
 * @return 返回断开连接操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT _nxde_mqtt_client_disconnect(NXD_MQTT_CLIENT *client_ptr);

/**
 * @brief 设置 MQTT 客户端的用户名和密码，用于身份验证。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param username 用户名字符串指针。
 * @param username_length 用户名的长度。
 * @param password 密码字符串指针。
 * @param password_length 密码的长度。
 * 
 * @return 返回设置操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT _nxde_mqtt_client_login_set(NXD_MQTT_CLIENT *client_ptr,
                                 CHAR *username, UINT username_length, CHAR *password, UINT password_length);

/**
 * @brief 从 MQTT 客户端接收的消息中获取主题和消息内容。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param topic_buffer 存储主题的缓冲区指针。
 * @param topic_buffer_size 主题缓冲区的大小。
 * @param actual_topic_length 实际主题长度的指针，函数返回时会设置该值。
 * @param message_buffer 存储消息内容的缓冲区指针。
 * @param message_buffer_size 消息缓冲区的大小。
 * @param actual_message_length 实际消息长度的指针，函数返回时会设置该值。
 * 
 * @return 返回获取消息操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT _nxde_mqtt_client_message_get(NXD_MQTT_CLIENT *client_ptr, UCHAR *topic_buffer, UINT topic_buffer_size, UINT *actual_topic_length,
                                   UCHAR *message_buffer, UINT message_buffer_size, UINT *actual_message_length);

/**
 * @brief 向 MQTT 服务器发布消息。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param topic_name 主题名称字符串指针。
 * @param topic_name_length 主题名称的长度。
 * @param message 要发布的消息字符串指针。
 * @param message_length 消息的长度。
 * @param retain 保留标志，1 表示消息应保留，0 表示不保留。
 * @param QoS 消息的服务质量级别，0、1 或 2。
 * @param timeout 超时设置，指定操作的超时时间。
 * 
 * @return 返回发布操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT _nxde_mqtt_client_publish(NXD_MQTT_CLIENT *client_ptr, CHAR *topic_name, UINT topic_name_length,
                               CHAR *message, UINT message_length, UINT retain, UINT QoS, ULONG timeout);

/**
 * @brief 设置 MQTT 客户端的接收通知回调函数。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param receive_notify 接收消息时调用的回调函数指针。
 * 
 * @return 返回设置操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT _nxde_mqtt_client_receive_notify_set(NXD_MQTT_CLIENT *client_ptr,
                                          VOID (*receive_notify)(NXD_MQTT_CLIENT *client_ptr, UINT message_count));

/**
 * @brief 设置 MQTT 客户端的内存释放回调函数。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param release_callback 内存释放函数的指针。
 * 
 * @return 返回设置操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT _nxde_mqtt_client_release_callback_set(NXD_MQTT_CLIENT *client_ptr, VOID (*release_callback)(CHAR *, UINT));

/**
 * @brief 订阅指定主题的消息。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param topic_name 要订阅的主题名称字符串指针。
 * @param topic_name_length 主题名称的长度。
 * @param QoS 消息的服务质量级别，0、1 或 2。
 * 
 * @return 返回订阅操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT _nxde_mqtt_client_subscribe(NXD_MQTT_CLIENT *client_ptr, CHAR *topic_name, UINT topic_name_length, UINT QoS);

/**
 * @brief 取消订阅指定主题的消息。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param topic_name 要取消订阅的主题名称字符串指针。
 * @param topic_name_length 主题名称的长度。
 * 
 * @return 返回取消订阅操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT _nxde_mqtt_client_unsubscribe(NXD_MQTT_CLIENT *client_ptr, CHAR *topic_name, UINT topic_name_length);

/**
 * @brief 设置客户端的遗嘱消息。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param will_topic 遗嘱主题字符串指针。
 * @param will_topic_length 遗嘱主题的长度。
 * @param will_message 遗嘱消息字符串指针。
 * @param will_message_length 遗嘱消息的长度。
 * @param will_retain_flag 遗嘱消息保留标志，1 表示保留，0 表示不保留。
 * @param will_QoS 遗嘱消息的服务质量级别，0、1 或 2。
 * 
 * @return 返回设置遗嘱消息操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT _nxde_mqtt_client_will_message_set(NXD_MQTT_CLIENT *client_ptr,
                                        const UCHAR *will_topic, UINT will_topic_length, const UCHAR *will_message,
                                        UINT will_message_length, UINT will_retain_flag, UINT will_QoS);

#ifdef NX_SECURE_ENABLE
/**
 * @brief 建立与 MQTT 服务器的安全连接（TLS）。
 * 
 * 此函数用于通过安全套接字（TLS）与指定的 MQTT 服务器建立连接。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param server_ip 指向 MQTT 服务器的 IP 地址结构的指针。
 * @param server_port 服务器的端口号。
 * @param tls_setup 指向用于设置 TLS 连接的回调函数指针。
 *                   此回调函数应配置 TLS 会话及相关证书。
 * @param keepalive 客户端与服务器之间的心跳时间，以秒为单位。
 * @param clean_session 指定是否使用干净的会话，1 表示使用，0 表示不使用。
 * @param wait_option 等待选项，用于指定操作的等待时间。
 * 
 * @return 返回安全连接操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT _nxd_mqtt_client_secure_connect(NXD_MQTT_CLIENT *client_ptr, NXD_ADDRESS *server_ip, UINT server_port,
                                     UINT (*tls_setup)(NXD_MQTT_CLIENT *client_ptr, NX_SECURE_TLS_SESSION *,
                                                       NX_SECURE_X509_CERT *, NX_SECURE_X509_CERT *),
                                     UINT keepalive, UINT clean_session, ULONG wait_option);

/**
 * @brief 建立与 MQTT 服务器的安全连接（TLS），带有超时选项。
 * 
 * 此函数用于通过安全套接字（TLS）与指定的 MQTT 服务器建立连接，
 * 支持在指定的超时时间内完成连接。
 * 
 * @param client_ptr 指向已创建的 NXD_MQTT_CLIENT 结构体的指针。
 * @param server_ip 指向 MQTT 服务器的 IP 地址结构的指针。
 * @param server_port 服务器的端口号。
 * @param tls_setup 指向用于设置 TLS 连接的回调函数指针。
 *                   此回调函数应配置 TLS 会话及相关证书。
 * @param keepalive 客户端与服务器之间的心跳时间，以秒为单位。
 * @param clean_session 指定是否使用干净的会话，1 表示使用，0 表示不使用。
 * @param timeout 指定连接操作的超时时间，以秒为单位。
 * 
 * @return 返回安全连接操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT _nxde_mqtt_client_secure_connect(NXD_MQTT_CLIENT *client_ptr, NXD_ADDRESS *server_ip, UINT server_port,
                                      UINT (*tls_setup)(NXD_MQTT_CLIENT *client_ptr, NX_SECURE_TLS_SESSION *,
                                                        NX_SECURE_X509_CERT *, NX_SECURE_X509_CERT *),
                                      UINT keepalive, UINT clean_session, ULONG timeout);
#endif /* NX_SECURE_ENABLE */

#endif /* ifndef NXD_MQTT_CLIENT_SOURCE_CODE */

#ifdef NXD_MQTT_CLOUD_ENABLE
/* MQTT create function based on cloud helper.  */
/**
 * @brief 创建一个 MQTT 云客户端实例。
 * 
 * 此函数用于创建一个 MQTT 客户端并将其关联到指定的云平台。
 * 
 * @param client_ptr 指向要创建的 NXD_MQTT_CLIENT 结构体的指针。该结构体将被初始化为云客户端。
 * @param client_name 客户端的名称，用于标识该客户端。
 * @param client_id 客户端的唯一标识符（ID），应在整个 MQTT 代理中唯一。
 * @param client_id_length 客户端 ID 的长度，以字节为单位。
 * @param ip_ptr 指向与此 MQTT 客户端相关的 IP 结构的指针。
 * @param pool_ptr 指向用于分配网络数据包的包池结构的指针。
 * @param cloud_ptr 指向与此 MQTT 客户端相关的云平台结构的指针。
 * 
 * @return 返回创建操作的状态代码，成功时返回 NXD_MQTT_SUCCESS，失败时返回相应的错误代码。
 */
UINT _nxd_mqtt_client_cloud_create(NXD_MQTT_CLIENT *client_ptr, CHAR *client_name,
                                   CHAR *client_id, UINT client_id_length,
                                   NX_IP *ip_ptr, NX_PACKET_POOL *pool_ptr, NX_CLOUD *cloud_ptr);
#endif /* NXD_MQTT_CLOUD_ENABLE */

/* Determine if a C++ compiler is being used.  If so, complete the standard
   C conditional started above.  */
#ifdef   __cplusplus
}
#endif


#endif /* NXD_MQTT_CLIENT_H  */

