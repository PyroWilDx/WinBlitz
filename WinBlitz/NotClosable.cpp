#include "NotClosable.h"
#include <QCloseEvent>

NotClosable::NotClosable(QWidget *parent)
    : QWidget{parent} {
    setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);
}

void NotClosable::closeEvent(QCloseEvent *e) {
    e->ignore();
}
