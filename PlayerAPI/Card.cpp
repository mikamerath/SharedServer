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

#include <iostream>

enum Suit { HEARTS, SPADES, CLUBS, DIAMONDS, JOKER };

class Card {
  //	card(){} Commented out the default constructor as an empty card object
  //is meaningless.
  ~card() {}
  Suit suit;
  int value;

  card(Suit su){
      suit = su;
      if (su == JOKER){
          value =-1;
      }
      else{
        std::cout << "Error. Cannot instantiate a card without a value." << std::endl;
        throw(2);
      }
  }

  card(Suit su, int val) {
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

  int getSuit() { return suit; }
  int getValue() { return value; }
};

// bool testCardStruct() {
//   bool pass = false;
//   // Create all Cards in a 52 card deck. if getSuit() and getValue() return the
//   // correct value, the test passes.
//   for (int i = 0; i < 4; i++) {
//     for (int j = 1; j < 14; j++) {
//       card c(i, j);
//       if (c.getSuit() == i && c.getValue() == j) {
//         pass = true;
//       } else {
//         pass = false;
//       }
//     }
//   }
//
//   // Create a joker. Once again, if getSuit() and getValue() return the correct
//   // value, the test passes.
//   card j(
//       4,
//       100); // purposefully demonstrate any value is assigned to a joker card.
//   if (j.getSuit() == 4 && j.getValue() == 100) {
//     pass = true;
//   } else {
//     pass = false;
//   }
//   // card c(-1, 15);// spits out an error;
//   // card d("string", "string"); //Won't compile.
//   // card e('c', 'c');// spits out an error;
//   // card f(2.3, 8.7);// works if you really want to use a float or somethihng.
//   return pass;
// }
