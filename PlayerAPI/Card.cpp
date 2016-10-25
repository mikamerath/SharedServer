#include "Card.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>

Card::Card(Suit su)
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

Card::Card(Suit su, int val)
{
  // Assign suit
  suit = su;

  // Assign Value
  if (su == UNDEFINED)
  {
    value = -1; // a card of type UNDEFINED will take any value.
  }
  else if (val < 2 || val > 14)
  {
    // Values are from 2 to 14 corrosponding from 2 - Ace.
    std::cout << "Error: Tried to instantiate a card of undefined value"
              << std::endl;
    throw(2);
  }
  else
  {
    value = val;
  }
}

bool operator<(const Card& a, const Card& b)
{
  if (a.getSuit() < b.getSuit())
  {
    return true;
  }
  else if (a.getSuit() > b.getSuit())
  {
    return false;
  }
  else
    return a.getValue() < b.getValue();
}

bool operator==(const Card& a, const Card& b)
{
  if (a.getSuit() == b.getSuit() && a.getValue() == b.getValue())
  {
    return true;
  }
  else
  {
    return false;
  }
}

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
      deck.push_back(Card(suit, i));
    }
  }
  std::random_device rd;
  std::mt19937 generator(rd());
  std::shuffle(deck.begin(), deck.end(), generator);
  return deck;
}
