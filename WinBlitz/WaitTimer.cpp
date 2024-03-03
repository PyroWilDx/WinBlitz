#include "WaitTimer.h"
#include "ui_WaitTimer.h"
#include "MainWindow.h"
#include <QRandomGenerator>
#include <QTimer>

WaitTimer::WaitTimer(QWidget *parent)
        : NotClosable(parent), ui(new Ui::WaitTimer) {
    ui->setupUi(this);

    setSecLeft(QRandomGenerator::global()->bounded(2, 16));

    gTimer = new QTimer();
    connect(gTimer, &QTimer::timeout, this, &WaitTimer::onTimerTick);
    gTimer->start(1000);

    connect(ui->Button, &QPushButton::clicked, this, &WaitTimer::onButtonClicked);
}

WaitTimer::~WaitTimer() {
    delete gTimer;

    delete ui;
}

void WaitTimer::setSecLeft(int value) {
    secLeft = std::max(value, 0);
    ui->Timer->setText(QString::number(secLeft));
}

void WaitTimer::onTimerTick() {
    setSecLeft(secLeft - 1);
}

void WaitTimer::onButtonClicked() {
    if (secLeft == 0) {
        MainWindow::getInstance()->removeWindow(this);
        return;
    }
}
