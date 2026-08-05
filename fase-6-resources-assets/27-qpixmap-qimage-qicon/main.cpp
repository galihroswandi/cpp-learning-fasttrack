#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QImage>
#include <QIcon>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSize>
#include <QStyle>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget window;
    window.setWindowTitle("QPixmap, QImage, QIcon Demo");
    auto* root = new QVBoxLayout(&window);

    // 1. ==== 1. Pixmap - load & display gambar ===
    QPixmap original(":/img/images/logo.png");
    auto* pixLabel = new QLabel;
    pixLabel->setPixmap(original.scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    root->addWidget(new QLabel("<b>QPixmap (display ke layar):</b>"));
    root->addWidget(pixLabel);

    // 2. === 2. QImage - manipulasi pixel (invert warna) ===
    QImage img = original.toImage().convertToFormat(QImage::Format_RGB32);
    img.invertPixels(); // bikin negatif color
    auto* invertedLabel = new QLabel;
    invertedLabel->setPixmap(QPixmap::fromImage(img).scaled(150, 150, Qt::KeepAspectRatioByExpanding));
    root->addWidget(new QLabel("<b>QImage (pixel manipulation - inverted): </b>"));
    root->addWidget(invertedLabel);

    // 3. === 3. QIcon - multisize + state-aware di button ===
    QIcon icon(":/img/images/logo.png");
    auto* btnRow = new QHBoxLayout;

    auto* btnNormal = new QPushButton("Normal");
    btnNormal->setIcon(icon);
    btnNormal->setIconSize(QSize(32, 32));

    auto* btnDisabled = new QPushButton("Disabled");
    btnDisabled->setIcon(icon);
    btnDisabled->setIconSize(QSize(32, 32));
    btnDisabled->setEnabled(false);

    auto* btnStd = new QPushButton("Standard Icon");
    btnStd->setIcon(a.style()->standardIcon(QStyle::SP_DialogHelpButton));
    btnStd->setIconSize(QSize(40, 40));

    btnRow->addWidget(btnNormal);
    btnRow->addWidget(btnDisabled);
    btnRow->addWidget(btnStd);
    root->addWidget(new QLabel("<b>QIcon (auto-disabled state + Qt Standard icon):</b>"));
    root->addLayout(btnRow);

    window.resize(500, 600);
    window.show();
    return QApplication::exec();
}
