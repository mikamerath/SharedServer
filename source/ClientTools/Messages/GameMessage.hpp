#ifndef GAMEMESSAGE_HPP
#define GAMEMESSAGE_HPP

// replace this include with path to card.hpp
#include "source/PlayerAPI/Card.hpp"

#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>

enum MessageState
{
	PASSING_m,
	BIDDING_m,
	PLAYING_m,
	ROUND_OVER_m,
	GAME_OVER_m
};

class GameMessage
{
  friend class boost::serialization::access;

public:
  MessageState s;
  bool turn;
  std::vector<Card> field;
  std::vector<int> handSizes;
  std::vector<Card> playerHand;
  bool deckEmpty;

  GameMessage()
  {
    s = PASSING_m;
    turn = false;
    field = {};
    handSizes = {0, 0, 0, 0};
    playerHand = {};
    deckEmpty = false;
  }

  GameMessage(MessageState state,
              bool t,
              std::vector<Card> f,
              std::vector<int> h,
              std::vector<Card> p,
              bool d)
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
