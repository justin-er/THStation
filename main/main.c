#include <stdio.h>
#include <stdbool.h>

#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led_strip.h"
#include "dht.h"

#include "THReader.h"
#include "LEDController.h"

void app_main(void)
{
// start reading temperature and humidity
    // startTHReader();

// blink LED
    // struct LEDColor violet = {red: 10, green: 5, blue: 20 };
    // struct LEDColor green = {red: 20, green: 10, blue: 0 };
    // struct LEDColor red = {red: 10, green: 0, blue: 0 };

    // startLEDBlinking(500, red);
    // vTaskDelay(pdMS_TO_TICKS(5000));

    // stopLEDBlinking();
    // setLED(violet);
    // vTaskDelay(pdMS_TO_TICKS(5000));
        
    // clearLED();
    // startLEDBlinking(500, green);
}
