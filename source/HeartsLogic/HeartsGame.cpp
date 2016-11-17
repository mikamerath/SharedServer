#include "HeartsGame.hpp"
#include <iostream>

// constructor
// takes in a vector of players
HeartsGame::HeartsGame(std::vector<Player>& players)
{
  this->players = players;
  std::vector<Card> tmp;
  for (int i = 0; i < 4; i++)
  {
    cardsToPass.push_back(tmp);
  }
}

HeartsGame::~HeartsGame()
{
}

// creates deck of cards taken from Card.cpp
// returns the deck
std::vector<Card> HeartsGame::initializeDeck()

{
  std::vector<Card> deck;
  deck.reserve(52);
  std::vector<Suit> suits = {HEARTS, SPADES, CLUBS, DIAMONDS};
  for (auto&& suit : suits)
  {
    for (int i = 2; i <= 14; i++)
    {
      deck.push_back(Card(suit, (Value)i));
    }
  }
  return deck;
}

// looks through each hand to find the 2 of clubs
// returns the index of the player with the 2 of clubs
int HeartsGame::findTwoOfClubs()
{
  for (size_t i = 0; i < players.size(); ++i)
  {
    std::vector<Card> temp = players[i].getHand();
    for (auto j = 0; j < 13; ++j)
    {
      if (temp[j].getSuit() == Suit::CLUBS && temp[j].getValue() == 2)
      {
        return i;
      }
    }
  }
  return -1;
}

// function for passing cards at beginging of round
// takes the round number
void HeartsGame::passCards(int round)
{
  for (size_t i = 0; i < players.size(); i++)
  {
    Card card1 = cardsToPass[(i + round + 1) % players.size()][0];
    Card card2 = cardsToPass[(i + round + 1) % players.size()][1];
    Card card3 = cardsToPass[(i + round + 1) % players.size()][2];
    players[i].insertCardToHand(card1);
    players[i].insertCardToHand(card2);
    players[i].insertCardToHand(card3);
  }

  cardsToPass.clear();
}

// checks to see if a players hand is all hearts.
// takes a vector of cards, ie the player's hand
// returns a bool of whether all the cards are hearts
bool HeartsGame::allhearts(std::vector<Card> h)
{

  for (size_t i = 0; i < h.size(); ++i)
  {
    if (h[i].getSuit() != HEARTS)
    {
      return false;
    }
  }
  return true;
}

// compares hand against the lead suit
// Takes in a suit and the player's hand
// returns a bool whether there is a card with suit s
// in the hand
bool HeartsGame::noLeadSuit(Suit s, std::vector<Card> h)
{
  for (size_t i = 0; i < h.size(); ++i)
  {
    if (h[i].getSuit() == s)
    {
      return false;
    }
  }
  return true;
}

// checks to see if a move is valid
// takes index of player in vector, the proposed card,
// the trick number, and the turn number
// returns a bool of whether the card is a valid move
bool HeartsGame::validateMove(int index, Card move, int numTrick, int turn)
{
  Suit lead;
  if (centerPile.size() > 0) lead = centerPile[0].getSuit();
  if (turn == 0)
  {
    if (centerPile.size() == 0)
    {
      if (move.getSuit() != CLUBS && move.getValue() != TWO)
        return false;
      else
        return true;
    }
    else
    {
      if (move.getSuit() != lead && noLeadSuit(lead, players[index].getHand()))
      {
        if (move.getSuit() == HEARTS && brokenHearts)
          return true;
        else if (move.getSuit() == HEARTS &&
                 allhearts(players[index].getHand()))
        {
          brokenHearts = true;
          return true;
        }
        else if (move.getSuit() == HEARTS)
          return false;
        else
          return true;
      }
      else if (move.getSuit() != lead)
        return false;
      else
        return true;
    }
  }
  else
  {
    if (centerPile.size() == 0)
    {
      if (move.getSuit() == HEARTS && allhearts(players[index].getHand()))
      {
        brokenHearts = true;
        return true;
      }
      else if (move.getSuit() == HEARTS && brokenHearts)
        return true;
      else if (move.getSuit() == HEARTS)
        return false;
      return true;
    }
    else
    {
      if (move.getSuit() != lead && noLeadSuit(lead, players[index].getHand()))
      {
        if (move.getSuit() == HEARTS && brokenHearts)
          return true;
        else if (move.getSuit() == HEARTS &&
                 allhearts(players[index].getHand()))
        {
          brokenHearts = true;
          return true;
        }
        else if (move.getSuit() == HEARTS)
          return false;
        else
          return true;
      }
      else if (move.getSuit() != lead)
        return false;
      else
        return true;
    }
  }
  return false;
}

// shuffle and deals the cards to the players
// takes in a deck of cards
void HeartsGame::dealCards(std::vector<Card>& Deck)
{

  std::random_device rd;
  std::mt19937 generator(rd());
  std::shuffle(Deck.begin(), Deck.end(), generator);
  for (size_t i = 0; i < players.size(); i++)
  {
    for (auto j = 0; j < 13; j++)
    {
      players[i].insertCardToHand(Deck[(j) + (13 * i)]);
    }
  }
}

// begins the game of hearts
// can be called multiple times to
// play again
void HeartsGame::play_Hearts()
{
  // creates deck of cards
  auto deck = initializeDeck();

  // deals cards and resets round scores to 0
  dealCards(deck);
}

// preps the passing cards
// takes the vector of card indexes and the name of the player
bool HeartsGame::setPassCards(std::vector<Card> cards, std::string name)
{

  for (int i = 0; i < players.size(); i++)
  {
    if (players[i].getName() == name)
    {
      for (int j = cards.size() - 1; j >= 0; j--)
      {
        passCard(cards[j], i);
        if (!players[i].removeCardFromHand(cards[j])) return false;
      }
    }
  }
  return true;
}

// plays a card
// takes the card index value in hand and player's name
// returns -1 if card was invalid else returns the player
// that made the move
int HeartsGame::playCard(Card card, std::string name)
{
  int j = 0;
  for (int i = 0; i < players.size(); i++)
  {
    if (players[i].getName() == name)
    {
      if (!validateMove(i, card, 13 - players[i].getHand().size(), turn))
      {
        return -1;
      }

      players[i].removeCardFromHand(card);
      centerPile.push_back(card);
      j = i;
    }
  }
  turn = (turn + 1) % 4;
  return j;
}

// finished the turn
// takes the index of the current player
// returns the player index who won the trick
int HeartsGame::endTurn(int currentPlayer)
{
  Suit leadSuit = centerPile[0].getSuit();
  int maxIndex = 0;
  int maxValue = 0;
  int score = 0;
  for (int i = 0; i < centerPile.size(); i++)
  {
    Card tmp = centerPile[i];
    if (tmp.getSuit() == leadSuit && tmp.getValue() > maxValue)
    {
      maxValue = tmp.getValue();
      maxIndex = i;
    }
    if (tmp.getSuit() == SPADES && tmp.getValue() == 11) score += 13;
    if (tmp.getSuit() == HEARTS) score++;
  }
  players[(maxIndex + currentPlayer) % players.size()].incrementRoundScore(
    score);
  centerPile.clear();
  return (maxIndex + currentPlayer) % players.size();
}

// finishes the round and applies scores
void HeartsGame::endRound()
{
  for (int i = 0; i < players.size(); i++)
  {
    if (players[i].getRoundScore() == 26)
    {
      players[(i + 1) % 4].setRoundScore(26);
      players[(i + 2) % 4].setRoundScore(26);
      players[(i + 3) % 4].setRoundScore(26);
      break;
    }
  }
  for (int i = 0; i < players.size(); i++)
  {
    players[i].startNewRound();
  }
}

// passes a card
// takes a card and index of player
void HeartsGame::passCard(Card tmp, int i)
{
  cardsToPass[i].push_back(tmp);
}