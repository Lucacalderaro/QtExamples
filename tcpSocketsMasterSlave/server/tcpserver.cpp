#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent) : QObject(parent)
{
    tcpSocket = new QTcpSocket();
    tcpServer = new QTcpServer();
    tcpServer->setMaxPendingConnections(1); // Only one client can connect to the server at a time.
}

TcpServer::~TcpServer()
{
    delete tcpSocket;
    delete tcpServer;
}

void TcpServer::listenToSocket()
{
    if(!tcpServer->isListening())
    {
        //listen only this address and port
        tcpServer->listen(QHostAddress(ip), port);

        // Once a client connect to the server, trigger connectSocket function
        connect(tcpServer, &QTcpServer::newConnection, this, &TcpServer::connectSocket);
        emit serverListening();
    }
}

void TcpServer::connectSocket()
{
    if(tcpSocket->state() == 0)
    {
        delete tcpSocket;
        tcpSocket = tcpServer->nextPendingConnection();
        connect(tcpSocket, &QTcpSocket::readyRead, this, &TcpServer::read);
        connect(tcpSocket, &QTcpSocket::disconnected, this, &TcpServer::disconnected);
        emit connected();

        in.setDevice(tcpSocket);
        in.setVersion(QDataStream::Qt_5_10);

        // If connection successful, close the server.
        if (tcpSocket->state() != 0)
        {
            disconnect(tcpServer, &QTcpServer::newConnection, this, &TcpServer::connectSocket);
            tcpServer->close();
        }
    }
}

void TcpServer::disconnectSocket()
{
    if(tcpSocket->state() != 0)
        tcpSocket->disconnectFromHost();
}

void TcpServer::read()
{

    in.startTransaction();

    QByteArray payload;
    in >> payload;

    if (!in.commitTransaction())
        return;

    emit messageReceived(payload);
}

void TcpServer::send(QByteArray payload)
{
    if(tcpSocket->state() != 0)
    {
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_10);
        out << payload;
        tcpSocket->write(block);
    }
}
