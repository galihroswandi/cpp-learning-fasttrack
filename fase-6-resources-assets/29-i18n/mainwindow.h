#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QEvent>

class MainWindow : public QWidget {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr) : QWidget(parent) {
        auto* root = new QVBoxLayout(this);

        greetingLabel = new QLabel;
        countLabel = new QLabel;

        auto* btnRow = new QHBoxLayout;
        btnEN = new QPushButton;
        btnID = new QPushButton;
        btnRow->addWidget(btnEN);
        btnRow->addWidget(btnID);

        root->addWidget(greetingLabel);
        root->addWidget(countLabel);
        root->addLayout(btnRow);

        connect(btnEN, &QPushButton::clicked, this, [this]() {
            emit changeLanguageRequested("en");
        });
        connect(btnID, &QPushButton::clicked, this, [this]() {
            emit changeLanguageRequested("id");
        });

        retranslateUi();
    }

signals:
    void changeLanguageRequested(const QString& code);

protected:
    void changeEvent(QEvent* e) override {
        if (e->type() == QEvent::LanguageChange) {
            retranslateUi();
        }
        QWidget::changeEvent(e);
    }

private:
    void retranslateUi() {
        setWindowTitle(tr("i18n Demo"));
        greetingLabel->setText(tr("Hello, world!"));

        int count = 12;
        countLabel->setText(tr("You have %1 new messages").arg(count));

        btnEN->setText(tr("English"));
        btnEN->setToolTip(tr("Click to switch to English"));
        btnID->setText(tr("Indonesian"));
        btnID->setToolTip(tr("Click to switch to Indonesian"));
    }

    QLabel *greetingLabel, *countLabel;
    QPushButton *btnEN, *btnID;
};

#endif
