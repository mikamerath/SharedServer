#include "NetworkInterface.hpp"

NetworkInterface::NetworkInterface(int port, io_service & service, std::ostream& outStream)
  : activePort(port), ioService(service), out(outStream)
{
  out << "Network basic initialization complete..." << std::endl;
}
