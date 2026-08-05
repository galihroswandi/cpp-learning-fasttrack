#ifndef ALARM_SYSTEM_H
#define ALARM_SYSTEM_H

#include <QObject>
#include <QDebug>

class AlarmSystem: public QObject
{
    Q_OBJECT;

public:
    AlarmSystem(QObject* parent = nullptr): QObject(parent){};

public slots:
    void tempReceiver(double temp)
    {
        if(temp > 80)
            qCritical() << "[ALERT] Suhu kritis: " << temp;
        else
            qDebug() << "[OK] Suhu normal: " << temp;
    }
};

#endif // ALARM_SYSTEM_H
