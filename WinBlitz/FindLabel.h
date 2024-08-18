#ifndef FINDLABEL_H
#define FINDLABEL_H

#include "NotClosable.h"

namespace Ui {
class FindLabel;
}

class FindLabel : public NotClosable {
    Q_OBJECT

public:
    explicit FindLabel(QWidget *parent = nullptr);
    ~FindLabel();

private:
    Ui::FindLabel *ui;

    char genRandomChar();

    QString genRandomWord(int length);
};

#endif
