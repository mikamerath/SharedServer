#include<iostream>
#include<string>

#include <boost/serialization/access.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/algorithm/string.hpp>

#include "ClientNetworkInterface.hpp"
#include "source/Messages/LobbyGame.hpp"


void procJoinGame(std::string response) {
  if (boost::algorithm::starts_with(response, "FAILURE")) {
    std::cout << "FAILED TO JOIN GAME, " << response << std::endl;
  }
  else {
    std::cout << "Joined Game..." << std::endl;
  }
}

void procGameMade(std::string response) {
  if (boost::algorithm::starts_with(response, "FAILURE")) {
    std::cout << "FAILED TO MAKE GAME, " << response << std::endl;
  }
  else {
    std::cout << "Created and joined Game..." << std::endl;
  }
}

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
  bool gotSome = false;
  while (true) {
    try {
      ia >> g;
      gotSome = true;
      std::cout << "\t" << g.name << " | " << printGameType(g.type) 
        << " | " << g.numberJoined << "/4 | ";
      for (auto name : g.playerNames) {
        std::cout << "(" << name << ")";
      }
      std::cout << "\n";
    }
    catch(...){
      break;
    }
  }
  if (!gotSome) {
    std::cout << "<NONE FOUND>" << std::endl;
  }
  std::cout << std::endl;
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
      
      if (boost::algorithm::starts_with(msg, "GET GAMES")) 
      {
        msg = NI.recieve();
        procGamesGot(msg);
      }
      else if (boost::algorithm::starts_with(msg, "MAKE")) 
      {
        msg = NI.recieve();
        procGameMade(msg);
      }
      else if (boost::algorithm::starts_with(msg, "LOGIN")) 
      {
        msg = NI.recieve();
        std::cout << "Now logged in." << std::endl;
      }
      else if (boost::algorithm::starts_with(msg, "JOIN")) 
      {
        msg = NI.recieve();
        procJoinGame(msg);
      }
      else {
        msg = NI.recieve();
        std::cout << "Server Responds : " << msg << std::endl;
      }
     
      if (!NI.isConnected()) {
        std::cout << "Connection to server lost..." << std::endl;
        break;
      }
      std::cout << "Enter message to send : " << std::endl;
      std::getline(std::cin, msg);
    }
  }
  else { // start in offline mode
    std::cout << "Could not connect... press enter to quit";
    std::cin.get();
  }
  std::cout << "...press enter to quit...";
  std::cin.get();
}