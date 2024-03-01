#include "MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w = MainWindow();
    w.move(0, 0);
    w.show();
    w.startLoop();
    return a.exec();
}
