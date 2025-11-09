#ifndef UTILS_H
#define UTILS_H

#include "monitor.h"
#include <vector>

std::vector<ProcessInfo> getProcessList();
float getTotalMemory();
float getUsedMemory();
float getCpuUsage();

#endif
