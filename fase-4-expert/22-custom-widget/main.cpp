#include "circle_button.h"

#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMainWindow window;
    QWidget* central = new QWidget(&window);
    window.setCentralWidget(central);

    QVBoxLayout* layout = new QVBoxLayout(central);
    QLabel* label = new QLabel("Belum diklik", central);
    label->setAlignment(Qt::AlignCenter);

    CircleButton* btn = new CircleButton("Klik", QColor(0, 0, 255), central);

    // btn->setDisabled(true);
    layout->addWidget(label);
    layout->addWidget(btn, 0, Qt::AlignCenter);

    QObject::connect(btn, &CircleButton::clicked, [label](){
        label->setText("Diklik!");
    });

    window.setWindowTitle("Custom Widget");
    window.resize(300, 250);
    window.show();

    return a.exec();
}
