#include "CrazyEightsLogic.hpp"
#include <iostream>

CrazyEightsLogic::CrazyEightsLogic(std::vector<Player>& netPlayers)
{
  players = netPlayers;
  for (auto && player: players){
   player.setValidateMove([this](Card c){isValidCard(c);});
   player.setValidateSuit([this](Suit s){validateSuit(s);}); 
 }
  deck = initializeDeck();
  deal(5);
  turn = 0;
  cardsDrawnCounter = 0;
}

void CrazyEightsLogic::playGame()
{
  players = getPlayers();

  bool done = false;
  auto cardIndex = 0;

  while (!done)
  {
    std::cout << "Player " << getTurn() + 1 << " your turn!" << std::endl;
    std::vector<Card> playerCards = players[getTurn()].getHand();

    displayHand(players[getTurn()].getHand());

    std::cout << "Discard pile has "
              << convertRankToString(getDiscardPile().back().getValue())
              << " of "
              << convertSuitToString(getDiscardPile().back().getSuit())
              << std::endl;
    std::cout << "Pick a card to play or enter negative number to draw: ";
    std::cin >> cardIndex;
    std::cout << std::endl;
    // players[turn].requestMove();  // request move function instead of stuff above

    bool isPlayerTurn = true;

    while (isPlayerTurn)
    {
      if (cardIndex < 0)
      {
        if (getCardsDrawnCounter() > 2)
        {
          std::cout
            << "You have drawn the max number of cards! Your turn is over!"
            << std::endl;
          isPlayerTurn = false;
          setCardsDrawnCounter(0);
          nextTurn();
          players = getPlayers();
        }
        else
        {
          std::cout << "You drew a card from the deck!" << std::endl;
          drawCard();
          std::cout << "Here is your hand: " << std::endl;
          players = getPlayers();
          playerCards = players[getTurn()].getHand();
          displayHand(playerCards);
          setCardsDrawnCounter(getCardsDrawnCounter() + 1);
          std::cout << "Discard pile has "
                    << convertRankToString(getDiscardPile().back().getValue())
                    << " of "
                    << convertSuitToString(getDiscardPile().back().getSuit())
                    << std::endl;
          std::cout
            << "Pick a card to play or enter a negative number to draw: ";
          std::cin >> cardIndex;
        }
      }
      else if (cardIndex >= 0 && isValidCard(playerCards[cardIndex]))
      {
        std::cout << "Player " << getTurn() + 1 << " played "
                  << convertRankToString(playerCards[cardIndex].getValue())
                  << " of "
                  << convertSuitToString(playerCards[cardIndex].getSuit())
                  << std::endl;

        playCard(playerCards[cardIndex]);
        if (isGameOver())
        {
          std::cout << "Game Over" << std::endl;
          std::cout << "Player " << getTurn() + 1 << " Wins!" << std::endl;
          std::cout << "Player " << getTurn() + 1 << " scored "
                    << calculateScore(getPlayers()) << " points this round."
                    << std::endl;
          isPlayerTurn = false;
          done = true;
        }
        else
        {
          nextTurn();
          players = getPlayers();
          playerCards = players[getTurn()].getHand();
          isPlayerTurn = false;
        }
      }
      else
      {
        std::cout << "Card Index: " << cardIndex
                  << " Card: " << playerCards[cardIndex].getSuit() << ", "
                  << playerCards[cardIndex].getValue() << std::endl;
        std::cout << "Invalid card!" << std::endl;
        std::cout << "Pick a card to play or enter negative number to draw: ";
        std::cin >> cardIndex;
        players = getPlayers();
      }
    }

    std::cout << std::endl;
  }
}

void CrazyEightsLogic::deal(int numCards)
{
  for (int i = 0; i < players.size(); i++)
  {
    players[i].initializeHand(deck, numCards);
  }
  discardPile.push_back(deck.back());
  deck.pop_back();
}

bool CrazyEightsLogic::isGameOver()
{
  if (players[turn].getHand().size() == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool CrazyEightsLogic::isValidCard(Card card)
{
  Card topDiscard = discardPile.back();
  bool isInHand = false;
  bool isValidPlay = false;
  Player currentPlayer = players[turn];
  std::vector<Card> playerHand = currentPlayer.getHand();

  // Check to see if card is in hand
  for (int i = 0; i < playerHand.size(); i++)
  {
    if (card == playerHand[i])
    {
      isInHand = true;
    }
  }

  if (!isInHand)
  {
    displayHand(playerHand);
  }

  if (topDiscard.getValue() == 8)
  {
    if (card.getSuit() == currentSuit)
    {
      isValidPlay = true;
    }
  }
  else
  {
    if (topDiscard.getSuit() == card.getSuit())
    {
      isValidPlay = true;
    }
  }

  if (topDiscard.getValue() == card.getValue() || card.getValue() == 8)
  {
    isValidPlay = true;
  }

  if (isValidPlay && isInHand)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void CrazyEightsLogic::displayHand(std::vector<Card> hand)
{
  for (int i = 0; i < hand.size(); i++)
  {
    std::string suit = convertSuitToString(hand[i].getSuit());
    std::string rank = convertRankToString(hand[i].getValue());
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

// bool CrazyEightsLogic::validateSuit()
// {
//   int turn = getTurn();
//   std::vector<Player> players = getPlayers();
//   Suit selection = players[turn].receivedSuit();
//
//   if (selection < 1 || selection > 4)
//   {
//     std::cout << "Invalid selection.  Select a suit: " << std::endl;
//     std::cout << "1 - Hearts" << std::endl;
//     std::cout << "2 - Spades" << std::endl;
//     std::cout << "3 - Clubs" << std::endl;
//     std::cout << "4 - Diamonds" << std::endl;
//     players[turn].requestSuit();
//   }
//  else {
//     UpdateGameStateMessage();
//     nextTurn();
//     players[turn].requestMove();
//   }
// }

/**
*
* This playCard is used for Networking
*
*/
// void CrazyEightsLogic::playCard(Card& card)
// {
//
//
//   discardPile.push_back(card);
//   players[turn].removeCardFromHand(card);
// }

void CrazyEightsLogic::playCard(Card& card)
{
  int selection;
  // Suit selection;

  if (card.getValue() == 8)
  {
    std::cout << "You played an 8.  Select a suit: " << std::endl;
    std::cout << "1 - Hearts" << std::endl;
    std::cout << "2 - Spades" << std::endl;
    std::cout << "3 - Clubs" << std::endl;
    std::cout << "4 - Diamonds" << std::endl;
    std::cin >> selection;
    // players[turn].requestSuit
//////////////////////////////////////////////////////////////////
    // receivedSuit will return a suit
    // this part below should be separate function if request suit working
    while (selection < 1 || selection > 4)
    {
      std::cout << "Invalid selection.  Select a suit: " << std::endl;
      std::cout << "1 - Hearts" << std::endl;
      std::cout << "2 - Spades" << std::endl;
      std::cout << "3 - Clubs" << std::endl;
      std::cout << "4 - Diamonds" << std::endl;
      std::cin >> selection;
    }

    switch (selection)
    {
    case 1:
      currentSuit = HEARTS;
      break;
    case 2:
      currentSuit = SPADES;
      break;
    case 3:
      currentSuit = CLUBS;
      break;
    case 4:
      currentSuit = DIAMONDS;
      break;
    default:
      currentSuit = card.getSuit();
      break;
    }
  }
  discardPile.push_back(card);
  players[turn].removeCardFromHand(card);
}

void CrazyEightsLogic::drawCard()
{
  players[turn].insertCardToHand(deck.back());
  deck.pop_back();
}

void CrazyEightsLogic::nextTurn()
{
  turn = (turn + 1) % players.size();
}

void CrazyEightsLogic::setCardsDrawnCounter(int numDrawn)
{
  cardsDrawnCounter = numDrawn;
}

int CrazyEightsLogic::getCardsDrawnCounter()
{
  return cardsDrawnCounter;
}

int CrazyEightsLogic::calculateScore(std::vector<Player> players)
{
  int totalScore = 0;
  std::vector<Card> playerHand;

  for (int i = 0; i < players.size(); i++)
  {
    playerHand = players[i].getHand();

    for (int j = 0; j < playerHand.size(); j++)
    {
      totalScore += getCardScoreValue(playerHand[j]);
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
