#include "esp_log.h"
#include <driver/adc.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/// @brief a struce to storage the result
typedef struct TEMP6000
{
    float LX;
} TEMP6000_data_t;

esp_err_t TEMP6000_measure(TEMP6000_data_t *pTEMP6000_data, adc2_channel_t channel);

esp_err_t TEMP6000_setup(adc2_channel_t channel);