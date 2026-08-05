#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QListWidgetItem>
#include <QVBoxLayout>
#include <QString>
#include <QLabel>
#include <QDateTime>
#include <QTimeZone>
#include <QSqlQuery>
#include <QSqlError>

class Sidebar : public QWidget
{
    Q_OBJECT
public:
    explicit Sidebar(QWidget *parent = nullptr);

    void loadNote();

private slots:
    void onAddClicked();
    void onSelectedItem(QListWidgetItem* current, QListWidgetItem*);

signals:
    void onNoteAdd(int id);
    void noteSelectedId(int id);

private:
    QPushButton* addButton;
    QListWidget* listWidget;
    QListWidgetItem* item;
    QLabel* textItem;
    QLabel* time;

    void applyStyling();
    void setListItem(int id, QString text, QDateTime waktu);
};

#endif // SIDEBAR_H
