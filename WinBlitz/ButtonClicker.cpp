#include "ButtonClicker.h"
#include "./ui_ButtonClicker.h"
#include <QRandomGenerator>

ButtonClicker::ButtonClicker(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::ButtonClicker) {
    ui->setupUi(this);

    pressedTarget = QRandomGenerator::global()->bounded(10, 30);
    pressedCount = 0;

    ui->Info1->setText("Press the button " + QString::number(pressedTarget) + " times");

    connect(ui->Button, &QPushButton::clicked, this, &ButtonClicker::onButtonClicked);

    updatePressedCountText();
}

ButtonClicker::~ButtonClicker() {
    delete ui;
}

void ButtonClicker::onButtonClicked() {
    pressedCount++;
    if (pressedCount == pressedTarget) {
        close();
        return;
    }
    updatePressedCountText();
}

void ButtonClicker::updatePressedCountText() {
    ui->PressCount->setText("Count : " + QString::number(pressedCount));
}
