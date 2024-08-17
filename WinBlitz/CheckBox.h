#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "NotClosable.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class CheckBox;
}
QT_END_NAMESPACE

class CheckBox : public NotClosable {
    Q_OBJECT

public:
    explicit CheckBox(QWidget *parent = nullptr);
    ~CheckBox();

private:
    Ui::CheckBox *ui;

    int checkedCount;
    int checkBoxCount;
};

#endif
