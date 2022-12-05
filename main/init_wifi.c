// device.esp - caOS Device System for ESP chips
// (c) 2022 Star Inc. (https://starinc.xyz)
// License: MIT

#include "init_wifi.h"

void wifi_server_start()
{
    printf("Hello world!\n");
    esp_wifi_init();
    esp_wifi_deinit();
}

void wifi_client_connect()
{
    printf("Hello world!\n");
    esp_wifi_init();
    esp_wifi_deinit();
}
