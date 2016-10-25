/*
* The Player Class holds information about each player in the game.
* The functions in this class will need to be written by the Player Networking
* group.
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
  Player(std::string ip);
  std::vector<Card> requestCardsPassed(); // Hearts
  std::vector<Card> requestMove();        // Everyone
  void requestBid();                      // Spades

  void updateGameStatus(
    /*coded message of state*/); // takes message from Game and adds hand to it

  void endTheRound();
  void endTheGame();

  void initializeHand(std::vector<Card>& deck, unsigned int numCards);
  std::vector<Card> getHand() { return hand; };
  void insertCardToHand(const Card&);
  bool removeCardFromHand(const Card&);

  std::string getIp() { return ip; };
  void setIp(std::string s) { ip = s; };

  int getRoundScore() { return roundScore; };
  void setRoundScore(int i) { roundScore = i; };
  void incrementRoundScore(int i) { roundScore += i; };

  // void addRoundScoreToOverallScore() { overallScore.push_back(roundScore); };
  std::vector<int> getOverallScores() { return overallScore; };

  int getBid() { return bid; };
  void setBid(int b) { bid = b; };

  int getBags() { return bags; };
  void setBags(int b) { bags = b; };

  int getTricksWon() { return tricksWon; };
  void setTricksWon(int t) { tricksWon = t; };
  void incrementTricksWon() { tricksWon++; };
};
