#include "ServerNetworkInterface.hpp"

ServerNetworkInterface::ServerNetworkInterface(int port, io_service & service, std::ostream& outStream)
  : NetworkInterface(port, service, outStream), acceptor(service, tcp::endpoint(tcp::v4(), port)),
  accepting(false), active(true)
{
  ioThread = std::thread([&] {serviceLoop(); });
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

std::string ServerNetworkInterface::getMessages()
{
  std::string msg = "";
  for (int i = 0; i < knownConnections.size(); i++)
  {
    msg += knownConnections[i]->read();
  }
  return msg;
}

void ServerNetworkInterface::acceptConnection()
{
  out << "Waiting for new connection request on " 
    << acceptor.local_endpoint().address() <<":"
    << acceptor.local_endpoint().port() << "..."<< std::endl;
  waitingConn =
    TCPConnection::create(acceptor.get_io_service());

  //acceptor.async_accept(waitingConn->getSocket(), handleAccept);
  acceptor.async_accept(waitingConn->getSocket(),
    boost::bind(&ServerNetworkInterface::handleAccept,this,
      boost::asio::placeholders::error));
}

void ServerNetworkInterface::handleAccept(const boost::system::error_code & error)
{
  out << "Connection established with client" 
      /*<< new_connection->remoteEndpoint() */<< " at <Time stamp here>" << std::endl;
  if (!error)
  {
    knownConnections.emplace_back(waitingConn);
  }
  else {
    out << "An error occured establishing a connection";
  }
  acceptConnection();
}

void ServerNetworkInterface::serviceLoop()
{
  while (active) {
    ioService.run();
  }
}

ServerNetworkInterface::~ServerNetworkInterface()
{
  active = false;
  ioThread.join();
}
