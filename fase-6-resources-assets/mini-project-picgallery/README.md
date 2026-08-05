# 🎯 Mini-Project Fase 6 — PicGallery i18n

Image viewer multi-bahasa dengan custom theming. Integrasi 5 konsep Fase 6 dalam 1 app.

## Tech checklist

- [ ] **QRC** (Topik 26) — font + theme + .qm di-embed di binary
- [ ] **QPixmap/QImage/QIcon** (Topik 27) — thumbnail grid + sepia filter
- [ ] **QFont** (Topik 28) — custom font di-bundle + applied global
- [ ] **i18n** (Topik 29) — switch ID/EN realtime, `tr()` + QTranslator
- [ ] **Accessibility** (Topik 30) — semantic naming + tab order + keyboard nav

## Workflow rekomendasi (urutan kerja)

1. **Setup skeleton** (sudah disiapkan): CMakeLists, mainwindow.h, fullview.h, main.cpp, resources.qrc, dark.qss, i18n/picgallery_id.ts.
2. **Implementasi MainWindow bare minimum** — window kosong + tombol Open Folder + grid kosong. Build + run.
3. **Open folder logic** — QFileDialog, scan folder, populate grid dengan thumbnail QPixmap.
4. **Klik thumbnail → FullView dialog** — display fullsize image.
5. **Sepia filter** — pakai QImage manipulasi pixel.
6. **Custom font** — download Inter, taruh di assets/fonts/, daftarin di QRC, load di main.cpp.
7. **Dark theme** — load dark.qss dari QRC.
8. **i18n** — bungkus semua string dengan tr(), jalanin lupdate, isi terjemahan ID, lrelease, embed .qm di QRC, setup loadLang lambda di main.cpp.
9. **Accessibility** — accessibleName/Description, setTabOrder chain, setDefault, multi-modal status.
10. **Test offline** — copy binary ke /tmp, jalanin, pastikan tetap kerja.
11. **Commit** ke git dengan pesan jelas.

## Asset yang lo perlu download/siapkan

- **Font** Inter (atau pilihan lo): https://fonts.google.com/specimen/Inter → taruh `Inter-Regular.ttf` di `assets/fonts/`.
- **Foto sample** untuk testing: bisa pakai foto pribadi atau download bebas dari Unsplash.

## Folder struktur

```
picgallery/
├── CMakeLists.txt          ← sudah disiapkan
├── README.md               ← file ini
├── main.cpp                ← TODO: load font/theme/translator
├── mainwindow.h            ← TODO: implement window + grid + signals
├── fullview.h              ← TODO: implement dialog + sepia filter
├── resources.qrc           ← sudah disiapkan, isi font/qm setelah ready
├── assets/
│   ├── fonts/              ← taruh .ttf di sini
│   └── themes/
│       └── dark.qss        ← sudah disiapkan
└── i18n/
    ├── picgallery_id.ts    ← akan ke-populate oleh lupdate
    └── picgallery_id.qm    ← ke-generate oleh lrelease
```

## Build commands

```bash
# Build & run via Qt Creator: open CMakeLists.txt, Ctrl+R

# Workflow translation:
lupdate main.cpp mainwindow.h fullview.h -ts i18n/picgallery_id.ts
# Isi terjemahan di .ts
lrelease i18n/picgallery_id.ts -qm i18n/picgallery_id.qm
# Rebuild di Qt Creator
```

## Acceptance criteria

Lihat brief lengkap di percakapan Claude. App lo selesai kalau:

1. ✅ Open folder + grid thumbnail
2. ✅ Klik thumbnail → full view + sepia filter
3. ✅ Multi-bahasa ID/EN switch realtime
4. ✅ Custom font + dark theme bundled QRC
5. ✅ Accessibility (keyboard nav + semantic name)
6. ✅ Offline & portable
7. ✅ Commit ke git

## Cara kerja sama Claude

Lo implement sendiri. Claude cuma intervene saat lo:
- Stuck dan ketik "stuck" + describe masalahnya
- Mau code review (tunjukin file yang lo kerjain)
- Butuh hint specific (jangan minta full solution — pikir dulu)

Setelah selesai semua AC, tunjukin demo ke Claude untuk wrap-up review + commit.
