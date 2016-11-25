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
  std::vector<Player> players;
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
      player.updateGameStatus(/*coded message*/);
    }
  }
  void deal(int numCards);
  std::vector<Player> getPlayers() { return players; }
  std::vector<Card> getDiscardPile() { return discardPile; }
  std::vector<Card> getDeck() { return deck; }
};

class Message
{
  State s;
  bool turn;
  std::vector<Card> field;
};

#endif