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

void app_main(void)
{
    startTHReader();
}
