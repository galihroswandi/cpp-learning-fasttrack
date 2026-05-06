# C++ → Qt Fast-Track (2 Minggu)

Target: web developer yang baru belajar C++ supaya **cukup produktif** di project kantor yang berbasis **Qt** (menuju workflow ECDIS: parse data → model → render).

Repo ini sudah punya project bertahap:
- `Project0_CPP_Refresh` (C++ fundamentals)
- `Project1_Qt_Basics` (Qt Widgets + signal/slot)
- `Project2_Graphics` (QGraphicsView/Scene)
- `Project3_S57_Parser` (mini S-57 educational parser)
- `Project4_ECDIS_Integration` (integrasi parser + render)

---

## Setup (sekali saja)

### Paket minimal (Ubuntu/Debian)
- Compiler & tools:
  - `build-essential`, `cmake`
- Qt:
  - Qt 6: paket dev `qt6-base-dev` (atau instalasi Qt dari Qt Online Installer)
  - Qt 5: paket dev `qtbase5-dev`

Catatan:
- Repo ini pakai CMake di semua project.
- Kalau Qt tidak terdeteksi, gunakan `CMAKE_PREFIX_PATH` / `Qt6_DIR` / `Qt5_DIR` saat konfigurasi CMake (lihat README tiap project).

---

## Cara kerja harian (aturan main)
- **Run dulu, baru modif.** Jangan menebak output.
- Setiap sesi 60–120 menit:
  - 10 menit baca README + lihat struktur file
  - 30–60 menit run & ubah kecil (latihan wajib)
  - 10 menit tulis catatan: “apa yang baru”, “apa yang bikin error”, “apa yang aku pahami”
- Fokus 3 hal yang paling sering kepakai di Qt:
  - **Lifetime/ownership**
  - **Event-driven programming (signals/slots + event loop)**
  - **Model data → rendering**

---

## Minggu 1 — Fondasi C++ + Qt Core/Widgets

### Day 1 (±2 jam): Tooling + Memory mental model
Kerjakan:
- `Project0_CPP_Refresh` program `01_Memory_Management.cpp`

Checkpoint:
- Kamu bisa menjelaskan perbedaan stack/heap, dangling pointer, dan kenapa Qt mengandalkan object lifetime yang jelas.

### Day 2 (±2 jam): OOP buat baca API Qt
Kerjakan:
- `Project0_CPP_Refresh` program `02_OOP_Classes.cpp`

Checkpoint:
- Kamu paham inheritance + virtual function (ini kepakai saat baca class Qt turunan `QWidget`/`QObject`).

### Day 3 (±2 jam): STL untuk data handling
Kerjakan:
- `Project0_CPP_Refresh` program `03_STL_Containers.cpp`

Checkpoint:
- Kamu nyaman pakai `std::vector` untuk data geometry/feature list (yang nanti dirender).

### Day 4 (±2 jam): File I/O + parsing mindset
Kerjakan:
- `Project0_CPP_Refresh` program `04_File_IO.cpp`

Checkpoint:
- Kamu bisa baca file binary sederhana dan tahu cara validasi header/record.

### Day 5 (±1.5 jam): Exception + RAII (wajib untuk “production mindset”)
Kerjakan:
- `Project0_CPP_Refresh` program `05_Exception_Handling.cpp`

Checkpoint:
- Kamu paham RAII dan “cleanup otomatis saat scope selesai” (ini fondasi agar code Qt nggak bocor resource).

### Day 6 (±2 jam): Modern C++ features yang sering dipakai
Kerjakan:
- `Project0_CPP_Refresh` program `06_Modern_CPP.cpp`

Checkpoint:
- Kamu tahu kapan pakai `std::unique_ptr` vs raw pointer (di Qt raw pointer sering muncul, tapi ownership tetap harus jelas).

### Day 7 (±2–3 jam): Masuk Qt Widgets + signals/slots
Kerjakan:
- `Project1_Qt_Basics`

Checkpoint:
- Kamu bisa build/run app, klik tombol, lihat log berubah.
- Kamu paham alur: user event → signal → slot → update UI.

---

## Minggu 2 — Graphics, Parsing, dan Integrasi ala ECDIS mini

### Day 8 (±2–3 jam): Graphics scene/view dasar
Kerjakan:
- `Project2_Graphics`

Checkpoint:
- Kamu paham hubungan `QGraphicsView` ↔ `QGraphicsScene` ↔ item (line/polygon/text).
- Zoom/pan bekerja dan kamu ngerti “transform” di level view.

### Day 9 (±2 jam): Struktur data hasil parsing
Kerjakan:
- `Project3_S57_Parser`

Checkpoint:
- Bisa generate sample file, lalu parse dan lihat output feature list.
- Kamu bisa menjelaskan format mini S-57 di README dan alur parse-nya.

### Day 10 (±2–3 jam): Integrasi file → parser → render
Kerjakan:
- `Project4_ECDIS_Integration`

Checkpoint:
- Bisa run app dan load `../data/sample_chart.s57` lalu melihat fitur tergambar.

### Day 11 (±2 jam): Debugging flow (yang sering kejadian di Qt)
Kerjakan:
- Tambahkan log yang tepat (kapan parse mulai/selesai, jumlah features).
- Latihan membaca error build/link (terutama Qt + moc).

Checkpoint:
- Kalau build error, kamu tahu harus cek: CMake output, Qt package ditemukan atau tidak, dan apakah `AUTOMOC` aktif.

### Day 12 (±2–3 jam): Threading/IO mindset (tanpa implementasi berat)
Kerjakan:
- Di `Project4_ECDIS_Integration`, pahami kenapa parsing/IO sebaiknya tidak memblok UI thread.

Checkpoint:
- Kamu bisa menjelaskan: UI thread harus responsif; kerja berat pindah ke worker (konsep).

### Day 13 (±2 jam): “Office readiness” mini-refactor
Kerjakan:
- Rapikan ownership: siapa “own” scene, view, model data.
- Pisahkan minimal: parsing result → render function.

Checkpoint:
- Kamu bisa jelaskan “batas layer”: parser (pure C++) vs UI (Qt).

### Day 14 (±1–2 jam): Simulasi kerja kantor
Kerjakan:
- Ambil 1 fitur kecil yang realistis:
  - mis. tombol “Reload chart”, atau filter list feature, atau toggle tampil/sembunyi polygon.

Checkpoint:
- Bisa implement perubahan kecil end-to-end tanpa “nyasar” di codebase.

---

## Perintah build cepat (template)

Untuk setiap project:

```bash
cd /home/galih/Documents/Explore/belajar-cpp/<ProjectX>
mkdir -p build
cmake -S . -B build
cmake --build build -j
```

Kalau Qt tidak ketemu (contoh):

```bash
cmake -S . -B build -DCMAKE_PREFIX_PATH="/path/to/Qt"
cmake --build build -j
```

---

## Checklist “cukup produktif”
- Bisa membaca class Qt yang turunan `QObject/QWidget` dan paham lifetime-nya (parent-child).
- Bisa bikin UI kecil: button + input + list/log + status bar.
- Bisa render data menjadi item di `QGraphicsScene`.
- Bisa membaca file binary sederhana, validasi, dan convert ke struktur C++.
- Bisa integrasi parser → render tanpa bikin UI nge-freeze (paham konsep thread/worker).

