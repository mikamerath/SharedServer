#ifndef NETWORK_INTERFACE
#define NETWORK_INTERFACE

#include <boost\asio.hpp>
#include "TCPConnection.hpp"
#include <iostream>
#include "GeneralMessage.hpp"
#include "source/PlayerAPI/Player.hpp"

using namespace boost::asio;

/*
Core interface for creating a network connection. It encapsulates all the logic needed to 
send and recieve messages based on a single request-reply pattern. 
*/
class NetworkInterface
{
public:

protected:
  NetworkInterface(int port, io_service& service, std::ostream& outStream);

  io_service& ioService;
  int activePort;
  std::ostream& out;

  NetworkInterface(int port);
  ~NetworkInterface()
  {
  }

  /*
  Sends a message to the given player and then calls the callback function when the 
  server recieves a response from the player.
  */
  void sendMessage(Player*p_player, GeneralMessage msg, void(*callBack)(GeneralMessage))
  {
  }
  /*
  Begins looping logic to recieve and route any messages from any connected clients.
  */
  void beginRecieve()
  {
  }
  /*
  Closes all connections in preperation for server shutdown.
  */
  void closeConnection()
  {
  }

private:
  io_service ioService;
  ip::tcp::acceptor acceptor;
};
#endif // !NETWORK_INTERFACE
