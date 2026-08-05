#ifndef VESSEL_TRACKER_H
#define VESSEL_TRACKER_H

#include <QObject>
#include <QDebug>

class GPSReceiver: public QObject
{
    Q_OBJECT

public:
    GPSReceiver(QObject *parent = nullptr): QObject(parent) {}

    void simulasiData()
    {
        emit posisiUpdate("KRI Diponegoro", -12.3456, 76.1012);
        emit posisiUpdate("KRI Nanggala", -12.8921, 112.1012);
        emit posisiUpdate("KRI Dr. Soeharso", -12.7829, 112.1038);

        emit koneksiHilang("KRI Nanggala");
    }
signals:
    void posisiUpdate(QString namaKapal, double lat, double lon);
    void koneksiHilang(QString namaKapal);
};


class ECDISDisplay: public QObject
{
    Q_OBJECT

public:
    ECDISDisplay(QObject *parent = nullptr) : QObject(parent) {}

public slots:
    void onPosisiUpdate(QString namaKapal, double lat, double lon)
    {
        qDebug() << "[ECDIS]" << namaKapal << " -> Lat:" << lat << ", Lon:" << lon;
    }

    void onKoneksiHilang(QString namaKapal)
    {
        qWarning() << "[WARNING] Koneksi hilang: " << namaKapal;
    }
};

#endif
