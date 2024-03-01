#include "NotClosable.h"
#include <QCloseEvent>

NotClosable::NotClosable(QWidget *parent)
    : QWidget{parent}
{}

void NotClosable::closeEvent(QCloseEvent *e) {
    e->ignore();
}
