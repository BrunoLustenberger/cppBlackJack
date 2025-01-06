#ifndef DEALER_H
#define DEALER_H

#include "cards.h"


/**
 * Compute the expected win of the player given a hand of the player and first card of the dealer.
 * It is assumed, that the player stands and thus the dealer draws until they must stop.
 * Optionally the entire tree of possible cards for the dealer is printed to std::cout.
 * A bet of 1$ is assumed.
 * precondition: the playerHand is not a bust
 */
double expectedWinOnStand(const Hand& playerHand, int dealerCard, bool printTree);

#endif
