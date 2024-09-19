#include "CheckBox.h"
#include "ui_CheckBox.h"
#include "MainWindow.h"
#include <QRandomGenerator>
#include <QCheckBox>

CheckBox::CheckBox(QWidget *parent)
        : NotClosable(parent), ui(new Ui::CheckBox) {
    ui->setupUi(this);

    gName = "Check Boxes";

    checkedCount = 0;
    checkBoxCount = QRandomGenerator::global()->bounded(6, 22);

    int currCount = 0;
    int i = 16;
    int j = 80;
    while (currCount < checkBoxCount) {
        QCheckBox *checkBox = new QCheckBox(this);
        checkBox->move(i , j);
        connect(checkBox, &QCheckBox::stateChanged, this, [this](int state) {
            if (state == Qt::Checked) {
                checkedCount++;
                if (checkedCount == checkBoxCount) {
                    MainWindow::getInstance()->removeWindow(this);
                    return;
                }
            } else {
                checkedCount--;
            }
        });
        i += 32;
        if (i > 360) {
            i = 16;
            j += 32;
        }
        currCount++;
    }
}

CheckBox::~CheckBox() {
    delete ui;
}
