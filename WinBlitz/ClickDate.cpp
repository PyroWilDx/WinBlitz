#include "ClickDate.h"
#include "ui_ClickDate.h"
#include "MainWindow.h"
#include <QRandomGenerator>
#include <QCalendarWidget>

ClickDate::ClickDate(QWidget *parent)
        : NotClosable(parent), ui(new Ui::ClickDate) {
    ui->setupUi(this);

    setRandomTargetDate(1000, 3000);

    ui->Info1->setText("Set Date : " +
                       QString::number(targetDate.day()).rightJustified(2, '0') + "/" +
                       QString::number(targetDate.month()).rightJustified(2, '0') + "/" +
                       QString::number(targetDate.year()) + " (DD/MM/YYYY)");

    connect(ui->Calendar, &QCalendarWidget::clicked, this, &ClickDate::onCalendarClicked);
}

ClickDate::~ClickDate() {
    delete ui;
}

void ClickDate::setRandomTargetDate(int startYear, int endYear) {
    QRandomGenerator* generator = QRandomGenerator::global();
    int year = generator->bounded(startYear, endYear + 1);
    int month = generator->bounded(1, 13);
    int day = generator->bounded(1, QDate(year, month, 1).daysInMonth() + 1);
    targetDate = QDate(year, month, day);
}

void ClickDate::onCalendarClicked(const QDate &date) {
    if (date.day() == targetDate.day() &&
            date.month() == targetDate.month() &&
            date.year() == targetDate.year()) {
        MainWindow::getInstance()->removeWindow(this);
        return;
    }
}
