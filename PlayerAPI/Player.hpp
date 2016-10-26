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

#include "Card.hpp"
#include <string>
#include <vector>

class Player
{
private:
  std::vector<Card> hand;
  std::string ip;
  int roundScore;                // Hearts
  std::vector<int> overallScore; // Everyone
  int bid;                       // Spades
  int bags;                      // Spades
  int tricksWon;                 // Spades

  void alertClientEndOfRound(/*coded message of state*/);
  void alertClientEndOfGame(/*coded message of state*/);

public:
  Player(std::string ipAddress);

  // The functions below allow for communication from the server to the client.
  std::vector<Card> requestCardsPassed(); // Hearts
  std::vector<Card> requestMove();        // Everyone
  void requestBid();                      // Spades
  void updateGameStatus(
    /*coded message of state*/); // takes message from Game and adds hand to it

  // The functions below reset the neccesary variables at the end of game/round.
  // They also alert the client of a change in game status.
  void endTheRound();
  void endTheGame();

  // The functions below allow for the management of a player's hand.
  void initializeHand(std::vector<Card>& deck, unsigned int numCards);
  std::vector<Card> getHand() const;
  void insertCardToHand(const Card&);
  bool removeCardFromHand(const Card&);

  // The functions below allow for the management of a player's score.
  int getRoundScore() const;
  void setRoundScore(int);
  void incrementRoundScore(int);
  std::vector<int> getOverallScores() const;

  // The functions below are for use in the game Spades.
  int getBid() const;
  int getBags() const;
  void setBags(int);
  int getTricksWon() const;
  void setTricksWon(int);
  void incrementTricksWon();
};
