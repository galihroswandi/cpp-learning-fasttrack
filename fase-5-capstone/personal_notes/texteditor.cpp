#include "texteditor.h"
#include "theme.h"

TextEditor::TextEditor(QWidget *parent) : QWidget{parent}
{
    stack = new QStackedWidget;

    emptyView = buildEmptyState();
    editView = editState();

    stack->addWidget(emptyView);
    stack->addWidget(editView);
    stack->setCurrentIndex(0);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(stack);

    connect(saveButton, &QPushButton::clicked, this, &TextEditor::onSaveNote);
    connect(delButton, &QPushButton::clicked, this, &TextEditor::onDelNote);

    applyStyle();
}

QWidget* TextEditor::buildEmptyState()
{
    QWidget* empty = new QWidget;
    QVBoxLayout* lay = new QVBoxLayout(empty);
    lay->setAlignment(Qt::AlignCenter);

    // Icon
    QLabel* iconLabel = new QLabel;
    QPixmap pix(":/icons/resources/icons/empty-state.svg");
    iconLabel->setPixmap(pix.scaled(120, 120, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    iconLabel->setAlignment(Qt::AlignCenter);

    // Text
    QLabel* textLabel = new QLabel("Pilih catatan untuk mulai menulis");
    textLabel->setAlignment(Qt::AlignCenter);
    textLabel->setStyleSheet("color: #888; font-size: 16px;");

    lay->addWidget(iconLabel);
    lay->addWidget(textLabel);
    return empty;
}

QWidget* TextEditor::editState()
{
    QWidget* editView = new QWidget();

    header = new EditorHeader();
    QWidget* footerWidget = new QWidget;
    footerWidget->setObjectName("footer-widget");

    note = new QTextEdit();
    note->setObjectName("note");

    QHBoxLayout* footerAction = new QHBoxLayout(footerWidget);
    saveButton = new QPushButton("Simpan");
    saveButton->setObjectName("save-button");
    saveButton->setCursor(Qt::PointingHandCursor);

    delButton = new QPushButton("Hapus");
    delButton->setObjectName("del-button");
    delButton->setCursor(Qt::PointingHandCursor);

    footerAction->addWidget(saveButton);
    footerAction->addWidget(delButton);
    footerAction->addStretch();

    QVBoxLayout* layout = new QVBoxLayout(editView);
    layout->addWidget(header);
    layout->addWidget(note, 1);
    layout->addWidget(footerWidget);

    return editView;
}

void TextEditor::applyStyle()
{
    setStyleSheet(QString(R"(
        QWidget#footer-widget {
            border-top: 1px solid %4;
        }

        QTextEdit#note {
            font-family: "JetBrains Mono";
            font-size: 14px;
            background-color: %1;
            border: none;
            padding: 5px;
            color: %2;
        }

        QPushButton {
            border-radius: 6px;
            padding: 10px 20px;
            font-size: 16px;
        }

        QPushButton#save-button {
            background-color: %3;
        }

        QPushButton#del-button {
            background-color: %1;
            border: 1px solid %4;
            color: %5;
        }
    )").arg(Theme::BG, Theme::INK, Theme::ACCENT, Theme::RULE, Theme::INK_SOFT));
}

void TextEditor::onSelectedNote(int id)
{
    if(!id) return;

    stack->setCurrentIndex(1);

    QSqlQuery query;
    query.prepare("SELECT title, content, updated_at FROM notes WHERE id = :id");
    query.bindValue(":id", id);

    if(!query.exec())
    {
        qWarning() << "Gagal load note : " << query.lastError().text();
    }

    if(query.next())
    {
        QString title = query.value(0).toString();
        QString noteContent = query.value(1).toString();
        QDateTime lastUpdate = query.value(2).toDateTime();

        note->setText(noteContent);
        header->setTitle(title);
        header->setLastUpdated(lastUpdate);

        currentId = id;
    }
}

void TextEditor::onSaveNote()
{
    if(currentId <= 0)
    {
        QMessageBox::warning(this, "Info", "Pilih note dulu");
        return;
    }

    QSqlQuery query;
    query.prepare("UPDATE notes SET title = :title, content = :content, updated_at = CURRENT_TIMESTAMP WHERE id = :id");
    query.bindValue(":title", header->getTitle());
    query.bindValue(":content", note->toPlainText());
    query.bindValue(":id", currentId);

    if(!query.exec())
    {
        QMessageBox::critical(this, "Failed", "Failed to save note : "+query.lastError().text());
        return;
    }

    if(query.numRowsAffected() == 0)
    {
        QMessageBox::warning(this, "Info", "Data note tidak ada");
        return;
    }

    QMessageBox::information(this, "Success", "Note Saved Successfully");
    emit reloadData(currentId);
    onSelectedNote(currentId);
}

void TextEditor::onDelNote()
{
    if(currentId <= 0)
    {
        QMessageBox::warning(this, "Info", "Pilih note terlebih dahulu!");
        return;
    }

    QMessageBox::StandardButton yakin = QMessageBox::question(this, "Konfirmasi", "Apakah anda yakin ingin menghapus catatan ini ?", QMessageBox::Yes | QMessageBox::No);
    if(yakin == QMessageBox::Yes)
    {
        QSqlQuery query;
        query.prepare("DELETE FROM notes WHERE id = :id");
        query.bindValue(":id", currentId);

        if(!query.exec())
        {
            QMessageBox::information(this, "Failed", "Gagal menghapus catatan !");
            return;
        }

        QMessageBox::information(this, "Success", "Catatan berhasil dihapus!");
        emit reloadData(currentId);

        stack->setCurrentIndex(0);
    }
}