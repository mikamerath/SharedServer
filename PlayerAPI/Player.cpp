/*
* This file holds the function definitions for the Player class.
*
* Above each function is a short description of what each function does. If
* there are any questions, please do not hesitate to contact Katie Sweet or
* Ligia Frangello.
*
* -Ligia Frangello and Katie Sweet
*/

#include "Player.hpp"

// Constructor for the Player class. Takes in the IP address of the client.
Player::Player(std::string ipAddress)
  : ip(ipAddress), roundScore(0), bid(0), bags(0), tricksWon(0)
{
}

// Requests from client which cards they want to pass and returns their choice.
std::vector<Card> Player::requestCardsPassed()
{
  std::vector<Card> c;
  // NEEDS TO BE FILLED IN BY PLAYER NETWORKING GROUP
  return c;
}

// Requests a move from client and returns their choice.
std::vector<Card> Player::requestMove()
{
  std::vector<Card> c;
  // NEEDS TO BE FILLED IN BY PLAYER NETWORKING GROUP
  return c;
}

// Requests a bid from client and returns their choice.
void Player::requestBid()
{
  // NEEDS TO BE FILLED IN BY PLAYER NETWORKING GROUP
}

// Sends client an updated game status.
void Player::updateGameStatus()
{
  // NEEDS TO BE FILLED IN BY PLAYER NETWORKING GROUP
}

// Sends client information about end of round, including overallScore, etc.
void Player::alertClientEndOfRound()
{
  // NEEDS TO BE FILLED IN BY PLAYER NETWORKING GROUP
}

// Sends client information about end of game.
void Player::alertClientEndOfGame()
{
  // NEEDS TO BE FILLED IN BY PLAYER NETWORKING GROUP
}

// Function called at the end of a round. Updates the overallScore vector with
// the roundScore, alerts the client of the change in game status, then clears
// the scores and bids to get ready for the next round.
void Player::endTheRound()
{
  overallScore.push_back(roundScore);
  alertClientEndOfRound();
  roundScore = 0;
  bid = 0;
}

// Function called at the end of a game. Updates the overallScore vector with
// the roundScore, alerts the client of the change in game status, then clears
// the game dependent variables to get ready the next game.
void Player::endTheGame()
{
  overallScore.push_back(roundScore);
  alertClientEndOfGame();
  roundScore = 0;
  bid = 0;
  bags = 0;
  tricksWon = 0;
  overallScore.clear();
}

// Inserts card into the hand. The hand will not be sorted, unless necessary.
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

// Initializes a players hand with the 'numCards' specified.
// The deck must be passed in so that the cards can be removed from the deck
// when added to the player's hand.
void Player::initializeHand(std::vector<Card>& deck, unsigned int numCards)
{
  hand.clear();
  for (unsigned int i = 0; i < numCards; i++)
  {
    hand.push_back(deck.back());
    deck.pop_back();
  }
}

// Returns a vector of Cards that matches the Player's hand.
std::vector<Card> Player::getHand() const
{
  return hand;
}

// Returns a players score the current round.
int Player::getRoundScore() const
{
  return roundScore;
}

// Allows for a players round score to be sent. Anticipated to be unnecessary
// since the round score will be set to 0 automatically when endTheRound()
// is called, and the incrementRoundScore function below will allow for an
// increase in the round score after a particular trick finishes.
void Player::setRoundScore(int i)
{
  roundScore = i;
}

// Allows for a players round score to be increased by the integer specified.
// For use in games like Hearts where a player's round score may be updated
// multiple times in one round (i.e. after a trick is assigned).
void Player::incrementRoundScore(int i)
{
  roundScore += i;
}

// Returns a vector of scores for each player. Each entry in the vector
// corresponds to the player's score in a different round within the game.
std::vector<int> Player::getOverallScores() const
{
  return overallScore;
}

// Gets the value that a player bid (Spades).
int Player::getBid() const
{
  return bid;
}

// Gets the number of bags a player had (Spades).
int Player::getBags() const
{
  return bags;
}

// Sets the number of bags a player had (Spades).
void Player::setBags(int b)
{
  bags = b;
}

// Gets the number of tricks a player has won in a round (Spades).
int Player::getTricksWon() const
{
  return tricksWon;
}

// Sets the number of tricks a player has won in a round (Spades).
void Player::setTricksWon(int t)
{
  tricksWon = t;
}

// Increments the number of tricks a player has won in a round (Spades).
// Allows for the number of tricks won to be updated after every trick.
void Player::incrementTricksWon()
{
  tricksWon++;
}
