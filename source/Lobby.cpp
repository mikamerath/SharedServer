#include <iostream>
#include "Lobby.hpp"

Lobby::Lobby()
{
    
}

void Lobby::RequestGameDetails(std::string& player)// pass in the player object
{
    int i = 0;
    std::cout << "Please choose the following game: " << std::endl;
    std::cout << "1. HEART" << std::endl;
    std::cout << "2. SPADE" << std::endl;
    std::cout << "3. CRAZY EIGHTS" << std::endl;
    std::cout << ">>";
    
    std::cin >> i;
    switch(i)
    {
        case HEART: std::cout << "Heart\n";
            createGame(player);
            break;
        case SPADE: std::cout << "Spades\n";
            createGame(player);
            break;
        case CRAZY_EIGHTS: std::cout << "Crazy Eights\n";
            createGame(player);
            break;
    }
}

void Lobby::createGame(std::string& player)
{
    std::string GameID;
    std::cout << "Name the lobby" << std::endl;
    std::cout << ">>";
    std::cin >> GameID;
    
    //create an instance of game hearts
    std::vector<std::string> heartsGame;
    heartsGame.push_back(player);
    currentAvailableGames[GameID] = heartsGame;
}

void Lobby::joinGame(std::string& player2)
{
    if(currentAvailableGames.empty())
    {
        std::cout << "Sorry but there are no games to join." << std::endl;
    }
    else
    {
        std::cout << "Please enter the name of the game you would like to join." << std::endl;
        std::cout << ">>";
        std::string userInput;
        std::cin >> userInput;
        if (currentAvailableGames[userInput].size() != 4)
        {
            for(auto & map: currentAvailableGames)
            {
                if(userInput == map.first)
                {
                    std::string decision;
                    std::cout << "Would you like to join? (Yes or No)" << std::endl;
                    std::cout << ">>";
                    std::cin >> decision;
                    if(decision == "yes" || decision == "YES")
                    {
                        currentAvailableGames[userInput].push_back(player2);
                        display();
                    }
                    else display();
                    
                }
            }
        }
        else std::cout << "Game is full. Please choose another game." << std::endl;
    }
}

int Lobby::CountPlayers(std::vector<std::string> game)
{
    int numberofPlayers = 0;
    for(int i = 0; i < game.size(); i++)
    {
        game[i];
        numberofPlayers++;
    }
    return numberofPlayers;
}

void Lobby::display()
{
    std::cout << "---------Available Lobbies-----------" << std::endl;
    std::cout << "Name:--------------players:----------" << std::endl;
    for(auto&  vectr : currentAvailableGames)
    {
        std::cout << vectr.first << "---------------"
        << CountPlayers(vectr.second) << "/4-------------" << std::endl;
    }
}
void Lobby::remove ()
{
    if(currentAvailableGames.empty())
    {
        std::cout << "Sorry but there are no game to remove." << std::endl;
    }
    else
    {
        std::cout << "Please enter the name of the game to delete." << std::endl;
        std::cout << ">>";
        std::string userInput;
        std::cin >> userInput;
        //currentAvailableGames.erase(userInput);
        for(auto & map: currentAvailableGames)
        {
            if(userInput == map.first)
            {
                currentAvailableGames.erase(userInput);
            }
            
        }
    }
}

bool Lobby::isEmpty()
{
    return currentAvailableGames.empty();
}

