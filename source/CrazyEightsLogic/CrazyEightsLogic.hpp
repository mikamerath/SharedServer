#ifndef CRAZY_EIGHTS_LOGIC_H
#define CRAZY_EIGHTS_LOGIC_H
/*
 * Crazy Eights Logic Class
 * 
 * This class holds the logic to play a game of Crazy Eights
 *
 * 
 * 
 */
// maybe include Game.hpp, Player.hpp, Card.cpp, etc.
class CrazyEightsLogic : public Game
{
  private:
      Suit currentSuit;
  public:
    CrazyEightsLogic();
};
#endif
