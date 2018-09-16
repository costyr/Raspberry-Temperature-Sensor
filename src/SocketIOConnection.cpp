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
  mSocketIOClient.sync_close();
  mSocketIOClient.clear_con_listeners();
}

void SocketIOConnection::Connect(const string & aURL)
{
  mSocketIOClient.set_fail_listener(std::bind(&SocketIOConnection::OnFail, this));
  mSocketIOClient.set_close_listener(std::bind(&SocketIOConnection::OnClosed, this));

  mSocketIOClient.set_reconnect_attempts(0);
  mSocketIOClient.connect(aURL);
}

void SocketIOConnection::Emit(float aTemperature, const string & aRoomId)
{
  auto msg                = sio::object_message::create();
  msg->get_map()["token"] = sio::string_message::create(mToken);
  msg->get_map()["temp"]  = sio::double_message::create(aTemperature);
  mSocketIOClient.socket("/thermostat")->emit(aRoomId, msg);
}

void SocketIOConnection::EmitHumidity(float aHumidity, const string & aRoomId)
{
  auto msg                   = sio::object_message::create();
  msg->get_map()["token"]    = sio::string_message::create(mToken);
  msg->get_map()["humidity"] = sio::double_message::create(aHumidity);
  mSocketIOClient.socket("/thermostat")->emit(aRoomId, msg);
}

bool SocketIOConnection::ConnectionFailed() const
{
  return mConnectionFailed;
}

bool SocketIOConnection::ConnectionClosed() const
{
  return mConnectionClosed;
}

void SocketIOConnection::OnFail()
{
  mConnectionFailed = true;
}

void SocketIOConnection::OnClosed()
{
  mConnectionClosed = true;
}
