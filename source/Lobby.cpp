#include "Lobby.hpp"

Lobby::Lobby()
{
  currentAvailableGames.emplace(
    "GAME1", LobbyGame("GAME1", GameType::HEARTGAME));
  currentAvailableGames.emplace(
    "GAME2", LobbyGame("GAME2", GameType::HEARTGAME));
  currentAvailableGames.emplace(
    "GAME3", LobbyGame("GAME3", GameType::SPADEGAME));
  currentAvailableGames.emplace(
    "GAME4", LobbyGame("GAME4", GameType::SPADEGAME));
  currentAvailableGames.emplace(
    "GAME5", LobbyGame("GAME5", GameType::EIGHTSGAME));
  currentAvailableGames.emplace(
    "GAME6", LobbyGame("GAME6", GameType::EIGHTSGAME));
}

void Lobby::addPlayer(std::shared_ptr<Player> newPlayer)
{
  knownPlayers.emplace(newPlayer->getId(), newPlayer);
  newPlayer->setProcLobbyCommand(
    boost::bind(&Lobby::proccessPlayerMessage, this, _1, _2));
  newPlayer->readLobbyMessage();
}

void Lobby::proccessPlayerMessage(std::string msg, int id)
{
  std::shared_ptr<Player> p = whoIs(id);
  std::cout << "Got : " << msg << " from : " << *p << std::endl;
  bool willRemain = true;
  if (p != NULL)
  {
    if (boost::algorithm::starts_with(msg, "GET GAMES"))
    {
      procGetGames(p, msg);
    }
    else if (boost::algorithm::starts_with(msg, "LOGIN"))
    {
      procLogin(p, msg);
    }
    else if (boost::algorithm::starts_with(msg, "REGISTER"))
    {
      procRegister(p, msg);
    }
    else if (boost::algorithm::starts_with(msg, "MAKE"))
    {
      // willRemain = false;
      procMakeGame(p, msg);
    }
    else if (boost::algorithm::starts_with(msg, "JOIN"))
    {
      // willRemain = false;
      procJoinGame(p, msg);
    }
    else
      p->connection->write("No Such Command");
    p->readLobbyMessage();
  }
}

void Lobby::procLogin(std::shared_ptr<Player> p, std::string msg)
{
  std::stringstream ss;
  std::string command, name, pass;
  ss << msg;
  ss >> command;
  ss >> name;
  ss >> pass;

  p->setName(name);
  p->connection->write("SUCCESS");
}

void Lobby::procRegister(std::shared_ptr<Player> p, std::string msg)
{
  // TODO FIll in
}

void Lobby::procGetGames(std::shared_ptr<Player> p, std::string msg)
{
  GameType t = getGameType(msg);
  std::stringstream ss;
  boost::archive::text_oarchive oa(ss);
  if (t == GameType::ALL)
  {
    for (auto game : currentAvailableGames)
    {
      oa << game.second;
    }
  }
  else
  {
    for (auto game : currentAvailableGames)
    {
      if (game.second.type == t) oa << game.second;
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
  name.erase(0, 1);

  GameType gameType = translateType(type);
  if (gameType == GameType::UNKNOWN)
  {
    p->connection->write("FAILURE : UNKNOWN GAME TYPE");
    return;
  }

  if (currentAvailableGames.find(name) != currentAvailableGames.end())
  {
    p->connection->write("FAILURE : ALREADY EXSISTS");
    return;
  }

  LobbyGame game(name, gameType);
  game.joinedPlayers.emplace_back(p->getId());
  game.playerNames.emplace_back(p->getName());
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
  name.erase(0, 1);

  LobbyGame& game = findGame(name);
  if (game.type == GameType::UNKNOWN)
  {
    p->connection->write("FAILURE : GAME NOT FOUND");
    return;
  }

  if (game.numberJoined == 4)
  {
    p->connection->write("FAILURE : GAME FULL");
    return;
  }

  game.joinedPlayers.emplace_back(p->getId());
  game.playerNames.emplace_back(p->getName());
  game.numberJoined++;

  p->connection->write("SUCCESS");

  if (game.numberJoined == 4)
  {
    procStartGame(game);
  }
}

void Lobby::procStartGame(LobbyGame& game)
{
  std::shared_ptr<Game> newGame;
  switch (game.type)
  {
  case GameType::EIGHTSGAME:
  // newGame = std::make_shared<CrazyEightsLogic>(whoIs(game.joinedPlayers));
  case GameType::HEARTGAME:
  // newGame = std::make_shared<HeartsGame>(whoIs(game.joinedPlayers));
  case GameType::SPADEGAME:
    newGame = std::make_shared<Spades>(whoIs(game.joinedPlayers));
  default:
    break;
  }

  inProggressGames.emplace_back(newGame);
  currentAvailableGames.erase(game.name);
  // newGame->start();
}

std::shared_ptr<Player> Lobby::whoIs(int id)
{
  auto it = knownPlayers.find(id);
  if (it != knownPlayers.end())
    return it->second;
  else
    return NULL;
}

std::vector<std::shared_ptr<Player>> Lobby::whoIs(std::vector<int> ids)
{
  std::vector<std::shared_ptr<Player>> players;
  for (auto id : ids)
  {
    players.emplace_back(whoIs(id));
  }
  return players;
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
  if (type == "HEARTS")
    return GameType::HEARTGAME;
  else if (type == "SPADES")
    return GameType::SPADEGAME;
  else if (type == "EIGHTS")
    return GameType::EIGHTSGAME;
  else
    return GameType::UNKNOWN;
}

LobbyGame& Lobby::findGame(std::string name)
{
  auto it = currentAvailableGames.find(name);
  if (it != currentAvailableGames.end())
    return it->second;
  else
  {
    LobbyGame undef = LobbyGame("", GameType::UNKNOWN);
    return undef;
  }
}
