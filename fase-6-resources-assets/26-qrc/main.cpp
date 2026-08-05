#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QPixmap>
#include <QLabel>
#include <QFile>
#include <QIODevice>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget window;

    window.setWindowTitle("QRC Basic");

    auto* layout = new QVBoxLayout(&window);

    // 1. Load gambar dari QRC
    auto* imgLabel = new QLabel;
    QPixmap pix(":/assets/images/logo.png");
    imgLabel->setPixmap(pix.scaled(128, 128, Qt::KeepAspectRatio));
    layout->addWidget(imgLabel);
\
    // 2. Load text dari QRC (pakai alias)
    QFile file(":/text/hello.txt");
    QString isi = "(File tidak terbaca)";
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        isi = in.readAll();
        file.close();
    }
    layout->addWidget(new QLabel(isi));

    window.resize(400, 300);
    window.show();

    return QApplication::exec();
}
