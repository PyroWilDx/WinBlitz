#include "FindLabel.h"
#include "ui_FindLabel.h"
#include "MainWindow.h"
#include <QRandomGenerator>
#include <QGridLayout>
#include <QPushButton>

FindLabel::FindLabel(QWidget *parent)
        : NotClosable(parent), ui(new Ui::FindLabel) {
    ui->setupUi(this);

    gName = "Find Label";

    int wordLength = 6;

    int r = QRandomGenerator::global()->bounded(10);
    int c = QRandomGenerator::global()->bounded(6);
    QString findWord = genRandomWord(wordLength);

    ui->Info1->setText("Find Button \"" + findWord + "\"");

    QGridLayout *gridLayout = new QGridLayout(ui->ScrollWidget);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 6; j++) {
            QString currWord;
            if (i == r && j == c) {
                currWord = findWord;
            } else {
                currWord = genRandomWord(wordLength);
                while (currWord.compare(findWord) == 0) {
                    currWord = genRandomWord(wordLength);
                }
            }
            QPushButton *currButton = new QPushButton(currWord);
            gridLayout->addWidget(currButton, i, j);
            if (i == r && j == c) {
                connect(currButton, &QPushButton::clicked, this, [this]() {
                    MainWindow::getInstance()->removeWindow(this);
                    return;
                });
            }
        }
    }
}

FindLabel::~FindLabel() {
    delete ui;
}

char FindLabel::genRandomChar() {
    int rdFormat = QRandomGenerator::global()->bounded(62);
    if (rdFormat < 10) {
        return (char) QRandomGenerator::global()->bounded(48, 58);
    } else if (rdFormat < 36) {
        return (char) QRandomGenerator::global() ->bounded(97, 123);
    }
    return (char) QRandomGenerator::global()->bounded(65, 91);
}

QString FindLabel::genRandomWord(int length) {
    QString word = QString();
    for (int i = 0; i < length; i++) {
        word += genRandomChar();
    }
    return word;
}
