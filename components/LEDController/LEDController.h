#ifndef LEDController_h
#define LEDController_h

#include <stdio.h>

typedef struct LEDColor LEDColor;

void setLED(struct LEDColor color);
void startLEDBlinking(uint period, struct LEDColor color);
void stopLEDBlinking();
void clearLED(void);

typedef struct LEDColor {
    uint red;
    uint green;
    uint blue;
} LEDColor;

extern LEDColor redLED;
extern LEDColor greenLED;
extern LEDColor blueLED;

#endif
