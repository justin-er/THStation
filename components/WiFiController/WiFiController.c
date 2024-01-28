#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "esp_netif.h"

#define wifiAP_SSID                 "ESP32SSID"
#define wifiAP_SSIDMaxLength        32
#define wifiAP_SSIDIsHidden         0
#define wifiAPPassword              "Password"
#define wifiAPMaxPasswordLength     64
#define wifiAPChannel               1
#define wifiAPBeaconInterval        100
#define wifiAP_IPAddress            "192.168.0.1"
#define wifiAPGatewayAddress        "192.168.0.1"
#define wifiAPNetmask               "255.255.255.0"
#define wifiSTAPowerSave            WIFI_PS_NONE
#define wifiAPBandwidth             WIFI_BW_HT20
#define wifiConnectionRetryNumbers  5

extern esp_netif_t* espSTANetworkInterface;
extern esp_netif_t* espAPNetworkInterface;

typedef enum WifiControllerMessage {
    startHTTPServer,
    connectingFromHTTPServer,
    staConnectedDidGetIP,
} WifiControllerMessage;

typedef struct WifiControllerMessageQueue {
    enum WifiControllerMessage message;
} WifiControllerMessageQueue;

BaseType_t wifiControllerSendMessage(WifiControllerMessage message) {
    return 0;
}

