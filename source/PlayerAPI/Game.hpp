/*
* The Game class holds information that will be needed for each game.
* The functions in the class should be filled in by the Game Lobby group.
*
*
*/

#ifndef GAME_HPP
#define GAME_HPP

#include "Card.hpp"
#include "Player.hpp"

#include <algorithm>
#include <random>

#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>

enum State
{
  PASSING,
  BIDDING,
  PLAYING,
  ROUND_OVER,
  GAME_OVER
};

class Game
{
protected:
  State s;
  std::vector<Card> deck;
  std::vector<Card> discardPile;
  std::vector<std::shared_ptr<Player>> players;
  std::vector<Card> field;
  int turn; // index in player vector
public:
  // Function used to deal out a random deck of 52 cards
  std::vector<Card> initializeDeck()
  {
    std::vector<Card> deck;
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
    return deck;
  }
  void UpdateGameStateMessage()
  {
    for (auto&& player : players)
    {
	player->updateGameStatus(/*coded message*/);
    }
  }
  void deal(int numCards);
  std::vector<std::shared_ptr<Player>> getPlayers() { return players; }
  std::vector<Card> getDiscardPile() { return discardPile; }
  std::vector<Card> getDeck() { return deck; }
};

class Message
{
	friend class boost::serialization::access;

public:
  State s;
  bool turn;
  std::vector<Card> field;
  std::vector<int> handSizes;
  std::vector<Card> playerHand;
  bool deckEmpty;
  
  Message()
  {

  }

  Message(State state, bool t, std::vector<Card> f, std::vector<int> h, std::vector<Card> p, bool d)
  {
    s = state;
    turn = t;
    field = f;
    handSizes = h;
    playerHand = p;
    deckEmpty = d;
  }
  
  template <class Archive>
  inline void serialize(Archive& ar, const unsigned int version)
  {
    ar& s;
    ar& turn;
    ar& field;
    ar& handSizes;
    ar& playerHand;
    ar& deckEmpty;
  }
};

#endif