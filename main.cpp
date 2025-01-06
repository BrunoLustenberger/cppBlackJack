#include <iostream>
#include "cards_test.h"
#include "dealer_test.h"
#include "dealer.h"
using namespace std;

/**
* .
*/

 int main() {
 
    cout << "testing Black Jack computations";
    cout << endl;

    testCards();
    testDealer();

#ifdef MINI_BLACK_JACK
    double ew = expectedWinOnStand({4,3}, 5, true);
#else
    double ew = expectedWinOnStand({8,9}, 12, true);
#endif
    cout << "expected win on stand" << ew << std::endl;

    return 0;
 }
//(prevent eol warning)
