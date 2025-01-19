
#include <cassert>
#include <list>
#include <iostream>
#include "cards.h"
#include "dealer.h"

Hand gpHand; //global playerHand, instead of static
int gpValue; //global value of playerHand

class DealerNode {
public: //everything, as the class is internal

    //static Hand& playerHand;//linker complains, see belwo

    Hand dealerHand;
    double probability; //to reach this node from the parent node
    double expectedWin; //if this node is reached

    //the child nodes
    std::list<DealerNode> children;

    DealerNode(const Hand& dH, double p) {
        dealerHand = dH;
        probability = p;
        children = {};
    }

    /**
     * Compute the expected win, if the this dealerHand has been reached.
     * Case0:  bust. The player wins.
     * Case1:  dealer must stand. Then the values of dealerHand and playerHand are compared
     * Case2:  dealer must draw. Then the childnode for each possible next card is created
     *         and the probability for drawing the card is noted. Then each childnode is
     *         evaluated in turn. Finally, the weighted sum of the expectedWins gives the
     *         expectedWin of this node.  
     */
    void evaluate() {
        int dValue = dealerHandValue(dealerHand);
        if (dValue > goalValue()) {
            //case0
            expectedWin = 1.0;
        }
        else if (dValue >= dealerMustStandOn()) {
            //case1
            assert(dealerHand.size() >= 2);
            if (blackJack(gpHand) && blackJack(dealerHand)) {
                expectedWin = 0.0;
            } else if (blackJack(gpHand) && !blackJack(dealerHand)) {
                expectedWin = 1.5;
            } else if (!blackJack(gpHand) && blackJack(dealerHand)) {
                expectedWin = -1.0;
            } else if (gpValue == dValue) {
                expectedWin = 0.0;
            } else if (gpValue > dValue) {
                expectedWin = 1.0;
            } else if (gpValue < dValue) {
                expectedWin = -1.0;
            } else {
                assert(false);
            }
        } else {
            //case2
            //get proability of each card
            CardProbabilities cps;
            getCardProbabilities(cps, gpHand, dealerHand);
            //make the list of children, at the same time, evaluate each node and update weighted sum
            double weightedSum = 0.0;
            for (int cardNr = 1; cardNr <= highestCardNr(); cardNr++) {
                //create child node
                Hand h = dealerHand;
                h.push_back(cardNr);
                DealerNode child(h,cps[cardNr-1]);
                //evaluate
                child.evaluate();
                //sum
                weightedSum += child.probability * child.expectedWin;
                //insert into list
                children.push_back(child);
            }
            //note expected win
            expectedWin = weightedSum;
        }
    }

    void print(const unsigned int level) {
        //print line for this node
        for (unsigned int n = 0; n < level; n++) {
            std::cout << "\t";
        }
        std::cout << handToString(dealerHand);
        std::cout << " " << probabilityToString(probability);
        std::cout << " " << expectedWinToString(expectedWin);
        std::cout << std::endl;
        //print the children
        std::list<DealerNode>::iterator li;
        for (li = children.begin(); li != children.end(); li++) {
            (*li).print(level+1); //*li.print not accepted
        }
    }

};

double expectedWinOnStand(const Hand& playerHand, int dealerCard, bool printTree) {
    assert(playerHandValue(playerHand) <= goalValue()); //not a bust
    assert(playerHand.size() >= 2); //otherwise no stand
    //create the root node containing this card
    //DealerNode::playerHand = playerHand; -- linker complains about "unefined symbols"
    gpHand = playerHand; //workaround: global var
    gpValue = playerHandValue(gpHand); //dito
    Hand dealerHand = {dealerCard};
    DealerNode rootNode(dealerHand, 1.0);
    //evaluate the node
    rootNode.evaluate();
    //print if enabled
    if (printTree) {
        std::cout << "player hand: " << handToString(playerHand) 
                  << " dealer card: " << handToString(dealerHand)
                  << std::endl;
        std::cout << "each line shows dealer hand, probability, expected win" << std::endl;
        rootNode.print(0);
    }
    //return its expected win.
    return rootNode.expectedWin;
}



