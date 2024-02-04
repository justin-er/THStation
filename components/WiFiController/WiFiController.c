#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "esp_netif.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "lwip/netdb.h"

#include "LEDController.h"
#include "WiFiController.h"

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

const char* tag = "WifiController";
const LEDColor wifiStartingColor = { red: 5, green: 0, blue: 0 };

extern esp_netif_t *espSTANetworkInterface;
extern esp_netif_t* espAPNetworkInterface;

QueueHandle_t wifiControllerQueueHandle;
esp_netif_t* wifiSTA = NULL;
esp_netif_t* wifiAP = NULL;

BaseType_t wifiControllerSendMessage(WifiControllerMessage message) {
    return 0;
}

void startWifiController(void) {
    ESP_LOGI(tag, "Starting WifiController");
    startLEDBlinking(250, wifiStartingColor);
}

