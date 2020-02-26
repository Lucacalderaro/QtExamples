#include "commandmaster.h"

CommandMaster::CommandMaster(TcpClient *parent) : TcpClient(parent)
{
    connect(this, &CommandMaster::messageReceived, this, &CommandMaster::interpretReceived);
}

void CommandMaster::switchOnLedReceived()
{
    QByteArray payload;
    payload.append(QString("start").toUtf8());
    send(payload);
}

void CommandMaster::interpretReceived(QByteArray payload)
{
    if (payload == QByteArray(QString("ready").toUtf8()))
        emit serverReady();
    else
        qDebug() << "Not a command";
}
