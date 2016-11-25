/*This is the executable for the Server, everyting will be initialized
 *here and it will serve to provide all the services that are available
 *in the library
 */

#include<iostream>
#include<vector>
#include"source\PlayerAPI\Player.hpp"
#include"source\NetworkInterface\ServerNetworkInterface.hpp"

std::vector<std::shared_ptr<Player>> players = std::vector<std::shared_ptr<Player>>();

void addPlayer(std::shared_ptr<Player> p) {
  std::cout << "Player Added... " << *p << std::endl;
  players.emplace_back(p);
  p->readMessage();
}

int main() {
  io_service service;
  ServerNetworkInterface NI(12000, service, std::cout, addPlayer);
  NI.startAccepting();
  std::string msg = "<NONE>";
  while (msg != "EXIT") {
    msg = NI.getMessages();
    if (msg != "")
      std::cout << msg << "\n";
  }
  std::cin.get();
}