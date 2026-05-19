#include "counterwidget.h"

CounterWidget::CounterWidget(QWidget* parent): QWidget(parent), count(0)
{
    label = new QLabel("0", this);
    toggleButton = new QPushButton("Stop", this);
    resetButton = new QPushButton("Reset", this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    QHBoxLayout* hlayout = new QHBoxLayout();
    layout->addWidget(label);
    layout->addLayout(hlayout);
    hlayout->addWidget(toggleButton);
    hlayout->addWidget(resetButton);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &CounterWidget::onTick);
    connect(toggleButton, &QPushButton::clicked, this, &CounterWidget::onToggle);
    connect(resetButton, &QPushButton::clicked, this, &CounterWidget::onReset);

    timer->start(1000);

    QTimer::singleShot(5000, this, [this](){
        label->setText("5 Detik berlalu");
    });
}

void CounterWidget::onTick()
{
    count++;
    label->setText(QString::number(count));
}

void CounterWidget::onToggle()
{
    if(timer->isActive())
    {
        timer->stop();
        toggleButton->setText("Start");
    }
    else
    {
        timer->start(100);
        toggleButton->setText("Stop");
    }
}

void CounterWidget::onReset()
{
    count = 0;
    label->setText(QString::number(count));
}