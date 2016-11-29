/*This is the executable for the Server, everyting will be initialized
 *here and it will serve to provide all the services that are available
 *in the library
 */

#include<sstream>
#include<iostream>
#include<vector>
#include"source\PlayerAPI\Player.hpp"
#include"source\NetworkInterface\ServerNetworkInterface.hpp"
#include"Lobby.hpp"

struct unStartedGame {
public :
  int id;
  int joinedPlayers;
  std::string type;

  unStartedGame(int id, int joinedPlayers, std::string type) :
    id(id), joinedPlayers(joinedPlayers), type(type) {}
};

std::vector<std::shared_ptr<Player>> knownPlayers = std::vector<std::shared_ptr<Player>>();
std::vector<unStartedGame> lobbyGames = std::vector<unStartedGame>();
Lobby lobby = Lobby();

std::string formatGame(unStartedGame g) {
  std::stringstream ss;
  ss << g.id << " | " << g.joinedPlayers << "/4 | " << g.type;
  return ss.str();
}

void addPlayer(std::shared_ptr<Player> p) {
  std::cout << "Player Added... " << *p << std::endl;
  knownPlayers.emplace_back(p);
  p->connection->write("Lobby Update");
  for (int i = 0; i < lobbyGames.size(); i++)
  {
    p->connection->write(formatGame(lobbyGames[i]));
  }
  p->connection->write("Update End");
  p->readMessage();
}

int main() {
  lobbyGames.emplace_back(unStartedGame(0, 2, "EIGHTS"));
  lobbyGames.emplace_back(unStartedGame(1, 3, "SPADES"));
  lobbyGames.emplace_back(unStartedGame(2, 1, "HEARTS"));

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