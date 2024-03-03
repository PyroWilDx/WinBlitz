#ifndef WAITTIMER_H
#define WAITTIMER_H

#include "NotClosable.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class WaitTimer;
}
QT_END_NAMESPACE

class WaitTimer : public NotClosable {
    Q_OBJECT

public:
    explicit WaitTimer(QWidget *parent = nullptr);
    ~WaitTimer();

    void setSecLeft(int value);

    void onTimerTick();

private slots:
    void onButtonClicked();

private:
    Ui::WaitTimer *ui;

    QTimer *gTimer;
    int secLeft;
};

#endif
