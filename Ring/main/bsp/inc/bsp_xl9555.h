/**
 ****************************************************************************************************
 * @file        xl9555.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-08-26
 * @brief       XL9555驱动代码
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 ESP32-S3 开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#ifndef __XL9555_H
#define __XL9555_H

#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../bsp.h"


/* 引脚与相关参数定义 */
#define XL9555_INT_IO               GPIO_NUM_40                     /* XL9555_INT引脚 */
#define XL9555_INT                  gpio_get_level(XL9555_INT_IO)   /* 读取XL9555_INT的电平 */

/* XL9555命令宏 */
#define XL9555_INPUT_PORT0_REG      0                               /* 输入寄存器0地址 */
#define XL9555_INPUT_PORT1_REG      1                               /* 输入寄存器1地址 */
#define XL9555_OUTPUT_PORT0_REG     2                               /* 输出寄存器0地址 */
#define XL9555_OUTPUT_PORT1_REG     3                               /* 输出寄存器1地址 */
#define XL9555_INVERSION_PORT0_REG  4                               /* 极性反转寄存器0地址 */
#define XL9555_INVERSION_PORT1_REG  5                               /* 极性反转寄存器1地址 */
#define XL9555_CONFIG_PORT0_REG     6                               /* 方向配置寄存器0地址 */
#define XL9555_CONFIG_PORT1_REG     7                               /* 方向配置寄存器1地址 */


/* XL9555各个IO的功能 */
#define AP_INT_IO                   0
#define QMA_INT_IO                  1
#define SPK_EN_IO                   2
#define BEEP_IO                     3
#define OV_PWDN_IO                  4
#define OV_RESET_IO                 5
#define GBC_LED_IO                  6
#define GBC_KEY_IO                  7
#define LCD_BL_IO                   8
#define CT_RST_IO                   9
#define SLCD_RST_IO                 10
#define SLCD_PWR_IO                 11
#define KEY3_IO                     12
#define KEY2_IO                     13
#define KEY1_IO                     14
#define KEY0_IO                     15




#define KEY0                        xl9555_pin_read(KEY0_IO)        /* 读取KEY0引脚 */
#define KEY1                        xl9555_pin_read(KEY1_IO)        /* 读取KEY1引脚 */
#define KEY2                        xl9555_pin_read(KEY2_IO)        /* 读取KEY2引脚 */
#define KEY3                        xl9555_pin_read(KEY3_IO)        /* 读取KEY3引脚 */

#define KEY0_PRES                   1                               /* KEY0按下 */
#define KEY1_PRES                   2                               /* KEY1按下 */
#define KEY2_PRES                   3                               /* KEY1按下 */
#define KEY3_PRES                   4                               /* KEY1按下 */

typedef struct {
    gpio_num_t i2c_sda;
    gpio_num_t i2c_scl;
    gpio_num_t interrupt_output;
} esp_xl9555_config_t;

typedef enum {
    XL9555_IO_OUTPUT,
    XL9555_IO_INPUT
} esp_xl9555_io_config_t;

typedef enum {
    XL9555_IO_LOW,
    XL9555_IO_HIGH,
    XL9555_LEVEL_ERROR
} esp_xl9555_io_level_t;

typedef enum {
    XL9555_IO_RETAINED,
    XL9555_IO_INVERTED
} esp_xl9555_io_polarity_t;


/**
 * @brief 初始化 XL9555
 * 
 * @param cfg 配置结构体指针，包含 XL9555 的配置参数
 * @return esp_err_t 初始化结果
 */
esp_err_t xl9555_init(esp_xl9555_config_t *cfg);

/**
 * @brief 设置指定 GPIO 引脚的输入输出模式
 * 
 * @param gpio_num GPIO 引脚编号
 * @param io_config 配置模式：输入或输出
 * @return esp_err_t 设置结果
 */
esp_err_t xl9555_set_io_config(uint16_t gpio_num, esp_xl9555_io_config_t io_config);

/**
 * @brief 设置指定 GPIO 引脚的输出电平
 * 
 * @param gpio_num GPIO 引脚编号
 * @param level 输出电平（高电平或低电平）
 * @return esp_err_t 设置结果
 */
esp_err_t xl9555_set_output_state(uint16_t gpio_num, esp_xl9555_io_level_t level);

/**
 * @brief 设置指定 GPIO 引脚的极性反转
 * 
 * @param gpio_num GPIO 引脚编号
 * @param polarity 极性反转模式：正常或反转
 * @return esp_err_t 设置结果
 */
esp_err_t xl9555_set_polarity_inversion(uint16_t gpio_num, esp_xl9555_io_polarity_t polarity);

/**
 * @brief 获取指定 GPIO 引脚的输入输出模式
 * 
 * @param gpio_num GPIO 引脚编号
 * @return esp_xl9555_io_config_t 当前模式：输入或输出
 */
esp_xl9555_io_config_t xl9555_get_io_config(uint16_t gpio_num);

/**
 * @brief 读取 XL9555 所有 GPIO 引脚的状态
 * 
 * 该函数读取 XL9555 的所有输入和输出端口状态，并进行处理。
 */
void xl9555_read_all(void);

/**
 * @brief 反初始化 XL9555，释放资源
 * 
 * @return esp_err_t 反初始化结果
 */
esp_err_t xl9555_deinit(void);

/**
 * @brief 获取指定 GPIO 引脚的输出电平状态
 * 
 * @param gpio_num GPIO 引脚编号
 * @return esp_xl9555_io_level_t 当前输出电平：高电平或低电平
 */
esp_xl9555_io_level_t xl9555_get_output_state(uint16_t gpio_num);

/**
 * @brief 获取指定 GPIO 引脚的输入电平状态
 * 
 * @param gpio_num GPIO 引脚编号
 * @return esp_xl9555_io_level_t 当前输入电平：高电平或低电平
 */
esp_xl9555_io_level_t xl9555_get_input_state(uint16_t gpio_num);


#endif
