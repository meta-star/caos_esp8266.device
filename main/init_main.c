// device.esp - caOS Device System for ESP chips
// (c) 2022 Star Inc. (https://starinc.xyz)
// License: MIT

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "wifi_ap.h"

void app_main()
{
    wifi_ap_start();
}
