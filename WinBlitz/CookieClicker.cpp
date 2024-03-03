#include "CookieClicker.h"
#include "ui_CookieClicker.h"
#include "MainWindow.h"
#include <QRandomGenerator>

CookieClicker::CookieClicker(QWidget *parent)
    : NotClosable(parent), ui(new Ui::CookieClicker) {
    ui->setupUi(this);

    pressedTarget = QRandomGenerator::global()->bounded(6, 16);
    pressedCount = 0;

    ui->Info1->setText("Press the button " + QString::number(pressedTarget) + " times");

    connect(ui->Cookie, &QPushButton::clicked, this, &CookieClicker::onCookieClicked);

    updatePressedCountText();
}

CookieClicker::~CookieClicker() {
    delete ui;
}

void CookieClicker::onCookieClicked() {
    pressedCount++;
    if (pressedCount == pressedTarget) {
        MainWindow::getInstance()->removeWindow(this);
        return;
    }
    updatePressedCountText();
}

void CookieClicker::updatePressedCountText() {
    ui->PressCount->setText("Count : " + QString::number(pressedCount));
}
