#include "MainWindow.h"
#include "GraphicsView.h"

#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QPen>
#include <QBrush>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      centralWidget(new QWidget(this)),
      view(new GraphicsView(this)),
      resetButton(new QPushButton(tr("Reset View"), this)),
      zoomInButton(new QPushButton(tr("Zoom In"), this)),
      zoomOutButton(new QPushButton(tr("Zoom Out"), this)),
      zoomSlider(new QSlider(Qt::Horizontal, this)),
      zoomLabel(new QLabel(tr("Zoom: 100%"), this)),
      statusBar(new QStatusBar(this)) {
    setupUi();
    setupScene();
}

MainWindow::~MainWindow() = default;

void MainWindow::setupUi() {
    setCentralWidget(centralWidget);

    zoomSlider->setRange(50, 200);
    zoomSlider->setValue(100);
    zoomSlider->setTickInterval(10);
    zoomSlider->setTickPosition(QSlider::TicksBelow);

    auto* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(8);

    auto* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(resetButton);
    buttonLayout->addWidget(zoomInButton);
    buttonLayout->addWidget(zoomOutButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(zoomLabel);
    mainLayout->addLayout(buttonLayout);

    view->setMinimumSize(640, 480);
    mainLayout->addWidget(view, 1);
    mainLayout->addWidget(zoomSlider);

    setStatusBar(statusBar);
    statusBar->showMessage(tr("Ready - use mouse drag to pan, wheel to zoom"));

    connect(resetButton, &QPushButton::clicked, this, &MainWindow::onResetView);
    connect(zoomInButton, &QPushButton::clicked, this, &MainWindow::onZoomIn);
    connect(zoomOutButton, &QPushButton::clicked, this, &MainWindow::onZoomOut);
    connect(zoomSlider, &QSlider::valueChanged, this, &MainWindow::onZoomChanged);
}

void MainWindow::setupScene() {
    auto* scene = new QGraphicsScene(this);
    scene->setSceneRect(-500, -500, 1000, 1000);

    // Background grid
    QPen gridPen(QColor(200, 200, 200));
    gridPen.setWidth(0);
    for (int i = -500; i <= 500; i += 50) {
        scene->addLine(-500, i, 500, i, gridPen);
        scene->addLine(i, -500, i, 500, gridPen);
    }

    // Water area
    auto* water = scene->addRect(-500, -500, 1000, 1000, QPen(Qt::NoPen), QBrush(QColor(204, 229, 255)));
    water->setZValue(-10);

    // Coastline polygon
    QPolygonF coast;
    coast << QPointF(-400, 120) << QPointF(-300, 200) << QPointF(-120, 180)
          << QPointF(80, 260) << QPointF(220, 160) << QPointF(320, 240)
          << QPointF(420, 90) << QPointF(380, -80) << QPointF(180, -140)
          << QPointF(-40, -100) << QPointF(-220, -200) << QPointF(-420, -140);
    auto* coastItem = scene->addPolygon(coast, QPen(QColor(80, 120, 40), 4), QBrush(QColor(165, 214, 167)));
    coastItem->setZValue(0);

    // Shipping lane
    QPen lanePen(QColor(255, 140, 0), 3, Qt::DashLine);
    lanePen.setCapStyle(Qt::RoundCap);
    scene->addLine(-450, -300, 420, 320, lanePen);
    scene->addEllipse(-455, -305, 10, 10, QPen(Qt::NoPen), QBrush(Qt::red));
    scene->addEllipse(415, 315, 10, 10, QPen(Qt::NoPen), QBrush(Qt::red));

    // Example depth contour lines
    QPen contourPen(QColor(0, 102, 204), 1);
    contourPen.setStyle(Qt::DotLine);
    scene->addEllipse(-250, -250, 200, 120, contourPen);
    scene->addEllipse(100, -100, 180, 90, contourPen);

    // Navigation buoys
    QBrush buoyBrush(Qt::yellow);
    QPen buoyPen(Qt::black);
    scene->addEllipse(-180, 210, 20, 20, buoyPen, buoyBrush);
    scene->addEllipse(240, -40, 16, 16, buoyPen, buoyBrush);
    scene->addEllipse(20, 180, 18, 18, buoyPen, buoyBrush);

    // Labels
    auto* label1 = scene->addText(tr("Coastline"));
    label1->setPos(-240, 100);
    label1->setDefaultTextColor(Qt::darkGreen);

    auto* label2 = scene->addText(tr("Shipping lane"));
    label2->setPos(-200, -280);
    label2->setDefaultTextColor(Qt::darkRed);

    auto* label3 = scene->addText(tr("Depth contour"));
    label3->setPos(120, -80);
    label3->setDefaultTextColor(Qt::blue);

    view->setScene(scene);
    view->setZoom(100);
}

void MainWindow::onResetView() {
    view->resetTransform();
    view->setZoom(100);
    zoomSlider->setValue(100);
    statusBar->showMessage(tr("View reset to 100%"));
}

void MainWindow::onZoomIn() {
    int value = qMin(200, zoomSlider->value() + 10);
    zoomSlider->setValue(value);
}

void MainWindow::onZoomOut() {
    int value = qMax(50, zoomSlider->value() - 10);
    zoomSlider->setValue(value);
}

void MainWindow::onZoomChanged(int value) {
    zoomLabel->setText(tr("Zoom: %1%" ).arg(value));
    view->setZoom(value);
    statusBar->showMessage(tr("Zoom set to %1%" ).arg(value));
}
