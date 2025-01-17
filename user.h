#ifndef USER_H
#define USER_H

#include "cards.h"


/**
 * Gets all input from user for entire program run.
 * nrofDecks: from 1 t0 6 is possible
 * mini: true for mini blackjack, else false
 * playerHand: the cards of the user
 * dealerCard: the card of the dealer
 * printDealerTree: print the decision tree of the dealer for player choosing stand
 * printPlayerTree: print the decision tree of the player choosing hit
 * errorMessage: if emtpy, ok.
 */

void getUserInput(int& nrofDecks, bool& mini, Hand& playerHand, int& dealerCardNr, 
    bool& printDealerTree, bool& printPlayerTree, std::string& errorMessage);

#endif
