#ifndef SERVER_NETWORK_INTERFACE
#define SERVER_NETWORK_INTERFACE

#include"NetworkInterface.hpp"
#include <boost/bind.hpp>
#include <iostream>

using namespace boost::asio;
using ip::tcp;

class ServerNetworkInterface 
  : NetworkInterface
{
public:
  ServerNetworkInterface(int port, io_service& service, std::ostream& outStream);
  void startAccepting();
  

private:
  void acceptConnection();

  void handleAccept(TCPConnection::pointer new_connection,
    const boost::system::error_code& error);

  bool accepting;
  boost::asio::ip::tcp::acceptor acceptor;

};
#endif // !SERVER_NETWORK_INTERFACE
