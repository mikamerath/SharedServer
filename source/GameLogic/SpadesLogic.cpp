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
  if (plId == 3)
  {
    return 0;
  }
  else
  {
    return ++plId;
  }
}

void Spades::receiveValidMove(Card c)
{
  movePlaceHolder = c;
  waitingForMove = false;
  // the return card is coming here!!
}

void Spades::receiveBid(int b)
{
  // do something with bid
  bidPlaceHolder = b;
  waitingForBid = false;
  // How do I figure which player gave it to me?
}

Spades::Spades(std::vector<std::shared_ptr<Player>> p)
{
  players = p;
  for (auto&& player : players)
  {
    player->setValidateMove([this](Card c) { receiveValidMove(c); });
    player->setValidateBid([this](int bid) { receiveBid(bid); });
  }
}

void Spades::getBids()
{
  for (auto&& p : players)
  {
    p->setValidateBid([this](int b) { receiveBid(b); });
    waitingForBid = true;
    p->requestBid();
    while (waitingForBid)
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(400));
    }
    p->setBid(bidPlaceHolder);
  }
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

bool Spades::validMove(std::vector<Card> tr,
                       int pl,
                       Suit& leadSuit,
                       int currentTurn)
{
  auto h = players.at(pl)->getHand();
  if (tr.at(0).getSuit() == tr.back().getSuit() &&
      tr.at(0).getValue() == tr.back().getValue())
  {
    if (tr.back().getSuit() == SPADES)
    {
      if (spadesBroken == true)
      {
        leadSuit = SPADES;
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
      leadSuit = (Suit)tr.back().getSuit();
      std::cout << "tr.back() was led" << std::endl;
    }
  }
  if (tr.back().getSuit() == leadSuit)
  {
    return true;
  }
  for (auto c : h)
  {
    if (c.getSuit() == leadSuit)
    {
      return false;
    }
  }
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
      }
						p->setRoundScore(sc);
    }
    else if (bid > tricks)
    {
						for (int bags = tricks; bags < bid; bags++)
						{
							bag++;
						}
						if (bag > 10) {
							p->setRoundScore(-100);
							p->setBags(bag % 10);
						}
						else
						{
							p->setRoundScore(0);
						}
    }
    std::cout << "p.getId() + p.getRoundScore() " << p->getId() << ":"
              << p->getRoundScore() << std::endl;
  }
}

void Spades::validMoveFailLoop(bool vm,
                               std::vector<Card>& trick,
                               Suit ledSuit,
                               int& i)
{
  while (vm == false)
  {
    std::cout << "Invalid Move!!!" << std::endl;
    std::cout << std::endl;
    auto sendBack = trick.back();
    trick.pop_back();
    players.at(turn)->insertCardToHand(sendBack);
    waitingForMove = true;
    players.at(turn)->requestMove();
    while (waitingForMove)
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(400));
    }
    trick.push_back(movePlaceHolder);
    vm = validMove(trick, turn, ledSuit, i);
    if (vm && i == 0)
    {
      ledSuit = (Suit)trick.at(0).getSuit();
    }
  }
}

void Spades::beginTrick(std::vector<Card> trick, Suit ledSuit, int trickWinner)
{
  for (int i = 0; i < 4; i++)
  {
    waitingForMove = true;
    players.at(turn)->requestMove();
    while (waitingForMove)
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(400));
    }
    trick.push_back(movePlaceHolder);
    if (validMove(trick, turn, ledSuit, i))
    {
      std::vector<Card> m;
      m.push_back(trick.at(i));
    }
    else
    {
      bool vm = false;
      validMoveFailLoop(vm, trick, ledSuit, i);
    }
    turn = getNextPlayer(turn);
    if (players.at(turn)->getHand().empty())
    {
      s = ROUND_OVER;
    }
    std::cout << "Updating Connected Games..." << std::endl;
  }
  trickWinner = getTrickWinner(trick, trickWinner);
  players.at(trickWinner)->incrementTricksWon();
  SpadesLog(turn,
            trickWinner,
            trick,
            players.at(turn)->getHand(),
            players.at(turn)->getId());
  trick.clear();
  turn = trickWinner;
}

void Spades::beginRound(int starter)
{
  Suit ledSuit = HEARTS;
  std::vector<Card> trick;
  int trickWinner = 0;
  int turn = 0;
  while (s == PLAYING)
  {
    beginTrick(trick, ledSuit, trickWinner);
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
  players.at(0)->initializeHand(deck, 13);
  players.at(1)->initializeHand(deck, 13);
  players.at(2)->initializeHand(deck, 13);
  players.at(3)->initializeHand(deck, 13);
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
