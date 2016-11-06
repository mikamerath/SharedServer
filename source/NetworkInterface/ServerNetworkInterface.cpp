#include "ServerNetworkInterface.hpp"


ServerNetworkInterface::ServerNetworkInterface(int port, io_service & service, std::ostream& outStream)
  : NetworkInterface(port,service,outStream), acceptor(service, tcp::endpoint(tcp::v4(), port)),
  accepting(false)
{
  out << "Server network initialization complete..." << std::endl;
}

void ServerNetworkInterface::startAccepting()
{
  out << "Preparing to accept new connections..." << std::endl;
  if (accepting) {
    return;
  }
  else {
    accepting = true;
    acceptConnection();
  }
}

void ServerNetworkInterface::acceptConnection()
{
  out << "Waiting for new connection request..." << std::endl;
  TCPConnection::pointer new_connection =
    TCPConnection::create(acceptor.get_io_service());

  acceptor.async_accept(new_connection->socket(),
    boost::bind(&ServerNetworkInterface::handleAccept, this, new_connection,
      boost::asio::placeholders::error));
}

void ServerNetworkInterface::handleAccept(TCPConnection::pointer new_connection, const boost::system::error_code & error)
{
  out << "Connection established with client" 
      << new_connection->endpoint << " at <Time stamp here>" << std::endl;
  if (!error)
  {
    new_connection->start();
    acceptConnection();
  }
}
