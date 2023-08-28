#include "temp6000.h"

esp_err_t TEMP6000_measure(TEMP6000_data_t *pTEMP6000_data, adc2_channel_t channel)
{
    int read_raw;
    esp_err_t ret = 1;
    esp_err_t err = adc2_get_raw( channel, ADC_BITWIDTH_12, &read_raw);
    if (err == ESP_OK) {
        read_raw = read_raw * 0.025;
        if(read_raw > 100)
        {
            read_raw = 100;
        }
        else if(read_raw < 0)
        {
            read_raw = 0;
        }
        pTEMP6000_data->LX = read_raw;
        ESP_LOGD("TEMP6000_task", "LX: %.2f", pTEMP6000_data->LX);
    } else if ( err == ESP_ERR_TIMEOUT ) {
        ESP_LOGW("TEMP6000_task", "LX READ ERROR");
        return ret;
    }
    ret = 0;
    return ret;
}

esp_err_t TEMP6000_setup(adc2_channel_t channel)
{
    esp_err_t ret = 1;
    adc2_config_channel_atten( channel, ADC_ATTEN_DB_0 );
    return ret;
}
