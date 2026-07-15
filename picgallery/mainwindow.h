#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// TODO MINI-PROJECT FASE 6 — MainWindow
//
// Tanggung jawab class ini:
// 1. Window utama dengan toolbar/button row:
//    - "Open Folder" → QFileDialog::getExistingDirectory
//    - "🇬🇧 English" + "🇮🇩 Indonesia" → emit changeLanguageRequested signal
// 2. QListWidget mode IconMode untuk grid thumbnail (atau QGridLayout pilihan lo)
// 3. Klik thumbnail → buka FullView dialog dengan path foto
// 4. Override changeEvent(LanguageChange) → retranslateUi()
// 5. Accessibility:
//    - setAccessibleName + setAccessibleDescription untuk tombol
//    - setTabOrder eksplisit
//    - "Open Folder" sebagai default button
//
// Pattern referensi:
// - Topik 16 (Model/View): QListWidget IconMode untuk thumbnail grid
// - Topik 17 (Event): changeEvent override
// - Topik 27 (QPixmap): scaled() untuk thumbnail
// - Topik 30 (a11y): setAccessibleName, setBuddy, setTabOrder

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QPaintEvent>

// TODO: include yang lo butuhkan

class MainWindow : public QWidget {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);

signals:
    void changeLanguageRequested(const QString& code);

// protected:
//     void changeEvent(QEvent* e) override;

// private slots:
//     void onOpenFolder();
//     void onThumbnailClicked(/* TODO: parameter sesuai signal yang lo connect */);

private:
//     void retranslateUi();
//     void loadFolder(const QString& path);
    QWidget* buildTopBar();
    QWidget* buildEmptyWidget();
    QWidget* buildFooter();
    void applyStyle();

    // TODO: deklarasi member widget (button, list, dll)
    QPushButton* btnAddFile;
    QPushButton* btnEN;
    QPushButton* btnID;
};

#endif
