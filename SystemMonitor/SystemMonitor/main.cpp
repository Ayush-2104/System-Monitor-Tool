#include <unistd.h>  // For sleep()
#include "monitor.h"
#include "ui.h"

int main() {
    SystemMonitor monitor;
    UI ui;

    while (true) {
        monitor.update();
        ui.display(monitor);
        sleep(2); // Refresh every 2 seconds
    }

    return 0;
}
