#include <algorithm> // For std::min
#include <sstream>
#include <iomanip>
#include <cassert>
#include <iostream>
#include "cards.h"

//sum the cardValues, counting all aces with 1.
//note, whether an ace occurs
void simpleSum(int& sum, bool& aceFound, const Hand& hand) {
    sum = 0;
    aceFound = false;
    Hand::const_iterator vi;
    for (vi = hand.begin(); vi != hand.end(); vi++)
    {
        int value = std::min(*vi,highestCardValue);
        sum += value;
        aceFound = aceFound || (*vi == 1);
    }
}

int playerHandValue(const Hand& hand) {
    //sum the cardValues, counting all aces with 1
    bool aceFound;
    int sum;
    simpleSum(sum, aceFound, hand);
    //check, whether first ace can be counted with aceSoftValue
    if (aceFound) {
        int sum2 = sum + highestCardValue; //cf. definition of aceSoftValue
        if (sum2 <= goalValue) {
            sum = sum2;
        }
    }
    // result
    return sum;
}

int dealerHandValue(const Hand& hand) {
    //sum the cardValues, counting all aces with 1
    bool aceFound = false;
    int sum = 0;
    Hand::const_iterator vi;
    for (vi = hand.begin(); vi != hand.end(); vi++)
    {
        int value = std::min(*vi,highestCardValue);
        sum += value;
        if (!aceFound && value == 1) {
            aceFound = true;
            int sum2 = sum + highestCardValue; //cf. definition of aceSoftValue
            if (sum2 <= goalValue) {
                sum = sum2;
            }
        }
    }
    // result
    return sum;
}

bool blackJack(const Hand& hand) {
    return  hand.size() == 2 && 
            (   (hand[0] == 1 && hand[1] >= highestCardValue) ||
                (hand[0] >= highestCardValue && hand[1] == 1)
            );
}            

std::string handToString(const Hand& hand) {
    std::ostringstream oss;
    Hand::const_iterator vi;
    for (vi = hand.begin(); vi != hand.end(); vi++) {
        if (*vi < 10) {
            oss << *vi;
        } else if (*vi == 10) {
            oss << 'X';
        } else if (*vi == 11) {
            oss << 'J';
        } else if (*vi == 12) {
            oss << 'Q';
        } else if (*vi == 13) {
            oss << 'K';
        } else {
            assert(false);            
        } 
    }
    return oss.str();
}

void getCardProbabilities (CardProbabilities& cardProbabilites, const Hand& playerHand, const Hand& dealerHand) {
    /* -- simpliefied
    cardProbabilites.resize(highestCardNr);
    for (int n = 1; n <= highestCardNr; n++) {
        cardProbabilites[n-1] = 1.0/highestCardNr;
    }
    */
   /* -- not yet*/
    CardSet remainingCards;
    getRemainingCards(remainingCards, playerHand, dealerHand);
    cardProbabilites.resize(highestCardNr);
    double nrofRemainingCards = double(remainingCards.size());
    for (int n = 1; n <= highestCardNr; n++) {
        cardProbabilites[n-1] = remainingCards.count(n)/nrofRemainingCards;
    }
   /**/
}

std::string probabilityToString(double probability) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(4) << probability;
    return oss.str();
}

std::string expectedWinToString(double expectedWin) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(4) << expectedWin;
    return oss.str();
}

CardSet gAllCards = {};

/**
 * remove each card of hand from the given set cards
 */
void removeCards(CardSet& cards, const Hand& hand) {
    Hand::const_iterator vi;
    for (vi = hand.begin(); vi != hand.end(); vi++) {
        int cardNr = *vi;
        //std::cout << cardNr << " " << cards.count(cardNr) << std::endl;
        auto it = cards.find(cardNr);
        assert(it != cards.end());
        assert(cards.count(cardNr) > 0);
        cards.erase(it);
    }
}

void getRemainingCards(CardSet& cards, const Hand& playerHand, const Hand& dealerHand) {
    //initialize allCards if necessary
    if (gAllCards.empty()) {
        for (int n = 1; n <= highestCardNr; n++) {
            for (int count = 1; count <= nrofCardsPerCardNrInGame; count++) {
                gAllCards.insert(n);
            }
        }
    }
    //get a copy of all cards
    cards = gAllCards;
    //delete the player hand cards
    removeCards(cards, playerHand);
    //delete the dealer hand cards
    removeCards(cards, dealerHand);
}


