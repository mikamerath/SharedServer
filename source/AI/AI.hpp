#ifndef AI_HPP
#define AI_HPP

#include "source/PlayerAPI/Player.hpp"
#include <random>

class AI : public Player
{
private:
  int numCardsTriedToPlay;
  bool smartAI;
  void makeDumbAIMove();
  void makeDumbBid();
  void makeDumbSuitChoice();

public:
  AI(int, TCPConnection::pointer);
  void setSmartAI(bool);
  void updateGameStatus(/*coded message of state*/);
  void requestMove();
  void requestBid();
  void requestSuit();
  bool isSmartAI();
  int getNumCardsTriedToPlay();
};

#endif
