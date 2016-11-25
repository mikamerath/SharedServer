#ifndef NETWORK_INTERFACE
#define NETWORK_INTERFACE

#include <boost\asio.hpp>
#include "TCPConnection.hpp"
#include <iostream>
#include <thread>
#include "GeneralMessage.hpp"
#include "source/PlayerAPI/Player.hpp"

using namespace boost::asio;
using ip::tcp;

/*
Core interface for creating a network connection. It encapsulates all the logic needed to 
send and recieve messages based on a single request-reply pattern. 
*/
class NetworkInterface
{
public:

protected:
  io_service& ioService;
  int activePort;
  bool active;
  std::ostream& out;
  std::thread ioThread;


  NetworkInterface(int port, io_service& service, std::ostream& outStream);

  ~NetworkInterface()
  {
    active = false;
    ioThread.join();
  }

  void ioLoop();

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

  
};
#endif // !NETWORK_INTERFACE
