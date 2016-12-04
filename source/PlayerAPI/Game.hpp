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
#include "source/AI/AI.hpp"
#include "source/Messages/GameMessage.hpp"

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
  // virtual start();
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
  //This now does everything except turn. Not sure how it's tracked now. - C-Merrill
  void UpdateGameStateMessage()
  {
	  GameMessage message;
	  message.s = (MessageState)s;
	  message.field = field;
	  for (auto player : players) {
		  message.handSizes.push_back(player->getHand().size());
	  }
	  message.deckEmpty = deck.empty();
    for (auto&& player : players)
    {
      if (player->getId() >= 10000)
      {
        std::static_pointer_cast<AI>(player)->updateGameStatus(message);
      }
      else
      {
        player->updateGameStatus(message);
      }
    }
  }
  void deal(int numCards);
  std::vector<std::shared_ptr<Player>> getPlayers() { return players; }
  std::vector<Card> getDiscardPile() { return discardPile; }
  void setDiscardPile(std::vector<Card> dp) { discardPile = dp; }
  std::vector<Card> getDeck() { return deck; }

  void requestMove(std::shared_ptr<Player> player)
  {
    if (player->getId() >= 10000)
    {
      std::static_pointer_cast<AI>(player)->requestMove();
    }
    else
    {
      player->requestMove();
    }
  }

  void requestPass(std::shared_ptr<Player> player)
  {
    if (player->getId() >= 10000)
    {
      std::static_pointer_cast<AI>(player)->requestPass();
    }
    else
    {
      player->requestPass();
    }
  }

  void requestBid(std::shared_ptr<Player> player)
  {
    if (player->getId() >= 10000)
    {
      std::static_pointer_cast<AI>(player)->requestBid();
    }
    else
    {
      player->requestBid();
    }
  }

  void requestSuit(std::shared_ptr<Player> player)
  {
    if (player->getId() >= 10000)
    {
      std::static_pointer_cast<AI>(player)->requestSuit();
    }
    else
    {
      player->requestSuit();
    }
  }
};

// class Message
//{
//  State s;
//  bool turn;
//  std::vector<Card> field;
//};

#endif
