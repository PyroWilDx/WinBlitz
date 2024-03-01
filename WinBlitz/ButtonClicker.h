#ifndef BUTTONCLICKER_H
#define BUTTONCLICKER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class ButtonClicker;
}
QT_END_NAMESPACE

class ButtonClicker : public QMainWindow {
    Q_OBJECT

public:
    explicit ButtonClicker(QWidget *parent = nullptr);
    ~ButtonClicker();

private slots:
    void onButtonClicked();

private:
    void updatePressedCountText();

private:
    Ui::ButtonClicker *ui;

    int pressedTarget;
    int pressedCount;
};

#endif
