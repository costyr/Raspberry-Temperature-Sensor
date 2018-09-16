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

  void EmitHumidity(float aHumidity, const string & aRoomId);

  bool ConnectionFailed() const;

  bool ConnectionClosed() const;

private:
  string      mToken;
  sio::client mSocketIOClient;

  std::atomic<bool> mConnectionFailed{ false };

  std::atomic<bool> mConnectionClosed{ false };

  void OnFail();

  void OnClosed();
};

#endif  // _SOCKET_IO_CONNECTION_H_
