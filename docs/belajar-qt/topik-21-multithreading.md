# Topik 21 — Multithreading dengan QtConcurrent
Diarsipkan: 2026-05-29 (dari CATATAN_CPP.md — Fase 3 Topik 8)
Project: [thread_basic/](../../thread_basic/)

## Ringkasan konsep
**Widget Qt tidak thread-safe** — semua operasi widget WAJIB di UI thread (main thread). Untuk task berat (network call, kalkulasi panjang, file IO besar), pakai `QtConcurrent::run()` yang offload ke thread pool. Hasil di-bridge balik ke UI thread lewat `QFutureWatcher` + signal `finished`. Alternative high-level vs low-level: `QtConcurrent` untuk task sederhana satu shot; `QThread` kalau butuh kontrol lifecycle thread penuh.

## Analogi JavaScript/React
| Web | Qt |
|---|---|
| Web Worker | `QtConcurrent::run()` / `QThread` |
| `postMessage` ke worker | passing data lewat `QFuture` |
| `worker.onmessage` | `QFutureWatcher::finished` signal |
| Worker tidak bisa akses DOM | Worker thread tidak boleh akses widget |
| `async`/`await` | `QFuture::result()` (blocking) atau watcher signal (async) |

## Kode inti
```cmake
find_package(Qt6 REQUIRED COMPONENTS Widgets Concurrent)
target_link_libraries(app PRIVATE Qt6::Widgets Qt6::Concurrent)
```

```cpp
#include <QtConcurrent>
#include <QFutureWatcher>

// Fungsi di background — DILARANG akses widget
static int tugasBerat() {
    QThread::sleep(5);
    return 42;
}

class MainWindow : public QMainWindow {
public:
    MainWindow() {
        watcher = new QFutureWatcher<int>(this);
        connect(watcher, &QFutureWatcher<int>::finished,
                this, &MainWindow::onSelesai);

        progressBar->setRange(0, 0);           // indeterminate (bouncing)
        QFuture<int> future = QtConcurrent::run(tugasBerat);
        watcher->setFuture(future);
    }
private slots:
    void onSelesai() {
        int hasil = watcher->result();         // aman update widget di sini
        label->setText(QString::number(hasil));
        progressBar->setRange(0, 100);
        progressBar->setValue(100);
    }
private:
    QFutureWatcher<int>* watcher;
    QLabel* label;
    QProgressBar* progressBar;
};
```

## Aturan penting
- **Kapan pakai `QtConcurrent`:** task background sederhana yang return nilai, gak butuh thread persistent.
- **Kapan pakai `QThread`:** butuh kontrol penuh thread lifecycle (start, pause, stop, event loop di worker).
- **Common mistake:** akses widget dari worker thread → crash atau corruption. Selalu emit signal ke UI thread.
- **Common mistake:** `progressBar->setRange(0, 100)` tapi gak update value selama task jalan → bar stuck di 0%.

## Catatan tambahan
- `progressBar->setRange(0, 0)` = indeterminate mode (bouncing animation, gak tau %).
- `progressBar->setRange(0, 100); setValue(n)` = determinate mode (tau persentase).
- Untuk passing progress dari worker, pakai `QPromise` + `setProgressValue()` (Qt 6).
- Hindari shared mutable state antar thread — kalau perlu, pakai `QMutex` atau `std::atomic`.
- `QFuture<void>` untuk task yang gak return nilai; `QFutureWatcher<void>` korespondennya.
