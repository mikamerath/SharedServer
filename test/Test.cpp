/*This file is where all unit testing will be going. All you need to do
 *is include the appropriate header files and then perform your test.
 */

#define BOOST_TEST_MODULE const string test;

// Project Includes
#include "../source/GameLogic/SpadesLogic.hpp"
#include "../source/PlayerAPI/Card.hpp"
#include "../source/PlayerAPI/Player.hpp"

// Standard Includes
#include <sstream>
#include <vector>

// Boost Includes
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/serialization/access.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(startNewRound)
{
  boost::asio::io_service service;
  Player player(1, TCPConnection::create(service));
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
  boost::asio::io_service service;
  Player player(1, TCPConnection::create(service));
  player.setRoundScore(10);
  player.setBid(5);
  player.setBags(2);
  player.setTricksWon(1);
  player.startNewGame();
  BOOST_CHECK_EQUAL(player.getRoundScore(), 0);
  BOOST_CHECK_EQUAL(player.getBid(), 0);
  BOOST_CHECK_EQUAL(player.getBags(), 0);
  BOOST_CHECK_EQUAL(player.getTricksWon(), 0);
  BOOST_CHECK_EQUAL(player.getOverallScores().empty(), 1);
}

BOOST_AUTO_TEST_CASE(insertCardToHand)
{
  boost::asio::io_service service;
  Player player(1, TCPConnection::create(service));
  Card card(HEARTS, TWO);
  player.insertCardToHand(card);
  BOOST_CHECK_EQUAL(player.getHand().size(), 1);
}

BOOST_AUTO_TEST_CASE(removeCardFromHand)
{
  boost::asio::io_service service;
  Player player(1, TCPConnection::create(service));
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

BOOST_AUTO_TEST_CASE(SpadesGetNextPlayer)
{
  Spades s;
  for (int i = 0; i < 4; i++)
  {
    BOOST_CHECK_EQUAL(s.getNextPlayer(i), ((i + 1) % 4));
  }
}

//This first part tests all cases where an ace  of any suit is played
//Player 0 should always win the trick for the sake of this test
//I feel this is sufficient for cases where the hand is all of the same suit.
BOOST_AUTO_TEST_CASE(SpadesTrickWinnerTestSameSuit) {
	for (int j = 0; j < 4; j++) {
		std::vector<Card> trick;
		Card highCard((Suit)j, (Value)14);
		int tw = 0;
		trick.push_back(highCard);
		for (int i = 2; i < 6; i++) {
			Card c((Suit)j, (Value)i);
			trick.push_back(c);
		}
		Spades s;
		auto winner = s.getTrickWinner(trick, tw);
		BOOST_CHECK_EQUAL(winner, 0);
		trick.clear();

		trick.push_back(highCard);
		for (int i = 6; i < 10; i++) {
			Card c((Suit)j, (Value)i);
			trick.push_back(c);
		}
		winner = s.getTrickWinner(trick, tw);
		BOOST_CHECK_EQUAL(winner, 0);
		trick.clear();
		
		trick.push_back(highCard);
		for (int i = 10; i < 14; i++) {
			Card c((Suit)j, (Value)i);
			trick.push_back(c);
		}
		winner = s.getTrickWinner(trick, tw);
		BOOST_CHECK_EQUAL(winner, 0);
	}
}

//This makes sure that the lead suit (if not trumped by spades) wins. ~SPADES equals 1~
//Once again though not logically airtight, this should be enough to demonstrate that 
//if a card is led, and the other cards are neither that same suit nor spades, the led card wins.
BOOST_AUTO_TEST_CASE(SpadesTrickWinnerTestNotSpades) {
	std::vector<Card> trick;
	Card ledCard((Suit)0, (Value)2);
	int tw = 0;
	trick.push_back(ledCard);
	for (int i = 2; i < 6; i++) {
		Card c((Suit)2, (Value)i);
		trick.push_back(c);
	}
	Spades s;
	auto winner = s.getTrickWinner(trick, tw);
	BOOST_CHECK_EQUAL(0, winner);
	trick.clear();
	winner = 0;

	tw = 0;
	trick.push_back(ledCard);
	for (int i = 2; i < 6; i++) {
		Card c((Suit)3, (Value)i);
		trick.push_back(c);
	}
	winner = s.getTrickWinner(trick, tw);
	BOOST_CHECK_EQUAL(0, winner);
}

//This test demonstrates that the dinkiest spade trumps the highest cards of other suits.
BOOST_AUTO_TEST_CASE(SpadesTrickWinnerTestTrumpedBySpades) {
	std::vector<Card> trick;
	int tw = 0;
	Card trump((Suit)1, (Value)2);
	trick.push_back(trump);
	for (int i = 11; i < 14; i++) {
		Card c((Suit)0, (Value)i);
		trick.push_back(c);
	}
	Spades s;
	auto winner = s.getTrickWinner(trick, tw);
	BOOST_CHECK_EQUAL(0, winner);
	trick.clear();
	winner = 0;

	tw = 0;
	trick.push_back(trump);
	for (int i = 11; i < 14; i++) {
		Card c((Suit)2, (Value)i);
		trick.push_back(c);
	}
	winner = s.getTrickWinner(trick, tw);
	BOOST_CHECK_EQUAL(0, winner);
	trick.clear();
	winner = 0;

	tw = 0;
	trick.push_back(trump);
	for (int i = 11; i < 14; i++) {
		Card c((Suit)3, (Value)i);
		trick.push_back(c);
	}
	winner = s.getTrickWinner(trick, tw);
	BOOST_CHECK_EQUAL(0, winner);
	trick.clear();
	winner = 0;
}
