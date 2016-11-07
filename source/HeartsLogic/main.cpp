#include "HeartsGame.hpp"

#include <iostream>

int main()
{
  std::vector<Player> players;
  players.reserve(4);
  HeartsGame game(players);
  std::cout << "IT BUILDS\n";
  return 0;
}