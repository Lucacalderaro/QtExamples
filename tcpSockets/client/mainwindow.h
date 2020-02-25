#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <tcpclient.h>

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
    TcpClient *tcpClient;

    void sendMessage();
    void connectSocket();

    void socketConnected();
    void socketDisconnected();
};

#endif // MAINWINDOW_H
