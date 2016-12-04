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
  void makeDumbPass();

public:
  AI(int, TCPConnection::pointer);
  void alertStartingGame();
  void setSmartAI(bool);
  void updateGameStatus(/*coded message of state*/);
  void requestMove();
  void requestBid();
  void requestSuit();
  void requestPass();
  bool isSmartAI();
  int getNumCardsTriedToPlay();
};

#endif
