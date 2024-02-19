#ifndef LEDController_h
#define LEDController_h

#include <stdio.h>

typedef struct LEDColor LEDColor;

void setLED(struct LEDColor color);
void startLEDBlinking(uint32_t period, struct LEDColor color);
void stopLEDBlinking();
void clearLED(void);

typedef struct LEDColor {
    uint32_t red;
    uint32_t green;
    uint32_t blue;
} LEDColor;

extern LEDColor redLED;
extern LEDColor greenLED;
extern LEDColor blueLED;

#endif
