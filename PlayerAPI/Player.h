/*
* Player Class
*
* -Ligia Frangello and Katie Sweet
*
*/
#include <string>
#include <vector>

class Player{
    std::vector<Card> hand;
    std::string ip;
    int roundScore; // Hearts
    std::vector<int> overallScore; // Everyone
    int bid; //Spades
    int bags; // Spades
    int tricksWon; // Spades

    Player(std::string ip);
    // If server does function calls (pull fashion)
    std::vector<Card> requestCardsPassed(); //Hearts
    std::vector<Card> requestMove(); // Everyone
    int requestBid(); // Spades

    void updateGameStatus(coded message of state); //takes message from Game and adds hand to it
    void endTheRound(coded message of state); //returns true if ready for next round
    void endTheGame(coded message of state); 

    std::vector<Card> getHand( return hand );
    void setHand(std::vector<card>);
}

// In Game Class (Hearts):
//   std::vector<Player> players; (players would be 0 indexed)
//   for (auto&& p: players){
//     p.requestCardsPassed(Field);
//   }
//   players[0].requestMove()
//   for (auto&& p: players){
//     p.updateField(Field);
//   }
