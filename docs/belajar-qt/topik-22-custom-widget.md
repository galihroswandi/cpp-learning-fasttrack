# Topik 22 — Custom Widget
Diarsipkan: 2026-05-29 (dari CATATAN_CPP.md — Fase 4 Topik 1)
Project: [custom_widget/](../../fase-4-expert/22-custom-widget/)

## Ringkasan konsep
Custom widget = subclass `QWidget` + override `paintEvent` (drawing) + event methods (interaktivitas). Pattern: **state member** (`hovered`, `pressed`) di-update dari event method → `update()` → `paintEvent` baca state → render sesuai state. Wajib override `sizeHint()` — tanpanya widget muncul 0×0 di layout system. Setiap event method harus panggil parent (`QWidget::enterEvent(e)`) supaya event chain Qt tetap jalan.

## Analogi JavaScript/React
| React custom component | Qt custom widget |
|---|---|
| `const [hovered, setHovered] = useState(false)` | `bool hovered = false` (member) |
| `onMouseEnter` prop | `enterEvent(QEnterEvent*)` override |
| `onMouseLeave` prop | `leaveEvent(QEvent*)` override |
| `onClick` prop | `mouseReleaseEvent` + emit signal |
| JSX render method | `paintEvent` |
| `style={{ background: hovered ? 'blue' : 'gray' }}` | `if (hovered) brush = ...` di paintEvent |

## Kode inti
```cpp
class CircleButton : public QWidget {
    Q_OBJECT
public:
    CircleButton(const QString& text, QColor color, QWidget* parent = nullptr)
        : QWidget(parent), label(text), baseColor(color) {
        setCursor(Qt::PointingHandCursor);
    }

    QSize sizeHint() const override { return QSize(120, 120); }   // WAJIB

signals:
    void clicked();

protected:
    void paintEvent(QPaintEvent*) override {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);

        QColor bg = baseColor;
        if (pressed)      bg = baseColor.darker(140);
        else if (hovered) bg = baseColor.lighter(120);

        p.setBrush(bg);
        p.setPen(Qt::NoPen);
        p.drawEllipse(rect());

        p.setPen(Qt::white);
        p.drawText(rect(), Qt::AlignCenter, label);
    }

    void enterEvent(QEnterEvent* e) override {
        hovered = true; update();
        QWidget::enterEvent(e);
    }
    void leaveEvent(QEvent* e) override {
        hovered = false; pressed = false; update();
        QWidget::leaveEvent(e);
    }
    void mousePressEvent(QMouseEvent* e) override {
        if (e->button() == Qt::LeftButton) { pressed = true; update(); }
    }
    void mouseReleaseEvent(QMouseEvent* e) override {
        if (e->button() == Qt::LeftButton && pressed) {
            pressed = false; update();
            emit clicked();
        }
    }

private:
    QString label;
    QColor baseColor;
    bool hovered = false, pressed = false;
};
```

## Aturan penting
- **Kapan bikin custom widget:** UI elemen yang gak ada di Qt bawaan (gauge, radar display, custom button shape).
- **Kapan TIDAK bikin custom widget:** kalau pakai widget bawaan + QSS cukup — jangan over-engineer.
- **Common mistake:** lupa `sizeHint()` override → widget muncul ukuran 0×0, gak kelihatan.
- **Common mistake:** `mouseReleaseEvent` tanpa cek `&& pressed` → klik dari luar yang berakhir di widget juga trigger clicked().
- **Common mistake:** lupa `update()` setelah state berubah → tampilan stuck di state lama.

## Catatan tambahan
- `darker(n)` / `lighter(n)`: n > 100 = lebih gelap/terang. Default kalau gak pass: 200.
- Cursor harus dikembalikan di `leaveEvent` kalau widget ganti cursor saat hover.
- Untuk widget yang banyak state, pertimbangkan pakai enum: `enum class State { Normal, Hover, Pressed, Disabled }`.
- Untuk emit signal dari paintEvent → SALAH. Emit dari event handler (klik), bukan dari render.
