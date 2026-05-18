#include <QCoreApplication>
#include "vessel_tracker.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    GPSReceiver gpsReceiver;
    ECDISDisplay ecdisDisplay;

    QObject::connect(&gpsReceiver, &GPSReceiver::posisiUpdate, &ecdisDisplay, &ECDISDisplay::onPosisiUpdate);
    QObject::connect(&gpsReceiver, &GPSReceiver::koneksiHilang, &ecdisDisplay, &ECDISDisplay::onKoneksiHilang);

    gpsReceiver.simulasiData();

    // SensorGPS sensor;
    // LayarECDIS layar;

    // QObject::connect(&sensor, &SensorGPS::posisiDiperbarui, &layar, &LayarECDIS::onPosisiDiperbarui);
    // QObject::connect(&sensor, &SensorGPS::errorSensor, &layar, &LayarECDIS::onErrorSensor);
    // QObject::connect(&sensor, &SensorGPS::posisiDiperbarui, &layar, &LayarECDIS::slotInt);

    // sensor.simulasiBaca();

    return 0;
}