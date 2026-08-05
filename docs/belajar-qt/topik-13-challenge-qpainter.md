# Topik 13 — Challenge: QPainter
Diarsipkan: 2026-05-29 (dari CATATAN_CPP.md — Fase 1 Challenge 3)
Project: [qt_painter/](../../fase-1-fondasi/13-challenge-qpainter/)

## Ringkasan konsep
Challenge: bikin custom widget yang gambar shape (lingkaran, garis, teks) di canvas. Tujuan: paham siklus `update()` → `paintEvent()` (sama seperti `requestAnimationFrame()` → render callback), dan kenapa `fillRect` di awal paintEvent penting (= clear frame sebelumnya, mirip `clearRect` di Canvas web).

## Analogi JavaScript/React
```js
// Web — game loop
function render() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    ctx.fillStyle = 'red';
    ctx.fillRect(x, y, 50, 50);
    requestAnimationFrame(render);
}
```
```cpp
// Qt — paintEvent dipanggil setiap update()
void paintEvent(QPaintEvent*) override {
    QPainter p(this);
    p.fillRect(rect(), Qt::black);              // ≈ clearRect
    p.setBrush(Qt::red);
    p.drawRect(x, y, 50, 50);
}
// trigger redraw — bukan panggil paintEvent langsung
update();
```

## Kode inti
```cpp
class CanvasWidget : public QWidget {
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent*) override {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);

        // 1. Clear/background
        p.fillRect(rect(), QColor(30, 30, 40));

        // 2. Shape
        p.setPen(QPen(Qt::yellow, 3));
        p.setBrush(Qt::darkRed);
        p.drawEllipse(QPoint(width()/2, height()/2), 60, 60);

        // 3. Garis & teks
        p.setPen(Qt::white);
        p.drawLine(0, 0, width(), height());
        p.drawText(QPoint(10, 20), "Custom Canvas");
    }
};
```

## Aturan penting
- **Kapan pakai `paintEvent` override:** custom widget yang butuh drawing manual.
- **Kapan TIDAK pakai:** UI standar — pakai widget bawaan + QSS.
- **Common mistake:** panggil `paintEvent()` langsung dari kode → Qt protest. Pakai `update()`.
- **Common mistake:** lupa `fillRect` di awal → jejak gambar frame sebelumnya tetap kelihatan (animasi smear).
- **Common mistake:** `QPainter p` di luar paintEvent → target gak ada, drawing gak muncul.

## Catatan tambahan
- `QPainter` constructor: `QPainter painter(this)` mengaktifkan painting; destructor auto-end painting saat keluar scope. Jangan call `begin()`/`end()` manual.
- `rect()` return `QRect` dengan ukuran widget saat ini — selalu pakai ini, bukan hardcoded ukuran.
- `QPainter::Antialiasing` smooth tapi lebih lambat — matikan untuk render banyak elemen sederhana.
