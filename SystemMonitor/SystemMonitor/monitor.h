#ifndef MONITOR_H
#define MONITOR_H

#include <vector>
#include <string>

struct ProcessInfo {
    int pid;
    std::string name;
    float cpuUsage;
    float memUsage;
};

class SystemMonitor {
public:
    void update();
    std::vector<ProcessInfo> getProcesses() const;
    float getTotalMemory() const;
    float getUsedMemory() const;
    float getCpuLoad() const;

private:
    std::vector<ProcessInfo> processes;
    float totalMemory;
    float usedMemory;
    float cpuLoad;
};

#endif
