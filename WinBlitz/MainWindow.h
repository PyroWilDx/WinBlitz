#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSet>

#define START_WINDOW_COUNT 2
#define MAX_WINDOW_COUNT 10

class NotClosable;
class QTimer;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    static MainWindow *getInstance();

    void startLoop();

    void gLoop();

    void finishLoop();

    NotClosable *getRandomMiniGame();

    void addWindow(NotClosable *window);

    void closeWindow(NotClosable *window);

    void removeWindow(NotClosable *window);

    void clearWindows();

protected:
    void closeEvent(QCloseEvent *e) override;

private slots:
    void onStartButtonClicked();

    void onExitButtonClicked();

private:
    static MainWindow *sInstance;

    Ui::MainWindow *ui;

    QTimer *gTimer;
    QSet<NotClosable *> windows;
};

#endif
