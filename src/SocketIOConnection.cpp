/**
 *  
 */

#include "SocketIOConnection.h"

SocketIOConnection::SocketIOConnection() 
{

}

void SocketIOConnection::Connect(const string & aURL) 
{
  mSocketIOClient.connect(aURL);
}

void SocketIOConnection::Emit(float aTemperature) 
{
  mSocketIOClient.socket->emit("Room1Temp", aTemperature);
}