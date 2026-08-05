#include "temp_monitor.h"
#include "alarm_system.h"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    TemperatureMonitor tempMonitor;
    AlarmSystem alarmSystem;

    QObject::connect(&tempMonitor, &TemperatureMonitor::onReadTemperature, &alarmSystem, &AlarmSystem::tempReceiver);

    tempMonitor.readTemperature();

    return 0;
}
