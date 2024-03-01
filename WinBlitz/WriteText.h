#ifndef WRITETEXT_H
#define WRITETEXT_H

#include "NotClosable.h"
#include <QVector>

#define WORDS_COUNT 3000

QT_BEGIN_NAMESPACE
namespace Ui {
class WriteText;
}
QT_END_NAMESPACE

class WriteText : public NotClosable {
    Q_OBJECT

public:
    explicit WriteText(QWidget *parent = nullptr);
    ~WriteText();

private slots:
    void onTextInputKeyPressed(const QString &s);

    void onTextInputReturnPressed();

private:
    void generateWords();

    void setRemainingWordsText();

private:
    Ui::WriteText *ui;

    QVector<QString> wordsVec;
    int wordsLeft;
};

#endif
