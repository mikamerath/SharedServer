/*
* The Player Class holds information about each player in the game.
* The functions in this class will need to be written by the Player Networking
* group.
*
* -Ligia Frangello and Katie Sweet
*
*/
#include <string>
#include <vector>

class Player
{
  std::vector<Card> hand;
  std::string ip;
  int roundScore;                // Hearts
  std::vector<int> overallScore; // Everyone
  int bid;                       // Spades
  int bags;                      // Spades
  int tricksWon;                 // Spades

  Player(std::string ip);
  std::vector<Card> requestCardsPassed(); // Hearts
  std::vector<Card> requestMove();        // Everyone
  int requestBid();                       // Spades

  void updateGameStatus(
    /*coded message of state*/); // takes message from Game and adds hand to it
  void endTheRound(/*coded message of state*/);
  void endTheGame(/*coded message of state*/);

  std::vector<Card> getHand(return hand);
  void setHand(std::vector<card>);
}
