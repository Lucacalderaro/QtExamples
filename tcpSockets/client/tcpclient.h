#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>
#include <QDataStream>

/*!
 * \class TcpClient
 * \brief The TcpClient class provides the minimum members to establish a TCP connection.
 *
 * The TcpClient class encapsulates data to be sent in packets defined by the Qt_5_10 protocol.
 * Custom protocol can be used by subclassing TcpClient.
 */

class TcpClient : public QObject
{
    Q_OBJECT

public:
    explicit TcpClient(QObject *parent = nullptr);
    ~TcpClient();

public slots:
    void connectSocket();       // Try to connect the socket to the Host.
    void disconnectSocket();    // Disconnect from Host.
    void send(QByteArray payload); // Send data to the Host.

    void setIp(QString ip_);    // Set address of the Host.
    void setPort(int port_);    // Set the port which the Host is listening.

signals:
    void connected();           // This signal is emitted once the connection is established.
    void disconnected();        // This signal is emitted once the socket disconnect from the Host.
    void messageReceived(QByteArray message);  // This signal is emitted once the socket received an entire message.

private:
    QString ip;                 // Address of the Host.
    int port;                   // Port which the Host is listening.
    QTcpSocket * tcpSocket;     // Pointer to the instance of QTcpSocket class.
    QDataStream in;             // Datastream used to deserialize the data to be read.

    void read();                // Read the buffer of the socket and check if the entire data packet is arrived.
};

#endif // TCPCLIENT_H
