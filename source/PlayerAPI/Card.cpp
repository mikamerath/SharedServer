/*
 * Card Class
 *
 * -David Browning, Ligia Frangello & Katie Sweet
 *
 * The purpose of this file is to allow others to build a card object.
 * Cards contain a suit and a value.
 * Suit is an enum {HEARTS}
 *
 * The constuctor accepts the suit enum and one integer.
 *
 * The suit enum (HEARTS, SPADES, CLUBS, DIAMONDS, UNDEFINED) determines the
 * suit. The reason for the UNDEFINED suit type is that in the Player Class,
 * there is a function called requestMove() that returns a vector of Cards.
 * In the game Crazy Eight's, a move can consist of drawing a card from the
 * deck. We need an UNDEFINED type to alertnthe Crazy Eight's game logic that
 * they chose the draw pile instead of playing a card.
 *
 * The integer (1-13) determines the value. Value is on a 1 based index for
 * easier scoring.
 *
 */

#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>

enum Suit
{
  HEARTS,
  SPADES,
  CLUBS,
  DIAMONDS,
  UNDEFINED
};

class Card
{
private:
  Suit suit;
  unsigned int value;

public:
  ~Card() {}
  Card(Suit su)
  {
    suit = su;
    if (su == UNDEFINED)
    {
      value = 0;
    }
    else
    {
      std::cout << "Error. Cannot instantiate a card without a value."
                << std::endl;
      throw(2);
    }
  }
  Card(Suit su, int val)
  {
    // Assign suit
    suit = su;

    // Assign Value
    if (su == UNDEFINED)
    {
      value = -1; // a card of type UNDEFINED will take any value.
    }
    else if (val < 1 || val > 13)
    {
      // Values are from 1 to 13 corrosponding from Ace - King.
      std::cout << "Error: Tried to instantiate a card of undefined value"
                << std::endl;
      throw(2);
    }
    else
    {
      value = val;
    }
  }
  Suit getSuit() const { return suit; }
  int getValue() const { return value; }
};

std::vector<Card> initializeDeck()
{
  std::vector<Card> deck;
  deck.reserve(52);
  std::vector<Suit> suits = {HEARTS, SPADES, CLUBS, DIAMONDS};
  for (auto&& suit : suits)
  {
    for (int i = 1; i < 14; i++)
    {
      deck.push_back(Card(suit, i));
    }
  }
  std::random_device rd;
  std::mt19937 generator(rd());
  std::shuffle(deck.begin(), deck.end(), generator);
  return deck;
}
