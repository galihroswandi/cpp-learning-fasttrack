# Topik 14 — QTimer
Diarsipkan: 2026-05-29 (dari CATATAN_CPP.md — Fase 2 Topik 1)
Project: [timer_basic/](../../timer_basic/)

## Ringkasan konsep
`QTimer` adalah padanan `setInterval`/`setTimeout` di JavaScript — emit signal `timeout` setiap interval tertentu (ms). Untuk timer berulang, pakai `timer->start(ms)` + connect signal `timeout`. Untuk timer sekali, pakai `QTimer::singleShot()`. **Jangan pakai `sleep()`** untuk delay di Qt — itu membekukan event loop, semua UI freeze. **Lambda capture** wajib eksplisit di C++ (beda dari closure otomatis JS) — pakai `[this]` supaya bisa akses member class.

## Analogi JavaScript/React
| JavaScript | Qt |
|---|---|
| `setInterval(fn, ms)` | `timer->start(ms)` + connect ke slot |
| `clearInterval(id)` | `timer->stop()` |
| `setTimeout(fn, ms)` | `QTimer::singleShot(ms, this, lambda)` |
| Closure otomatis `() => label.x = 1` | Lambda capture eksplisit `[this]() { label->setX(1); }` |

## Kode inti
```cpp
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr) : QMainWindow(parent) {
        // Setup label dst...
        timer = new QTimer(this);              // parent this → auto-delete
        connect(timer, &QTimer::timeout, this, &MainWindow::onTick);
        timer->start(1000);                    // 1 detik

        // singleShot dengan lambda
        QTimer::singleShot(5000, this, [this]() {
            //                ^^^^   ^^^^^^
            //          context Qt   C++ capture
            label->setText("5 detik berlalu");
        });
    }
private slots:
    void onTick() { counter++; label->setText(QString::number(counter)); }
private:
    QTimer* timer;
    QLabel* label;
    int counter = 0;
};
```

## Aturan penting
- **Kapan pakai `QTimer`:** animasi, polling, periodic update.
- **Kapan pakai `singleShot`:** delay sekali (debounce, splash screen, delayed init).
- **Kapan TIDAK pakai `sleep()`:** **NEVER** di GUI thread — pakai QTimer.
- **Common mistake:** lambda tanpa `[this]` akses member → compile error `'label' was not declared`.
- **Common mistake:** lupa parent saat `new QTimer()` → memory leak kalau widget di-destroy tapi timer gak.

## Catatan tambahan
- `timer->stop()` cuma stop interval, **tidak reset** state internal — `start()` lagi lanjut dari posisi sekarang.
- Interval `0` = "jalan secepat mungkin saat event loop idle" (gak instant, tetap antri event).
- Lambda capture mode:
  - `[this]` — akses member by pointer (paling umum)
  - `[&]` — capture semua by reference (hati-hati lifetime)
  - `[=]` — capture semua by value (copy)
  - `[var]` — capture spesifik
