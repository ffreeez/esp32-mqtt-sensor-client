#include "aht20.h"
#include "temp6000.h"
#include <stdio.h>

#define I2C_MASTER_SDA_IO 17
#define I2C_MASTER_SCL_IO 16
#define I2C_MASTER_FREQ_HZ 100 * 1000

const adc2_channel_t channel =  ADC2_CHANNEL_4;

TEMP6000_data_t TEMP6000_data = 
{
    .LX = 0,
};

i2c_config_t conf =
{
    .mode = I2C_MODE_MASTER,
    .sda_io_num = I2C_MASTER_SDA_IO,
    .sda_pullup_en = GPIO_PULLUP_DISABLE,
    .scl_io_num = I2C_MASTER_SCL_IO,
    .scl_pullup_en = GPIO_PULLUP_DISABLE,
    .master.clk_speed = I2C_MASTER_FREQ_HZ,
};

AHT20_data_t AHT20_data =
{
    .RH = 0,
    .TEMP = 0
};

void sensor_setup()
{
    i2c_param_config(I2C_MASTER_PORT, &conf);
    i2c_driver_install(I2C_MASTER_PORT, I2C_MODE_MASTER, 0, 0, 0);
    TEMP6000_setup(channel);
}

void app_main(void)
{
    sensor_setup();
    while (1)
    {
        esp_err_t ret_aht20, ret_temp6000;
        ret_aht20 = AHT20_measure(&AHT20_data);
        if(ret_aht20 == 0)
        {
            ret_temp6000 = TEMP6000_measure(&TEMP6000_data, channel);
            if(ret_temp6000 == 0)
            printf("RH: %.2f; TEMP: %.2f; LX: %.2f\n", AHT20_data.RH, AHT20_data.TEMP, TEMP6000_data.LX);
            
        }
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}
