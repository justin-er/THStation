#include <stdio.h>

struct LEDColor {
    uint red;
    uint green;
    uint blue;
};

void setLED(struct LEDColor color);
void blinkLED(uint period, struct LEDColor color);
void clearLED(void);