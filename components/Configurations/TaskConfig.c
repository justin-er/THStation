#include <stdio.h>
#include "TaskConfig.h"

struct TaskConfig thReaderTaskConfig = {
    .stackSize = 4096,
    .priority = 1,
    .coreID = 2
};

struct TaskConfig ledControllerTaskConfig = {
    .stackSize = 1048,
    .priority = 0,
    .coreID = 2
};
