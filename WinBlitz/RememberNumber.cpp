#include "RememberNumber.h"
#include "ui_RememberNumber.h"
#include "MainWindow.h"
#include <QRandomGenerator>
#include <QTimer>

RememberNumber::RememberNumber(QWidget *parent)
        : NotClosable(parent), ui(new Ui::RememberNumber) {
    ui->setupUi(this);

    gName = "Remember Number";

    int nLength = QRandomGenerator::global()->bounded(2, 8);
    rdNumber = 0;
    for (int i = 0; i < nLength; i++) {
        rdNumber *= 10;
        rdNumber += QRandomGenerator::global()->bounded(10);
    }
    ui->Number->setText(QString::number(rdNumber));

    waitTime = QRandomGenerator::global()->bounded(4, 10);
    waitTime *= 1000;
    gTimer = new QTimer();
    connect(gTimer, &QTimer::timeout, this, &RememberNumber::onTimerTick);

    connect(ui->StartButton, &QPushButton::clicked, this, &RememberNumber::onStartButtonClicked);

    ui->Answer->hide();
    connect(ui->Answer, &QLineEdit::returnPressed, this, &RememberNumber::onAnswerReturnPressed);
}

RememberNumber::~RememberNumber() {
    delete gTimer;

    delete ui;
}

void RememberNumber::setSecLeft(int value) {
    secLeft = value;
    ui->Timer->setText(QString::number(secLeft));
}

void RememberNumber::onTimerTick() {
    setSecLeft(secLeft - 1);
}

void RememberNumber::onTimerFinished() {
    gTimer->stop();
    ui->Timer->hide();
    ui->StartButton->setText("Retry");
    ui->StartButton->show();
    ui->Answer->show();
}

void RememberNumber::onStartButtonClicked() {
    if (ui->StartButton->text() == "Start") {
        ui->StartButton->hide();
        ui->Number->hide();
        ui->Timer->show();
        setSecLeft(waitTime / 1000);
        gTimer->start(1000);
        QTimer::singleShot(waitTime, this, &RememberNumber::onTimerFinished);
    } else {
        ui->Answer->hide();
        ui->Number->show();
        ui->StartButton->setText("Start");
    }
}

void RememberNumber::onAnswerReturnPressed() {
    bool isInt = false;
    int answerValue = ui->Answer->text().toInt(&isInt);
    if (isInt && answerValue == rdNumber) {
        MainWindow::getInstance()->removeWindow(this);
        return;
    }
}
