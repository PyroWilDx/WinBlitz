#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSet>

class NotClosable;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    static MainWindow *getInstance();

    ~MainWindow();

    void addWindow(NotClosable *window);

    void removeWindow(NotClosable *window);

protected:
    void closeEvent(QCloseEvent *e) override;

private:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    static MainWindow *sInstance;

    Ui::MainWindow *ui;

    QSet<NotClosable *> windows;
};

#endif
