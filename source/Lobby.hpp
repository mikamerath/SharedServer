//
//  LobbyLogic.hpp
//  LobbyFinal
//
//  Created by Alex Collantes on 11/17/16.
//  Copyright © 2016 Alex Collantes. All rights reserved.
//

#ifndef LobbyLogic_hpp
#define LobbyLogic_hpp


#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include <iostream>

#include <boost\serialization\access.hpp>
#include <boost\archive\text_oarchive.hpp>
#include <boost\archive\text_iarchive.hpp>
#include <boost\algorithm\string.hpp>

#include "source\Messages\LobbyGame.hpp"
#include "source\PlayerAPI\Player.hpp"
#include "source\PlayerAPI\Game.hpp"


/* NEEDED FEATURES
add player to lobby
add function for player to callback when a message is recieved and proccess it
add functions for player to call to join game, create game, request list of games, leave game
notify waiting game players of other player join/leave
*/

class Lobby
{
public:
    Lobby();

    // Method called externally when a player connects to the server
    void addPlayer(std::shared_ptr<Player> newPlayer);
    // Method used to attempt to proccess a message recieved from the client
    // while the player is considered to be in the lobby.
    void proccessPlayerMessage(std::string msg, int id);

    // Method to send back a list of availible games at the request of the client
    void procGetGames(std::shared_ptr<Player> p, std::string msg);
    void procMakeGame(std::shared_ptr<Player> p, std::string msg);
    void procJoinGame(std::shared_ptr<Player> p, std::string msg);
    void procLeaveGame(std::shared_ptr<Player> p);

    /*
    void CreateGame(Player& player);
    void joinGame(Player& player2);
    void display();
    void remove();
    void RequestGameDetails(std::vector<std::shared_ptr<Player>>& players);
    int CountPlayers(std::vector<std::shared_ptr<Player>> game);
    bool isEmpty();
    void CreateTestGame(std::vector<std::shared_ptr<Player>>& players);
    void CreateCrazyEightsLogic(std::vector<std::shared_ptr<Player>>& players);
    void CreateSpadesLogic(std::vector<std::shared_ptr<Player>>& players);
    void CreateHeartLogic(std::vector<std::shared_ptr<Player>>& players);
    std::string NameOfGame();
    */
    
private:
  // Hellper to identify the sender of a message from known players
  std::shared_ptr<Player> whoIs(int id);
  GameType getGameType(std::string msg);
  GameType translateType(std::string type);
  LobbyGame& findGame(std::string name);

  std::map<std::string, LobbyGame> currentAvailableGames;
  std::map<int , std::shared_ptr<Player>> knownPlayers;
  //std::map<std::string, std::vector<std::string>> unjoinableGames;
};


#endif /* LobbyLogic_hpp */
