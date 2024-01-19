#include <stdio.h>

typedef struct LEDColor LEDColor;

void setLED(struct LEDColor color);
void startLEDBlinking(uint period, struct LEDColor color);
void stopLEDBlinking();
void clearLED(void);

struct LEDColor {
    uint red;
    uint green;
    uint blue;
};
