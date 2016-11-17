#include "source/PlayerAPI/Player.hpp"
/*
* The functions in this file deal with the networking for the player.
* All of these functions are defined within the Player.hpp file.
*
* Each of these functions need to be filled in by the PlayerNetworking group.
*/

// Constructs and sends a message to ask for a move from the client.
void Player::requestMove()
{
}

// Constructs and sends a message to ask for a bid from the client. (Spades)
void Player::requestBid()
{
}

// Called from within the game. Sends the client a message with all of the
// information about the game state (including field information).
// This function appends the hand of the Player onto the message and sends
// it to the client.
void Player::updateGameStatus(/* Message m*/)
{
}

// This is the callback function for requestMove.
std::vector<Card> Player::receivedMove()
{
  std::vector<Card> c;
  return c;
}

// This is the callback function for requestBid.
int Player::receivedBid()
{
  // CALL validateBid();
  int b = 0;
  return b;
}

// Constructs and sends a message to ask for a suit from the client. (Eights)
void Player::requestSuit()
{
  // CALL validateSuit();
}

// This is the callback function for requestSuit.
Suit Player::receivedSuit()
{
  // CALL validateSuit();
  Suit s = HEARTS;
  return s;
}
