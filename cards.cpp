#include <algorithm> // For std::min
#include <sstream>
#include <iomanip>
#include <cassert>
#include <iostream>
#include "cards.h"

// configuration
// -------------

//default: real blackjack
int g_nrofDecks = 6;
bool g_miniBlackjack = false;
int g_highestCardNr = 13; //king
  // cards have numbers from 1 to highestCardNr()
int g_highestCardValue = 10; 
  //cardNr >= highestCardValue() --> value of this card is highestCardValue()
int g_dealerMustStandOn = 17;
int g_aceSoftValue = 11;
int g_goalValue = 21;

void setnrofDecks(int n) {
    assert(n >= 1);
    g_nrofDecks = n;
}

void setMiniBlackJack(bool on) {
    g_miniBlackjack = on;
    if (g_miniBlackjack) {
        g_highestCardNr = 5;
        g_highestCardValue = 5; 
        g_dealerMustStandOn = 9;
    } else {
        g_highestCardNr = 13;
        g_highestCardValue = 10; 
        g_dealerMustStandOn = 17;
    }
    g_aceSoftValue = g_highestCardValue + 1;
    g_goalValue = g_highestCardValue + g_aceSoftValue;
}

int highestCardNr() {return g_highestCardNr;}

int highestCardValue() {return g_highestCardValue;}

int dealerMustStandOn() {return g_dealerMustStandOn;}

int aceSoftValue() {return g_aceSoftValue;}

int goalValue() {return g_goalValue;}

int nrofDecks() {return g_nrofDecks;}

int nrofCardsPerCardNrInGame() {return nrofCardsPerCardNrInDeck * g_nrofDecks;}



//sum the cardValues, counting all aces with 1.
//note, whether an ace occurs
void simpleSum(int& sum, bool& aceFound, const Hand& hand) {
    sum = 0;
    aceFound = false;
    Hand::const_iterator vi;
    for (vi = hand.begin(); vi != hand.end(); vi++)
    {
        int value = std::min(*vi,g_highestCardValue);
        sum += value;
        aceFound = aceFound || (*vi == 1);
    }
}

int playerHandValue(const Hand& hand) {
    //sum the cardValues, counting all aces with 1
    bool aceFound;
    int sum;
    simpleSum(sum, aceFound, hand);
    //check, whether first ace can be counted with aceSoftValue()
    if (aceFound) {
        int sum2 = sum + g_highestCardValue; //cf. definition of aceSoftValue()
        if (sum2 <= g_goalValue) {
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
        int value = std::min(*vi,g_highestCardValue);
        sum += value;
        if (!aceFound && value == 1) {
            aceFound = true;
            int sum2 = sum + g_highestCardValue; //cf. definition of aceSoftValue()
            if (sum2 <= g_goalValue) {
                sum = sum2;
            }
        }
    }
    // result
    return sum;
}

bool blackJack(const Hand& hand) {
    return  hand.size() == 2 && 
            (   (hand[0] == 1 && hand[1] >= g_highestCardValue) ||
                (hand[0] >= g_highestCardValue && hand[1] == 1)
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

void stringToHand(const std::string& s, Hand& hand, std::string& errorMessage) {
    size_t l = s.length();
    hand.resize(l);
    errorMessage = "";
    int cardNr;
    for (int n = 0; n < l; n++) {
        charToCardNr(s[n], cardNr, errorMessage);
        if (errorMessage != "") {return;}
        hand[n] = cardNr;
    }
}

void charToCardNr(char c, int& cardNr, std::string& errorMessage) {
    int nc= static_cast<int>(c) - static_cast<int>('0');
    errorMessage = "";
    if (g_miniBlackjack) {
        if (1 <= nc && nc <= g_highestCardNr) {
            cardNr = nc;
            return;
        }
        errorMessage = "invalid char: ";
        errorMessage.push_back(c);
    } else {
        if (1 <= nc && nc <= 9) {
            cardNr = nc;
            return;
        } else {
            switch(c) {
            case 'X':
                cardNr = 10;
                break;
            case 'J':
                cardNr = 11;
                break;
            case 'Q':
                cardNr = 12;
                break;
            case 'K':
                cardNr = 13;
                break;
            default:
                errorMessage = "invalid char: ";
                errorMessage.push_back(c);
            }
        }
    }
}

void getCardProbabilities (CardProbabilities& cardProbabilites, const Hand& playerHand, const Hand& dealerHand) {
    CardSet remainingCards;
    getRemainingCards(remainingCards, playerHand, dealerHand);
    cardProbabilites.resize(g_highestCardNr);
    double nrofRemainingCards = double(remainingCards.size());
    for (int n = 1; n <= g_highestCardNr; n++) {
        cardProbabilites[n-1] = remainingCards.count(n)/nrofRemainingCards;
    }
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
        for (int n = 1; n <= g_highestCardNr; n++) {
            for (int count = 1; count <= nrofCardsPerCardNrInGame(); count++) {
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


