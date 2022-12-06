// device.esp - caOS Device System for ESP chips
// (c) 2022 Star Inc. (https://starinc.xyz)
// License: MIT

#define CAOS_CLIENT_STATE_ONLINE 0
#define CAOS_CLIENT_STATE_OFFLINE 1
#define CAOS_CLIENT_STATE_UNAUTHORIZED 2
#define CAOS_CLIENT_STATE_NETWORK_ERROR 3
#define CAOS_CLIENT_STATE_UNKNOWN_ERROR 4

typedef struct caos_client_device_profile
{
    char *device_name;
} caos_client_device_profile_t;

int caos_client_get_state();
caos_client_device_profile_t *caos_client_get_device_profile();
