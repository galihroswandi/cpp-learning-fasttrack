# Topik 12 — Challenge: Widget & Layout
Diarsipkan: 2026-05-29 (dari CATATAN_CPP.md — Fase 1 Challenge 2)
Project: [temp_conversion/](../../fase-1-fondasi/12-challenge-widget-layout/)

## Ringkasan konsep
Challenge: bikin GUI converter suhu Celsius → Fahrenheit dengan `QLineEdit` (input), `QPushButton` (trigger), dan `QLabel` (output). Layout: vertical untuk top-level, horizontal nested untuk row tombol. Kunci: validasi input pakai `QDoubleValidator` supaya user gak bisa ketik huruf, dan paham **type promotion** di C++ (`9/5` = 1 integer division, `9.0/5` = 1.8 double).

## Analogi JavaScript/React
| Web | Qt |
|---|---|
| `<input type="text" pattern="[0-9.]+">` | `lineEdit->setValidator(new QDoubleValidator(this))` |
| `parseFloat(input.value)` | `lineEdit->text().toDouble()` |
| `label.innerText = ...` | `label->setText(...)` |
| Flexbox column + row nested | `QVBoxLayout` + `QHBoxLayout` nested |

## Kode inti
```cpp
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr) : QMainWindow(parent) {
        QWidget* central = new QWidget(this);
        setCentralWidget(central);
        QVBoxLayout* root = new QVBoxLayout(central);

        input = new QLineEdit;
        input->setValidator(new QDoubleValidator(-1000, 1000, 2, this));

        QPushButton* btn = new QPushButton("Convert");
        output = new QLabel("Hasil: -");

        QHBoxLayout* row = new QHBoxLayout;
        row->addWidget(input);
        row->addWidget(btn);

        root->addLayout(row);
        root->addWidget(output);

        connect(btn, &QPushButton::clicked, this, &MainWindow::onConvert);
    }
private slots:
    void onConvert() {
        double c = input->text().toDouble();
        double f = c * 9.0 / 5.0 + 32.0;       // PENTING: 9.0 bukan 9
        output->setText(QString("Hasil: %1 F").arg(f, 0, 'f', 2));
    }
private:
    QLineEdit* input;
    QLabel* output;
};
```

## Aturan penting
- **Kapan pakai `setCentralWidget()`:** WAJIB kalau extend `QMainWindow` dan mau taruh widget di tengah.
- **Kapan pakai `QDoubleValidator`:** semua `QLineEdit` yang nerima input numerik — cegah user input invalid.
- **Common mistake type promotion:**
  - `9 / 5` = `1` (integer division)
  - `9.0 / 5` = `1.8` (one operand double → result double)
  - `inputDouble * 9 / 5` = double (karena `inputDouble * 9` udah jadi double)

## Catatan tambahan
- `addLayout()` memindahkan ownership layout ke parent layout, jadi gak perlu manual delete.
- `QDoubleValidator` punya constructor `(min, max, decimals, parent)` — kalau range gak penting, bisa `new QDoubleValidator(this)` saja.
- Untuk format output 2 desimal: `QString::number(f, 'f', 2)` atau `arg(f, 0, 'f', 2)`.
