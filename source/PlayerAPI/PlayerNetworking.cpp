#include "Player.hpp"
#include "../NetworkInterface/NetworkInterface.hpp"
/*
* The functions in this file deal with the networking for the player.
* All of these functions are defined within the Player.hpp file.
*
* Each of these functions need to be filled in by the PlayerNetworking group.
*/


// Constructs and sends a message to ask for a move from the client.
void Player::requestMove()
{
	//still not sure how these functions should be called, will fix later
	GeneralMessage message; //(your turn, please make move, etc...)(However the message will be coded)
	sendMessage(this, message, receivedMove()); //
	beginRecieve();
}

// Constructs and sends a message to ask for a bid from the client. (Spades)
void Player::requestBid()
{
	//still not sure how these functions should be called, will fix later
	GeneralMessage message; //message requesting a bid
	sendMessage(this, message, receivedBid());
	beginRecieve();
}

// Constructs and sends a message to ask for a suit from the client. (Eights)
void Player::requestSuit()
{
	//still not sure how these functions should be called, will fix later
	GeneralMessage message; //message requesting a suit
	sendMessage(this, message, receivedSuit());
	beginRecieve();
}

// Called from within the game. Sends the client a message with all of the
// information about the game state (including field information).
// This function appends the hand of the Player onto the message and sends
// it to the client.
void Player::updateGameStatus(/* Message m*/)
{
	//still not sure how these functions should be called, will fix later
	GeneralMessage message; //message containing the game state and the player's hand, to be added later
	sendMessage(this, message, /*callback function? */);
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
  int b = 0;
  return b;
}

// This is the callback function for requestSuit.
Suit Player::receivedSuit()
{
  Suit s = HEARTS;
  return s;
}
