#ifndef NOTCLOSABLE_H
#define NOTCLOSABLE_H

#include <QWidget>

class NotClosable : public QWidget {
    Q_OBJECT

public:
    explicit NotClosable(QWidget *parent = nullptr);

protected:
    void closeEvent(QCloseEvent *e) override;

};

#endif
