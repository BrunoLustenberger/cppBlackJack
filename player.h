#ifndef PLAYER_H
#define PLAYER_H

#include "cards.h"


/**
 * Compute the expected win of the player when they HIT, i.e. draw at least 1 additional card.
 * The hand of the player and first card card of the dealer are given.
 * The given hand of the player can be any hand, i.e. can contain more than 2 cards.
 * A bet of 1$ is assumed.
 * Optionally the entire tree of possible draws for the player is printed to std::cout.
 * In this tree, each node contains the expected wins for STAND and HIT.
 * Precondition: the playerHand is not a bust
 */
double expectedWinOnHit(const Hand& playerHand, int dealerCard, bool printTree);

#endif
