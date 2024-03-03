#ifndef NOTCLOSABLE_H
#define NOTCLOSABLE_H

#include <QWidget>

class NotClosable : public QWidget {
    Q_OBJECT

public:
    explicit NotClosable(QWidget *parent = nullptr);

    QString getName();

    void setClearedTrue();

protected:
    void closeEvent(QCloseEvent *e) override;
    QString gName;
    bool gCleared;
};

#endif
