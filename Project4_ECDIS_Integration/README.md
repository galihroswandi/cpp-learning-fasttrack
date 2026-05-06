# Project 4: ECDIS Integration

## Tujuan

Project ini menggabungkan parser S-57 sederhana dengan tampilan Qt grafik.

Anda akan belajar:
- Menggabungkan backend parser dengan frontend Qt
- Membaca file chart melalui dialog file
- Memvisualisasikan features ECDIS di `QGraphicsScene`
- Mengubah geometry S-57 menjadi item Qt
- Menampilkan daftar fitur yang berhasil di-load

---

## Struktur Project

```
Project4_ECDIS_Integration/
├── CMakeLists.txt
├── README.md
├── data/
│   └── sample_chart.s57
├── include/
│   ├── MainWindow.h
│   └── S57Parser.h
└── src/
    ├── main.cpp
    ├── MainWindow.cpp
    └── S57Parser.cpp
```

---

## Build & Run

```bash
cd /home/galih/Documents/Explore/belajar-cpp/Project4_ECDIS_Integration
mkdir -p build
cd build
cmake ..
make
./ECDISIntegrationApp ../data/sample_chart.s57
```

Jika Qt tidak ditemukan, tambahkan `Qt6_DIR` atau `CMAKE_PREFIX_PATH` ke direktori instalasi Qt Anda:

```bash
cmake -DCMAKE_PREFIX_PATH="/path/to/Qt" ..
```

Catatan:
- Jika memakai Qt 6 dari installer, path umum `CMAKE_PREFIX_PATH` mengarah ke folder Qt root (yang berisi `lib/cmake/Qt6`).
- Jika kamu memakai Qt 5, CMake akan otomatis memilih Qt5 bila Qt6 tidak ada (karena `CMakeLists.txt` mendukung Qt6/Qt5).

Untuk menghasilkan ulang sample chart:

```bash
python3 scripts/generate_sample_chart.py
```

Jika ingin membuka file lain:
```bash
./ECDISIntegrationApp /path/to/another_chart.s57
```

---

## Fitur Aplikasi

1. `Load Chart` untuk membuka file S-57 sederhana
2. `Reset View` untuk mengembalikan zoom dan pan
3. `QGraphicsView` menampilkan point, line, polygon
4. `QListWidget` menampilkan ringkasan fitur yang dibaca
5. `QStatusBar` menunjukkan status parsing dan rendering

---

## Catatan

- File sample menggunakan format mini-S57 edukasional.
- Aplikasi ini mendemonstrasikan pipeline lengkap: file -> parser -> visualisasi.
- Langkah berikutnya: tambah support untuk format S-57 nyata dan layer control.

---

## 🧪 Latihan Wajib (mendekati workflow kantor)

### Latihan 1 — Pisahkan “data model” vs “rendering”
- **Task**:
  - Pastikan hasil parsing disimpan sebagai data (mis. `std::vector<Feature>`) lalu rendering hanya membaca data itu.
  - Tambahkan 1 fungsi untuk “render ulang” tanpa re-parse (contoh: tombol `Reload Render` yang merender ulang data terakhir).
- **Checkpoint**:
  - Kamu paham: parsing itu I/O + CPU, rendering itu UI; keduanya jangan tercampur.

### Latihan 2 — Kontrol layer sederhana
- **Task**:
  - Tambahkan toggle sederhana untuk tampil/sembunyi tipe feature tertentu (point/line/polygon).
- **Checkpoint**:
  - Kamu paham pola ECDIS: layer on/off biasanya hanya mengatur visibilitas per kategori.

### Latihan 3 — Jangan freeze UI (konsep)
- **Task**:
  - Ukur kasar: kalau file besar, parse bisa lama. Catat bahwa solusi umum adalah worker thread + signal balik ke UI.
- **Checkpoint**:
  - Kamu bisa menjelaskan kenapa parsing sebaiknya tidak jalan di UI thread.

---

## ✅ Checkpoint selesai Project 4
- [ ] Bisa load file sample dari argumen CLI dan dari tombol Open
- [ ] Feature tergambar di scene dan list/log tampil
- [ ] Ada minimal 1 toggle visibilitas feature type
