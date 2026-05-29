# Topik 27 — QPixmap, QImage, QIcon
Tanggal: 2026-05-29

## Ringkasan konsep
Tiga kelas image di Qt dengan peran berbeda: **QImage** (CPU memory, thread-safe, untuk manipulasi pixel — invert, filter, format conversion), **QPixmap** (GPU/display memory, GUI-thread only, untuk render efisien ke widget), dan **QIcon** (container multi-resolution + state-aware untuk action/button — auto-handle disabled, hover, HiDPI). Pattern standar image processing: load → `toImage()` → manipulate → `QPixmap::fromImage()` → display. Pattern downloader: worker thread cuma boleh kerja di QImage, convert ke QPixmap di main thread saat akan ditampilkan.

## Analogi JavaScript/React
| Web | Qt |
|---|---|
| `ImageData` (Canvas getImageData) — pixel access | `QImage` |
| `<img>` element setelah loaded — siap render | `QPixmap` |
| `<img srcset="...">` adaptive resolution | `QIcon` multi-size |
| Material-UI `<Icon name="..." />` adaptive ke theme | `QStyle::standardIcon(SP_*)` |
| `object-fit: contain` | `Qt::KeepAspectRatio` |
| `object-fit: fill` | `Qt::IgnoreAspectRatio` |
| `object-fit: cover` | `Qt::KeepAspectRatioByExpanding` |

## Kode inti
```cpp
// 1. QPixmap — display
QPixmap pix(":/img/logo.png");
label->setPixmap(pix.scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));

// 2. QImage — manipulate pixel
QImage img = pix.toImage().convertToFormat(QImage::Format_RGB32);
img.invertPixels();
label2->setPixmap(QPixmap::fromImage(img));

// 3. QIcon — state-aware untuk button
QIcon icon(":/img/logo.png");
btn->setIcon(icon);
btn->setIconSize(QSize(32, 32));
btnDisabled->setIcon(icon);
btnDisabled->setEnabled(false);            // auto-greyout

// Standard icon (adapt ke OS theme)
btn->setIcon(app.style()->standardIcon(QStyle::SP_DialogHelpButton));
```

## Aturan penting
- **Kapan pakai QImage:** manipulasi pixel (filter, invert, blend), load di worker thread, format conversion eksplisit.
- **Kapan pakai QPixmap:** display ke widget, render di `paintEvent()`, cache untuk performance.
- **Kapan pakai QIcon:** asset untuk button/action/menu/toolbar yang butuh state (disabled, hover) atau multi-resolution untuk HiDPI.
- **Kapan TIDAK pakai QPixmap:** di worker thread → crash. QPixmap = GUI thread only.
- **Kapan TIDAK pakai QImage:** untuk display langsung — overhead CPU→GPU upload setiap render. Convert sekali ke QPixmap di akhir.
- **Common mistake:** load `QPixmap` di `QtConcurrent::run` → crash/warning. Solusi: `QImage::fromData()` di worker, `QPixmap::fromImage()` di UI thread.
- **Common mistake:** skip `convertToFormat()` → manipulasi behavior beda untuk file indexed-color vs RGB → bug.

## Hasil eksperimen
- **Eksp 1 (SmoothTransformation vs FastTransformation):** Smooth pakai bilinear interpolation (halus tapi lambat), Fast pakai nearest-neighbor (pixelated tapi 5-10× cepat). Default pakai Smooth untuk UI quality; Fast wajib di pixel art game atau preview realtime saat drag-resize.
- **Eksp 2 (tanpa convertToFormat):** untuk PNG RGBA standar hasilnya identik karena format internalnya sudah RGB32. Tapi untuk PNG indexed-color (palette-based), `invertPixels()` cuma flip index palette → warna acak bukan negatif. Convert eksplisit = perilaku predictable di semua input.
- **Eksp 3 (3 mode aspect ratio):**
  - `KeepAspectRatio` — fit di area, sisa space transparan (≈ `object-fit: contain`)
  - `IgnoreAspectRatio` — squashed ke exact size (≈ `object-fit: fill`)
  - `KeepAspectRatioByExpanding` — fill area penuh, sebagian terpotong (≈ `object-fit: cover`). Skenario: background image, hero section, thumbnail card uniform.

## Jawaban cek paham
1. **Pemilihan kelas per skenario:**
   - **Toolbar 8 ikon + HiDPI** → **QIcon** (state-aware disabled, multi-resolution untuk Retina).
   - **App filter foto (sepia, brightness)** → **QImage** untuk manipulasi + **QPixmap** untuk display hasil. Pattern: original ke QImage → apply filter per-pixel → `QPixmap::fromImage()` ke label.
   - **Splash screen logo 1200×600** → **QPixmap**. Pure display, no manipulation, no state.
   - **App downloader** → **QImage di worker thread** + **QPixmap di UI thread**. Kritis: QPixmap GUI-thread only, jadi worker hanya boleh decode ke QImage, lalu emit signal dengan QImage payload ke main thread untuk convert ke QPixmap saat display.

2. **Trade-off thumbnail gallery 200 foto:**
   - **Pilihan A (lazy on-scroll)** — startup cepat, RAM hemat, tapi disk I/O berulang setiap scroll bikin stutter; scroll bolak-balik = redundan baca file.
   - **Pilihan B (preload semua)** — scroll smooth, tapi startup blocking 5-10 detik, RAM tumpuk (200 × 100×100×4 ≈ 8 MB, atau 400 MB kalau 10k foto).
   - **Pilihan C (optimal)** = lazy load + cache + worker thread. Pakai `QPixmapCache` (built-in LRU) atau `QCache<QString, QPixmap>` dengan max entry. Load di worker (placeholder gray box sementara), swap saat selesai. Pattern ini di pakai semua gallery app pro (Instagram, Google Photos).

## Catatan tambahan
- `QPixmap::isNull()` cek kalau load gagal — silent fail, gak ada exception.
- Format `QImage`: `Format_RGB32`, `Format_ARGB32` (dengan alpha), `Format_Grayscale8`, `Format_Indexed8` (palette), `Format_Mono`. Konversi eksplisit untuk consistency.
- `QIcon::addFile(path, size, mode, state)` — manual control per (size, mode, state) combo. Mode: `Normal`, `Disabled`, `Active`, `Selected`. State: `On`, `Off`.
- `QStyle::SP_*` enum punya banyak standard icon: `SP_DialogOpenButton`, `SP_DialogSaveButton`, `SP_MessageBoxWarning`, `SP_DirIcon`, `SP_FileIcon`, dll.
- Untuk SVG icon (scalable lossless di HiDPI), pakai `QIcon` dengan path `.svg` — Qt punya `QSvgRenderer` di module `Svg`. Module ini perlu di-add ke CMake.
- `QPixmapCache::setCacheLimit(KB)` — set global cache size; `QPixmapCache::insert/find(key, pixmap)` API key-based.
