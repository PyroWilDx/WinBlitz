#include "NotClosable.h"
#include "MainWindow.h"
#include <QCloseEvent>
#include <QApplication>

NotClosable::NotClosable(QWidget *parent)
        : QWidget{parent} {
    setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::MSWindowsFixedSizeDialogHint);

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

void NotClosable::keyPressEvent(QKeyEvent *e) {
    QMap<int, QPoint> *kMap = MainWindow::getInstance()->getKeyWindowPositionMap();

    if (!kMap->contains(e->key())) return;

    QPoint posPercent = kMap->value(e->key());
    QRect screenSize = QApplication::primaryScreen()->geometry();
    float x = (posPercent.x() / 100.f) * screenSize.width();
    float y = (posPercent.y() / 100.f) * screenSize.height();
    move(x, y);
}
