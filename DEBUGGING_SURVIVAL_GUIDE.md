# Debugging Survival Guide (C++ / Qt)

Dokumen ini dibuat untuk kamu yang background web dev dan baru masuk ke C++/Qt, supaya saat error di kantor kamu punya “playbook” yang cepat.

---

## 1) Cara pikir dasar: bedakan 3 kelas masalah
- **Compile error**: salah include, tipe, signature, template, missing symbol saat compile.
- **Link error**: kompilasi sukses tapi gagal link (library/module/moc tidak ikut).
- **Runtime crash/hang**: segfault, abort, deadlock, UI freeze.

---

## 2) Error paling sering di Qt + CMake (AUTOMOC / Q_OBJECT)

Gejala:
- Link error seperti `undefined reference to vtable for ...`
- Atau object punya `Q_OBJECT` tapi meta-object code tidak terbentuk.

Solusi cepat:
- Pastikan `CMAKE_AUTOMOC` **ON** di `CMakeLists.txt` project Qt.
- Pastikan header class yang punya `Q_OBJECT` benar-benar di-compile oleh target (minimal file `.cpp` yang include header itu masuk ke `add_executable()`).

Catatan:
- Di repo ini, `Project1_Qt_Basics`, `Project2_Graphics`, `Project4_ECDIS_Integration` sudah di-set `CMAKE_AUTOMOC ON`.

---

## 3) UI freeze: rule of thumb yang wajib

Gejala:
- Window tidak bisa di-drag, button tidak respons, “Not responding”.

Penyebab umum:
- Kamu melakukan kerja berat (parse file besar, loop panjang, networking blocking) di **UI thread**.

Solusi konsep:
- Pindahkan kerja berat ke worker thread (mis. `QThread`/`QtConcurrent`) lalu **kirim hasil balik** ke UI via signal/slot.
- Untuk simulasi ringan, gunakan `QTimer` (bukan `sleep()`).

---

## 4) Logging cepat di Qt

Pakai:
- `qDebug()` untuk info
- `qWarning()` untuk warning
- `qCritical()` untuk error berat

Tips:
- Selalu log **awal/akhir** operasi besar: “start parse”, “end parse”, “feature count”.
- Log “input penting” saat gagal: file path, record index, ukuran data.

---

## 5) Crash / segfault: langkah cepat (Linux)

### Compile dengan simbol debug
Untuk CMake:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j
```

### Jalankan pakai gdb

```bash
gdb --args ./YourApp arg1 arg2
run
bt
```

Yang dicari:
- Lokasi crash (stack trace `bt`)
- Nilai parameter yang aneh (null pointer, ukuran vector, index out-of-range)

---

## 6) Sanitizers (wajib untuk belajar cepat memory bugs)

### AddressSanitizer + UndefinedBehaviorSanitizer
CMake flags cepat:

```bash
cmake -S . -B build \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_CXX_FLAGS="-fsanitize=address,undefined -fno-omit-frame-pointer" \
  -DCMAKE_LINKER_FLAGS="-fsanitize=address,undefined"
cmake --build build -j
```

Run:
- ASan biasanya langsung kasih report: use-after-free, buffer overflow, double free.

Catatan:
- Jalankan ini paling sering di `Project0_CPP_Refresh` saat belajar pointer/ownership.

---

## 7) Lifetime/Ownership rules (praktis untuk Qt)

### Rule A — Parent owns child (Qt Widgets/QObject)
- Kalau kamu buat `QWidget/QObject` dengan parent yang benar, Qt akan auto-delete child saat parent dihancurkan.
- Ini alasan di code Qt kamu sering lihat raw pointer untuk widget (bukan berarti “bebas leak” — ownership tetap harus jelas via parent).

### Rule B — Jangan simpan pointer tanpa jelas ownership
Kalau kamu simpan pointer ke object yang kamu tidak own:
- Pastikan siapa yang own (parent, container, scope).
- Hindari menyimpan pointer ke stack object yang akan habis scope.

### Rule C — Data model C++ (non-QObject) pakai RAII modern
- Untuk data parser/geometry: pakai `std::vector`, `std::string`, `std::unique_ptr` sesuai kebutuhan.

---

## 8) Checklist cepat sebelum tanya orang kantor

Saat kamu minta bantuan, siapkan:
- **Error message lengkap** (copy dari terminal)
- **Command build** yang kamu pakai
- **OS + Qt version** (Qt5/Qt6)
- Kalau crash: stack trace `gdb bt`
- Kalau UI freeze: bagian code yang loop/IO yang kamu curigai

