/*
 * musings on a game class all games will inherit from this and likely override
 * the functions
 *

enum gameTitle{SPADES, HEARTS, CRAZY_EIGHTS}

class game {
public:
  game(std::vector<player>, gameTitle){}
  game~(){}
  void initializeDeck(); // This puts all of the cards in the deck and shuffles it.
  void deal();      // Something like while(cards in deck) for each player
                    // player.give(card);
  void play();      // The catalyst for actually beginning the game loop.
  void beginRound();
  bool getRoundStatus(); // returns roundIsDone
  bool getGameStatus();  // returns gameIsDone

private:
  std::vector<card> deck;      // game is in charge of the deck
  std::vector<player> players; // game has to know about the players
  bool isPassingRound; // keeps track of whether or not it is a passing round
  bool roundIsDone; // keeps track of whether or not the round is over (probably
                    // unneccessary)
  bool gameIsDone; // keeps track of whether or not the game is over (also
                   // probably unnecessary)
}
*/
#ifndef GAME_HPP
#define GAME_HPP

#include<vector>
#include"card.cpp"
#include"player.hpp"

enum State {PASSING, BIDDING, PLAYING, ROUND_OVER, GAME_OVER};

class Game{
    protected:
        std::vector<Card> deck;
        std::vector<Card> discardPile;
        std::vector<Player> players;
        State s;
        std::vector<Card> field;
        int turn; //index in player vector
    public:
        void start();
	Game(){}
        Game(std::vector<Player> p){
		players = p;
		start();
	}
	~Game(){}
        void initializeDeck();
        void UpdateGameStateMessage(){
          for (auto&& player: players){
              //player.updateGameStatus(coded message)
	      std::cout << "Eventually, a message should be sent here" << std::endl;  
          }
        }
        void deal(int numCards);
	void printPlayerHands();
};

#endif

class Message{
    State s;
    bool turn;
    std::vector<Card> field;
};
