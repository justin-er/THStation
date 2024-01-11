#include <stdio.h>

#ifndef TASK_CONFIG_H
#define TASK_CONFIG_H

struct TaskConfig {
    int stackSize;
    int priority;
    int coreID;
};

extern struct TaskConfig thReaderTaskConfig;
extern struct TaskConfig ledControllerTaskConfig;

#endif // TASK_CONFIG_H
