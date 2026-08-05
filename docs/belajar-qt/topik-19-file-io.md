# Topik 19 — File I/O
Diarsipkan: 2026-05-29 (dari CATATAN_CPP.md — Fase 3 Topik 6)
Project: [fileio_basic/](../../fase-3-advanced/19-file-io/)

## Ringkasan konsep
Qt punya `QFile` + `QTextStream` untuk baca/tulis text file dengan handling cross-platform line ending. Flag `QFile::Text` penting — auto-convert `\r\n` (Windows) ↔ `\n` (Unix). Selalu cek `file.open()` return value sebelum operasi. Pattern app editor standar: track `document()->isModified()` untuk Save (langsung tulis kalau path ada) vs Save As (selalu show file dialog). `closeEvent` cek modified → tanya user simpan dulu.

## Analogi JavaScript/React
| Node.js | Qt |
|---|---|
| `fs.readFileSync(path, 'utf-8')` | `QFile + QTextStream::readAll()` |
| `fs.writeFileSync(path, data)` | `QFile + QTextStream operator<<` |
| `Buffer` untuk binary | `QFile::readAll()` return `QByteArray` |
| Browser File API dialog | `QFileDialog::getOpenFileName()` |

## Kode inti
```cpp
// Baca
QFile file(path);
if (!file.open(QFile::ReadOnly | QFile::Text)) return;
QTextStream in(&file);
editor->setPlainText(in.readAll());
file.close();

// Tulis
QFile out(path);
if (!out.open(QFile::WriteOnly | QFile::Text)) return;
QTextStream ts(&out);
ts << editor->toPlainText();
out.close();
editor->document()->setModified(false);        // reset flag manual

// File dialog
QString path = QFileDialog::getOpenFileName(
    this, "Buka", "", "Text (*.txt);;All (*)");
if (path.isEmpty()) return;                    // user cancel

// Save vs Save As
void onSimpan() {
    if (filePath.isEmpty()) {
        filePath = QFileDialog::getSaveFileName(...);
        if (filePath.isEmpty()) return;
    }
    // tulis ke filePath...
}

// closeEvent + isModified
void closeEvent(QCloseEvent* event) {
    if (editor->document()->isModified()) {
        auto jawab = QMessageBox::question(this, "Konfirmasi",
            "Simpan sebelum keluar?",
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (jawab == QMessageBox::Yes) { onSimpan(); event->accept(); }
        else if (jawab == QMessageBox::No) event->accept();
        else event->ignore();
    } else {
        event->accept();
    }
}
```

## Aturan penting
- **Kapan pakai `QFile::Text`:** semua text file — handle line ending cross-platform.
- **Kapan TIDAK pakai `QFile::Text`:** binary file (image, audio, .db) — `\r\n` conversion bakal corrupt data.
- **Common mistake:** lupa cek `file.open()` return value → `readAll()` return empty string, gak ada warning.
- **Common mistake:** `setModified(false)` gak dipanggil setelah save → close window masih nanya "Simpan?" padahal udah disimpan.

## Catatan tambahan
- `QFileDialog::getSaveFileName()` return `""` kalau user cancel — wajib cek `isEmpty()`.
- Filter format: `"Text (*.txt);;All Files (*)"` — pakai `;;` (double semicolon) sebagai separator.
- Untuk file besar, baca per-baris: `while (!in.atEnd()) { QString line = in.readLine(); ... }`.
- `QSaveFile` lebih aman untuk write — write ke temp file dulu, baru atomic rename ke target. Hindari corrupt kalau crash di tengah write.
