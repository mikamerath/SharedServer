#include "Player.hpp"

Player::Player(std::string ipAddress)
{
  ip = ipAddress;
  roundScore = 0;
  bid = 0;
  bags = 0;
  tricksWon = 0;
}

// NEEDS TO BE FILLED IN BY PLAYER NETWORKING GROUP
std::vector<Card> Player::requestCardsPassed()
{
  std::vector<Card> c;
  // Requests from client which cards they want to pass
  // Return their choice
  return c;
}

// NEEDS TO BE FILLED IN BY PLAYER NETWORKING GROUP
std::vector<Card> Player::requestMove()
{
  std::vector<Card> c;
  // Requests a move from client
  // Returns their move
  return c;
}

// NEEDS TO BE FILLED IN BY PLAYER NETWORKING GROUP
void Player::requestBid()
{
  bid = 0;
  // Requests a bid from client
  // Returns their bid
}

// NEEDS TO BE FILLED IN BY PLAYER NETWORKING GROUP
void Player::updateGameStatus()
{
  // Sends client an updated game status
}

// NEEDS TO BE FILLED IN BY PLAYER NETWORKING GROUP
void Player::alertClientEndOfRound()
{
  // Sends client information about end of round,
  // including overallScore, etc.
}

// NEEDS TO BE FILLED IN BY PLAYER NETWORKING GROUP
void Player::alertClientEndOfGame()
{
  // Sends client information about end of game.
}

void Player::endTheRound()
{
  overallScore.push_back(roundScore);
  alertClientEndOfRound();
  roundScore = 0;
  bid = 0;
}

void Player::endTheGame()
{
  overallScore.push_back(roundScore);
  alertClientEndOfGame();
  roundScore = 0;
  bid = 0;
  bags = 0;
  tricksWon = 0;
}

// Inserts card into the hand.
// The hand will not be sorted, unless necessary.
void Player::insertCardToHand(const Card& c)
{
  hand.push_back(c);
}

// Attempts to remove card from hand. If card is in hand, it will be removed
// and the function will return true. If the card is not in the hand, it will
// return false and no cards will be removed.
bool Player::removeCardFromHand(const Card& c)
{
  for (auto&& card : hand)
  {
    if (card == c)
    {
      std::swap(card, hand[hand.size() - 1]);
      hand.pop_back();
      return true;
    }
  }
  return false;
}

void Player::initializeHand(std::vector<Card>& deck, unsigned int numCards)
{
  for (unsigned int i = 0; i < numCards; i++)
  {
    hand.push_back(deck.back());
    deck.pop_back();
  }
}
