#include "AI.hpp"

AI::AI(int id, TCPConnection::pointer conn)
  : Player(id, conn), numCardsTriedToPlay(0), smartAI(false)
{
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
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<> dist(0, 3);
  auto suit = static_cast<Suit>(dist(rd));
  validateSuit(suit);
}
