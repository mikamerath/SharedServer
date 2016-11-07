#include "ClientNetworkInterface.hpp"

ClientNetworkInterface::ClientNetworkInterface(int port, io_service & service, std::ostream& outStream)
  : NetworkInterface(port,service,outStream), conn(TCPConnection::create(service))
{
  out << "Client network interface initialized..." << std::endl;
}

void ClientNetworkInterface::connect(std::string ip, int port)
{
  out << "Attempting to connect to " << ip << ":" << port << "..." << std::endl;

  boost::asio::ip::tcp::endpoint endpoint(
    boost::asio::ip::address::from_string(ip), 12345);

  try {
    conn->connect(endpoint);
  }
  catch(boost::system::system_error e){
    out << "Failed to connect to " << ip << ":" << port << "..." << std::endl;
    out << "Error code = " << e.code() <<  " : " << e.code().message() << std::endl;
  }
}
