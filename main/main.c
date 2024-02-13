#include <stdio.h>
#include <stdbool.h>

#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led_strip.h"
#include "dht.h"
#include "nvs_flash.h"

#include "THReader.h"
#include "LEDController.h"
#include "WiFiController.h"

void app_main(void) {
// start reading temperature and humidity
    // startTHReader();

// blink LED
    // LEDColor violet = {red : 10, green : 5, blue : 20};
    // LEDColor green = {red : 20, green : 10, blue : 0};
    // LEDColor red = {red : 10, green : 0, blue : 0};

// startLEDBlinking(500, red);
// vTaskDelay(pdMS_TO_TICKS(5000));

// stopLEDBlinking();
// setLED(violet);
// vTaskDelay(pdMS_TO_TICKS(5000));

// clearLED();
    // startLEDBlinking(5ˆb00, green);

// WifiController
// Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

// Start Wifi
    startWifiController();
}
