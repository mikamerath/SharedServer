#ifndef HEARTS_GAME_HPP
#define HEARTS_GAME_HPP

#include "source\PlayerAPI\Player.hpp"
#include <boost/asio.hpp>
#include <random>

class HeartsGame
{
public:
  HeartsGame(std::vector<Player>& players);
  ~HeartsGame();
  void play_Hearts();
  // looks through each hand to find the 2 of clubs
  int findTwoOfClubs();
  // function for passing cards at beginging of round
  void passCards(int round);
  int endTurn(int currentPlayer);
  void endRound();
  bool setPassCards(std::vector<Card> cards, std::string name);
  int playCard(Card card, std::string name);
  std::vector<Player> getPlayers() { return players; }
  std::vector<Card> getCenterPile() { return centerPile; }
private:
  std::vector<Card> initializeDeck();
  void dealCards(std::vector<Card>& Deck);

  // checks to see if a players hand is all hearts.
  bool allhearts(std::vector<Card> h);
  // compares hand against the lead suit
  bool noLeadSuit(Suit s, std::vector<Card> h);
  bool validateMove(int index, Card move, int t, int i);
  std::vector<Player> players;
  std::vector<Card> centerPile;

  bool brokenHearts = false;

  int turn = 0;
  std::vector<std::vector<Card>> cardsToPass;
  void passCard(Card tmp, int i);
};

#endif // HEARTS_GAME_HPP