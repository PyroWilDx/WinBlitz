#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include "NotClosable.h"
#include "CookieClicker.h"
#include "WriteText.h"
#include "Calculation.h"
#include "WaitTimer.h"
#include "RememberNumber.h"
#include <QScreen>
#include <QTimer>
#include <QRandomGenerator>
#include <QPushButton>
#include <QStyle>
#include <QDebug>

MainWindow *MainWindow::sInstance = nullptr;

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    sInstance = this;

    ui->setupUi(this);

    currWindowHeight = 0;

    gTimer = new QTimer();
    gTimer->setSingleShot(false);
    connect(gTimer, &QTimer::timeout, this, &MainWindow::gLoop);

    windows = QSet<NotClosable *>();

    clearedWindowCount = 0;
    activeWindowCount = 0;

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
    if (rd < 10 || windows.isEmpty()) {
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
    // int rd = QRandomGenerator::global()->bounded(5);
    int rd = 4;
    switch (rd) {
        case 0:
            mg = new CookieClicker();
            break;
        case 1:
            mg = new WriteText();
            break;
        case 2:
            mg = new Calculation();
            break;
        case 3:
            mg = new WaitTimer();
            break;
        case 4:
            mg = new RememberNumber();
            break;
    }
    return mg;
}

void MainWindow::addWindow(NotClosable *window) {
    windows.insert(window);
    window->setWindowTitle(window->getName() + " (Window " +
                           QString::number(clearedWindowCount + activeWindowCount + 1) + ")");
    window->setAttribute(Qt::WA_ShowWithoutActivating);
    window->move(QApplication::primaryScreen()->geometry().width() - window->width(), currWindowHeight);
    window->show();
    setActiveWindowCount(activeWindowCount + 1);
    setCurrWindowHeight(currWindowHeight + QApplication::style()->pixelMetric(QStyle::PM_TitleBarHeight));
}

void MainWindow::closeWindow(NotClosable *window) {
    window->close();
    delete window;
}

void MainWindow::removeWindow(NotClosable *window) {
    closeWindow(window);
    windows.remove(window);
    setClearedWindowCount(clearedWindowCount + 1);
    setActiveWindowCount(activeWindowCount - 1);
}

void MainWindow::clearWindows() {
    for (NotClosable *window : std::as_const(windows)) {
        closeWindow(window);
    }
    windows.clear();
}

void MainWindow::setCurrWindowHeight(int value) {
    currWindowHeight = value;
    if (currWindowHeight > 0.88 * QApplication::primaryScreen()->geometry().height()) {
        currWindowHeight = 0;
    }
}

void MainWindow::setClearedWindowCount(int value) {
    clearedWindowCount = value;
    ui->ClearedWindowText->setText("Cleared Windows : " + QString::number(clearedWindowCount));
}

void MainWindow::setActiveWindowCount(int value) {
    activeWindowCount = value;
    ui->ActiveWindowText->setText("Active Windows : " + QString::number(activeWindowCount));
}

void MainWindow::closeEvent(QCloseEvent *e) {
    QMainWindow::closeEvent(e);

    clearWindows();
}

void MainWindow::onStartButtonClicked() {
    if (ui->StartButton->text() == "Start") {
        ui->StartButton->setText("Stop");
        setClearedWindowCount(0);
        setActiveWindowCount(0);
        setCurrWindowHeight(0);
        startLoop();
    } else {
        finishLoop();
        ui->StartButton->setText("Start");
    }
}

void MainWindow::onExitButtonClicked() {
    close();
}
