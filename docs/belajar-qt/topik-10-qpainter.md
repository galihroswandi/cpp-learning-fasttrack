# Topik 10 — QPainter & Rendering
Diarsipkan: 2026-05-29 (dari CATATAN_CPP.md — Sesi 10)

## Ringkasan konsep
`QPainter` adalah API drawing Qt — analog dengan Canvas 2D context di web. Semua drawing **WAJIB di dalam `paintEvent()`** yang di-override di widget — di luar itu, target drawing gak ada. Untuk trigger redraw, panggil **`update()`** (bukan `paintEvent()` langsung) — Qt akan schedule paintEvent di waktu yang tepat, mirip `requestAnimationFrame()`. Untuk posisi yang responsive saat resize, selalu pakai `width()`/`height()` (bukan koordinat hardcoded).

## Analogi JavaScript/React
| HTML5 Canvas | Qt QPainter |
|---|---|
| `requestAnimationFrame(render)` | `update()` |
| `ctx.strokeStyle = "red"` | `painter.setPen(...)` |
| `ctx.fillStyle = "blue"` | `painter.setBrush(...)` |
| `ctx.arc(x, y, r, 0, 2*PI)` | `painter.drawEllipse(QPoint(x,y), r, r)` |
| `ctx.fillRect(x, y, w, h)` | `painter.fillRect(rect, color)` |
| `ctx.clearRect(0,0,w,h)` | `painter.fillRect(rect(), bgColor)` (manual clear) |

## Kode inti
```cpp
class ChartWidget : public QWidget {
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent* event) override;
};

void ChartWidget::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Background — sekaligus clear frame sebelumnya
    painter.fillRect(rect(), QColor(20, 60, 120));

    // Lingkaran di tengah, ikut resize
    painter.setPen(QPen(QColor(255, 50, 50), 2, Qt::DashLine));
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(QPoint(width()/2, height()/2), 40, 40);

    // Teks dan garis diagonal
    painter.setPen(Qt::white);
    painter.drawText(QPoint(10, 20), "teks");
    painter.drawLine(0, 0, width(), height());
}
```

## Aturan penting
- **Kapan pakai QPainter:** custom drawing (chart, game, visualization, custom widget).
- **Kapan TIDAK pakai QPainter:** UI standar yang bisa pakai widget bawaan (QLabel, QPushButton) — overkill.
- **Common mistake:** panggil `paintEvent()` manual → tidak boleh, pakai `update()`.
- **Common mistake:** koordinat hardcoded (`painter.drawEllipse(QPoint(300, 200), ...)`) → object stuck di tempat saat window di-resize.
- **Common mistake:** lupa `fillRect` di awal paintEvent → jejak frame sebelumnya tetap kelihatan (animasi jadi smear).

## Catatan tambahan
- `painter.save()` / `painter.restore()` untuk simpan state pen/brush/transform — useful saat draw banyak elemen dengan style berbeda.
- `QPainter::Antialiasing` bikin tepi smooth, tapi lebih lambat untuk batch besar.
- Untuk transform (rotate, scale, translate): `painter.translate(x, y)` lalu `painter.rotate(deg)` — applied ke semua drawing setelahnya sampai restore.
- Drawing order = visual order (Z-index): yang digambar belakangan tampil di atas.
