#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include "NotClosable.h"
#include "CookieClicker.h"
#include "WriteText.h"
#include "Calculation.h"
#include "WaitTimer.h"
#include "SlideTo.h"
#include "ClickDate.h"
#include "RememberNumber.h"
#include <QScreen>
#include <QTimer>
#include <QRandomGenerator>
#include <QPushButton>
#include <QStyle>
#include <QWindow>
#include <QtMath>

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

    keyWindowPositionMap = {
        {Qt::Key_F1, {0, 0}},
        {Qt::Key_F2, {0, 32}},
        {Qt::Key_F3, {0, 66}},
        {Qt::Key_F4, {32, 0}},
        {Qt::Key_F5, {32, 32}},
        {Qt::Key_F6, {32, 66}},
        {Qt::Key_F7, {66, 0}},
        {Qt::Key_F8, {66, 32}},
        {Qt::Key_F9, {66, 66}}
    };

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
    int p = (int) (10. + qLn(qPow(clearedWindowCount + 1, qLn(clearedWindowCount + 1))));
    if (rd < p || windows.isEmpty()) {
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
    // int rd = QRandomGenerator::global()->bounded(6);
    int rd = 6;
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
        case 5:
            mg = new SlideTo();
            break;
        case 6:
            mg = new ClickDate();
    }
    return mg;
}

void MainWindow::addWindow(NotClosable *window) {
    windows.insert(window);
    window->setWindowTitle(window->getName() + " (Window " +
                           QString::number(clearedWindowCount + activeWindowCount + 1) + ")");
    window->setAttribute(Qt::WA_ShowWithoutActivating);
    window->setWindowFlag(Qt::WindowStaysOnTopHint, false);
    window->move(QApplication::primaryScreen()->geometry().width() - window->width(), currWindowHeight);
    window->show();
    setActiveWindowCount(activeWindowCount + 1);
    setCurrWindowHeight(currWindowHeight + QApplication::style()->pixelMetric(QStyle::PM_TitleBarHeight));
    // QApplication::focusWindow()->raise();
}

void MainWindow::closeWindow(NotClosable *window) {
    window->setClearedTrue();
    window->close();
    QTimer delTimer = QTimer();
    delTimer.singleShot(1, this, [=]() {
        delete window;
    });
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
    if (currWindowHeight > 0.56 * QApplication::primaryScreen()->geometry().height()) {
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

QMap<int, QPoint> *MainWindow::getKeyWindowPositionMap() {
    return &keyWindowPositionMap;
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
        move(0, 0);
        startLoop();
    } else {
        finishLoop();
        ui->StartButton->setText("Start");
    }
}

void MainWindow::onExitButtonClicked() {
    close();
}
