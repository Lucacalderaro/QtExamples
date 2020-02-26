#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEditIp->setText("127.0.0.1");
    ui->lineEditPort->setText("8000");

    commandMaster = new CommandMaster();
    connect(commandMaster, &CommandMaster::connected, this, &MainWindow::socketConnected);
    connect(commandMaster, &CommandMaster::disconnected, this, &MainWindow::socketDisconnected);
    connect(commandMaster, &CommandMaster::serverReady, this, &MainWindow::serverReady);

    connect(ui->pushButtonTurnLedOn, &QPushButton::clicked, this, &MainWindow::turnLedOn);
    connect(ui->pushButtonConnect, &QPushButton::clicked, this, &MainWindow::connectSocket);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete commandMaster;
}

void MainWindow::turnLedOn()
{
    commandMaster->switchOnLedReceived();
    ui->pushButtonTurnLedOn->setDisabled(true);
}

void MainWindow::serverReady()
{
    ui->pushButtonTurnLedOn->setDisabled(false);
}

void MainWindow::connectSocket()
{
    commandMaster->setIp(ui->lineEditIp->text());
    commandMaster->setPort(ui->lineEditPort->text().toInt());
    commandMaster->connectSocket();
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
