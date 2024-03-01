#ifndef COOKIECLICKER_H
#define COOKIECLICKER_H

#include "NotClosable.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class CookieClicker;
}
QT_END_NAMESPACE

class CookieClicker : public NotClosable {
    Q_OBJECT

public:
    explicit CookieClicker(QWidget *parent = nullptr);
    ~CookieClicker();

private slots:
    void onCookieClicked();

private:
    void updatePressedCountText();

private:
    Ui::CookieClicker *ui;

    int pressedTarget;
    int pressedCount;
};

#endif
