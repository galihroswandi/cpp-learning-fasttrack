# Topik 8 — Qt: QObject & Signal/Slot
Diarsipkan: 2026-05-29 (dari CATATAN_CPP.md — Sesi 8)

## Ringkasan konsep
Signal/slot adalah mekanisme komunikasi antar object di Qt — sender **gak perlu tahu** siapa penerimanya (loose coupling), dan koneksi **type-safe di compile time** (typo nama signal/slot = compile error). Untuk pakai signal/slot, class wajib **(1)** inherit `QObject`, **(2)** punya macro `Q_OBJECT` di awal body class, dan **(3)** definisi di file `.h` supaya **MOC (Meta-Object Compiler)** bisa generate kode signal/slot otomatis.

## Analogi JavaScript/React
| JavaScript | Qt |
|---|---|
| `addEventListener('event', fn)` | `QObject::connect(sender, signal, receiver, slot)` |
| `emit('event', data)` | `emit namaSignal(data)` |
| Typo nama event = runtime error | Typo nama signal = compile error |
| Event listener tidak type-checked | Argument signal/slot wajib match tipenya |

## Kode inti
```cpp
// sensor.h
class SensorGPS : public QObject {
    Q_OBJECT                                    // WAJIB
public:
    explicit SensorGPS(QObject* parent = nullptr) : QObject(parent) {}
    void baca() {
        emit posisiDiperbarui(-6.2088, 106.8456);
    }
signals:                                        // signal selalu return void
    void posisiDiperbarui(double lat, double lon);
};

// main.cpp — connect Qt5/6 style (type-safe)
QObject::connect(&sensor, &SensorGPS::posisiDiperbarui,
                 &display, &Display::onPosisi);

// Hindari Qt4 style (string-based, typo = runtime error)
// QObject::connect(&sensor, SIGNAL(...), &display, SLOT(...));
```

## Aturan penting
- **Kapan pakai signal/slot:** komunikasi antar object yang harus loose coupling (sensor → display, model → view).
- **Kapan TIDAK pakai signal/slot:** call function biasa cukup — jangan over-engineer untuk komunikasi tightly-coupled internal.
- **Common mistake:** lupa `Q_OBJECT` macro → linker error `undefined reference to vtable`. Atau definisi class di file `.cpp` bukan `.h` → MOC gak proses.
- **Common mistake:** signal return value selain `void` → compile error.

## Catatan tambahan
- `Q_OBJECT` ≠ inherit `QObject`. Inherit ngasih lo machinery dasar; Q_OBJECT instruksi ke MOC untuk generate kode signal/slot/meta-object.
- Qt log levels:
  - `qDebug() << "info"` — debug info
  - `qWarning() << "..."` — peringatan, tidak fatal
  - `qCritical() << "..."` — error serius
  - `qFatal() << "..."` — fatal, program abort
- Lambda bisa jadi slot: `connect(btn, &QPushButton::clicked, [&]() { ... });`
- Disconnect manual: `disconnect(sender, signal, receiver, slot);` — biasanya gak perlu kalau parent-child relationship.
