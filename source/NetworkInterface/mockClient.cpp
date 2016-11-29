#include<iostream>
#include<string>

#include <boost\serialization\access.hpp>
#include <boost\archive\text_oarchive.hpp>
#include <boost\archive\text_iarchive.hpp>
#include <boost\algorithm\string.hpp>

#include "ClientNetworkInterface.hpp"
#include "source\PlayerAPI\LobbyGame.hpp"


std::string printGameType(GameType t) {
  switch (t)
  {
  case HEARTGAME:
    return "Type : Hearts";
  case SPADEGAME:
    return "Type : Spades";
  case EIGHTSGAME:
    return "Type : Eights";
  default:
    return "Type : Unknown";
  }
}

void procGamesGot(std::string msg) {
  std::stringstream ss;
  ss << msg;
  std::cout << "\nGot Games : \n";
  boost::archive::text_iarchive ia(ss);
  LobbyGame g;
  while (true) {
    try {
      ia >> g;
      std::cout << "\t" << g.name << " | " << printGameType(g.type) 
        << " | " << g.numberJoined << "/4\n";
    }
    catch(...){
      break;
    }
  }
}

int main() {
  io_service service;
  ClientNetworkInterface NI(0, service, std::cout);
  NI.connect("127.0.0.1", 12000); // the port wont change, but the IP will be the Ip of 
                                  // the server.

  if (NI.isConnected()) { // start the client in online mode
    std::string msg = "";
    std::cout << "Enter message to send : " << std::endl;
    std::getline(std::cin, msg);
    while (msg != "EXIT") {
      NI.send(msg);
      if (boost::algorithm::starts_with(msg, "GET GAMES")) {
        msg = NI.recieve();
        procGamesGot(msg);
      }
      else {
        msg = NI.recieve();
        std::cout << "Server Responds : " << msg << std::endl;
      }
      std::cout << "Enter message to send : " << std::endl;
      std::getline(std::cin, msg);
    }
  }
  else { // start in offline mode
    std::cout << "Could not connect... press enter to quit";
    std::cin.get();
  }
  
}