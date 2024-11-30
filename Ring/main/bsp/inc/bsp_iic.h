/*
  * ESPRESSIF MIT License
  *
  * Copyright (c) 2017 <ESPRESSIF SYSTEMS (SHANGHAI) PTE LTD>
  *
  * Permission is hereby granted for use on ESPRESSIF SYSTEMS products only, in which case,
  * it is free of charge, to any person obtaining a copy of this software and associated
  * documentation files (the "Software"), to deal in the Software without restriction, including
  * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
  * and/or sell copies of the Software, and to permit persons to whom the Software is furnished
  * to do so, subject to the following conditions:
  *
  * The above copyright notice and this permission notice shall be included in all copies or
  * substantial portions of the Software.
  *
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
  * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
  * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
  * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
  * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
  *
  */
#ifndef _IOT_I2C_BUS_H_
#define _IOT_I2C_BUS_H_

#include "driver/i2c.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void *i2c_bus_handle_t;

/**
 * @brief 创建并初始化 I2C 总线，返回 I2C 总线句柄
 *
 * @param port       I2C 端口号
 * @param conf       I2C 配置参数的指针
 *
 * @return
 *     - I2C 总线句柄
 */
i2c_bus_handle_t i2c_bus_create(i2c_port_t port, i2c_config_t *conf);

/**
 * @brief 向 I2C 总线写入字节数据
 *
 * @param bus        I2C 总线句柄
 * @param addr       设备的地址
 * @param reg        设备的寄存器地址
 * @param regLen     寄存器的长度
 * @param data       数据指针
 * @param datalen    数据的长度
 *
 * @return
 *     - NULL 失败
 *     - 其它值 成功
 */
esp_err_t i2c_bus_write_bytes(i2c_bus_handle_t bus, int addr, uint8_t *reg, int regLen, uint8_t *data, int datalen);

/**
 * @brief 向 I2C 总线写入数据
 *
 * @param bus        I2C 总线句柄
 * @param addr       设备的地址
 * @param data       数据指针
 * @param datalen    数据的长度
 *
 * @return
 *     - NULL 失败
 *     - 其它值 成功
 */
esp_err_t i2c_bus_write_data(i2c_bus_handle_t bus, int addr, uint8_t *data, int datalen);

/**
 * @brief 从 I2C 总线读取字节数据
 *
 * @param bus        I2C 总线句柄
 * @param addr       设备的地址
 * @param reg        设备的寄存器地址
 * @param regLen     寄存器的长度
 * @param outdata    输出数据指针
 * @param datalen    输出数据的长度
 *
 * @return
 *     - NULL 失败
 *     - 其它值 成功
 */
esp_err_t i2c_bus_read_bytes(i2c_bus_handle_t bus, int addr, uint8_t *reg, int reglen, uint8_t *outdata, int datalen);

/**
 * @brief 删除并释放 I2C 总线对象
 *
 * @param bus        I2C 总线句柄
 *
 * @return
 *     - ESP_OK 成功
 *     - ESP_FAIL 失败
 */
esp_err_t i2c_bus_delete(i2c_bus_handle_t bus);

/**
 * @brief 开始发送 I2C 缓冲命令
 *
 * @param bus            I2C 总线句柄
 * @param cmd            I2C 命令句柄
 * @param ticks_to_wait  最大阻塞时间
 *
 * @return
 *     - ESP_OK 成功
 *     - ESP_FAIL 失败
 */
esp_err_t i2c_bus_cmd_begin(i2c_bus_handle_t bus, i2c_cmd_handle_t cmd, portBASE_TYPE ticks_to_wait);

/**
 * @brief 自动探测 I2C 设备
 *
 * @param bus            I2C 总线句柄
 * @param addr           I2C 地址
 *
 * @return
 *     - ESP_OK 找到 I2C 设备
 *     - ESP_FAIL 失败
 */
esp_err_t i2c_bus_probe_addr(i2c_bus_handle_t bus, uint8_t addr);


#ifdef __cplusplus
}
#endif

#endif
