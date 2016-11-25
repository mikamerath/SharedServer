/*
* The Player Class holds information about each player in the game.
* Further details about what each function does are outlined above the
* respective function in the Card.cpp file.
*
* Many of the functions in this class will need to be written by the Player
* Networking group.
*
* -Ligia Frangello and Katie Sweet
*
*/
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "source\NetworkInterface\TCPConnection.hpp"
#include "Card.hpp"
#include <functional>
#include <string>
#include <vector>

class Player
{
private:
  int id;
  std::string ip;
  std::string name;

  std::vector<Card> hand;
  int roundScore;                // Hearts
  std::vector<int> overallScore; // Everyone
  int bid;                       // Spades
  int bags;                      // Spades
  int tricksWon;                 // Spades
  std::function<void(Suit)> validateSuit;
  std::function<void(Card)> validateMove;
  std::function<void(int)> validateBid;

public:
  TCPConnection::pointer connection;

  Player(int id, TCPConnection::pointer connection);

  void setName(std::string);
  std::string getName() const;
  int getId();

  void setValidateSuit(std::function<void(Suit)>);
  void setValidateMove(std::function<void(Card)>);
  void setValidateBid(std::function<void(int)>);

  // The functions below reset the necessary variables at the start of
  // round/game.
  void startNewRound();
  void startNewGame();

  // The functions below allow for communication from the server to the client.
  void requestMove(); // Everyone
  void requestBid();  // Spades
  void requestSuit(); // Crazy 8's
  void updateGameStatus(/*coded message of state*/);

  // The functions below are callback functions for server/client communication.
  std::vector<Card> receivedMove();
  int receivedBid();
  Suit receivedSuit();

  // The functions below allow for the management of a player's hand.
  void initializeHand(std::vector<Card>& deck, unsigned int numCards);
  void insertCardToHand(const Card&);
  bool removeCardFromHand(const Card&);
  std::vector<Card> getHand() const;

  // The functions below allow for the management of a player's score.
  int getRoundScore() const;
  void setRoundScore(int);
  void incrementRoundScore(int);
  std::vector<int> getOverallScores() const;
  int getTotalScore() const;

  // The functions below are for use in the game Spades.
  int getBid() const;
  void setBid(int);
  int getBags() const;
  void setBags(int);
  int getTricksWon() const;
  void setTricksWon(int);
  void incrementTricksWon();

  // Make player comparable for BOOST_CHECK_EQUAL
  friend bool operator==(const Player& p1, const Player& p2);
  friend std::ostream& operator<<(std::ostream& out, const Player& p);
};

#endif
