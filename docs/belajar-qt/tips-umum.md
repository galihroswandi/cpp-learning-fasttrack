# Tips Umum — C++ & Qt
Diarsipkan: 2026-05-29 (dari CATATAN_CPP.md — Tips Umum)

## CMake — Cara tambah Qt module

Setiap module Qt yang dipakai **wajib** disebut di 2 tempat di CMakeLists.txt:

```cmake
find_package(Qt6 REQUIRED COMPONENTS Widgets Network Concurrent)
target_link_libraries(app PRIVATE Qt6::Widgets Qt6::Network Qt6::Concurrent)
```

### Mapping fitur → module

| Kalau lo pakai... | Module |
|---|---|
| `QWidget`, `QPushButton`, `QLabel`, layout | `Widgets` |
| `QNetworkAccessManager`, HTTP request | `Network` |
| `QtConcurrent::run`, `QFutureWatcher` | `Concurrent` |
| `QSqlDatabase`, `QSqlQuery`, `QSqlTableModel` | `Sql` |
| `QGraphicsScene`, `QGraphicsItem` | `Widgets` (sudah include) |
| `QFile`, `QTimer`, `QString`, `QObject` | `Core` (auto-include) |
| `QChart`, `QLineSeries` | `Charts` |
| `QOpenGLWidget`, OpenGL rendering | `OpenGLWidgets` |
| `QQuickView`, QML | `Quick`, `Qml` |
| Plugin via `Q_PLUGIN_METADATA` | `Core` |
| Resource file `.qrc` | `set(CMAKE_AUTORCC ON)` (bukan module) |

Setelah edit `CMakeLists.txt`: **Build → Re-run CMake** di Qt Creator, atau hapus folder `build/` dan re-configure.

---

## Perbedaan mendasar JavaScript vs C++

| JavaScript | C++ |
|---|---|
| Tipe dinamis | Tipe statis, dikunci saat deklarasi |
| Garbage Collector otomatis | Manual `delete` atau smart pointer |
| `undefined` saat akses property tidak ada | `map[]` MEMBUAT entry baru — pakai `count()` |
| `for...of` | Range-based `for (const auto& x : container)` |
| `import` | `#include` |
| `class extends` | `class Child : public Parent` |
| Override otomatis | Butuh `virtual` (base) + `override` (child) eksplisit |
| `this.property` | `this->property` (via pointer) |
| Closure capture otomatis | Lambda capture eksplisit `[this]`, `[&]`, `[=]` |
| Event bubble otomatis ke parent | TIDAK otomatis — pakai event filter |
| String concat dengan `+` | `QString::arg()` atau `+` (operator overload) |
| `JSON.parse` / `JSON.stringify` | `QJsonDocument::fromJson` / `toJson` |
| `fetch` async/await | `QNetworkAccessManager` signal-based |
| `setInterval` / `setTimeout` | `QTimer::start()` / `QTimer::singleShot()` |

---

## Aturan compile yang sering kelewat

1. **MOC trigger**: class dengan `Q_OBJECT` wajib di file `.h`. MOC scan header, generate `moc_*.cpp` saat build.
2. **`set(CMAKE_AUTOMOC ON)`**: WAJIB di CMakeLists.txt supaya MOC jalan otomatis.
3. **`set(CMAKE_AUTORCC ON)`**: WAJIB kalau pakai `.qrc` resource file.
4. **`set(CMAKE_AUTOUIC ON)`**: WAJIB kalau pakai Qt Designer `.ui` file.
5. **Class dengan signal/slot di `.cpp` doang** → linker error `undefined reference to vtable`. Solusi: pindah definisi ke `.h`.

---

## Koordinat GPS — selalu `double`

- `float` cuma 7 digit presisi — error puluhan meter untuk koordinat global (lat/lon ±180).
- `double` 15-17 digit presisi — error sub-millimeter, aman untuk skala global.
- Sekalipun lo "yakin" precision-nya cukup, tetep pakai `double` — overhead RAM minimal di app desktop.

---

## Format output angka di Qt

```cpp
QString::number(3.14159, 'f', 2)               // "3.14" — fixed, 2 desimal
QString::number(3.14159, 'e', 3)               // "3.142e+00" — exponential
QString("%1°").arg(lat, 0, 'f', 4)             // arg version, 4 desimal
QString::asprintf("%.2f km", 12.34567)         // printf-style

// JANGAN pakai std::to_string(double) → trailing zeros (3.140000)
```

---

## Debugging tips

- `qDebug() << var` — auto format (string, int, QObject pointer, dll).
- `qDebug() << obj->metaObject()->className()` — runtime class name.
- `qDebug() << reply->errorString()` — human-readable error message.
- `Q_ASSERT(cond)` — assert di debug build, no-op di release.
- Set `QT_LOGGING_RULES="*.debug=true"` di env untuk enable semua qDebug.
- Qt Creator → Tools → Options → Debugger → enable "Show standard namespace" untuk smart pointer.

---

## Hal yang sering bikin frustasi pemula

1. **Lupa `setCentralWidget()`** di QMainWindow → window kosong walaupun widget udah dibikin.
2. **Stack-allocated widget** keluar scope → window kosong/crash. Selalu `new QWidget(parent)`.
3. **Lupa parent saat `new`** → memory leak kalau widget di-destroy tapi child gak.
4. **Signal/slot signature mismatch** → connection silent fail. Qt5 style (`&Class::signal`) catch ini di compile.
5. **MOC gak generate** karena class di file `.cpp` → vtable error. Pindah ke `.h`.
6. **`QFile::Text` flag lupa** untuk text file → line ending corrupted di Windows.
7. **Worker thread akses widget** → crash. Pakai `QFutureWatcher` + signal ke UI thread.
