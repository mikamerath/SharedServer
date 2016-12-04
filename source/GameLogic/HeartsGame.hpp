#ifndef HEARTS_GAME_HPP
#define HEARTS_GAME_HPP

#include "source/PlayerAPI/Game.hpp"
#include "source/PlayerAPI/Player.hpp"

#include <setjmp.h>
#include <boost/asio.hpp>
#include <random>

class HeartsGame : public Game
{
public: 
  HeartsGame(std::vector<std::shared_ptr<Player>>& players);
  ~HeartsGame();
  // looks through each hand to find the 2 of clubs
  int findTwoOfClubs();
  // function for passing cards at beginging of round
  void passCards(int round);
  void endTurn(int currentPlayer);
  void endRound();
  bool setPassCards(Card card, int id);
  int playCard(Card card, int id);
  std::vector<std::shared_ptr<Player>> getPlayers() { return players; }
  std::vector<Card> getCenterPile() { return centerPile; }
  void start();

private:
  std::vector<Card> initializeDeck();
  void dealCards(std::vector<Card>& Deck);
  std::vector<std::shared_ptr<Player>> players;
  // compares hand against the lead suit
  bool noLeadSuit(Suit s, std::vector<Card> h);
  void validateMove(int index, Card move);
  std::vector<Card> centerPile;

  bool brokenHearts = false;
  void validatePass(Card c, int id);
  int turn = 0;
  int numTrick = 0;
  std::vector<std::vector<Card>> cardsToPass;
  void passCard(Card tmp, int i);
  bool roundOver = false;
  void gameOver();
  int round = 0;
};

#endif // HEARTS_GAME_HPP
