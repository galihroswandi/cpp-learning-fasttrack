#include <QApplication>
#include <QWidget>
#include <QFontDatabase>
#include <QStringList>
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>
#include <QFontMetrics>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // === 1. Load font dari QRC ===
    int fontId = QFontDatabase::addApplicationFont(":/fonts/inter.ttf");
    QString family;
    if(fontId == -1)
    {
        qWarning() << "Gagal load custom font!";
    } else {
        family = QFontDatabase::applicationFontFamilies(fontId).at(0);
        qDebug() << "Family yang dipakai: " << family;
    }

    QWidget window;
    window.setWindowTitle("QFont & Typoghraphy Demo");
    auto* root = new QVBoxLayout(&window);

    // === 2. Default Qt font (system) ===
    auto* defaultLabel = new QLabel("Default system font - apa kata default OS lo?");
    root->addWidget(defaultLabel);

    // === 3. Custom font dari QRC ===
    QFont interFont(family, 14);
    auto* customLabel = new QLabel("Custom font: Inter 14pt");
    customLabel->setFont(interFont);
    root->addWidget(customLabel);

    // === 4. Variasi weight + italic ===
    QFont boldFont(family, 18);
    boldFont.setWeight(QFont::Bold);
    auto* boldLabel = new QLabel("Bold heading style");
    boldLabel->setFont(boldFont);
    root->addWidget(boldLabel);

    QFont italicFont(family, 12);
    italicFont.setItalic(true);
    auto* italicLabel = new QLabel("Italic - biasanya untuk emphasis");
    italicLabel->setFont(italicFont);
    root->addWidget(italicLabel);

    // === 5. QFontMetrics - ukur text sebelum render ===
    QFontMetrics fm(interFont);
    QString sampleText = "Berapa lebar string ini dalam pixel?";
    int width = fm.horizontalAdvance(sampleText);
    int height = fm.height();
    auto* metricsLabel = new QLabel(QString("Text di atas: lebar = %1 px, tinggi = %2 px").arg(width).arg(height));
    root->addWidget(metricsLabel);

    // === 6. Elide (truncate dengan ellipsis) ===
    QString longText = "Ini text yang sangat panjang dan akan dipotong dengan ellipsis kalau gak muat di area sempit ya gak sih";
    QString elided = fm.elidedText(longText, Qt::ElideRight, 300);
    auto* elideLabel = new QLabel(elided);
    elideLabel->setFont(interFont);
    elideLabel->setFixedWidth(320);
    root->addWidget(elideLabel);

    // === Variasi A — synthesized bold (algoritma) ===
    QFont boldVariasiFont(family, 18);
    boldVariasiFont.setWeight(QFont::Bold);
    auto* customVariasiFont = new QLabel("This is custom variasi font");
    customVariasiFont->setFont(boldVariasiFont);
    root->addWidget(customVariasiFont);

    // Variasi B — pakai weight ekstrim
    QFont blackVariasiFont(family, 18);
    blackVariasiFont.setWeight(QFont::Black);
    auto* customBlackVariasi = new QLabel("This is custom variasi black font");
    customBlackVariasi->setFont(blackVariasiFont);
    root->addWidget(customBlackVariasi);

    window.resize(500, 350);
    window.show();

    return QApplication::exec();
}
