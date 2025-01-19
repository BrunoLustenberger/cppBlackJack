#include <iostream>
#include "cards_test.h"
#include "dealer_test.h"
#include "dealer.h"
#include "player.h"
#include "user.h"
using namespace std;

/**
* .
*/

 int main() {
 
    cout << "testing Black Jack computations" << endl;

    setMiniBlackJack(true);
    testCards();
    testDealer();
    setMiniBlackJack(false);
    testCards();
    testDealer();

    int nrofDecks;
    bool mini;
    Hand playerHand;
    int dealerCardNr;
    bool printDealerTree;
    bool printPlayerTree;
    string errorMessage;

    getUserInput(nrofDecks, mini, playerHand, dealerCardNr, 
        printDealerTree, printPlayerTree, errorMessage);

    if (errorMessage != "") {
        cout << "invalid user input: " << errorMessage << endl;
        return 1;
    }

    cout << "Blackjack computations for your input" << endl;

    setnrofDecks(nrofDecks);
    setMiniBlackJack(mini);

    double ewStand = expectedWinOnStand(playerHand, dealerCardNr, printDealerTree);
    double ewHit = expectedWinOnHit(playerHand, dealerCardNr, printPlayerTree);

    cout << "expected win on stand: " << ewStand << endl;
    cout << "expected win on hit: " << ewHit << endl;

    return 0;
 }
//(prevent eol warning)
