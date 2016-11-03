/*
 * This is me thinking through what I'm going to need in a player class.
 *
#include"card.cpp"
#include<vector>

#include "card.cpp"

class player {
public:
  std::vector<card> getHand();       // This will be necessary for determining valid moves.
  void give(card); // For the deal/passing/drawing etc
  void setValidMoves(std::vector<card>); // game logic gives this to the player.
  card getMove();                        // to make a move
  void passCards(player, std::vector<card>); // something like this will be
                                             // necessary for hearts/spade
  void pass(); // Not sure how crazy eights will handle passing maybe we do need
               // an empty card object or something.
  int getScore();
  void setScore(int); // appended or replaced.

private:
  std::vector<card> hand; // I like this method as opposed to a deck we split between players.
  std::vector<card> validMoves; // where valid moves will be stored for comparison.
  int handSize;   // unnecessary as hand.size() works, but might be useful.
  int score;
}
*/

/*
* Player Class
*
* -Ligia Frangello and Katie Sweet
*
*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <memory>
#include <random>

class Player{
  private:
    int id;//This could be helpful.
    std::vector<Card> hand;
    std::string ip;
    int roundScore; // Hearts
    std::vector<int> overallScore; // Everyone
    int bid; //Spades
    int bags; // Spades
    int tricksWon = 0; // Spades
    int score;
    
  public:
    Player(){}
    Player(std::string playerIp, int playerId)
    {
	ip = playerIp; 
	id = playerId; 
	
    }
    void giveCard(Card c){
     hand.push_back(c);
    }
    
    // If server does function calls (pull fashion)
    std::vector<Card> requestCardsPassed(); //Hearts
    std::vector<Card> requestMove(){
     int index;
     std::cout << "Here are your cards Player " << id << std::endl;
     int i = 0;
     for(auto&& c: hand){
      std::cout << i << ": "; 
      c.print();
      i++;
     }
	 if (id == 0){
     		std::cout << "give me a move:";
		 std::cin >> index;
		 index = index % hand.size();
		 
	 }
	 else{
		 std::random_device rd;
		 std::mt19937 g(rd());
		 index = g() % hand.size();
	 }
     std::vector<Card> move;
     move.push_back(hand.at(index));
     //std::sort(hand.begin(), hand.end());
     //hand.pop_back();
     hand.erase(hand.begin() + index);
     return move;
    } // Everyone
    int requestBid(){
     std::cout << "Here are your cards" << std::endl;
     int i = 0;
     for(auto&& c: hand){
      std::cout << i << "."; 
      c.print();
      i++;
     }
     int b;
     std::cout << "bid:";
     std::cin >> b;
     return b;
    } // Spades
    void setBid(int b){bid = b;}
    int getBid(){return bid;}
    void setId(int i){id = i;}
    int getId(){return id;}
    void augTricksWon(){
	tricksWon++;
    }
    int getTricksWon(){return tricksWon;}
    void setBags(int b){bags = b;}
    int getBags(){return bags;}
    void addBag(){bags++;}
    void setScore(int s){score = s;}
    int getScore(){return score;}

    //void updateGameStatus(coded message of state); //takes message from Game and adds hand to it
    //void endTheRound(coded message of state); //returns true if ready for next round
    //void endTheGame(coded message of state); 

    std::vector<Card> getHand(){return hand;}
    void setHand(std::vector<Card> h){hand = h;}
};
#endif
