#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <commandmaster.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    CommandMaster *commandMaster;

    void turnLedOn();
    void serverReady();
    void connectSocket();

    void socketConnected();
    void socketDisconnected();
};

#endif // MAINWINDOW_H
