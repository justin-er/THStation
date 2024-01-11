#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_err.h"

#include "led_strip.h"
#include "led_strip_rmt.h"
#include "led_strip_spi.h"
#include "led_strip_types.h"
#include "led_strip_interface.h"

#include "GeneralConfig.h"
#include "GPIOConfig.h"
#include "LEDController.h"
#include "TaskConfig.h"

#define LED_STRIP_LED_NUMBERS 1

led_strip_handle_t led_strip;
TaskHandle_t ledTaskHandle = NULL;

// Function Prototypes
void blinkLEDHanlder(void *pvParameters);

led_strip_handle_t configure_led(void)
{
    // LED strip general initialization, according to your led board design
    led_strip_config_t strip_config = {
        .strip_gpio_num = GPIO_Default_RGB_LED,   // The GPIO that connected to the LED strip's data line
        .max_leds = LED_STRIP_LED_NUMBERS,        // The number of LEDs in the strip,
        .led_pixel_format = LED_PIXEL_FORMAT_GRB, // Pixel format of your LED strip
        .led_model = LED_MODEL_WS2812,            // LED strip model
        .flags.invert_out = false,                // whether to invert the output signal
    };

    // LED strip backend configuration: SPI
    led_strip_spi_config_t spi_config = {
        .clk_src = SPI_CLK_SRC_DEFAULT, // different clock source can lead to different power consumption
        .flags.with_dma = true,         // Using DMA can improve performance and help drive more LEDs
        .spi_bus = SPI2_HOST,           // SPI bus ID
    };

    // LED Strip object handle
    led_strip_handle_t led_strip;
    ESP_ERROR_CHECK(led_strip_new_spi_device(&strip_config, &spi_config, &led_strip));
    ESP_LOGI(TAG, "Created LED strip object with SPI backend");
    return led_strip;
}

void configLEDIfRequired(void) {
    if (led_strip == NULL) {
        led_strip = configure_led();
    }
}

void configLEDControllerTaskIfRequired(void) {
    static uint8_t ucParameterToPass;
    xTaskCreate(
        &blinkLEDHanlder,
        "LEDControllerTask",
        ledControllerTaskConfig.stackSize, 
        &ucParameterToPass,
        ledControllerTaskConfig.priority,
        &ledTaskHandle
    );
}

void clearLED(void) {
    configLEDIfRequired();
    ESP_ERROR_CHECK(led_strip_clear(led_strip));
    ESP_LOGI(TAG, "LED OFF!");
}

void blinkLED (uint period, struct LEDColor color) {
    vTaskResume(ledTaskHandle);
}

void blinkLEDHanlder(void *pvParameters) {
    configLEDIfRequired();

    bool led_on_off = false;

    // while (true)
    // {
    //     if (led_on_off) {
    //         for (int i = 0; i < LED_STRIP_LED_NUMBERS; i++) {
    //             ESP_ERROR_CHECK(led_strip_set_pixel(led_strip, i, color.red, color.green, color.blue));
    //         }
    //     } else {
    //         ESP_ERROR_CHECK(led_strip_clear(led_strip));
    //     }

    //     led_on_off = !led_on_off;
    //     vTaskDelay(pdMS_TO_TICKS(500));
    // }
}

void setLED(struct LEDColor color) {
    configLEDIfRequired();

    for (int i = 0; i < LED_STRIP_LED_NUMBERS; i++)
    {
        ESP_ERROR_CHECK(led_strip_set_pixel(led_strip, i, color.red, color.green, color.blue));
    }
}

