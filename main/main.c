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
    startTHReader();
    setLED(30, 30, 30);
}
