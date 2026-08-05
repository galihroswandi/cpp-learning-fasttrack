#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), darkMode(true)
{
    QWidget* central = new QWidget(this);
    setCentralWidget(central);

    QVBoxLayout* layout = new QVBoxLayout(central);

    labelStatus = new QLabel("Qt Style Sheet Demo", this);
    labelStatus->setAlignment(Qt::AlignCenter);
    labelStatus->setObjectName("labelJudul");

    labelDescription = new QLabel("This is description", this);
    labelDescription->setAlignment(Qt::AlignCenter);

    btnPrimary = new QPushButton("Primary Button", this);
    btnDanger = new QPushButton("Danger Button", this);
    btnToggle = new QPushButton("Toggle Theme", this);
    btnAdd = new QPushButton("Add Button", this);

    btnDanger->setObjectName("btnDanger");

    QHBoxLayout* hbox = new QHBoxLayout();
    hbox->addWidget(btnPrimary);
    hbox->addWidget(btnDanger);
    hbox->addWidget(btnAdd);

    layout->addWidget(labelStatus);
    layout->addWidget(labelDescription);
    layout->addLayout(hbox);
    layout->addWidget(btnToggle);
    layout->setSpacing(12);
    layout->setContentsMargins(20, 20, 20, 20);


    connect(btnToggle, &QPushButton::clicked, this, &MainWindow::onToggleTheme);

    applyTheme();
}

void MainWindow::applyTheme()
{
    if(darkMode)
    {
        setStyleSheet(R"(
            QMainWindow, QWidget {
                background-color: #1e1e2e;
                color: #cdd6f4;
            }

            QMainWindow, QWidget, QLabel {
                font-size: 20px;
                color: #4ade80;
            }

            QLabel#labelJudul {
                font-size: 18px;
                font-weight: bold;
                color: #cba6f7;
                padding: 10px;
            }

            QPushButton {
                background-color: #313244;
                color: #cdd6f4;
                border: 1px solid #45475a;
                border-radius: 6px;
                padding: 8px 16px;
                font-size: 13px;
            }

            QPushButton:hover {
                background-color: #45475a;
            }

            QPushButton:pressed {
                background-color: #585b70;
            }

            QPushButton#btnDanger {
                background-color: #f38ba8;
                color: #1e1e2e;
                border: none;
            }

            QPushButton#btnDanger:hover{
                background-color: #eba0ac;
            }
        )");
    }else {
        setStyleSheet(R"(
            QMainWindow, QWidget {
                background-color: #eff1f5;
                color: #4c4f69;
            }

            QLabel#labelJudul {
                font-size: 18px;
                font-weight: bold;
                color: #8839ef;
                padding: 10px;
            }

            QPushButton {
                background-color: #dce0e8;
                color: #4c4f69;
                border: 1px solid #bcc0cc;
                border-radius: 6px;
                padding: 8px 16px;
                font-size: 13px;
            }

            QPushButton:hover {
                background-color: #ccd0da;
            }

            QPushButton:pressed {
                background-color: #bcc0cc;
            }

            QPushButton#btnDanger {
                background-color: #d20f39;
                color: #eff1f5;
                border:none;
            }

            QPushButton#btnDanger:hover {
                background-color: #e64553;
            }
        )");
    }

    darkMode = !darkMode;
}

void MainWindow::onToggleTheme()
{
    applyTheme();
}
















