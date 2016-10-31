#include"NetworkInterface.h"

NetworkInterface::NetworkInterface(int port):
  ioService(),
  acceptor(ioService,ip::tcp::endpoint(ip::tcp::v4(),port))
{
  
}

NetworkInterface::~NetworkInterface()
{
}

void NetworkInterface::sendMessage(Player * p_player, 
  GeneralMessage msg, void(*callBack)(GeneralMessage))
{
}

void NetworkInterface::beginRecieve()
{
}

void NetworkInterface::closeConnection()
{
}
