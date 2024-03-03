#ifndef WAITTIMER_H
#define WAITTIMER_H

#include <QWidget>

namespace Ui {
class WaitTimer;
}

class WaitTimer : public QWidget
{
    Q_OBJECT

public:
    explicit WaitTimer(QWidget *parent = nullptr);
    ~WaitTimer();

private:
    Ui::WaitTimer *ui;
};

#endif // WAITTIMER_H
