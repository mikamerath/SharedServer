#include<iostream>
#include"ClientNetworkInterface.hpp"


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
      msg = NI.recieve();
      std::cout << "Server Responds : " << msg << std::endl;
      std::cout << "Enter message to send : " << std::endl;
      std::getline(std::cin, msg);
    }
  }
  else { // start in offline mode
    std::cout << "Could not connect... press enter to quit";
    std::cin.get();
  }
  
}