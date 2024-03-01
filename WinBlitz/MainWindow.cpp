#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include "NotClosable.h"

MainWindow *MainWindow::sInstance = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow *MainWindow::getInstance() {
    if (sInstance == nullptr) {
        sInstance = new MainWindow();
    }
    return sInstance;
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::addWindow(NotClosable *window) {
    windows.insert(window);
    window->show();
}

void MainWindow::removeWindow(NotClosable *window) {
    window->close();
    delete window;
    windows.remove(window);
}

void MainWindow::closeEvent(QCloseEvent *e) {
    for (NotClosable *window : std::as_const(windows)) {
        window->close();
        delete window;
    }
}
