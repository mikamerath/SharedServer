/*This file is where all unit testing will be going. All you need to do
 *is include the appropriate header files and then perform your test.
 */

#define BOOST_TEST_MODULE const string test;

// Project Includes

#include "source/PlayerAPI/Card.hpp"
#include "source/PlayerAPI/Player.hpp"
#include "source/Lobby.hpp"
#include "source/Messages/GameMessage.hpp"
 #include "../source/GameLogic/SpadesLogic.hpp"
 #include "../source/PlayerAPI/Card.hpp"
 #include "../source/PlayerAPI/Player.hpp"
#include "source/NetworkInterface/ClientNetworkInterface.hpp"
#include "source/NetworkInterface/ServerNetworkInterface.hpp"

// Standard Includes
#include <sstream>
#include <vector>
#include <fstream>

// Boost Includes
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>
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


BOOST_AUTO_TEST_CASE(SerializeMessage)
{
	std::stringstream serialize;
	std::vector<Card> cards;
	cards.push_back(Card(CLUBS, TWO));
	cards.push_back(Card(HEARTS, ACE));
	std::vector<int> hands;
	hands.push_back(5);
	hands.push_back(9);
	GameMessage serializeMessage(PASSING, false, cards, hands, cards, true);
	boost::archive::text_oarchive oArchive(serialize);
	oArchive << serializeMessage;

	GameMessage deserializeMessage;
	std::stringstream deserialize(serialize.str());
	boost::archive::text_iarchive iArchive(deserialize);
	iArchive >> deserializeMessage;

	BOOST_CHECK_EQUAL(deserializeMessage.s, PASSING);
	BOOST_CHECK_EQUAL(deserializeMessage.turn, false);
	BOOST_CHECK_EQUAL(deserializeMessage.field.at(0).getSuit(), CLUBS);
	BOOST_CHECK_EQUAL(deserializeMessage.field.at(1).getValue(), ACE);
	BOOST_CHECK_EQUAL(deserializeMessage.handSizes.at(0), 5);
	BOOST_CHECK_EQUAL(deserializeMessage.handSizes.at(1), 9);
	BOOST_CHECK_EQUAL(deserializeMessage.playerHand.at(1).getSuit(), HEARTS);
	BOOST_CHECK_EQUAL(deserializeMessage.playerHand.at(0).getValue(), TWO);
	BOOST_CHECK_EQUAL(deserializeMessage.deckEmpty, true);
}

BOOST_AUTO_TEST_CASE(Login)
{
	boost::asio::io_service service;
	boost::asio::io_service clientService;
	Lobby lobby2 = Lobby();
	ClientNetworkInterface* NI = new ClientNetworkInterface(5555, clientService, std::cout);
	ServerNetworkInterface NI1(12000, service, std::cout, boost::bind(&Lobby::addPlayer, lobby2, _1));
	NI1.startAccepting();
	std::ofstream fout;
	fout.open("database.txt");
	fout << "USERS" << std::endl;
	fout << "testuser" << std::endl;
	fout << "testpassword" << std::endl;
	fout.close();
	Lobby lobby = Lobby();
	std::shared_ptr<Player> player(new Player(1, TCPConnection::create(service)));
	player->setName("testuser");
	NI->connect("127.0.0.1", 12000);
	std::shared_ptr<Player> player2(new Player(2, TCPConnection::create(service)));
	lobby.procLogin(player2, "LOGIN testuser testpassword");
	BOOST_CHECK_EQUAL(player->getName(), player2->getName());
}

BOOST_AUTO_TEST_CASE(SpadesGetNextPlayer)
{
  Spades s;
  for (int i = 0; i < 4; i++)
  {
    BOOST_CHECK_EQUAL(s.getNextPlayer(i), ((i + 1) % 4));
  }
}
