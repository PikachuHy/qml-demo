
#include <iostream>
#include <cstring>
#include <vector>
#include <zconf.h>
#include <proc/sysinfo.h>
int main() {

    while(true) {
        meminfo();
        auto memoryPercent = (kb_main_total - kb_main_available) * 100.0 / kb_main_total;
        auto swapPercent = kb_swap_used * 100.0 / kb_swap_total;
        std::cout << "mem: " << memoryPercent << " swap: " << swapPercent<<std::endl;
        sleep(2);
    }
}