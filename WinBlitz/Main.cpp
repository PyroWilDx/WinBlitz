#include "MainWindow.h"
#include "CookieClicker.h"
#include "WriteText.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow *w = MainWindow::getInstance();
    w->show();
    w->move(0, 0);
    w->addWindow(new CookieClicker());
    w->addWindow(new WriteText());
    return a.exec();
}
