# Topik 29 — Qt Internationalization (i18n)
Tanggal: 2026-06-03

## Ringkasan konsep
Qt i18n bikin app yang bisa **switch bahasa runtime tanpa rebuild**. Pattern: bungkus semua string user-facing dengan `tr("...")` (marker, bukan terjemahan). Tooling `lupdate` scan source code, extract semua `tr()` jadi file `.ts` (XML editable dengan slot `<translation>`). Translator isi terjemahan, lalu `lrelease` compile `.ts` → `.qm` (binary lookup table). Runtime, app load `.qm` via `QTranslator` dan `installTranslator()` — broadcast `QEvent::LanguageChange` ke semua widget. Widget yang override `changeEvent()` panggil `retranslateUi()` untuk re-execute `tr()` calls → UI update. Pakai `%1`/`%2` placeholder bukan string concat, karena urutan kata beda antar bahasa.

## Analogi JavaScript/React
| React i18next | Qt |
|---|---|
| `useTranslation('namespace').t('key')` | `tr("key")` (context = class name) |
| `en.json`, `id.json` | `app_id.ts` → `app_id.qm` |
| `i18n.changeLanguage('id')` | `qApp->installTranslator(...)` |
| `i18n.on('languageChanged', cb)` | `changeEvent(QEvent::LanguageChange)` |
| `t('msg', { count })` | `tr("...%1").arg(count)` |
| Plural with ICU MessageFormat | `tr("%n file(s)", "", n)` Qt plural rules |

## Kode inti

### CMake setup
```cmake
find_package(Qt6 REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES i18n/app_id.ts)

qt_add_translations(target_name TS_FILES ${TS_FILES})
```

### Widget yang support language switch
```cpp
class MainWindow : public QWidget {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr) : QWidget(parent) {
        // ... build UI ...
        retranslateUi();   // initial render
    }

protected:
    void changeEvent(QEvent* e) override {
        if (e->type() == QEvent::LanguageChange) {
            retranslateUi();   // re-execute tr() saat language change
        }
        QWidget::changeEvent(e);
    }

private:
    void retranslateUi() {
        setWindowTitle(tr("i18n Demo"));
        greetingLabel->setText(tr("Hello, world!"));
        countLabel->setText(tr("You have %1 new messages").arg(count));
    }
};
```

### Main + QTranslator
```cpp
QTranslator translator;
auto loadLang = [&](const QString& code) {
    if (code == "en") {
        qApp->removeTranslator(&translator);   // English = source, no translator
        return;
    }
    QString qmPath = QString(":/i18n/app_%1.qm").arg(code);
    if (translator.load(qmPath)) {
        qApp->installTranslator(&translator);  // trigger LanguageChange event
    }
};
```

### Workflow CLI
```bash
# Extract tr() ke .ts
lupdate main.cpp mainwindow.h -ts i18n/app_id.ts

# Isi terjemahan (manual atau pakai Qt Linguist GUI)
linguist i18n/app_id.ts

# Compile ke binary
lrelease i18n/app_id.ts -qm i18n/app_id.qm

# Build + run (Ctrl+B, Ctrl+R di Qt Creator)
```

## Aturan penting
- **Kapan pakai i18n:** app multi-bahasa, compliance regulasi (maritime/medical/government), branding global.
- **Kapan TIDAK pakai i18n:** app internal tim 1 bahasa — overhead developer effort gede, ROI nol. Jangan bungkus `tr()` "for future-proofing".
- **Kapan pakai `.arg(%1)` vs string concat:** SELALU `.arg()`. Concat bikin terjemahan gak natural di bahasa dengan urutan kata berbeda (Hungarian, Jepang).
- **Kapan pakai `%n` plural:** kalau angka mempengaruhi grammar (1 file vs 5 files di EN). Indonesia/Jepang gak butuh — tetap pakai `%1`.
- **Common mistake:** Q_OBJECT class di `.cpp` tanpa `#include "filename.moc"` — AUTOMOC gak reliable di sini. Best practice: class dengan Q_OBJECT di file `.h`.
- **Common mistake:** ubah string source di code tanpa jalanin `lupdate` → runtime fallback ke source (English) karena key lama gak match → translator silently broken.
- **Common mistake:** edit `.ts` manual padahal udah ada Qt Linguist GUI. Manual edit risiko XML invalid.
- **Common mistake:** typo di string source — `"Hello, world!"` vs `"Hello,  world!"` (dua space) — lookup miss, fallback ke EN.

## Hasil eksperimen
- **Eksp 1 (string mismatch):** Ubah `tr("Hello, world!")` jadi `tr("Hello, world!!!")` → klik Indonesian → label tetap English. Bukti: `.qm` lookup itu **byte-by-byte exact match**, gak ada fuzzy matching. Typo/whitespace/punctuation silently break i18n.
- **Eksp 2 (tambah string baru workflow):** Tambah `setToolTip(tr(...))` di code → jalanin `lupdate` → entry baru muncul di `.ts` dengan `type="unfinished"` → isi terjemahan → `lrelease` → rebuild → tooltip terjemah. Workflow standar production = wajib pakai `lupdate` (bukan edit XML manual).
- **Eksp 3 (placeholder %1):** Angka `count` tetap angka di semua bahasa, ditampilkan via `.arg(count)`. Translator Jepang bisa taruh `%1` di posisi berbeda dalam kalimat (`"あなたは%1件の..."`) — natural per bahasa. String concat (`"You have " + n + " messages"`) memaksa urutan fixed → unnatural di bahasa lain. Untuk plural ekstrim (Arab 6 form), pakai `%n` placeholder dengan count argument.

## Jawaban cek paham

### 1. Workflow saat polish wording string yang udah live
**Yang terjadi di `.ts` ID/JA setelah `lupdate`:**
- Entry lama (`"Vessel is approaching dangerous area"`) **gak dihapus** — ditandai `<translation type="vanished">Kapal mendekati area berbahaya</translation>`. History preserved.
- Entry baru (`"Warning: vessel approaching restricted zone"`) ditambah dengan `<translation type="unfinished"></translation>` — perlu diisi.

**Risiko deploy tanpa update terjemahan:**
- Runtime `tr("Warning: ...")` lookup di `.qm` lama → key gak match → fallback ke source EN.
- Operator non-EN (di kapal kondisi safety-critical) tiba-tiba lihat label warning kritis dalam English doang. Bisa jadi insiden.
- Audit compliance fail (regulasi maritime mengharuskan multi-bahasa).
- UI inkonsisten (sebagian label baru EN, sebagian lama ID) → user pikir app bug.

**Strategi terbaik supaya translator gak hilang context:**
- Pakai **Qt Linguist GUI** — fitur "Use translation from vanished" carry over terjemahan lama ke key baru (translator gak ngerjain dari nol). Untuk polish kecil (typo, capitalization), 80% terjemahan masih relevan.
- Konvensi tim: PR ubah string user-facing **wajib include `.ts` updated**, translator review sebelum merge.
- Hindari polish kecil string yang stabil. Batch perubahan masif di PR khusus i18n, jangan campur dengan PR feature.

### 2. Trade-off A (runtime tr lookup) vs B (cache pre-translated)
**Pilihan untuk app ECDIS:** Tetap **(A) runtime lookup** — yang code lo udah pakai sekarang.

**Alasan:** Premise "B lebih efisien" itu sebenernya **premature optimization**. `tr()` lookup hash table O(1) ~100-500 nanoseconds per call. Untuk app desktop 200 widget render 60fps = ~6ms total per detik. Negligible.

**Kenapa B sebenarnya LEBIH KOMPLEKS, bukan lebih simple:**
- Lo butuh state cache + invalidation logic
- Saat user klik switch language: `changeEvent(LanguageChange)` fire, tapi cache lo masih string lama → label gak update → **tombol switch keliatan rusak**. UX bug halus tapi parah.
- Untuk fix: lo harus implement re-translate cache di `changeEvent` → ujung-ujungnya jadi sama dengan strategi A, plus layer cache yang gak ada gunanya.

**Kapan B masuk akal (jarang):**
- Embedded system dengan CPU sangat lemah (microcontroller, kiosk hardware lama).
- Profiler **udah membuktikan** `tr()` adalah bottleneck nyata.
- Game engine HUD render text di tight loop 1000+ FPS.

**Flexibility menang:** kapten Indonesia hand-over shift ke kapten Filipina → langsung switch UI tanpa restart (gak hilang state radar tracking, unsaved log).

**Pelajaran:** percaya profiler, bukan intuisi. "Kayaknya overhead" tanpa measurement = premature optimization.

## Catatan tambahan
- **Context di `tr()`:** lookup key = `(class name, source string)`. Class beda → terjemahan beda (`"Open"` di FileDialog = "Buka", di WindowState = "Terbuka").
- **`QObject::tr("...")`** untuk konteks luar class (free function, static method).
- **`QCoreApplication::translate("Context", "...")`** untuk kontrol context manual.
- **Qt Linguist** = GUI tool dedicated untuk translator (`/home/galih/Qt/6.5.3/gcc_64/bin/linguist`). Tampilan: panel context | list string | input terjemahan + suggestion dari vanished entries.
- **`%n` plural:** `tr("%n file(s)", "", count)` — Qt pilih singular/plural form sesuai bahasa target. Polish/Russian punya 3 form, Arab 6 form. Indonesia/Jepang gak butuh plural form.
- **Locale formatting:** `QLocale::toString(number)` untuk format angka sesuai locale (1,234.56 EN vs 1.234,56 DE). `QString::number()` selalu pakai format default.
- **RTL languages:** `qApp->setLayoutDirection(Qt::RightToLeft)` saat load translator Arab/Hebrew — Qt auto-flip layout (toolbar, menu, scrollbar).
- **CMake target `update_translations`** otomatis dibuat oleh `qt_add_translations()`. Run via `cmake --build build_dir --target update_translations`.
- **English sebagai source language:** gak perlu file `.qm` untuk EN — cukup `removeTranslator(&translator)` untuk balik ke source string asli.
- **Multiple translator:** bisa stack `installTranslator(qtTranslator)` + `installTranslator(appTranslator)` — Qt cari di urutan reverse stack.
