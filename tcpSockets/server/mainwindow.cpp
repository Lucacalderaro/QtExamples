#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEditReceived->setReadOnly(true);
    ui->lineEditIp->setText("127.0.0.1");
    ui->lineEditPort->setText("8000");

    tcpServer = new TcpServer();
    connect(tcpServer, &TcpServer::connected, this, &MainWindow::socketConnected);
    connect(tcpServer, &TcpServer::disconnected, this, &MainWindow::socketDisconnected);
    connect(tcpServer, &TcpServer::messageReceived, ui->lineEditReceived, &QLineEdit::setText);
    connect(tcpServer, &TcpServer::serverListening, this, &MainWindow::serverListening);

    connect(ui->pushButtonSend, &QPushButton::clicked, this, &MainWindow::sendMessage);
    connect(ui->pushButtonListen, &QPushButton::clicked, this, &MainWindow::listen);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tcpServer;
}

void MainWindow::sendMessage()
{
    tcpServer->send(ui->lineEditSend->text().toUtf8());
}

void MainWindow::listen()
{
    tcpServer->setIp(ui->lineEditIp->text());
    tcpServer->setPort(ui->lineEditPort->text().toInt());
    tcpServer->listenToSocket();
}

void MainWindow::serverListening()
{
    ui->pushButtonListen->setText("Listening");
    ui->pushButtonListen->setDisabled(true);
}

void MainWindow::socketConnected()
{
    ui->pushButtonListen->setText("Connected");
    ui->pushButtonListen->setDisabled(true);
}

void MainWindow::socketDisconnected()
{
    ui->pushButtonListen->setText("Listen");
    ui->pushButtonListen->setDisabled(false);
}
