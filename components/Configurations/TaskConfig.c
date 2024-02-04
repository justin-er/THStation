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
