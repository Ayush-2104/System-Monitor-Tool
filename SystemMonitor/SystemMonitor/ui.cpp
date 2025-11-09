#include "ui.h"
#include <iostream>
#include <iomanip>

void UI::display(const SystemMonitor& monitor) {
    system("clear");
    std::cout << "CPU Load: " << monitor.getCpuLoad() << "%\n";
    std::cout << "Memory Usage: " << monitor.getUsedMemory() << " / " << monitor.getTotalMemory() << " MB\n\n";
    std::cout << std::left << std::setw(10) << "PID"
              << std::setw(25) << "Name"
              << std::setw(10) << "CPU%"
              << std::setw(10) << "MEM%" << "\n";

    for (const auto& proc : monitor.getProcesses()) {
        std::cout << std::setw(10) << proc.pid
                  << std::setw(25) << proc.name
                  << std::setw(10) << proc.cpuUsage
                  << std::setw(10) << proc.memUsage << "\n";
    }
}
