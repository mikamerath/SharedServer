#ifndef SPADESLOGIC_HPP
#define SPADESLOGIC_HPP

#include "source/PlayerAPI/Game.hpp"
#include <vector>
#include <iostream>

class Spades : public Game
{
public:
	void setDeck();
	void start();
	void getBids();
	void beginRound(int);
	void beginTrick(std::vector<Card>, Suit, int);
	bool validMove(std::vector<Card>, int, Suit&, int);
	void validMoveFailLoop(bool, std::vector<Card>&, Suit, int&);
	int getTrickWinner(std::vector<Card>, int);
	int getNextPlayer(int);
	void score();
	Spades(std::vector<std::shared_ptr<Player>>);
	~Spades() {}
private:
	int starter;
	bool spadesBroken;
};
#endif
