/*
* The Game class holds information that will be needed for each game.
* The functions in the class should be filled in by the Game Lobby group.
*
*
*/

#include "Player.hpp"
#include "Card.hpp"
#include<random>
#include<algorithm>

  enum State
  {
    PASSING,
    BIDDING,
    PLAYING,
    ROUND_OVER,
    GAME_OVER
  };
#ifndef GAME_HPP
#define GAME_HPP

class Game
{
protected:

  std::vector<Card> deck;
  std::vector<Card> discardPile;
  std::vector<Player> players;
  State s;
  std::vector<Card> field;
  int turn; // index in player vector
public:
  //void initializeDeck();
  //void initializeDeck();
  void updateGameStateMessage()
  {
    for (auto&& player : players)
    {
      //player.updateGameStatus(/*coded message*/)
    }
  }
  //void deal(int numCards);
  void initializeDeck(){
  deck.reserve(52);
  std::vector<Suit> suits = {HEARTS, SPADES, CLUBS, DIAMONDS};
  for (auto&& suit : suits)
  {
    for (int i = 2; i < 15; i++)
    {
      deck.push_back(Card(suit, static_cast<Value>(i)));
    }
  }
  std::random_device rd;
  std::mt19937 generator(rd());
  std::shuffle(deck.begin(), deck.end(), generator);
}
};


#endif
/*class Message
{
  State s;
  bool turn;
  std::vector<Card> field;
};*/