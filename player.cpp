
#include <cmath> // for fmax
#include <cassert>
#include <list>
#include <iostream>
#include "cards.h"
#include "dealer.h"
#include "player.h"

int sDealerCard; //global, see below

class PlayerNode {
public: //everything, as the class is internal

    //static int sDealerCard; // linker: Undefined symbols for architecture x86_64:

    Hand playerHand; //if this node is reached
    double probability; //to reach this node from the parent node
    double ewStand; //expected win on stand, if this node is reached
    double ewHit; //expected win on hit, if this node is reached

    //the child nodes
    std::list<PlayerNode> children;

    PlayerNode(const Hand& pH, double p) {
        playerHand = pH;
        probability = p;
        children = {};
    }

    /**
     * Compute the expected win for stand an hit, if the this dealerHand has been reached.
     * Case0:  bust. The dealer wins. Both expected wins are set to -1.0.
     * Case1:  The expected win on stand is computed. 
     *     a)  player must must stand. Then expected win on hit is set to -1.0
     *     b)  expected win on hit is computed by evaluating the child nodes.
     *         The childnode for each possible next card is created and the probability for 
     *         drawing the card is noted. Then each childnode is evaluated in turn. 
     *         Finally, the weighted sum of max(ewStand,ewHit) of each childnode gives the
     *         expected win on hit of this node.
     */
    void evaluate() {
        int pValue = playerHandValue(playerHand);
        if (pValue > goalValue()) {
        //case0
            ewStand = -1.0;
            ewHit = -1.0;
        } else {
        //case1
            ewStand = expectedWinOnStand(playerHand, sDealerCard, false);
            if (pValue == goalValue()) {
            //case1 a)
                ewHit = -1.0;
            } else {
            //case1 b)
                //get proability of each card
                CardProbabilities cps;
                getCardProbabilities(cps, playerHand, {sDealerCard});
                //make the list of children, at the same time, evaluate each node and update weighted sum
                double weightedSum = 0.0;
                for (int cardNr = 1; cardNr <= highestCardNr(); cardNr++) {
                    //create child node
                    Hand h = playerHand;
                    h.push_back(cardNr);
                    PlayerNode child(h,cps[cardNr-1]);
                    //evaluate
                    child.evaluate();
                    //sum
                    weightedSum += child.probability * fmax(child.ewStand, child.ewHit);
                    //insert into list
                    children.push_back(child);
                }
                //note expected win
                ewHit = weightedSum;
            }
        }
    }

    void print(const unsigned int level) {
        //print line for this node
        for (unsigned int n = 0; n < level; n++) {
            std::cout << "\t";
        }
        std::cout << handToString(playerHand);
        std::cout << " " << probabilityToString(probability);
        std::cout << " " << expectedWinToString(ewStand);
        std::cout << " " << expectedWinToString(ewHit);
        std::cout << std::endl;
        //print the children
        std::list<PlayerNode>::iterator li;
        for (li = children.begin(); li != children.end(); li++) {
            (*li).print(level+1); //*li.print not accepted
        }
    }

};


double expectedWinOnHit(const Hand& playerHand, int dealerCard, bool printTree) {
    assert(playerHandValue(playerHand) <= goalValue()); //not a bust
    assert(playerHand.size() >= 2); //otherwise no choice between stand or hit
    //create the root node containing this situation
    //PlayerNode::sDealerCard = dealerCard;
    sDealerCard = dealerCard;
    PlayerNode rootNode(playerHand, 1.0);
    //evaluate the node
    rootNode.evaluate();
    //print if enabled
    if (printTree) {
        std::cout << "player hand: " << handToString(playerHand) 
                  << " dealer card: " << handToString({dealerCard})
                  << std::endl;
        std::cout << "each line shows player hand, probability, "
                  << "expected win on stand, expected win on hit" << std::endl;
        rootNode.print(0);
    }
    //return its expected win.
    return rootNode.ewHit;
}



