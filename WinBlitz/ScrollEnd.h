#ifndef SCROLLEND_H
#define SCROLLEND_H

#include "NotClosable.h"

namespace Ui {
class ScrollEnd;
}

class ScrollEnd : public NotClosable {
    Q_OBJECT

public:
    explicit ScrollEnd(QWidget *parent = nullptr);
    ~ScrollEnd();

private:
    Ui::ScrollEnd *ui;
};

#endif
