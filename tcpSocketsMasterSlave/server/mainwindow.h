#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <commandslave.h>

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
    CommandSlave * commandSlave;

    void sendMessage();
    void listen();

    void serverListening();
    void socketConnected();
    void socketDisconnected();

    void switchOnLed();
};

#endif // MAINWINDOW_H
