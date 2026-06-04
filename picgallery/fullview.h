#ifndef FULLVIEW_H
#define FULLVIEW_H

// TODO MINI-PROJECT FASE 6 — FullView Dialog
//
// Tanggung jawab class ini:
// 1. Dialog modal yang nampilin foto fullsize (QLabel + setPixmap)
// 2. Tombol "Apply Sepia" → convert QImage, manipulate pixel, set pixmap baru
// 3. Tombol "Reset" → kembalikan ke original
// 4. Tombol "Close" → tutup dialog
// 5. Multi-bahasa via tr() + changeEvent override
// 6. Accessibility: accessibleName/Description, tab order
//
// Pattern sepia (untuk setiap pixel):
//   gray = 0.3*R + 0.59*G + 0.11*B
//   r_new = clamp(gray + 40, 0, 255)
//   g_new = clamp(gray + 20, 0, 255)
//   b_new = clamp(gray - 20, 0, 255)
//
// Pattern referensi:
// - Topik 27 (QImage): toImage + convertToFormat + setPixel/pixelColor
// - Topik 29 (i18n): tr() + changeEvent
// - Topik 30 (a11y): semantic naming

#include <QDialog>

// TODO: include yang lo butuhkan

class FullView : public QDialog {
    Q_OBJECT
public:
    FullView(const QString& imagePath, QWidget* parent = nullptr);

protected:
    void changeEvent(QEvent* e) override;

private slots:
    void onApplySepia();
    void onReset();

private:
    void retranslateUi();
    QImage applySepiaFilter(const QImage& original);

    QString filePath;
    QPixmap originalPixmap;

    // TODO: deklarasi widget (imageLabel, button, dll)
};

#endif
