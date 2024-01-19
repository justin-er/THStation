#include <stdio.h>
#include "TaskConfig.h"

struct TaskConfig thReaderTaskConfig = {
    .stackSize = 4096,
    .priority = 1,
    .coreID = 1
};

struct TaskConfig ledControllerTaskConfig = {
    .stackSize = 4096,
    .priority = 0,
    .coreID = 1
};
