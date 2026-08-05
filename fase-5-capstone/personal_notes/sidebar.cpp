#include "sidebar.h"
#include "theme.h"

Sidebar::Sidebar(QWidget *parent) : QWidget{parent}
{
    setObjectName("sidebar");
    addButton = new QPushButton("+ Catatan baru", this);
    addButton->setObjectName("add-button");
    addButton->setCursor(QCursor(Qt::PointingHandCursor));

    listWidget = new QListWidget();
    listWidget->setObjectName("list-note");
    listWidget->setFocusPolicy(Qt::NoFocus);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(addButton);
    layout->addWidget(listWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->setStretch(1, 1);

    connect(addButton, &QPushButton::clicked, this, &Sidebar::onAddClicked);
    connect(listWidget, &QListWidget::currentItemChanged, this, &Sidebar::onSelectedItem);

    applyStyling();
    loadNote();
}

void Sidebar::onSelectedItem(QListWidgetItem* current, QListWidgetItem*)
{
    if(!current)return;
    int id = current->data(Qt::UserRole).toInt();
    emit noteSelectedId(id);
}

void Sidebar::loadNote()
{
    listWidget->clear();

    QSqlQuery query;
    query.exec("SELECT id, title, created_at, content FROM notes");

    while(query.next())
    {
        setListItem(query.value(0).toInt(), query.value(1).toString(), query.value(2).toDateTime());
    }
}

void Sidebar::onAddClicked()
{
    QSqlQuery query;
    query.prepare("INSERT INTO notes (title, content) VALUES (:title, :content)");
    query.bindValue(":title", "Catatan baru");
    query.bindValue(":content", "");

    if (!query.exec()) {
        qWarning() << "Insert gagal:" << query.lastError().text();
        return;
    }

    int newId = query.lastInsertId().toInt();
    qDebug() << "Note baru dengan id:" << newId;
    emit Sidebar::onNoteAdd(newId);
    listWidget->clear();
    loadNote();
}


void Sidebar::setListItem(int id, QString text, QDateTime waktu)
{
    QListWidgetItem* item = new QListWidgetItem;
    QWidget* card = new QWidget;
    card->setCursor(Qt::PointingHandCursor);

    QHBoxLayout* hbox = new QHBoxLayout(card);

    waktu.setTimeZone(QTimeZone::UTC);
    QDateTime jakarta = waktu.toTimeZone(QTimeZone("Asia/Jakarta"));

    textItem = new QLabel(text);
    textItem->setObjectName("list-title");
    time = new QLabel(jakarta.toString("hh:mm"));
    time->setObjectName("list-time");

    hbox->addWidget(textItem);
    hbox->addStretch();
    hbox->addWidget(time);

    item->setSizeHint(QSize(0, 50));

    item->setData(Qt::UserRole, id);
    listWidget->addItem(item);
    listWidget->setItemWidget(item, card);
}

void Sidebar::applyStyling()
{
    setStyleSheet(QString(R"(
        QPushButton#add-button {
            background-color: %1;
            border-radius: 6px;
            padding: 7px 6px;
            font-size: 16px;
            color: white;
            margin: 10px;
        }

        QListWidget#list-note {
            border: none;
            font-size: 16px;
            background-color: %2;
            color: %4;
        }

        QListWidget#list-note::item {
            font-weight: bold;
            padding: 8px;
            border: none;
        }

        QListWidget#list-note QLabel#list-title {
            color: %4;
        }

        QListWidget#list-note QLabel#list-time {
            color: %5;
        }

        QListWidget#list-note::item:selected {
            background-color: %3;
            border: none;
            border-left: 3px solid %1;
            outline: none;
        }

        QListWidget#list-note::item:hover {
            background-color: %3;
        }
    )").arg(Theme::ACCENT, Theme::BG, Theme::SELBG, Theme::INK, Theme::INK_MUTED));
}