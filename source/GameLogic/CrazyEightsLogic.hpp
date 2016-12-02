#ifndef CRAZY_EIGHTS_LOGIC_H
#define CRAZY_EIGHTS_LOGIC_H

#include "source/PlayerAPI/Card.hpp"
#include "source/PlayerAPI/Game.hpp"
#include "source/PlayerAPI/Player.hpp"

class CrazyEightsLogic : public Game
{
private:
  int cardsDrawnCounter = 0;       // needs to get reset after each turn
  Suit currentSuit = Suit::HEARTS; // player chooses suit if 8 is played
public:
  CrazyEightsLogic(std::vector<std::shared_ptr<Player>>& netPlayers);
  void deal(int numCards);
  bool isGameOver();
  void gameOver(std::vector<std::shared_ptr<Player>>& netPlayers);
  void validCard(Card card);
  void processValidMove();
  std::string convertSuitToString(Suit suit);
  std::string convertRankToString(Value value);
  void displayHand(std::vector<Card> hand);
  void drawCard();
  void refillDeck();
  void setCardsDrawnCounter(int numDrawn);
  int getCardsDrawnCounter();
  void playCard(Card&);
  void validateSuit(Suit suit);
  int calculateScore(std::vector<std::shared_ptr<Player>> players);
  int getCardScoreValue(Card card);
  void nextTurn();
  int getTurn();
  void start();
};
#endif
