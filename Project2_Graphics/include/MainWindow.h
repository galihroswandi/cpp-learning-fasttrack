#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class GraphicsView;
class QPushButton;
class QSlider;
class QLabel;
class QStatusBar;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private slots:
    void onResetView();
    void onZoomIn();
    void onZoomOut();
    void onZoomChanged(int value);

private:
    void setupUi();
    void setupScene();

    QWidget* centralWidget;
    GraphicsView* view;
    QPushButton* resetButton;
    QPushButton* zoomInButton;
    QPushButton* zoomOutButton;
    QSlider* zoomSlider;
    QLabel* zoomLabel;
    QStatusBar* statusBar;
};

#endif // MAINWINDOW_H
