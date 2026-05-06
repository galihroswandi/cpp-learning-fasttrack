# Project 2: Graphics & Drawing

## Tujuan

Project ini memperkenalkan Qt graphics framework dengan cara membuat tampilan chart dasar.

Anda akan belajar:
- `QGraphicsView` dan `QGraphicsScene`
- Menambahkan objek grafik (`QGraphicsLineItem`, `QGraphicsPolygonItem`, `QGraphicsTextItem`)
- Membuat grid dan latar chart
- Menangani zoom dan pan
- Mengintegrasikan UI Qt dengan canvas grafik
- Membuat aplikasi yang terlihat seperti peta/chart ECDIS sederhana

---

## Struktur Project

```
Project2_Graphics/
├── CMakeLists.txt
├── README.md
├── include/
│   ├── GraphicsView.h
│   └── MainWindow.h
└── src/
    ├── GraphicsView.cpp
    ├── MainWindow.cpp
    └── main.cpp
```

---

## Build & Run

```bash
cd /home/galih/Documents/Explore/belajar-cpp/Project2_Graphics
mkdir -p build
cd build
cmake ..
make
./GraphicsDrawingApp
```

Jika Qt tidak ditemukan, gunakan `CMAKE_PREFIX_PATH`:

```bash
cmake -DCMAKE_PREFIX_PATH="/path/to/Qt" ..
```

---

## Apa yang dipelajari

1. Bagaimana `QGraphicsView` menampilkan `QGraphicsScene`
2. Cara menggambar bentuk 2D di Qt
3. Cara membuat peta sederhana dengan grid dan fitur garis
4. Cara memanipulasi view dengan zoom dan pan
5. Struktur aplikasi Qt yang lebih kompleks

---

## Catatan

Aplikasi ini belum membaca file S-57. Ini adalah langkah penting sebelum memasukkan parser data ke dalam scene.

Setelah selesai, lanjut ke Project 3 untuk menambahkan S-57 parser dan mengisi scene dengan data nyata.

---

## 🧪 Latihan Wajib (Graphics mindset untuk ECDIS)

### Latihan 1 — Layer sederhana (grid vs features)
- **Task**:
  - Buat 2 grup item: (1) grid/background, (2) feature items.
  - Tambahkan tombol/aksi untuk hide/show salah satu grup (minimal lewat `setVisible()`).
- **Checkpoint**:
  - Kamu paham bahwa “layer” itu biasanya hanya organisasi item di scene (atau grouping), bukan sesuatu yang magis.

### Latihan 2 — Koordinat & transform yang predictable
- **Task**:
  - Pastikan kamu tahu mana yang terjadi di level item (pos/transform) vs level view (zoom/pan).
  - Tambahkan 1 teks kecil di scene yang menunjukkan nilai zoom saat ini.
- **Checkpoint**:
  - Kamu bisa menjelaskan: zoom biasanya mengubah transform di `QGraphicsView`, bukan mengubah data geometry asli.

### Latihan 3 — Styling feature (warna/pen/brush)
- **Task**:
  - Bedakan style untuk line vs polygon (pen width, brush alpha).
- **Checkpoint**:
  - Kamu bisa mengontrol penampilan item tanpa mengubah data.

---

## ✅ Checkpoint selesai Project 2
- [ ] Grid tampil dan feature item tampil
- [ ] Zoom/pan berjalan stabil
- [ ] Ada minimal 1 toggle layer sederhana
