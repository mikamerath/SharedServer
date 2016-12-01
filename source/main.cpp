/*This is the executable for the Server, everyting will be initialized
 *here and it will serve to provide all the services that are available
 *in the library
 */

#include<sstream>
#include<iostream>
#include<vector>
#include"source/PlayerAPI/Player.hpp"
#include"source/NetworkInterface/ServerNetworkInterface.hpp"
#include"Lobby.hpp"

Lobby lobby = Lobby();

//void addPlayer(std::shared_ptr<Player> p) {
//  std::cout << "Player Added... " << *p << std::endl;
//  knownPlayers.emplace_back(p);
//  p->connection->write("Lobby Update");
//  for (int i = 0; i < lobbyGames.size(); i++)
//  {
//    p->connection->write(formatGame(lobbyGames[i]));
//  }
//  p->connection->write("Update End");
//  p->readMessage();
//}

int main()
{
  io_service service;
  ServerNetworkInterface NI(12000, service, std::cout, boost::bind(&Lobby::addPlayer,lobby,_1));
  NI.startAccepting();
  std::string msg = "<NONE>";
  while (msg != "EXIT") {
   // msg = NI.getMessages();
    std::cout << "Enter Server Command : " << std::endl;
    std::getline(std::cin, msg);
  }
  std::cin.get();
}
