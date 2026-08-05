#ifndef EDITORHEADER_H
#define EDITORHEADER_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QDateTime>
#include <QLabel>
#include <QVBoxLayout>
#include <QTimeZone>
#include <QString>

class EditorHeader : public QWidget
{
    Q_OBJECT
public:
    EditorHeader(QWidget* parent = nullptr);
    void setTitle(QString title);
    QString getTitle();
    void setLastUpdated(QDateTime lastUpdate);

private:
    QLineEdit* titleInput;
    QLabel* timeLabel;

    void applyStyle();
};

#endif // EDITORHEADER_H
