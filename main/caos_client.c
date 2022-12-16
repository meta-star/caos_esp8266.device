// device.esp8266 - caOS Device System for ESP8266 chips
// (c) 2022 Star Inc. (https://starinc.xyz)
// License: MIT

#define CAOS_CLIENT_HOST "https://client.startw.cf"
#define CAOS_CLIENT_PORT 443
#define CAOS_CLIENT_PATH_PREFIX "/metastar_caos/cloud"

#define CAOS_CLIENT_USER_AGENT "startw-caos device v2.0"

#include "esp_http_client.h"
#include "esp_log.h"

#include "wifi_sta.h"
#include "caos_client.h"

static const char *TAG = "HTTP_CLIENT";

/**
 * caos_client_get_state
 * returns the connection state from caos.cloud.
 */
int caos_client_get_state()
{
    // check wifi state
    if (wifi_sta_get_state() != WIFI_STA_STATE_OK)
        return CAOS_CLIENT_STATE_NETWORK_ERROR;

    // all passed
    return CAOS_CLIENT_STATE_ONLINE;
}

esp_err_t _http_event_handler(esp_http_client_event_t *evt) {
    return ESP_OK;
};

/**
 * caos_client_get_device_profile
 * returns the profile of this device.
 */
caos_client_device_profile_t *caos_client_get_device_profile()
{
    caos_client_device_profile_t *profile;

    esp_http_client_config_t config = {
        .host = CAOS_CLIENT_HOST,
        .port = CAOS_CLIENT_PORT,
        .path = "/get",
        .transport_type = HTTP_TRANSPORT_OVER_TCP,
        .event_handler = _http_event_handler,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);

    esp_err_t err = esp_http_client_perform(client);
    if (err == ESP_OK) {
        ESP_LOGI(TAG, "HTTP GET Status = %d, content_length = %d",
                esp_http_client_get_status_code(client),
                esp_http_client_get_content_length(client));
    } else {
        ESP_LOGE(TAG, "HTTP GET request failed: %s", esp_err_to_name(err));
    }

    profile = malloc(sizeof(caos_client_device_profile_t));

    return profile;
}
