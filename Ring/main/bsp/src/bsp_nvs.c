#include "../bsp.h"


void bsp_InitNVS(void)
{
    esp_err_t err = nvs_flash_init();
    if(err != ESP_OK)
    {
        nvs_flash_erase();
        ESP_ERROR_CHECK(nvs_flash_init());
    }
}
/**
 * @brief 封装 nvs_set_blob 函数，通过字符串写入 NVS
 * 
 * @param namespace NVS 命名空间的名称
 * @param key 键值，用于存储字符串
 * @param str 要写入的字符串
 * @return esp_err_t 写入结果，ESP_OK 表示成功，其他值表示失败
 */
esp_err_t bsp_set_string_to_nvs(const char *namespace, const char *key, const char *str)
{
    nvs_handle_t handle;
    esp_err_t err;

    // 打开 NVS 命名空间
    err = nvs_open(namespace, NVS_READWRITE, &handle);
    if (err != ESP_OK) {
        return err;  // 打开失败，返回错误码
    }

    // 将字符串写入 NVS
    err = nvs_set_blob(handle, key, str, strlen(str) + 1);  // 包括 '\0' 字符
    if (err != ESP_OK) {
        nvs_close(handle);  // 如果写入失败，关闭 NVS
        return err;
    }

    // 提交更改
    err = nvs_commit(handle);
    nvs_close(handle);  // 操作完成后关闭 NVS
    return err;
}



/**
 * @brief 封装 nvs_set_blob 函数，通过数组写入 NVS
 * 
 * @param namespace NVS 命名空间的名称
 * @param key 键值，用于存储数组
 * @param array 数组的指针
 * @param length 数组的长度
 * @return esp_err_t 写入结果，ESP_OK 表示成功，其他值表示失败
 */
esp_err_t bsp_set_array_to_nvs(const char *namespace, const char *key, const void *array, size_t length)
{
    nvs_handle_t handle;
    esp_err_t err;

    // 打开 NVS 命名空间
    err = nvs_open(namespace, NVS_READWRITE, &handle);
    if (err != ESP_OK) {
        return err;  // 打开失败，返回错误码
    }

    // 将数组写入 NVS
    err = nvs_set_blob(handle, key, array, length);
    if (err != ESP_OK) {
        nvs_close(handle);  // 如果写入失败，关闭 NVS
        return err;
    }

    // 提交更改
    err = nvs_commit(handle);
    nvs_close(handle);  // 操作完成后关闭 NVS
    return err;
}



/**
 * @brief 从 NVS 中读取指定键的值（字符串或数组），处理长度为 0 的情况
 * 
 * @param namespace NVS 命名空间的名称
 * @param key 键值，用于获取对应的数据
 * @param out_data 指向接收读取数据的缓冲区
 * @param length 指定缓冲区的大小（传入指针，返回实际读取的大小）
 * @return esp_err_t 读取结果，ESP_OK 表示成功，其他值表示失败
 */
esp_err_t bsp_get_data_from_nvs(const char *namespace, const char *key, void *out_data, size_t *length)
{
    if (length == NULL || *length == 0) {
        // 如果长度指针为 NULL 或长度为 0，直接返回错误
        return ESP_ERR_INVALID_ARG;
    }

    nvs_handle_t handle;
    esp_err_t err;

    // 打开 NVS 命名空间
    err = nvs_open(namespace, NVS_READONLY, &handle);
    if (err != ESP_OK) {
        return err;  // 打开失败，返回错误码
    }

    // 获取数据的大小
    size_t required_size = 0;
    err = nvs_get_blob(handle, key, NULL, &required_size);
    if (err != ESP_OK) {
        nvs_close(handle);  // 如果获取失败，关闭 NVS
        return err;
    }

    // 检查获取的长度是否为 0
    if (required_size == 0) {
        nvs_close(handle);
        return ESP_ERR_NVS_NOT_FOUND;  // 返回表示键值为空或未初始化的错误
    }

    // 检查缓冲区是否足够
    if (*length < required_size) {
        nvs_close(handle);
        return ESP_ERR_NVS_INVALID_LENGTH;  // 缓冲区不足
    }

    // 读取数据
    err = nvs_get_blob(handle, key, out_data, length);
    nvs_close(handle);  // 操作完成后关闭 NVS
    return err;
}


/**
 * @brief 存储多个键值对到 NVS
 * 
 * @param namespace NVS 命名空间的名称
 * @param keys 键值对数组，每个元素包含键名和对应的字符串值
 * @param values 每个键对应的字符串值
 * @param count 键值对数量
 * @return esp_err_t 操作结果，ESP_OK 表示成功，其他值表示失败
 */
esp_err_t bsp_set_multiple_strings_to_nvs(const char *namespace, const char *keys[], const char *values[], size_t count)
{
    if (namespace == NULL || keys == NULL || values == NULL || count == 0) {
        return ESP_ERR_INVALID_ARG;  // 参数无效
    }

    nvs_handle_t handle;
    esp_err_t err;

    // 打开 NVS 命名空间
    err = nvs_open(namespace, NVS_READWRITE, &handle);
    if (err != ESP_OK) {
        return err;
    }

    // 遍历键值对并存储
    for (size_t i = 0; i < count; i++) {
        if (keys[i] == NULL || values[i] == NULL) {
            nvs_close(handle);
            return ESP_ERR_INVALID_ARG;  // 单个键或值为空
        }

        // 将字符串存储到对应键
        err = nvs_set_blob(handle, keys[i], values[i], strlen(values[i]) + 1);
        if (err != ESP_OK) {
            nvs_close(handle);
            return err;  // 写入失败，提前退出
        }
    }

    // 提交更改
    err = nvs_commit(handle);
    nvs_close(handle);  // 操作完成后关闭 NVS
    return err;
}

esp_err_t bsp_get_multiple_data_from_nvs(const char *namespace, const char *keys[], void *out_data[], size_t lengths[], size_t count) 
{
    if (namespace == NULL || keys == NULL || out_data == NULL || lengths == NULL || count == 0) {
        return ESP_ERR_INVALID_ARG;  // 参数无效
    }

    nvs_handle_t handle;
    esp_err_t err;

    // 打开 NVS 命名空间
    err = nvs_open(namespace, NVS_READONLY, &handle);
    if (err != ESP_OK) {
        return err;
    }

    for (size_t i = 0; i < count; i++) {
        if (keys[i] == NULL || out_data[i] == NULL || lengths[i] == 0) {
            nvs_close(handle);
            return ESP_ERR_INVALID_ARG;  // 单个键、输出缓冲区或长度无效
        }

        size_t required_size = 0;
        err = nvs_get_blob(handle, keys[i], NULL, &required_size);
        if (err != ESP_OK) {
            nvs_close(handle);
            return err;  // 如果获取失败，直接返回错误
        }

        // 检查长度是否为 0 或缓冲区不足
        if (required_size == 0 || lengths[i] < required_size) {
            nvs_close(handle);
            return ESP_ERR_NVS_INVALID_LENGTH;
        }

        // 读取数据
        err = nvs_get_blob(handle, keys[i], out_data[i], &lengths[i]);
        if (err != ESP_OK) {
            nvs_close(handle);
            return err;  // 读取失败，提前退出
        }
    }

    nvs_close(handle);
    return ESP_OK;  // 全部读取成功
}


esp_err_t bsp_set_data_to_multiple_namespaces(
    const char *namespaces[],      // 命名空间数组
    size_t ns_count,               // 命名空间数量
    const char **keys[],           // 每个命名空间的键数组（动态长度）
    size_t key_counts[],           // 每个命名空间的键数量
    const void **data[],           // 每个命名空间的值数组（动态长度）
    size_t *data_lengths[]         // 每个命名空间的值长度数组（动态长度）
) {
    if (namespaces == NULL || keys == NULL || data == NULL || data_lengths == NULL || ns_count == 0) {
        return ESP_ERR_INVALID_ARG;  // 参数无效
    }

    for (size_t ns_index = 0; ns_index < ns_count; ns_index++) {
        const char *namespace = namespaces[ns_index];
        size_t key_count = key_counts[ns_index];

        // 打开当前命名空间（写入模式）
        nvs_handle_t handle;
        esp_err_t err = nvs_open(namespace, NVS_READWRITE, &handle);
        if (err != ESP_OK) {
            return err;  // 打开命名空间失败
        }

        for (size_t key_index = 0; key_index < key_count; key_index++) {
            const char *key = keys[ns_index][key_index];
            const void *value = data[ns_index][key_index];
            size_t value_length = data_lengths[ns_index][key_index];

            // 检查参数有效性
            if (key == NULL || value == NULL || value_length == 0) {
                nvs_close(handle);
                return ESP_ERR_INVALID_ARG;
            }

            // 写入数据
            err = nvs_set_blob(handle, key, value, value_length);
            if (err != ESP_OK) {
                nvs_close(handle);
                return err;  // 写入失败
            }
        }

        // 提交数据
        err = nvs_commit(handle);
        if (err != ESP_OK) {
            nvs_close(handle);
            return err;  // 提交失败
        }

        nvs_close(handle);  // 关闭当前命名空间
    }

    return ESP_OK;  // 全部写入成功
}


esp_err_t bsp_get_data_from_multiple_namespaces(
    const char *namespaces[],       // 命名空间数组
    size_t ns_count,                // 命名空间数量
    const char **keys[],            // 每个命名空间的键数组（动态长度）
    size_t key_counts[],            // 每个命名空间的键数量
    void **out_data[],              // 每个命名空间的输出缓冲区数组（动态长度）
    size_t *lengths[]               // 每个命名空间的缓冲区长度数组（动态长度）
) {
    if (namespaces == NULL || keys == NULL || out_data == NULL || lengths == NULL || ns_count == 0) {
        return ESP_ERR_INVALID_ARG;  // 参数无效
    }

    for (size_t ns_index = 0; ns_index < ns_count; ns_index++) {
        const char *namespace = namespaces[ns_index];
        size_t key_count = key_counts[ns_index];

        // 打开当前命名空间
        nvs_handle_t handle;
        esp_err_t err = nvs_open(namespace, NVS_READONLY, &handle);
        if (err != ESP_OK) {
            return err;  // 打开命名空间失败
        }

        for (size_t key_index = 0; key_index < key_count; key_index++) {
            const char *key = keys[ns_index][key_index];
            void *buffer = out_data[ns_index][key_index];
            size_t buffer_length = lengths[ns_index][key_index];

            // 检查参数有效性
            if (key == NULL || buffer == NULL || buffer_length == 0) {
                nvs_close(handle);
                return ESP_ERR_INVALID_ARG;
            }

            // 获取键值长度
            size_t required_size = 0;
            err = nvs_get_blob(handle, key, NULL, &required_size);
            if (err != ESP_OK) {
                nvs_close(handle);
                return err;  // 获取长度失败
            }

            // 检查长度是否为 0 或缓冲区不足
            if (required_size == 0 || buffer_length < required_size) {
                nvs_close(handle);
                return ESP_ERR_NVS_INVALID_LENGTH;
            }

            // 读取数据
            err = nvs_get_blob(handle, key, buffer, &buffer_length);
            if (err != ESP_OK) {
                nvs_close(handle);
                return err;  // 读取失败
            }
        }

        nvs_close(handle);  // 关闭当前命名空间
    }

    return ESP_OK;  // 全部读取成功
}


