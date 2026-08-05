# Topik 26 — Qt Resource System (QRC)
Tanggal: 2026-05-29

## Ringkasan konsep
Qt Resource System (QRC) adalah mekanisme buat **embed file asset (gambar, ikon, QSS, font, JSON, text) langsung ke dalam executable** lewat file XML manifest `.qrc`. CMake (dengan `CMAKE_AUTORCC ON`) akan otomatis manggil `rcc` (Resource Compiler) untuk convert daftar file di `.qrc` jadi byte array di binary. Setelah itu, file diakses dari C++ pakai path virtual yang dimulai dengan titik dua: `":/prefix/path/file.ext"`. Resource bersifat **read-only at runtime** — `QFile::open(WriteOnly)` selalu gagal di path `:/...`. Library QtWidgets sendiri pakai mekanisme ini buat embed ikon default (`:/qt-project.org/styles/commonstyle/...`).

## Analogi JavaScript/React
- **QRC = Webpack/Vite asset bundling.** File `logo.png` "hilang" dari disk user tapi tetap bisa di-`import` karena udah di-inline ke bundle.
- **Path `":/assets/..."` = `import logo from '@assets/logo.png'`** dengan alias path resolution.
- **Prefix di `<qresource>`** = base path di alias config Webpack.
- **`alias` di `<file>`** = `import { default as shortName } from './really-long-filename.png'` — decouple nama variable di kode dari nama file fisik.
- **QRC vs folder `public/`** = bundled asset vs static file yang di-serve terpisah; file di luar QRC harus di-copy manual saat deploy.

## Kode inti

**resources.qrc**
```xml
<!DOCTYPE RCC>
<RCC version="1.0">
    <qresource prefix="/assets">
        <file>images/icon.png</file>
    </qresource>
    <qresource prefix="/text">
        <file alias="hello.txt">hello.txt</file>
    </qresource>
</RCC>
```

**CMakeLists.txt (bagian penting)**
```cmake
set(CMAKE_AUTORCC ON)

add_executable(qrc_basic
    main.cpp
    resources.qrc
)
```

**main.cpp (load dari QRC)**
```cpp
QPixmap pix(":/assets/images/icon.png");
imgLabel->setPixmap(pix.scaled(128, 128, Qt::KeepAspectRatio));

QFile file(":/text/hello.txt");
if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QTextStream in(&file);
    isi = in.readAll();
    file.close();
}
```

## Aturan penting
- **Kapan pakai:** asset kecil yang wajib selalu ada (ikon toolbar, logo, splash, default QSS, default config JSON), asset yang gak boleh diutak-atik user.
- **Kapan TIDAK pakai:** file besar (binary jadi gemuk + RAM boros), file yang user harus bisa edit/write (theme custom, runtime config, dokumen user) — karena QRC read-only.
- **Common mistake:**
  1. Lupa `:` di depan path → Qt cari di filesystem disk → pixmap null → silent fail di runtime.
  2. Lupa `set(CMAKE_AUTORCC ON)` atau lupa masukin `.qrc` ke `add_executable()` → resource gak ke-compile → semua path `:/...` invalid.
  3. Prefix mismatch antara `.qrc` dan path di kode.
  4. Path file di `.qrc` relative ke lokasi `.qrc` itu sendiri, **bukan** ke `CMakeLists.txt`.

## Hasil eksperimen
- **Eksp 1 (hilangin `:` dari path):** `QPixmap` jadi null, muncul warning runtime `QPainter::drawPixmap: Pixmap is a null pixmap`. Build tetap sukses — QRC path salah = silent failure di runtime, gak ada compile error.
- **Eksp 2 (matikan `CMAKE_AUTORCC`):** Build tetap sukses tapi `.qrc` jadi XML mati. Pixmap null, `QFile::open()` return false, label nampilin fallback string `"(File tidak terbaca)"`.
- **Eksp 3 (QDirIterator list semua resource):** Output nunjukin ratusan resource bawaan Qt di prefix `:/qt-project.org/styles/commonstyle/images/...` (ikon dialog standar, media controls, file manager), plus `:/qt-project.org/qmessagebox/images/qtlogo-64.png`. Insight: **QtWidgets sendiri pakai QRC** buat ikon-ikon default. Resource user (`:/assets/...`, `:/text/...`) muncul di bagian bawah list.

## Jawaban cek paham
1. **Strategy untuk default_theme (read-only) + user_theme (editable)?** → Pilihan **(A)**: default di QRC, user di disk (`QStandardPaths::AppConfigLocation`). Alasan: QRC read-only — kalau user_theme di QRC, user gak bisa save tema kustomnya. Sebaliknya, kalau default_theme di disk, user bisa rusakin atau hapus → fallback hilang → app crash. Pola idiomatik: `QFile::exists(userPath) ? userPath : ":/themes/default.json"`.
2. **Bedanya `<file>hello.txt</file>` vs `<file alias="hello.txt">hello.txt</file>` di kasus ini?** → Identik (alias sama persis dengan nama file fisik). **Skenario alias bermanfaat:** ketika nama file fisik panjang/aneh, contoh `Inter-VariableFont_slnt,wght.ttf` (dari Google Fonts) → akses dari kode sebagai `":/fonts/inter.ttf"` (Cara B) jauh lebih bersih daripada `":/fonts/Inter-VariableFont_slnt,wght.ttf"` (Cara A). Keuntungan tambahan: **decoupling** — kalau file fisik di-rename (mis. update versi font), cukup ubah `.qrc`, kode C++ gak perlu disentuh.

## Catatan tambahan
- Path file di `.qrc` selalu **relatif ke folder `.qrc`** — bukan ke `CMakeLists.txt`. Penting kalau `.qrc` taruhnya di subfolder.
- Resource path support `QFile`, `QDir`, `QPixmap`, `QImage`, `QIcon`, `QSvgRenderer`, dan `QTextStream` — transparent ke API I/O.
- Bisa pakai ikon bawaan Qt langsung (`:/qt-project.org/...`) tapi **anti-pattern** — path internal bisa berubah antar versi. Pakai `QStyle::standardIcon(QStyle::SP_DialogHelpButton)` yang adaptive ke OS theme.
- Buat list isi QRC saat runtime (debug): `QDirIterator(":", QDirIterator::Subdirectories)`.
- Untuk file besar (>1MB) yang mau di-embed, tambahin atribut `<file compress="9">file.dat</file>` di `.qrc` — RCC akan zlib-compress, decompress saat akses.
- Qt Creator punya **QRC editor GUI** — double-click `.qrc` di project tree untuk edit visual (Add Prefix, Add Files), auto-save dan auto-include ke build.
