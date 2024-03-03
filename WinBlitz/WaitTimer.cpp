#include "WaitTimer.h"
#include "ui_WaitTimer.h"

WaitTimer::WaitTimer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WaitTimer)
{
    ui->setupUi(this);
}

WaitTimer::~WaitTimer()
{
    delete ui;
}
