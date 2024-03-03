#ifndef CALCULATION_H
#define CALCULATION_H

#include "NotClosable.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Calculation;
}
QT_END_NAMESPACE

class Calculation : public NotClosable {
    Q_OBJECT

public:
    explicit Calculation(QWidget *parent = nullptr);
    ~Calculation();

private slots:
    void onAnswerReturnPressed();

private:
    Ui::Calculation *ui;

    int answer;
};

#endif // CALCULATION_H
