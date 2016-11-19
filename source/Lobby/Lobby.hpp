#ifndef Lobby_hpp
#define Lobby_hpp

#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include <iostream>

class Lobby
{
public:
    Lobby();
    void createGame(std::string& player);
    void joinGame(std::string& player2);
    void display();
    void remove();
    void RequestGameDetails(std::string& player);
    int CountPlayers(std::vector<std::string> game);
    bool isEmpty();
    
private:
    enum Game
    {
        HEART = 1,
        SPADE = 2,
        CRAZY_EIGHTS = 3
    };
    std::map<std::string, std::vector<std::string> > currentAvailableGames;
    //std::map<std::string, std::vector<std::string>> unjoinableGames;
};

#endif
