#ifndef COMMANDSLAVE_H
#define COMMANDSLAVE_H

#include <tcpserver.h>

/*!
 * \brief The CommandSlave class
 *
 * The CommandSlave is a subclass of TcpServer. It adds the definition of specific commands in a master-slave architecture.
 */
class CommandSlave : public TcpServer
{
    Q_OBJECT

public:
    CommandSlave(TcpServer *parent = nullptr);

    void serverReady();

signals:
    void switchOnLed();

private:
    void interpretReceived(QByteArray payload);
};

#endif // COMMANDSLAVE_H
