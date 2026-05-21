# Catatan Belajar C++ untuk ECDIS

Ringkasan materi dari sesi belajar. Background: web dev JS/TS yang belajar C++ untuk kontribusi ke project ECDIS (Electronic Chart Display and Information System).

---

## Sesi 1 — Syntax Dasar & Tipe Statis

### Konsep utama
Di JavaScript, tipe variabel bisa berubah kapan saja. Di C++, tipe **dikunci saat deklarasi** dan tidak bisa berubah. Error tipe ketahuan saat **compile**, bukan saat program jalan.

### Tipe dasar

| C++ | JS padanan | Keterangan |
|---|---|---|
| `int` | `number` (bulat) | Bilangan bulat |
| `double` | `number` (desimal) | Desimal 64-bit, untuk koordinat GPS |
| `float` | - | Desimal 32-bit, presisi lebih rendah |
| `bool` | `boolean` | `true`/`false`, disimpan sebagai 1/0 |
| `std::string` | `string` | Butuh `#include <string>` |

### Contoh

```cpp
#include <iostream>
#include <string>

int main() {
    int kecepatan = 12;
    double latitude = -6.2088;   // selalu double untuk koordinat GPS
    bool berlayar = true;
    std::string nama_kapal = "KM Nusantara";

    std::cout << nama_kapal << std::endl;
    std::cout << std::boolalpha << berlayar << std::endl; // tampil "true", bukan "1"

    return 0;
}
```

### Format output

```cpp
#include <iomanip>

std::cout << std::fixed << std::setprecision(4) << latitude;  // 4 angka desimal
std::cout << std::setw(3) << std::setfill('0') << heading;   // leading zero: 045
```

### Compile & run
```bash
g++ main.cpp -o output && ./output
```

---

## Sesi 2 — Fungsi & Parameter

### Konsep utama
Setiap fungsi C++ wajib deklarasikan **tipe return** dan **tipe setiap parameter**. Fungsi harus dideklarasikan sebelum dipanggil — gunakan **function prototype** jika definisi ada di bawah `main`.

### Syntax

```cpp
// Prototype — "janji" ke compiler
double hitungJarak(double lat1, double lon1, double lat2, double lon2);
void tampilkanPosisi(double lat, double lon);   // void = tidak return apa-apa

int main() {
    double d = hitungJarak(-6.2, 106.8, -7.2, 112.7);
    tampilkanPosisi(-6.2, 106.8);
    return 0;
}

double hitungJarak(double lat1, double lon1, double lat2, double lon2) {
    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;
    return std::sqrt(dlat * dlat + dlon * dlon);  // butuh #include <cmath>
}
```

### Kapan pakai void vs return type
- `void` → fungsi hanya punya efek samping (print, tulis file, ubah state)
- return type → fungsi menghasilkan nilai yang dibutuhkan caller

### Implicit type conversion
`int` bisa otomatis dikonversi ke `double` (widening, aman). Sebaliknya tidak — `double` ke `int` memotong desimal dan compiler bisa warning.

---

## Sesi 3 — Pointer & Referensi

### Konsep utama
Setiap variabel punya **alamat di RAM**. Pointer menyimpan alamat itu. Referensi adalah alias (nama lain) untuk variabel yang sama.

### Dua operator penting

| Operator | Nama | Arti |
|---|---|---|
| `&` | address-of | "ambil alamat variabel ini" |
| `*` | dereference | "pergi ke alamat ini, ambil nilainya" |

### Pointer

```cpp
double latitude = -6.2088;
double* ptr = &latitude;    // ptr menyimpan alamat latitude
                             // * di sini = bagian dari TIPE (double*)

*ptr = -7.2575;             // * di sini = dereference operator
                             // sama dengan: latitude = -7.2575
```

### Referensi

```cpp
double latitude = -6.2088;
double& ref = latitude;     // ref adalah alias untuk latitude
ref = -7.2575;              // sama persis dengan: latitude = -7.2575
```

### Perbedaan pointer vs referensi

| | Pointer `*` | Referensi `&` |
|---|---|---|
| Bisa null | Ya | Tidak |
| Bisa diarahkan ulang | Ya | Tidak |
| Perlu dereference | Ya (`*ptr`) | Tidak (langsung pakai) |
| Kapan dipakai | Data opsional, array dinamis | Parameter fungsi |

### Pass by reference di fungsi

```cpp
// Tanpa referensi — nilai di caller TIDAK berubah
void tambahOffset(double lat) { lat += 0.5; }

// Dengan referensi — nilai di caller IKUT berubah
void tambahOffset(double& lat) { lat += 0.5; }

// const& — baca saja, tidak ubah, tidak copy
void tampilkan(const double& lat) { std::cout << lat; }
```

### Aturan pointer dan inheritance
- `Vessel* v = new Warship(...)` → **valid** (child IS-A parent)
- `Warship* v = new Vessel(...)` → **invalid** (parent bukan child)

---

## Sesi 4 — OOP: Class, Constructor, Destructor

### Konsep utama
Class di C++ mirip JS ES6, tapi:
- Default access adalah **private** (bukan public seperti JS)
- Ada **destructor** (`~ClassName`) yang dipanggil saat objek keluar scope
- **Lifetime objek dikontrol oleh scope `{}`**, bukan garbage collector

### Access modifier

| Modifier | Akses dari luar class | Akses dari class anak |
|---|---|---|
| `private` | Tidak | Tidak |
| `protected` | Tidak | Ya |
| `public` | Ya | Ya |

### Syntax

```cpp
class Vessel {
private:
    std::string nama;
    double latitude, longitude;
    double kecepatan;

public:
    // Constructor — member initializer list (cara idiomatik C++)
    Vessel(std::string n, double lat, double lon)
        : nama(n), latitude(lat), longitude(lon), kecepatan(0.0) {
        std::cout << "[+] Vessel dibuat: " << nama << std::endl;
    }

    // Destructor
    ~Vessel() {
        std::cout << "[-] Vessel dihapus: " << nama << std::endl;
    }

    // Setter dengan validasi
    void setKecepatan(double k) {
        if (k < 0) return;   // tolak nilai tidak valid
        kecepatan = k;
    }

    // Getter
    double getLatitude() { return latitude; }

    void tampilkan() {
        std::cout << "Kapal: " << nama << " | Speed: " << kecepatan << std::endl;
    }
};
```

### Scope dan destructor

```cpp
int main() {
    {
        Vessel kapal("KM A", -6.2, 106.8);
        kapal.tampilkan();
    }  // destructor KM A dipanggil DI SINI

    {
        Vessel kapal2("KM B", -7.2, 112.7);
    }  // destructor KM B dipanggil DI SINI

    return 0;
}
```

### Pass object ke fungsi
Selalu gunakan `const&` untuk objek agar tidak membuat salinan:
```cpp
void cetakKapal(const Vessel& v) { v.tampilkan(); }  // tidak ada copy
// bukan:
void cetakKapal(Vessel v) { v.tampilkan(); }  // membuat copy, destructor 2x
```

---

## Sesi 5 — Inheritance & Polymorphism

### Konsep utama
C++ mendukung inheritance seperti JS, tapi polymorphism membutuhkan keyword **`virtual`** secara eksplisit. Tanpa `virtual`, memanggil method lewat pointer induk selalu jalan method induk.

### Syntax inheritance

```cpp
class Vessel {
protected:
    std::string nama;

public:
    Vessel(std::string n) : nama(n) {}
    virtual ~Vessel() {}           // WAJIB virtual jika jadi base class
    virtual void tampilkan() {     // virtual = bisa di-override
        std::cout << "Kapal: " << nama << std::endl;
    }
};

class Warship : public Vessel {
private:
    int jumlah_meriam;

public:
    Warship(std::string n, int meriam)
        : Vessel(n), jumlah_meriam(meriam) {}  // panggil constructor induk

    void tampilkan() override {    // override = eksplisit menimpa method induk
        Vessel::tampilkan();       // panggil versi induk dulu (seperti super.tampilkan())
        std::cout << "Meriam: " << jumlah_meriam << std::endl;
    }
};
```

### Polymorphism via virtual

```cpp
Vessel* armada[3];
armada[0] = new Vessel("KM Nusantara");
armada[1] = new Warship("KRI Diponegoro", 76);
armada[2] = new PassengerShip("Ferry B", 200);

for (int i = 0; i < 3; i++) {
    armada[i]->tampilkan();  // memanggil method yang TEPAT untuk setiap tipe
}
```

### Urutan constructor & destructor
- **Constructor:** induk dipanggil **duluan**, lalu anak (membangun dari bawah ke atas)
- **Destructor:** anak dipanggil **duluan**, lalu induk (membongkar dari atas ke bawah)

### Kenapa destructor harus virtual
Tanpa `virtual ~Vessel()`, pemanggilan `delete` via pointer induk hanya menjalankan destructor induk. Destructor anak tidak pernah jalan → resource leak.

---

## Sesi 6 — STL: vector, map, string

### Konsep utama
STL menyediakan struktur data siap pakai. Gunakan ini daripada implementasi sendiri.

| JavaScript | C++ STL | Header |
|---|---|---|
| `Array` / `[]` | `std::vector<T>` | `<vector>` |
| `Map` / `Object` | `std::map<K,V>` | `<map>` |
| `string` | `std::string` | `<string>` |

### vector

```cpp
#include <vector>

std::vector<std::string> kapal;
kapal.push_back("KM Nusantara");   // tambah di akhir
kapal.push_back("KRI Diponegoro");

std::cout << kapal.size() << std::endl;  // jumlah elemen

// Loop — selalu pakai const& untuk efisiensi
for (const std::string& nama : kapal) {
    std::cout << nama << std::endl;
}

// JANGAN push_back di dalam range-based for loop — undefined behavior!
```

### map

```cpp
#include <map>

std::map<std::string, double> kecepatan;
kecepatan["KM Nusantara"] = 14.5;

// map selalu terurut by key (alfabetis) — berbeda dari JS Map
// Akses key yang tidak ada MEMBUAT entry baru dengan nilai default!

// Cara aman cek key:
if (kecepatan.count("KM Nusantara") > 0) {
    std::cout << kecepatan["KM Nusantara"] << std::endl;
}

// Loop map
for (const auto& entry : kecepatan) {
    std::cout << entry.first << ": " << entry.second << std::endl;
    //          ^ key                   ^ value
}
```

### Format double ke string (untuk log/string building)

```cpp
#include <sstream>
#include <iomanip>

std::ostringstream oss;
oss << std::fixed << std::setprecision(1) << 14.5678;
std::string hasil = oss.str();  // "14.6"

// Jangan pakai std::to_string(double) untuk format — selalu 6 desimal
```

---

## Sesi 7 — Memory Management

### Konsep utama
- Variabel lokal dialokasikan di **stack** — otomatis dihapus saat keluar scope
- `new` mengalokasikan di **heap** — harus manual `delete`, atau pakai smart pointer
- Lupa `delete` = **memory leak**
- Early return / exception melewati `delete` → pakai smart pointer

### Raw pointer (hindari di kode modern)

```cpp
Sensor* raw = new Sensor("GPS");
raw->baca();
delete raw;   // wajib — tidak ada yang auto-cleanup

// Bahaya:
delete raw;
raw->baca();  // use-after-free → segfault / undefined behavior
```

### Smart pointer (gunakan ini)

```cpp
#include <memory>

// unique_ptr — satu pemilik, auto-delete saat keluar scope
std::unique_ptr<Sensor> uptr = std::make_unique<Sensor>("Radar");
uptr->baca();
// tidak perlu delete — otomatis saat scope berakhir

// Tidak bisa di-copy, hanya bisa dipindah:
auto uptr2 = std::move(uptr);  // uptr sekarang null

// shared_ptr — bisa banyak pemilik, hapus saat semua selesai
std::shared_ptr<Sensor> sptr1 = std::make_shared<Sensor>("AIS");
{
    std::shared_ptr<Sensor> sptr2 = sptr1;  // reference count = 2
    sptr1.use_count();  // 2
}  // sptr2 hancur, reference count = 1 — sensor BELUM dihapus
// sptr1 hancur di akhir scope → count = 0 → sensor dihapus
```

### Ambil raw pointer dari smart pointer (non-owning)

```cpp
Sensor* raw = uptr.get();   // .get() — bukan ->get()
raw->baca();                 // gunakan, tapi JANGAN delete
```

### Kapan pakai yang mana

| | `unique_ptr` | `shared_ptr` |
|---|---|---|
| Kepemilikan | Satu pemilik | Banyak pemilik |
| Contoh ECDIS | Sensor fisik (Radar, AIS) | Data navigasi dibaca banyak modul |
| Overhead | Minimal | Ada reference counter |

### RAII — Resource Acquisition Is Initialization
Smart pointer adalah implementasi RAII: resource dipegang objek yang umurnya dikontrol scope. Destructor selalu jalan, bahkan saat exception atau early return.

### Destructor chain otomatis
```cpp
// Saat unique_ptr<Manager> keluar scope:
// unique_ptr → hapus Manager → hapus vector → hapus setiap unique_ptr<Sensor>
//            → hapus setiap Sensor
// Semua tanpa satu pun delete eksplisit
```

---

## Sesi 8 — Qt Basics: QObject & Signal/Slot

### Konsep utama
Signal/slot adalah sistem komunikasi antar objek di Qt. Sender tidak perlu tahu siapa yang menerima — loose coupling seperti event emitter di JS, tapi type-safe di compile time.

| JavaScript | Qt Signal/Slot |
|---|---|
| `addEventListener('event', fn)` | `QObject::connect(sender, signal, receiver, slot)` |
| `emit('event', data)` | `emit namaSignal(data)` |
| Runtime type check | Compile-time type check |
| String-based event name | Function pointer — typo = error |

### Syarat class Qt
Setiap class yang pakai signal/slot **wajib**:
1. Inherit dari `QObject`
2. Punya macro `Q_OBJECT` di awal class body
3. Didefinisikan di file `.h` (diproses moc)

### Syntax

```cpp
#include <QObject>
#include <QDebug>

class SensorGPS : public QObject {
    Q_OBJECT

public:
    explicit SensorGPS(QObject* parent = nullptr) : QObject(parent) {}

    void simulasiBaca() {
        emit posisiDiperbarui(-6.2088, 106.8456);  // kirim signal
    }

signals:
    void posisiDiperbarui(double lat, double lon);  // deklarasi saja, moc yang implement
};

class ECDISDisplay : public QObject {
    Q_OBJECT

public:
    explicit ECDISDisplay(QObject* parent = nullptr) : QObject(parent) {}

public slots:
    void onPosisiDiperbarui(double lat, double lon) {
        qDebug() << "Posisi:" << lat << lon;
    }
};
```

### Connect signal ke slot

```cpp
// main.cpp
SensorGPS sensor;
ECDISDisplay display;

// Qt5/6 style — type-safe, pointer ke fungsi
QObject::connect(&sensor,  &SensorGPS::posisiDiperbarui,
                 &display, &ECDISDisplay::onPosisiDiperbarui);

sensor.simulasiBaca();  // emit signal → slot dipanggil otomatis

// Disconnect
QObject::disconnect(&sensor, &SensorGPS::posisiDiperbarui,
                    &display, &ECDISDisplay::onPosisiDiperbarui);
```

### Aturan signal/slot
- Slot boleh punya **lebih sedikit parameter** dari signal — extra param dibuang
- Tipe harus cocok — implicit conversion bisa terjadi diam-diam (hati-hati!)
- Satu signal bisa connect ke **banyak slot** (many-to-many)
- `emit` memanggil semua slot yang terhubung secara sinkron

### Qt log levels

```cpp
qDebug()    << "info debug";      // development info
qInfo()     << "info biasa";      // runtime info
qWarning()  << "ada masalah";     // peringatan — tidak fatal
qCritical() << "error serius";    // error tapi program masih jalan
qFatal()    << "fatal error";     // program abort
```

### Build Qt project
Qt butuh build system khusus — tidak bisa pakai `g++` langsung.
- Gunakan **Qt Creator** → Build → Run (`Ctrl+R`)
- Output ada di "Application Output" panel

---

## Sesi 9 — Qt Widgets & Event Handling

### Konsep utama
Qt Widgets adalah library GUI Qt. Semua elemen UI adalah object yang dihubungkan via signal/slot. Widget disusun menggunakan layout manager.

### QApplication vs QCoreApplication
- `QCoreApplication` — untuk console/non-GUI app (event loop saja)
- `QApplication` — inherit dari QCoreApplication, tambah font, palette, window management. **Wajib untuk GUI.**

### Widget dasar

| Widget | Fungsi | Padanan HTML |
|---|---|---|
| `QLabel` | Tampilkan teks/gambar | `<span>`, `<p>` |
| `QPushButton` | Tombol klik | `<button>` |
| `QLineEdit` | Input teks satu baris | `<input type="text">` |
| `QMainWindow` | Jendela utama | `<body>` |

### Structure dasar MainWindow

```cpp
// mainwindow.h
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
private slots:
    void onTombolKlik();
private:
    QLabel* label;
    QPushButton* tombol;
};

// mainwindow.cpp
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    QWidget* central = new QWidget(this);
    setCentralWidget(central);           // wajib untuk QMainWindow

    QVBoxLayout* layout = new QVBoxLayout(central);
    label  = new QLabel("teks awal", this);
    tombol = new QPushButton("Klik", this);
    layout->addWidget(label);
    layout->addWidget(tombol);

    connect(tombol, &QPushButton::clicked, this, &MainWindow::onTombolKlik);
}

void MainWindow::onTombolKlik() {
    label->setText("Diklik!");
}
```

### Layout manager

```cpp
QVBoxLayout* vbox = new QVBoxLayout();   // susun vertikal (column)
QHBoxLayout* hbox = new QHBoxLayout();   // susun horizontal (row)

// Nested layout — JANGAN beri parent yang sama dengan parent layout
QHBoxLayout* hbox = new QHBoxLayout();  // tanpa parent
vbox->addLayout(hbox);                   // ownership via addLayout
// BUKAN: new QHBoxLayout(central) jika central sudah punya layout
```

### Qt ownership model — tidak perlu delete manual
```cpp
// Widget dengan parent — otomatis dihapus saat parent dihapus
QLabel* label = new QLabel("teks", this);  // 'this' adalah parent
// Saat MainWindow dihapus → semua child dihapus otomatis
```

### QString formatting
```cpp
QString text = QString("Posisi #%1: Lat %2, Lon %3")
               .arg(updateCount)          // %1
               .arg(lat)                  // %2
               .arg(lon);                 // %3

// Ambil teks dari QLineEdit:
QString input = lineEdit->text();

// Update label:
label->setText(text);
```

### Pola uiUpdate() — centralize UI refresh
```cpp
void uiUpdate() {
    labelNama->setText(namaKapal);
    labelPosisi->setText(QString("Lat %1").arg(lat));
    // semua update UI di satu tempat
    // panggil dari semua slot yang mengubah state
}
```

---

## Sesi 10 — QPainter & Rendering Dasar

### Konsep utama
`QPainter` adalah API drawing Qt untuk render langsung ke widget — garis, bentuk, teks, polygon. Di ECDIS dipakai untuk chart display, plot posisi kapal, dan route rendering.

### Flow rendering
```
Data berubah → update() → Qt schedule → paintEvent() dipanggil → gambar ulang
```
**Jangan panggil `paintEvent` langsung** — selalu lewat `update()`.

### Setup

```cpp
// chartwidget.h
class ChartWidget : public QWidget {
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent* event) override;
};

// chartwidget.cpp
void ChartWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  // tepi halus
    // ... drawing di sini
}
```

### Sistem koordinat
- `(0, 0)` = pojok kiri atas widget
- X bertambah ke kanan, Y bertambah ke bawah
- Konversi geografis → pixel: Y perlu dikali negatif karena latitude tumbuh ke atas

```cpp
int px = (int)((lon - lonRef) * scale + width() / 2);
int py = (int)((lat + latRef) * (-scale) + height() / 2);
```

### QPainter API dasar

```cpp
// Background
painter.fillRect(rect(), QColor(20, 60, 120));

// Garis
painter.setPen(QPen(QColor(r, g, b), tebal, Qt::SolidLine));
painter.drawLine(x1, y1, x2, y2);

// Polygon (segitiga kapal)
QPolygon ship;
ship << QPoint(px, py-12) << QPoint(px-8, py+8) << QPoint(px+8, py+8);
painter.setBrush(QColor(255, 200, 0));
painter.setPen(Qt::NoPen);
painter.drawPolygon(ship);

// Lingkaran / danger zone
painter.setPen(QPen(QColor(255, 50, 50), 2, Qt::DashLine));
painter.setBrush(Qt::NoBrush);
painter.drawEllipse(QPoint(px, py), 40, 40);

// Teks
painter.setPen(Qt::white);
painter.drawText(x, y, "teks");
painter.drawText(10, 20, QString("Update: %1").arg(count));
```

### QTimer — gerakkan kapal otomatis

```cpp
#include <QTimer>

// Setup di constructor
QTimer* timer = new QTimer(this);
connect(timer, &QTimer::timeout, this, &ChartWidget::moveShip);
timer->start(800);   // emit timeout setiap 800ms

// Slot
void ChartWidget::moveShip() {
    shipLon += 0.05;
    updateCount++;
    update();        // trigger repaint
}

// Toggle stop/start
void ChartWidget::toggleTimer() {
    if (timer->isActive()) timer->stop();
    else timer->start(800);
}
```

### Padanan JS
| JS | Qt |
|---|---|
| `canvas.getContext('2d')` | `QPainter painter(this)` |
| `ctx.fillStyle = 'blue'` | `painter.setBrush(QColor(...))` |
| `ctx.fillRect(...)` | `painter.fillRect(...)` |
| `ctx.arc(...)` | `painter.drawEllipse(...)` |
| `setInterval(fn, 800)` | `QTimer` + `start(800)` |
| `setState() / render()` | `update()` → `paintEvent()` |

---

## Fase 1 — Challenge Review (2026-05-18)

### Challenge 1: Signal & Slot — LULUS ✓

**Project:** `temp_monitor/` — TemperatureMonitor emit suhu → AlarmSystem cetak alert

**Poin yang dipelajari ulang:**
- Signal **wajib** return `void` — bukan `double` atau tipe lain
- `Q_OBJECT` ≠ `public QObject`: Q_OBJECT adalah instruksi ke **MOC** untuk generate kode signal/slot. Tanpa Q_OBJECT, MOC tidak bekerja → signal/slot tidak bisa dipakai
- `app.exec()` = blocking event loop — untuk app sederhana yang tidak butuh event loop, cukup `return 0`
- `QCoreApplication` untuk console/non-GUI, `QApplication` untuk GUI

**Qt4-style connect (lama, hindari):**
```cpp
// String-based — typo tidak ketahuan saat compile, error baru muncul runtime
QObject::connect(&sensor, SIGNAL(posisiDiperbarui(double, double)),
                 &display, SLOT(onPosisiDiperbarui(double, double)));
```

**Qt5/6-style connect (pakai ini):**
```cpp
// Pointer to member function — typo = compile error, type-safe
QObject::connect(&sensor, &Sender::namaSignal, &receiver, &Receiver::namaSlot);
```

---

### Challenge 2: Widget & Layout — LULUS ✓

**Project:** `temp_conversion/` — konverter Celsius ke Fahrenheit dengan QMainWindow

**Poin yang dipelajari ulang:**
- `setCentralWidget(central)` wajib untuk QMainWindow sebelum bisa taruh widget
- `QHBoxLayout` bisa di-nest ke dalam `QVBoxLayout` via `addLayout()` — ownership otomatis berpindah
- `QDoubleValidator` — validator input angka, mencegah user ketik huruf
- Semua widget sebaiknya diberi parent `this` saat konstruksi — Qt reparent otomatis via layout tapi inkonsisten kalau tidak ditulis

**Kenapa widget selalu pointer (`QLabel*`, bukan `QLabel`):**
1. Qt ownership model — widget dialokasikan di heap supaya parent bisa delete saat dihancurkan
2. Kalau nilai biasa (stack), widget dihapus saat keluar scope — terlalu cepat
3. `QObject` copy constructor **di-delete** — Qt melarang salinan widget, wajib pakai pointer

**Type promotion dalam ekspresi campuran:**
`double × int` → int dipromote ke double → hasil double → tidak ada integer division
```cpp
inputUserDouble * 9 / 5   // inputUserDouble=double → *9 → double → /5 → double ✓
9 / 5                      // int/int → integer division = 1 ✗ (jangan tulis ini)
9.0 / 5                    // double/int → double = 1.8 ✓ (cara eksplisit)
```

**Format angka ke QString:**
```cpp
QString::number(nilai, 'f', 2)                          // 'f' = fixed, 2 = 2 desimal
QString("Hasil: %1 °F").arg(QString::number(nilai, 'f', 2))
```

---

### Challenge 3: QPainter — LULUS ✓

**Project:** `qt_painter/` — widget custom dengan background, lingkaran transparan, dan teks

**Konsep utama QPainter:**
- `paintEvent` = sesi menggambar. Semua drawing WAJIB di dalam sini
- Jangan panggil `paintEvent()` langsung — panggil `update()` untuk minta Qt jadwalkan di waktu yang tepat
- `update()` ≈ `requestAnimationFrame()` di JS — Qt batch beberapa `update()` menjadi satu `paintEvent`
- `QPainter painter(this)` hanya valid di dalam `paintEvent` — di luar sesi ini widget tidak dalam mode drawing

**Posisi dinamis — selalu pakai `width()/2` dan `height()/2`:**
```cpp
painter.drawEllipse(QPoint(width()/2, height()/2), 60, 60);  // ikut resize ✓
painter.drawEllipse(QPoint(300, 200), 60, 60);                // hardcoded, tidak ikut resize ✗
```

**API QPainter penting:**
```cpp
painter.setRenderHint(QPainter::Antialiasing);           // tepi halus
painter.fillRect(rect(), QColor(20, 30, 60));            // background — rect() selalu pas ukuran widget
painter.setPen(QPen(warna, tebal, Qt::SolidLine));       // atur garis tepi
painter.setBrush(Qt::NoBrush);                           // isi transparan
painter.setBrush(QBrush(QColor(0, 150, 255, 80)));       // isi semi-transparan (alpha 0-255)
painter.drawEllipse(QPoint(cx, cy), rx, ry);             // lingkaran
painter.drawLine(x1, y1, x2, y2);                        // garis
painter.drawText(QPoint(x, y), "teks");                  // teks
```

**Padanan JS Canvas:**
| JS Canvas | Qt QPainter |
|---|---|
| `requestAnimationFrame(render)` | `update()` |
| fungsi `render()` | `paintEvent()` |
| `ctx.strokeStyle` | `painter.setPen(...)` |
| `ctx.fillStyle` | `painter.setBrush(...)` |
| `ctx.arc(...)` | `painter.drawEllipse(...)` |

---

## Fase 2 — Intermediate

### Topik 1: QTimer — SELESAI ✓

**Project:** `timer_basic/` — counter dengan start/stop/reset dan singleShot

**Padanan JS:**
| JavaScript | Qt |
|---|---|
| `setInterval(fn, ms)` | `timer->start(ms)` + connect ke slot |
| `clearInterval(id)` | `timer->stop()` |
| `setTimeout(fn, ms)` | `QTimer::singleShot(ms, this, slot/lambda)` |

**Aturan penting:**
- Beri parent `this` saat buat QTimer — ikut dihapus saat widget dihapus
- Jangan pakai `sleep()` — membekukan event loop, UI tidak responsif
- `stop()` tidak reset — `count` tetap di nilai terakhir
- Update UI langsung di slot reset, jangan tunggu tick berikutnya

**Lambda capture di C++ vs JS closure:**
```cpp
// JS — closure otomatis akses variabel luar
const fn = () => label.setText("x");  // otomatis bisa akses label

// C++ — harus eksplisit capture
auto fn = [this]() { label->setText("x"); };  // [this] = izinkan akses member
auto fn2 = []()   { label->setText("x"); };  // ERROR — label tidak dikenal
```

**`QTimer::singleShot` dengan lambda:**
```cpp
QTimer::singleShot(5000, this, [this]() {
//                        ^^^^  ^^^^^^
//                  context Qt  C++ lambda capture
    label->setText("5 detik berlalu");
});
```
- `this` argumen Qt: kalau widget dihapus sebelum timeout, lambda tidak dipanggil
- `[this]` lambda capture: izinkan akses `label`, `count`, dll via `this`

---

### Topik 2: Animasi QTimer + QPainter — SELESAI ✓

**Project:** `ball_animation/` — bola memantul di 4 sisi dengan dx/dy velocity

**Pattern animasi Qt:**
```
QTimer (16ms) → onMoveBall() → update state → update() → paintEvent() → gambar ulang
```

**Velocity vector — lebih baik dari string arah:**
```cpp
int dx = 3;   // + = kanan, - = kiri
int dy = 2;   // + = bawah, - = atas

// Bounce: balik tanda saat menyentuh dinding
if (ballX - radius < 0 || ballX + radius > width())  dx = -dx;
if (ballY - radius < 0 || ballY + radius > height()) dy = -dy;
```
- `int dx/dy` lebih aman dari `QString arah` — typo ketahuan saat compile
- Urutan: **gerak dulu, baru cek boundary** — cek posisi baru, bukan posisi lama

**Jangan pakai `==` untuk boundary check:**
```cpp
if (ballX == 0)  // BERBAHAYA — bola loncat 3px per frame, bisa skip nilai 0
if (ballX < 0)   // BENAR — range check, tidak bisa dilewati
```

**Inisialisasi posisi awal harus valid:**
```cpp
// SALAH — ballX=0 langsung trigger boundary, dx balik terus
ballX(0), radius(30)    // 0 - 30 = -30 < 0 → stuck

// BENAR — mulai dari dalam area widget
ballX(100), radius(30)  // 100 - 30 = 70 > 0 → aman
```

**16ms ≈ 60fps** — standar animasi smooth. Di bawah 30fps (>33ms) terasa patah-patah.

---

### Topik 3: Model/View Architecture — SELESAI ✓

**Project:** `modelview_basic/` — list kota dengan tambah/hapus, dua view satu model

**Tiga peran:**
| Peran | Tanggung jawab | Padanan JS |
|---|---|---|
| **Model** | Simpan dan kelola data | Array / state |
| **View** | Tampilkan data dari model | Komponen React |
| **Delegate** | Kontrol cara tiap item dirender | Custom cell renderer |

**Flow kerja:**
```
Model punya data → View tanya model → View render
Data berubah → Model emit signal → Semua view terhubung update otomatis
```

**Koneksi model ke view — satu baris:**
```cpp
listView->setModel(model);   // view subscribe ke semua perubahan model
comboBox->setModel(model);   // view kedua, data sama, tampilan berbeda
// Tambah/hapus di model → kedua view update otomatis via signal/slot
```

**Operasi model:**
```cpp
// Tambah item di akhir
int row = model->rowCount();
model->insertRow(row);
model->setData(model->index(row), teks);

// Hapus item — selalu guard dulu
int idx = comboBox->currentIndex();
if (idx < 0) return;          // guard: model kosong → idx = -1
model->removeRow(idx);

QModelIndex idx = listView->currentIndex();
if (!idx.isValid()) return;   // guard: tidak ada yang dipilih
model->removeRow(idx.row());
```

**`QModelIndex` vs `int`:**
- `int` — hanya row, cukup untuk list flat (QComboBox)
- `QModelIndex` — bawa row + column + parent, support tree/table, punya `isValid()`

---

### Topik 4: Event Handling Lanjutan — SELESAI ✓

**Project:** `modelview_basic/` — tambah keyPressEvent, mouseMoveEvent, closeEvent

**Event handling via override (bukan connect):**
| Web Event | Qt Override |
|---|---|
| `keydown` | `keyPressEvent(QKeyEvent* e)` |
| `mousemove` | `mouseMoveEvent(QMouseEvent* e)` |
| window close | `closeEvent(QCloseEvent* e)` |

**Aturan wajib — panggil parent jika tidak handle sendiri:**
```cpp
void MyWidget::keyPressEvent(QKeyEvent* e) {
    if (e->key() == Qt::Key_Escape) {
        // handle sendiri
    } else {
        QMainWindow::keyPressEvent(e);  // WAJIB — supaya Tab, Space, dll tetap jalan
    }
}
```
Tanpa memanggil parent: semua key yang tidak kamu tangkap jadi "ditelan" — Tab, Space, shortcut bawaan Qt semua mati.

**closeEvent — accept vs ignore:**
```cpp
void MainWindow::closeEvent(QCloseEvent* event) {
    if (yakinKeluar) event->accept();  // window ditutup
    else             event->ignore();  // window tetap terbuka, seolah X tidak ditekan
}
```
Padanan JS: `window.confirm()` — dialog yes/no yang memblok.

**Mouse tracking — tidak aktif secara default:**
```cpp
// Default: mouseMoveEvent hanya dipanggil saat tombol mouse ditekan (drag)
// Untuk tracking bebas:
setMouseTracking(true);           // untuk MainWindow
central->setMouseTracking(true);  // untuk central widget
```

**Event Filter — intercept event dari child widget:**
```cpp
// Di constructor:
central->installEventFilter(this);

// Implementasi:
bool MainWindow::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::MouseMove) {
        QMouseEvent* me = static_cast<QMouseEvent*>(event);
        statusBar()->showMessage(QString("x:%1 y:%2").arg(me->pos().x()).arg(me->pos().y()));
    }
    return QMainWindow::eventFilter(obj, event);  // lempar ke parent
}
```
Di Qt, event tidak otomatis bubble ke parent seperti di web — pakai event filter untuk intercept event dari child.

---

### Topik 5: QSS / Theming — SELESAI ✓

**Project:** `qss_basic/` — dark/light theme toggle dengan QSS

**Tiga cara apply QSS (luas ke sempit):**
```cpp
qApp->setStyleSheet("...");         // seluruh app
mainWindow->setStyleSheet("...");   // window + semua child
button->setStyleSheet("...");       // widget ini saja (≈ inline style di CSS)
```

**Selector QSS:**
```css
QPushButton { }              /* semua QPushButton */
QPushButton:hover { }        /* pseudo-state — WAJIB ditulis eksplisit, tidak ada default */
QPushButton:pressed { }
QPushButton#btnDanger { }    /* hanya widget dengan objectName "btnDanger" */
```

**Spesifisitas:** `#objectName` > `WidgetType` > inherited dari parent

**setObjectName — wajib untuk selector `#id`:**
```cpp
btnDanger->setObjectName("btnDanger");  // baru bisa pakai QPushButton#btnDanger di QSS
```

**Raw string literal untuk QSS panjang:**
```cpp
setStyleSheet(R"(
    QPushButton { border-radius: 6px; }
)");
// R"(...)" = padanan template literal JS ` ` — bisa multiline, tidak perlu \n
```

**Perbedaan dari CSS web:**
- Pseudo-state (`hover`, `pressed`) tidak ada default visual — harus ditulis semua
- `border-radius` butuh `border` juga dideklarasikan
- Tidak ada class selector (`.class`) — pakai `#objectName` sebagai gantinya

---

### Topik 6: File I/O — SELESAI ✓

**Project:** `fileio_basic/` — text editor sederhana dengan buka/simpan file

**Dua class utama:**
- `QFile` — handle file (open, close, exists, remove)
- `QTextStream` — baca/tulis teks (seperti readline di Node.js)

**Pattern baca file:**
```cpp
QFile file(path);
if (!file.open(QFile::ReadOnly | QFile::Text)) return;  // selalu cek!
QTextStream in(&file);
editor->setPlainText(in.readAll());
file.close();
```

**Pattern tulis file:**
```cpp
QFile file(path);
if (!file.open(QFile::WriteOnly | QFile::Text)) return;
QTextStream out(&file);
out << editor->toPlainText();
file.close();
editor->document()->setModified(false);  // reset flag setelah simpan
```

**`QFile::Text` — konversi line ending antar OS:**
- Windows: `\r\n`, Linux/Mac: `\n`
- Dengan `Text`: Qt auto-konversi saat baca/tulis
- Tanpa `Text`: karakter `\r` ekstra muncul di akhir setiap baris

**Save vs Save As pattern:**
```cpp
void onSimpan() {
    if (filePath.isEmpty()) {
        // belum punya file → Save As (muncul dialog)
        filePath = QFileDialog::getSaveFileName(...);
        if (filePath.isEmpty()) return;
    }
    // sudah punya file → Save langsung tanpa dialog
    // tulis ke filePath
}
```

**closeEvent + isModified:**
```cpp
void MainWindow::closeEvent(QCloseEvent* event) {
    if (editor->document()->isModified()) {
        // tanya user
        if (yakin) { onSimpan(); event->accept(); }
        else        { event->ignore(); }  // batalkan close
    } else {
        event->accept();  // tidak ada perubahan, langsung tutup
    }
}
// PENTING: setModified(false) setelah simpan — tidak reset otomatis!
```

**File dialog:**
```cpp
// Buka
QString path = QFileDialog::getOpenFileName(this, "Judul", "", "Text (*.txt);;All (*)");
// Simpan
QString path = QFileDialog::getSaveFileName(this, "Judul", "", "Text (*.txt)");
// Selalu cek isEmpty() — return "" kalau user cancel
```

---

### Topik 7: Networking — SELESAI ✓

**Project:** `networking_basic/` — HTTP GET ke httpbin.org dengan QNetworkAccessManager

**CMake — wajib tambah Network module:**
```cmake
find_package(Qt6 REQUIRED COMPONENTS Widgets Network)
target_link_libraries(app PRIVATE Qt6::Widgets Qt6::Network)
```

**Tiga class utama:**
- `QNetworkAccessManager` — satu instance per app, seperti `fetch` itu sendiri
- `QNetworkRequest` — berisi URL dan headers
- `QNetworkReply` — response object, emit signal `finished` saat data datang

**Pattern request:**
```cpp
// Setup — satu kali di constructor
manager = new QNetworkAccessManager(this);
connect(manager, &QNetworkAccessManager::finished,
        this, &MainWindow::onReplyFinished);  // fired untuk SETIAP reply

// Send request — tidak blocking, langsung return
QNetworkRequest request;
request.setUrl(QUrl("https://api.example.com/data"));
manager->get(request);
```

**Pattern handle response:**
```cpp
void MainWindow::onReplyFinished(QNetworkReply* reply) {
    if (reply->error() != QNetworkReply::NoError) {
        // handle error
        reply->deleteLater();  // WAJIB di setiap exit path
        return;
    }
    QString data = QString::fromUtf8(reply->readAll());
    reply->deleteLater();  // deleteLater, bukan delete — masih di call stack Qt
}
```

**Penting:**
- `manager->get()` ≈ `fetch()` tanpa `await` — async, tidak blocking
- `finished` signal dipanggil untuk **setiap** reply — termasuk kalau ada 2 request bersamaan
- `deleteLater()` bukan `delete` — reply masih di call stack saat slot dipanggil
- Disable tombol saat request in-flight untuk cegah double request

**Padanan JS:**
| JavaScript | Qt |
|---|---|
| `fetch(url)` | `manager->get(QNetworkRequest(url))` |
| `.then(res => res.text())` | `connect(manager, &QNAM::finished, slot)` |
| `res.ok` | `reply->error() == NoError` |
| `res.text()` | `QString::fromUtf8(reply->readAll())` |

---

**Kapan pakai Model/View:**
- List, tabel, tree dari data yang bisa berubah
- Data yang sama perlu tampil di beberapa tempat sekaligus
- Jangan pakai untuk satu `QLabel` statis — terlalu overkill

---

## Tips Umum

### Compile flags berguna
```bash
g++ -std=c++14 file.cpp -o output     # C++14 (untuk make_unique)
g++ -Wall file.cpp -o output           # tampilkan semua warning
g++ -std=c++14 -Wall file.cpp -o output
```

### Hal yang berbeda dari JavaScript

| JavaScript | C++ |
|---|---|
| Tipe dinamis | Tipe statis, dikunci saat deklarasi |
| GC otomatis | Manual `delete` atau smart pointer |
| `undefined` saat akses property tidak ada | `map[]` membuat entry baru! |
| `for...of` | Range-based `for (const auto& x : container)` |
| `import` | `#include` |
| `class extends` | `class Child : public Parent` |
| Override otomatis | Butuh `virtual` dan `override` eksplisit |
| `this.property` | `this->property` (via pointer) |

### Koordinat GPS — selalu `double`
`float` hanya 7 digit presisi — bisa beda **puluhan meter** untuk koordinat global. Di ECDIS selalu gunakan `double` untuk latitude/longitude.
