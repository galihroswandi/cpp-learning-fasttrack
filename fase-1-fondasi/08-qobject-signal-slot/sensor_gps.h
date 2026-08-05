#ifndef SENSOR_GPS_H
#define SENSOR_GPS_H

#include <QObject>
#include <QDebug>

class SensorGPS: public QObject
{
    Q_OBJECT

public:
    explicit SensorGPS(QObject *parent = nullptr): QObject(parent){}

    void simulasiBaca()
    {
        qDebug() << "GPS Membaca posisi...";
        emit posisiDiperbarui(-6.2088, 106.8456);
        emit posisiDiperbarui(-7.2575, 112.7521);
        emit errorSensor("AIS Tidak Terbaca");
    }

signals:
    void posisiDiperbarui(double lat, double lon);
    void errorSensor(QString pesan);
};

class LayarECDIS: public QObject
{
    Q_OBJECT

public:
    explicit LayarECDIS(QObject *parent = nullptr): QObject(parent){}

public slots:
    void onPosisiDiperbarui(double lat, double lon)
    {
        qDebug() << "[ECDIS] Posisi baru: " << lat << lon;
    }

    void onErrorSensor(QString pesan)
    {
        qDebug() << "[ECDIS] Sensor error: " << pesan;
    }

    void slotInt(int x)
    {
        qDebug() << "[ECDIS] Nilai x: " << x;
    }
};

#endif