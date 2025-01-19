#ifndef DEALER_H
#define DEALER_H

#include "cards.h"


/**
 * Compute the expected win of the player when they STAND, i.e. don't draw any more cards.
 * The dealer must now draw cards until they must stop.
 * The hand of the player and first card card of the dealer are given.
 * The given hand of the player can be any hand, i.e. can contain more than 2 cards.
 * A bet of 1$ is assumed.
 * Optionally the entire tree of possible draws for the dealer is printed to std::cout.
 * In this tree, each node contains the expected win for STAND.
 * Precondition: the playerHand is not a bust
 */

  
double expectedWinOnStand(const Hand& playerHand, int dealerCard, bool printTree);

#endif
