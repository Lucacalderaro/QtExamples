# QtExamples
Collection of Qt examples:

- SignalThread: Creates two new threads, other than the main thread, with their own event loop. The main thread manage the communication between the new threads through signal slot connection. The events of the new threads target the members of the user defined classes.

- TcpSockets: Create a server and client sockets classes that exchange QByteArrays.

- TcpSocketsMasterSlave: Buils a Master and Slave architecture on top of the server and client classes.
