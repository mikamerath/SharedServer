//The smart AI works by calling the makeMove() function when it is the AI's turn.  makeMove returns the a card object (the best card) to be played in the AI's hand.
//need to access the AI's hand, I'm calling it "hand" in the code below.
//need to access the top card on the discard pile, which I'm calling "topDiscard" and the object type is Card.
//I have a function pickSuit down below when the AI plays an 8 it will smartly pick which suit.  Need to have a way for the AI to pass the suit to the game.


//check suit and see if it matches, then check value to see if one mathces of that.  If neither,
//then look for an 8 to play and play an 8 with the most suit in your hand.
Card makeMove()
{
  //look for valid suit card
  for (int i = 0; i < hand.size(); ++i)
  {
    if (hand[i].suit == topDiscard.suit)
    {
      return hand[i];
    }
  }

  //no valid suit card found, look for a valid value card
  for (int i = 0; i < hand.size(); ++i)
  {
    if (hand[i].value == topDiscard.value)
    {
      return hand[i];
    }
  }

  //neither suit nor value found, play an 8
  var index = getEightIndex();
  if (index >= 0) //have an 8
  {
    return hand[index];

    //choosing suit
    //Suit highestSuit = getHighestSuit();
    //pickSuit(highestSuit);
  }
  else //do not have an 8
  {
    return undefinedCard; //put an undefined card to draw here
  }
}


Suit getHighestSuit()
{
  int numberOfHearts = getSuitDistribution(Suit::HEARTS);
  int numberOfSpades = getSuitDistribution(Suit::SPADES);
  int numberOfClubs = getSuitDistribution(Suit::CLUBS);
  int numberOfDiamonds = getSuitDistribution(Suit::DIAMONDS);

  if (numberOfHearts > numberOfSpades && numberOfHearts > numberOfClubs && numberOfHearts > numberOfDiamonds)
  {
    return Suit::HEARTS;
  }
  else if (numberOfSpades > numberOfHearts && numberOfSpades > numberOfClubs && numberOfSpades > numberOfDiamonds)
  {
    return Suit::SPADES;
  }
  else if (numberOfClubs > numberOfHearts && numberOfClubs > numberOfSpades && numberOfClubs > numberOfDiamonds)
  {
    return Suit::CLUBS;
  }
  else if (numberOfDiamonds > numberOfHearts && numberOfDiamonds > numberOfSpades && numberOfDiamonds > numberOfClubs)
  {
    return Suit::DIAMONDS;
  }
  return highestSuit;
}


int getSuitDistribution(Suit selectedSuit)
{
  int numberOfSuitedCards = 0;
  for (int i = 0; i < hand.size(); ++i)
  {
    if (hand[i].suit == selectedSuit && hand[i].value != 8)
    {
      numberOfSuitedCards++;
    }
  }
  return numberOfSuitedCards;
}

//check if there is an eight in the hand
int getEightIndex()
{
  for (int i = 0; i < hand.size(); ++i)
  {
    if (hand[i].value == 8)
    {
      return i;
    }
  }
  return -1;
}


