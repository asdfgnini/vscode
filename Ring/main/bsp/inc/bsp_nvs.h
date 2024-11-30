#ifndef BSP_NVS_H_
#define BSP_NVS_H_

#include "nvs_flash.h"
#include "string.h"




// 初始化 NVS（非易失性存储）系统
void bsp_InitNVS(void);


/**
 * @brief 封装 nvs_set_blob 函数，通过字符串写入 NVS,在一个命名空间内，操作一个键值
 * 
 * @param namespace NVS 命名空间的名称
 * @param key 键值，用于存储字符串
 * @param str 要写入的字符串
 * @return esp_err_t 写入结果，ESP_OK 表示成功，其他值表示失败
 */
esp_err_t bsp_set_string_to_nvs(const char *namespace, const char *key, const char *str);

/**
 * @brief 封装 nvs_set_blob 函数，通过数组写入 NVS，在一个命名空间内，操作一个键值
 * 
 * @param namespace NVS 命名空间的名称
 * @param key 键值，用于存储数组
 * @param array 数组的指针
 * @param length 数组的长度
 * @return esp_err_t 写入结果，ESP_OK 表示成功，其他值表示失败
 */
esp_err_t bsp_set_array_to_nvs(const char *namespace, const char *key, const void *array, size_t length);


/**
 * @brief 从 NVS 中读取指定键的值（字符串或数组），处理长度为 0 的情况，在一个命名空间内，操作一个键值
 * 
 * @param namespace NVS 命名空间的名称
 * @param key 键值，用于获取对应的数据
 * @param out_data 指向接收读取数据的缓冲区
 * @param length 指定缓冲区的大小（传入指针，返回实际读取的大小）
 * @return esp_err_t 读取结果，ESP_OK 表示成功，其他值表示失败
 */
esp_err_t bsp_get_data_from_nvs(const char *namespace, const char *key, void *out_data, size_t *length);



/**
 * @brief 存储多个键值对到 NVS，操作的是一个命名空间，查看app文件内nvs_demo.c获取例子
 * 
 * @param namespace NVS 命名空间的名称
 * @param keys 键值对数组，每个元素包含键名和对应的字符串值
 * @param values 每个键对应的字符串值
 * @param count 键值对数量
 * @return esp_err_t 操作结果，ESP_OK 表示成功，其他值表示失败
 */
esp_err_t bsp_set_multiple_strings_to_nvs(const char *namespace, const char *keys[], const char *values[], size_t count);


//一次性读取单个命名空间内的多个键值，查看app文件内nvs_demo.c获取例子
esp_err_t bsp_get_multiple_data_from_nvs(const char *namespace, const char *keys[], void *out_data[], size_t lengths[], size_t count);


//一次性操作多个命名空间进行写入，支持多个命名空间，每个命名空间的键值数量可以不同，查看app文件内nvs_demo.c获取例子
esp_err_t bsp_set_data_to_multiple_namespaces(
    const char *namespaces[],      // 命名空间数组
    size_t ns_count,               // 命名空间数量
    const char **keys[],           // 每个命名空间的键数组（动态长度）
    size_t key_counts[],           // 每个命名空间的键数量
    const void **data[],           // 每个命名空间的值数组（动态长度）
    size_t *data_lengths[]         // 每个命名空间的值长度数组（动态长度）
);

//一次性操作多个命名空间进行读取，支持多个命名空间，每个命名空间的键值数量可以不同，查看app文件内nvs_demo.c获取例子
esp_err_t bsp_get_data_from_multiple_namespaces(
    const char *namespaces[],       // 命名空间数组
    size_t ns_count,                // 命名空间数量
    const char **keys[],            // 每个命名空间的键数组（动态长度）
    size_t key_counts[],            // 每个命名空间的键数量
    void **out_data[],              // 每个命名空间的输出缓冲区数组（动态长度）
    size_t *lengths[]               // 每个命名空间的缓冲区长度数组（动态长度）
);


#endif

