#include <stdio.h>
#include "TaskConfig.h"

TaskConfig thReaderTaskConfig = {
    .stackSize = 4096,
    .priority = 1,
    .coreID = 1
};

TaskConfig ledControllerTaskConfig = {
    .stackSize = 4096,
    .priority = 0,
    .coreID = 1
};

TaskConfig wifiControllerTaskConfig = {
    .stackSize = 4096,
    .priority = 5,
    .coreID = 0
};

TaskConfig httpServerTaskConfig = {
    .stackSize = 8192,
    .priority = 4,
    .coreID = 0
};

TaskConfig httpServerMonitorTaskConfig = {
    .stackSize = 4096,
    .priority = 3,
    .coreID = 0
};
