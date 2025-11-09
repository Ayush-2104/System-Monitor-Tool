#include "utils.h"
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <unistd.h>

float getTotalMemory() {
    std::ifstream meminfo("/proc/meminfo");
    std::string line;
    float total = 0;
    while (std::getline(meminfo, line)) {
        if (line.find("MemTotal") != std::string::npos) {
            std::istringstream iss(line);
            std::string key;
            float value;
            std::string unit;
            iss >> key >> value >> unit;
            total = value / 1024;
            break;
        }
    }
    return total;
}

float getUsedMemory() {
    std::ifstream meminfo("/proc/meminfo");
    std::string line;
    float total = 0, free = 0;
    while (std::getline(meminfo, line)) {
        if (line.find("MemTotal") != std::string::npos) {
            std::istringstream iss(line);
            std::string key;
            float value;
            std::string unit;
            iss >> key >> value >> unit;
            total = value;
        } else if (line.find("MemAvailable") != std::string::npos) {
            std::istringstream iss(line);
            std::string key;
            float value;
            std::string unit;
            iss >> key >> value >> unit;
            free = value;
            break;
        }
    }
    return (total - free) / 1024;
}

float getCpuUsage() {
    std::ifstream stat("/proc/stat");
    std::string line;
    std::getline(stat, line);
    std::istringstream iss(line);
    std::string cpu;
    long user, nice, system, idle;
    iss >> cpu >> user >> nice >> system >> idle;
    long total = user + nice + system + idle;
    return 100.0 * (user + nice + system) / total;
}

std::vector<ProcessInfo> getProcessList() {
    std::vector<ProcessInfo> list;
    DIR* dir = opendir("/proc");
    struct dirent* entry;

    while ((entry = readdir(dir)) != nullptr) {
        if (isdigit(entry->d_name[0])) {
            int pid = atoi(entry->d_name);
            std::string path = "/proc/" + std::string(entry->d_name);
            std::ifstream status(path + "/status");
            std::ifstream stat(path + "/stat");

            std::string name;
            float mem = 0;
            float cpu = 0;

            if (status) {
                std::string line;
                while (std::getline(status, line)) {
                    if (line.find("Name:") == 0) {
                        name = line.substr(6);
                    }
                    if (line.find("VmRSS:") == 0) {
                        std::istringstream iss(line.substr(7));
                        iss >> mem;
                        mem /= 1024; // Convert to MB
                        break;
                    }
                }
            }

            if (stat) {
                long utime, stime;
                std::string dummy;
                stat >> dummy >> dummy >> dummy >> dummy >> dummy >> dummy >> dummy >> dummy >> dummy >> dummy;
                stat >> utime >> stime;
                cpu = (utime + stime) / sysconf(_SC_CLK_TCK);
            }

            if (!name.empty()) {
                list.push_back({pid, name, cpu, mem});
            }
        }
    }
    closedir(dir);
    return list;
}
