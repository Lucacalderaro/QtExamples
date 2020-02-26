#include "commandslave.h"

CommandSlave::CommandSlave(TcpServer *parent) : TcpServer(parent)
{
    connect(this, &CommandSlave::messageReceived, this, &CommandSlave::interpretReceived);
}

void CommandSlave::serverReady()
{
    send(QString("ready").toUtf8());
}

void CommandSlave::interpretReceived(QByteArray payload)
{
    if (payload == QByteArray(QString("start").toUtf8()))
        emit switchOnLed();
    else
        qDebug() << "Not a command";
}
