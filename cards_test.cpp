#include <cassert>
#include "cards.h"
#include "cards_test.h"

void testPlayerHandValue() {
    assert(playerHandValue({highestCardNr,1}) == goalValue);
    assert(playerHandValue({1,highestCardNr}) == goalValue);
    assert(playerHandValue({highestCardValue,1}) == goalValue);
    assert(playerHandValue({1,highestCardValue}) == goalValue);
    assert(playerHandValue({1,highestCardValue-1,1}) == goalValue);
    assert(playerHandValue({1,highestCardValue-1,2}) == highestCardValue+2);
    assert(playerHandValue({1,highestCardValue-2,1}) == goalValue-1);
    assert(playerHandValue({1,1,1}) == aceSoftValue+2);
}

void testDealerHandValue() {
    assert(dealerHandValue({highestCardNr,1}) == goalValue);
    assert(dealerHandValue({1,highestCardNr}) == goalValue);
    assert(dealerHandValue({highestCardValue,1}) == goalValue);
    assert(dealerHandValue({1,highestCardValue}) == goalValue);
    assert(dealerHandValue({1,highestCardValue-1,1}) == goalValue);
    assert(dealerHandValue({1,highestCardValue-1,2}) == goalValue+1);
    assert(dealerHandValue({1,highestCardValue-2,1}) == goalValue-1);
    assert(dealerHandValue({1,1,1}) == aceSoftValue+2);
    #ifdef MINI_BLACK_JACK
        assert(dealerHandValue({5,2,1}) == 8); 
    #endif
}

void testBlackJack() {
    assert(blackJack({highestCardNr,1}));
    assert(blackJack({1,highestCardNr}));
    assert(blackJack({highestCardValue,1}));
    assert(blackJack({1,highestCardValue}));
    assert(!blackJack({highestCardNr,highestCardNr}));
    assert(!blackJack({1,1}));
}


void testCards() {
    testPlayerHandValue();
    testDealerHandValue();
    testBlackJack();
}

