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

    tcpClient = new TcpClient();
    connect(tcpClient, &TcpClient::connected, this, &MainWindow::socketConnected);
    connect(tcpClient, &TcpClient::disconnected, this, &MainWindow::socketDisconnected);
    connect(tcpClient, &TcpClient::messageReceived, ui->lineEditReceived, &QLineEdit::setText);

    connect(ui->pushButtonSend, &QPushButton::clicked, this, &MainWindow::sendMessage);
    connect(ui->pushButtonConnect, &QPushButton::clicked, this, &MainWindow::connectSocket);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tcpClient;
}

void MainWindow::sendMessage()
{
    tcpClient->send(ui->lineEditSend->text().toUtf8());
}

void MainWindow::connectSocket()
{
    tcpClient->setIp(ui->lineEditIp->text());
    tcpClient->setPort(ui->lineEditPort->text().toInt());
    tcpClient->connectSocket();
}

void MainWindow::socketConnected()
{
    ui->pushButtonConnect->setText("Connected");
    ui->pushButtonConnect->setDisabled(true);
}

void MainWindow::socketDisconnected()
{
    ui->pushButtonConnect->setText("Connect");
    ui->pushButtonConnect->setDisabled(false);
}
