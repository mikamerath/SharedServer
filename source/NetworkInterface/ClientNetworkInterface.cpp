#include "ClientNetworkInterface.hpp"

ClientNetworkInterface::ClientNetworkInterface(int port, io_service & service, std::ostream& outStream)
  : NetworkInterface(port,service,outStream)
{
  out << "Client network interface initialized..." << std::endl;
}
