/**
 *
 */

#ifndef _SOCKET_IO_CONNECTION_H_
#define _SOCKET_IO_CONNECTION_H_

#include "Common.h"
#include "socket.io-client-cpp/src/sio_client.h"
#include "socket.io-client-cpp/src/sio_socket.h"

class SocketIOConnection
{
public:
  SocketIOConnection(const string & aToken);

  ~SocketIOConnection();

  void Connect(const string & aURL);

  void Emit(float aTemperature, const string & aRoomId);

  bool ConnectionFailed() const;

private:
  string      mToken;
  sio::client mSocketIOClient;

  bool mConnectionFailed{ false };

  void OnFail();
};

#endif  // _SOCKET_IO_CONNECTION_H_
