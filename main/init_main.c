// device.esp8266 - caOS Device System for ESP8266 chips
// (c) 2022 Star Inc. (https://starinc.xyz)
// License: MIT

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "wifi_ap.h"

void app_main()
{
    // ESP_ERROR_CHECK(nvs_flash_init());

    // ESP_LOGI(TAG, "ESP_WIFI_MODE_AP");
    wifi_init_softap();
}
