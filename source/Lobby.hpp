#ifndef LobbyLogic_hpp
#define LobbyLogic_hpp

/// Standard Includes
#include <fstream>
#include <iostream>
#include <map>
#include <stdio.h>
#include <string>
#include <vector>
/// Boost Includes
#include <boost/algorithm/string.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>
/// Application Includes
#include "source/GameLogic/CrazyEightsLogic.hpp"
#include "source/GameLogic/HeartsGame.hpp"
#include "source/GameLogic/SpadesLogic.hpp"
#include "source/Messages/LobbyGame.hpp"
#include "source/PlayerAPI/Game.hpp"
#include "source/PlayerAPI/Player.hpp"

/* NEEDED FEATURES
add functions for player to call leave game
notify waiting game players of other player join/leave
*/

// Class used to create games, allow players to interact with games, and start
// games
// when ready
class Lobby
{
public:
  // constructor
  Lobby();

  // Method called externally when a player connects to the server
  void addPlayer(std::shared_ptr<Player> newPlayer);
  // Method used to attempt to proccess a message recieved from the client
  // while the player is considered to be in the lobby.
  void proccessPlayerMessage(std::string msg, int id);

  // Method to handle a login by the player, which changes the player name from
  // guest to the name supplied
  void procLogin(std::shared_ptr<Player> p, std::string msg);
  // Method to handle a register request by player, which will change player
  // name
  // from guest to the name supplied
  void procRegister(std::shared_ptr<Player> p, std::string msg);
  // Method to send back a list of availible games at the request of the client
  void procGetGames(std::shared_ptr<Player> p, std::string msg);
  // Method to make a game at the request of the client
  void procMakeGame(std::shared_ptr<Player> p, std::string msg);
  // method to join a game at the request of the client
  void procJoinGame(std::shared_ptr<Player> p, std::string msg);
  // method to leave a game at the request of the client
  void procLeaveGame(std::shared_ptr<Player> p);
  // Reads in data from database file
  void readInDatabase();
  // Writes data to database file
  void writeToDatabase();
  // mehtod to start the game once it is full;
  void procStartGame(LobbyGame& game);

private:
  // Helper to identify the sender of a message from known players
  std::shared_ptr<Player> whoIs(int id);
  // Helper to get a list of players from a list of IDs
  std::vector<std::shared_ptr<Player>> whoIs(std::vector<int> ids);
  // Helper to get the game type from a create game message
  GameType getGameType(std::string msg);
  // Helper to translate a single word into a game type
  GameType translateType(std::string type);
  // Helper to find a game by name, returns a LobbyGame with GameType::UNKNOWN
  // if the game is not found
  LobbyGame& findGame(std::string name);
  LobbyGame undef = LobbyGame("", GameType::UNKNOWN);

  // A map of all games that are joinable where the key is the game name
  std::map<std::string, LobbyGame> currentAvailableGames;
  // A list of games that are currently being played
  std::vector<std::shared_ptr<Game>> inProggressGames;
  // A map of all known players that ignores connection status where the
  // key is the player ID
  std::map<int, std::shared_ptr<Player>> knownPlayers;
  std::vector<std::string> storedPlayerNames;
  std::map<std::string, std::string> storedPlayerPasswords;
  // std::map<std::string, std::vector<std::string>> unjoinableGames;
};

#endif /* LobbyLogic_hpp */
