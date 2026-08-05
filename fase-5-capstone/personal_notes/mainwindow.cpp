#include "mainwindow.h"
#include "sidebar.h"
#include "texteditor.h"
#include "theme.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setMinimumSize(768, 600);

    QSplitter *splitter = new QSplitter(this);
    setCentralWidget(splitter);
    splitter->setObjectName("wrapper");

    Sidebar *sidebar = new Sidebar(splitter);
    sidebar->setObjectName("sidebar");
    sidebar->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    TextEditor *textEditor = new TextEditor(splitter);
    textEditor->setObjectName("editor");
    textEditor->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    splitter->addWidget(sidebar);
    splitter->addWidget(textEditor);
    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 1);
    splitter->resize(600, 400);

    connect(sidebar, &Sidebar::noteSelectedId, textEditor, &TextEditor::onSelectedNote);
    connect(textEditor, &TextEditor::reloadData, sidebar, &Sidebar::loadNote);

    applyTheme();
}

MainWindow::~MainWindow()
{
    QSqlDatabase db = QSqlDatabase::database();
    db.close();
}

void MainWindow::applyTheme()
{
    setStyleSheet(QString(R"(
        QSplitter#wrapper::handle {
            background-color: %3;
            width: 2px;
        }

        QSplitter#wrapper {
            background-color: %1;
            color: %2;
        }

        QWidget#editor {
            background-color: %2;
        }
    )")
    .arg(Theme::BG, Theme::INK, Theme::RULE));
}