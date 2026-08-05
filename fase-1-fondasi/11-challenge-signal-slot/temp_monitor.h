#ifndef TEMP_MONITOR_H
#define TEMP_MONITOR_H

#include <QObject>
#include <QDebug>

class TemperatureMonitor: public QObject
{
    Q_OBJECT

public:
    explicit TemperatureMonitor(QObject* parent = nullptr): QObject(parent){};

    void readTemperature()
    {
        qDebug() << "[Temp-Monitor] Suhu terbaca : " << temp;
        emit onReadTemperature(temp);
    };

signals:
    void onReadTemperature(double temp);

protected:
    double temp = 87.5;

};

#endif
