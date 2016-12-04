#include "AI.hpp"

AI::AI(int id, TCPConnection::pointer conn)
  : Player(id, conn), numCardsTriedToPlay(0), smartAI(false)
{
}

void AI::alertStartingGame()
{
  std::cout << "AI starting game" << std::endl;
}

void AI::setSmartAI(bool smart)
{
  smartAI = smart;
}

bool AI::isSmartAI()
{
  return smartAI;
}

// I'm assuming here that you call updateGameStatus after a move is accepted...
// If this is true, the request move should function appropriately.
void AI::updateGameStatus(/*coded message of state*/)
{
  std::cout << "AI updating game status" << std::endl;
  numCardsTriedToPlay = 0;
}

int AI::getNumCardsTriedToPlay()
{
  return numCardsTriedToPlay;
}

void AI::requestMove()
{
  if (!smartAI)
  {
    makeDumbAIMove();
  }
}

void AI::makeDumbAIMove()
{
  std::cout << "AI making dumb move" << std::endl;
  Card move;
  if (numCardsTriedToPlay < hand.size())
  {
    move = hand.at(numCardsTriedToPlay);
    ++numCardsTriedToPlay;
  }
  else
  {
    move = Card(UNDEFINED);
  }
  validateMove(move);
}

void AI::requestBid()
{
  if (!smartAI)
  {
    makeDumbBid();
  }
}

void AI::makeDumbBid()
{
  std::cout << "AI making dumb bid" << std::endl;
  validateBid(3);
}

void AI::requestSuit()
{
  if (!smartAI)
  {
    makeDumbSuitChoice();
  }
}

void AI::makeDumbSuitChoice()
{
  std::cout << "AI making dumb suit choice" << std::endl;
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<> dist(0, 3);
  auto suit = static_cast<Suit>(dist(rd));
  validateSuit(suit);
}

void AI::requestPass()
{
  if (!smartAI)
  {
    makeDumbPass();
  }
}

// If pass gets changed to a vector of cards, this needs to be changed.
void AI::makeDumbPass()
{
  validatePass(hand.at(numCardsTriedToPlay));
  numCardsTriedToPlay++;
}
