# Project 1: Qt Basics

## Tujuan

Project ini membantu Anda memahami konsep dasar Qt untuk membangun GUI di C++.

Dalam project ini Anda akan belajar:
- Struktur project Qt dengan CMake
- Membuat aplikasi Qt sederhana
- Menggunakan `QMainWindow`, `QWidget`, dan layout
- Menghubungkan `signals` dan `slots`
- Mengelola event dari tombol dan input teks
- Menggunakan widget dasar: `QPushButton`, `QLineEdit`, `QLabel`, `QListWidget`, `QStatusBar`
- Menjalankan aplikasi Qt di Linux

---

## Struktur Project

```
Project1_Qt_Basics/
├── CMakeLists.txt
├── README.md
├── include/
│   └── MainWindow.h
└── src/
    ├── main.cpp
    └── MainWindow.cpp
```

---

## Fungsi Aplikasi

Aplikasi ini terdiri dari:
- Input nama chart
- Tombol `Load Chart`
- Log area yang memuat informasi saat loading
- Slider zoom sederhana
- Status bar untuk menampilkan pesan

Aplikasi ini tidak benar-benar memuat chart, tetapi menyediakan kerangka yang cocok untuk next step Project 2.

---

## Build & Run

### Prasyarat

Pastikan Qt (Qt 6 **atau** Qt 5) dan CMake sudah terinstall di sistem Anda.

### Langkah build

```bash
cd /home/galih/Documents/Explore/belajar-cpp/Project1_Qt_Basics
mkdir -p build
cd build
cmake ..
make
```

### Menjalankan aplikasi

```bash
./QtBasicsApp
```

Jika Qt tidak ditemukan, gunakan `CMAKE_PREFIX_PATH`:

```bash
cmake -DCMAKE_PREFIX_PATH="/path/to/Qt" ..
```

---

## Apa yang dipelajari

1. `QApplication` sebagai entry point
2. `QMainWindow` sebagai window utama
3. `QWidget` sebagai widget dasar
4. Layout Qt: `QVBoxLayout`, `QHBoxLayout`
5. `signals` dan `slots` untuk interaksi GUI
6. Menambahkan widget secara dinamis di runtime
7. Menampilkan status message di `QStatusBar`

---

## Tips practice

1. Ubah label dan tombol
2. Tambahkan widget baru seperti `QCheckBox` atau `QComboBox`
3. Ubah gaya dengan `setStyleSheet()`
4. Simulasikan real chart loader dengan timer atau progress bar
5. Pelajari `QObject::connect()` secara manual

---

## 🧪 Latihan Wajib (wajib untuk adaptasi kerja Qt)

### Latihan 1 — Signals/Slots (lambda vs slot method)
- **Task**:
  - Tambahkan 1 koneksi `connect()` yang memakai **lambda** (mis. saat tombol `Clear` diklik).
  - Tambahkan 1 koneksi `connect()` yang memakai **slot method** (yang sudah ada), lalu bandingkan style-nya.
- **Checkpoint**:
  - Kamu paham bahwa signals/slots itu mekanisme event-driven utama di Qt.

### Latihan 2 — Lifetime (parent-child ownership)
- **Task**:
  - Pastikan semua widget dibuat dengan parent yang benar (mis. dibuat dengan `centralWidget` sebagai parent) supaya tidak perlu `delete` manual.
  - Pahami bahwa Qt akan auto-delete child saat parent dihancurkan.
- **Checkpoint**:
  - Kamu bisa menjelaskan kenapa Qt jarang pakai `std::unique_ptr<QWidget>` untuk widget yang punya parent.

### Latihan 3 — Event loop + timer
- **Task**:
  - Tambahkan `QTimer` untuk simulasi loading chart (mis. menambah log setiap 200ms selama 1–2 detik).
- **Checkpoint**:
  - Kamu paham: UI tetap responsif karena kerja “bertahap” dipicu event loop (bukan `sleep()`).

---

## ✅ Checkpoint selesai Project 1
- [ ] App bisa build & run dari CMake
- [ ] Tombol bekerja dan log/statusbar berubah
- [ ] Kamu paham `connect()` dan basic event loop

---

### Next step

Setelah Anda bisa build dan menjalankan aplikasi ini, lanjut ke **Project 2: Graphics & Drawing** untuk membuat visualisasi chart dasar.
