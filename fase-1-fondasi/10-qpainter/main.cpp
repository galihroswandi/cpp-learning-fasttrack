#include "chartwidget.h"

#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget window;
    window.setWindowTitle("ECDIS Chart");

    ChartWidget* chart = new ChartWidget(&window);
    QPushButton* btnToggle = new QPushButton("Toggle Stop & Go", &window);

    QVBoxLayout* layout = new QVBoxLayout(&window);
    layout->addWidget(chart);
    layout->addWidget(btnToggle);

    QObject::connect(btnToggle, &QPushButton::clicked, chart, &ChartWidget::toggleTimer);

    window.show();
    return a.exec();
}
