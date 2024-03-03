#ifndef SLIDETO_H
#define SLIDETO_H

#include "NotClosable.h"

namespace Ui {
class SlideTo;
}

class SlideTo : public NotClosable {
    Q_OBJECT

public:
    explicit SlideTo(QWidget *parent = nullptr);
    ~SlideTo();

private slots:
    void onSliderValueChanged();

    void onSliderReleased();

private:
    Ui::SlideTo *ui;

    int targetNumber;
};

#endif
