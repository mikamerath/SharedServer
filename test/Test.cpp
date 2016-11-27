/*This file is where all unit testing will be going. All you need to do
 *is include the appropriate header files and then perform your test.
 */

#define BOOST_TEST_MODULE const string test;

// Project Includes
#include "../source/PlayerAPI/Card.hpp"
#include "../source/PlayerAPI/Player.hpp"
#include "../source/SpadesLogic/SpadesLogic.hpp"

// Standard Includes
#include <sstream>
#include <vector>

// Boost Includes
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/access.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(startNewRound)
{
  Player player(1, "100");
  player.setRoundScore(10);
  player.setBid(5);
  player.setTricksWon(1);
  player.startNewRound();
  BOOST_CHECK_EQUAL(player.getRoundScore(), 0);
  BOOST_CHECK_EQUAL(player.getBid(), 0);
  BOOST_CHECK_EQUAL(player.getTricksWon(), 0);
  BOOST_CHECK_EQUAL(player.getOverallScores().size(), 1);
}

BOOST_AUTO_TEST_CASE(startNewGame)
{
  Player player(1, "100");
  player.setRoundScore(10);
  player.setBid(5);
  player.setBags(2);
  player.setTricksWon(1);
  player.startNewGame();
  BOOST_CHECK_EQUAL(player.getRoundScore(), 0);
  BOOST_CHECK_EQUAL(player.getBid(), 0);
  BOOST_CHECK_EQUAL(player.getBags(), 0);
  BOOST_CHECK_EQUAL(player.getTricksWon(), 0);
  BOOST_CHECK_EQUAL(player.getOverallScores().empty() , 1);
}

BOOST_AUTO_TEST_CASE(insertCardToHand)
{
  Player player(1, "100");
  Card card(HEARTS, TWO);
  player.insertCardToHand(card);
  BOOST_CHECK_EQUAL(player.getHand().size(), 1);
}

BOOST_AUTO_TEST_CASE(removeCardFromHand)
{
  Player player(1, "100");
  Card card(HEARTS, TWO);
  player.insertCardToHand(card);
  BOOST_CHECK_EQUAL(player.removeCardFromHand(card), 1);
  BOOST_CHECK_EQUAL(player.removeCardFromHand(card), 0);
}

BOOST_AUTO_TEST_CASE(SerializeCard)
{
  std::stringstream serialize;
  Card serializeCard(CLUBS, ACE);
  boost::archive::text_oarchive oArchive(serialize);
  oArchive << serializeCard;

  Card deserializeCard;
  std::stringstream deserialize(serialize.str());
  boost::archive::text_iarchive iArchive(deserialize);
  iArchive >> deserializeCard;

  BOOST_CHECK_EQUAL(deserializeCard.getSuit(), CLUBS);
  BOOST_CHECK_EQUAL(deserializeCard.getValue(), ACE);
}

BOOST_AUTO_TEST_CASE(SpadesConstructor) {
 Player one(1, "192.168.0.0");
 Player two(2, "192.168.0.1");
 Player three(3, "192.168.0.1");
 Player four(4, "192.168.0.1");
 std::vector<Player> testPlayers;
 testPlayers.push_back(one);
 testPlayers.push_back(two);
 testPlayers.push_back(three);
 testPlayers.push_back(four);
 Spades testSpades(testPlayers);
 for (int i = 0; i < 4; i++) {
  BOOST_CHECK_EQUAL(testPlayers.at(i).getId(), testSpades.getPlayers().at(i).getId());
 }
	
}

BOOST_AUTO_TEST_CASE(SpadesTrickWinner) {
 Player one(1, "192.168.0.0");
 Player two(2, "192.168.0.1");
 Player three(3, "192.168.0.1");
 Player four(4, "192.168.0.1");
 std::vector<Player> p;
 p.push_back(one);
 p.push_back(two);
 p.push_back(three);
 p.push_back(four);
 Spades s(p);
 
 for (int i = 2; i < 15; i++) {
  Card cardOne(SPADES, (Value)i);
  Card cardTwo(HEARTS, (Value)i);
  Card cardThree(CLUBS, (Value)i);
  Card cardFour(DIAMONDS, (Value)i);
  std::vector<Card> testTrick;
  testTrick.push_back(cardOne);
  testTrick.push_back(cardTwo);
  testTrick.push_back(cardThree);
  testTrick.push_back(cardFour);
  BOOST_CHECK_EQUAL(s.getTrickWinner(testTrick, 0), 0);
 }
 for (int j = 0; j < 4; j++) {
  for (int i = 2; i < 12; i++) {
   Card cardOne((Suit)j, (Value)(i + 3));
   Card cardTwo((Suit)j, (Value)(i + 2));
   Card cardThree((Suit)j, (Value)(i + 1));
   Card cardFour((Suit)j, (Value)i);
   std::vector<Card> testTrick;
   testTrick.push_back(cardOne);
   testTrick.push_back(cardTwo);
   testTrick.push_back(cardThree);
   testTrick.push_back(cardFour);
   BOOST_CHECK_EQUAL(s.getTrickWinner(testTrick, 0), 0);
  }
 }
}


// EOF
