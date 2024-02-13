// #include <stdio.h>
// #include <freertos/FreeRTOS.h>
// #include <freertos/task.h>

// #include "esp_netif.h"
#ifndef WiFiController_h
#define WiFiController_h

typedef enum {
    startHTTPServer,
    connectingFromHTTPServer,
    staConnectedDidGetIP,
} WifiControllerMessageType;

typedef struct {
    WifiControllerMessageType messageType;
} WifiControllerMessage;

BaseType_t wifiControllerSendMessage(WifiControllerMessageType messageType);

void startWifiController(void);

#endif 
