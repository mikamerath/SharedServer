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
		Player newPlayer(i,"123.123.123.123");
		players.push_back(newPlayer);
	}
	HeartsGame game(players);
	BOOST_CHECK_EQUAL(game.getPlayers().size(), 4);
	BOOST_CHECK_EQUAL(game.getCenterPile().size(), 0);

}
//EOF