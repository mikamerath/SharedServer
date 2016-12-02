#include "ServerNetworkInterface.hpp"

ServerNetworkInterface::ServerNetworkInterface(int port, io_service & service, 
  std::ostream& outStream, std::function<void(std::shared_ptr<Player>)> addP)
  : NetworkInterface(port, service, outStream),
  acceptor(service, tcp::endpoint(tcp::v4(), port)), accepting(false), addPlayer(addP),
  playerCounter(0)
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

//std::string ServerNetworkInterface::getMessages()
//{
//  std::string msg = "";
//  for (int i = 0; i < knownConnections.size(); i++)
//  {
//    msg += knownConnections[i]->read();
//  }
//  return msg;
//}

void ServerNetworkInterface::acceptConnection()
{
  out << "Waiting for new connection request on " 
    << acceptor.local_endpoint().address() <<":"
    << acceptor.local_endpoint().port() << "..."<< std::endl;
  waitingConn =
    TCPConnection::create(acceptor.get_io_service());

  acceptor.async_accept(waitingConn->getSocket(),
    boost::bind(&ServerNetworkInterface::handleAccept,this,
      boost::asio::placeholders::error));
}

void ServerNetworkInterface::handleAccept(const boost::system::error_code & error)
{
  time_t rawtime;
  struct tm timeinfo;
  char timestamp[32];
  time(&rawtime);
  localtime_s(&timeinfo, &rawtime);
  asctime_s(timestamp, 32, &timeinfo);

  out << "Connection established with client : " 
      << waitingConn->getSocket().remote_endpoint() << ". At :" << timestamp;
  if (!error)
  {
    std::shared_ptr<Player> newPlayer = std::make_shared<Player>(playerCounter, waitingConn);
    addPlayer(newPlayer);
    playerCounter++;
  }
  else {
    out << "An error occured establishing a connection";
  }
  acceptConnection();
}

ServerNetworkInterface::~ServerNetworkInterface()
{
  active = false;
  ioThread.join();
}
