#ifndef REMEMBERNUMBER_H
#define REMEMBERNUMBER_H

#include "NotClosable.h"

namespace Ui {
class RememberNumber;
}

class RememberNumber : public NotClosable {
    Q_OBJECT

public:
    explicit RememberNumber(QWidget *parent = nullptr);
    ~RememberNumber();

    void setSecLeft(int value);

    void onTimerTick();

    void onTimerFinished();

private slots:
    void onStartButtonClicked();

    void onAnswerReturnPressed();

private:
    Ui::RememberNumber *ui;

    int rdNumber;

    int waitTime;
    int secLeft;
    QTimer *gTimer;
};

#endif
