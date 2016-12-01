#ifndef SPADESLOGIC_HPP
#define SPADESLOGIC_HPP

#include "source/PlayerAPI/Game.hpp"
#include <functional>
#include <iostream>
#include <vector>
#include <atomic>
#include <thread>
#include <chrono>

class Spades : public Game
{
public:
  void setDeck();
  void start();
  void getBids();
  void beginRound(int);
  void beginTrick(std::vector<Card>, Suit, int);
  bool validMove(std::vector<Card>, int, Suit&, int);
  void receiveValidMove(Card);
  void receiveBid(int);
  void validMoveFailLoop(bool, std::vector<Card>&, Suit, int&);
  int getTrickWinner(std::vector<Card>, int);
  int getNextPlayer(int);
  void score();
  Spades(){};
  Spades(std::vector<std::shared_ptr<Player>>);
  ~Spades() {}
private:
  int starter;
  bool spadesBroken;
  Card globalCard;
  std::atomic<int> bidPlaceHolder;
  Card movePlaceHolder;
  std::atomic<bool> waitingForBid;
  std::atomic<bool> waitingForMove;
};
 #endif
