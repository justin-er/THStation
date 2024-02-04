#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "esp_netif.h"

typedef enum {
    startHTTPServer,
    connectingFromHTTPServer,
    staConnectedDidGetIP,
} WifiControllerMessage;

typedef struct {
    WifiControllerMessage message;
} WifiControllerMessageQueue;

BaseType_t wifiControllerSendMessage(WifiControllerMessage message);

void startWifiController(void);
