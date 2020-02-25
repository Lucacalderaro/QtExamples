#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QByteArray>
#include <QDataStream>

/*!
 * \class TcpServer
 * \brief The TcpServer class provides the minimum members to establish a TCP server.
 *
 * The TcpServer class encapsulates data to be sent in packets defined by the Qt_5_10 protocol.
 * Custom protocol can be used by subclassing TcpServer and overriding the read and send methods.
 */

class TcpServer : public QObject
{
    Q_OBJECT

public:
    explicit TcpServer(QObject *parent = nullptr);
    ~TcpServer();

public slots:
    void listenToSocket();          // Makes the server listening for the specified port and addresses.
    void disconnectSocket();        // Disconnect socket.
    void send(QString payload);     // Send data to the Client.
    void setIp(QString ip_) {ip = ip_;}     // Set address of the Clients that can connect to the server.
    void setPort(int port_) {port = port_;} // Set the port to listen for connections.

signals:
    void connected();               // This signal is emitted once the connection is established.
    void disconnected();            // This signal is emitted once the socket has disconnected.
    void messageReceived(QString message);  // This signal is emitted once the socket received an entire message.
    void serverListening();         // This signal is emitted once the server is listening.

protected:
    void read();                    // Read the buffer of the socket and check if the entire data packet is arrived.

private:
    QString ip;                     // Address of the Clients that can connect to the server.
    int port;                       // Port to listen.
    QTcpServer * tcpServer;         // Pointer to the instance of QTcpSocket class.
    QTcpSocket * tcpSocket;         // Pointer to the instance of QTcpServer class.
    QDataStream in;                 // Datastream used to deserialize the data to be read.

    void connectSocket();           // Once a Client connect to the server create the socket to manage the connection.
};

#endif // TCPSERVER_H
