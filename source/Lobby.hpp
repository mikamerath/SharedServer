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

#include "source\PlayerAPI\Player.hpp";
#include "source\PlayerAPI\Game.hpp";
//#include "SpadesLogic.hpp"
#include "CrazyEightsLogic.hpp"
#include "HeartsGame.hpp"


class Lobby
{
public:
    Lobby();
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
    
private:
    enum Game
    {
        HEART = 1,
        SPADE = 2,
        CRAZY_EIGHTS = 3
    };
    std::map<std::string, std::vector<Player> > currentAvailableGames;
    //std::map<std::string, std::vector<std::string>> unjoinableGames;
};


#endif /* LobbyLogic_hpp */
