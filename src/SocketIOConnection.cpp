/**
 *
 */

#include "SocketIOConnection.h"

SocketIOConnection::SocketIOConnection(const string & aToken)
  : mToken(aToken)
{
}

SocketIOConnection::~SocketIOConnection()
{
  mSocketIOClient.close();
}

void SocketIOConnection::Connect(const string & aURL)
{
  mSocketIOClient.set_fail_listener(std::bind(&SocketIOConnection::OnFail, this));

  mSocketIOClient.set_reconnect_attempts(0);
  mSocketIOClient.connect(aURL);
}

void SocketIOConnection::Emit(float aTemperature)
{
  auto msg                = sio::object_message::create();
  msg->get_map()["token"] = sio::string_message::create(mToken);
  msg->get_map()["temp"]  = sio::double_message::create(aTemperature);
  mSocketIOClient.socket()->emit("Room1Temp", msg);
}

bool SocketIOConnection::ConnectionFailed() const
{
  return mConnectionFailed;
}

void SocketIOConnection::OnFail()
{
  mConnectionFailed = true;
}
