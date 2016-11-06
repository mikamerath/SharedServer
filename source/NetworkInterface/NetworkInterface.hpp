#ifndef NETWORK_INTERFACE
#define NETWORK_INTERFACE

#include <boost\asio.hpp>
#include "TCPConnection.hpp"
#include <iostream>

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


};
#endif // !NETWORK_INTERFACE
