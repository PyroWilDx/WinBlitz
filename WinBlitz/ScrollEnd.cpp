#include "ScrollEnd.h"
#include "ui_ScrollEnd.h"
#include "MainWindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollBar>

ScrollEnd::ScrollEnd(QWidget *parent)
        : NotClosable(parent), ui(new Ui::ScrollEnd) {
    ui->setupUi(this);

    QVBoxLayout *qLayout = new QVBoxLayout(ui->ScrollWidget);
    for (int i = 0; i < 100; i++) {
        qLayout->addWidget(new QLabel(ui->ScrollWidget));
    }

    connect(ui->Scroller->verticalScrollBar(), &QScrollBar::valueChanged, this, [this](int value) {
        if (value == this->ui->Scroller->verticalScrollBar()->maximum()) {
            MainWindow::getInstance()->removeWindow(this);
            return;
        }
    });
}

ScrollEnd::~ScrollEnd() {
    delete ui;
}
