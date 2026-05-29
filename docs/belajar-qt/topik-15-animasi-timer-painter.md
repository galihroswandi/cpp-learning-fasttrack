# Topik 15 — Animasi: QTimer + QPainter
Diarsipkan: 2026-05-29 (dari CATATAN_CPP.md — Fase 2 Topik 2)
Project: [ball_animation/](../../ball_animation/)

## Ringkasan konsep
Kombinasi `QTimer` + `paintEvent` = pattern animasi standar di Qt. Siklus: timer tick (16ms ≈ 60fps) → slot update state (posisi, velocity) → `update()` schedule paintEvent → frame baru digambar. Pakai **velocity vector** (`dx`, `dy`) bukan string arah (`"left"`, `"right"`) — lebih mudah handle pantulan: tinggal balik tanda (`dx = -dx`).

## Analogi JavaScript/React
```js
// Web — game loop
let x = 100, dx = 3;
function tick() {
    x += dx;
    if (x < 0 || x > canvas.width) dx = -dx;
    render();
    requestAnimationFrame(tick);
}
```
```cpp
// Qt — QTimer + update()
void onTick() {
    ballX += dx;
    if (ballX - radius < 0 || ballX + radius > width()) dx = -dx;
    update();   // schedule paintEvent
}
```

## Kode inti
```cpp
class BallWidget : public QWidget {
    Q_OBJECT
public:
    BallWidget(QWidget* parent = nullptr) : QWidget(parent) {
        QTimer* timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &BallWidget::moveBall);
        timer->start(16);                      // ≈ 60fps
    }
protected:
    void paintEvent(QPaintEvent*) override {
        QPainter p(this);
        p.fillRect(rect(), Qt::black);
        p.setBrush(Qt::red);
        p.drawEllipse(QPoint(ballX, ballY), radius, radius);
    }
private slots:
    void moveBall() {
        ballX += dx;
        ballY += dy;
        if (ballX - radius < 0 || ballX + radius > width())  dx = -dx;
        if (ballY - radius < 0 || ballY + radius > height()) dy = -dy;
        update();
    }
private:
    int ballX = 100, ballY = 100;              // posisi valid (bukan 0)
    int dx = 3, dy = 2;
    int radius = 30;
};
```

## Aturan penting
- **Kapan pakai 16ms timer:** animasi smooth 60fps. Di bawah 30fps (>33ms) jadi patah-patah.
- **Boundary check pakai range, bukan equality:**
  - `if (ballX == 0)` SALAH — bola loncat 3px, bisa skip nilai 0
  - `if (ballX < 0)` BENAR — range check, gak bisa lewat
- **Inisialisasi posisi awal harus valid:**
  - `ballX(0), radius(30)` SALAH — 0-30=-30 < 0 → stuck di tepi
  - `ballX(100), radius(30)` BENAR — 100-30=70 > 0
- **Common mistake:** cek boundary SEBELUM gerak → cek posisi lama, bukan baru.

## Catatan tambahan
- Untuk animasi lebih kompleks dengan easing curve, gunakan `QPropertyAnimation` atau `QVariantAnimation` (akan dibahas di Topik 35).
- `update()` coalesce multiple call dalam satu frame — aman dipanggil berkali-kali, hanya satu paintEvent yang dihasilkan.
- Untuk multiple object animated, simpan semua state di vector, loop dalam `moveBall()`, gambar semua di `paintEvent`.
