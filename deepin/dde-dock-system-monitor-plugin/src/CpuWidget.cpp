//
// Created by pikachu on 7/20/19.
//

#include "CpuWidget.h"
#include "widget/SingleIcon.h"
#include "widget/SingleLabel.h"
#include <QLabel>
#include <QTimer>
#include <QtWidgets/QHBoxLayout>
#include <QPainter>
#include <QPen>
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

CpuWidget::CpuWidget(QWidget *parent) {
    auto icon = new SingleIcon(":/icon_cpu_dark.svg");
    m_cpu = new SingleLabel("---");
    auto hbox = new QHBoxLayout();
    hbox->addWidget(icon);
    hbox->addWidget(m_cpu);
    setLayout(hbox);
}

void CpuWidget::updateInfo() {

    unsigned long long workCpuTime = 0;
    unsigned long long totalCpuTime = 0;
    totalCpuTime = getTotalCpuTime(workCpuTime);
    auto cpuPercent = (workCpuTime - prevWorkCpuTime) * 100.0 / (totalCpuTime - prevTotalCpuTime);
    int cpu = cpuPercent;
    if(cpu == 0) {
        m_cpu->setText("---");
    } else if (cpu < 10) {
        m_cpu->setText(QString("0%1%").arg(cpu));
    } else {
        m_cpu->setText(QString("%1%").arg(cpu));
    }
    prevTotalCpuTime = totalCpuTime;
    prevWorkCpuTime = workCpuTime;
}

void CpuWidget::paintEvent(QPaintEvent *event) {
#ifdef DEBUG
    QPainter painter(this);
    QPen pen(Qt::red, 5, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);
    painter.drawRect(0, 0, this->width(), this->height());
#endif
    QWidget::paintEvent(event);
}
