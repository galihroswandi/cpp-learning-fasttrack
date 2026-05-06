#include "MainWindow.h"

#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QListWidget>
#include <QSlider>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QTimer>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      centralWidget(new QWidget(this)),
      titleLabel(new QLabel(tr("ECDIS Chart Loader"), this)),
      chartNameInput(new QLineEdit(this)),
      loadButton(new QPushButton(tr("Load Chart"), this)),
      clearButton(new QPushButton(tr("Clear Log"), this)),
      logList(new QListWidget(this)),
      zoomSlider(new QSlider(Qt::Horizontal, this)),
      zoomLabel(new QLabel(tr("Zoom: 100%"), this)),
      statusBar(new QStatusBar(this)) {
    setupUi();
}

MainWindow::~MainWindow() = default;

void MainWindow::setupUi() {
    setCentralWidget(centralWidget);
    centralWidget->setObjectName("centralWidget");

    titleLabel->setStyleSheet("font-size: 20px; font-weight: bold;");
    chartNameInput->setPlaceholderText(tr("Enter S-57/S-101 chart filename..."));
    zoomSlider->setRange(50, 200);
    zoomSlider->setValue(100);

    auto* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(12, 12, 12, 12);
    mainLayout->setSpacing(10);

    auto* topLayout = new QHBoxLayout();
    topLayout->addWidget(titleLabel);
    topLayout->addStretch();
    mainLayout->addLayout(topLayout);

    auto* inputLayout = new QHBoxLayout();
    inputLayout->addWidget(chartNameInput);
    inputLayout->addWidget(loadButton);
    mainLayout->addLayout(inputLayout);

    auto* sliderLayout = new QHBoxLayout();
    sliderLayout->addWidget(zoomLabel);
    sliderLayout->addWidget(zoomSlider);
    mainLayout->addLayout(sliderLayout);

    mainLayout->addWidget(new QLabel(tr("Activity Log:"), this));
    mainLayout->addWidget(logList, 1);

    auto* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(clearButton);
    mainLayout->addLayout(buttonLayout);

    setStatusBar(statusBar);
    statusBar->showMessage(tr("Ready"));

    connect(loadButton, &QPushButton::clicked, this, &MainWindow::onLoadChartClicked);
    connect(clearButton, &QPushButton::clicked, logList, &QListWidget::clear);
    connect(chartNameInput, &QLineEdit::textChanged, this, &MainWindow::onChartNameChanged);
    connect(zoomSlider, &QSlider::valueChanged, this, &MainWindow::onZoomChanged);
}

void MainWindow::onLoadChartClicked() {
    const QString chartName = chartNameInput->text().trimmed();

    if (chartName.isEmpty()) {
        writeLog(tr("Please enter a chart name before loading."));
        statusBar->showMessage(tr("Chart name is required"));
        return;
    }

    writeLog(tr("Loading chart: %1").arg(chartName));
    statusBar->showMessage(tr("Loading chart..."));

    QTimer::singleShot(800, this, [this, chartName]() {
        writeLog(tr("Chart '%1' loaded successfully.").arg(chartName));
        statusBar->showMessage(tr("Chart loaded"));
    });
}

void MainWindow::onChartNameChanged(const QString& text) {
    if (text.trimmed().isEmpty()) {
        statusBar->showMessage(tr("Enter chart filename"));
    } else {
        statusBar->showMessage(tr("Ready to load '%1' ").arg(text));
    }
}

void MainWindow::onZoomChanged(int value) {
    zoomLabel->setText(tr("Zoom: %1%" ).arg(value));
    writeLog(tr("Zoom changed to %1%.").arg(value));
    statusBar->showMessage(tr("Zoom set to %1%" ).arg(value));
}

void MainWindow::writeLog(const QString& message) {
    logList->addItem(message);
    logList->scrollToBottom();
}
