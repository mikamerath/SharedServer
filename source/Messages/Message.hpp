#indef MESSAGE_HPP
#define MESSAGE_HPP

#include "source/PlayerAPI/Game.hpp"
#include "source/PlayerAPI/Card.hpp"

#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>

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
