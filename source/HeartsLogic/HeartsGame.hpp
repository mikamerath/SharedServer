#ifndef HEARTS_GAME_HPP
#define HEARTS_GAME_HPP

#include "Player.hpp"
#include <boost/asio.hpp>
#include <random>

class HeartsGame
{
public:
	HeartsGame(std::vector<Player> &players);
	~HeartsGame();
	void play_Hearts();
	

//private:

	std::vector<Card> initializeDeck();
	std::vector<Player> creatPlayers(int p);  //Creats a vector of Players to play the game.
	void dealCards(std::vector<Player>& players, std::vector<Card>& Deck);
	int findTwoOfClubs();  //looks through each hand to find the 2 of clubs
	int fixPass(int r, int p, int c);
	void passCards(int round);  //function for passing cards at beginging of round
	int scoretrick(std::vector<Card>& center, std::vector<Player>& players, int& turn);
	bool allhearts(std::vector<Card> h);  //checks to see if a players hand is all hearts.
	bool noLeadSuit(Suit s, std::vector<Card> h);  //compares hand against the lead suit
	bool validateMove(int index, Card move, int t, int i);
	std::vector<Player> players;
	std::vector<Card> centerPile;
	void setPassCards(std::vector<int> cards, std::string name);
	int playCard(std::string values, std::string name);
	bool brokenHearts = false;
	int endTurn(int currentPlayer);
	void endRound();
	int turn = 0;
	std::vector<std::vector<Card>> cardsToPass;
	void passCard(Card tmp, int i);
};

#endif //HEARTS_GAME_HPP