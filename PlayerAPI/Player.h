/*
* Player Class
*
* -Ligia Frangello and Katie Sweet
*
*/

class Player{
    std::vector<Card> hand;
    int bid;
    int ip;
    int port; 
    int score;

    Player(int ip, int port);
    // If server does function calls (pull fashion)
    std::vector<Card> requestCardsPassed();
    std::vector<Card> requestMove();
    std::vector<Card> requestMove(Card c); //If they draw in Crazy 8's
    int requestBid();

    void startGame(std::vector<Cards>);
    //void updateField(Field f);
    bool endTheRound(scores); //returns true if ready for next round
    void endTheGame(scores);

    std::vector<Card> getHand( return hand);
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
