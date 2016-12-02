#include "source/GameLogic/SpadesLogic.hpp"

void SpadesLog(
  int turn, int i, std::vector<Card> hand, std::vector<Card> trick, int id)
{
  std::cout << "Turn: " << turn << std::endl;
  std::cout << "TrickWinner: " << i << std::endl;
  std::cout << "Hand:" << std::endl;
  for (auto&& c : trick)
  {
    if (c.getSuit() == (Suit)SPADES)
    {
      std::cout << "\tSpades:" << c.getValue() << std::endl;
    }
    else if (c.getSuit() == (Suit)HEARTS)
    {
      std::cout << "\tHearts:" << c.getValue() << std::endl;
    }
    else if (c.getSuit() == (Suit)CLUBS)
    {
      std::cout << "\tClubs:" << c.getValue() << std::endl;
    }
    else if (c.getSuit() == (Suit)DIAMONDS)
    {
      std::cout << "\tDiamonds:" << c.getValue() << std::endl;
    }
  }
  std::cout << "Trick: " << std::endl;
  for (auto&& c : trick)
  {
    if (c.getSuit() == (Suit)SPADES)
    {
      std::cout << "\tSpades:" << c.getValue() << std::endl;
    }
    else if (c.getSuit() == (Suit)HEARTS)
    {
      std::cout << "\tHearts:" << c.getValue() << std::endl;
    }
    else if (c.getSuit() == (Suit)CLUBS)
    {
      std::cout << "\tClubs:" << c.getValue() << std::endl;
    }
    else if (c.getSuit() == (Suit)DIAMONDS)
    {
      std::cout << "\tDiamonds:" << c.getValue() << std::endl;
    }
  }
}

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
  if (plId >= 3)
  {
    return 0;
  }
  else
  {
    return ++plId;
  }
}

void Spades::roundOver(){
 s = ROUND_OVER;
 score();
 UpdateGameStateMessage();
}

void Spades::startNewRound()
{
 setDeck();
 for (auto player : players)
 {
  player->initializeHand(deck, 13);
  player->startNewRound();
 }
 if (s != GAME_OVER)
 {
  players.at(turn)->requestBid();
 }
}

void Spades::receiveValidMove(Card c)
{
  players.at(turn)->removeCardFromHand(c);
  trick.push_back(c);
  if (validMove())
  {
    turn = getNextPlayer(turn);
  }
  else
  {
    auto c = trick.back();
    players.at(turn)->insertCardToHand(c);
    trick.pop_back();
  }
  if (trick.size() < 4)
  {
    UpdateGameStateMessage();
    players.at(turn)->requestMove();
  }
  else
  {
    trickWinner = getTrickWinner(trick, trickWinner);
    if (players.at(turn)->getHand().size() < 1)
    {
     roundOver();
     startNewRound(); 
    }
    else
    {
      turn = trickWinner;
      players.at(turn)->incrementTricksWon();
      UpdateGameStateMessage();
      players.at(turn)->requestMove();
    }
  }
}

void Spades::receiveBid(int b)
{
  // do something with bid
  players.at(turn)->setBid(b);
  if (turn < 3)
  {
    turn = getNextPlayer(turn);
    players.at(turn)->requestBid();
  }
  else
  {
    turn = getNextPlayer(turn);
    UpdateGameStateMessage();
    players.at(turn)->requestMove();
  }
}

Spades::Spades(std::vector<std::shared_ptr<Player>> p)
{
  players = p;
  setDeck();
  for (auto&& player : players)
  {
    player->setValidateMove([this](Card c) { receiveValidMove(c); });
    player->setValidateBid([this](int bid) { receiveBid(bid); });
    player->initializeHand(deck, 13);
    player->startNewRound();
  }
  turn = 0;
  players.at(turn)->requestBid();
}

int Spades::getTrickWinner(std::vector<Card> trick, int tw)
{
  auto prevTw = tw;
  auto currentPlayer = tw;
  auto winningCard = trick.at(0);
  for (int i = 1; i < 4; i++)
  {
    currentPlayer = getNextPlayer(currentPlayer);
    if (trick.at(i).getSuit() == winningCard.getSuit())
    {
      if (trick.at(i).getValue() > winningCard.getValue())
      {
        winningCard = trick.at(i);
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
  return tw;
}

bool Spades::validMove()
{
  auto h = players.at(turn)->getHand();
  if (trick.at(0).getSuit() == trick.back().getSuit() &&
      trick.at(0).getValue() == trick.back().getValue())
  {
    if (trick.back().getSuit() == SPADES)
    {
      if (spadesBroken == true)
      {
        ledSuit = SPADES;
        return true;
      }
      else
      {
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
    {
      ledSuit = (Suit)trick.back().getSuit();
      std::cout << "tr.back() was led" << std::endl;
    }
  }
  if (trick.back().getSuit() == ledSuit)
  {
    return true;
  }
  for (auto c : h)
  {
    if (c.getSuit() == ledSuit)
    {
      return false;
    }
  }
  if (trick.back().getSuit() == SPADES)
  {
    spadesBroken = true;
  }
  return true;
}

void Spades::score()
{
  for (auto p : players)
  {
    auto bid = p->getBid();
    auto tricks = p->getTricksWon();
    auto bag = p->getBags();
    if (bid == tricks)
    {
      p->setRoundScore(bid * 10);
    }
    else if (bid < tricks)
    {
      int sc = bid * 10;
      for (int b = bid; b < tricks; b++)
      {
        sc++;
        bag++;
      }
      if (bag > 10)
      {
        p->setRoundScore(sc - 100);
        p->setBags(bag % 10);
      }
      else
      {
        p->setRoundScore(sc);
      }
    }
    else if (bid > tricks)
    {
      p->setRoundScore(0);
    }
    std::cout << "p.getId() + p.getRoundScore() " << p->getId() << ":"
              << p->getRoundScore() << std::endl;
    if (p->getTotalScore() > 100)
    {
      s = GAME_OVER;
      UpdateGameStateMessage();
    }
  }
}

void Spades::setDeck()
{
  initializeDeck();
}
