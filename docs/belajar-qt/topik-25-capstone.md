# Topik 25 — Capstone Project: Vessel Dashboard & Personal Notes
Diarsipkan: 2026-05-29 (dari CATATAN_CPP.md — Fase 5)
Project: [vessel_dashboard/](../../fase-5-capstone/vessel_dashboard/) dan [personal_notes/](../../fase-5-capstone/personal_notes/)

## Ringkasan konsep
Capstone fase 5 adalah integrasi semua konsep Qt fase 1-4 dalam project nyata. **Vessel Dashboard**: simulasi ECDIS sederhana — display vessel info dengan custom widget, QPainter rendering, dan signal/slot dari sensor simulator. **Personal Notes**: app catatan personal dengan QSplitter layout, SQLite CRUD lewat QtSql, dan QSS theming dark mode. Kedua project bukti bahwa konsep terpisah (widget + database + custom paint + theming) bisa dijahit jadi aplikasi utuh.

## Analogi JavaScript/React
- **Vessel Dashboard** = SPA React dengan canvas-based visualization (D3/Three.js) + state management.
- **Personal Notes** = Electron app sederhana dengan SQLite + dark theme — analog dengan Obsidian/Notion lite.

## Kode inti
Lihat langsung project source:
- [vessel_dashboard/](../../fase-5-capstone/vessel_dashboard/) — main.cpp, widget custom display, sensor simulator dengan QTimer.
- [personal_notes/](../../fase-5-capstone/personal_notes/) — QSplitter layout (sidebar + editor), QSqlTableModel untuk daftar note, QSS theme file.

Pattern utama yang dipakai:
- `QSplitter` untuk resizable panel layout (drag handle antara sidebar dan main editor)
- `QSqlTableModel` + `QListView` untuk daftar note dengan auto-sync
- `QTextEdit` untuk editor utama
- Trigger save dengan `QShortcut` (Ctrl+S) atau auto-save on text change (debounced QTimer)
- QSS dark theme di-load dari file `.qss` (atau embedded di QRC)

## Aturan penting
- **Kapan bikin capstone:** setelah selesai semua konsep dasar — paksa otak integrasikan, bukan cuma hafal terpisah.
- **Common mistake:** scope terlalu besar — capstone bukan untuk bikin Slack-clone, cukup integrasi konsep yang udah dipelajari.
- **Common mistake:** copy-paste kode tanpa paham → saat ada bug, gak tau di mana harus debug.
- **Pattern bagus:** mulai dari MVP (1 fitur ujung-ke-ujung), baru iterasi tambah fitur. Jangan bangun semua skeleton dulu tanpa ada yang jalan.

## Catatan tambahan
- Detail per-project gak dicatat di CATATAN_CPP.md asli — referensi langsung ke source code di repo.
- Project ini juga jadi referensi untuk fase 10 capstone lanjutan (topik 46-49) yang bakal pakai Charts, Graphics View, networking, dan resource system QRC.
- Setelah capstone, **wajib commit** ke git — jadi snapshot belajar yang bisa di-review lagi nanti.
