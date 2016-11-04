#include "HeartsGame.hpp"
#include <iostream>


HeartsGame::HeartsGame(std::vector <Player>& players)
{
	this->players = players;
	std::vector<Card> tmp;
	for (int i = 0; i < 4; i++)
	{
		cardsToPass.push_back(tmp);
	}
}

HeartsGame::~HeartsGame()
{
	
}

std::vector<Card> HeartsGame::initializeDeck() //creates deck of cards taken from Card.cpp

{
	std::vector<Card> deck;
	deck.reserve(52);
	std::vector<Suit> suits = { HEARTS, SPADES, CLUBS, DIAMONDS };
	for (auto && suit : suits) {
		for (int i = 2; i<=14; i++) {
			deck.push_back(Card(suit, (Value)i));
		}
	}
	return deck;
}

std::vector<Player> HeartsGame::creatPlayers(int p)  //Creats a vector of Players to play the game.
{
	std::vector<Player> players;
	players.reserve(p);

	/*for (auto i = 0; i < p; ++i)
	{
		players.push_back(Player(makename(i)));
		players[i].setScore(0);
	}*/

	return players;

}

int HeartsGame::findTwoOfClubs()  //looks through each hand to find the 2 of clubs
{
	for (size_t i = 0; i < players.size(); ++i)
	{
		std::vector<Card> temp = players[i].getHand();
		for (auto j = 0; j < 13; ++j)
		{
			if (temp[j].getSuit() == Suit::CLUBS && temp[j].getValue() == 2)
			{
				return i;
			}
		}
	}
	return -1;
}

int HeartsGame::fixPass(int r, int p, int c)
{
	if (r == 1) //pass to the Left
	{
		switch (p)
		{
		case 0:  return c + 9;
			break;
		case 1: return c;
			break;
		case 2: return c + 3;
			break;
		case 3: return c + 6;
			break;
		default: return -1;
		}
	}

	if (r == 2) // pass to the Right
	{
		switch (p)
		{
		case 0:  return c + 3;
			break;
		case 1: return c + 6;
			break;
		case 2: return c + 9;
			break;
		case 3: return c;
			break;
		default: return -1;
		}
	}

	if (r == 3) // pass across the Table
	{
		switch (p)
		{
		case 0:  return c + 6;
			break;
		case 1: return c + 9;
			break;
		case 2: return c;
			break;
		case 3: return c + 3;
			break;
		default: return -1;
		}
	}
	return -1;
}

void HeartsGame::passCards(int round)  //function for passing cards at beginging of round
{
		for (size_t i = 0; i < players.size(); i++)
		{
			Card card1 = cardsToPass[(i+round+1)%players.size()][0];
			Card card2 = cardsToPass[(i + round + 1) % players.size()][1];
			Card card3 = cardsToPass[(i + round + 1) % players.size()][2];
			players[i].insertCardToHand(card1);
			players[i].insertCardToHand(card2);
			players[i].insertCardToHand(card3);
		}

		cardsToPass.clear();
}

int HeartsGame::scoretrick(std::vector<Card>& center, std::vector<Player>& players, int& turn)
{
	int winner = turn;
	Suit lead = center[0].getSuit();
	int high = center[0].getValue();
	int score = 0;
	for (size_t i = 0; i < center.size(); ++i)
	{
		if (center[i].getSuit() == HEARTS) { ++score; }
		if ((center[i].getSuit() == lead) && (center[i].getValue() > high)) { winner = (turn + i) % 4;  high = center[i].getValue(); }
		if ((center[i].getSuit() == lead) && (center[i].getValue() == 1)) { winner = (turn + i) % 4; high = 14; }  //aces are high but its not a value in our cards
		if ((center[i].getSuit() == SPADES) && (center[i].getValue() == 12)) { score = score + 13; high = center[i].getValue(); }
	}

	//players[winner].setroundScore((players[winner].getroundScore()) + score);
	return winner;
}

bool HeartsGame::allhearts(std::vector<Card> h)  //checks to see if a players hand is all hearts.
{

	for (size_t i = 0; i < h.size(); ++i)
	{
		if (h[i].getSuit() != HEARTS)
		{
			return false;
		}
	}
	return true;
}

bool HeartsGame::noLeadSuit(Suit s, std::vector<Card> h)  //compares hand against the lead suit
{
	for (size_t i = 0; i < h.size(); ++i)
	{
		if (h[i].getSuit() == s)
		{
			return false;
		}
	}
	return true;
}

bool HeartsGame::validateMove(int index, Card move, int numTrick, int turn)
{
	Suit lead;
	if (centerPile.size() > 0) lead = centerPile[0].getSuit();
	if (turn == 0)
	{
		if (centerPile.size() == 0)
		{
			if (move.getSuit() != CLUBS && move.getValue() != TWO) return false;
			else return true;
		}
		else
		{
			if (move.getSuit() != lead && noLeadSuit(lead, players[index].getHand()))
			{
				if (move.getSuit() == HEARTS && brokenHearts) return true;
				else if (move.getSuit() == HEARTS && allhearts(players[index].getHand()))
				{
					brokenHearts = true;
					return true;
				}
				else if (move.getSuit() == HEARTS) return false;
				else return true;
			}
			else if (move.getSuit() != lead) return false;
			else return true;
		}
	}
	else
	{
		if (centerPile.size() == 0)
		{
			if (move.getSuit() == HEARTS && allhearts(players[index].getHand()))
			{
				brokenHearts = true;
				return true;
			}
			else if (move.getSuit() == HEARTS && brokenHearts)
				return true;
			else if (move.getSuit() == HEARTS)
				return false;
			return true;
		}
		else
		{
			if (move.getSuit() != lead && noLeadSuit(lead, players[index].getHand()))
			{
				if (move.getSuit() == HEARTS && brokenHearts) return true;
				else if (move.getSuit() == HEARTS && allhearts(players[index].getHand()))
				{
					brokenHearts = true;
					return true;
				}
				else if (move.getSuit() == HEARTS) return false;
				else return true;
			}
			else if (move.getSuit() != lead) return false;
			else return true;
		}
	}
	/*
	if (i != 0 && centerPile.size() > 0) { lead = centerPile[0].getSuit(); }//sets the lead suit
	if (t == 1 && move.getSuit() == HEARTS) { return false; }//cannot play hearts in first round
	if ((t == 1 && move.getSuit() == SPADES) && (move.getValue() == 12)) { return false; }//cannot play queen of spades in first round
	if ((t == 1 && i == 0) && (move.getSuit() != CLUBS && move.getValue() != 2)) { return false; }//must play 2 of clubs at the first of each round
	if ((i == 0 && move.getSuit() == CLUBS) && (move.getValue() == 2)) { return true; }
	if (i == 0 && allhearts(players[index].getHand())) { true; return true; }  //if player only has hearts hearts are broken and move is valid
	if (i == 0 && brokenHearts) { return true; }  //can play any card on first move once hearts are broken
	if (i != 0 && move.getSuit() == lead) { return true; }//if you play the same suit as lead it is valid
	if (i == 0 && move.getSuit() != HEARTS) { return true; } //can play anything but hearts to start
	if (i != 0 && move.getSuit() != lead)
	{
		if (noLeadSuit(lead, players[index].getHand()) && move.getSuit() == HEARTS) { brokenHearts = true;  return true; }
		else if (noLeadSuit(lead, players[index].getHand())) { return true; }
		else return false;*/

	//} //if no lead suit any play is valid, if valid play is hearts hearts is broken

	//else { return false; }
	return false;
}

void HeartsGame::dealCards(std::vector<Player>& players, std::vector<Card>& Deck)
{

	std::random_device rd;
	std::mt19937 generator(rd());
	std::shuffle(Deck.begin(), Deck.end(), generator);
	for (size_t i = 0; i < players.size(); i++)
	{
		for (auto j = 0; j < 13; j++)
		{
			players[i].insertCardToHand(Deck[(j)+(13 * i)]);

		}
	}
	/*for (int i = 0; i < players.size(); i++)
	{
		std::sort(players[i].getHand().begin(), players[i].getHand().end());
	}*/
}

void HeartsGame::play_Hearts()
{
	auto deck = initializeDeck();  //creates deck of cards

	dealCards(players, deck);  //deals cards and resets round scores to 0
}

void HeartsGame::setPassCards(std::vector<int> cards, std::string name)
{

	for (int i = 0; i < players.size(); i++)
	{
		if (players[i].getName() == name)
		{
			for (int j = cards.size() - 1; j >= 0; j--)
			{
				Card tmp = players[i].getHand()[cards[j]-1];
				passCard(tmp, i);
				if(players[i].removeCardFromHand(tmp)) std::cout << "yes" << std::endl;
			}			
		}
	}
}

int HeartsGame::playCard(std::string values, std::string name)
{
	int j = 0;
	for (int i = 0; i < players.size(); i++)
	{
		if (players[i].getName() == name)
		{
			Card tmp = players[i].getHand()[atoi(values.data())-1];
			if (!validateMove(i, tmp, 13 - players[i].getHand().size(), turn))
			{
				return -1;
			}
			
			players[i].removeCardFromHand(tmp);
			centerPile.push_back(tmp);
			j = i;
		}
	}
	turn++;
	if (turn > 3) turn = 0;
	return j;
}

int HeartsGame::endTurn(int currentPlayer)
{
	Suit leadSuit = centerPile[0].getSuit();
	int maxIndex = 0;
	int maxValue = 0;
	int score = 0;
	for (int i = 0; i < centerPile.size(); i++)
	{
		Card tmp = centerPile[i];
		if (tmp.getSuit() == leadSuit && tmp.getValue() > maxValue)
		{
			maxValue = tmp.getValue();
			maxIndex = i;
		}
		if (tmp.getSuit() == SPADES && tmp.getValue() == 11) score += 13;
		if (tmp.getSuit() == HEARTS) score++;
	}
	players[(maxIndex+currentPlayer)%players.size()].incrementRoundScore(score);
	centerPile.clear();
	return (maxIndex+currentPlayer)%players.size();
}

void HeartsGame::endRound()
{
	for (int i = 0; i < players.size(); i++)
	{
		if (players[i].getRoundScore() == 26)
		{
			players[(i + 1) % 4].setRoundScore(26);
			players[(i + 2) % 4].setRoundScore(26);
			players[(i + 3) % 4].setRoundScore(26);
			break;
		}
	}
	for (int i = 0; i < players.size(); i++)
	{
		players[i].startNewRound();
	}
}

void HeartsGame::passCard(Card tmp, int i)
{
	cardsToPass[i].push_back(tmp);
}