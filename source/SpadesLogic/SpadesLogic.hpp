#ifndef SPADESLOGIC_HPP
#define SPADESLOGIC_HPP
#include "source/PlayerAPI/Game.hpp"

#include <iostream>
#include <vector>

class Spades : public Game
{
public:
  void setDeck();
  void printPlayerHands();
  void start();
  void getBids();
  void beginRound(int);
  void startTrick();
  bool validMove(std::vector<Card>, int, Suit&, int);
  int getTrickWinner(std::vector<Card>, int);
  int getNextPlayer(int);
  void score();
  void recordMove(std::vector<Card>);
  Spades(std::vector<Player>);
  ~Spades() {}
private:
  int starter;
  bool spadesBroken;
};

#endif
