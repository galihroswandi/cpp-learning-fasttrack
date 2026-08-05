#include "mainwindow.h"
#include "theme.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIcon>
#include <QSize>
#include <QPixmap>
#include <QImage>

MainWindow::MainWindow(QWidget* parent): QWidget(parent)
{
    auto* root = new QVBoxLayout(this);

    root->setContentsMargins(0,0,0,0);
    root->addWidget(buildTopBar());
    root->addWidget(buildEmptyWidget(), 1);
    root->addWidget(buildFooter());

    applyStyle();
}

QWidget *MainWindow::buildFooter()
{
    QWidget* footer = new QWidget;
    footer->setObjectName("app-footer");
    footer->setAttribute(Qt::WA_StyledBackground, true);

    QHBoxLayout* footerLayout = new QHBoxLayout(footer);
    footerLayout->setContentsMargins(12, 6, 12, 6);

    QWidget* statusWidget = new QWidget;
    statusWidget->setStyleSheet("background-color: transparent;");
    auto* statusLayout = new QHBoxLayout(statusWidget);
    auto* dotStatus = new QLabel;
    dotStatus->setFixedSize(10, 10);
    dotStatus->setStyleSheet(QString("background-color: %1; border-radius: 5px;").arg(Theme::green));
    auto* statusLabel = new QLabel(tr("Ready"));
    statusLayout->addWidget(dotStatus);
    statusLayout->addWidget(statusLabel);

    auto* loadedCountLabel = new QLabel(tr("0 photos loaded"));
    loadedCountLabel->setStyleSheet("background-color: transparent;");
    footerLayout->addWidget(statusWidget);
    footerLayout->addStretch();
    footerLayout->addWidget(loadedCountLabel);

    return footer;
}

QWidget *MainWindow::buildEmptyWidget()
{
    // ======= EMPTY WIDGET =======
    QWidget* emptyWidget = new QWidget;
    emptyWidget->setObjectName("empty-widget");

    // Load Image Alternative empty
    QVBoxLayout* emptyLayout = new QVBoxLayout(emptyWidget);
    QPixmap emptyIcon(":/images/empty.png");
    emptyLayout->setAlignment(Qt::AlignCenter);

    auto* pixAltEmptyImage = new QLabel;
    pixAltEmptyImage->setPixmap(emptyIcon.scaled(150,150, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    auto* emptyLabel = new QLabel(tr("No photos yet"));
    emptyLabel->setAlignment(Qt::AlignCenter);

    auto* emptyDescription = new QLabel("<p>Click <strong>Open Folder</strong> to load all photos from a directory,<br> or <strong>Add Files</strong> to pick individual photos.</p>");
    emptyDescription->setAlignment(Qt::AlignCenter);

    emptyLayout->addWidget(pixAltEmptyImage, 0, Qt::AlignCenter);
    emptyLayout->addWidget(emptyLabel);
    emptyLayout->addWidget(emptyDescription);

    return emptyWidget;
}


QWidget *MainWindow::buildTopBar()
{
    auto *topbarWidget = new QWidget;
    auto* headerLayout = new QHBoxLayout(topbarWidget);
    topbarWidget->setObjectName("app-topbar");

    // Create Folder Button
    QIcon folderIcon(":/icons/folder.svg");
    btnAddFile = new QPushButton(tr(" &O pen Folder"));
    btnAddFile->setIcon(folderIcon);
    btnAddFile->setIconSize(QSize(24, 24));

    // Create language widget
    QWidget* languageWidget = new QWidget;
    languageWidget->setObjectName("language-wrapper");
    languageWidget->sizeHint();
    languageWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    auto* btnRow = new QHBoxLayout(languageWidget);
    btnEN = new QPushButton("🇬🇧 EN");
    btnEN->setObjectName("active");
    btnID = new QPushButton("🇮🇩 ID");
    btnRow->addWidget(btnEN);
    btnRow->addWidget(btnID);

    headerLayout->addWidget(btnAddFile);
    headerLayout->addStretch();
    headerLayout->addWidget(languageWidget);

    return topbarWidget;
}

void MainWindow::applyStyle()
{
    setStyleSheet(QString(R"(
        QWidget#app-topbar {
            background-color: %1;
            border-bottom: 1px solid %2;
        }

        QWidget#language-wrapper {
            background-color: #313244;
            border: 1px solid #45475a;
            padding: 1px;
            border-radius: 6px;
        }

        QWidget#language-wrapper QPushButton {
            border: none;
            padding: 4px 8px;
            border-radius: 4px;
            font-size: 16px;
        }

        QWidget#language-wrapper QPushButton#active {
            border: none;
            background-color: #89b4fa;
            color: #1e1e2e;
        }

        QWidget#app-footer {
            background-color: %1;
            border-top: 1px solid %2;
        }
    )").arg(Theme::mantle, Theme::surface0));
}