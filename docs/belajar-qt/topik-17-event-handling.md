# Topik 17 — Event Handling Lanjutan
Diarsipkan: 2026-05-29 (dari CATATAN_CPP.md — Fase 2 Topik 4)
Project: [modelview_basic/](../../modelview_basic/)

## Ringkasan konsep
Event di Qt **gak datang lewat `connect()`** — tapi lewat **override method** spesifik di widget (`keyPressEvent`, `mouseMoveEvent`, `closeEvent`, dll). Setelah handle event, **wajib lempar ke parent** (`QMainWindow::keyPressEvent(e)`) supaya event default Qt (Tab navigation, shortcut, dll) tetap jalan. Untuk intercept event dari child widget, pakai **event filter** (`installEventFilter`) karena Qt **tidak otomatis bubble event** ke parent seperti DOM.

## Analogi JavaScript/React
| Web event | Qt override |
|---|---|
| `addEventListener('keydown', ...)` | `keyPressEvent(QKeyEvent* e)` override |
| `addEventListener('mousemove', ...)` | `mouseMoveEvent(QMouseEvent* e)` override |
| `addEventListener('beforeunload', ...)` | `closeEvent(QCloseEvent* e)` override |
| Event bubble otomatis ke parent | TIDAK otomatis — pakai event filter |
| `e.preventDefault()` | `event->accept()` / `event->ignore()` |

## Kode inti
```cpp
class MainWindow : public QMainWindow {
protected:
    void keyPressEvent(QKeyEvent* e) override {
        if (e->key() == Qt::Key_Escape) {
            close();
        } else {
            QMainWindow::keyPressEvent(e);     // WAJIB lempar ke parent
        }
    }

    void closeEvent(QCloseEvent* event) override {
        if (yakin) event->accept();             // window ditutup
        else       event->ignore();             // batal close
    }
};

// Mouse tracking — default OFF (cuma trigger saat tombol ditekan)
setMouseTracking(true);
central->setMouseTracking(true);

// Event filter — intercept event dari child
central->installEventFilter(this);

bool MainWindow::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::MouseMove) {
        auto* me = static_cast<QMouseEvent*>(event);
        statusBar()->showMessage(QString("x:%1 y:%2")
            .arg(me->pos().x()).arg(me->pos().y()));
    }
    return QMainWindow::eventFilter(obj, event);   // chain ke parent
}
```

## Aturan penting
- **Kapan pakai event filter:** intercept event dari child widget (yang gak bisa di-override karena bukan custom class).
- **Kapan pakai event override:** widget lo sendiri yang mau handle event-nya.
- **Common mistake:** lupa panggil `QMainWindow::keyPressEvent(e)` → Tab navigation, shortcut Qt, semua mati.
- **Common mistake:** `setMouseTracking(false)` (default) → mouseMoveEvent cuma jalan saat tombol ditekan.

## Catatan tambahan
- Event flow: target widget → parent → grandparent. Setiap level bisa "konsumsi" event dengan `event->accept()` atau lempar lanjut.
- `event->accept()` vs `event->ignore()`:
  - `accept` = "gue handle, gak usah propagate"
  - `ignore` = "gue gak handle, lanjut propagate ke parent"
- Untuk shortcut keyboard, lebih baik pakai `QAction` + `setShortcut()` daripada handle `keyPressEvent` manual — auto integrasi dengan menu.
