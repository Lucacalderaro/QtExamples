#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEditIp->setText("127.0.0.1");
    ui->lineEditPort->setText("8000");
    ui->widgetLed->setStyleSheet("background-color:red;");

    commandSlave = new CommandSlave();
    connect(commandSlave, &CommandSlave::connected, this, &MainWindow::socketConnected);
    connect(commandSlave, &CommandSlave::disconnected, this, &MainWindow::socketDisconnected);
    connect(commandSlave, &CommandSlave::serverListening, this, &MainWindow::serverListening);

    connect(commandSlave, &CommandSlave::switchOnLed, this, &MainWindow::switchOnLed);
    connect(ui->pushButtonListen, &QPushButton::clicked, this, &MainWindow::listen);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete commandSlave;
}

void MainWindow::sendMessage()
{
    commandSlave->serverReady();
}

void MainWindow::listen()
{
    commandSlave->setIp(ui->lineEditIp->text());
    commandSlave->setPort(ui->lineEditPort->text().toInt());
    commandSlave->listenToSocket();
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

void MainWindow::switchOnLed()
{
    ui->widgetLed->setStyleSheet("background-color:green;");
    commandSlave->serverReady();
}
