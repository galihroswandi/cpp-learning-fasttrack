#include "editorheader.h"
#include "theme.h"

EditorHeader::EditorHeader(QWidget* parent) : QWidget(parent)
{
    setObjectName("editor-header");
    setAttribute(Qt::WA_StyledBackground, true);

    titleInput = new QLineEdit();
    titleInput->setPlaceholderText("Masukan Judul");
    titleInput->setObjectName("note-title");

    QString time = QDateTime::currentDateTime().toString("dd MMM yyyy, hh:mm");
    timeLabel = new QLabel("Terakhir diubah · " + time);
    timeLabel->setObjectName("time-label");

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(titleInput);
    layout->addWidget(timeLabel);
    layout->setSpacing(5);

    applyStyle();
}

QString EditorHeader::getTitle()
{
    return titleInput->text();
}

void EditorHeader::setTitle(QString title)
{
    titleInput->setText(title);
}

void EditorHeader::setLastUpdated(QDateTime lastUpdate)
{
    lastUpdate.setTimeZone(QTimeZone::UTC);
    QDateTime jakarta = lastUpdate.toTimeZone(QTimeZone("Asia/Jakarta"));

    QString text = QString("Terakhir diubah · %1").arg(jakarta.toString("dd MMM yyyy, hh:mm"));
    timeLabel->setText(text);
}

void EditorHeader::applyStyle()
{

    setStyleSheet(QString(R"(
        EditorHeader {
            border-bottom: 1px solid %3;
            padding: 0 10px;
        }

        QLineEdit#note-title {
            background-color: %1;
            font-family: "JetBrains Mono";
            font-size: 24px;
            border: none;
            padding: 5px 4px;
            color: %4;
        }

        QLineEdit#note-title::placeholder {
            color: rgba(154, 148, 131, 0.5);
            text-opacity: 0.5;
        }

        QLabel#time-label {
            color: %2;
        }
    )").arg(Theme::BG, Theme::INK_MUTED, Theme::RULE, Theme::INK));
}