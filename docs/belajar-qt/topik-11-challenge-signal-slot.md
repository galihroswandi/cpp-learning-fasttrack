# Topik 11 — Challenge: Signal & Slot
Diarsipkan: 2026-05-29 (dari CATATAN_CPP.md — Fase 1 Challenge 1)
Project: [temp_monitor/](../../temp_monitor/)

## Ringkasan konsep
Challenge pertama: bikin sensor temperatur yang emit signal saat suhu berubah, dan display yang receive signal untuk update tampilan. Tujuannya internalize konsep loose coupling (sensor gak tau ada display) dan type-safe connection (compile-time check). Pakai `QCoreApplication` karena console-based, gak butuh widget.

## Analogi JavaScript/React
- Mirip dengan **EventEmitter** di Node.js — `emitter.emit('temperatureChange', value)` lalu `emitter.on('temperatureChange', handler)`.
- Bedanya: Qt connection wajib match signature signal dengan slot di compile-time (typo = error). Node EventEmitter cuma string-based.

## Kode inti
```cpp
// sensor.h
class TempSensor : public QObject {
    Q_OBJECT
public:
    void baca() { emit suhuBerubah(28.5); }
signals:
    void suhuBerubah(double celsius);
};

// display.h
class Display : public QObject {
    Q_OBJECT
public slots:
    void onSuhu(double c) { qDebug() << "Suhu:" << c; }
};

// main.cpp
int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);
    TempSensor sensor;
    Display display;
    QObject::connect(&sensor, &TempSensor::suhuBerubah,
                     &display, &Display::onSuhu);
    sensor.baca();
    return 0;   // bukan app.exec() karena bukan event-loop based
}
```

## Aturan penting
- **Signal wajib return `void`** — gak boleh return nilai apapun.
- **`Q_OBJECT` ≠ `public QObject`** — Q_OBJECT adalah instruksi MOC, public QObject adalah inheritance. Wajib dua-duanya.
- **Kapan pakai `QCoreApplication`:** console/CLI app, server, daemon.
- **Kapan pakai `QApplication`:** ada widget (GUI).
- **Common mistake:** `app.exec()` di console app sederhana yang gak butuh event loop → blocking selamanya.

## Catatan tambahan
- Untuk app dengan timer/network/async, **wajib** `app.exec()` (start event loop). Untuk app sync sederhana, cukup `return 0`.
- Connect bisa dari signal ke signal: forward signal ke parent (mirip event re-emit).
