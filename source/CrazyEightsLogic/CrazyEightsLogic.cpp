#include "CrazyEightsLogic.hpp"
#include <iostream>

CrazyEightsLogic::CrazyEightsLogic(std::vector<Player>& netPlayers)
{
    players = netPlayers;
    deck = initializeDeck();
    std::cout << "Initial deck size: " << deck.size() << std::endl;
    deal(5);
    std::cout << "Deck size after deal: " << deck.size() << std::endl;
    turn = 0;

}

void CrazyEightsLogic::deal(int numCards)
{
    for (int i=0; i< players.size(); i++)
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
    for (int i=0; i<playerHand.size(); i++)
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

    std::cout << "Is In Hand: " << isInHand << std::endl;
    std::cout << "Is valid: " << isValidPlay << std::endl;

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
    for (int i=0; i<hand.size(); i++)
    {
        std::string suit = convertSuitToString(hand[i].getSuit());
        std::string rank = convertRankToString(hand[i].getValue());
        std::cout << "Player Card " << i << ": " << rank << " of " << suit << std::endl;
    }
}

int CrazyEightsLogic::getTurn()
{
    return turn;
}

void CrazyEightsLogic::playCard(Card &card)
{
    int selection;
    if (card.getValue() == 8)
    {
        std::cout << "You played an 8.  Select a suit: " << std::endl;
        std::cout << "1 - Hearts" << std::endl;
        std::cout << "2 - Spades" << std::endl;
        std::cout << "3 - Clubs" << std::endl;
        std::cout << "4 - Diamonds" << std::endl;
        std::cin >> selection;

        while (selection < 1 || selection > 4)
        {
            std::cout << "Invalid selection.  Select a suit: " << std::endl;
            std::cout << "1 - Hearts" << std::endl;
            std::cout << "2 - Spades" << std::endl;
            std::cout << "3 - Clubs" << std::endl;
            std::cout << "4 - Diamonds" << std::endl;
            std::cin >> selection;
        }

        switch (selection) {
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
int CrazyEightsLogic::getNumCardsDrawnCounter()
{
    return cardsDrawnCounter;
}

std::string CrazyEightsLogic::convertSuitToString(Suit suit)
{
    std::string cardSuit;
    switch(suit)
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

    switch(value)
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
