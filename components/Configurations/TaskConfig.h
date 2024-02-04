#include <stdio.h>

#ifndef TASK_CONFIG_H
#define TASK_CONFIG_H

typedef struct {
    int stackSize;
    int priority;
    int coreID;
} TaskConfig;

extern TaskConfig thReaderTaskConfig;
extern TaskConfig ledControllerTaskConfig;
extern TaskConfig wifiControllerTaskConfig;

#endif // TASK_CONFIG_H
