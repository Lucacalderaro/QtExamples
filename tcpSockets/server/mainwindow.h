#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <tcpserver.h>

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
    TcpServer * tcpServer;

    void sendMessage();
    void listen();

    void serverListening();
    void socketConnected();
    void socketDisconnected();
};

#endif // MAINWINDOW_H
