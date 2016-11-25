#include<iostream>
#include<vector>
#include"source\PlayerAPI\Player.hpp"
#include"NetworkInterface.hpp"
#include"ServerNetworkInterface.hpp"

std::vector<Player> players = std::vector<Player>();

void addPlayer(Player p) {
  std::cout << "Player Added... " << p << std::endl;
  players.emplace_back(p);
}

int main() {
  io_service service;
  ServerNetworkInterface NI(12000, service, std::cout,addPlayer);
  std::cout << "Hello World" << std::endl;
  NI.startAccepting();
  std::string msg = "<NONE>";
  while (msg != "EXIT") {
    msg = NI.getMessages();
    if(msg!="")
      std::cout << msg << "\n";
  }
  std::cin.get();
}