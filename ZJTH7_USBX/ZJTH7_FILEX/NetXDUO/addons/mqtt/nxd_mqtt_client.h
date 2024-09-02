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
/** NetX ���                                                            */
/**                                                                       */
/**   MQTT (��Ϣ����ң�⴫��Э��)                                         */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/


/**************************************************************************/
/*                                                                        */
/*  Ӧ�ó���ӿڶ���                                      ������          */
/*                                                                        */
/*    nxd_mqtt_client.h                                   ����ֲ�� C ����  */
/*                                                           6.1.2        */
/*  ����                                                                  */
/*                                                                        */
/*    Yuxin Zhou, Microsoft Corporation                                   */
/*                                                                        */
/*  ����                                                                  */
/*                                                                        */
/*    ���ļ������� NetX MQTT �ͻ�����������������������ͺ��ⲿ���á�����  */
/*    �Ѿ������� nx_api.h �� nx_port.h �ļ���                            */
/*                                                                        */
/*  ������ʷ                                                              */
/*                                                                        */
/*    ����              ����                      ����                    */
/*                                                                        */
/*  05-19-2020     Yuxin Zhou               ��ʼ�汾 6.0                   */
/*  09-30-2020     Yuxin Zhou               �޸���ע�ͣ�������� ACK ����  */
/*                                            ֪ͨ���汾������ 6.1         */
/*  11-09-2020     Yuxin Zhou               �޸���ע�ͣ�����������ݰ� ID  */
/*                                            �������汾������ 6.1.2       */
/*                                                                        */
/**************************************************************************/

#ifndef _NXD_MQTT_CLIENT_H_
#define _NXD_MQTT_CLIENT_H_

/* �ж��Ƿ�ʹ���� C++ ������������ǣ�ȷ��ʹ�ñ�׼ C ���� API ��Ϣ�� */

#ifdef   __cplusplus

/* �ǵģ�C++ ���������ڡ�ʹ�ñ�׼ C�� */
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
#error "�ù��� NXD_MQTT_REQUIRE_TLS ��Ҫ���� NX_SECURE_ENABLE��"
#endif /* NX_SECURE_ENABLE */
#endif /* NXD_MQTT_REQUIRE_TLS */

/* �������ڲ�ʹ�õ� memcpy��memset �� memcmp ������ */
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

/* ����Ĭ�ϵ� MQTT �� TLS���ǰ�ȫ���˿ں� */
#define NXD_MQTT_PORT                                                  1883

/* ����Ĭ�ϵ� TCP �׽��ִ��ڴ�С�� */
#ifndef NXD_MQTT_CLIENT_SOCKET_WINDOW_SIZE
#define NXD_MQTT_CLIENT_SOCKET_WINDOW_SIZE                             8192
#endif /* NXD_MQTT_CLIENT_SOCKET_WINDOW_SIZE */

/* ����Ĭ�ϵ� MQTT �߳�ʱ��Ƭ�� */
#ifndef NXD_MQTT_CLIENT_THREAD_TIME_SLICE
#define NXD_MQTT_CLIENT_THREAD_TIME_SLICE                              2
#endif

/* ���ñ��ֻ��ʱ����Ĭ�ϼ�ʱ���ʣ���λΪ ThreadX ��ʱ���δ�Ĭ��ֵΪһ�롣 */
#ifndef NXD_MQTT_KEEPALIVE_TIMER_RATE
#define NXD_MQTT_KEEPALIVE_TIMER_RATE                                  (NX_IP_PERIODIC_RATE)
#endif

/* ���� PING ��Ӧ��Ĭ�ϳ�ʱʱ�䡣*/
/* �ڷ��� MQTT Ping ���������ͻ����ڴ�ʱ����δ�յ� Ping ��Ӧ����ͻ��˽��Ͽ�������������ӡ�Ĭ��ֵΪһ�롣 */
#ifndef NXD_MQTT_PING_TIMEOUT_DELAY
#define NXD_MQTT_PING_TIMEOUT_DELAY                                    (NX_IP_PERIODIC_RATE)
#endif

/* �����á��˷��Ŷ������ڼ����ԡ� */
#ifndef NXD_MQTT_MAX_TOPIC_NAME_LENGTH
#define NXD_MQTT_MAX_TOPIC_NAME_LENGTH                                 12
#endif

/* �����á��˷��Ŷ������ڼ����ԡ� */
#ifndef NXD_MQTT_MAX_MESSAGE_LENGTH
#define NXD_MQTT_MAX_MESSAGE_LENGTH                                    32
#endif

#ifndef NXD_MQTT_INITIAL_PACKET_ID_VALUE
#define NXD_MQTT_INITIAL_PACKET_ID_VALUE                               1
#endif

/* Ϊ�׽��ֲ��������͡����ա��Ͽ����ӣ����ó�ʱʱ�䡣 */
#ifndef NXD_MQTT_SOCKET_TIMEOUT
#define NXD_MQTT_SOCKET_TIMEOUT                                         NX_WAIT_FOREVER
#endif

/* ����Ĭ�ϵ� MQTT TLS����ȫ���˿ں� */
#define NXD_MQTT_TLS_PORT                                              8883


// ���� MQTT Э��汾
#define MQTT_PROTOCOL_LEVEL                                            4

/* ���� CONNECT ���ݰ���ʹ�õ�λ�ֶκͳ���ֵ�� */
// �û�����־����ʾ�� CONNECT ���ݰ��а����û���
#define MQTT_CONNECT_FLAGS_USERNAME                                    (1 << 7)
// �����־����ʾ�� CONNECT ���ݰ��а�������
#define MQTT_CONNECT_FLAGS_PASSWORD                                    (1 << 6)
// ������־����ʾ�������һ����Ϣ
#define MQTT_CONNECT_FLAGS_WILL_RETAIN                                 (1 << 5)
// ��Ҫ��������Ϣ�� QoS �ȼ� 0
#define MQTT_CONNECT_FLAGS_WILL_QOS_0                                  0
// ��Ҫ��������Ϣ�� QoS �ȼ� 1
#define MQTT_CONNECT_FLAGS_WILL_QOS_1                                  (1 << 3)
// ��Ҫ��������Ϣ�� QoS �ȼ� 2
#define MQTT_CONNECT_FLAGS_WILL_QOS_2                                  (2 << 3)
// ��Ҫ�����ı�־����ʾ�Ƿ����������Ϣ
#define MQTT_CONNECT_FLAGS_WILL_FLAG                                   (1 << 2)
// ����Ự��־����ʾ�Ƿ����֮ǰ�ĻỰ
#define MQTT_CONNECT_FLAGS_CLEAN_SESSION                               (1 << 1)
// ��Ҫ������ QoS �ֶΣ����ڱ�ʾ��Ϣ�� QoS �ȼ�
#define MQTT_CONNECT_FLAGS_WILL_QOS_FIELD                              (3 << 3)

/* ���� CONNACK ���ݰ���ʹ�õ�λ�ֶκͳ���ֵ�� */
// �����ṩ��־
#define MQTT_CONNACK_CONNECT_FLAGS_SP                                  (1)
// ���ӷ����룺�ѽ���
#define MQTT_CONNACK_CONNECT_RETURN_CODE_ACCEPTED                      (0)
// ���ӷ����룺�����ܵ�Э��汾
#define MQTT_CONNACK_CONNECT_RETURN_CODE_UNACCEPTABLE_PROTOCOL_VERSION (1)
// ���ӷ����룺��ʶ�����ܾ�
#define MQTT_CONNACK_CONNECT_RETURN_CODE_IDENTIFIER_REJECTED           (2)
// ���ӷ����룺������������
#define MQTT_CONNACK_CONNECT_RETURN_CODE_SERVER_UNAVAILABLE            (3)
// ���ӷ����룺������û���������
#define MQTT_CONNACK_CONNECT_RETURN_CODE_BAD_USERNAME_PASSWORD         (4)
// ���ӷ����룺δ��Ȩ
#define MQTT_CONNACK_CONNECT_RETURN_CODE_NOT_AUTHORIZED                (5)

/* ���� PUBLISH ���ݰ���ʹ�õ�λ�ֶκͳ���ֵ�� */
// �ط���־����ʾ��Ϣ�Ƿ�Ϊ�ظ�����
#define MQTT_PUBLISH_DUP_FLAG                                          (1 << 3)
// ������ QoS �ȼ� 0
#define MQTT_PUBLISH_QOS_LEVEL_0                                       (0)
// ������ QoS �ȼ� 1
#define MQTT_PUBLISH_QOS_LEVEL_1                                       (1 << 1)
// ������ QoS �ȼ� 2
#define MQTT_PUBLISH_QOS_LEVEL_2                                       (2 << 1)
// QoS �ȼ��ֶΣ����ڱ�ʾ��Ϣ�� QoS �ȼ�
#define MQTT_PUBLISH_QOS_LEVEL_FIELD                                   (3 << 1)
// ������־����ʾ��ϢӦ������
#define MQTT_PUBLISH_RETAIN                                            (1)

// ���Ʊ��������ֶ�����
#define MQTT_CONTROL_PACKET_TYPE_FIELD                                 0xF0

// ����̶�ͷ����С
#define MQTT_FIXED_HEADER_SIZE                                         2

// ���Ʊ������Ͷ���
#define MQTT_CONTROL_PACKET_TYPE_CONNECT                               (1)  // CONNECT ����
#define MQTT_CONTROL_PACKET_TYPE_CONNACK                               (2)  // CONNACK ����
#define MQTT_CONTROL_PACKET_TYPE_PUBLISH                               (3)  // PUBLISH ����
#define MQTT_CONTROL_PACKET_TYPE_PUBACK                                (4)  // PUBACK ����
#define MQTT_CONTROL_PACKET_TYPE_PUBREC                                (5)  // PUBREC ����
#define MQTT_CONTROL_PACKET_TYPE_PUBREL                                (6)  // PUBREL ����
#define MQTT_CONTROL_PACKET_TYPE_PUBCOMP                               (7)  // PUBCOMP ����
#define MQTT_CONTROL_PACKET_TYPE_SUBSCRIBE                             (8)  // SUBSCRIBE ����
#define MQTT_CONTROL_PACKET_TYPE_SUBACK                                (9)  // SUBACK ����
#define MQTT_CONTROL_PACKET_TYPE_UNSUBSCRIBE                           (10) // UNSUBSCRIBE ����
#define MQTT_CONTROL_PACKET_TYPE_UNSUBACK                              (11) // UNSUBACK ����
#define MQTT_CONTROL_PACKET_TYPE_PINGREQ                               (12) // PINGREQ ����
#define MQTT_CONTROL_PACKET_TYPE_PINGRESP                              (13) // PINGRESP ����
#define MQTT_CONTROL_PACKET_TYPE_DISCONNECT                            (14) // DISCONNECT ����

/* �ж��Ƿ�ʹ���� C++ ������������ǣ�������������ı�׼ C �������롣 */


/* MQTT CONNACK ���ݰ��ṹ�嶨�� */
/* ���ڱ�ʾ����˶Կͻ��������������Ӧ���ݰ� */
typedef struct MQTT_PACKET_CONNACK_STRUCT
{
    UCHAR mqtt_connack_packet_header;             /* CONNACK ���ݰ��Ĺ̶�ͷ�� */
    UCHAR mqtt_connack_packet_remaining_length;   /* ʣ�೤���ֶΣ���ʾCONNACK���ݰ����ֽ������������̶�ͷ�� */
    UCHAR mqtt_connack_packet_ack_flags;          /* ȷ�ϱ�־�ֶΣ�����ָʾ���ӵĻỰ״̬ */
    UCHAR mqtt_connack_packet_return_code;        /* �����룬ָʾ��������Ľ�� */
} MQTT_PACKET_CONNACK;

/* MQTT PUBLISH ���ݰ��ṹ�嶨�� */
/* ���ڱ�ʾ�ͻ��˻����˷�������Ϣ���ݰ� */
typedef struct MQTT_PACKET_PUBLISH_STRUCT
{
    UCHAR mqtt_publish_packet_header;             /* PUBLISH ���ݰ��Ĺ̶�ͷ�� */
    UCHAR mqtt_publish_packet_remaining_length;   /* ʣ�೤���ֶΣ���ʾ PUBLISH ���ݰ����ֽ������������̶�ͷ�� */
} MQTT_PACKET_PUBLISH;

/* MQTT PUBLISH ��Ӧ���ݰ��ṹ�嶨�� */
/* ���ڱ�ʾ��Է����������Ӧ���ݰ����� PUBACK��PUBREC��PUBREL��PUBCOMP */
typedef struct MQTT_PACKET_PUBLISH_RESPONSE_STRUCT
{
    UCHAR mqtt_publish_response_packet_header;                /* PUBLISH ��Ӧ���ݰ��Ĺ̶�ͷ�� */
    UCHAR mqtt_publish_response_packet_remaining_length;      /* ʣ�೤���ֶΣ���ʾ PUBLISH ��Ӧ���ݰ����ֽ������������̶�ͷ�� */
    UCHAR mqtt_publish_response_packet_packet_identifier_msb; /* ���ݰ���ʶ���ĸ��ֽڣ�����Ψһ��ʶ���ݰ� */
    UCHAR mqtt_publish_response_packet_packet_identifier_lsb; /* ���ݰ���ʶ���ĵ��ֽ� */
} MQTT_PACKET_PUBLISH_RESPONSE;

/* MQTT SUBSCRIBE ���ݰ��ṹ�嶨�� */
/* ���ڱ�ʾ�ͻ��������˷��͵Ķ����������ݰ� */
typedef struct MQTT_PACKET_SUBSCRIBE_STRUCT
{
    UCHAR mqtt_subscribe_packet_header;                     /* SUBSCRIBE ���ݰ��Ĺ̶�ͷ�� */
    UCHAR mqtt_subscribe_packet_remaining_length;           /* ʣ�೤���ֶΣ���ʾ SUBSCRIBE ���ݰ����ֽ������������̶�ͷ�� */
    UCHAR mqtt_subscribe_packet_packet_identifier_msb;      /* ���ݰ���ʶ���ĸ��ֽڣ�����Ψһ��ʶ���ݰ� */
    UCHAR mqtt_subscribe_packet_packet_identifier_lsb;      /* ���ݰ���ʶ���ĵ��ֽ� */
} MQTT_PACKET_SUBSCRIBE;

/* MQTT PING �������ݰ��ṹ�嶨�� */
/* ���ڱ�ʾ�ͻ��������˷��͵������������ݰ� */
typedef struct MQTT_PACKET_PING_STRUCT
{
    UCHAR mqtt_ping_packet_header;                /* PINGREQ ���ݰ��Ĺ̶�ͷ�� */
    UCHAR mqtt_ping_packet_remaining_length;      /* ʣ�೤���ֶΣ���ʾ PINGREQ ���ݰ����ֽ������������̶�ͷ�� */
} MQTT_PACKET_PING;

/* MQTT DISCONNECT ���ݰ��ṹ�嶨�� */
/* ���ڱ�ʾ�ͻ��˻����˷��͵ĶϿ������������ݰ� */
typedef struct MQTT_PACKET_DISCONNECT_STRUCT
{
    UCHAR mqtt_disconnect_packet_header;          /* DISCONNECT ���ݰ��Ĺ̶�ͷ�� */
    UCHAR mqtt_disconnect_packet_remaining_length;/* ʣ�೤���ֶΣ���ʾ DISCONNECT ���ݰ����ֽ������������̶�ͷ�� */
} MQTT_PACKET_DISCONNECT;


/* ���� NetX MQTT �ͻ��˱�ʶ�� */
#define NXD_MQTT_CLIENT_ID                   0x4D515454

/* ����Ĭ�ϵ� MQTT �� TLS���ǰ�ȫ���˿ں� */
#define NXD_MQTT_CLIENT_NONTLS_PORT          1883

/* ����Ĭ�ϵ� MQTT TLS����ȫ���˿ں� */
#define NXD_MQTT_CLIENT_TLS_PORT             8883

/* ���� MQTT �ͻ���״̬ */
#define NXD_MQTT_CLIENT_STATE_INITIALIZE     0  /* ��ʼ��״̬ */
#define NXD_MQTT_CLIENT_STATE_IDLE           1  /* ����״̬ */
#define NXD_MQTT_CLIENT_STATE_CONNECTING     2  /* ��������״̬ */
#define NXD_MQTT_CLIENT_STATE_CONNECTED      3  /* ������״̬ */

/* ���� MQTT �����ķ���״̬�� */
#define NXD_MQTT_SUCCESS                     0x0     /* �����ɹ� */
#define NXD_MQTT_ALREADY_CONNECTED           0x10001 /* �Ѿ����� */
#define NXD_MQTT_NOT_CONNECTED               0x10002 /* δ���� */
#define NXD_MQTT_MUTEX_FAILURE               0x10003 /* ����������ʧ�� */
#define NXD_MQTT_INTERNAL_ERROR              0x10004 /* �ڲ����� */
#define NXD_MQTT_CONNECT_FAILURE             0x10005 /* ����ʧ�� */
#define NXD_MQTT_PACKET_POOL_FAILURE         0x10006 /* ���ݰ��ط���ʧ�� */
#define NXD_MQTT_COMMUNICATION_FAILURE       0x10007 /* ͨ��ʧ�� */
#define NXD_MQTT_SERVER_MESSAGE_FAILURE      0x10008 /* ��������Ϣ����ʧ�� */
#define NXD_MQTT_INVALID_PARAMETER           0x10009 /* ��Ч�Ĳ��� */
#define NXD_MQTT_NO_MESSAGE                  0x1000A /* û����Ϣ */
#define NXD_MQTT_PACKET_POOL_EMPTY           0x1000B /* ���ݰ���Ϊ�� */
#define NXD_MQTT_QOS2_NOT_SUPPORTED          0x1000C /* ��֧�� QoS 2 */
#define NXD_MQTT_INSUFFICIENT_BUFFER_SPACE   0x1000D /* �������ռ䲻�� */
#define NXD_MQTT_CLIENT_NOT_RUNNING          0x1000E /* �ͻ���δ���� */
#define NXD_MQTT_INVALID_PACKET              0x1000F /* ��Ч�����ݰ� */
#define NXD_MQTT_PARTIAL_PACKET              0x10010 /* ���ݰ������� */
#define NXD_MQTT_CONNECTING                  0x10011 /* ���������� */
#define NXD_MQTT_INVALID_STATE               0x10012 /* ��Ч��״̬ */

/* ���´������� CONNACK ��Ϣ�е����ӷ�������ƥ�� */
#define NXD_MQTT_ERROR_CONNECT_RETURN_CODE   0x10080 /* ���ӷ�������� */
#define NXD_MQTT_ERROR_UNACCEPTABLE_PROTOCOL 0x10081 /* ���ɽ��ܵ�Э��汾 */
#define NXD_MQTT_ERROR_IDENTIFYIER_REJECTED  0x10082 /* ��ʶ�����ܾ� */
#define NXD_MQTT_ERROR_SERVER_UNAVAILABLE    0x10083 /* ������������ */
#define NXD_MQTT_ERROR_BAD_USERNAME_PASSWORD 0x10084 /* �û������������ */
#define NXD_MQTT_ERROR_NOT_AUTHORIZED        0x10085 /* δ��Ȩ */


typedef struct NXD_MQTT_CLIENT_STRUCT
{
    CHAR *nxd_mqtt_client_name;                       /* MQTT �ͻ������ơ� */
    CHAR *nxd_mqtt_client_id;                         /* �ͻ��˵� MQTT ID�� */
    UINT nxd_mqtt_client_id_length;                   /* �ͻ��� ID �ĳ��ȡ� */
    CHAR *nxd_mqtt_client_username;                   /* �ͻ��˵��û����� */
    USHORT nxd_mqtt_client_username_length;           /* �û����ĳ��ȡ� */
    CHAR *nxd_mqtt_client_password;                   /* �ͻ��˵����롣 */
    USHORT nxd_mqtt_client_password_length;           /* ����ĳ��ȡ� */
    UCHAR nxd_mqtt_client_will_qos_retain;            /* �ͻ���������Ϣ�� QoS ����ͱ�����־�� */
    const UCHAR *nxd_mqtt_client_will_topic;          /* ������Ϣ�����⡣ */
    UINT nxd_mqtt_client_will_topic_length;           /* ������Ϣ����ĳ��ȡ� */
    const UCHAR *nxd_mqtt_client_will_message;        /* ������Ϣ�����ݡ� */
    UINT nxd_mqtt_client_will_message_length;         /* ������Ϣ���ݵĳ��ȡ� */
    NX_IP *nxd_mqtt_client_ip_ptr;                    /* ָ������� IP �ṹ��ָ�롣 */
    NX_PACKET_POOL *nxd_mqtt_client_packet_pool_ptr;  /* ָ��ͻ������ݰ��ص�ָ�롣 */
    TX_MUTEX *nxd_mqtt_client_mutex_ptr;              /* ָ��ͻ��˻�������ָ�롣 */
    TX_TIMER nxd_mqtt_timer;                          /* MQTT �ͻ��˶�ʱ���� */
    
#ifndef NXD_MQTT_CLOUD_ENABLE
    TX_MUTEX nxd_mqtt_protection;                     /* MQTT �ͻ��˱����������� */
    TX_THREAD nxd_mqtt_thread;                        /* MQTT �ͻ����̡߳� */
    TX_EVENT_FLAGS_GROUP nxd_mqtt_events;             /* MQTT �¼���־�顣 */
#else
    NX_CLOUD *nxd_mqtt_client_cloud_ptr;              /* ָ��������ƽṹ��ָ�롣 */
    NX_CLOUD nxd_mqtt_client_cloud;                   /* MQTT ��ʵ���� */
    NX_CLOUD_MODULE nxd_mqtt_client_cloud_module;     /* ���������߳������е� MQTT ģ�顣 */
#endif /* NXD_MQTT_CLOUD_ENABLE */

    UINT nxd_mqtt_ping_timeout;                       /* PING �����ĳ�ʱʱ�䡣 */
    UINT nxd_mqtt_ping_not_responded;                 /* ��־ָʾ PING �Ƿ�����Ӧ�� */
    UINT nxd_mqtt_ping_sent_time;                     /* ���� PING ��Ϣʱ�� TX ��ʱ���̶ȡ� */
    UINT nxd_mqtt_timeout;                            /* �´γ�ʱʱ�� TX ��ʱ���̶ȡ� */
    UINT nxd_mqtt_timer_value;                        /* MQTT �ͻ��������Զ�ʱ���Ŀ̶�ֵ�� */
    UINT nxd_mqtt_keepalive;                          /* ���ֻ��ֵ��ת��Ϊ TX �̶ȡ� */
    UINT nxd_mqtt_clean_session;                      /* ����Ự��־�� */
    UINT nxd_mqtt_client_state;                       /* ��¼�ͻ���״̬�� */
    NX_TCP_SOCKET nxd_mqtt_client_socket;             /* �ͻ��˵� TCP �׽��֡� */
    struct NXD_MQTT_CLIENT_STRUCT *nxd_mqtt_client_next; /* ָ����һ���ͻ��˽ṹ��ָ�롣 */
    UINT nxd_mqtt_client_packet_identifier;           /* �ͻ������ݰ���ʶ���� */
    NX_PACKET *nxd_mqtt_client_processing_packet;     /* ���ڴ�������ݰ��� */
    NX_PACKET *message_transmit_queue_head;           /* ��Ϣ���Ͷ��е�ͷָ�롣 */
    NX_PACKET *message_transmit_queue_tail;           /* ��Ϣ���Ͷ��е�βָ�롣 */
    NX_PACKET *message_receive_queue_head;            /* ��Ϣ���ն��е�ͷָ�롣 */
    NX_PACKET *message_receive_queue_tail;            /* ��Ϣ���ն��е�βָ�롣 */
    UINT message_receive_queue_depth;                 /* ��Ϣ���ն��е���ȡ� */
    VOID (*nxd_mqtt_client_receive_notify)(struct NXD_MQTT_CLIENT_STRUCT *client_ptr, UINT number_of_messages); /* ��Ϣ����֪ͨ�Ļص������� */
    VOID (*nxd_mqtt_connect_notify)(struct NXD_MQTT_CLIENT_STRUCT *client_ptr, UINT status, VOID *context);      /* ����״̬��֪ͨ�ص������� */
    VOID *nxd_mqtt_connect_context;                   /* ����״̬�ص���������ָ�롣 */
    VOID (*nxd_mqtt_disconnect_notify)(struct NXD_MQTT_CLIENT_STRUCT *client_ptr); /* �Ͽ�����״̬��֪ͨ�ص������� */
    UINT (*nxd_mqtt_packet_receive_notify)(struct NXD_MQTT_CLIENT_STRUCT *client_ptr, NX_PACKET *packet_ptr, VOID *context); /* ���ݰ�����֪ͨ�Ļص������� */
    VOID *nxd_mqtt_packet_receive_context;            /* ���ݰ����ջص���������ָ�롣 */
    VOID (*nxd_mqtt_ack_receive_notify)(struct NXD_MQTT_CLIENT_STRUCT *client_ptr, UINT type, USHORT packet_id, NX_PACKET *transmit_packet_ptr, VOID *context); /* ȷ����Ϣ����֪ͨ�Ļص������� */
    VOID *nxd_mqtt_ack_receive_context;               /* ȷ����Ϣ���ջص���������ָ�롣 */
    
#ifdef NX_SECURE_ENABLE
    UINT nxd_mqtt_client_use_tls;                     /* ָʾ�ͻ����Ƿ�ʹ�� TLS�� */
    UINT (*nxd_mqtt_tls_setup)(struct NXD_MQTT_CLIENT_STRUCT *, NX_SECURE_TLS_SESSION *, NX_SECURE_X509_CERT *, NX_SECURE_X509_CERT *); /* TLS ���õĻص������� */
    NX_SECURE_X509_CERT nxd_mqtt_tls_certificate;     /* �ͻ��� TLS ֤�顣 */
    NX_SECURE_X509_CERT nxd_mqtt_tls_trusted_certificate; /* �����ε� TLS ֤�顣 */
    NX_SECURE_TLS_SESSION nxd_mqtt_tls_session;       /* TLS �Ự�� */
    UINT nxd_mqtt_tls_in_progress;                    /* TLS ���ڽ����еı�־�� */
#endif
} NXD_MQTT_CLIENT;


#ifndef NXD_MQTT_CLIENT_SOURCE_CODE

/* Ӧ�ó�������ߴ���ʱ��ִ�� API ӳ�䡣 */

/* ȷ���Ƿ���Ҫ���д����顣�����Ҫ���� API ����ӳ�䵽�ʵ��Ĵ�����ǰ�ˡ�
   ���򣬽� API ����ӳ�䵽ʵ��ִ�й����ĺ��ĺ�����
   ע�⣺Ĭ�����ô����顣 */

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

/* ��������˴����飬API ����ֱ��ӳ�䵽���ĺ�����
   ���磺nxd_mqtt_client_create ӳ�䵽 _nxd_mqtt_client_create��
   ����ʵ��ִ�д��� MQTT �ͻ��˵ĺ��ĺ����� */

#else /* ���δ���ô����� */

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

/* ��������˴����飬API ����ӳ�䵽���д����鹦�ܵĺ�����
   ���磺nxd_mqtt_client_create ӳ�䵽 _nxde_mqtt_client_create��
   ���ڵ��ú��ĺ���֮ǰ���д����顣 */

#endif /* NX_DISABLE_ERROR_CHECKING */


/**
 * @brief ����һ�� MQTT �ͻ��ˡ�
 * 
 * @param client_ptr ָ��Ҫ������ NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param client_name �ͻ������Ƶ��ַ���ָ�롣
 * @param client_id �ͻ��� ID ���ַ���ָ�롣
 * @param client_id_length �ͻ��� ID �ĳ��ȡ�
 * @param ip_ptr ָ����ÿͻ��˹����� IP �ṹ���ָ�롣
 * @param pool_ptr ָ�����ڿͻ��˵İ��ص�ָ�롣
 * @param stack_ptr ָ������ MQTT �ͻ��˵��߳�ջ��ָ�롣
 * @param stack_size �߳�ջ�Ĵ�С��
 * @param mqtt_thread_priority MQTT �̵߳����ȼ���
 * @param memory_ptr ָ������ MQTT �ͻ��˵��ڴ��ָ�롣
 * @param memory_size ���� MQTT �ͻ��˵��ڴ��С��
 * 
 * @return ���ش���������״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT nxd_mqtt_client_create(NXD_MQTT_CLIENT *client_ptr, CHAR *client_name, CHAR *client_id, UINT client_id_length,
                            NX_IP *ip_ptr, NX_PACKET_POOL *pool_ptr, VOID *stack_ptr, ULONG stack_size, UINT mqtt_thread_priority,
                            VOID *memory_ptr, ULONG memory_size);

/**
 * @brief ���ӵ� MQTT ��������
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param server_ip ָ������� IP ��ַ��ָ�롣
 * @param server_port �������Ķ˿ںš�
 * @param keepalive �������ӵ�����ʱ�䣨�룩��
 * @param clean_session ����Ự��־�����Ϊ 1����������ʱ�����ǰ�ĻỰ���ݡ�
 * @param timeout ���ӳ�ʱʱ�䣨���룩��
 * 
 * @return �������Ӳ�����״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT nxd_mqtt_client_connect(NXD_MQTT_CLIENT *client_ptr, NXD_ADDRESS *server_ip, UINT server_port,
                             UINT keepalive, UINT clean_session, ULONG timeout);

/**
 * @brief ���� MQTT �ͻ��˵ĵ�¼��Ϣ���û��������룩��
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param username �û����ַ���ָ�롣
 * @param username_length �û����ĳ��ȡ�
 * @param password �����ַ���ָ�롣
 * @param password_length ����ĳ��ȡ�
 * 
 * @return �������ò�����״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT nxd_mqtt_client_login_set(NXD_MQTT_CLIENT *client_ptr,
                               CHAR *username, UINT username_length, CHAR *password, UINT password_length);

/**
 * @brief ���� MQTT �ͻ��˵�������Ϣ��
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param will_topic ������Ϣ�������ַ���ָ�롣
 * @param will_topic_length ������Ϣ����ĳ��ȡ�
 * @param will_message ������Ϣ�������ַ���ָ�롣
 * @param will_message_length ������Ϣ���ݵĳ��ȡ�
 * @param will_retain_flag ������Ϣ�ı�����־��
 * @param will_QoS ������Ϣ�� QoS �ȼ���
 * 
 * @return �������ò�����״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT nxd_mqtt_client_will_message_set(NXD_MQTT_CLIENT *client_ptr,
                                      const UCHAR *will_topic, UINT will_topic_length, UCHAR *will_message, UINT will_message_length,
                                      UINT will_retain_flag, UINT will_QoS);

#ifdef NX_SECURE_ENABLE
/**
 * @brief ��ȫ���ӵ� MQTT ��������ʹ�� TLS����
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param server_ip ָ������� IP ��ַ��ָ�롣
 * @param server_port �������Ķ˿ںš�
 * @param tls_setup ָ������ TLS ���õĻص�����ָ�롣
 * @param keepalive �������ӵ�����ʱ�䣨�룩��
 * @param clean_session ����Ự��־�����Ϊ 1����������ʱ�����ǰ�ĻỰ���ݡ�
 * @param timeout ���ӳ�ʱʱ�䣨���룩��
 * 
 * @return �������Ӳ�����״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT nxd_mqtt_client_secure_connect(NXD_MQTT_CLIENT *client_ptr, NXD_ADDRESS *server_ip, UINT server_port,
                                    UINT (*tls_setup)(NXD_MQTT_CLIENT *client_ptr, NX_SECURE_TLS_SESSION *, NX_SECURE_X509_CERT *, NX_SECURE_X509_CERT *),
                                    UINT keepalive, UINT clean_session, ULONG timeout);
#endif
									  
/**
 * @brief ������Ϣ��ָ�����⡣
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param topic_name Ҫ������Ϣ�����������ַ���ָ�롣
 * @param topic_name_length �������Ƶĳ��ȡ�
 * @param message Ҫ��������Ϣ�����ַ���ָ�롣
 * @param message_length ��Ϣ���ݵĳ��ȡ�
 * @param retain �Ƿ�����Ϣ�ı�־��1 ��ʾ������0 ��ʾ��������
 * @param QoS ��Ϣ�� QoS �ȼ���0��1 �� 2����
 * @param timeout ���������ĳ�ʱʱ�䣨���룩��
 * 
 * @return ���ط���������״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT nxd_mqtt_client_publish(NXD_MQTT_CLIENT *client_ptr, CHAR *topic_name, UINT topic_name_length, CHAR *message, UINT message_length,
                             UINT retain, UINT QoS, ULONG timeout);

/**
 * @brief ����ָ�����⡣
 * 
 * @param mqtt_client_pr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param topic_name Ҫ���ĵ����������ַ���ָ�롣
 * @param topic_name_length �������Ƶĳ��ȡ�
 * @param QoS ����ʱ�� QoS �ȼ���0��1 �� 2����
 * 
 * @return ���ض��Ĳ�����״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT nxd_mqtt_client_subscribe(NXD_MQTT_CLIENT *mqtt_client_pr, CHAR *topic_name, UINT topic_name_length, UINT QoS);

/**
 * @brief ȡ������ָ�����⡣
 * 
 * @param mqtt_client_pr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param topic_name Ҫȡ�����ĵ����������ַ���ָ�롣
 * @param topic_name_length �������Ƶĳ��ȡ�
 * 
 * @return ����ȡ�����Ĳ�����״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT nxd_mqtt_client_unsubscribe(NXD_MQTT_CLIENT *mqtt_client_pr, CHAR *topic_name, UINT topic_name_length);

/**
 * @brief ���ý���֪ͨ�Ļص������������յ���Ϣʱ����øú�����
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param receive_notify ����֪ͨ�Ļص�����ָ�룬�������� MQTT �ͻ���ָ��ͽ��յ�����Ϣ������
 * 
 * @return �������ò�����״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT nxd_mqtt_client_receive_notify_set(NXD_MQTT_CLIENT *client_ptr,
                                        VOID (*receive_notify)(NXD_MQTT_CLIENT *client_ptr, UINT number_of_messages));

/**
 * @brief ��ȡ���յ�����Ϣ��
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param topic_buffer ���ڴ���������ƵĻ�����ָ�롣
 * @param topic_buffer_size �������ƻ������Ĵ�С��
 * @param actual_topic_length ʵ���������Ƶĳ��ȣ����������
 * @param message_buffer ���ڴ����Ϣ���ݵĻ�����ָ�롣
 * @param message_buffer_size ��Ϣ���ݻ������Ĵ�С��
 * @param actual_message_length ʵ����Ϣ���ݵĳ��ȣ����������
 * 
 * @return ���ػ�ȡ������״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT nxd_mqtt_client_message_get(NXD_MQTT_CLIENT *client_ptr, UCHAR *topic_buffer, UINT topic_buffer_size, UINT *actual_topic_length,
                                 UCHAR *message_buffer, UINT message_buffer_size, UINT *actual_message_length);

/**
 * @brief �� MQTT �������Ͽ����ӡ�
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * 
 * @return ���ضϿ����Ӳ�����״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT nxd_mqtt_client_disconnect(NXD_MQTT_CLIENT *client_ptr);

/**
 * @brief ɾ�� MQTT �ͻ��ˣ��ͷ������Դ��
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * 
 * @return ����ɾ��������״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT nxd_mqtt_client_delete(NXD_MQTT_CLIENT *client_ptr);

/**
 * @brief ���öϿ�����֪ͨ�Ļص�����������������Ͽ�����ʱ����øú�����
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param disconnect_notify �Ͽ�����֪ͨ�Ļص�����ָ�롣
 * 
 * @return �������ò�����״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT nxd_mqtt_client_disconnect_notify_set(NXD_MQTT_CLIENT *client_ptr, VOID (*disconnect_notify)(NXD_MQTT_CLIENT *));

#else /* ifdef NXD_MQTT_CLIENT_SOURCE_CODE */

/**
 * @brief ������ MQTT �����������ӡ�
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param server_ip ָ������� IP ��ַ�� NXD_ADDRESS �ṹ��ָ�롣
 * @param server_port �������Ķ˿ںš�
 * @param keepalive �������ӵ�����ʱ�䣨�룩��
 * @param clean_session �Ƿ�����Ự��־��1 ��ʾ�����0 ��ʾ������
 * @param wait_option �ȴ�ѡ�ָ�������ĳ�ʱʱ�䡣
 * 
 * @return �������Ӳ�����״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT _nxd_mqtt_client_connect(NXD_MQTT_CLIENT *client_ptr, NXD_ADDRESS *server_ip, UINT server_port,
                              UINT keepalive, UINT clean_session, ULONG wait_option);

/**
 * @brief ����һ�� MQTT �ͻ���ʵ����
 * 
 * @param client_ptr ָ��Ҫ������ NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param client_name �ͻ��������ַ���ָ�롣
 * @param client_id �ͻ��� ID �ַ���ָ�롣
 * @param client_id_length �ͻ��� ID �ĳ��ȡ�
 * @param ip_ptr ָ������� NX_IP �ṹ���ָ�롣
 * @param pool_ptr ָ�����ڿͻ��˵� NX_PACKET_POOL �ṹ���ָ�롣
 * @param stack_ptr ָ���߳�ջ��ָ�롣
 * @param stack_size �߳�ջ�Ĵ�С��
 * @param mqtt_thread_priority MQTT �̵߳����ȼ���
 * @param memory_ptr ���ڷ���ͻ����ڴ��ָ�롣
 * @param memory_size Ҫ������ڴ��С��
 * 
 * @return ���ش���������״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT _nxd_mqtt_client_create(NXD_MQTT_CLIENT *client_ptr, CHAR *client_name,
                             CHAR *client_id, UINT client_id_length,
                             NX_IP *ip_ptr, NX_PACKET_POOL *pool_ptr,
                             VOID *stack_ptr, ULONG stack_size, UINT mqtt_thread_priority,
                             VOID *memory_ptr, ULONG memory_size);

/**
 * @brief ɾ�� MQTT �ͻ��ˣ��ͷ������Դ��
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * 
 * @return ����ɾ��������״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT _nxd_mqtt_client_delete(NXD_MQTT_CLIENT *client_ptr);

/**
 * @brief �� MQTT �������Ͽ����ӡ�
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * 
 * @return ���ضϿ����Ӳ�����״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT _nxd_mqtt_client_disconnect(NXD_MQTT_CLIENT *client_ptr);

/**
 * @brief ���öϿ�����֪ͨ�Ļص�����������������Ͽ�����ʱ����øú�����
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param disconnect_notify �Ͽ�����֪ͨ�Ļص�����ָ�롣
 * 
 * @return �������ò�����״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT _nxd_mqtt_client_disconnect_notify_set(NXD_MQTT_CLIENT *client_ptr, VOID (*disconnect_notify)(NXD_MQTT_CLIENT *));

/**
 * @brief ���ÿͻ��˵��û��������룬�������� MQTT ������ʱ�������֤��
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param username �û����ַ���ָ�롣
 * @param username_length �û����ĳ��ȡ�
 * @param password �����ַ���ָ�롣
 * @param password_length ����ĳ��ȡ�
 * 
 * @return �������ò�����״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT _nxd_mqtt_client_login_set(NXD_MQTT_CLIENT *client_ptr,
                                CHAR *username, UINT username_length, CHAR *password, UINT password_length);
/**
 * @brief ��ȡ���յ�����Ϣ�������⡣
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param topic_buffer ���ڴ洢����Ļ�������
 * @param topic_buffer_size ���⻺�����Ĵ�С��
 * @param actual_topic_length ʵ�����ⳤ�ȵ�ָ�룬��������ʱ�����ø�ֵ��
 * @param message_buffer ���ڴ洢��Ϣ�Ļ�������
 * @param message_buffer_size ��Ϣ�������Ĵ�С��
 * @param actual_message_length ʵ����Ϣ���ȵ�ָ�룬��������ʱ�����ø�ֵ��
 * 
 * @return ���ػ�ȡ��Ϣ������״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT _nxd_mqtt_client_message_get(NXD_MQTT_CLIENT *client_ptr, UCHAR *topic_buffer, UINT topic_buffer_size, UINT *actual_topic_length,
                                  UCHAR *message_buffer, UINT message_buffer_size, UINT *actual_message_length);

/**
 * @brief ���� MQTT �������ݰ���
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param packet_ptr ָ��Ҫ���͵� NX_PACKET ���ݰ���ָ�롣
 * @param packet_id ��Ϣ���ı�ʶ����
 * @param QoS ��Ϣ�ķ��������ȼ���
 * @param wait_option �ȴ�ѡ�ָ�������ĳ�ʱʱ�䡣
 * 
 * @return ���ط��Ͳ�����״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT _nxd_mqtt_client_publish_packet_send(NXD_MQTT_CLIENT *client_ptr, NX_PACKET *packet_ptr,
                                          USHORT packet_id, UINT QoS, ULONG wait_option);

/**
 * @brief ������Ϣ��ָ�����⡣
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param topic_name ������Ϣ�������ַ���ָ�롣
 * @param topic_name_length �������Ƶĳ��ȡ�
 * @param message Ҫ��������Ϣ�ַ���ָ�롣
 * @param message_length ��Ϣ�ĳ��ȡ�
 * @param retain �Ƿ�����Ϣ��־��1 ��ʾ������0 ��ʾ��������
 * @param QoS ��Ϣ�ķ��������ȼ���
 * @param timeout ��ʱ���ã�ָ�������ĳ�ʱʱ�䡣
 * 
 * @return ���ط���������״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT _nxd_mqtt_client_publish(NXD_MQTT_CLIENT *client_ptr, CHAR *topic_name, UINT topic_name_length,
                              CHAR *message, UINT message_length, UINT retain, UINT QoS, ULONG timeout);

/**
 * @brief ���ý�����Ϣ��֪ͨ�ص������������յ���Ϣʱ����øú�����
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param receive_notify ������Ϣ֪ͨ�Ļص�����ָ�롣
 * 
 * @return �������ò�����״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT _nxd_mqtt_client_receive_notify_set(NXD_MQTT_CLIENT *client_ptr,
                                         VOID (*receive_notify)(NXD_MQTT_CLIENT *client_ptr, UINT message_count));

/**
 * @brief �����ڴ��ͷŻص���������������Ϣ���պ��ͷ��ڴ档
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param memory_release_function �ڴ��ͷź�����ָ�롣
 * 
 * @return �������ò�����״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT _nxd_mqtt_client_release_callback_set(NXD_MQTT_CLIENT *client_ptr, VOID (*memory_release_function)(CHAR *, UINT));

/**
 * @brief ���Ļ�ȡ���������⡣
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param op �������ͣ����Ļ�ȡ�����ĵı�ʶ��
 * @param topic_name ���������ַ���ָ�롣
 * @param topic_name_length �������Ƶĳ��ȡ�
 * @param packet_id_ptr ��Ϣ����ʶ����ָ�롣
 * @param QoS ��Ϣ�ķ��������ȼ���
 * 
 * @return ���ز�����״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT _nxd_mqtt_client_sub_unsub(NXD_MQTT_CLIENT *client_ptr, UINT op,
                                CHAR *topic_name, UINT topic_name_length, USHORT *packet_id_ptr, UINT QoS);

/**
 * @brief ����ָ�����⡣
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param topic_name ���������ַ���ָ�롣
 * @param topic_name_length �������Ƶĳ��ȡ�
 * @param QoS ��Ϣ�ķ��������ȼ���
 * 
 * @return ���ض��Ĳ�����״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT _nxd_mqtt_client_subscribe(NXD_MQTT_CLIENT *client_ptr, CHAR *topic_name, UINT topic_name_length, UINT QoS);

/**
 * @brief ȡ������ָ�����⡣
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param topic_name ���������ַ���ָ�롣
 * @param topic_name_length �������Ƶĳ��ȡ�
 * 
 * @return ����ȡ�����Ĳ�����״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT _nxd_mqtt_client_unsubscribe(NXD_MQTT_CLIENT *client_ptr, CHAR *topic_name, UINT topic_name_length);

/**
 * @brief ����������Ϣ�������ڿͻ�������Ͽ�ʱ�������������
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param will_topic ������Ϣ�������ַ���ָ�롣
 * @param will_topic_length ��������ĳ��ȡ�
 * @param will_message ������Ϣ�ַ���ָ�롣
 * @param will_message_length ������Ϣ�ĳ��ȡ�
 * @param will_retain_flag �Ƿ���������Ϣ��־��1 ��ʾ������0 ��ʾ��������
 * @param will_QoS ������Ϣ�ķ��������ȼ���
 * 
 * @return �������ò�����״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT _nxd_mqtt_client_will_message_set(NXD_MQTT_CLIENT *client_ptr,
                                       const UCHAR *will_topic, UINT will_topic_length, const UCHAR *will_message,
                                       UINT will_message_length, UINT will_retain_flag, UINT will_QoS);
/**
 * @brief �ӽ��յ������ݰ��ж�ȡʣ�೤�ȡ�
 * 
 * @param packet_ptr ָ����յ� NX_PACKET ���ݰ���ָ�롣
 * @param remaining_length �洢ʣ�೤�ȵ�ָ�룬��������ʱ�����ø�ֵ��
 * @param offset_ptr �洢��ǰ��ȡƫ������ָ�룬��������ʱ�����ø�ֵ��
 * 
 * @return ���ض�ȡ������״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT _nxd_mqtt_read_remaining_length(NX_PACKET *packet_ptr, UINT *remaining_length, ULONG *offset_ptr);

/**
 * @brief ���� MQTT ���ݰ��Ĺ̶�ͷ����
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param packet_ptr ָ��Ҫ���õ� NX_PACKET ���ݰ���ָ�롣
 * @param control_header ����ͷ���ֶΣ�ָʾ��Ϣ���ͺͱ�־��
 * @param length ���ݰ����ܳ��ȡ�
 * @param wait_option �ȴ�ѡ�ָ�������ĳ�ʱʱ�䡣
 * 
 * @return �������ò�����״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT _nxd_mqtt_client_set_fixed_header(NXD_MQTT_CLIENT *client_ptr, NX_PACKET *packet_ptr, UCHAR control_header, UINT length, UINT wait_option);

/**
 * @brief �� MQTT ���ݰ��и�����Ϣ��
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param packet_ptr ָ��Ҫ������Ϣ�� NX_PACKET ���ݰ���ָ�롣
 * @param message Ҫ���ӵ���Ϣ�ַ���ָ�롣
 * @param length ��Ϣ�ĳ��ȡ�
 * @param wait_option �ȴ�ѡ�ָ�������ĳ�ʱʱ�䡣
 * 
 * @return ���ظ�����Ϣ������״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT _nxd_mqtt_client_append_message(NXD_MQTT_CLIENT *client_ptr, NX_PACKET *packet_ptr, CHAR *message, UINT length, ULONG wait_option);

/**
 * @brief ������ MQTT �����������ӡ�
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param wait_option �ȴ�ѡ�ָ�������ĳ�ʱʱ�䡣
 */
VOID _nxd_mqtt_client_connection_end(NXD_MQTT_CLIENT *client_ptr, ULONG wait_option);

/**
 * @brief ������յ��ķ������ݰ���
 * 
 * @param packet_ptr ָ����յ��� NX_PACKET ���ݰ���ָ�롣
 * @param topic_offset_ptr �洢����ƫ������ָ�룬��������ʱ�����ø�ֵ��
 * @param topic_length_ptr �洢���ⳤ�ȵ�ָ�룬��������ʱ�����ø�ֵ��
 * @param message_offset_ptr �洢��Ϣƫ������ָ�룬��������ʱ�����ø�ֵ��
 * @param message_length_ptr �洢��Ϣ���ȵ�ָ�룬��������ʱ�����ø�ֵ��
 * 
 * @return ���ش��������״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT _nxd_mqtt_process_publish_packet(NX_PACKET *packet_ptr, ULONG *topic_offset_ptr, USHORT *topic_length_ptr,
                                      ULONG *message_offset_ptr, ULONG *message_length_ptr);

/**
 * @brief ������ MQTT �����������ӣ������������֤��
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param server_ip ָ������� IP ��ַ��ָ�롣
 * @param server_port �������˿ںš�
 * @param keepalive ���ֻ��ʱ������
 * @param clean_session ����Ự�ı�־��1 ��ʾ�����0 ��ʾ�������
 * @param timeout ��ʱ���ã�ָ�������ĳ�ʱʱ�䡣
 * 
 * @return �������Ӳ�����״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT _nxde_mqtt_client_connect(NXD_MQTT_CLIENT *client_ptr, NXD_ADDRESS *server_ip, UINT server_port,
                               UINT keepalive, UINT clean_session, ULONG timeout);

/**
 * @brief ���� MQTT �ͻ���ʵ������ʼ����
 * 
 * @param client_ptr ָ��Ҫ������ NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param client_name �ͻ��������ַ���ָ�롣
 * @param client_id �ͻ��� ID �ַ���ָ�롣
 * @param client_id_length �ͻ��� ID �ĳ��ȡ�
 * @param ip_ptr ָ������� NX_IP �ṹ���ָ�롣
 * @param pool_ptr ָ������ MQTT �ͻ��˵� NX_PACKET_POOL ��ָ�롣
 * @param stack_ptr ָ��ͻ����߳�ջ��ָ�롣
 * @param stack_size �ͻ����߳�ջ�Ĵ�С��
 * @param mqtt_thread_priority MQTT �ͻ����̵߳����ȼ���
 * @param memory_ptr ָ�����ڿͻ��˵��ڴ��ָ�롣
 * @param memory_size �ͻ��������ڴ�Ĵ�С��
 * 
 * @return ���ش���������״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT _nxde_mqtt_client_create(NXD_MQTT_CLIENT *client_ptr, CHAR *client_name, CHAR *client_id, UINT client_id_length,
                              NX_IP *ip_ptr, NX_PACKET_POOL *pool_ptr,
                              VOID *stack_ptr, ULONG stack_size, UINT mqtt_thread_priority,
                              VOID *memory_ptr, ULONG memory_size);
/**
 * @brief ɾ�� MQTT �ͻ���ʵ�����ͷ������Դ��
 * 
 * @param client_ptr ָ��Ҫɾ���� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * 
 * @return ����ɾ��������״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT _nxde_mqtt_client_delete(NXD_MQTT_CLIENT *client_ptr);

/**
 * @brief ���� MQTT �ͻ��˵ĶϿ�����֪ͨ�ص�������
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param disconnect_notify �Ͽ�����ʱ���õĻص�����ָ�롣
 * 
 * @return �������ò�����״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT _nxde_mqtt_client_disconnect_notify_set(NXD_MQTT_CLIENT *client_ptr, VOID (*disconnect_notify)(NXD_MQTT_CLIENT *));

/**
 * @brief �Ͽ��� MQTT �����������ӡ�
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * 
 * @return ���ضϿ����Ӳ�����״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT _nxde_mqtt_client_disconnect(NXD_MQTT_CLIENT *client_ptr);

/**
 * @brief ���� MQTT �ͻ��˵��û��������룬���������֤��
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param username �û����ַ���ָ�롣
 * @param username_length �û����ĳ��ȡ�
 * @param password �����ַ���ָ�롣
 * @param password_length ����ĳ��ȡ�
 * 
 * @return �������ò�����״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT _nxde_mqtt_client_login_set(NXD_MQTT_CLIENT *client_ptr,
                                 CHAR *username, UINT username_length, CHAR *password, UINT password_length);

/**
 * @brief �� MQTT �ͻ��˽��յ���Ϣ�л�ȡ�������Ϣ���ݡ�
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param topic_buffer �洢����Ļ�����ָ�롣
 * @param topic_buffer_size ���⻺�����Ĵ�С��
 * @param actual_topic_length ʵ�����ⳤ�ȵ�ָ�룬��������ʱ�����ø�ֵ��
 * @param message_buffer �洢��Ϣ���ݵĻ�����ָ�롣
 * @param message_buffer_size ��Ϣ�������Ĵ�С��
 * @param actual_message_length ʵ����Ϣ���ȵ�ָ�룬��������ʱ�����ø�ֵ��
 * 
 * @return ���ػ�ȡ��Ϣ������״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT _nxde_mqtt_client_message_get(NXD_MQTT_CLIENT *client_ptr, UCHAR *topic_buffer, UINT topic_buffer_size, UINT *actual_topic_length,
                                   UCHAR *message_buffer, UINT message_buffer_size, UINT *actual_message_length);

/**
 * @brief �� MQTT ������������Ϣ��
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param topic_name ���������ַ���ָ�롣
 * @param topic_name_length �������Ƶĳ��ȡ�
 * @param message Ҫ��������Ϣ�ַ���ָ�롣
 * @param message_length ��Ϣ�ĳ��ȡ�
 * @param retain ������־��1 ��ʾ��ϢӦ������0 ��ʾ��������
 * @param QoS ��Ϣ�ķ�����������0��1 �� 2��
 * @param timeout ��ʱ���ã�ָ�������ĳ�ʱʱ�䡣
 * 
 * @return ���ط���������״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT _nxde_mqtt_client_publish(NXD_MQTT_CLIENT *client_ptr, CHAR *topic_name, UINT topic_name_length,
                               CHAR *message, UINT message_length, UINT retain, UINT QoS, ULONG timeout);

/**
 * @brief ���� MQTT �ͻ��˵Ľ���֪ͨ�ص�������
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param receive_notify ������Ϣʱ���õĻص�����ָ�롣
 * 
 * @return �������ò�����״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT _nxde_mqtt_client_receive_notify_set(NXD_MQTT_CLIENT *client_ptr,
                                          VOID (*receive_notify)(NXD_MQTT_CLIENT *client_ptr, UINT message_count));

/**
 * @brief ���� MQTT �ͻ��˵��ڴ��ͷŻص�������
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param release_callback �ڴ��ͷź�����ָ�롣
 * 
 * @return �������ò�����״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT _nxde_mqtt_client_release_callback_set(NXD_MQTT_CLIENT *client_ptr, VOID (*release_callback)(CHAR *, UINT));

/**
 * @brief ����ָ���������Ϣ��
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param topic_name Ҫ���ĵ����������ַ���ָ�롣
 * @param topic_name_length �������Ƶĳ��ȡ�
 * @param QoS ��Ϣ�ķ�����������0��1 �� 2��
 * 
 * @return ���ض��Ĳ�����״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT _nxde_mqtt_client_subscribe(NXD_MQTT_CLIENT *client_ptr, CHAR *topic_name, UINT topic_name_length, UINT QoS);

/**
 * @brief ȡ������ָ���������Ϣ��
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param topic_name Ҫȡ�����ĵ����������ַ���ָ�롣
 * @param topic_name_length �������Ƶĳ��ȡ�
 * 
 * @return ����ȡ�����Ĳ�����״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT _nxde_mqtt_client_unsubscribe(NXD_MQTT_CLIENT *client_ptr, CHAR *topic_name, UINT topic_name_length);

/**
 * @brief ���ÿͻ��˵�������Ϣ��
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param will_topic ���������ַ���ָ�롣
 * @param will_topic_length ��������ĳ��ȡ�
 * @param will_message ������Ϣ�ַ���ָ�롣
 * @param will_message_length ������Ϣ�ĳ��ȡ�
 * @param will_retain_flag ������Ϣ������־��1 ��ʾ������0 ��ʾ��������
 * @param will_QoS ������Ϣ�ķ�����������0��1 �� 2��
 * 
 * @return ��������������Ϣ������״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT _nxde_mqtt_client_will_message_set(NXD_MQTT_CLIENT *client_ptr,
                                        const UCHAR *will_topic, UINT will_topic_length, const UCHAR *will_message,
                                        UINT will_message_length, UINT will_retain_flag, UINT will_QoS);

#ifdef NX_SECURE_ENABLE
/**
 * @brief ������ MQTT �������İ�ȫ���ӣ�TLS����
 * 
 * �˺�������ͨ����ȫ�׽��֣�TLS����ָ���� MQTT �������������ӡ�
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param server_ip ָ�� MQTT �������� IP ��ַ�ṹ��ָ�롣
 * @param server_port �������Ķ˿ںš�
 * @param tls_setup ָ���������� TLS ���ӵĻص�����ָ�롣
 *                   �˻ص�����Ӧ���� TLS �Ự�����֤�顣
 * @param keepalive �ͻ����������֮�������ʱ�䣬����Ϊ��λ��
 * @param clean_session ָ���Ƿ�ʹ�øɾ��ĻỰ��1 ��ʾʹ�ã�0 ��ʾ��ʹ�á�
 * @param wait_option �ȴ�ѡ�����ָ�������ĵȴ�ʱ�䡣
 * 
 * @return ���ذ�ȫ���Ӳ�����״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
 */
UINT _nxd_mqtt_client_secure_connect(NXD_MQTT_CLIENT *client_ptr, NXD_ADDRESS *server_ip, UINT server_port,
                                     UINT (*tls_setup)(NXD_MQTT_CLIENT *client_ptr, NX_SECURE_TLS_SESSION *,
                                                       NX_SECURE_X509_CERT *, NX_SECURE_X509_CERT *),
                                     UINT keepalive, UINT clean_session, ULONG wait_option);

/**
 * @brief ������ MQTT �������İ�ȫ���ӣ�TLS�������г�ʱѡ�
 * 
 * �˺�������ͨ����ȫ�׽��֣�TLS����ָ���� MQTT �������������ӣ�
 * ֧����ָ���ĳ�ʱʱ����������ӡ�
 * 
 * @param client_ptr ָ���Ѵ����� NXD_MQTT_CLIENT �ṹ���ָ�롣
 * @param server_ip ָ�� MQTT �������� IP ��ַ�ṹ��ָ�롣
 * @param server_port �������Ķ˿ںš�
 * @param tls_setup ָ���������� TLS ���ӵĻص�����ָ�롣
 *                   �˻ص�����Ӧ���� TLS �Ự�����֤�顣
 * @param keepalive �ͻ����������֮�������ʱ�䣬����Ϊ��λ��
 * @param clean_session ָ���Ƿ�ʹ�øɾ��ĻỰ��1 ��ʾʹ�ã�0 ��ʾ��ʹ�á�
 * @param timeout ָ�����Ӳ����ĳ�ʱʱ�䣬����Ϊ��λ��
 * 
 * @return ���ذ�ȫ���Ӳ�����״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
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
 * @brief ����һ�� MQTT �ƿͻ���ʵ����
 * 
 * �˺������ڴ���һ�� MQTT �ͻ��˲����������ָ������ƽ̨��
 * 
 * @param client_ptr ָ��Ҫ������ NXD_MQTT_CLIENT �ṹ���ָ�롣�ýṹ�彫����ʼ��Ϊ�ƿͻ��ˡ�
 * @param client_name �ͻ��˵����ƣ����ڱ�ʶ�ÿͻ��ˡ�
 * @param client_id �ͻ��˵�Ψһ��ʶ����ID����Ӧ������ MQTT ������Ψһ��
 * @param client_id_length �ͻ��� ID �ĳ��ȣ����ֽ�Ϊ��λ��
 * @param ip_ptr ָ����� MQTT �ͻ�����ص� IP �ṹ��ָ�롣
 * @param pool_ptr ָ�����ڷ����������ݰ��İ��ؽṹ��ָ�롣
 * @param cloud_ptr ָ����� MQTT �ͻ�����ص���ƽ̨�ṹ��ָ�롣
 * 
 * @return ���ش���������״̬���룬�ɹ�ʱ���� NXD_MQTT_SUCCESS��ʧ��ʱ������Ӧ�Ĵ�����롣
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

