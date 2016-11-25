#include<iostream>
#include"ClientNetworkInterface.hpp"


int main() {
  io_service service;
  ClientNetworkInterface NI(0, service, std::cout);
  std::cout << "Hello World" << std::endl;
  NI.connect("127.0.0.1", 12000);
  std::string msg = "";
  while (msg != "EXIT") {
    std::getline(std::cin, msg);
    NI.send(msg);
  }
}