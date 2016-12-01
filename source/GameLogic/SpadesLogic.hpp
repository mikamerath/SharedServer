#ifndef SPADESLOGIC_HPP
#define SPADESLOGIC_HPP

#include "source/PlayerAPI/Game.hpp"
#include <atomic>
#include <chrono>
#include <functional>
#include <iostream>
#include <thread>
#include <vector>

class Spades : public Game
{
public:
  void setDeck();
  bool validMove();
  void receiveValidMove(Card);
  void receiveBid(int);
  int getTrickWinner(std::vector<Card>, int);
  int getNextPlayer(int);
  void score();
  Spades(){};
  Spades(std::vector<std::shared_ptr<Player>>);
  ~Spades(){}
private:
  int starter;
  bool spadesBroken;
  Card globalCard;
  std::atomic<int> bidPlaceHolder;
  Card movePlaceHolder;
  std::atomic<bool> waitingForBid;
  std::atomic<bool> waitingForMove;
		std::vector<Card> trick;
		Suit ledSuit;
		int trickWinner;
};
#endif
