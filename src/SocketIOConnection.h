/**
 *  
 */

#ifndef _SOCKET_IO_CONNECTION_H_
#define _SOCKET_IO_CONNECTION_H_

#include "socket.io-client-cpp/src/sio_client.h"
#include "socket.io-client-cpp/src/sio_socket.h"

#include <string>

class SocketIOConnection
{
public:
  SocketIOConnection();

  void Connect(const string & aURL);

  void Emit();

private:  
  sio::client mSocketIOClient;
};

#endif // _SOCKET_IO_CONNECTION_H_