
/*
 * Card Class
 *
 * -David Browning, Ligia Frangello & Katie Sweet
 *
 * The purpose of this file is to allow others to build a card object.
 * Cards contain a suit and a value.
 * Suit is an enum {HEARTS}
 *
 * The constuctor accepts the suit enum and one integer.
 * The suit enum (HHEARTS, SPADES, CLUBS, DIAMONDS, JOKER) determines the suit.
 * The integer (1-13) determines the value. Value is on a 1 based index for easier
 * scoring.
 *
 */

#ifndef CARD_CPP
#define CARD_CPP

#include <string>
#include <iostream>

enum Suit { HEARTS, SPADES, CLUBS, DIAMONDS, JOKER, UNDEFINED };

struct Card {
  //	card(){} Commented out the default constructor as an empty card object
  //is meaningless.
  
  Suit suit;
  int value;
  int id;
  int numCardsConstructed;
  


  bool operator<(const Card& a) const
  {
      return id < a.id; 
  }

  Card(Suit su){
      id = ++numCardsConstructed;
      suit = su;
      if (su == UNDEFINED){
          value =-1;
      }
      else{
        std::cout << "Error. Cannot instantiate a card without a value." << std::endl;
        throw(2);
      }
  }

  Card(Suit su, int val) {
      id = ++numCardsConstructed;
      // Assign suit
      suit = su;

      // Assign Value
      if (su == JOKER) {
        value = -1; // a card of type JOKER will take any value.
      }
      else if (val < 1 || val > 13) {
        // Values are from 1 to 13 corrosponding from Ace - King.
        std::cout << "Error: Tried to instantiate a card of undefined value"
                  << std::endl;
        throw(2);
      }

      else {
        value = val;
      }
  }

  ~Card(){}

 void print(){
	std::string s;
	switch(suit){
		case(HEARTS):s = "Hearts";
			break;
		case(SPADES):s="Spades";
			break;
		case(DIAMONDS):s="Diamonds";
			break;
		case(CLUBS):s="Clubs";
			break;
		default:{s= "?";}	
	}
	std::cout << value << " of " << s << std::endl;
  }

void tableprint(){
	std::string s;
	switch(suit){
		case(HEARTS):s = "Hearts";
			break;
		case(SPADES):s="Spades";
			break;
		case(DIAMONDS):s="Diamonds";
			break;
		case(CLUBS):s="Clubs";
			break;
		default:{s= "?";}	
	}
	std::cout << "................................." <<  value << " of " << s << ".............................." << std::endl;
  }

  int getSuit() { return suit; }
  int getValue() { return value; }

  bool operator==(const Card &other) const {
	  return (suit == other.suit && value == other.value);
  }
};

#endif


/*
 * Card Struct
 *
 * -David Browning
 *
 * The purpose of this file is to allow others to build a card object.
 * Cards contain a suit and a value, both of type int.
 *
 * The constuctor accepts two integers, the first (0-4) determines the suit, the
 * second (1-14) determines the value. Value is on a 1 based index for easier
 * scoring.
 *
 * Might be overkill.
 *

 void print(){
	std::string s;
	switch(suit){
		case(HEARTS):s = "Hearts";
			break;
		case(SPADES):s="Spades";
			break;
		case(DIAMONDS):s="Diamonds";
			break;
		case(CLUBS):s="Clubs";
			break;
		default:{s= "?";}	
	}
	std::cout << value << " of " << s << std::endl;
  }

#include <iostream>

// If there is a controversial aspect to this file it is the following
// enumeration.
// I'm thinking that if this is declared in the card file (and therfore
// accessible everywhere) it would be beneficial to the rest of the program.
// Very open to changing if others feel differently.

enum suit { HEARTS, SPADES, CLUBS, DIAMONDS, JOKER, UNDEF };

struct card {
  //	card(){} Commented out the default constructor as an empty card object
  // is meaningless.
  ~card() {}
  suit _s;
  int value;
  card(suit su, int val) {
    try {
      _s = su;
      if (_s == JOKER) {
        value = val; // a card of type JOKER will take any value.
      } else if (val < 1 || val > 14) {
        // Values are from 1 to 14 corrosponding from Ace - King.
        std::cout << "Error: Tried to instantiate a card of undefined value"
                  << std::endl;
        throw(2);
      } else {
        value = val;
      }

    } catch (int n) {
      std::cout << "Error: " << n << " an illegal card was attempted"
                << std::endl;
      _s = UNDEF;
      value = -1;
      return;
    }
  }
  void print() { // Prints the suit and value of the card. e.g. card c(2, 7);
                 // c.print(); will print "CLUBS 7"
    switch (_s) {
    case (HEARTS): {
      std::cout << "HEARTS ";
    } break;
    case (SPADES): {
      std::cout << "SPADES ";
    } break;
    case (CLUBS): {
      std::cout << "CLUBS ";
    } break;
    case (DIAMONDS): {
      std::cout << "DIAMONDS ";
    } break;
    case (JOKER): {
      std::cout << "JOKER ";
    } break;
    default: { std::cout << "UNDEFINED "; } //
    }

    std::cout << value << std::endl;
  }
  int getSuit() { return _s; }
  int getValue() { return value; }
};

bool testCardStruct() {
  bool pass = false;
  // Create all Cards in a 52 card deck. if getSuit() and getValue() return the
  // correct value, the test passes.
  for (int i = 0; i < 4; i++) {
    for (int j = 1; j < 14; j++) {
      if (i == 0) {
        card c(HEARTS, j);
        // c.print();
        pass = true;
      } else if (i == 1) {
        card c(SPADES, j);
        // c.print();
        pass = true;
      } else if (i == 2) {
        card c(CLUBS, j);
        // c.print();
        pass = true;
      } else if (i == 3) {
        card c(DIAMONDS, j);
        // c.print();
        pass = true;
      }
    }
    pass = false;
  } // Disclaimer, I realize that this isn't a very good test, but so long as
    // all cards can be constructed, the test should pass.

  // Create a joker. Once again, if getSuit() and getValue() return the correct
  // value, the test passes.
  card j(
      JOKER,
      100); // purposefully demonstrate any value is assigned to a joker card.
  if (j.getValue() == 100) {
    // j.print();
    pass = true;
  } else {
    pass = false;
  }
  // card c(-1, 15);// spits out an error;
  // card d("string", "string"); //Won't compile.
  // card e('c', 'c');// spits out an error;
  // card f(2.3, 8.7);// works if you really want to use a float or somethihng.
  return pass;
}*/

