#include "NotClosable.h"
#include <QCloseEvent>

NotClosable::NotClosable(QWidget *parent)
        : QWidget{parent} {
    setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);

    gName = "";
    gCleared = false;
}

QString NotClosable::getName() {
    return gName;
}

void NotClosable::setClearedTrue() {
    gCleared = true;
}

void NotClosable::closeEvent(QCloseEvent *e) {
    if (!gCleared) e->ignore();
}
