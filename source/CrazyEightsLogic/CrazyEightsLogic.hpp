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
  CrazyEightsLogic(std::vector<Player>& netPlayers);
  void deal(int numCards);
  bool isGameOver();
  bool isValidCard(Card card);
  std::string convertSuitToString(Suit suit);
  std::string convertRankToString(Value value);
  void displayHand(std::vector<Card> hand);
  void drawCard();
  void setCardsDrawnCounter(int numDrawn);
  int getNumCardsDrawnCounter();
  void playCard(Card&);
  int calculateScore(std::vector<Player> players);
  int getCardScoreValue(Card card);
  void nextTurn();
  int getTurn();
  void playGame();
};
#endif
