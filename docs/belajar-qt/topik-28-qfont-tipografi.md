# Topik 28 — QFont & Tipografi
Tanggal: 2026-06-02

## Ringkasan konsep
**QFont** itu *value object* yang mendeskripsikan font (family, size, weight, italic). Untuk konsistensi lintas OS, jangan andalkan font sistem — **bundle font sendiri lewat QRC** lalu register pakai `QFontDatabase::addApplicationFont()`. Hal kritis: **family name yang ke-register sering beda dari nama file** (contoh: `Inter-Regular.ttf` → family `"Inter 18pt"`). Selalu ambil nama resmi via `applicationFontFamilies(fontId)` — jangan hardcode string nama font. Untuk Bold/Italic asli (bukan synthesized yang jelek), load file weight terpisah atau pakai variable font. Apply font default seluruh app pakai `qApp->setFont()` di `main()` — single source of truth.

## Analogi JavaScript/React
| Web/CSS | Qt |
|---|---|
| `@font-face { src: url('inter.woff2') }` | `QFontDatabase::addApplicationFont(":/fonts/inter.ttf")` |
| `font-family: 'Inter', sans-serif` | `QFont("Inter", 14)` |
| `font-size: 14pt` (DPI-aware) | `font.setPointSize(14)` |
| `font-size: 14px` (exact pixel) | `font.setPixelSize(14)` |
| `font-weight: 700` | `font.setWeight(QFont::Bold)` |
| `font-style: italic` | `font.setItalic(true)` |
| `text-overflow: ellipsis` | `QFontMetrics::elidedText()` |
| `ctx.measureText(s).width` | `QFontMetrics::horizontalAdvance(s)` |
| CSS Reset / global theme | `qApp->setFont(appFont)` |

## Kode inti
```cpp
// 1. Load font + ambil family name resmi (best practice)
int fontId = QFontDatabase::addApplicationFont(":/fonts/inter.ttf");
QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);

// 2. Apply font global ke seluruh app
QFont appFont(family, 14);
qApp->setFont(appFont);

// 3. Override per-widget untuk exception
QFont headingFont(family, 24);
headingFont.setWeight(QFont::Bold);
headingLabel->setFont(headingFont);

// 4. QFontMetrics untuk ukur text
QFontMetrics fm(appFont);
int width = fm.horizontalAdvance("Sample text");
int height = fm.height();
QString elided = fm.elidedText(longText, Qt::ElideMiddle, 300);
```

## Aturan penting
- **Kapan bundle font sendiri:** app yang harus tampil konsisten lintas OS, app brand-driven, app fullscreen/kiosk.
- **Kapan pakai font sistem:** native look-and-feel sengaja (admin tool, dev tool yang harus blend in).
- **Kapan `setPointSize()` vs `setPixelSize()`:** point untuk UI text (DPI-aware, otomatis adjust Retina); pixel untuk text yang harus exact pixel (grid table, screenshot generator).
- **Common mistake:** hardcode `QFont("Inter")` padahal family resmi `"Inter 18pt"` → silent fallback ke font generik, lo gak ngeh. Pakai `applicationFontFamilies()`.
- **Common mistake:** `setBold(true)` padahal cuma load file Regular → synthesized fake bold (jelek). Load Bold file terpisah atau pakai variable font.
- **Common mistake:** apply font per-widget di semua tempat → ganti font default butuh find-replace di 100 file. Pakai `qApp->setFont()` global.

## Hasil eksperimen
- **Eksp 1 (Inter vs Inter 18pt):** Family name yang ke-register `"Inter 18pt"` bukan `"Inter"` (Google Fonts pecah Inter jadi varian optical-size). Code dengan `QFont("Inter")` silent fallback ke font generik — keliatan beda hanya saat side-by-side dengan `QFont("Inter 18pt")`. Lebar text berubah dari 313 → 307 px = bukti konkret font BENERAN ganti, bukan ilusi visual.
- **Eksp 2 (decoupling pattern):** Dengan `family = applicationFontFamilies(fontId).at(0)`, ganti font Inter → Roboto cukup swap file di folder `fonts/`, **0 baris main.cpp** yang diubah. Pattern decoupling = robust terhadap perubahan asset.
- **Eksp 3 (synthesized bold vs black):** Load cuma Regular, lalu setWeight `Bold (700)` vs `Black (900)` — hasilnya **hampir identik**. Karena Qt synthesize keduanya dari glyph Regular yang sama, algoritma penebalan stroke gak bisa bedain Bold dari Black tanpa reference asli. Bukti: weight constants cuma intent, rendering aktual butuh glyph yang sesuai.
- **Eksp 4 (ElideMiddle):** Kepake saat awal DAN akhir text punya info penting — file path, URL, transaction ID, breadcrumb. `ElideRight` untuk prefix-heavy (judul artikel, label).

## Jawaban cek paham
1. **Strategy bundling untuk app ECDIS cross-OS dengan heading bold + angka monospace + warning italic** → **(C) Bundle multiple file font** (Inter Regular + Bold + Italic + JetBrains Mono Regular). Alasan: konsistensi lintas OS terjamin (font asli bukan sistem), Bold/Italic asli (bukan synthesized), monospace dedicated untuk angka align rapi. (A) salah karena font sistem beda lintas OS → tampilan inkonsisten. (B) kurang ideal karena synthesized bold jelek. (D) variable font lebih advanced/optimal tapi (C) lebih safe untuk learning.

2. **Global vs per-widget font setting** → Pendekatan **B (qApp->setFont)** untuk app dengan ratusan widget. Alasan: single source of truth, ganti font global cukup 1 baris, widget baru otomatis inherit. **Konsekuensi pendekatan A** (per-widget): designer minta ganti font → find & replace di puluhan file → risiko miss satu widget → inkonsistensi. Persis seperti CSS Reset di web — set baseline global sekali, override exception aja. **Pendekatan A masih dipakai untuk override exception**: heading yang lebih besar, monospace untuk angka GPS, warning label khusus.

## Catatan tambahan
- **Variable font (Qt 6.5+):** 1 file `.ttf` punya semua weight kontinyu (100-900). Lebih kecil dari multiple static files, support weight non-standard (350, 450). Gunakan `QFont::setWeight(QFont::Weight(550))` untuk weight custom.
- **Font fallback chain:** `font.setFamilies({"Inter", "Helvetica", "sans-serif"})` — Qt coba family pertama dulu, fallback ke berikutnya kalau gak ada.
- **`QFontDatabase::families()`** return semua family yang tersedia (sistem + bundled) — useful untuk debug "kenapa font gue gak ke-load".
- **QSS sebagai alternative apply font:** `setStyleSheet("QLabel { font-family: 'Inter 18pt'; font-size: 14pt; }")` — lebih konsisten kalau lo udah pakai QSS theme. QSS dan QFont bisa coexist.
- **Letter spacing**: `font.setLetterSpacing(QFont::PercentageSpacing, 110)` (110% = renggang) atau `AbsoluteSpacing` untuk control pixel-level.
- **Word spacing**: `font.setWordSpacing(5)` — extra pixel antar kata.
- **Hint:** `font.setHintingPreference(QFont::PreferNoHinting)` matikan hinting (untuk preview cetak). Default `PreferDefaultHinting` ngikut sistem.
- **QFontMetricsF** (versi float) untuk presisi sub-pixel — pakai kalau lo butuh layout super-presisi (font sample preview, kerning editor).
