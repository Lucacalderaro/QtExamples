#include "tcpclient.h"

TcpClient::TcpClient(QObject *parent) :
    QObject(parent), tcpSocket(new QTcpSocket(this))
{
    tcpSocket = new QTcpSocket();
    connect(tcpSocket, &QTcpSocket::connected, this, &TcpClient::connected);  // Forward signal outside tcpClient.
    connect(tcpSocket, &QTcpSocket::disconnected, this, &TcpClient::disconnected);  // Forward signal outside tcpClient.

    in.setDevice(tcpSocket);    // Set the dataStream read buffer to point to tcpSocket.
    in.setVersion(QDataStream::Qt_5_10);
    connect(tcpSocket, &QIODevice::readyRead, this, &TcpClient::read);  // Any data arrived at the socket, trigger read function to check if the entire data arrived.
}

TcpClient::~TcpClient()
{
    delete tcpSocket;
}

void TcpClient::connectSocket()
{
    if(tcpSocket->state() == 0)
        tcpSocket->connectToHost(ip,port);
}

void TcpClient::disconnectSocket()
{
    if(tcpSocket->state() != 0)
        tcpSocket->disconnectFromHost();
}

void TcpClient::read()
{
    // Add the last data arrived at the socket to the stream.
    in.startTransaction();

    // Deserialize the stream.
    QString payload;
    in >> payload;

    // If the entire data packet has arrived continue, otherwise return to loop event.
    if (!in.commitTransaction())
        return;

    emit messageReceived(payload);
}

void TcpClient::send(QString payload)
{
    if(tcpSocket->state() != 0)
    {
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);  // Create dataStream pointing to a qbyteArray in which data can only be written.
        out.setVersion(QDataStream::Qt_5_10);
        out << payload;     // Serialize data using the dataStream method, with protocol Qt_5_10. Data is written in the qbyteArray.
        tcpSocket->write(block);    // Write the block to the socket. The data will be sent asynchronously.
    }
}

void TcpClient::setIp(QString ip_) {ip = ip_;}

void TcpClient::setPort(int port_) {port = port_;}
