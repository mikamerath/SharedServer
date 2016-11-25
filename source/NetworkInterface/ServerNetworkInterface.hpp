#ifndef SERVER_NETWORK_INTERFACE
#define SERVER_NETWORK_INTERFACE

#include"NetworkInterface.hpp"
#include <boost/bind.hpp>
#include <iostream>
#include <thread>

using namespace boost::asio;
using ip::tcp;

class ServerNetworkInterface 
  : NetworkInterface
{
public:
  ServerNetworkInterface(int port, io_service& service, std::ostream& outStream);
  void startAccepting();
  std::string getMessages();
  
  void serviceLoop();

  ~ServerNetworkInterface();
private:
  void acceptConnection();
  void handleAccept(const boost::system::error_code& error);

  bool active;
  bool accepting;
  boost::asio::ip::tcp::acceptor acceptor;
  std::vector<TCPConnection::pointer> knownConnections;
  TCPConnection::pointer waitingConn;
  std::thread ioThread;
};
#endif // !SERVER_NETWORK_INTERFACE
