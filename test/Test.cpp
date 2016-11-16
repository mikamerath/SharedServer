/*This file is where all unit testing will be going. All you need to do
 *is include the appropriate header files and then perform your test.
 */

#define BOOST_TEST_MODULE const string test;

// Boost Includes
#include <boost/test/unit_test.hpp>

#include "source\HeartsLogic\HeartsGame.hpp"
#include "source\PlayerAPI\Player.hpp"

BOOST_AUTO_TEST_CASE(cardInitialization)
{
  BOOST_CHECK_EQUAL(0, 0);
  BOOST_CHECK_EQUAL(20, 20);
}

BOOST_AUTO_TEST_CASE(otherTest)
{
  BOOST_CHECK_EQUAL(10, 10);
  BOOST_CHECK_EQUAL(5, 5);
}

BOOST_AUTO_TEST_CASE(heartsGameInitialization)
{
	std::vector<Player> players;
	for (int i = 0; i < 4; i++)
	{
		Player newPlayer(i,"123.123.123." + std::to_string(i));
		players.push_back(newPlayer);
	}
	HeartsGame game(players);
	BOOST_CHECK_EQUAL(game.getPlayers().size(), 4);
	for (int i = 0; i < 4; i++)
		BOOST_CHECK_EQUAL(game.getPlayers()[i].getId(), i);
	BOOST_CHECK_EQUAL(game.getCenterPile().size(), 0);
	game.play_Hearts();
	for (int i = 0; i < 4; i++)
		BOOST_CHECK_EQUAL(game.getPlayers()[i].getHand().size(), 13);
	Card twoOfClubs(CLUBS, TWO);
	int playerWithTwoOfClubs = -1;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < game.getPlayers()[i].getHand().size(); j++)
		{
			if (game.getPlayers()[i].getHand()[j] == twoOfClubs) playerWithTwoOfClubs = i;
		}
	}
	BOOST_CHECK_EQUAL(game.findTwoOfClubs(), playerWithTwoOfClubs);
}

BOOST_AUTO_TEST_CASE(heartsGamefindTwoOfClubs)
{
/*
 * 
 */

}


BOOST_AUTO_TEST_CASE(heartsGamePassCards)
{
/*
 * show that 3 cards are passed to each player
 */

}


BOOST_AUTO_TEST_CASE(heartsGameAllHearts)
{
/*
 * test whether hand of player is all hearts
 */

}

BOOST_AUTO_TEST_CASE(heartsGameNoLeadSuit)
{
/*
 * compare hand against lead suit
 * returns a bool whether there is a card with the suit in it
 */

}


BOOST_AUTO_TEST_CASE(heartsGameValidateMove)
{
/*
 * test whether card is valid 
 * 	right suit
 *
 */

}


BOOST_AUTO_TEST_CASE(heartsGameDealCards)
{


}

BOOST_AUTO_TEST_CASE(heartsGamePlayHearts)
{

}

BOOST_AUTO_TEST_CASE(heartsGameSetPassCards)
{

}

BOOST_AUTO_TEST_CASE(heartsGamePlayCard)
{

}

BOOST_AUTO_TEST_CASE(heartsGameEndTurn)
{

}

BOOST_AUTO_TEST_CASE(heartsGameEndRound)
{

}

BOOST_AUTO_TEST_CASE(heartsGamePassCard)
{

}

//EOF