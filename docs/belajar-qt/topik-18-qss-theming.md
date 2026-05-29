# Topik 18 — QSS / Theming
Diarsipkan: 2026-05-29 (dari CATATAN_CPP.md — Fase 3 Topik 5)
Project: [qss_basic/](../../qss_basic/)

## Ringkasan konsep
**QSS (Qt Style Sheets)** adalah CSS untuk Qt — syntax hampir identik. Apply ke 3 level: seluruh app (`qApp->setStyleSheet`), per-window (`mainWindow->setStyleSheet`), atau per-widget (`button->setStyleSheet`, mirip inline style). Untuk pseudo-state seperti `:hover`, lo **wajib tulis eksplisit** — Qt gak punya default hover effect kayak browser. Selector class CSS (`.btn`) gak ada — pakai `#objectName` setelah `setObjectName("btnDanger")`.

## Analogi JavaScript/React
| CSS / Web | QSS |
|---|---|
| Global stylesheet | `qApp->setStyleSheet(...)` |
| Component scoped CSS | `widget->setStyleSheet(...)` |
| Inline `style={{...}}` | `widget->setStyleSheet(...)` (specific) |
| `:hover` (default browser ada efek) | `:hover` (Qt tidak ada default — wajib eksplisit) |
| `.classname` | Tidak ada — pakai `#objectName` |
| `#id` | `#objectName` (set via `setObjectName()`) |

## Kode inti
```cpp
// Cara apply
qApp->setStyleSheet("...");                    // seluruh app
mainWindow->setStyleSheet("...");              // window + child
button->setStyleSheet("...");                  // widget ini saja

// setObjectName WAJIB untuk selector #id
btnDanger->setObjectName("btnDanger");

// Raw string literal (mirip template literal JS)
setStyleSheet(R"(
    QPushButton {
        background: #313244;
        border-radius: 6px;
        padding: 8px 16px;
    }
    QPushButton:hover   { background: #45475a; }
    QPushButton:pressed { background: #585b70; }
    QPushButton#btnDanger { background: #f38ba8; }
)");
```

## Aturan penting
- **Kapan pakai global QSS:** theme app (dark mode, brand color) — apply di `main()`.
- **Kapan pakai widget-level QSS:** override spesifik untuk 1 widget tanpa polusi global.
- **Common mistake:** lupa tulis `:hover` state → button gak ada efek hover.
- **Common mistake:** pakai `.classname` → gak ngaruh, Qt gak support class selector.
- **Spesifisitas:** `#objectName` > `WidgetType` > inherited dari parent.

## Catatan tambahan
- QSS support sebagian besar property CSS standar: `color`, `background`, `border`, `padding`, `margin`, `font`, `border-radius`.
- Selector lain: `QPushButton[flat="true"]` (attribute), `QPushButton:disabled`, `QPushButton:focus`.
- Untuk pseudo-state combo: `QPushButton:hover:pressed { ... }`.
- QSS bisa di-load dari file: baca `.qss` file, lalu `setStyleSheet(content)`. Atau embed di QRC (`:/styles/theme.qss`).
- Hot-reload theme: pakai `QFileSystemWatcher` watch `.qss` file, re-apply saat berubah.
