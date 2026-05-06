# Project 3: S-57 Parser

## Tujuan

Project ini mengenalkan dasar parsing file chart untuk ECDIS menggunakan C++.

Anda akan belajar:
- Membaca file binary dengan `std::ifstream`
- Menggunakan helper `read()` untuk parse struktur data
- Menggunakan struct dan vector untuk menyimpan feature
- Menangani error saat membaca file
- Menyusun parser yang bisa dikembangkan ke format nyata

---

## Catatan Penting

File S-57 nyata menggunakan format ISO 8211 dan jauh lebih kompleks dari contoh ini.
Project ini menggunakan format _simplified mini-S57_ sebagai langkah pembelajaran sebelum mengerjakan parser S-57 sebenarnya.

Dengan memahami struktur ini, Anda siap belajar detail ISO 8211 dan elemen S-57 berikutnya.

---

## Struktur Project

```
Project3_S57_Parser/
├── CMakeLists.txt
├── README.md
├── data/
│   └── sample_chart.s57  (generated binary sample file)
├── include/
│   └── S57Parser.h
└── src/
    ├── main.cpp
    ├── S57Parser.cpp
    └── GenerateSampleData.cpp
```

---

## Mini S-57 Format (Educational)

File sample menggunakan struktur sederhana:
- Magic header: `S57MINI` (8 bytes)
- Version: 1 byte
- Record count: 4 bytes (uint32)

Setiap record berisi:
- Record type: 1 byte
  - 1 = Point feature
  - 2 = Line feature
  - 3 = Polygon feature
- Feature ID: 4 bytes (uint32)
- Vertex count: 4 bytes (uint32)
- Vertex data: each vertex 16 bytes (double lon + double lat)
- Name length: 2 bytes (uint16)
- Name string: variable length

Contoh record:
```
[1][123][1][lon][lat][4]["Buoy A"]
```

---

## Build & Run

### Generate sample data

```bash
cd /home/galih/Documents/Explore/belajar-cpp/Project3_S57_Parser
mkdir -p build
cd build
cmake ..
make
./GenerateS57Sample
```

### Jalankan parser

```bash
./S57ParserApp ../data/sample_chart.s57
```

---

## Output

Parser akan mencetak daftar feature beserta koordinat dan nama.

Contoh fitur:
- Point feature: buoy atau waypoint
- Line feature: shipping lane atau coastline segment
- Polygon feature: area shallow water atau land

---

## Latihan

1. Tambahkan atribut baru seperti "feature category".
2. Ubah file generator menjadi juga menulis atribut tambahan.
3. Update parser untuk membaca data tambahan.
4. Integrasikan parser dengan Project 2 untuk menggambar geometry di scene.

---

## 🧪 Latihan Wajib (robust parsing + data model)

### Latihan 1 — Error messages yang actionable
- **Task**:
  - Saat magic header salah / versi salah / record count tidak masuk akal, tampilkan error dengan konteks: file path + posisi read + alasan.
- **Checkpoint**:
  - Kamu bisa membedakan “EOF karena file pendek” vs “format invalid”.

### Latihan 2 — Data structure hasil parse
- **Task**:
  - Pastikan parser mengembalikan struktur data yang rapi (mis. `std::vector<Feature>`), dan tidak mencampur parsing dengan printing terlalu banyak.
  - Buat 1 fungsi “summary” yang hanya mencetak jumlah point/line/polygon.
- **Checkpoint**:
  - Kamu paham separation: parse → data → presentation.

### Latihan 3 — Validasi vertex count
- **Task**:
  - Tambahkan guard: vertex count 0 untuk line/polygon dianggap invalid (atau ditangani khusus) dan tidak boleh membuat read jadi out-of-sync.
- **Checkpoint**:
  - Kamu paham kenapa parser harus tahan data rusak.

---

## ✅ Checkpoint selesai Project 3
- [ ] Bisa generate sample dan parse tanpa crash
- [ ] Output ringkasan benar (jumlah fitur per tipe)
- [ ] Error invalid file terbaca jelas (bukan sekadar “failed”)

---

## Keterangan

Walaupun contoh ini bukan file S-57 asli, pendekatan parser yang digunakan sangat relevan:
- baca header
- validasi magic
- baca record satu per satu
- simpan hasil dalam struktur C++
- tampilkan data dengan cara yang mudah dibaca

Langkah berikutnya: hubungkan parser ke Qt scene di Project 4.
