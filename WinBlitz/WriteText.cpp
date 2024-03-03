#include "WriteText.h"
#include "ui_WriteText.h"
#include "MainWindow.h"
#include <QKeyEvent>
#include <QFile>
#include <QTextStream>
#include <QRandomGenerator>

WriteText::WriteText(QWidget *parent)
        : NotClosable(parent), ui(new Ui::WriteText) {
    ui->setupUi(this);

    generateWords();
    setRemainingWordsText();

    ui->Words->setWordWrap(true);
    connect(ui->TextInput, &QLineEdit::returnPressed, this, &WriteText::onTextInputReturnPressed);
    connect(ui->TextInput, &QLineEdit::textChanged, this, &WriteText::onTextInputKeyPressed);
}

WriteText::~WriteText() {
    delete ui;
}

void WriteText::onTextInputKeyPressed(const QString &s) {
    if (s.length() == 0) return;
    if (s.at(s.length() - 1) == ' ') {
        ui->TextInput->setText(s.left(s.length() - 1));
        onTextInputReturnPressed();
    }
}

void WriteText::onTextInputReturnPressed() {
    QString currWord = ui->TextInput->text();
    int i = wordsVec.indexOf(currWord);
    if (i != -1) {
        wordsLeft--;
        if (wordsLeft == 0) {
            MainWindow::getInstance()->removeWindow(this);
            return;
        }
        ui->TextInput->setText("");
        int l = wordsVec[i].length();
        wordsVec[i] = QString('-').repeated(l);
        setRemainingWordsText();
    }
}

void WriteText::generateWords() {
    QFile wordsFile("Resource/WriteTextWords.txt");
    wordsFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&wordsFile);
    while (!in.atEnd()) {
        QString word = in.readLine();
        if (QRandomGenerator::global()->bounded(WORDS_COUNT) < 4) {
            wordsVec.push_back(word);
        }
    }
    wordsLeft = wordsVec.length();
    if (wordsVec.isEmpty()) generateWords();
}

void WriteText::setRemainingWordsText() {
    QString wordsText = "";
    for (const QString &word : std::as_const(wordsVec)) {
        if (!wordsText.isEmpty()) wordsText += " ";
        wordsText += word;
    }
    ui->Words->setText(wordsText);
}
