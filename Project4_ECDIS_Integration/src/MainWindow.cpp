#include "MainWindow.h"
#include "S57Parser.h"

#include <QFileDialog>
#include <QGraphicsEllipseItem>
#include <QGraphicsPolygonItem>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPainter>

namespace {

constexpr double LonMin = -10.0;
constexpr double LonMax = 10.0;
constexpr double LatMin = -10.0;
constexpr double LatMax = 10.0;
constexpr int SceneSize = 1000;

QPointF geoToScene(double lon, double lat) {
    double x = (lon - LonMin) / (LonMax - LonMin) * SceneSize;
    double y = SceneSize - (lat - LatMin) / (LatMax - LatMin) * SceneSize;
    return QPointF(x, y);
}

} // anonymous namespace

MainWindow::MainWindow(const QString& defaultFile, QWidget* parent)
    : QMainWindow(parent)
    , currentFilePath(defaultFile)
    , view(new QGraphicsView(this))
    , scene(new QGraphicsScene(this))
    , loadButton(new QPushButton(tr("Load Chart"), this))
    , openButton(new QPushButton(tr("Open File"), this))
    , resetButton(new QPushButton(tr("Reset View"), this))
    , fileLabel(new QLabel(this))
    , logList(new QListWidget(this))
    , statusBar(new QStatusBar(this))
{
    setupUi();
    setupScene();
    onLoadChart();
}

MainWindow::~MainWindow() = default;

void MainWindow::setupUi() {
    auto* centralWidget = new QWidget(this);
    auto* mainLayout = new QHBoxLayout(centralWidget);

    auto* leftLayout = new QVBoxLayout();
    leftLayout->addWidget(fileLabel);
    leftLayout->addWidget(view);
    leftLayout->addWidget(statusBar);

    auto* rightLayout = new QVBoxLayout();
    rightLayout->addWidget(loadButton);
    rightLayout->addWidget(openButton);
    rightLayout->addWidget(resetButton);
    rightLayout->addWidget(new QLabel(tr("Loaded Features:"), this));
    rightLayout->addWidget(logList);
    rightLayout->addStretch(1);

    mainLayout->addLayout(leftLayout, 3);
    mainLayout->addLayout(rightLayout, 1);

    setCentralWidget(centralWidget);

    connect(loadButton, &QPushButton::clicked, this, &MainWindow::onLoadChart);
    connect(openButton, &QPushButton::clicked, this, &MainWindow::onOpenFile);
    connect(resetButton, &QPushButton::clicked, this, &MainWindow::onResetView);
}

void MainWindow::setupScene() {
    scene->setSceneRect(0, 0, SceneSize, SceneSize);
    view->setScene(scene);
    view->setRenderHint(QPainter::Antialiasing, true);
    view->setDragMode(QGraphicsView::ScrollHandDrag);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
}

void MainWindow::onLoadChart() {
    clearScene();
    logList->clear();

    QString displayPath = currentFilePath;
    if (displayPath.isEmpty()) {
        updateStatus(tr("No file path specified."));
        return;
    }

    fileLabel->setText(tr("Chart file: %1").arg(displayPath));
    updateStatus(tr("Parsing chart file..."));

    auto result = S57::S57Parser::parseFile(displayPath.toStdString());
    if (!result.success) {
        writeLog(QString::fromStdString(result.message));
        updateStatus(tr("Failed to load chart."));
        return;
    }

    writeLog(QString::fromStdString(result.message));
    for (const auto& feature : result.features) {
        QString featureText = QString("ID %1: %2 (%3 vertices)")
            .arg(feature.id)
            .arg(QString::fromStdString(feature.name))
            .arg(static_cast<int>(feature.vertices.size()));
        writeLog(featureText);
    }

    renderFeatures(result.features);
    updateStatus(tr("Chart loaded: %1 features rendered.").arg(static_cast<int>(result.features.size())));
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::renderFeatures(const std::vector<S57::Feature>& features) {
    scene->setBackgroundBrush(QBrush(QColor(240, 245, 255)));
    scene->addRect(0, 0, SceneSize, SceneSize, QPen(Qt::black, 1));

    for (const auto& feature : features) {
        if (feature.vertices.empty()) {
            continue;
        }

        switch (feature.type) {
            case S57::FeatureType::Point: {
                auto pt = geoToScene(feature.vertices[0].lon, feature.vertices[0].lat);
                auto* item = scene->addEllipse(pt.x() - 6, pt.y() - 6, 12, 12,
                                              QPen(Qt::blue), QBrush(Qt::blue));
                item->setToolTip(QString::fromStdString(feature.name));
                break;
            }
            case S57::FeatureType::Line: {
                QPolygonF poly;
                for (const auto& vertex : feature.vertices) {
                    poly << geoToScene(vertex.lon, vertex.lat);
                }
                auto* item = scene->addPolygon(poly, QPen(Qt::darkGreen, 2));
                item->setToolTip(QString::fromStdString(feature.name));
                break;
            }
            case S57::FeatureType::Polygon: {
                QPolygonF poly;
                for (const auto& vertex : feature.vertices) {
                    poly << geoToScene(vertex.lon, vertex.lat);
                }
                auto* item = scene->addPolygon(poly, QPen(Qt::red, 2), QBrush(QColor(255, 0, 0, 80)));
                item->setToolTip(QString::fromStdString(feature.name));
                break;
            }
            default:
                writeLog(tr("Skipped unknown feature type %1").arg(static_cast<int>(feature.type)));
                break;
        }
    }
}

void MainWindow::onOpenFile() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open mini-S57 chart"), currentFilePath, tr("S-57 Files (*.s57);;All Files (*)"));
    if (fileName.isEmpty()) {
        return;
    }
    currentFilePath = fileName;
    onLoadChart();
}

void MainWindow::onResetView() {
    view->resetTransform();
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    updateStatus(tr("View reset."));
}

void MainWindow::clearScene() {
    scene->clear();
}

void MainWindow::writeLog(const QString& message) {
    logList->addItem(message);
}

void MainWindow::updateStatus(const QString& message) {
    statusBar->showMessage(message);
}
