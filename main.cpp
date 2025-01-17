#include <iostream>
#include "cards_test.h"
#include "dealer_test.h"
#include "dealer.h"
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

    double ew = expectedWinOnStand(playerHand, dealerCardNr, printDealerTree);

    /*
    setMiniBlackJack(true);
    double ew = expectedWinOnStand({4,3}, 5, true);
   */
 
    cout << "expected win on stand" << ew << endl;

    return 0;
 }
//(prevent eol warning)
