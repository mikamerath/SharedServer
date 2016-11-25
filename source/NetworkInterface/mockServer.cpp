#include<iostream>
#include"NetworkInterface.hpp"
#include"ServerNetworkInterface.hpp"



void accept_handler(const boost::system::error_code& error)
{
  if (!error)
  {
    std::cout << "Got Con";
  }
}


int main() {

  io_service service;
  ServerNetworkInterface NI(12000, service, std::cout);
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