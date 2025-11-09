#include "monitor.h"
#include "utils.h"
#include <fstream>
#include <sstream>
#include <unistd.h>

void SystemMonitor::update() {
    processes = getProcessList();
    totalMemory = getTotalMemory();
    usedMemory = getUsedMemory();
    cpuLoad = getCpuUsage();
}

std::vector<ProcessInfo> SystemMonitor::getProcesses() const {
    return processes;
}

float SystemMonitor::getTotalMemory() const {
    return totalMemory;
}

float SystemMonitor::getUsedMemory() const {
    return usedMemory;
}

float SystemMonitor::getCpuLoad() const {
    return cpuLoad;
}
