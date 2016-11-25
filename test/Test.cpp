/*This file is where all unit testing will be going. All you need to do
 *is include the appropriate header files and then perform your test.
 */

#define BOOST_TEST_MODULE const string test;

// Project Includes
#include "../source/PlayerAPI/Card.hpp"
#include "../source/PlayerAPI/Player.hpp"
#include "source\GameLogic\HeartsGame.hpp"


// Standard Includes
#include <sstream>

// Boost Includes
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/access.hpp>
#include <boost/test/unit_test.hpp>
#include <boost\asio\io_service.hpp>

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
  BOOST_CHECK_EQUAL(player.getOverallScores().empty() , 1);
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

BOOST_AUTO_TEST_CASE(heartsGameInitialization)
{
  boost::asio::io_service service;
  std::vector<Player> players;
  for (int i = 0; i < 4; i++)
  {
    Player newPlayer(i, TCPConnection::create(service));
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
      if (game.getPlayers()[i].getHand()[j] == twoOfClubs)
        playerWithTwoOfClubs = i;
    }
  }
  BOOST_CHECK_EQUAL(game.findTwoOfClubs(), playerWithTwoOfClubs);
}

// int findTwoOfClubs();
BOOST_AUTO_TEST_CASE(heartsGamefindTwoOfClubs)
{
  boost::asio::io_service service;
  std::vector<Player> players;
  for (int i = 0; i < 4; i++)
  {
    Player newPlayer(i, TCPConnection::create(service));
    players.push_back(newPlayer);
  }
  HeartsGame game(players);
  game.play_Hearts();

  for (size_t i = 0; i < players.size(); ++i)
  {
    std::vector<Card> temp = players[i].getHand();
    for (auto j = 0; j < temp.size(); ++j)
    {
      if (temp[j].getSuit() == Suit::CLUBS && temp[j].getValue() == 2)
      {
        BOOST_CHECK(game.findTwoOfClubs() == i);
        return;
      }
    }
  }
}

// bool setPassCards(std::vector<Card> cards, std::string name);
BOOST_AUTO_TEST_CASE(heartsGameSetPassCards)
{
  boost::asio::io_service service;
  Card aceofSpades = Card(SPADES, ACE);
  Card threeOfHearts(HEARTS, THREE);
  Card kingOfClubs(CLUBS, KING);
  std::vector<Player> players;

  for (int i = 0; i < 4; i++)
  {
    Player newPlayer(i, TCPConnection::create(service));
    players.push_back(newPlayer);
  }
  std::vector<Card> v;
  v.push_back(aceofSpades);
  v.push_back(threeOfHearts);
  v.push_back(kingOfClubs);
  HeartsGame game(players);

  BOOST_CHECK(game.setPassCards(v, "abc") == true);
}

// int playCard(Card card, std::string name);
BOOST_AUTO_TEST_CASE(heartsGamePlayCard)
{
  boost::asio::io_service service;
  std::vector<Player> players;
  for (int i = 0; i < 4; i++)
  {
    Player newPlayer(i, TCPConnection::create(service));
    players.push_back(newPlayer);
  }
  HeartsGame game(players);
  Card twoOfClubs(CLUBS, TWO);
  game.play_Hearts();

  BOOST_CHECK(game.playCard(twoOfClubs, "0") == 0);
}

// EOF
