#ifndef CLICKDATE_H
#define CLICKDATE_H

#include "NotClosable.h"
#include <QDate>

QT_BEGIN_NAMESPACE
namespace Ui {
class ClickDate;
}
QT_END_NAMESPACE

class ClickDate : public NotClosable {
    Q_OBJECT

public:
    explicit ClickDate(QWidget *parent = nullptr);
    ~ClickDate();

    void setRandomTargetDate(int startYear, int endYear);

private slots:
    void onCalendarClicked(const QDate &date);

private:
    Ui::ClickDate *ui;

    QDate targetDate;
};

#endif
