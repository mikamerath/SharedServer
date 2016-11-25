#ifndef __SERVER__
#define __SERVER__

#include<iostream>
#include<vector>
#include"source\PlayerAPI\Player.hpp"
#include"source\NetworkInterface\ServerNetworkInterface.hpp"

class Server {
private:
  // The vector of al known connected players
  std::vector<std::shared_ptr<Player>> players = std::vector<std::shared_ptr<Player>>();

};

#endif // __SERVER__