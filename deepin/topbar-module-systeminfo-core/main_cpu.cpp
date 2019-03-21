#include <iostream>
#include <cstring>
#include <vector>
#include <zconf.h>

typedef struct CpuStruct {
    long long unsigned idle, nonIdle;
} CpuStruct;

std::vector<CpuStruct> getCpuTimes() {
    std::vector<CpuStruct> times;

    // adapted from https://github.com/scaidermern/top-processes/blob/master/top_proc.c#L54
    FILE *file = fopen("/proc/stat", "r");
    if (file == NULL) {
        perror("Could not open stat file");
        return times;
    }

    char buffer[1024];
    memset(buffer, 1,
           1024); // initialise the buffer with known data but not 0 (null) so that the next while loop still works
    // skip the first line
    while (buffer[0] != '\n' && buffer != NULL) {
        buffer[0] = (char) fgetc(file);
    }

    while (buffer != NULL) {
        unsigned long long user = 0, nice = 0, system = 0, idle = 0;
        // added between Linux 2.5.41 and 2.6.33, see man proc(5)
        unsigned long long iowait = 0, irq = 0, softirq = 0, steal = 0, guest = 0, guestnice = 0;

        char *ret = fgets(buffer, sizeof(buffer) - 1, file);
        if (ret == NULL) {
            perror("Could not read stat file");
            fclose(file);
            return times;
        } else if (strncmp(buffer, "cpu", 3)) {
            break; // we got all of the cpu lines
        }

        sscanf(buffer,
               "cpu  %16llu %16llu %16llu %16llu %16llu %16llu %16llu %16llu %16llu %16llu",
               &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal, &guest, &guestnice);

        // sum everything up (except guest and guestnice since they are already included
        // in user and nice, see http://unix.stackexchange.com/q/178045/20626)

        CpuStruct cpu = {idle + iowait, user + nice + system + irq + softirq + steal};
        times.push_back(cpu);
    }

    fclose(file);
    return times;
}
/**
 * @brief getTotalCpuTime Read the data from /proc/stat and get the total time the cpu has been busy
 * @return The total cpu time
 */
unsigned long long getTotalCpuTime(unsigned long long &workTime)
{
    FILE* file = fopen("/proc/stat", "r");
    if (file == NULL) {
        perror("Could not open stat file");
        return 0;
    }

    char buffer[1024];
    unsigned long long user = 0, nice = 0, system = 0, idle = 0;
    // added between Linux 2.5.41 and 2.6.33, see man proc(5)
    unsigned long long iowait = 0, irq = 0, softirq = 0, steal = 0, guest = 0, guestnice = 0;

    char* ret = fgets(buffer, sizeof(buffer) - 1, file);
    if (ret == NULL) {
        perror("Could not read stat file");
        fclose(file);
        return 0;
    }
    fclose(file);

    sscanf(buffer,
           "cpu  %16llu %16llu %16llu %16llu %16llu %16llu %16llu %16llu %16llu %16llu",
           &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal, &guest, &guestnice);

    workTime = user + nice + system;

    // sum everything up (except guest and guestnice since they are already included
    // in user and nice, see http://unix.stackexchange.com/q/178045/20626)
    return user + nice + system + idle + iowait + irq + softirq + steal;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::vector<CpuStruct> cpuTimes = getCpuTimes();
    unsigned long long workCpuTime = 0;
    unsigned long long prevWorkCpuTime = 0;
    unsigned long long prevTotalCpuTime = 0;
    while(true) {
        auto totalCpuTime = getTotalCpuTime(workCpuTime);
        std::cout << "total cpu time: " << totalCpuTime << "work cpu time: "<< workCpuTime << std::endl;
        std::cout << workCpuTime * 100 / totalCpuTime << std::endl;
        auto cpuPercent = (workCpuTime - prevWorkCpuTime) * 100.0 / (totalCpuTime - prevTotalCpuTime);
        std::cout << "ret: " << cpuPercent << std::endl;
        prevTotalCpuTime = totalCpuTime;
        prevWorkCpuTime = workCpuTime;
        sleep(2);
    }
}