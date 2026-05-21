# Catatan Belajar C++ & Qt

Background: web dev JS/TS yang belajar C++ untuk kontribusi ke project ECDIS.

---

## Daftar Isi

### Sesi 1–10: C++ Dasar & Qt Dasar
- [Sesi 1 — Syntax Dasar & Tipe Statis](#sesi-1)
- [Sesi 2 — Fungsi & Parameter](#sesi-2)
- [Sesi 3 — Pointer & Referensi](#sesi-3)
- [Sesi 4 — OOP: Class, Constructor, Destructor](#sesi-4)
- [Sesi 5 — Inheritance & Polymorphism](#sesi-5)
- [Sesi 6 — STL: vector, map, string](#sesi-6)
- [Sesi 7 — Memory Management](#sesi-7)
- [Sesi 8 — Qt: QObject & Signal/Slot](#sesi-8)
- [Sesi 9 — Qt: Widgets & Layout](#sesi-9)
- [Sesi 10 — Qt: QPainter & Rendering](#sesi-10)

### Fase 1: Challenge Review
- [Challenge 1 — Signal & Slot](#c1)
- [Challenge 2 — Widget & Layout](#c2)
- [Challenge 3 — QPainter](#c3)

### Fase 2: Intermediate
- [Topik 1 — QTimer](#f2t1)
- [Topik 2 — Animasi QTimer + QPainter](#f2t2)
- [Topik 3 — Model/View Architecture](#f2t3)
- [Topik 4 — Event Handling Lanjutan](#f2t4)

### Fase 3: Advanced
- [Topik 5 — QSS / Theming](#f3t5)
- [Topik 6 — File I/O](#f3t6)
- [Topik 7 — Networking](#f3t7)
- [Topik 8 — Multithreading](#f3t8)

### [Tips Umum](#tips)

---

## Sesi 1 — Syntax Dasar & Tipe Statis {#sesi-1}

Di JavaScript, tipe variabel bisa berubah kapan saja. Di C++, tipe **dikunci saat deklarasi**. Error tipe ketahuan saat **compile**, bukan saat runtime.

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

## Sesi 2 — Fungsi & Parameter {#sesi-2}

Setiap fungsi C++ wajib deklarasikan **tipe return** dan **tipe setiap parameter**. Fungsi harus dideklarasikan sebelum dipanggil — gunakan **function prototype** jika definisi ada di bawah `main`.

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

- `void` → fungsi hanya punya efek samping (print, tulis file, ubah state)
- return type → fungsi menghasilkan nilai yang dibutuhkan caller
- `int` bisa otomatis dikonversi ke `double` (widening, aman). Sebaliknya tidak.

---

## Sesi 3 — Pointer & Referensi {#sesi-3}

Setiap variabel punya **alamat di RAM**. Pointer menyimpan alamat itu. Referensi adalah alias untuk variabel yang sama.

| Operator | Nama | Arti |
|---|---|---|
| `&` | address-of | "ambil alamat variabel ini" |
| `*` | dereference | "pergi ke alamat ini, ambil nilainya" |

```cpp
double latitude = -6.2088;
double* ptr = &latitude;    // ptr menyimpan alamat latitude
*ptr = -7.2575;             // sama dengan: latitude = -7.2575

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
void tambahOffset(double lat) { lat += 0.5; }   // caller TIDAK berubah
void tambahOffset(double& lat) { lat += 0.5; }  // caller IKUT berubah
void tampilkan(const double& lat) { ... }        // baca saja, tidak copy
```

- `Vessel* v = new Warship(...)` → valid (child IS-A parent)
- `Warship* v = new Vessel(...)` → invalid (parent bukan child)

---

## Sesi 4 — OOP: Class, Constructor, Destructor {#sesi-4}

Class di C++ mirip JS ES6, tapi default access adalah **private** dan ada **destructor**.

| Modifier | Akses dari luar | Akses dari anak |
|---|---|---|
| `private` | Tidak | Tidak |
| `protected` | Tidak | Ya |
| `public` | Ya | Ya |

```cpp
class Vessel {
private:
    std::string nama;
    double latitude, longitude, kecepatan;

public:
    Vessel(std::string n, double lat, double lon)
        : nama(n), latitude(lat), longitude(lon), kecepatan(0.0) {}

    ~Vessel() { std::cout << "[-] Dihapus: " << nama << std::endl; }

    void setKecepatan(double k) { if (k >= 0) kecepatan = k; }
    double getLatitude() { return latitude; }
};
```

- Destructor dipanggil saat objek keluar scope `{}`
- Selalu gunakan `const&` untuk pass object ke fungsi — hindari copy

---

## Sesi 5 — Inheritance & Polymorphism {#sesi-5}

Polymorphism di C++ membutuhkan keyword **`virtual`** secara eksplisit.

```cpp
class Vessel {
public:
    virtual ~Vessel() {}
    virtual void tampilkan() { std::cout << "Kapal" << std::endl; }
};

class Warship : public Vessel {
public:
    void tampilkan() override {
        Vessel::tampilkan();  // seperti super.tampilkan()
        std::cout << "Warship" << std::endl;
    }
};

// Polymorphism
Vessel* armada[2];
armada[0] = new Vessel("KM A");
armada[1] = new Warship("KRI B", 76);
for (auto v : armada) v->tampilkan();  // memanggil method yang TEPAT
```

- **Constructor:** induk dipanggil duluan, lalu anak
- **Destructor:** anak dipanggil duluan, lalu induk
- Tanpa `virtual ~Vessel()`: destructor anak tidak pernah jalan → resource leak

---

## Sesi 6 — STL: vector, map, string {#sesi-6}

| JavaScript | C++ STL | Header |
|---|---|---|
| `Array` / `[]` | `std::vector<T>` | `<vector>` |
| `Map` / `Object` | `std::map<K,V>` | `<map>` |
| `string` | `std::string` | `<string>` |

```cpp
// vector
std::vector<std::string> kapal;
kapal.push_back("KM Nusantara");
for (const std::string& nama : kapal) { std::cout << nama << std::endl; }
// JANGAN push_back di dalam range-based for loop!

// map — selalu terurut by key, akses key tidak ada MEMBUAT entry baru!
std::map<std::string, double> kecepatan;
kecepatan["KM Nusantara"] = 14.5;
if (kecepatan.count("KM Nusantara") > 0) { ... }  // cara aman cek key
for (const auto& entry : kecepatan) {
    std::cout << entry.first << ": " << entry.second << std::endl;
}

// Format double ke string
std::ostringstream oss;
oss << std::fixed << std::setprecision(1) << 14.5678;
std::string hasil = oss.str();  // "14.6" — jangan pakai std::to_string(double)
```

---

## Sesi 7 — Memory Management {#sesi-7}

- **Stack** — variabel lokal, otomatis dihapus saat keluar scope
- **Heap** — `new`, harus manual `delete` atau pakai smart pointer
- Lupa `delete` = **memory leak**

```cpp
// Raw pointer — hindari di kode modern
Sensor* raw = new Sensor("GPS");
raw->baca();
delete raw;

// unique_ptr — satu pemilik, auto-delete saat keluar scope
auto uptr = std::make_unique<Sensor>("Radar");
uptr->baca();
auto uptr2 = std::move(uptr);  // uptr sekarang null

// shared_ptr — banyak pemilik, hapus saat semua selesai
auto sptr1 = std::make_shared<Sensor>("AIS");
{ auto sptr2 = sptr1; }  // count=2, lalu 1 — belum dihapus
// sptr1 hancur → count=0 → dihapus

// Ambil raw pointer tanpa ownership
Sensor* raw = uptr.get();  // JANGAN delete raw ini
```

| | `unique_ptr` | `shared_ptr` |
|---|---|---|
| Kepemilikan | Satu pemilik | Banyak pemilik |
| Overhead | Minimal | Ada reference counter |

**RAII:** resource dipegang objek yang umurnya dikontrol scope. Destructor selalu jalan, bahkan saat exception.

---

## Sesi 8 — Qt: QObject & Signal/Slot {#sesi-8}

Signal/slot = komunikasi antar objek. Sender tidak perlu tahu siapa penerima — loose coupling, type-safe di compile time.

| JavaScript | Qt |
|---|---|
| `addEventListener('event', fn)` | `QObject::connect(sender, signal, receiver, slot)` |
| `emit('event', data)` | `emit namaSignal(data)` |
| Runtime type check | Compile-time type check |

### Syarat class Qt
1. Inherit dari `QObject`
2. Punya macro `Q_OBJECT` di awal class body
3. Didefinisikan di file `.h` (diproses MOC)

> `Q_OBJECT` ≠ `public QObject`. Q_OBJECT adalah instruksi ke **MOC** untuk generate kode signal/slot.

```cpp
class SensorGPS : public QObject {
    Q_OBJECT
public:
    explicit SensorGPS(QObject* parent = nullptr) : QObject(parent) {}
    void baca() { emit posisiDiperbarui(-6.2088, 106.8456); }
signals:
    void posisiDiperbarui(double lat, double lon);  // selalu void!
};

// Connect — Qt5/6 style (type-safe, typo = compile error)
QObject::connect(&sensor, &SensorGPS::posisiDiperbarui,
                 &display, &Display::onPosisi);

// Qt4 style — hindari (string-based, typo baru ketahuan saat runtime)
QObject::connect(&sensor, SIGNAL(posisiDiperbarui(double,double)),
                 &display, SLOT(onPosisi(double,double)));
```

### Qt log levels
```cpp
qDebug()    << "info debug";
qWarning()  << "peringatan — tidak fatal";
qCritical() << "error serius";
qFatal()    << "fatal — program abort";
```

---

## Sesi 9 — Qt: Widgets & Layout {#sesi-9}

- `QCoreApplication` — console/non-GUI (event loop saja)
- `QApplication` — GUI, wajib untuk semua widget

| Widget | Fungsi | Padanan HTML |
|---|---|---|
| `QLabel` | Tampilkan teks/gambar | `<span>`, `<p>` |
| `QPushButton` | Tombol klik | `<button>` |
| `QLineEdit` | Input teks satu baris | `<input type="text">` |
| `QMainWindow` | Jendela utama dengan menu/toolbar | `<body>` |

```cpp
// Structure dasar MainWindow
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    QWidget* central = new QWidget(this);
    setCentralWidget(central);  // WAJIB untuk QMainWindow

    QVBoxLayout* layout = new QVBoxLayout(central);
    QHBoxLayout* hbox   = new QHBoxLayout();  // nested layout tanpa parent

    label  = new QLabel("teks", this);
    tombol = new QPushButton("Klik", this);
    layout->addWidget(label);
    layout->addLayout(hbox);  // ownership berpindah via addLayout

    connect(tombol, &QPushButton::clicked, this, &MainWindow::onKlik);
}
```

**Kenapa widget selalu pointer (`QLabel*`):**
1. Qt ownership model — heap supaya parent bisa delete saat dihancurkan
2. Stack = dihapus saat keluar scope constructor — terlalu cepat
3. `QObject` copy constructor di-delete — tidak bisa copy, wajib pointer

```cpp
// QString formatting
QString text = QString("Lat %1, Lon %2").arg(lat).arg(lon);
QString input = lineEdit->text();
label->setText(text);

// Format angka
QString::number(nilai, 'f', 2)  // fixed, 2 desimal
```

---

## Sesi 10 — Qt: QPainter & Rendering {#sesi-10}

`QPainter` = API drawing Qt. Semua drawing WAJIB di dalam `paintEvent`.

```
Data berubah → update() → Qt schedule → paintEvent() → gambar ulang
```

> Jangan panggil `paintEvent()` langsung. `update()` ≈ `requestAnimationFrame()` di JS.

```cpp
class ChartWidget : public QWidget {
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent* event) override;
};

void ChartWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  // tepi halus

    painter.fillRect(rect(), QColor(20, 60, 120));  // background, rect() = ukuran widget

    painter.setPen(QPen(QColor(255, 50, 50), 2, Qt::DashLine));
    painter.setBrush(Qt::NoBrush);                  // isi transparan
    painter.drawEllipse(QPoint(width()/2, height()/2), 40, 40);  // dinamis!

    painter.setPen(Qt::white);
    painter.drawText(QPoint(10, 20), "teks");
    painter.drawLine(0, 0, width(), height());
}
```

**Posisi dinamis — selalu pakai `width()/2` dan `height()/2`:**
```cpp
painter.drawEllipse(QPoint(width()/2, height()/2), 60, 60);  // ikut resize ✓
painter.drawEllipse(QPoint(300, 200), 60, 60);                // hardcoded ✗
```

| JS Canvas | Qt QPainter |
|---|---|
| `requestAnimationFrame(render)` | `update()` |
| `ctx.strokeStyle` | `painter.setPen(...)` |
| `ctx.fillStyle` | `painter.setBrush(...)` |
| `ctx.arc(...)` | `painter.drawEllipse(...)` |
| `ctx.fillRect(...)` | `painter.fillRect(...)` |

---

## Fase 1 — Challenge Review {#fase-1}

### Challenge 1 — Signal & Slot {#c1}
**Project:** `temp_monitor/`

- Signal **wajib** return `void`
- `Q_OBJECT` ≠ `public QObject`: Q_OBJECT instruksi ke MOC, bukan inheritance
- `app.exec()` = blocking event loop — untuk app sederhana cukup `return 0`
- `QCoreApplication` untuk console, `QApplication` untuk GUI

---

### Challenge 2 — Widget & Layout {#c2}
**Project:** `temp_conversion/`

- `setCentralWidget(central)` wajib sebelum taruh widget di QMainWindow
- `QHBoxLayout` di-nest ke `QVBoxLayout` via `addLayout()` — ownership otomatis berpindah
- `QDoubleValidator` — cegah user ketik huruf di input angka

**Type promotion:**
```cpp
inputDouble * 9 / 5   // double × int → double → /int → double ✓
9 / 5                  // int/int → integer division = 1 ✗
9.0 / 5                // double/int → double = 1.8 ✓
```

---

### Challenge 3 — QPainter {#c3}
**Project:** `qt_painter/`

- `QPainter` hanya valid di dalam `paintEvent` — di luar sesi menggambar, target tidak ada
- `update()` → Qt panggil `paintEvent` di waktu yang tepat, tidak langsung
- `fillRect` di awal paintEvent = "hapus frame sebelumnya"
- Tanpa `fillRect`: jejak gambar sebelumnya tidak terhapus

---

## Fase 2 — Intermediate {#fase-2}

### Topik 1 — QTimer {#f2t1}
**Project:** `timer_basic/`

| JavaScript | Qt |
|---|---|
| `setInterval(fn, ms)` | `timer->start(ms)` + connect ke slot |
| `clearInterval(id)` | `timer->stop()` |
| `setTimeout(fn, ms)` | `QTimer::singleShot(ms, this, slot/lambda)` |

```cpp
timer = new QTimer(this);  // parent this — ikut dihapus saat widget dihapus
connect(timer, &QTimer::timeout, this, &Widget::onTick);
timer->start(1000);

// singleShot dengan lambda
QTimer::singleShot(5000, this, [this]() {
//                        ^^^^  ^^^^^^
//                  context Qt  C++ lambda capture
    label->setText("5 detik berlalu");
});
```

**Lambda capture — beda dari JS closure:**
```cpp
// JS — closure otomatis akses variabel luar
const fn = () => label.setText("x");

// C++ — harus eksplisit
auto fn = [this]() { label->setText("x"); };  // [this] = izinkan akses member
auto fn2 = []()   { label->setText("x"); };  // ERROR — label tidak dikenal
```

- Jangan pakai `sleep()` — membekukan event loop
- `stop()` tidak reset nilai — lanjut dari angka terakhir

---

### Topik 2 — Animasi QTimer + QPainter {#f2t2}
**Project:** `ball_animation/`

```
QTimer (16ms) → slot → update state → update() → paintEvent() → gambar ulang
```

**16ms ≈ 60fps** — standar animasi smooth. Di bawah 30fps (>33ms) terasa patah-patah.

```cpp
// Velocity vector — lebih baik dari QString arah
int dx = 3;   // + = kanan, - = kiri
int dy = 2;   // + = bawah, - = atas

void moveBall() {
    ballX += dx;
    ballY += dy;
    // gerak dulu, baru cek boundary — cek posisi BARU bukan posisi lama
    if (ballX - radius < 0 || ballX + radius > width())  dx = -dx;
    if (ballY - radius < 0 || ballY + radius > height()) dy = -dy;
    update();
}
```

```cpp
// Inisialisasi posisi awal harus valid
ballX(0), radius(30)    // SALAH — 0-30=-30 < 0 → stuck di tepi
ballX(100), radius(30)  // BENAR — 100-30=70 > 0 → aman

// Boundary check — jangan pakai ==
if (ballX == 0)  // BERBAHAYA — bola loncat 3px, bisa skip nilai 0
if (ballX < 0)   // BENAR — range check, tidak bisa dilewati
```

---

### Topik 3 — Model/View Architecture {#f2t3}
**Project:** `modelview_basic/`

| Peran | Tanggung jawab | Padanan JS |
|---|---|---|
| **Model** | Simpan dan kelola data | Array / state |
| **View** | Tampilkan data dari model | Komponen React |
| **Delegate** | Kontrol cara tiap item dirender | Custom cell renderer |

```
Model punya data → View tanya model → View render
Data berubah → Model emit signal → Semua view update otomatis
```

```cpp
model = new QStringListModel(this);
model->setStringList({"Jakarta", "Surabaya", "Medan"});

listView->setModel(model);   // satu baris = view subscribe semua perubahan
comboBox->setModel(model);   // data sama, tampilan berbeda — sync otomatis

// Tambah item
int row = model->rowCount();
model->insertRow(row);
model->setData(model->index(row), teks);

// Hapus — selalu guard dulu
int idx = comboBox->currentIndex();
if (idx < 0) return;          // guard: model kosong → idx = -1
model->removeRow(idx);

QModelIndex idx = listView->currentIndex();
if (!idx.isValid()) return;   // guard: tidak ada yang dipilih
model->removeRow(idx.row());
```

**`QModelIndex` vs `int`:** QModelIndex bawa row + column + parent, support tree/table, punya `isValid()`. `int` cukup untuk list flat.

Pakai Model/View untuk: list/tabel/tree yang bisa berubah, data yang perlu tampil di beberapa tempat. Jangan untuk satu `QLabel` statis.

---

### Topik 4 — Event Handling Lanjutan {#f2t4}
**Project:** `modelview_basic/`

Event tidak datang lewat `connect()` — tapi lewat **override method**:

| Web Event | Qt Override |
|---|---|
| `keydown` | `keyPressEvent(QKeyEvent* e)` |
| `mousemove` | `mouseMoveEvent(QMouseEvent* e)` |
| window close | `closeEvent(QCloseEvent* e)` |

```cpp
void MyWidget::keyPressEvent(QKeyEvent* e) {
    if (e->key() == Qt::Key_Escape) {
        // handle sendiri
    } else {
        QMainWindow::keyPressEvent(e);  // WAJIB — lempar ke parent
        // Tanpa ini: Tab, Space, shortcut Qt semua "ditelan" dan mati
    }
}

void MainWindow::closeEvent(QCloseEvent* event) {
    if (yakin) event->accept();   // window ditutup
    else       event->ignore();   // window tetap terbuka
}
```

**Mouse tracking — tidak aktif secara default:**
```cpp
setMouseTracking(true);           // untuk MainWindow
central->setMouseTracking(true);  // untuk central widget
```

**Event Filter — intercept event dari child widget:**
```cpp
// Di Qt, event tidak otomatis bubble ke parent seperti di web
central->installEventFilter(this);

bool MainWindow::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::MouseMove) {
        QMouseEvent* me = static_cast<QMouseEvent*>(event);
        statusBar()->showMessage(QString("x:%1 y:%2")
            .arg(me->pos().x()).arg(me->pos().y()));
    }
    return QMainWindow::eventFilter(obj, event);
}
```

---

## Fase 3 — Advanced {#fase-3}

### Topik 5 — QSS / Theming {#f3t5}
**Project:** `qss_basic/`

QSS = Qt Style Sheets, syntaxnya hampir identik CSS.

```cpp
// Tiga cara apply — dari luas ke sempit
qApp->setStyleSheet("...");         // seluruh app
mainWindow->setStyleSheet("...");   // window + semua child
button->setStyleSheet("...");       // widget ini saja (≈ inline style)
```

```css
QPushButton { background: #313244; border-radius: 6px; padding: 8px 16px; }
QPushButton:hover   { background: #45475a; }  /* WAJIB tulis eksplisit, tidak ada default */
QPushButton:pressed { background: #585b70; }
QPushButton#btnDanger { background: #f38ba8; }  /* target by objectName */
```

```cpp
// setObjectName — wajib untuk selector #id
btnDanger->setObjectName("btnDanger");

// Raw string literal untuk QSS panjang — padanan template literal JS
setStyleSheet(R"(
    QPushButton { border-radius: 6px; }
)");
```

**Spesifisitas:** `#objectName` > `WidgetType` > inherited dari parent

**Beda dari CSS web:**
- Pseudo-state tidak ada default — harus tulis semua (`hover`, `pressed`, dll)
- Tidak ada class selector (`.class`) — pakai `#objectName`

---

### Topik 6 — File I/O {#f3t6}
**Project:** `fileio_basic/`

```cpp
// Baca file
QFile file(path);
if (!file.open(QFile::ReadOnly | QFile::Text)) return;  // selalu cek!
QTextStream in(&file);
editor->setPlainText(in.readAll());
file.close();

// Tulis file
QFile file(path);
if (!file.open(QFile::WriteOnly | QFile::Text)) return;
QTextStream out(&file);
out << editor->toPlainText();
file.close();
editor->document()->setModified(false);  // reset flag — tidak otomatis!
```

**`QFile::Text`** — konversi line ending antar OS (`\r\n` ↔ `\n`). Tanpanya: karakter `\r` ekstra di Windows.

**Save vs Save As:**
```cpp
void onSimpan() {
    if (filePath.isEmpty()) {
        filePath = QFileDialog::getSaveFileName(...);  // Save As — muncul dialog
        if (filePath.isEmpty()) return;
    }
    // Save — tulis langsung tanpa dialog
}
```

**File dialog:**
```cpp
QString path = QFileDialog::getOpenFileName(this, "Buka", "", "Text (*.txt);;All (*)");
QString path = QFileDialog::getSaveFileName(this, "Simpan", "", "Text (*.txt)");
// Selalu cek isEmpty() — return "" kalau user cancel
```

**closeEvent + isModified:**
```cpp
void MainWindow::closeEvent(QCloseEvent* event) {
    if (editor->document()->isModified()) {
        auto jawab = QMessageBox::question(this, "Konfirmasi", "Simpan sebelum keluar?",
                                           QMessageBox::Yes | QMessageBox::No);
        if (jawab == QMessageBox::Yes) { onSimpan(); event->accept(); }
        else                           { event->ignore(); }
    } else {
        event->accept();
    }
}
```

---

### Topik 7 — Networking {#f3t7}
**Project:** `networking_basic/`

```cmake
# CMake — tambah Network module
find_package(Qt6 REQUIRED COMPONENTS Widgets Network)
target_link_libraries(app PRIVATE Qt6::Widgets Qt6::Network)
```

```cpp
// Setup — satu QNAM per app
manager = new QNetworkAccessManager(this);
connect(manager, &QNetworkAccessManager::finished,
        this, &MainWindow::onReplyFinished);  // fired untuk SETIAP reply

// Send request — tidak blocking, langsung return
QNetworkRequest request;
request.setUrl(QUrl("https://api.example.com/data"));
manager->get(request);

// Handle response
void onReplyFinished(QNetworkReply* reply) {
    if (reply->error() != QNetworkReply::NoError) {
        qWarning() << reply->errorString();
        reply->deleteLater();  // WAJIB di setiap exit path
        return;
    }
    QString data = QString::fromUtf8(reply->readAll());
    reply->deleteLater();  // deleteLater bukan delete — masih di call stack Qt
}
```

| JavaScript | Qt |
|---|---|
| `fetch(url)` | `manager->get(QNetworkRequest(url))` |
| `.then(res => res.text())` | signal `finished` → slot |
| `res.ok` | `reply->error() == NoError` |
| `res.text()` | `QString::fromUtf8(reply->readAll())` |

- `finished` dipanggil untuk **setiap** reply — termasuk kalau ada 2 request bersamaan
- Disable tombol saat request in-flight untuk cegah double request

---

### Topik 8 — Multithreading dengan QtConcurrent {#f3t8}
**Project:** `thread_basic/`

```cmake
find_package(Qt6 REQUIRED COMPONENTS Widgets Concurrent)
target_link_libraries(app PRIVATE Qt6::Widgets Qt6::Concurrent)
```

```cpp
// Fungsi di background — DILARANG akses widget dari sini!
// Widget Qt tidak thread-safe — semua operasi widget WAJIB di UI thread
static int tugasBerat() {
    QThread::sleep(5);
    return 42;
}

// Setup watcher — jembatan background thread → UI thread
watcher = new QFutureWatcher<int>(this);
connect(watcher, &QFutureWatcher<int>::finished, this, &MainWindow::onSelesai);

// Jalankan di background — tidak blocking
QFuture<int> future = QtConcurrent::run(tugasBerat);
watcher->setFuture(future);

// Slot ini dipanggil di UI thread — aman update widget
void onSelesai() {
    int hasil = watcher->result();
    label->setText(QString::number(hasil));
}
```

**Progress bar:**
```cpp
progressBar->setRange(0, 0);    // indeterminate — tidak tahu berapa %, animasi bouncing
progressBar->setRange(0, 100);  // determinate — tahu progress, pakai setValue(n)
```

| | `QtConcurrent` | `QThread` |
|---|---|---|
| Level | High-level | Low-level |
| Kode | Satu baris | Banyak setup |
| Cocok untuk | Task sederhana | Thread lifecycle penuh |

---

## Tips Umum {#tips}

### CMake — Cara Tambah Qt Module

Setiap module Qt yang dipakai **wajib** ada di dua tempat:
```cmake
find_package(Qt6 REQUIRED COMPONENTS Widgets Network Concurrent)
target_link_libraries(app PRIVATE Qt6::Widgets Qt6::Network Qt6::Concurrent)
```

| Kamu pakai | Module |
|---|---|
| Widget, Button, Label | `Widgets` |
| QNetworkReply | `Network` |
| QtConcurrent | `Concurrent` |
| QFile, QTimer, QString | `Core` (sudah include otomatis) |

Setelah edit CMakeLists.txt: **Build → Re-run CMake** di Qt Creator.

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
| Closure otomatis | Lambda capture eksplisit `[this]` |
| Event bubble ke parent | Tidak otomatis — pakai event filter |

### Koordinat GPS — selalu `double`
`float` hanya 7 digit presisi — bisa beda **puluhan meter** untuk koordinat global.
