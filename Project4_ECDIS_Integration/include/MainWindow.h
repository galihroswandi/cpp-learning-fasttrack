#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <vector>

namespace S57 {
struct Feature;
}

class QPushButton;
class QLabel;
class QGraphicsView;
class QGraphicsScene;
class QListWidget;
class QStatusBar;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(const QString& defaultFile, QWidget* parent = nullptr);
    ~MainWindow() override;

private slots:
    void onLoadChart();
    void onOpenFile();
    void onResetView();

private:
    void setupUi();
    void setupScene();
    void renderFeatures(const std::vector<S57::Feature>& features);
    void clearScene();
    void writeLog(const QString& message);
    void updateStatus(const QString& message);

    QString currentFilePath;
    QGraphicsView* view;
    QGraphicsScene* scene;
    QPushButton* loadButton;
    QPushButton* openButton;
    QPushButton* resetButton;
    QLabel* fileLabel;
    QListWidget* logList;
    QStatusBar* statusBar;
};

#endif // MAINWINDOW_H
