#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <dht.h>

#include "GPIOConfig.h"
#include "TaskConfig.h"

void dht_test(void *pvParameters) {
    float temperature, humidity;

#ifdef CONFIG_EXAMPLE_INTERNAL_PULLUP
    gpio_set_pull_mode(GIOP_THD_Sensor, GPIO_PULLUP_ONLY);
#endif

    while (true) {
        if (dht_read_float_data(DHT_TYPE_AM2301, GIOP_THD_Sensor, &humidity, &temperature) == ESP_OK) {
            printf("Humidity: %.1f%% Temp: %.1fC\n", humidity, temperature);
        } else {
            printf("Could not read data from sensor\n");
        }
        // If you read the sensor data too often, it will heat up
        // http://www.kandrsmith.org/RJS/Misc/Hygrometers/dht_sht_how_fast.html
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void startTHReader(void) {
    xTaskCreate(
        &dht_test,
        "dht_test",
        thReaderTaskConfig.stackSize,
        NULL,
        thReaderTaskConfig.priority,
        NULL);
}

