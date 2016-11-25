#ifndef SERVER_NETWORK_INTERFACE
#define SERVER_NETWORK_INTERFACE

#include"source\PlayerAPI\Player.hpp"
#include"NetworkInterface.hpp"
#include <boost/bind.hpp>
#include <iostream>
#include <thread>
#include <functional>

using namespace boost::asio;
using ip::tcp;

class ServerNetworkInterface 
  : NetworkInterface
{
public:
  ServerNetworkInterface(int port, io_service& service, 
    std::ostream& outStream, std::function<void(Player)> addP);
  void startAccepting();
  std::string getMessages();
  
  ~ServerNetworkInterface();
private:
  void acceptConnection();
  void handleAccept(const boost::system::error_code& error);

  int playerCounter;
  std::function<void(Player)> addPlayer;
  bool accepting;
  boost::asio::ip::tcp::acceptor acceptor;
  std::vector<TCPConnection::pointer> knownConnections;
  TCPConnection::pointer waitingConn;
};
#endif // !SERVER_NETWORK_INTERFACE
