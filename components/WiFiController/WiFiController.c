#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/task.h>

#include "esp_netif.h"
#include "esp_err.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "esp_wifi_types.h"
#include "lwip/netdb.h"

#include "LEDController.h"
#include "TaskConfig.h"
#include "WiFiController.h"

#define tag                         "WifiController"
#define wifiAP_SSID                 "ESP32SSID"
#define wifiAP_SSIDMaxLength        32
#define wifiAP_SSIDIsHidden         0
#define wifiAPPassword              "Password"
#define wifiAPMaxPasswordLength     64
#define wifiAPMaxConnections        5
#define wifiAPChannel               1
#define wifiAPBeaconInterval        100
#define wifiAP_IPAddress            "192.168.0.1"
#define wifiAPGatewayAddress        "192.168.0.1"
#define wifiAPNetmask               "255.255.255.0"
#define wifiSTAPowerSave            WIFI_PS_NONE
#define wifiAPBandwidth             WIFI_BW_HT20
#define wifiConnectionRetryNumbers  5

const LEDColor wifiStartingColor = { red: 5, green: 0, blue: 0 };

esp_netif_t* espSTANetworkInterface;
esp_netif_t* espAPNetworkInterface;

QueueHandle_t wifiControllerQueueHandle;
esp_netif_t* wifiSTA = NULL;
esp_netif_t* wifiAP = NULL;

// Function Prototypes
static void wifiTaskHanlder(void *pvParameters);
static void setupWifiEnventHandler(void);
static void handleWifiEvent(void *arg, esp_event_base_t event, int32_t eventID, void *eventData);
static void handleIPEvent(void *arg, esp_event_base_t event, int32_t eventID, void *eventData); 
static void setupDefaultWifi(void);
static void setupWifiAP(void);

BaseType_t wifiControllerSendMessage(WifiControllerMessageType messageType)
{
    WifiControllerMessage message;
    message.messageType = messageType;

    return xQueueSend(wifiControllerQueueHandle, &message, portMAX_DELAY);
}

void startWifiController(void) {
    ESP_LOGI(tag, "Starting WifiController");
    startLEDBlinking(250, wifiStartingColor);
    esp_log_level_set("wifi", ESP_LOG_NONE);

    wifiControllerQueueHandle = xQueueCreate(3, sizeof(WifiControllerMessage));
    
    xTaskCreatePinnedToCore(
        &wifiTaskHanlder,
        "WifiControllerTask",
        wifiControllerTaskConfig.stackSize,
        NULL,
        wifiControllerTaskConfig.priority,
        NULL,
        wifiControllerTaskConfig.coreID
    );
}

void wifiTaskHanlder(void *pvParameters) {
    WifiControllerMessage message;

    setupWifiEnventHandler();
    setupDefaultWifi();
    setupWifiAP();

    ESP_ERROR_CHECK(esp_wifi_start());

    wifiControllerSendMessage(startHTTPServer);

    while(true) {

        if (xQueueReceive(wifiControllerQueueHandle, &message, portMAX_DELAY)) {
            switch (message.messageType) {
                case startHTTPServer:
                    ESP_LOGI(tag, "WifiController did receive startHTTPServer");
                    setLED(redLED);
                    
                    break;

                case connectingFromHTTPServer:
                    ESP_LOGI(tag, "WifiController did receive connectingFromHTTPServer");
                    setLED(blueLED);

                    break;

                case staConnectedDidGetIP:
                    ESP_LOGI(tag, "WifiController did receive staConnectedDidGetIP");
                    setLED(greenLED);

                    break;
            }
        }
    }
}

void setupWifiEnventHandler(void) {
    esp_err_t result = esp_event_loop_create_default();
    ESP_ERROR_CHECK(result);

    esp_event_handler_instance_t wifiEventInstance;
    esp_event_handler_instance_t ipEventInstance;

    esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &handleWifiEvent, NULL, &wifiEventInstance);
    esp_event_handler_instance_register(IP_EVENT, ESP_EVENT_ANY_ID, &handleIPEvent, NULL, &ipEventInstance);
}

static void handleWifiEvent(void *arg, esp_event_base_t event, int32_t eventID, void *eventData) {
    switch(eventID) {
    case WIFI_EVENT_AP_START:
        ESP_LOGI(tag, "WIFI_EVENT_AP_START");
        break;

    case WIFI_EVENT_AP_STOP:
        ESP_LOGI(tag, "WIFI_EVENT_AP_STOP");
        break;

    case WIFI_EVENT_AP_STACONNECTED:
        ESP_LOGI(tag, "WIFI_EVENT_AP_STACONNECTED");
        break;

    case WIFI_EVENT_AP_STADISCONNECTED:
        ESP_LOGI(tag, "WIFI_EVENT_AP_STADISCONNECTED");
        break;

    case WIFI_EVENT_STA_START:
        ESP_LOGI(tag, "WIFI_EVENT_STA_START");
        break;

    case WIFI_EVENT_STA_CONNECTED:
        ESP_LOGI(tag, "WIFI_EVENT_STA_CONNECTED");
        break;

    case WIFI_EVENT_STA_DISCONNECTED:
        ESP_LOGI(tag, "WIFI_EVENT_STA_DISCONNECTED");

        // wifi_event_sta_disconnected_t *wifi_event_sta_disconnected = (wifi_event_sta_disconnected_t *)malloc(sizeof(wifi_event_sta_disconnected_t));
        // *wifi_event_sta_disconnected = *((wifi_event_sta_disconnected_t *)event_data);
        // printf("WIFI_EVENT_STA_DISCONNECTED, reason code %d\n", wifi_event_sta_disconnected->reason);

        // if (g_retry_number < MAX_CONNECTION_RETRIES)
        // {
        //     esp_wifi_connect();
        //     g_retry_number++;
        // }
        // else
        // {
        //     wifi_app_send_message(WIFI_APP_MSG_STA_DISCONNECTED);
        // }

        break;
    }
}

static void handleIPEvent(void *arg, esp_event_base_t event, int32_t eventID, void *eventData) {
    switch (eventID) {
    case IP_EVENT_STA_GOT_IP:
        ESP_LOGI(tag, "IP_EVENT_STA_GOT_IP");

        // wifi_app_send_message(WIFI_APP_MSG_STA_CONNECTED_GOT_IP);

        break;
    }
}

static void setupDefaultWifi(void) {
    ESP_ERROR_CHECK(esp_netif_init());

    wifi_init_config_t wifiConfig = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&wifiConfig));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    espSTANetworkInterface = esp_netif_create_default_wifi_sta();
    espAPNetworkInterface = esp_netif_create_default_wifi_ap();
}

static void setupWifiAP(void) {
    // SoftAP - WiFi access point configuration
    wifi_config_t apConfig =
        {
            .ap = {
                .ssid = wifiAP_SSID,
                .ssid_len = strlen(wifiAP_SSID),
                .password = wifiAPPassword,
                .channel = wifiAPChannel,
                .ssid_hidden = wifiAP_SSIDIsHidden,
                .authmode = WIFI_AUTH_WPA2_PSK,
                .max_connection = wifiAPMaxConnections,
                .beacon_interval = wifiAPBeaconInterval,
            },
        };

    // Configure DHCP for the AP
    esp_netif_ip_info_t apIPInfo;
    memset(&apIPInfo, 0x00, sizeof(apIPInfo));

    esp_netif_dhcps_stop(espAPNetworkInterface);   //must call this first
    inet_pton(AF_INET, wifiAP_IPAddress, &apIPInfo.ip); // Assign access point's static IP, GW, and netmask
    inet_pton(AF_INET, wifiAPGatewayAddress, &apIPInfo.gw);
    inet_pton(AF_INET, wifiAPNetmask, &apIPInfo.netmask);
    ESP_ERROR_CHECK(esp_netif_set_ip_info(espAPNetworkInterface, &apIPInfo)); // Statically configure the network interface
    ESP_ERROR_CHECK(esp_netif_dhcps_start(espAPNetworkInterface)); // Start the AP DHCP server (for connecting stations e.g. your mobile device)

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_APSTA));  // Setting the mode as Access Point / Station Mode
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &apConfig)); // Set our configuration
    ESP_ERROR_CHECK(esp_wifi_set_bandwidth(WIFI_IF_AP, wifiAPBandwidth)); // Our default bandwidth 20 MHz
    ESP_ERROR_CHECK(esp_wifi_set_ps(wifiSTAPowerSave)); // Power save set to "NONE"
}