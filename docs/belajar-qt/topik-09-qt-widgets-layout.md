# Topik 9 — Qt Widgets & Layout
Diarsipkan: 2026-05-29 (dari CATATAN_CPP.md — Sesi 9)

## Ringkasan konsep
Qt punya 2 application class: **`QCoreApplication`** untuk console/non-GUI (cuma event loop), dan **`QApplication`** untuk GUI (wajib kalau pakai widget). Widget di Qt **selalu dialokasikan di heap pakai `new`** dan punya parent — parent otomatis hapus child saat dihancurkan (Qt ownership model). Layout (`QVBoxLayout`, `QHBoxLayout`, `QGridLayout`) handle positioning otomatis dan responsive saat window resize. `QMainWindow` butuh `setCentralWidget()` sebelum bisa taruh widget.

## Analogi JavaScript/React
| HTML / React | Qt Widget |
|---|---|
| `<span>`, `<p>` | `QLabel` |
| `<button>` | `QPushButton` |
| `<input type="text">` | `QLineEdit` |
| `<body>` | `QMainWindow` |
| `<div style="display: flex; flex-direction: column">` | `QVBoxLayout` |
| `<div style="display: flex">` | `QHBoxLayout` |

## Kode inti
```cpp
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr) : QMainWindow(parent) {
        QWidget* central = new QWidget(this);
        setCentralWidget(central);              // WAJIB

        QVBoxLayout* layout = new QVBoxLayout(central);
        QHBoxLayout* hbox = new QHBoxLayout();  // nested layout

        label = new QLabel("teks", this);
        tombol = new QPushButton("Klik", this);

        layout->addWidget(label);
        layout->addLayout(hbox);                // ownership berpindah

        connect(tombol, &QPushButton::clicked, this, &MainWindow::onKlik);
    }
private slots:
    void onKlik() {
        QString text = QString("Lat %1, Lon %2").arg(-6.2).arg(106.8);
        label->setText(text);
    }
private:
    QLabel* label;
    QPushButton* tombol;
};
```

## Aturan penting
- **Kapan pakai `QApplication` vs `QCoreApplication`:** ada widget = `QApplication`; pure backend/CLI = `QCoreApplication`.
- **Kapan pakai pointer untuk widget:** selalu. `QObject` copy constructor di-delete, harus heap-allocated dengan parent.
- **Common mistake:** lupa `setCentralWidget()` → widget gak muncul di `QMainWindow`. Atau bikin widget tanpa parent → memory leak kalau lo lupa delete manual.
- **Common mistake:** stack-allocated widget keluar scope sebelum show → window kosong/crash.

## Catatan tambahan
- `QString::number(nilai, 'f', 2)` — format angka fixed, 2 desimal.
- `QString::arg(...)` — string interpolation, support multiple `%1`, `%2`, dst.
- Layout otomatis manage size policy widget. Untuk override, pakai `widget->setSizePolicy(...)`.
- `addLayout()` vs `addWidget()` — addLayout untuk nesting layout, addWidget untuk widget biasa.
