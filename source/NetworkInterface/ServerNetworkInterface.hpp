#ifndef SERVER_NETWORK_INTERFACE
#define SERVER_NETWORK_INTERFACE

#include "NetworkInterface.hpp"
#include "source/PlayerAPI/Player.hpp"
#include <boost/bind.hpp>
#include <functional>
#include <iostream>
#include <thread>

using namespace boost::asio;
using ip::tcp;

/* The NI to be used by the server*/
class ServerNetworkInterface : NetworkInterface
{
public:
  /* constructor for the NI, addP should be a function called when a player
   * connects*/
  ServerNetworkInterface(int port,
                         io_service& service,
                         std::ostream& outStream,
                         std::function<void(std::shared_ptr<Player>)> addP);
  // Begins accepting connections aSync
  void startAccepting();
  // debugging function to help diagnose connection status
  //std::string getMessages();
  // deconstructor used to clean up
  ~ServerNetworkInterface();

private:
  void acceptConnection();
  void handleAccept(const boost::system::error_code& error);

  int playerCounter;
  std::function<void(std::shared_ptr<Player>)> addPlayer;
  bool accepting;
  boost::asio::ip::tcp::acceptor acceptor;
  //std::vector<TCPConnection::pointer> knownConnections;
  TCPConnection::pointer waitingConn;
};
#endif // !SERVER_NETWORK_INTERFACE
