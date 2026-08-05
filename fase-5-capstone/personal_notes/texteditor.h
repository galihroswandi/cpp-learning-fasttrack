#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H
#include "editorheader.h"

#include <QObject>
#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QDateTime>
#include <QString>
#include <QLabel>
#include <QPalette>
#include <QSize>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QStackedWidget>

class TextEditor : public QWidget
{
    Q_OBJECT
public:
    explicit TextEditor(QWidget *parent = nullptr);

private slots:
    void onSaveNote();
    void onDelNote();

public slots:
    void onSelectedNote(int id);

signals:
    void reloadData(int id);

private:
    QTextEdit* note;
    QPushButton* saveButton;
    QPushButton* delButton;
    EditorHeader* header;
    QStackedWidget* stack;
    QWidget* emptyView;
    QWidget* editView;
    int currentId = -1;

    void applyStyle();
    QWidget* buildEmptyState();
    QWidget* editState();
};

#endif // TEXTEDITOR_H
