#include "CrazyEightsLogic.hpp"
#include <iostream>

CrazyEightsLogic::CrazyEightsLogic(std::vector<std::shared_ptr<Player>>& netPlayers)
{
  players = netPlayers;
  for (auto && player: players){
      player->setValidateMove([this](Card c){validCard(c);});
      player->setValidateSuit([this](Suit s){validateSuit(s);});
  }
  deck = initializeDeck();
  deal(5);
  turn = 0;
  cardsDrawnCounter = 0;
  start();
}

void CrazyEightsLogic::start()
{
  UpdateGameStateMessage();
  players = getPlayers();
  players[turn]->requestMove();
}

void CrazyEightsLogic::deal(int numCards)
{
  for (int i = 0; i < players.size(); i++)
  {
    players.at(i)->initializeHand(deck, numCards);
  }
  discardPile.push_back(deck.back());
  deck.pop_back();
}

bool CrazyEightsLogic::isGameOver()
{
  if (players.at(turn)->getHand().size() == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void CrazyEightsLogic::gameOver(std::vector<std::shared_ptr<Player>>& players)
{
  s = GAME_OVER;
  // score for players
  int winningPlayerScore = calculateScore(players);

  for (int i = 0; i < players.size(); i++)
  {
    if (getTurn() == i)
    {
      players[i]->setRoundScore(winningPlayerScore);
    }
    else
    {
      players[i]->setRoundScore(0);
    }
  }

  UpdateGameStateMessage();
}

// refills the deck when empty
void CrazyEightsLogic::refillDeck()
{
  Card card = getDiscardPile().back();
  discardPile.pop_back();
  deck = discardPile;
  std::random_device rd;
  std::mt19937 random(rd());
  std::shuffle(deck.begin(), deck.end(), random);
  discardPile.clear();
  discardPile.push_back(card);
}

// validates whether or not a card is valid
void CrazyEightsLogic::validCard(Card card)
{
  if (card.getSuit() == UNDEFINED)
  {
    if (!getDiscardPile().empty())
    {
      drawCard();
    }
    else
    {
      refillDeck();
      drawCard();
    }
  }
  else
  {
    Card topDiscard = discardPile.back();
    bool isInHand = false;
    bool isValidMove = false;
    std::vector<std::shared_ptr<Player>> players = getPlayers();
    std::vector<Card> playerHand = players[getTurn()]->getHand();

    // Check to see if card is in hand
    for (int i = 0; i < playerHand.size(); i++)
    {
      if (card == playerHand.at(i))
      {
        isInHand = true;
      }
    }

    if (topDiscard.getValue() == 8)
    {
      if (card.getSuit() == currentSuit)
      {
        isValidMove = true;
      }
    }
    else
    {
      if (topDiscard.getSuit() == card.getSuit())
      {
        isValidMove = true;
      }
    }

    if (topDiscard.getValue() == card.getValue() || card.getValue() == 8)
    {
      isValidMove = true;
    }

    if (isValidMove && isInHand)
    {
      playCard(card);
      if (isGameOver())
      {
        players = getPlayers();
        gameOver(players);
      }
      else
      {
        if (card.getValue() == EIGHT)
        {
          players[getTurn()]->requestSuit();
        }
        else
        {
          nextTurn();
        }
      }
    }
    else
    {
      players[getTurn()]->requestMove();
    }
  }
}

void CrazyEightsLogic::displayHand(std::vector<Card> hand)
{
  for (int i = 0; i < hand.size(); i++)
  {
    std::string suit = convertSuitToString(hand.at(i).getSuit());
    std::string rank = convertRankToString(hand.at(i).getValue());
    std::cout << "Player Card " << i << ": " << rank << " of " << suit
              << std::endl;
  }
}

int CrazyEightsLogic::getTurn()
{
  return turn;
}
/**
*
* validateSuit is used for Networking
*
**/

void CrazyEightsLogic::validateSuit(Suit s)
{
  currentSuit = s;
  nextTurn();
}

/**
*
*  playCard is used for networking
*
*/
void CrazyEightsLogic::playCard(Card& card)
{
  discardPile.push_back(card);
  players.at(turn)->removeCardFromHand(card);
}

void CrazyEightsLogic::drawCard()
{
  players.at(turn)->insertCardToHand(deck.back());
  deck.pop_back();
  UpdateGameStateMessage();
  players[turn]->requestMove();
}

void CrazyEightsLogic::nextTurn()
{
  turn = (turn + 1) % players.size();
  UpdateGameStateMessage();
  players[turn]->requestMove();
}

void CrazyEightsLogic::setCardsDrawnCounter(int numDrawn)
{
  cardsDrawnCounter = numDrawn;
}

int CrazyEightsLogic::getCardsDrawnCounter()
{
  return cardsDrawnCounter;
}

int CrazyEightsLogic::calculateScore(std::vector<std::shared_ptr<Player>> players)
{
  int totalScore = 0;
  std::vector<Card> playerHand;

  for (int i = 0; i < players.size(); i++)
  {
    playerHand = players.at(i)->getHand();

    for (int j = 0; j < playerHand.size(); j++)
    {
      totalScore += getCardScoreValue(playerHand.at(j));
    }
  }
  return totalScore;
}

int CrazyEightsLogic::getCardScoreValue(Card card)
{
  Value value = card.getValue();

  switch (value)
  {
  case 2:
    return 2;
  case 3:
    return 3;
  case 4:
    return 4;
  case 5:
    return 5;
  case 6:
    return 6;
  case 7:
    return 7;
  case 8:
    return 50;
  case 9:
    return 9;
  case 10:
    return 10;
  case 11:
    return 10;
  case 12:
    return 10;
  case 13:
    return 10;
  case 14:
    return 1;
  default:
    return 0;
  }
}

std::string CrazyEightsLogic::convertSuitToString(Suit suit)
{
  std::string cardSuit;
  switch (suit)
  {
  case Suit::HEARTS:
    cardSuit = "Hearts";
    break;
  case Suit::SPADES:
    cardSuit = "Spades";
    break;
  case Suit::CLUBS:
    cardSuit = "Clubs";
    break;
  case Suit::DIAMONDS:
    cardSuit = "Diamonds";
    break;
  case Suit::UNDEFINED:
  default:
    cardSuit = "Undefined";
    break;
  }
  return cardSuit;
}

std::string CrazyEightsLogic::convertRankToString(Value value)
{
  std::string rank;

  switch (value)
  {
  case 2:
    rank = "2";
    break;
  case 3:
    rank = "3";
    break;
  case 4:
    rank = "4";
    break;
  case 5:
    rank = "5";
    break;
  case 6:
    rank = "6";
    break;
  case 7:
    rank = "7";
    break;
  case 8:
    rank = "8";
    break;
  case 9:
    rank = "9";
    break;
  case 10:
    rank = "10";
    break;
  case 11:
    rank = "Jack";
    break;
  case 12:
    rank = "Queen";
    break;
  case 13:
    rank = "King";
    break;
  case 14:
    rank = "Ace";
    break;
  default:
    rank = "Undefined";
    break;
  }
  return rank;
}
