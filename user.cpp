#include <iostream>
#include <cassert>
#include <string>
#include "user.h"
using namespace std;

/**
 * Simple Yes No test of string. 
 * If first char of string is y or Y then true, otherwise false
 */
bool stringToYesNo(string s) {
    if (s.length() > 0) {
        char c = s[0];
        return c == 'y' || c == 'Y';
    } else {
        return false;
    }
}

void getUserInput(int& nrofDecks, bool& mini, Hand& playerHand, int& dealerCardNr, 
    bool& printDealerTree, bool& printPlayerTree,std::string& errorMessage) {
    string s;
    char c;

    cout << "number of decks (1..6) : ";
    cin >> nrofDecks;
    if (nrofDecks < 1 || nrofDecks > 6) {
        errorMessage = "wrong number of decks";
        return;
    }

    cout << "mini blackjack (y) or real blackjack (n) ? ";
    cin >> s;
    mini = stringToYesNo(s);

    cout << "player hand : ";
    cin >> s;
    stringToHand(s, playerHand, errorMessage);
    if (errorMessage != "") {return;}

    cout << "dealer card : ";
    cin >> c;
    charToCardNr(c, dealerCardNr, errorMessage);
    if (errorMessage != "") {return;}

    cout << "print dealer tree ? (y) or (n) ";
    cin >> s;
    printDealerTree = stringToYesNo(s);

    cout << "print player tree ? (y) or (n) ";
    cin >> s;
    printPlayerTree = stringToYesNo(s);

}

