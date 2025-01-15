#ifndef CARDS_H
#define CARDS_H

#include <vector>
#include <set>

const int nrofCardsPerCardNrInDeck = 4;
    // Note: in blackjack, the suit of a card is irrelevant
    // e.g. we just have 4 kings in each deck.

void setMiniBlackJack(bool on);

void setnrofDecks(int n);

int highestCardNr();
int highestCardValue();
int dealerMustStandOn();
int aceSoftValue();
int goalValue();
int nrofDecks();
int nrofCardsPerCardNrInGame();

/**
 * A hand is a sequence of cards. The order of the cards is relevant, when
 * the value of an ace in a dealer hand must be determined. 
 * We use std::vector to represent hands.
 */

typedef std::vector<int> Hand;

/**
 * Computing the value of a hand. 
 * The rules for dealer and player hands are different because of the way aces are counted.
 */
int playerHandValue(const Hand& hand);
int dealerHandValue(const Hand& hand);

/**
 * Indicates a hand with black jack
 */
bool blackJack(const Hand& hand);

/**
 * Represent a hand as string
 */
std::string handToString(const Hand& hand);

/**
 * Probability of a cardNr given hands of player and dealer
 * Probability of cardNr n is at index n-1
 */
typedef std::vector<double> CardProbabilities;
void getCardProbabilities (CardProbabilities& cardProbabilites, const Hand& playerHand, const Hand& dealerHand);

/**
 * Represent a probability as string
 */
std::string probabilityToString(double probability);


/**
 * Represent an expected win as string
 */
std::string expectedWinToString(double expectedWin);

/**
 * Set of cards. Cards with same cardNr are elements with multiplicity
 */
typedef std::multiset<int> CardSet;

/**
 * All cards remaining given hand of player and dealer.
 * When both hands are empty, gets all cards of the game
 */
void getRemainingCards(CardSet& cards, const Hand& playerHand, const Hand& dealerHand);

#endif
