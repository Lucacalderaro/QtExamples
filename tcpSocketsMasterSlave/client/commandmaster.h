#ifndef COMMANDMASTER_H
#define COMMANDMASTER_H

#include <tcpclient.h>

/*!
 * \brief The CommandMaster class
 *
 * The CommandMaster is a subclass of TcpClient. It adds the definition of specific commands in a master-slave architecture.
 */
class CommandMaster : public TcpClient
{
    Q_OBJECT

public:
    CommandMaster(TcpClient *parent = nullptr);

    void switchOnLedReceived();

signals:
    void serverReady();

private:
    void interpretReceived(QByteArray payload);
};

#endif // COMMANDMASTER_H
