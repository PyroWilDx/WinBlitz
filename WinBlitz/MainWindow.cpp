#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include "NotClosable.h"
#include "CookieClicker.h"
#include "WriteText.h"
#include <QTimer>
#include <QRandomGenerator>
#include <QPushButton>

MainWindow *MainWindow::sInstance = nullptr;

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    sInstance = this;

    ui->setupUi(this);

    gTimer = new QTimer();
    gTimer->setSingleShot(false);
    connect(gTimer, &QTimer::timeout, this, &MainWindow::gLoop);

    windows = QSet<NotClosable *>();

    connect(ui->StartButton, &QPushButton::clicked, this, &MainWindow::onStartButtonClicked);
    connect(ui->ExitButton, &QPushButton::clicked, this, &MainWindow::onExitButtonClicked);
}

MainWindow::~MainWindow() {
    gTimer->stop();
    delete gTimer;

    clearWindows();

    delete ui;
}

MainWindow *MainWindow::getInstance() {
    return sInstance;
}

void MainWindow::startLoop() {
    gTimer->start(1000);

    for (int i = 0; i < START_WINDOW_COUNT; i++) {
        addWindow(getRandomMiniGame());
    }
}

void MainWindow::gLoop() {
    int rd = QRandomGenerator::global()->bounded(100);
    if (rd < 40) {
        if (windows.size() == MAX_WINDOW_COUNT) {
            finishLoop();
            return;
        }
        addWindow(getRandomMiniGame());
    }
}

void MainWindow::finishLoop() {
    gTimer->stop();
    clearWindows();
}

NotClosable *MainWindow::getRandomMiniGame() {
    NotClosable *mg = nullptr;
    int rd = QRandomGenerator::global()->bounded(2);
    switch (rd) {
        case 0:
            mg = new CookieClicker();
            break;
        case 1:
            mg = new WriteText();
            break;
    }
    return mg;
}

void MainWindow::addWindow(NotClosable *window) {
    windows.insert(window);
    window->setAttribute(Qt::WA_ShowWithoutActivating);
    window->show();
}

void MainWindow::closeWindow(NotClosable *window) {
    window->close();
    delete window;
}

void MainWindow::removeWindow(NotClosable *window) {
    closeWindow(window);
    windows.remove(window);
}

void MainWindow::clearWindows() {
    for (NotClosable *window : std::as_const(windows)) {
        closeWindow(window);
    }
    windows.clear();
}

void MainWindow::closeEvent(QCloseEvent *e) {
    QMainWindow::closeEvent(e);

    clearWindows();
}

void MainWindow::onStartButtonClicked() {
    if (ui->StartButton->text() == "Start") {
        startLoop();
        ui->StartButton->setText("Stop");
    } else {
        finishLoop();
        ui->StartButton->setText("Start");
    }
}

void MainWindow::onExitButtonClicked() {
    close();
}
