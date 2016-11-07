#include "Game.hpp"
//#include"Player.hpp"
//#include<random>
//#include<algorithm>
#include <iostream>
#include <vector>
//#include<unistd.h>

class Spades : public Game
{
public:
  void setDeck();
  void printPlayerHands();
  void start();
  void getBids();
  void beginRound(int);
  void startTrick();
  bool validMove(std::vector<Card>, int, Suit&, int);
  void getTrickWinner(std::vector<Card>, int&);
  int getNextPlayer(int);
  void score();
  void recordMove(std::vector<Card>);
  Spades(std::vector<Player>);
  ~Spades() {}
private:
  int starter;
  bool spadesBroken;
};

int Spades::getNextPlayer(int plId)
{
  if (plId == 3)
  {
    return 0;
  }
  else
  {
    return ++plId;
  }
}

int next(int plId)
{
  if (plId == 3)
  {
    return 0;
  }
  else
  {
    return ++plId;
  }
}

void printBoard(std::vector<Card> trick, std::vector<Card> hand, int turn)
{
  int posZero = turn;
  int posOne = next(turn);
  int posTwo = next(posOne);
  int posThree = next(posTwo);
  std::cout << "..........................................Player " << posTwo
            << "...........................\n";
  std::cout << "..............................................................."
               "..............\n";
  std::cout
    << ".Player " << posOne
    << "....................................................................\n";
  std::cout << "..............................................................."
               "..............\n";
  std::cout << "..............................................................."
               "..............\n";
  for (auto c : trick)
  {
    //c.tablePrint();
  }
  std::cout << "..............................................................."
               "..............\n";
  std::cout << "..............................................................."
               "..............\n";
  std::cout << "..............................................................."
               ".....player "
            << posThree << ".\n";
  std::cout << "..............................................................."
               "..............\n";
  std::cout << "..................Player " << turn
            << "...................................................\n";
}

Spades::Spades(std::vector<Player> p)
{
  players = p;
  start();
}

void Spades::getBids()
{
  for (auto&& p : players)
  {
    p.requestBid();
  }
}

void Spades::recordMove(std::vector<Card> m)
{
  // essentially update field, then setup and send message to clients.
  //m.at(0).print();
}

void Spades::getTrickWinner(std::vector<Card> trick, int& tw)
{

  // holy hell it cannot possibly be as difficult as it feels to determine the
  // winner of this thing.
  auto prevTw = tw;
  auto currentPlayer = tw;
  auto winningCard = trick.at(0);
  for (int i = 1; i < 4; i++)
  {
    currentPlayer = getNextPlayer(currentPlayer); // look at next player
    if (trick.at(i).getSuit() == winningCard.getSuit())
    { // same suit?
      if (trick.at(i).getValue() > winningCard.getValue())
      {                            // compare value
        winningCard = trick.at(i); // replace if greater value
        tw = currentPlayer;
      }
    }
    else if (trick.at(i).getSuit() == SPADES)
    {
      if (winningCard.getSuit() == SPADES)
      {
        if (trick.at(i).getValue() > winningCard.getValue())
        {
          winningCard = trick.at(i);
          tw = currentPlayer;
        }
      }
      else
      {
        winningCard = trick.at(i);
        tw = currentPlayer;
      }
    }
  }
}

bool Spades::validMove(std::vector<Card> tr, int pl, Suit& ls, int currentTurn)
{ // I'd like this to make sure of two things, one: validity of the move, and
  // two: the winner of the trick(thus far).
  auto h = players.at(pl).getHand();
  if (tr.at(0).getSuit() == tr.back().getSuit() &&
      tr.at(0).getValue() == tr.back().getValue())
  { // If this is the first card played in the trick
    if (tr.back().getSuit() == SPADES)
    { // If it's spades, spades has to be broken first
      if (spadesBroken == true)
      {
        ls = SPADES;
        return true;
      }
      else
      { // If spades isn't broken, you can only play spades if that is all you
        // have. (For the first move.)
        for (auto c : h)
        {
          if (c.getSuit() != SPADES)
          {
            return false;
          }
        }
      }
    }
    else
    { // It is the first move, and the lead suit is not spades
      ls = (Suit)tr.back().getSuit();
      //tr.back().print();
      std::cout << "tr.back() was led" << std::endl;
    }
  }
  if (tr.back().getSuit() == ls)
  {
    return true;
  }
  // first thing, check the hand, if the player has any card of lead suit, he
  // can't make the move he is trying to.
  for (auto c : h)
  {
    if (c.getSuit() == ls)
    {
      return false;
    }
  }
  // at this point, two things are true, the card played was NOT of the suit
  // led, and the player does NOT have any cards of the led suit.
  if (tr.back().getSuit() == SPADES)
  {
    spadesBroken = true;
  }
  return true;
}

void Spades::score()
{
  for (auto p : players)
  {
    auto bid = p.getBid();
    auto tricks = p.getTricksWon();
    auto bag = p.getBags();
    if (bid == tricks)
    {
      p.setRoundScore(bid * 10);
    }
    else if (bid < tricks)
    {
      int sc = bid * 10;
      for (int b = bid; b < tricks; b++)
      {
        sc++;
      }
      p.setRoundScore(sc);
    }
    else if (bid > tricks)
    {
      p.setRoundScore(0);
    }
    std::cout << "p.getId() + p.getRoundScore() " << p.getId() << ":"
              << p.getRoundScore() << std::endl;
  }
}

void Spades::beginRound(int starter)
{ // a more accurate title might be "playRound()" the round logic is this
  // function
  Suit ledSuit = HEARTS;
  // player 0 starts the round
  std::vector<Card> trick;
  int trickWinner = 0;
  int turn = 0;
  while (s == PLAYING)
  {
    // s = ROUND_OVER;

    for (int i = 0; i < 4; i++)
    {

      trick.push_back(players.at(turn).requestMove());
      if (validMove(trick, turn, ledSuit, i))
      {
        std::vector<Card> m;
        m.push_back(trick.at(i));
      }
      else
      {
        bool vm = false;
        while (vm == false)
        {
          std::cout << "Invalid Move!!!" << std::endl;
          std::cout << std::endl;
          // std::cout << "Trick: " << std::endl;
          auto sendBack = trick.back();
          trick.pop_back();
          // for(auto c : trick){
          //	c.print();
          //}
          players.at(turn).insertCardToHand(sendBack);
          trick.push_back(players.at(turn).requestMove());
          vm = validMove(trick, turn, ledSuit, i);
          if (vm && i == 0)
          {
            ledSuit = (Suit)trick.at(0).getSuit();
          }
        }

        // severe connection to client (you don't want to play with them
        // anyway).
      }
      turn = getNextPlayer(turn);
      if (players.at(turn).getHand().empty())
      {
        s = ROUND_OVER;
      }
      //printBoard(trick, players.at(turn).getHand(), turn); <- These are the three pieces of information that need to be sent to the player.
      std::cout << "Updating Connected Games..."<< std::endl;
      /*std::cout << "Trick: " << std::endl;
      for(auto c : trick){
              c.print();
      }*/
    }
    getTrickWinner(trick, trickWinner);
    std::cout << "Player " << trickWinner << " won the trick." << std::endl;
    players.at(trickWinner).incrementTricksWon();
    std::cout << players.at(trickWinner).getId() << " has won "
              << players.at(trickWinner).getTricksWon() << " tricks."
              << std::endl;
    trick.clear();
    turn = trickWinner;
  }
  score();
  initializeDeck();
  s = BIDDING;
  getBids();
  s = PLAYING;
  spadesBroken = false;
  beginRound(getNextPlayer(starter));
}

void Spades::start()
{
  setDeck();
  players.at(0).initializeHand(deck, 13);
  players.at(1).initializeHand(deck, 13);
  players.at(2).initializeHand(deck, 13);
  players.at(3).initializeHand(deck, 13);
  starter = 0;
  s = BIDDING;
  getBids();
  s = PLAYING;
  spadesBroken = false;
  beginRound(0);
}

void Spades::setDeck()
{
  initializeDeck();
}

void Spades::printPlayerHands()
{
}

int main()
{
  Player one(0, "192.168.0.1");
  Player two(1, "192.168.0.2");
  Player three(2, "192.168.0.3");
  Player four(3, "192.168.0.4");
  std::vector<Player> p;
  p.push_back(one);
  p.push_back(two);
  p.push_back(three);
  p.push_back(four);
  Spades mySpades(p);
  return 0;
} //Working test.
