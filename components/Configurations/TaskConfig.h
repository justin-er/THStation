#include <stdio.h>

typedef struct {
    int stackSize;
    int priority;
    int coreID;
} TaskConfig;

TaskConfig thReaderTaskConfig = {
    .stackSize = 4096,
    .priority = 1,
    .coreID = 2
};
