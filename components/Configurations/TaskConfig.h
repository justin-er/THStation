#include <stdio.h>

#ifndef TaskConfig_h
#define TaskConfig_h

typedef struct {
    int stackSize;
    int priority;
    int coreID;
} TaskConfig;

extern TaskConfig thReaderTaskConfig;
extern TaskConfig ledControllerTaskConfig;
extern TaskConfig wifiControllerTaskConfig;
extern TaskConfig httpServerTaskConfig;
extern TaskConfig httpServerMonitorTaskConfig;

#endif 