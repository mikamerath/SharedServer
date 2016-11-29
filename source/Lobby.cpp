//
//  LobbyLogic.cpp
//  LobbyFinal
//
//  Created by Alex Collantes on 11/17/16.
//  Copyright © 2016 Alex Collantes. All rights reserved.
//


/* NEEDED FEATURES
add player to lobby
add function for player to callback when a message is recieved and proccess it
add functions for player to call to join game, create game, request list of games, leave game
notify waiting game players of other player join/leave
*/

#include "Lobby.hpp"

Lobby::Lobby()
{
  currentAvailableGames.emplace("GAME1", LobbyGame("GAME1", GameType::HEARTGAME));
  currentAvailableGames.emplace("GAME2", LobbyGame("GAME2", GameType::HEARTGAME));
  currentAvailableGames.emplace("GAME3", LobbyGame("GAME3", GameType::SPADEGAME));
  currentAvailableGames.emplace("GAME4", LobbyGame("GAME4", GameType::SPADEGAME));
  currentAvailableGames.emplace("GAME5", LobbyGame("GAME5", GameType::EIGHTSGAME));
  currentAvailableGames.emplace("GAME6", LobbyGame("GAME6", GameType::EIGHTSGAME));
}
void Lobby::addPlayer(std::shared_ptr<Player> newPlayer)
{
  knownPlayers.emplace(newPlayer->getId(), newPlayer);
  newPlayer->setProcLobbyCommand(boost::bind(&Lobby::proccessPlayerMessage, this, _1,_2));
  newPlayer->readLobbyMessage();
}

void Lobby::proccessPlayerMessage(std::string msg, int id)
{
  std::shared_ptr<Player> p = whoIs(id);
  std::cout << "Got : " << msg << " from : " << *p << std::endl;
  if (p != NULL) {
    if (boost::algorithm::starts_with(msg,"GET GAMES")) procGetGames(p,msg);
    else if (boost::algorithm::starts_with(msg, "MAKE")) procMakeGame(p,msg);
    else if (boost::algorithm::starts_with(msg, "JOIN")) procJoinGame(p, msg);
    else p->connection->write("No Such Command");
    p->readLobbyMessage();
  }
}

void Lobby::procGetGames(std::shared_ptr<Player> p, std::string msg)
{
  GameType t = getGameType(msg);
  std::stringstream ss;
  boost::archive::text_oarchive oa(ss);
  if (t == GameType::ALL) {
    for (auto game : currentAvailableGames)
    {
      oa << game.second;
    }
  }
  else {
    for (auto game : currentAvailableGames)
    {
      if(game.second.type == t)
        oa << game.second;
    }
  }
  p->connection->write(ss.str());
}

void Lobby::procMakeGame(std::shared_ptr<Player> p, std::string msg)
{
  std::stringstream ss;
  ss << msg;
  std::string command, type, name;
  ss >> command;
  ss >> type;
  std::getline(ss, name);

  GameType gameType = translateType(type);
  if (gameType == GameType::UNKNOWN) {
    p->connection->write("FAILURE : UNKNOWN GAME TYPE");
    return;
  }

  LobbyGame game(name, gameType);
  game.joinedPlayers.emplace_back(p);
  game.numberJoined = 1;

  // TODO: implement catching of duplicate names

  currentAvailableGames.emplace(name, game);
  p->connection->write("SUCCESS");
}

void Lobby::procJoinGame(std::shared_ptr<Player> p, std::string msg)
{
  std::stringstream ss;
  ss << msg;
  std::string command, name;
  ss >> command;
  std::getline(ss, name);

  LobbyGame& game = findGame(name);
  if (game.type == GameType::UNKNOWN) {
    p->connection->write("FAILURE : GAME NOT FOUND");
    return;
  }

  if (game.numberJoined == 4) {
    p->connection->write("FAILURE : GAME FULL");
    return;
  }

  game.joinedPlayers.emplace_back(p);
  game.numberJoined++;

  if (game.numberJoined == 4) {
    // TODO: start the game and remove it from the joinable list
  }

  p->connection->write("SUCCESS");
}

std::shared_ptr<Player> Lobby::whoIs(int id)
{
  auto it = knownPlayers.find(id);
  if (it != knownPlayers.end()) return it->second;
  else return NULL;
}

GameType Lobby::getGameType(std::string msg)
{
  if (boost::algorithm::ends_with(msg, "HEARTS")) return GameType::HEARTGAME;
  if (boost::algorithm::ends_with(msg, "SPADES")) return GameType::SPADEGAME;
  if (boost::algorithm::ends_with(msg, "EIGHTS")) return GameType::EIGHTSGAME;
  if (boost::algorithm::ends_with(msg, "ALL")) return GameType::ALL;
  return GameType::ALL;
}

GameType Lobby::translateType(std::string type)
{
  if (type == "HEARTS") return GameType::HEARTGAME;
  else if (type == "SPADES") return GameType::SPADEGAME;
  else if (type == "EIGHTS") return GameType::EIGHTSGAME;
  else return GameType::UNKNOWN;
}

LobbyGame & Lobby::findGame(std::string name)
{
  auto it = currentAvailableGames.find(name);
  if (it != currentAvailableGames.end()) return it->second;
  else return LobbyGame("",GameType::UNKNOWN);
}


//
////Prompts user for type of game. Uses switch to create the actual game. Used in Join Game line 90.
//
//void Lobby::RequestGameDetails(std::vector<Player>& players)
//{
//    int i = 0;
//    std::cout << "Please choose the following game: " << std::endl;
//    std::cout << "1. HEART" << std::endl;
//    std::cout << "2. SPADE" << std::endl;
//    std::cout << "3. CRAZY EIGHTS" << std::endl;
//    std::cout << ">>";
//    
//    std::cin >> i;
//    switch(i)
//    {
//        case HEART: std::cout << "Heart\n";
//            CreateHeartLogic(players);
//            break;
//        case SPADE: std::cout << "Spades\n";
//            CreateSpadesLogic(players);
//            break;
//        case CRAZY_EIGHTS: std::cout << "Crazy Eights\n";
//            CreateCrazyEightsLogic(players);
//            break;
//    }
//}
//
///*
//    string s = NetworkInterface.read(string: ip);
//        sstream(s);
//        while (s.good()) {
//            input << s;
//        }
// */
//
//void Lobby::CreateGame(Player& player)
//{
//    std::string GameID;
//    std::cout << "Name the lobby" << std::endl;
//    std::cout << ">>";
//    std::cin >> GameID;
//    
//    //create a new instance of a vector
//    std::vector<Player> vectOfPlayers;
//    vectOfPlayers.push_back(player);
//    currentAvailableGames[GameID] = vectOfPlayers;
//    //std::cout << currentAvailableGames[GameID].size();
//}
////function to call to name the lobby
//std::string Lobby::NameOfGame(){
//    std::cout << "Please enter the name of the game you would like to join." << std::endl;
//    std::cout << ">>";
//    std::string userInput;
//    std::cin >> userInput;
//    return userInput;
//    
//}
//
//void Lobby::joinGame(Player& player2)
//{
//    if(currentAvailableGames.empty())
//    {
//        std::cout << "Sorry but there are no games to join." << std::endl;
//    }
//    else
//    {
//        std::string userInput = NameOfGame();
//
//        if (currentAvailableGames[userInput].size() < 5)
//        {
//            for(auto & map: currentAvailableGames)
//            {
//                if(userInput == map.first)
//                {
//                    std::string decision;
//                    std::cout << "Would you like to join? (Yes or No)" << std::endl;
//                    std::cout << ">>";
//                    std::cin >> decision;
//                    if(decision == "yes" || decision == "YES")
//                    {
//                        currentAvailableGames[userInput].push_back(player2);
//                        //display();
//                        if(currentAvailableGames[userInput].size() == 4){
//                            //create the game
//                            RequestGameDetails(currentAvailableGames[userInput]);
//                        }
//                    }
//                    else display();
//                    
//                }
//            }
//        }
//        else std::cout << "Game is full. Please choose another game." << std::endl;
//    }
//}
//
//int Lobby::CountPlayers(std::vector<Player> game)
//{
//    int numberofPlayers = 0;
//    for(int i = 0; i < game.size(); i++)
//    {
//        //game[i];
//        numberofPlayers++;
//    }
//    return numberofPlayers;
//}
//
//void Lobby::display()
//{
//    std::cout << "---------Available Lobbies-----------" << std::endl;
//    std::cout << "Name:--------------players:----------" << std::endl;
//    for(auto&  vectr : currentAvailableGames)
//    {
//        std::cout << vectr.first << "---------------"
//        << CountPlayers(vectr.second) << "/4-------------" << std::endl;
//    }
//}
//void Lobby::remove ()
//{
//    if(currentAvailableGames.empty())
//    {
//        std::cout << "Sorry but there are no game to remove." << std::endl;
//    }
//    else
//    {
//        std::cout << "Please enter the name of the game to delete." << std::endl;
//        std::cout << ">>";
//        std::string userInput;
//        std::cin >> userInput;
//        //currentAvailableGames.erase(userInput);
//        for(auto & map: currentAvailableGames)
//        {
//            if(userInput == map.first)
//            {
//                currentAvailableGames.erase(userInput);
//            }
//            
//        }
//    }
//}
//
//void Lobby::CreateCrazyEightsLogic(std::vector<Player> &players){
//    CrazyEightsLogic EightsGame(players);
//}
//void Lobby::CreateSpadesLogic(std::vector<Player>& players){
//    //SpadesLogic spadesGame(players);
//}
//void Lobby::CreateHeartLogic(std::vector<Player>& players){
//    HeartsGame heartsGame(players);
//    heartsGame.play_Hearts();
//}
//
//bool Lobby::isEmpty()
//{
//    return currentAvailableGames.empty();
//}
//int main(){
//    
//    Player player0(0, "1.11.111");
//    Player player1(1, "1.12.111");
//    Player player2(2, "1.13.111");
//    Player player3(3, "1.14.111");
//    Lobby lobby;
//    std::vector<Player> netplayers;
//    netplayers.push_back(player0);
//    netplayers.push_back(player1);
//    netplayers.push_back(player2);
//    netplayers.push_back(player3);
//    lobby.CreateHeartLogic(netplayers);
//    
//    
//    
//}
//
