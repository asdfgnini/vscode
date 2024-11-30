

#include "../bsp.h"

static char *TAG = "XL9555";
static i2c_bus_handle_t i2c_handle;

typedef struct {
    uint8_t addr;
    char *name;
} xl9555_dev_t;


//这里地址是7位地址左移一位后的地址，不然不对，因为后续没做左移一位的处理
static xl9555_dev_t dev_list[] = {
    { 0x40, "XL9555"}
};

static uint8_t xl9555_addr;

static esp_err_t expander_dev_prob()
{
    for (size_t i = 0; i < sizeof(dev_list) / sizeof(dev_list[0]); i++) {

        if (ESP_OK == i2c_bus_probe_addr(i2c_handle, dev_list[i].addr)) {
            ESP_LOGI(TAG, "Detected IO expander device at 0x%02X, name is: %s",
                     dev_list[i].addr, dev_list[i].name);
            xl9555_addr = dev_list[i].addr;
            return ESP_OK;
        }
    }
    xl9555_addr = 0;
    ESP_LOGE(TAG, "IO expander device has not detected");
    return ESP_ERR_NOT_FOUND;
}

static int i2c_init(gpio_num_t clk, gpio_num_t sda)
{
    int res = 0;
    i2c_config_t es_i2c_cfg = {
        .mode = I2C_MODE_MASTER,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 400000,
        .scl_io_num = clk,
        .sda_io_num = sda,
    };
    i2c_handle = i2c_bus_create(I2C_NUM_0, &es_i2c_cfg);
    return res;
}
esp_err_t xl9555_write_reg(uint8_t reg_addr, uint16_t data)
{
    uint8_t data_buf[2];
    // 将16位数据拆分为高字节和低字节
    data_buf[0] = (uint8_t)(data & 0xFF);      // 低字节
    data_buf[1] = (uint8_t)((data >> 8) & 0xFF);       // 高字节

    // 输出调试信息
    ESP_LOGI("I2C", "Writing to reg 0x%02X with data 0x%02X 0x%02X", reg_addr, data_buf[0], data_buf[1]);

    // 写入寄存器地址和16位数据
    esp_err_t ret = i2c_bus_write_bytes(i2c_handle, xl9555_addr, &reg_addr, sizeof(reg_addr), data_buf, sizeof(data_buf));

    // 检查返回值并输出错误信息
    if (ret != ESP_OK) {
        ESP_LOGE("I2C", "I2C Write Error: %s", esp_err_to_name(ret));
    }

    return ret;
}


static uint16_t xl9555_read_reg(uint8_t reg_addr)
{
    uint8_t data_buf[2];
    // 从指定寄存器地址读取 16 位数据
    esp_err_t ret = i2c_bus_read_bytes(i2c_handle, xl9555_addr, &reg_addr, sizeof(reg_addr), data_buf, sizeof(data_buf));
    if (ret != ESP_OK) {
        // 错误处理（可以根据需求调整）
        printf("Read failed: %s\n", esp_err_to_name(ret));
        return 0; // 返回默认值或特定错误值
    }

    // 输出读取到的数据进行调试
    printf("Data read: 0x%02X 0x%02X\n", data_buf[0], data_buf[1]);

    // 如果设备使用小端字节序，交换字节顺序
    uint16_t data = ((uint16_t)data_buf[1] << 8) | data_buf[0]; // 小端字节序

    return data;
}


esp_xl9555_io_level_t xl9555_get_input_state(uint16_t gpio_num)
{
    uint8_t reg_addr;
    uint16_t input_reg;

    // 判断要读取的寄存器地址
    if (gpio_num < 8) {
        reg_addr = XL9555_INPUT_PORT0_REG;  // 读取端口0的输入状态
    } else {
        reg_addr = XL9555_INPUT_PORT1_REG;  // 读取端口1的输入状态
        gpio_num -= 8;  // 将 gpio_num 转换为端口1的第一个引脚
    }

    // 从输入寄存器读取数据
    input_reg = xl9555_read_reg(reg_addr);

    // 判断 GPIO 的输入状态
    if ((input_reg >> gpio_num) & 0x01) {
        // 如果对应位为1，则为高电平
        return XL9555_IO_HIGH;
    } else {
        // 如果对应位为0，则为低电平
        return XL9555_IO_LOW;
    }
}


esp_err_t xl9555_set_io_config(uint16_t gpio_num, esp_xl9555_io_config_t io_config)
{
    uint8_t reg_addr = XL9555_CONFIG_PORT0_REG;  // 配置寄存器地址
    uint16_t data;

    // 读取当前寄存器值（假设该寄存器配置多个 GPIO）
    data = xl9555_read_reg(reg_addr);

    // 根据配置模式设置指定 GPIO 引脚
    if (io_config == XL9555_IO_OUTPUT) {
        // 将指定 GPIO 引脚设置为输出模式 (假设输入配置为 0)
        data &= ~(1 << gpio_num);  // 清除对应位，设置为输出
    } else {
        // 将指定 GPIO 引脚设置为输入模式 (假设输出配置为 1)
        data |= (1 << gpio_num);   // 设置对应位，设置为输入
    }

    // 将更新后的数据写回寄存器
    return xl9555_write_reg(reg_addr, data);

}
esp_xl9555_io_config_t xl9555_get_io_config(uint16_t gpio_num)
{
    uint8_t reg_addr;
    uint16_t config_reg;

    // 判断要读取的寄存器地址
    if (gpio_num < 8) {
        reg_addr = XL9555_CONFIG_PORT0_REG;  // 读取端口0的配置
    } else {
        reg_addr = XL9555_CONFIG_PORT1_REG;  // 读取端口1的配置
        gpio_num -= 8;  // 将 gpio_num 转换为端口1的第一个引脚
    }

    // 从配置寄存器读取数据
    config_reg = xl9555_read_reg(reg_addr);

    // 根据gpio_num获取对应的GPIO配置
    if ((config_reg >> gpio_num) & 0x01) {
        // 如果对应位为1，则为输入模式
        return XL9555_IO_INPUT;
    } else {
        // 如果对应位为0，则为输出模式
        return XL9555_IO_OUTPUT;
    }
}

void xl9555_read_all()
{
    for (int i = 0; i < 7; i++) {
        uint8_t reg = xl9555_read_reg(i);
        ESP_LOGI("TAG","REG:%02x, %02x\n", i, reg);
    }
}
esp_err_t xl9555_deinit()
{
    i2c_bus_delete(i2c_handle);
    return ESP_OK;
}

esp_err_t xl9555_set_output_state(uint16_t gpio_num, esp_xl9555_io_level_t level)
{
    uint8_t reg_addr = XL9555_OUTPUT_PORT0_REG;  // 假设控制输出状态的寄存器地址
    uint16_t data;

    // 读取当前寄存器值（该寄存器控制多个 GPIO 的输出电平）
    data = xl9555_read_reg(reg_addr);

    // 根据 level 设置 GPIO 的输出电平
    if (level == XL9555_IO_LOW) {
        // 将指定 GPIO 引脚设置为低电平 (假设低电平为 0)
        data &= ~(1 << gpio_num);  // 清除对应位，设置为低电平
    } else {
        // 将指定 GPIO 引脚设置为高电平 (假设高电平为 1)
        data |= (1 << gpio_num);   // 设置对应位，设置为高电平
    }

    // 写回更新后的寄存器值
    return xl9555_write_reg(reg_addr, data);
}

esp_xl9555_io_level_t xl9555_get_output_state(uint16_t gpio_num)
{
    uint8_t reg_addr;
    uint16_t output_reg;

    // 判断要读取的寄存器地址
    if (gpio_num < 8) {
        reg_addr = XL9555_OUTPUT_PORT0_REG;  // 读取端口0的输出状态
    } else {
        reg_addr = XL9555_OUTPUT_PORT1_REG;  // 读取端口1的输出状态
        gpio_num -= 8;  // 将 gpio_num 转换为端口1的第一个引脚
    }

    // 从输出寄存器读取数据
    output_reg = xl9555_read_reg(reg_addr);

    // 判断 GPIO 的输出状态
    if ((output_reg >> gpio_num) & 0x01) {
        // 如果对应位为1，则为高电平
        return XL9555_IO_HIGH;
    } else {
        // 如果对应位为0，则为低电平
        return XL9555_IO_LOW;
    }
}



esp_err_t xl9555_set_polarity_inversion(uint16_t gpio_num, esp_xl9555_io_polarity_t polarity)
{
    uint8_t reg_addr = XL9555_INVERSION_PORT0_REG;  // 假设控制输出状态的寄存器地址
    uint16_t data;

    // 读取当前寄存器值（该寄存器控制多个 GPIO 的输出电平）
    data = xl9555_read_reg(reg_addr);

    // 根据 level 设置 GPIO 的输出电平
    if (polarity == XL9555_IO_RETAINED) {
        // 将指定 GPIO 引脚设置为低电平 (假设低电平为 0)
        data &= ~(1 << gpio_num);  // 清除对应位，设置为低电平
    } else {
        // 将指定 GPIO 引脚设置为高电平 (假设高电平为 1)
        data |= (1 << gpio_num);   // 设置对应位，设置为高电平
    }

    // 写回更新后的寄存器值
    return xl9555_write_reg(reg_addr, data);
}

esp_err_t xl9555_init(esp_xl9555_config_t *cfg)
{
    esp_err_t ret = ESP_OK;
    i2c_init(cfg->i2c_scl, cfg->i2c_sda);

    expander_dev_prob();

    return ret;
}

