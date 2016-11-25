#include"Server.h"
#include "Server.hpp"

void Server::addPlayer(std::shared_ptr<Player> p)
{
  std::cout << "Player Added... " << *p << std::endl;
  players.emplace_back(p);
  p->readMessage();
}

void Server::run()
{
}
