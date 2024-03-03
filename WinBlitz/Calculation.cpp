#include "Calculation.h"
#include "ui_Calculation.h"
#include "MainWindow.h"
#include <QRandomGenerator>

Calculation::Calculation(QWidget *parent)
        : NotClosable(parent), ui(new Ui::Calculation) {
    ui->setupUi(this);

    gName = "Calculation";

    int x = QRandomGenerator::global()->bounded(20);
    int y = QRandomGenerator::global()->bounded(20);
    QString opStr;
    int rd = QRandomGenerator::global()->bounded(3);
    switch(rd) {
        case 0:
            answer = x + y;
            opStr = "+";
            break;
        case 1:
            answer = x - y;
            opStr = "-";
            break;
        case 2:
            answer = x * y;
            opStr = "×";
            break;
    }
    ui->Question->setText(QString::number(x) + " " + opStr + " " + QString::number(y) + " = ?");

    connect(ui->Answer, &QLineEdit::returnPressed, this, &Calculation::onAnswerReturnPressed);
}

Calculation::~Calculation() {
    delete ui;
}

void Calculation::onAnswerReturnPressed() {
    bool isInt = false;
    int answerValue = ui->Answer->text().toInt(&isInt);
    if (isInt && answerValue == answer) {
        MainWindow::getInstance()->removeWindow(this);
        return;
    }
}
