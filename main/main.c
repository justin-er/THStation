#include <stdio.h>
#include <stdbool.h>

#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "App/THReader/THReader.h"

void app_main(void)
{
    startTHReader();
}
