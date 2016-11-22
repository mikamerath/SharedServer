/*This file is where all unit testing will be going. All you need to do
 *is include the appropriate header files and then perform your test.
 */

#define BOOST_TEST_MODULE const string test;

// Boost Includes
#include <boost/test/unit_test.hpp>

#include "source\HeartsLogic\HeartsGame.hpp"
#include "source\PlayerAPI\Player.hpp"

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

//int findTwoOfClubs();
BOOST_AUTO_TEST_CASE(heartsGamefindTwoOfClubs){
    
    std::vector<Player> players;
    for (int i = 0; i < 4; i++){
        Player newPlayer(i,"123.123.123." + std::to_string(i));
        players.push_back(newPlayer);
    }
    HeartsGame game(players);
    game.play_Hearts();
    
    for (size_t i = 0; i < players.size(); ++i){
        std::vector<Card> temp = players[i].getHand();
        for (auto j = 0; j < temp.size(); ++j){
            if (temp[j].getSuit() == Suit::CLUBS && temp[j].getValue() == 2){
                BOOST_CHECK(game.findTwoOfClubs() == i);
                return;
            }
        }
    }
}

//bool setPassCards(std::vector<Card> cards, std::string name);
BOOST_AUTO_TEST_CASE(heartsGameSetPassCards){
    Card aceofSpades = Card(SPADES, ACE);
    Card threeOfHearts(HEARTS, THREE);
    Card kingOfClubs(CLUBS, KING);
    std::vector<Player> players;
    
    for (int i = 0; i < 4; i++){
        Player newPlayer(i,"123.123.123." + std::to_string(i));
        players.push_back(newPlayer);
    }
    std::vector<Card> v;
    v.push_back(aceofSpades);
    v.push_back(threeOfHearts);
    v.push_back(kingOfClubs);
    HeartsGame game(players);
    
    BOOST_CHECK(game.setPassCards(v, "abc") == true);
}

//int playCard(Card card, std::string name);
BOOST_AUTO_TEST_CASE(heartsGamePlayCard){
    std::vector<Player> players;
    for (int i = 0; i < 4; i++){
        Player newPlayer(i,"123.123.123." + std::to_string(i));
        players.push_back(newPlayer);
    }
    HeartsGame game(players);
    Card twoOfClubs(CLUBS, TWO);
    game.play_Hearts();
    
    BOOST_CHECK(game.playCard(twoOfClubs, "0") == 0);
}


//int endTurn(int currentPlayer);
BOOST_AUTO_TEST_CASE(heartsGameEndTurn){
    
}
//EOF
